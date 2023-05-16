#include "client_connection.hpp"


ClientConnection::ClientConnection(net::io_context &io_context,
                                   const tcp::resolver::results_type &endpoint) :
        io_context_(io_context), socket_(io_context) {
    do_connect(endpoint);
}

void ClientConnection::do_connect(
        const boost::asio::ip::basic_resolver<tcp, boost::asio::any_io_executor>::results_type &endpoint) {
    std::cout << "\t--- connect: start " << std::this_thread::get_id() << std::endl;
    boost::asio::async_connect(socket_, endpoint,
                               [this](boost::system::error_code ec, const tcp::endpoint &) {
                                   if (!ec) {
                                       std::cout << "\t--- connect: done " << std::this_thread::get_id() << std::endl;
                                       do_read_header();
                                   } else {
                                       std::cout << "\t--- connect: failed " << ec.message() << "  "
                                                 << std::this_thread::get_id() << std::endl;
                                   }
                               });
}

void ClientConnection::write(const std::string &body) {
    std::shared_ptr<char> header = std::make_shared<char>();
    std::sprintf(header.get(), "%4d", static_cast<unsigned int>(body.size()));
    std::string message(header.get()); // добавил перед строкой длину сообщения
    message += body;

    std::cout << "\t--- start pushing message to write " << std::this_thread::get_id() << std::endl;
    boost::asio::post(io_context_,
                      [this, message]() {
                          bool write_in_progress = !write_msgs_.empty();
                          write_msgs_.push(message);
                          std::cout << "\t--- message pushed " << std::this_thread::get_id() << std::endl << std::endl;
                          if (!write_in_progress) {
                              do_write();
                          }
                      });
}

void ClientConnection::close() {
    boost::asio::post(io_context_, [this]() { socket_.close(); });
}

void ClientConnection::do_read_header() {
    std::cout << "\t--- read: start reading " << std::this_thread::get_id() << std::endl;
    read_msg_.clear();
    read_msg_size_.clear();
    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_size_.data(), 4),
                            [this](boost::system::error_code ec, std::size_t /*length*/) {
                                if (!ec) {
                                    std::cout << "\t--- read: done " << std::this_thread::get_id() << std::endl;
                                    std::cout << "\t--- size of read message " << read_msg_size_.data() << std::endl;
                                    do_read_body();
                                } else {
                                    std::cout << "\t--- read: failed " << ec.message() << " "
                                              << std::this_thread::get_id() << std::endl;
                                    socket_.close();
                                }
                            });
}

void ClientConnection::do_read_body() {
    std::cout << "\t--- read: start reading body  " << std::this_thread::get_id() << std::endl;

    boost::asio::async_read(socket_,
                            boost::asio::buffer(read_msg_.data(), std::stoll(read_msg_size_)),
                            [this](boost::system::error_code ec, std::size_t /*length*/) {
                                if (!ec) {
                                    std::cout << "\t--- read: done " << std::this_thread::get_id() << std::endl
                                              << std::endl;
                                    std::cout << "<< ";
                                    std::cout << read_msg_.data() << std::endl;
                                    std::cout << "\n";
                                    do_read_header();
                                } else {
                                    std::cout << "\t--- read: failed " << ec.message() << " "
                                              << std::this_thread::get_id() << std::endl;
                                    socket_.close();
                                }
                            });
}

void ClientConnection::do_write() {
    std::cout << "\t--- write: start " << std::this_thread::get_id() << std::endl;
    boost::asio::async_write(socket_,
                             boost::asio::buffer(write_msgs_.front().data(),
                                                 write_msgs_.front().length()),
                             [this](boost::system::error_code ec, std::size_t /*length*/) {
                                 if (!ec) {
                                     std::cout << "\t--- write: done " << std::this_thread::get_id() << std::endl
                                               << std::endl;
                                     write_msgs_.pop();
                                     if (!write_msgs_.empty()) {
                                         do_write();
                                     }
                                 } else {
                                     std::cout << "\t--- write: failed " << ec.message() << " "
                                               << std::this_thread::get_id() << std::endl;
                                     socket_.close();
                                 }
                             });
}



