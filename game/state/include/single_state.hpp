#pragma once

#include "game_state.hpp"
#include "level_manager.hpp"
// #include "tile.hpp"
// #include "player_user_interface.hpp"
// #include "camera_target.hpp"
// #include "enemy.hpp"
// #include "collision_handler.hpp"
// #include "asset_manager.hpp"
// #include "background.hpp"

class SingleState : public GameState
{
public:
    SingleState();
    ~SingleState();

    void readMessage(const proto::Response &msg) override;
    void update(const sf::Event &event) override;
    void load() override;
    void unload() override {}

    // Heap methods
    void updateHeap() override;
    ObjectsHeap getHeap() override;

private:
    LevelManager *level_manager;
    // Objects
    // TODO remake background
    // TODO remove raw pointers
    // sf::Sprite bg_;
    // BackGroundShPtr bg_;
    // PlayerShPtr player_;
    // PUIShPtr player_user_interface_;
    // CameraTarget *camera_;
    // std::vector<TileShPtr> tiles_;
    // std::vector<EnemyShPtr> enemies_;
    // CollisionHandlerShPtr collision_handler_;

    // sf::Clock clock_;

    // Initions
    // void initBG();
    // TODO move Assets and Camera to game engine
    // void initAssets();
    // void initCamera();
    // void initPUI();
    // void initPlayer();
    // void initTiles();
    // void initEnemies();
    // void initCollisionHandler();

    // Updates
    // void updatePlayer(const sf::Event& event, const float delta_time);
    // void updateCamera();
    // void updatePUI();
    // void updateTiles(const sf::Event& event);
    // void updateCollision();
    // void updateEnemies(const sf::Event& event, const float delta_time);
    // void updateNonExistentObjects();

    // Draws
    // void drawBG();
    // void drawPlayer();
    // void drawTiles();
    // void drawEnemies();

    // Spawners
    // void spawnEnemies();
};
