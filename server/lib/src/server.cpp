#include <iostream>

#include "server.hpp"
#include "listener.hpp"

Server::Server(unsigned short port)
        : io_context_(), endpoint_(tcp::v4(), port) {}

void Server::run() {
    try {
        Listener server(io_context_, endpoint_);
        server.async_accept();
        io_context_.run();
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}
