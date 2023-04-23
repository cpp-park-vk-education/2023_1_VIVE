#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

class Game
{
private:
    sf::RenderWindow window;
    sf::Event event;

    // Entities

    // Initions
    void initWindow();

public:
    Game();
    virtual ~Game();

    // Accessors
    inline sf::RenderWindow &getWindow() { return window; }

    // Setters

    // Functions
    void update();
    void render();
};
