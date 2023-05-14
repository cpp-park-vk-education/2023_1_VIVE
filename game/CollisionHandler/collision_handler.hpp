#pragma once

#include "physical_object.hpp"
#include "player.hpp"
#include "tile.hpp"

#include <vector>
#include <iostream>

class CollisionHandler
{
private:
    bool checkAABBCollision(const PhysicalObject &obj1,
                            const PhysicalObject &obj2);

public:
    CollisionHandler();
    ~CollisionHandler();

    void checkPlayerTilesCollision(Player *player,
                                   std::vector<Tile *> &tiles);
};
