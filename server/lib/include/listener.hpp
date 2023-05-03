#pragma once

#include <string>
#include <unordered_map>

#include "boost/asio.hpp"

#include "room.hpp"

namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class Listener {
public:
    Listener(net::io_context& context, tcp::endpoint& endpoint);

    void async_accept();

private:
    void do_accept();

private:
    tcp::acceptor acceptor_;
    std::unordered_map<std::string, std::shared_ptr<Room>> mp;
};
