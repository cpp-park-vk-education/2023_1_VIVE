#pragma once

#include <queue>

#include "message.pb.h"
#include <thread>

#include "boost/asio.hpp"

namespace net = boost::asio;
using net::ip::tcp;

class ClientConnection;

using ClientConnectionShPtr = std::shared_ptr<ClientConnection>;

class ClientConnection : public std::enable_shared_from_this<ClientConnection>
{
public:
    ClientConnection(const std::string& ip, const std::string& port);

    void startIOContext();
    bool isConnected() const;

    void write(const std::string& msg);

    void close();

private:
    void doConnect();

    void doReadHeader();
    void doReadBody();

    void doWrite();

private:
    boost::asio::io_context io_context_;
    tcp::socket socket_;

    tcp::resolver resolver_;
    tcp::resolver::results_type endpoint_;

    std::string read_msg_;
    std::string read_msg_size_;
    std::queue<std::string> write_msgs_;
};


