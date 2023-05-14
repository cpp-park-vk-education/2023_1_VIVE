#include "state.hpp"

std::vector<DrawableShPtr> State::getHeap() {
    return objects_;
}
