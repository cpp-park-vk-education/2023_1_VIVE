#include "physical_object.hpp"

PhysicalObject::PhysicalObject(const sf::Vector2f size,
    const sf::Vector2f position)
    : hitbox_(size, position)
{
}

PhysicalObject::~PhysicalObject()
{
}

HitBox PhysicalObject::getHitBox() const
{
    return hitbox_;
}
