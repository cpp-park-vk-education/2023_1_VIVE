#pragma once

#include "single_state.hpp"

class HostCoopState : public SingleState {
    void readMessage(const proto::Response &msg);
    void update(const sf::Event &event);
};
