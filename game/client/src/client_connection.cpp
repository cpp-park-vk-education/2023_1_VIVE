#include "client_connection.hpp"
#include "boost/bind/bind.hpp"

#include "game.hpp"

using namespace boost::placeholders;

#include <iostream>

ClientConnection::ClientConnection(const std::string &ip, const std::string &port) :
        io_context_(), socket_(io_context_),
        resolver_(io_context_), endpoint_(resolver_.resolve(ip, port)) {
    doConnect();
    read_buffer_.prepare(max_body_size);
}

void ClientConnection::doConnect() {
    std::cout << "\t--- connect: start " << std::this_thread::get_id() << std::endl;
    boost::asio::async_connect(socket_, endpoint_,
                               [this](boost::system::error_code ec, const tcp::endpoint &) {
                                   if (!ec) {
                                       std::cout << "\t--- connect: done " << std::this_thread::get_id() << std::endl;
                                       doReadHeader();
                                   } else {
                                       std::cout << "\t--- connect: failed " << ec.message() << "  "
                                                 << std::this_thread::get_id() << std::endl;
                                   }
                               });
}

void ClientConnection::startIOContext() {
    io_context_.run();
}

void ClientConnection::write(const std::string &body) {

    std::cout << "\t" << body << "size: " << body.size() << std::endl;
    std::string header;
    std::sprintf(header.data(), "%4d", static_cast<unsigned int>(body.size()));
    std::string message(header.data() + body); // добавил перед строкой длину сообщения
    std::cout << "\t>>\"" << message << "\"" << std::endl;

    std::cout << "\t--- start pushing message to write " << std::this_thread::get_id() << std::endl;

    boost::asio::post(io_context_,
                      [this, message]() {
                          write_msgs_.push(message);
                          std::cout << "\t--- message pushed " << std::this_thread::get_id() << std::endl
                                    << std::endl;
                          doWrite();
                      });
}

void ClientConnection::close() {
    boost::asio::post(io_context_, [this]() { socket_.close(); });
}

bool ClientConnection::isConnected() const {
    return socket_.is_open();
}

void ClientConnection::doReadHeader() {
    std::cout << "\t--- read: start reading " << std::this_thread::get_id() << std::endl;
    boost::asio::async_read(socket_,
                            read_buffer_,
                            boost::asio::transfer_exactly(header_size),
                            [this](boost::system::error_code ec, std::size_t /*length*/) {
                                if (!ec) {
                                    std::cout << "\t--- read: done " << std::this_thread::get_id() << std::endl;
                                    std::string read_message_size(net::buffers_begin(read_buffer_.data()),
                                                net::buffers_end(read_buffer_.data()));

                                    std::cout << "\t--- size of read message " << read_message_size << std::endl;
                                    int body_size = decodeHeader(read_message_size);

                                    read_buffer_.consume(read_buffer_.size());
                                    read_buffer_.prepare(max_body_size);

                                    doReadBody(body_size);
                                } else {
                                    std::cout << "\t--- read: failed " << ec.message() << " "
                                              << std::this_thread::get_id() << std::endl;
                                    socket_.close();
                                }
                            });
}

void ClientConnection::doReadBody(int body_size) {
    std::cout << "\t--- read: start reading body  " << std::this_thread::get_id() << std::endl;
    boost::asio::async_read(socket_,
                            read_buffer_,
                            boost::asio::transfer_exactly(body_size),
                            [this](boost::system::error_code ec, std::size_t /*length*/) {
                                if (!ec) {
                                    std::cout << "\t--- read: done " << std::this_thread::get_id() << std::endl
                                              << std::endl;

                                    std::string string_buf{buffers_begin(read_buffer_.data()),
                                                           buffers_end(read_buffer_.data())};
                                    std::cout << "<< " << string_buf << std::endl;

                                    read_buffer_.consume(read_buffer_.size());
                                    read_buffer_.prepare(max_body_size);

                                    GameEngine::getClient()->readMessage(string_buf);

                                    doReadHeader();
                                } else {
                                    std::cout << "\t--- read: failed " << ec.message() << " "
                                              << std::this_thread::get_id() << std::endl;
                                    socket_.close();
                                }
                            });

}

void ClientConnection::doWrite() {

    std::cout << "\t--- write: start " << std::this_thread::get_id() << std::endl;
    boost::asio::async_write(socket_,
                             boost::asio::buffer(write_msgs_.front().data(),
                                                 write_msgs_.front().size()),
                             [this](boost::system::error_code ec, std::size_t /*length*/) {
                                 if (!ec) {
                                     std::cout << "\t--- write: done " << std::this_thread::get_id() << std::endl
                                               << std::endl;
                                     write_msgs_.pop();
                                     std::cout << "size of queue write_msg: " << write_msgs_.size() << std::endl;
                                     if (!write_msgs_.empty()) {
                                         doWrite();
                                     }
                                 } else {
                                     std::cout << "\t--- write: failed " << ec.message() << " "
                                               << std::this_thread::get_id() << std::endl;
                                     socket_.close();
                                 }
                             });
}

int ClientConnection::decodeHeader(const std::string &header_string) {
    int size = 0;
    try {
        size = std::stoi(header_string);
    } catch(const std::exception& e) {
        std::cout << "\t ERROR! " << e.what() << std::endl;
    }
    return size;
}

