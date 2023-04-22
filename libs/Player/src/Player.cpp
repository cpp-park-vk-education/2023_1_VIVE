#include "Player.hpp"

void Player::move(float deltaTime)
{
    // Move Player
    m_position += m_velocity * deltaTime;
}

void Player::handleCollisions()
{
    // handle collisions
}

void Player::initShape()
{
    shape.setFillColor(sf::Color::White);
    shape.setSize(sf::Vector2(50.f, 100.f));
}

Player::Player(float gravity=9.8f)
    : Physics(gravity)
{
    initShape();
}

void Player::moveLeft()
{
    m_velocity.x = -m_speed;
}

void Player::moveRight()
{
    m_velocity.x = m_speed;
}

void Player::jump()
{
    m_velocity.y = -m_jumpHeight;
}

void Player::stop()
{
    m_velocity.x = 0;
}

void Player::update(float deltaTime)
{
    // Update Player's physics
    applyGravity(deltaTime);
    move(deltaTime);
    handleCollisions();

    // Update Player's velocity
    m_velocity.x *= m_friction;
    m_velocity.y *= m_friction;

    // Update Player's position
    m_position += m_velocity * deltaTime;
}
