#include <iostream>

#include <thread>

#include "client.hpp"
#include "game.hpp"


void Client::connect() {
    c_ = std::make_shared<ClientConnection>(ip_, port_);
    try {
        std::thread t([this]() {
            c_->startIOContext();
        });
        t.detach();
    } catch (const std::exception &e) {
        std::cout << "\t error in client: " << e.what() << std::endl;
    }
}

void Client::write(const std::string &msg) {
    if (!c_ || !c_->isConnected()) {
        connect();
    }
    c_->write(msg);
}

void Client::readMessage(const std::string &msg_str) {
    proto::Response msg;
    if (!msg.ParseFromString(msg_str)) {
        std::cout << "\tError in deserializing message!" << std::endl;
        return;
    }
    GameEngine::readMessage(msg);
}

void Client::writeMessage(const proto::Request &msg) {
    std::string msg_str;
    if (!msg.SerializeToString(&msg_str)) {
        std::cout << "\tError in serializing message!" << std::endl;
        return;
    }
    write(msg_str);
}

Client::~Client() {
    c_->close();
}


