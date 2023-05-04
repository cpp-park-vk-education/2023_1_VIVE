#pragma once

#include "iobject.hpp"
#include "sub_level.hpp"

class Level {
public:
    std::vector<IObject> getObjects();
private:
    std::vector<SubLevel> sub_levels_;
    unsigned int cur_level_;
};
