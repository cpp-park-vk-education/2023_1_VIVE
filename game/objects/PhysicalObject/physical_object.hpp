#pragma once

#include "i_object.hpp"
#include "hit_box.hpp"

class PhysicalObject : public IObject
{
protected:
    sf::Sprite sprite_;
    HitBox hitbox_;

public:
    PhysicalObject(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~PhysicalObject();

    virtual void setPosition(const float x, const float y) = 0;
    virtual sf::Vector2f getPosition() = 0;
};
