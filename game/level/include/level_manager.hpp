#pragma once

#include <vector>

#include "object.hpp"
#include "level.hpp"
#include "sub_level.hpp"

#include <string>
#include <fstream>

const std::string LVL_DATA_DIR = "../data/";
const std::string LEVEL_SYMBOL = "$L";
const std::string SUBLEVEL_SYMBOL = "$SBL";
const std::string DATA_FILE_MASK = "lvl-" + LEVEL_SYMBOL + "-" + SUBLEVEL_SYMBOL;

enum BLOCK_TYPE : char
{
    NONE = '-',
    TILE = '#',
    PLAYER = '1',
    ENEMY = '2',
};

class LevelManager
{
private:
    std::vector<Level> levels_;
    LEVEL curr_level_;
    SUBLEVEL curr_sublevel_;

    SubLevel *parseLevelFile(const std::string &file_path);

public:
    LevelManager();

    void changeLevel(const LEVEL level);
    void changeSubLevel(const SUBLEVEL sublevel);

    SubLevel *loadSubLevel();

    void update(const sf::Event &event);

    // Getters
    std::vector<Object> getObjects();
    LEVEL getCurrLevel();
};

void replaceSubstring(std::string &str,
                      const std::string &oldSubStr,
                      const std::string &newSubStr);
