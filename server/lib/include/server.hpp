#pragma once

#include "boost/asio.hpp"

#include "room.hpp"

#include <vector>

namespace net = boost::asio;
using boost::asio::ip::tcp;

class Server
{
public:
    Server(unsigned short port);

    void run();

private:
    net::io_context io_context_;
    tcp::endpoint endpoint_;
};