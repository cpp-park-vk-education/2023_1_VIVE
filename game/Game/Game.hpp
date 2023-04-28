#pragma once
#include "Player.hpp"
#include "Menu.hpp"

class Game
{
private:
    sf::RenderWindow window;
    sf::Event event;
    Menu menu;

    // Entities
    Player *player;

    // Initions
    void initWindow();
    void initPlayer();

    // Timer
    sf::Clock clock;
    float delta_time;

public:
    Game();
    virtual ~Game();

    // Accessors
    inline sf::RenderWindow &getWindow() { return window; }

    // Functions
    void updatePlayer(const float delta_time);
    void renderPlayer();
    // void updateCollision();

    void update();
    void render();
};
