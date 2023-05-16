#include <iostream>

#include <thread>

#include "client.hpp"


void Client::connect() {

    if (connected_) {
        return;
    }
    try
    {

        tcp::resolver resolver_(io_context_);
        tcp::resolver::results_type endpoints_ = resolver_.resolve(ip_, port_);
        c_ = std::make_shared<ClientConnection>(io_context_, endpoints_);
        connected_ = true;
        std::thread t([this]()
                      {
                          io_context_.run();
                      });

        c_->close();
        t.join();
    }
    catch (std::exception& e)
    {
        connected_ = false;
        std::cerr << "Exception client: " << e.what() << "\n";
    }
}

void Client::write(const proto::Request &msg) {
    if (!connected_) {
        connect();
    }
    c_->write(msg.SerializeAsString());
}


