#pragma once

#include "SFML/Graphics.hpp"
#include "background.hpp"
#include "object.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "enemy.hpp"
#include "player_user_interface.hpp"
#include "collision_handler.hpp"
#include "camera_target.hpp"

enum SUBLEVEL
{
    SBL1 = 1,
};

class SubLevel
{
public:
    SubLevel(const sf::Vector2u size,
             std::vector<PlayerShPtr> players,
             std::vector<TileShPtr> tiles,
             std::vector<EnemyShPtr> enemies);

    std::vector<ObjectShPtr> getObjects();

    void update(const sf::Event &event);

    // Setters
    void setMapSize(const sf::Vector2u size);

    // Getters
    sf::Vector2u getMapSize() const;

private:

    BackGroundShPtr background_;
    // sf::Sprite background_;
    std::vector<TileShPtr> tiles_;
    std::vector<PlayerShPtr> players_;
    std::vector<EnemyShPtr> enemies_;
    PUIShPtr player_user_interface_;
    CollisionHandlerShPtr collision_handler_;
    // Boss boss_;

    CameraTarget *camera_;
    sf::Vector2u map_size_;

    // Time
    sf::Clock clock_;

    // Updates
    void updateBackGround();
    void updatePlayer(const sf::Event& event, const float delta_time);
    void updateCamera();
    void updatePUI();
    void updateTiles(const sf::Event& event);
    void updateCollision();
    void updateEnemies(const sf::Event& event, const float delta_time);
    void updateNonExistentObjects();


    // Initions
    void init();
    void initCamera();
    void initPUI();
    void initCollisionHandler();

    // Spawners
    void spawnEnemies();

};
