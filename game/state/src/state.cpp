#include "state.hpp"

void State::readMessage(const proto::Response &msg) {

}

ObjectsHeap State::getHeap() {
    return heap_;
}

void State::clearHeap()
{
    while (!heap_.empty())
    {
        heap_.pop();
    }
}

