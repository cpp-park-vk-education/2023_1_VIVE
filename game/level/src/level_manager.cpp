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

void LevelManager::update(const sf::Event &event)
{
    curr_sublevel_->update(event);
}

SubLevel *LevelManager::parseLevelFile(const std::string &file_path)
{
    // Vectors of objects
    sf::Sprite background;
    std::vector<TileShPtr> tiles;
    std::vector<PlayerShPtr> players;
    std::vector<EnemyShPtr> enemies;

    std::ifstream level_file(file_path);
    char curr_block;
    TileShPtr tile{};
    PlayerShPtr player{};
    EnemyShPtr enemy{};
    BossShPtr boss{};

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
        return new SubLevel(size, players, tiles, enemies, boss);
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
      curr_sublevel_num_(sublevel)
{
    // loadLevel();
    // loadSubLevel();
}

void LevelManager::changeLevel(const LEVEL level)
{
    // Check if given level is in the game
    if (level_info.find(level) != level_info.end())
    {
        curr_level_num_ = level;
        loadLevel();
    }
}

void LevelManager::changeSubLevel(const SUBLEVEL sublevel)
{
    // Check if given level is in the game
    auto it = std::find(
        level_info[curr_level_num_].begin(),
        level_info[curr_level_num_].end(),
        sublevel);

    if (it != level_info[curr_level_num_].end())
    {
        curr_sublevel_num_ = sublevel;
        loadSubLevel();
    }
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