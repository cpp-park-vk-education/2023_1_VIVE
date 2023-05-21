#include "level_manager.hpp"

SubLevel *LevelManager::loadSubLevel()
{
    // Find file for current level and sublevel
    std::string file_name = DATA_FILE_MASK;

    // Replace in data file mask current level and sublevel num
    replaceSubstring(file_name, LEVEL_SYMBOL, std::to_string(curr_level_ + 1));
    replaceSubstring(file_name, SUBLEVEL_SYMBOL, std::to_string(curr_sublevel_ + 1));

    std::string file_path = LVL_DATA_DIR + file_name;

    // Parse file
    return parseLevelFile(file_path);
}

void LevelManager::update(const sf::Event &event)
{

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

    size_t x_coord = 0;
    size_t y_coord = 0;

    if (level_file.is_open())
    {
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
                    sf::Vector2f(BASE_SIZE, BASE_SIZE * 2),
                    sf::Vector2f(x_coord, y_coord));
                enemies.push_back(enemy);
                x_coord += BASE_SIZE;
                break;

            case BLOCK_TYPE::NONE:
                x_coord += BASE_SIZE;
                break;
            
            case '\n':
                y_coord += BASE_SIZE;
                x_coord = 0;
                break;

            default:
                break;
            }
        }

        return new SubLevel(players, tiles, enemies);
    }
    else
    {
        return nullptr;
    }
}

LevelManager::LevelManager()
{
    curr_level_ = LEVEL::L1;
    curr_sublevel_ = SUBLEVEL::SBL_1;
}

void LevelManager::changeLevel(const LEVEL level)
{
    curr_level_ = level;
}

void LevelManager::changeSubLevel(const SUBLEVEL sublevel)
{
    curr_sublevel_ = sublevel;
}

LEVEL LevelManager::getCurrLevel()
{
    return curr_level_;
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