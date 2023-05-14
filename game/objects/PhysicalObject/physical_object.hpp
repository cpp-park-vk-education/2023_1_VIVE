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

    // Setters
    virtual void setPosition(const sf::Vector2f size) = 0;

    // Getters
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

    HitBox getHitBox() const;
};
