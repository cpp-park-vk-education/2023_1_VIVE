#pragma once

#include "boost/signals2.hpp"

#include "message.hpp"

class ReadFromServerSignal {
public:
    explicit ReadFromServerSignal(const boost::signals2::signal<void(const Message&)>& signal);

private:
    boost::signals2::signal <void(const Message&)> signal_;
};
