#pragma once

#include "physical_object.hpp"

class CollisionHandler
{
public:
    CollisionHandler();
    ~CollisionHandler();

    bool checkCollision(const PhysicalObject &ob1, const PhysicalObject &ob2);
};
