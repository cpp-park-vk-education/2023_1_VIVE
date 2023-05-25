#include "state_manager.hpp"

#include <iostream>

void StateManager::changeState(StateManager::EnState newState) {
    curState_ = newState;
}

std::vector<DrawableShPtr> StateManager::getHeap() {
    return to_state_object_[curState_]->getHeap();
}

void StateManager::update(const sf::Event &event) {
    to_state_object_[curState_]->update(event);
}

void StateManager::readMessage(const proto::Response &msg) {
    if (msg.has_join_state()) {
        to_state_object_[JOIN_STATE]->readMessage(msg);
    }
    if (msg.has_init_multiplayer_state()) {
        to_state_object_[INIT_MULTIPLAYER_STATE]->readMessage(msg);
    }
    to_state_object_[curState_]->readMessage(msg);
}


