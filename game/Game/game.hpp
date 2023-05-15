#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "player.hpp"
#include "tile.hpp"
#include "collision_handler.hpp"
#include "particle.hpp"
#include "particle_set.hpp"

#include <memory>
#include <vector>

class GameEngine
{
private:
    sf::RenderWindow window_;
    sf::Event event_;

    // Objects
    Player *player_;
    std::vector<Tile *> tiles_;

    ParticleSet *coin_particles_;

    CollisionHandler *collision_handler_;

    // Inits
    void initWindow();
    void initPlayer();
    void initTiles();
    void initParticles();

    // Updates
    void updatePlayer(const float delta_time);
    void updateTiles();
    void updateParticles(const float delta_time);
    void updateCollision();
    void update();

    // Draws
    void drawPlayer();
    void drawTiles();
    void drawParticles();
    void draw();

    // Timer
    sf::Clock clock_;

public:
    GameEngine();
    virtual ~GameEngine();

    void run();
};
