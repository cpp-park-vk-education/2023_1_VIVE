#pragma once

#include <vector>

#include "object.hpp"
#include "background.hpp"
#include "level.hpp"
#include "sub_level.hpp"
#include "trigger.hpp"

#include <string>
#include <fstream>
#include <filesystem>
#include <map>

const std::filesystem::path LVL_DATA_DIR = std::filesystem::current_path().parent_path() / "game" / "level" / "data";

// const std::string LVL_DATA_DIR = "../data/";
const std::string LEVEL_SYMBOL = "$L";
const std::string SUBLEVEL_SYMBOL = "$SBL";
const std::string DATA_FILE_MASK = "lvl-" + LEVEL_SYMBOL + "-" + SUBLEVEL_SYMBOL;

enum BLOCK_TYPE : char
{
    NONE = '-',
    TILE = '#',
    PLAYER = 'P',
    ENEMY = 'E',
    BOSS = 'B',
    TRIGGER = 'T',
};

class LevelManager
{
private:
    LEVEL curr_level_num_;
    SUBLEVEL curr_sublevel_num_;

    bool next_;

    Level *curr_level_;
    SubLevel *curr_sublevel_;

    SubLevel *parseLevelFile(const std::string &file_path);

    // Data about existing levels and sublevels
    std::map<LEVEL, std::vector<SUBLEVEL>> level_info = {
        {LEVEL::L1, {
                        SUBLEVEL::SBL1,
                        SUBLEVEL::SBL2,
                    }},
    };

    LevelManager();
    LevelManager(const LEVEL level, const SUBLEVEL sublevel);

public:
    LevelManager(const LevelManager &) = delete;
    LevelManager(LevelManager &&) = delete;
    LevelManager &operator=(const LevelManager &) = delete;
    LevelManager &operator=(LevelManager &&) = delete;
    static LevelManager *getInstance();

    bool checkLevel(const LEVEL level);
    bool checkSubLevel(const SUBLEVEL sublevel);

    void changeLevel(const LEVEL level);
    void changeSubLevel(const SUBLEVEL sublevel);

    void loadLevel();
    void loadSubLevel();
    void load();
    void unload();

    void changeNext() { next_ = true; }
    void nextLevel();

    void update(const sf::Event &event);

    // Getters
    std::vector<ObjectShPtr> getObjects();
    LEVEL getCurrLevel();
};

void replaceSubstring(std::string &str,
                      const std::string &oldSubStr,
                      const std::string &newSubStr);
