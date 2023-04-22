#include "Physics.hpp"

void Physics::applyGravity(float deltaTime)
{
    // apply gravity
    m_position.y += m_gravity * deltaTime;
}

Physics::Physics(float gravity=9.8f)
    : m_gravity(gravity)
{
}

sf::Vector2f Physics::getPosition() const
{
    return m_position;
}

sf::Vector2f Physics::getSize() const
{
    return m_size;
}

void Physics::setPosition(sf::Vector2f position)
{
    m_position = position;
}

void Physics::setSize(sf::Vector2f size)
{
    m_size = size;
}

void Physics::update(float deltaTime)
{
    // Update physics
    applyGravity(deltaTime);
    move(deltaTime);
    handleCollisions();
}
