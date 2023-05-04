#include "movable_object.hpp"

MovableObject::MovableObject(const sf::Vector2f size,
    const sf::Vector2f position)
    : PhysicalObject(size, position)
{
}

MovableObject::~MovableObject()
{
}
