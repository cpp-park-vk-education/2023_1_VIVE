#include <iostream>

#include "client.hpp"


Client::Client() {
    try
    {
        boost::asio::io_context io_context;

        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "5555");
        c_ = std::make_shared<ClientConnection>(io_context, endpoints);

        std::thread t([&io_context]()
                      {
                          io_context.run();
                      });

        c_->close();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void Client::write(const Message &msg) {

}

void Client::createNewRoom() {

}

void Client::joinRoom(unsigned int id) {

}

void Client::leaveRoom() {

}
