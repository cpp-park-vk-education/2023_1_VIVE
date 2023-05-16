#pragma once

#include "SFML/Graphics.hpp"

#include "iobject.hpp"
#include "Player.hpp"

class Tile {

};
class Enemy {

};
class Boss {

};

class SubLevel {
public:
    std::vector<IObject> getObjects();

private:
    sf::Sprite background_;
    std::vector<Tile> tiles_;
    std::vector<Player> players_;
    std::vector<Enemy> enemies_;
    Boss boss_;
};
