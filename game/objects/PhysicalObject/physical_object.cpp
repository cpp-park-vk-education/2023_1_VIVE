#include "physical_object.hpp"

PhysicalObject::PhysicalObject(const sf::Vector2f size,
                               const sf::Vector2f position)
    : hitbox_(size, position)
{
}

PhysicalObject::~PhysicalObject()
{
}

void PhysicalObject::setPosition(const sf::Vector2f position)
{
    sprite_.setPosition(position);
    hitbox_.setPosition(position);
}

sf::Vector2f PhysicalObject::getPosition() const
{
    return hitbox_.getPosition();
}

sf::FloatRect PhysicalObject::getGlobalBounds() const
{
    return hitbox_.getGlobalBounds();
}

HitBox PhysicalObject::getHitBox() const
{
    return hitbox_;
}
