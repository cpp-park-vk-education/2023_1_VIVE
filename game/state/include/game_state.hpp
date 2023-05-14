#pragma once

#include "state.hpp"

class PlayerUI {

};

class GameState : public State {
public:
    void updatePUI();

private:
    PlayerUI pui_;
};
