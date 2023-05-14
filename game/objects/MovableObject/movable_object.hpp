#pragma once

#include "physical_object.hpp"

class MovableObject : public PhysicalObject
{
protected:
    sf::Vector2f displacement_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;

    float drag_;
    float gravity_acceleration_;
    float max_speed_;
    float speed_;

    bool is_moving;

public:
    MovableObject(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~MovableObject();

    virtual void move(const sf::Vector2f displacement) = 0;
    virtual void updateMovement(const float delta_time) = 0;
};
