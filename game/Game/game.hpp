#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "player.hpp"
#include "tile.hpp"

#include <memory>
#include <vector>

class GameEngine
{
private:
    sf::RenderWindow window_;
    sf::Event event_;

    // Objects
    std::unique_ptr<Player> player_;
    std::vector<std::unique_ptr<Tile>> tiles_;

    // Inits
    void initWindow();
    void initPlayer();
    void initTiles();

    // Updates
    void updatePlayer(const float delta_time);
    void updateTiles();
    void update();

    // Draws
    void drawPlayer();
    void drawTiles();
    void draw();

    // Timer
    sf::Clock clock_;

public:
    GameEngine();
    virtual ~GameEngine();

    void run();
};
