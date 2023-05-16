#pragma once

#include "SFML/Graphics.hpp"

#include "object.hpp"
#include "player.hpp"

class Tile {

};
class Enemy {

};
class Boss {

};

class SubLevel {
public:
    std::vector<Object> getObjects();

private:
    sf::Sprite background_;
    std::vector<Tile> tiles_;
    std::vector<Player> players_;
    std::vector<Enemy> enemies_;
    Boss boss_;
};
