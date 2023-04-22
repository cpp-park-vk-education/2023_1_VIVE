#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

class Player
{
private:
    sf::RectangleShape shape;

public:
    Player();
    virtual ~Player();

    // Functions
    void update();
    void render();
};
