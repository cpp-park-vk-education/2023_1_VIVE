#include "state.hpp"

std::vector<DrawableShPtr> State::getHeap() {
    return objects_;
}

void State::readMessage(const proto::Response &msg) {

}
