#pragma once

#include "object.hpp"
#include "sub_level.hpp"

class Level {
public:
    std::vector<Object> getObjects();
private:
    std::vector<SubLevel> sub_levels_;
    unsigned int cur_level_;
};
