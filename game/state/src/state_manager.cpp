#include "state_manager.hpp"

#include <iostream>

void StateManager::changeState(StateManager::EnState newState) {
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

ObjectsHeap &StateManager::getHeap() {
    return to_state_object_[curState_]->getHeap();
}

void StateManager::update(const sf::Event &event) {
    to_state_object_[curState_]->update(event);
}

void StateManager::readMessage(const proto::Response &msg) {
    to_state_object_[curState_]->readMessage(msg);
}


