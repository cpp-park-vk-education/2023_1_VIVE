#pragma once

#include <vector>

#include "boost/heap/priority_queue.hpp"
#include "Player.hpp"
#include "iobject.hpp"

class State {
public:
    void updateHeap();
    std::vector<IObjectShPtr> getHeap();
    void setHeap(std::vector<IObjectShPtr> objects);

private:
    std::vector<Player> players_;
    std::vector<IObjectShPtr> objects_;
};
