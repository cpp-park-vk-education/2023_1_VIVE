#pragma once

#include "physical_object.hpp"

class MovableObject : PhysicalObject
{
protected:
    sf::Vector2f displacement_;
    sf::Vector2f valocity_;
    sf::Vector2f acceleration_;
    float drag_;
    float garavity_acceleration_;
    float max_speed_;
    float speed_;

    virtual void move(sf::Vector2f displacement) = 0;

public:
    MovableObject(/* args */);
    virtual ~MovableObject();

    virtual void updateMovement(const float delta_time) = 0;
};
