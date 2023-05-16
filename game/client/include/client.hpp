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
    void connect();
    void write(const proto::Request& msg);


private:
    boost::asio::io_context io_context_;
    ClientConnectionShPtr c_ = nullptr;

    bool connected_ = false;

    std::string ip_ = "127.0.0.1";
    std::string port_ = "5555";

};

