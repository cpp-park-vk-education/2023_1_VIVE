#include "client_connection.hpp"
#include "boost/bind/bind.hpp"

#include "game.hpp"

using namespace boost::placeholders;

#include <iostream>

ClientConnection::ClientConnection(const std::string &ip, const std::string &port) :
        io_context_(), socket_(io_context_),
        resolver_(io_context_), endpoint_(resolver_.resolve(ip, port)) {
    doConnect();
}

void ClientConnection::doConnect() {
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

    std::cout << ">>" << body << "size: " << body.size() << std::endl;
    std::string header;
    std::sprintf(header.data(), "%4d", static_cast<unsigned int>(body.size()));
    std::string message(header.data() + body); // добавил перед строкой длину сообщения

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
    read_msg_.clear();
    read_msg_size_.clear();
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_size_.data(), 4),
                            [this](boost::system::error_code ec, std::size_t /*length*/) {
                                if (!ec) {
                                    std::cout << read_msg_size_ << std::endl;
                                    std::cout << "\t--- read: done " << std::this_thread::get_id() << std::endl;
                                    std::cout << "\t--- size of read message " << read_msg_size_.data() << std::endl;
                                    doReadBody();
                                } else {
                                    std::cout << "\t--- read: failed " << ec.message() << " "
                                              << std::this_thread::get_id() << std::endl;
                                    socket_.close();
                                }
                            });
}

void ClientConnection::doReadBody() {
    std::cout << "\t--- read: start reading body  " << std::this_thread::get_id() << std::endl;
    int msg_size = 0;
    try {
        msg_size = std::stoi(read_msg_size_);
    }
    catch (const std::exception &e) {
        std::cerr << "Wrong read message size: " << e.what() << std::endl;
    }
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_.data(), msg_size),
                            [this](boost::system::error_code ec, std::size_t /*length*/) {
                                if (!ec) {
                                    std::cout << "\t--- read: done " << std::this_thread::get_id() << std::endl
                                              << std::endl;
                                    std::cout << "<< " << read_msg_.data() << std::endl;
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
