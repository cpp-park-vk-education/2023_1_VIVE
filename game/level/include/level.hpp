#pragma once

#include "object.hpp"
#include "sub_level.hpp"

enum LEVEL
{
    L1 = 0,
};

class Level {
public:
    std::vector<ObjectShPtr> getObjects();
private:
    std::vector<SubLevel> sub_levels_;
    unsigned int cur_level_;
};
