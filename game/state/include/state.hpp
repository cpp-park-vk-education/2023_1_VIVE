#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

#include "boost/heap/priority_queue.hpp"

#include "player.hpp"
#include "object.hpp"
#include "message.pb.h"
#include "queue"

class State;

using StateShPtr = std::shared_ptr<State>;
using ObjectsHeap = std::priority_queue<ObjectShPtr,
                                        std::vector<ObjectShPtr>,
                                        CompareObjectsShPtr>;

class State
{
public:
    virtual void readMessage(const proto::Response &msg) = 0;
    virtual void update(const sf::Event &event) = 0;
    virtual void load() = 0;
    virtual void unload() = 0;

    // Heap methods
    virtual void updateHeap() = 0;
    virtual ObjectsHeap &getHeap() = 0;
    virtual void setHeap(std::vector<ObjectShPtr> objects) = 0;

protected:
    std::vector<Player> players_;
    std::vector<DrawableShPtr> objects_;

    ObjectsHeap heap_;
    void clearHeap();
};
