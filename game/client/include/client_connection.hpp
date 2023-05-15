#pragma once

#include <queue>

#include "message.pb.h"

#include "boost/asio.hpp"

namespace net = boost::asio;
using net::ip::tcp;

class ClientConnection;

using ClientConnectionShPtr = std::shared_ptr<ClientConnection>;

class ClientConnection
{
public:
    ClientConnection(net::io_context& io_context,
           const tcp::resolver::results_type& endpoints);

    void write(const proto::Message& msg);
    void async_connect(char* ip, unsigned short port);
    bool connected();
    void close();
private:
    void do_connect(const tcp::resolver::results_type& endpoint);
    void do_read_header();
    void do_read_body();
    void do_write();
private:
    boost::asio::io_context& io_context_;
    tcp::socket socket_;
    proto::Message read_msg_;
    std::queue<proto::Message> write_msgs_;
};


