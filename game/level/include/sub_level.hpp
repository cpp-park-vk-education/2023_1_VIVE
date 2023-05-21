#pragma once

#include "SFML/Graphics.hpp"

#include "object.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "enemy.hpp"

enum SUBLEVEL
{
    SBL_1 = 0,
};

class SubLevel
{
public:
    SubLevel(std::vector<PlayerShPtr> players,
             std::vector<TileShPtr> tiles,
             std::vector<EnemyShPtr> enemies);

    std::vector<Object> getObjects();

private:
    sf::Sprite background_;
    std::vector<TileShPtr> tiles_;
    std::vector<PlayerShPtr> players_;
    std::vector<EnemyShPtr> enemies_;
    // Boss boss_;
};
