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
    ClientConnection(net::io_context& io_context,
           const tcp::resolver::results_type& endpoints);

    void write(const std::string& msg);
    void close();
private:
    void do_connect(const tcp::resolver::results_type& endpoint);
    void do_write();
    void do_read_header();
    void do_read_body();
private:
    boost::asio::io_context& io_context_;
    tcp::socket socket_;

    std::string read_msg_;
    std::string read_msg_size_;
    std::queue<std::string> write_msgs_;
};


