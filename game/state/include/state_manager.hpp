#pragma once

#include "message.hpp"

class StateManager {
    enum EnState {

    };
public:
    void changeState(EnState newState);
    void getHeap();
    void readMessage(const Message& msg);

private:
    EnState curState_;
};
