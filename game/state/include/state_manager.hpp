#pragma once

#include <vector>
#include <unordered_map>

#include "SFML/Graphics.hpp"

#include "object.hpp"
#include "message.pb.h"
#include "state.hpp"
#include "main_menu_state.hpp"
#include "single_state.hpp"
#include "init_multiplayer_state.hpp"
#include "join_state.hpp"
#include "host_coop_state.hpp"

class StateManager {
public:
    enum EnState {
        MAIN_MENU_STATE,
        INIT_MULTIPLAYER_STATE,
        JOIN_STATE,
        SINGLE_STATE,
        COOP_STATE,
        GAME_MENU_STATE,
        HOST_COOP_STATE,
        GUEST_COOP_STATE,
    };

public:
    void readMessage(const proto::Response &msg);

    void update(const sf::Event &event);

    void changeState(EnState newState);

    ObjectsHeap getHeap();
    void updateHeap();
    void clearHeap();

    EnState getState() const {
        return curState_;
    }

    void init();

private:
    EnState curState_ = MAIN_MENU_STATE;
    std::unordered_map<EnState, StateShPtr> to_state_object_ {
            {MAIN_MENU_STATE, std::make_shared<MainMenuState>()},
            {INIT_MULTIPLAYER_STATE, std::make_shared<InitMultiplayerState>()},
            {JOIN_STATE, std::make_shared<JoinState>()},
            {SINGLE_STATE, std::make_shared<SingleState>()},
            {HOST_COOP_STATE, std::make_shared<HostCoopState>()},
        //    {COOP_STATE, std::make_shared<CoopState>()},
    };
};
