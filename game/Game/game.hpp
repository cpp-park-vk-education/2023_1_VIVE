#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "player_user_interface.hpp"
#include "collision_handler.hpp"
#include "particle_set.hpp"
#include "camera_target.hpp"
#include "asset_manager.hpp"
#include "particle.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "tile.hpp"

#include <memory>
#include <vector>

class GameEngine
{
private:
    sf::RenderWindow window_;
    sf::Event event_;

    // Objects
    sf::Sprite bg_;
    Player *player_;
    PUI* player_user_interface_;
    CameraTarget* camera_;
    std::vector<Tile *> tiles_;
    ParticleSet *coin_particles_;
    std::vector<Enemy *> enemies_;

    CollisionHandler *collision_handler_;

    // Inits
    void initBG();
    void initAssets();
    void initWindow();
    void initCamera();
    void initPUI();
    void initPlayer();
    void initTiles();
    void initParticles();
    void initEnemies();

    // Updates
    void updatePlayer(const float delta_time);
    void updateCamera();
    void updatePUI();
    void updateTiles();
    void updateParticles(const float delta_time);
    void updateCollision();
    void updateEnemies(const float delta_time);
    void update();
    void updateNonExistentObjects();

    // Draws
    void drawBG();
    void drawPlayer();
    void drawTiles();
    void drawParticles();
    void drawEnemies();
    void draw();

    // Timer
    sf::Clock clock_;

public:
    GameEngine();
    virtual ~GameEngine();

    void run();
};
