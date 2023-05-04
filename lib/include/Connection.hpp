#pragma once

#include <boost/asio.hpp>
#include "RoomSignals.hpp"

class Connection;
using ConnectionShPtr = std::shared_ptr<Connection>;

using boost::asio::ip::tcp;

class Connection: public std::enable_shared_from_this<Connection>
{
private:
    tcp::socket socket_;
    int user_id_;

    Message read_mess;
    std::queue<Message> mess_queue_to_write;

    RoomSignalsShPtr room_actions;
    SignalManagerShPtr room_manager_;

public:
    Connection(int user_id, tcp::socket socket, SignalManagerShPtr room_manager);

    void doReadHeader();
    void doReadBody();
    void doWrite();
    void close();
    void deliver(const Message& mess);
    int getUserId() const;
};