#pragma once

#include "object.hpp"
#include "hit_box.hpp"

class PhysicalObject : public Object
{
protected:
    HitBox hitbox_;

    // Initions
    void virtual initPhysics() = 0;

public:
    PhysicalObject(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~PhysicalObject();

    virtual void setPosition(const sf::Vector2f size) = 0;
    virtual sf::Vector2f getPosition() = 0;

    HitBox getHitBox() const;
};
