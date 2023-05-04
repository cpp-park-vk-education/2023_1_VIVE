#pragma once

#include <queue>

#include "client_connection.hpp"
#include "message.hpp"
#include "read_from_server_signal.hpp"

#include "boost/asio.hpp"

namespace net = boost::asio;
using net::ip::tcp;

class Client
{
public:
    Client();

    void write(const Message& msg);
    void createNewRoom();
    void joinRoom(unsigned int id);
    void leaveRoom();


private:
    ClientConnectionShPtr c_;

};

