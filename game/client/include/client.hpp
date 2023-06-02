#pragma once

#include <queue>

#include "client_connection.hpp"
#include "message.pb.h"

#include "boost/asio.hpp"

namespace net = boost::asio;
using net::ip::tcp;

class Client
{
public:
    Client() = default;
    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;
    ~Client();

    void connect();
//    void disconnect();
    void readMessage(const std::string& msg_str);
    void writeMessage(const proto::Request &msg);

private:
    void write(const std::string &msg);

    ClientConnectionShPtr c_ = nullptr;

    std::string ip_ = "25.18.161.202";
    std::string port_ = "1234";

//    std::string ip_ = "127.0.0.1";
//    std::string port_ = "5555";
};

