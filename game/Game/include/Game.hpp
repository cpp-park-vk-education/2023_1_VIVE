#pragma once

#include "Player.hpp"

class Game
{
private:
    sf::RenderWindow window;
    sf::Event event;

    // Entities
    Player *player;

    // Initions
    void initWindow();
    void initPlayer();

public:
    Game();
    virtual ~Game();

    // Accessors
    inline sf::RenderWindow &getWindow() { return window; }

    // Setters

    // Functions
    void updatePlayer();
    void renderPlayer();

    void update();
    void render();
};
