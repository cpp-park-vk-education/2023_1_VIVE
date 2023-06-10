#include "level_manager.hpp"

void LevelManager::loadLevel()
{
    curr_level_ = new Level(curr_level_num_);
}

void LevelManager::loadSubLevel()
{
    // Find file for current level and sublevel
    std::string file_name = DATA_FILE_MASK;

    // Replace in data file mask current level and sublevel num
    replaceSubstring(file_name, LEVEL_SYMBOL, std::to_string(curr_level_num_));
    replaceSubstring(file_name, SUBLEVEL_SYMBOL, std::to_string(curr_sublevel_num_));

    std::filesystem::path file_path = LVL_DATA_DIR / file_name;
    std::cout << "File name: " << file_path << std::endl;

    // Parse file
    curr_sublevel_ = parseLevelFile(file_path);
}

void LevelManager::load()
{
    AssetManager::getInstance()->loadAssets(std::string("level" + std::to_string(curr_level_num_) + "_" + std::to_string(curr_sublevel_num_)));
    SoundManager::getInstance()->loadSoundAndMusicForLevel(std::string("level" + std::to_string(curr_level_num_) + "_" + std::to_string(curr_sublevel_num_)));
    std::cout << "Loading Level #" << curr_level_num_ << std::endl;
    loadLevel();
    std::cout << "Loading SubLevel #" << curr_sublevel_num_ << std::endl;
    loadSubLevel();
    std::cout << "Loaded successfully" << std::endl;
}

void LevelManager::unload()
{
}

void LevelManager::nextLevel()
{
    // SUBLEVEL new_sublevel = static_cast<SUBLEVEL>(
    //     static_cast<int>(curr_sublevel_num_) + 1);

    // LEVEL new_level = static_cast<LEVEL>(
    //     static_cast<int>(curr_level_num_) + 1);

    // if (checkSubLevel(new_sublevel))
    // {
    //     changeSubLevel(new_sublevel);
    // }
    // else if (checkLevel(new_level))
    // {
    //     changeLevel(new_level);
    //     changeSubLevel(SUBLEVEL::SBL1);
    // }

    changeSubLevel(SUBLEVEL::SBL2);

    // auto players = curr_sublevel_->getPlayers();
    delete curr_sublevel_;
    delete curr_level_;
    load();
}

void LevelManager::update(const sf::Event &event)
{
    if (next_)
    {
        nextLevel();
        next_ = false;
    }
    curr_sublevel_->update(event);
}

SubLevel *LevelManager::parseLevelFile(const std::string &file_path)
{
    // Vectors of objects
    sf::Sprite background;
    std::vector<TileShPtr> tiles;
    std::vector<PlayerShPtr> players;
    std::vector<EnemyShPtr> enemies;
    std::vector<TriggerShPtr> triggers;

    std::ifstream level_file(file_path);
    char curr_block;
    TileShPtr tile{};
    PlayerShPtr player{};
    EnemyShPtr enemy{};
    BossShPtr boss{};
    TriggerShPtr trigger{};

    size_t x_coord = 0;
    size_t y_coord = 0;
    sf::Vector2u size;

    if (level_file.is_open())
    {
        std::cout << "File exists" << std::endl;
        while (level_file.get(curr_block))
        {
            switch (curr_block)
            {
            case BLOCK_TYPE::TILE:
                tile = std::make_shared<Tile>(
                    sf::Vector2f(BASE_SIZE, BASE_SIZE),
                    sf::Vector2f(x_coord, y_coord));
                tiles.push_back(tile);
                x_coord += BASE_SIZE;
                break;

            case BLOCK_TYPE::PLAYER:
                player = std::make_shared<Player>(
                    sf::Vector2f(BASE_SIZE, BASE_SIZE * 2),
                    sf::Vector2f(x_coord, y_coord));
                players.push_back(player);
                x_coord += BASE_SIZE;
                break;

            case BLOCK_TYPE::ENEMY:
                enemy = std::make_shared<Enemy>(
                    sf::Vector2f(BASE_SIZE * 2.5f, BASE_SIZE * 3),
                    sf::Vector2f(x_coord, y_coord));
                enemies.push_back(enemy);
                x_coord += BASE_SIZE;
                break;

            case BLOCK_TYPE::BOSS:
                boss = std::make_shared<Boss>(
                    sf::Vector2f(BASE_SIZE * 4, BASE_SIZE * 5),
                    sf::Vector2f(x_coord, y_coord));
                x_coord += BASE_SIZE;
                break;

            case BLOCK_TYPE::TRIGGER:
                trigger = std::make_shared<Trigger>(
                    sf::Vector2f(BASE_SIZE, BASE_SIZE),
                    sf::Vector2f(x_coord, y_coord));
                triggers.push_back(trigger);
                x_coord += BASE_SIZE;
                break;

            case BLOCK_TYPE::NONE:
                x_coord += BASE_SIZE;
                break;

            case '\n':
                size.x = size.x > x_coord ? size.x : x_coord;
                y_coord += BASE_SIZE;
                x_coord = 0;
                break;

            default:
                x_coord += BASE_SIZE;
                break;
            }
        }
        size.y = y_coord;
        return new SubLevel(size, players, tiles, enemies, triggers, boss);
    }
    else
    {
        std::cout << "File doesn't exist" << std::endl;
        return nullptr;
    }
}

LevelManager::LevelManager()
{
    curr_level_num_ = LEVEL::L1;
    // loadLevel();
    curr_sublevel_num_ = SUBLEVEL::SBL1;
    // loadSubLevel();
}

LevelManager::LevelManager(const LEVEL level, const SUBLEVEL sublevel)
    : curr_level_num_(level),
      curr_sublevel_num_(sublevel),
      next_(false)
{
    // loadLevel();
    // loadSubLevel();
}

LevelManager *LevelManager::getInstance()
{
    static LevelManager lm;
    return &lm;
}

bool LevelManager::checkLevel(const LEVEL level)
{
    return level_info.find(level) != level_info.end();
}

bool LevelManager::checkSubLevel(const SUBLEVEL sublevel)
{
    auto it = std::find(
        level_info[curr_level_num_].begin(),
        level_info[curr_level_num_].end(),
        sublevel);

    return it != level_info[curr_level_num_].end();
}

void LevelManager::changeLevel(const LEVEL level)
{
    curr_level_num_ = level;
    loadLevel();
}

void LevelManager::changeSubLevel(const SUBLEVEL sublevel)
{
    curr_sublevel_num_ = sublevel;
    loadSubLevel();
}

std::vector<ObjectShPtr> LevelManager::getObjects()
{
    return curr_sublevel_->getObjects();
}

LEVEL LevelManager::getCurrLevel()
{
    return curr_level_num_;
}

void replaceSubstring(std::string &str,
                      const std::string &oldSubStr,
                      const std::string &newSubStr)
{
    size_t pos = 0;
    while ((pos = str.find(oldSubStr, pos)) != std::string::npos)
    {
        str.replace(pos, oldSubStr.length(), newSubStr);
        pos += newSubStr.length();
    }
}