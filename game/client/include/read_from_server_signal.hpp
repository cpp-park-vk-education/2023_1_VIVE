#pragma once

#include "boost/signals2.hpp"

#include "message.hpp"

class ReadFromServerSignal {
public:
    void connect(boost::function<void(const Message&)> func);

private:

    boost::signals2::signal <void(const Message&)> signal_;
};
