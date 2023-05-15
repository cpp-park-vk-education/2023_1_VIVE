#pragma once

#include "physical_object.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "particle_set.hpp"

#include <vector>
#include <iostream>
#include <memory>

class CollisionHandler
{
private:
    bool checkAABBCollision(const PhysicalObject *obj1,
                            const PhysicalObject *obj2);

    void handleCollision(MovableObject *movable_obj,
                         const PhysicalObject *static_obj);

    void checkPlayerTilesCollision(Player *player,
                                   std::vector<Tile *> &tiles);

    void checkParticleTileCollision(Particle *particle,
                                   std::vector<Tile *> &tiles);

public:
    CollisionHandler();
    ~CollisionHandler();

    void run(std::vector<Player *> &players,
             std::vector<Tile *> &tiles,
             ParticleSet *particles);
};

using CollisionHandlerShPtr = std::shared_ptr<CollisionHandler>;
