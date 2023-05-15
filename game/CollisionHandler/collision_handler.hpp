#pragma once

#include "physical_object.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "enemy.hpp"

#include <vector>
#include <iostream>
#include <memory>

class CollisionHandler
{
private:
    bool checkAABBCollision(const PhysicalObject &obj1,
                            const PhysicalObject &obj2);

    void checkPlayerTilesCollision(Player *player,
                                   std::vector<Tile *> &tiles);

public:
    CollisionHandler();
    ~CollisionHandler();

    void run(std::vector<Player *> &players,
             std::vector<Tile *> &tiles,
             std::vector<Enemy *> &enemies);
};

using CollisionHandlerShPtr = std::shared_ptr<CollisionHandler>;
