#pragma once

#include <boost/asio.hpp>
#include "room.hpp"

using boost::asio::ip::tcp;


class session: public std::enable_shared_from_this<session>
{
public:
    session(tcp::socket socket, Room& room);

    void start();
    void deliver(const chat_message& msg);

private:
    void do_read_header();
    void do_read_body();
    void do_write();

    tcp::socket socket_;
    Room& room_;
};
