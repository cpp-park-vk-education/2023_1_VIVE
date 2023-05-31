#include "state_manager.hpp"

#include <iostream>

void StateManager::changeState(StateManager::EnState newState) {
    to_state_object_[curState_]->unload();
    curState_ = newState;
    to_state_object_[curState_]->load();
}

void StateManager::updateHeap()
{
    to_state_object_[curState_]->updateHeap();
}

void StateManager::init()
{
    to_state_object_[curState_]->load();
}

ObjectsHeap StateManager::getHeap() {
    return to_state_object_[curState_]->getHeap();
}

void StateManager::clearHeap() {
    to_state_object_[curState_]->clearHeap();
}

void StateManager::update(const sf::Event &event) {
    clearHeap();
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


