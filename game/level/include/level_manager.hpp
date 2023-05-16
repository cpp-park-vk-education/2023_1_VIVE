#pragma once

#include <vector>

#include "iobject.hpp"
#include "level.hpp"

class LevelManager {
private:
    std::vector<Level> levels_;
    unsigned int cur_level_;

public:
    void changeLevel();
    std::vector<IObject> getObjects();
};
