#include "host_coop_state.hpp"


void HostCoopState::update(const sf::Event &event) {
    SingleState::update(event);

}

void HostCoopState::readMessage(const proto::Response &msg) {

}
