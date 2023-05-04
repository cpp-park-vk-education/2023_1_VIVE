#include "client_connection.hpp"


ClientConnection::ClientConnection(net::io_context &io_context,
                                   const tcp::resolver::results_type &endpoint):
                                   io_context_(io_context), socket_(io_context) {
    do_connect(endpoint);
}

void ClientConnection::write(const Message &msg) {

}

void ClientConnection::close() {

}

void ClientConnection::do_connect(
        const boost::asio::ip::basic_resolver<tcp, boost::asio::any_io_executor>::results_type &endpoint) {

}

void ClientConnection::do_read_header() {

}

void ClientConnection::do_read_body() {

}

void ClientConnection::do_write() {

}
