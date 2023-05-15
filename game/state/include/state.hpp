#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

#include "boost/heap/priority_queue.hpp"

#include "Player.hpp"
#include "iobject.hpp"
#include "message.pb.h"

class State;

using StateShPtr = std::shared_ptr<State>;

class State {
public:
    virtual void readMessage(const proto::Message& msg) = 0;
    virtual void update(const sf::Event& event) = 0;
    void updateHeap();
    std::vector<DrawableShPtr> getHeap();
    void setHeap(std::vector<DrawableShPtr> objects);

protected:
    std::vector<Player> players_;
    std::vector<DrawableShPtr> objects_;
};
