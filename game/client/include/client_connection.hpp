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
    static constexpr int header_size = 4;
    static constexpr int max_body_size = 1024;

public:
    ClientConnection(const std::string& ip, const std::string& port);

    void startIOContext();
    bool isConnected() const;

    void write(const std::string& msg);

    void close();

private:
    int decodeHeader(const std::string& header_string);
    void doConnect();

    void doReadHeader();
    void doReadBody(int body_size);

    void doWrite();

private:
    boost::asio::io_context io_context_;
    tcp::socket socket_;

    tcp::resolver resolver_;
    tcp::resolver::results_type endpoint_;

    boost::asio::streambuf read_buffer_;
    std::queue<std::string> write_msgs_;
};


