#pragma once

#include "object.hpp"
#include "sub_level.hpp"

enum LEVEL
{
    L1 = 1,
};

class Level
{
public:
    Level(LEVEL level_num);

    // std::vector<ObjectShPtr> getObjects();

private:
    // std::vector<SubLevel> sub_levels_;
    LEVEL level_num_;
};
