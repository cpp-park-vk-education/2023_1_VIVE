#pragma once

#include <set>


class Room
{
public:
    void join(session_ptr participant);
    void leave(session_ptr participant);
    void deliver(const chat_message& msg);

private:
    std::set<session_ptr> participants_;
    chat_message_queue recent_msgs_;
};

