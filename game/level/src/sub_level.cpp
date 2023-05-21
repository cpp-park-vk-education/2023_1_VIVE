#include "sub_level.hpp"

SubLevel::SubLevel(std::vector<PlayerShPtr> players, std::vector<TileShPtr> tiles, std::vector<EnemyShPtr> enemies)
    : players_(players),
      tiles_(tiles),
      enemies_(enemies)
{
}
