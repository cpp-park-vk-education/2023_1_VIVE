#include <iostream>

#include "listener.hpp"

Listener::Listener(net::io_context& context, tcp::endpoint& endpoint)
        : acceptor_(context, endpoint) {}

void Listener::async_accept() {
    do_accept();
}

void Listener::do_accept() {
    acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
//                    std::make_shared<chat_session>(std::move(socket), room_)->start();
                } else {
                    std::cout << "\t--- accept: failed " << ec.message() << " " << std::this_thread::get_id()
                              << std::endl;
                }
                do_accept();
            });

}
