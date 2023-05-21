#pragma once

#include "physical_object.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "particle_set.hpp"
#include "enemy.hpp"

#include <vector>
#include <iostream>
#include <memory>

class CollisionHandler
{
private:
    bool checkAABBCollision(const PhysicalObjectShPtr obj1,
                            const PhysicalObjectShPtr obj2);

    // TODO think about combining theese methods
    void handleCollision(MovableObjectShPtr movable_obj,
                         const PhysicalObjectShPtr static_obj);

    void checkPlayerTilesCollision(PlayerShPtr player,
                                   std::vector<TileShPtr> &tiles);

    void checkParticleTileCollision(ParticleShPtr particle,
                                    std::vector<TileShPtr> &tiles);

    void checkParticleSetTileCollision(ParticleSetShPtr particles,
                                       std::vector<TileShPtr> &tiles);

    void checkEnemyTileCollision(EnemyShPtr enemy, std::vector<TileShPtr> &tiles);

    void checkPlayerParticleCollision(PlayerShPtr player, ParticleShPtr particle);

public:
    CollisionHandler();
    ~CollisionHandler();

    void run(std::vector<PlayerShPtr> &players,
             std::vector<TileShPtr> &tiles,
             //  ParticleSetShPtrparticles,
             std::vector<EnemyShPtr> &enemies);
};

using CollisionHandlerShPtr = std::shared_ptr<CollisionHandler>;
