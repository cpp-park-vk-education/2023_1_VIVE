#pragma once

#include "Player.hpp"

class Game
{
private:
    sf::RenderWindow *window;

public:
    Game(sf::RenderWindow *window);
    virtual ~Game();

    // Accessors
    inline sf::RenderWindow &getWindow() { return *window; }

    // Setters

    // Functions
    void update();
    void render();
};
