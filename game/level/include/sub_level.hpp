#pragma once

#include "SFML/Graphics.hpp"
#include "background.hpp"
#include "object.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "enemy.hpp"
#include "boss.hpp"
#include "player_user_interface.hpp"
#include "collision_handler.hpp"
#include "camera_target.hpp"

enum SUBLEVEL
{
    SBL1 = 1,
    SBL2,
};

class SubLevel
{
public:
    SubLevel(const sf::Vector2u size,
             std::vector<PlayerShPtr> players,
             std::vector<TileShPtr> tiles,
             std::vector<EnemyShPtr> enemies,
             std::vector<TriggerShPtr> triggers,
             BossShPtr boss);


    void update(const sf::Event &event);

    // Setters
    void setMapSize(const sf::Vector2u size);

    // Getters
    std::vector<ObjectShPtr> getObjects();
    sf::Vector2u getMapSize() const;
    std::vector<PlayerShPtr> &getPlayers();

private:
    BackGroundShPtr background_;
    std::vector<TileShPtr> tiles_;
    std::vector<PlayerShPtr> players_;
    std::vector<EnemyShPtr> enemies_;
    std::vector<TriggerShPtr> triggers_;
    BossShPtr boss_;
    PUIShPtr player_user_interface_;
    CollisionHandlerShPtr collision_handler_;

    std::vector<ParticleShPtr> drop_;

    int players_count_;
    int enemies_count_;

    CameraTargetShPtr camera_;
    sf::Vector2u map_size_;

    // Time
    sf::Clock clock_;

    bool checkObjectInCamera(const PhysicalObjectShPtr object);
    // bool checkEnemyInCamera(const EnemyShPtr enemy);

    // Updates
    void updateBackGround();
    void updatePlayer(const sf::Event &event, const float delta_time);
    void updateCamera();
    void updatePUI();
    void updateTiles(const sf::Event &event);
    void updateCollision();
    void updateEnemies(const sf::Event &event, const float delta_time);
    void updateTriggers(const sf::Event &event);
    void updateBoss(const sf::Event &event, const float delta_time);
    void updateDrop(const sf::Event &event, const float delta_time);
    void updateNonExistentObjects();
    void updateOutOfBounds();

    // Initions
    void init();
    void initCamera();
    void initPUI();
    void initCollisionHandler();

    // Spawners
    void spawnEnemies();
    void spawnPlayer(PlayerShPtr player);
};
