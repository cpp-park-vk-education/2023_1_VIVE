#include "movable_object.hpp"

MovableObject::MovableObject(const sf::Vector2f size,
    const sf::Vector2f position)
    : PhysicalObject(size, position)
{
}

MovableObject::~MovableObject()
{
}

void MovableObject::setVelocity(const sf::Vector2f &velocity)
{
    velocity_ = velocity;
}

void MovableObject::setAcceleration(const sf::Vector2f &acceleration)
{
    acceleration_ = acceleration;
}

void MovableObject::setDisplacement(const sf::Vector2f &displacement)
{
    displacement_ = displacement;
}

sf::Vector2f MovableObject::getVelocity() const
{
    return velocity_;
}

sf::Vector2f MovableObject::getAcceleration() const
{
    return acceleration_;
}

sf::Vector2f MovableObject::getDisplacement() const
{
    return displacement_;
}
