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

    // Timer
    sf::Clock clock;
    float deltaTime;

public:
    Game();
    virtual ~Game();

    // Accessors
    inline sf::RenderWindow &getWindow() { return window; }

    // Functions
    void updatePlayer();
    void renderPlayer();
    void updateCollision();

    void update();
    void render();
};
