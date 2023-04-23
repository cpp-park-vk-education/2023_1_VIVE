#include "Player.hpp"

void Player::initShape(sf::Vector2f size)
{
    shape.setFillColor(sf::Color::White);
    shape.setSize(size);
}

void Player::initPhysics()
{
    velocityMax = 15.f;
    velocityMin = 1.f;
    acceleration = 2.f;
    drag = 0.8f;
}

Player::Player(sf::Vector2f hit_box_size, sf::Vector2f hit_box_position)
    : Entity(hit_box_size, hit_box_position)
{
    initShape(hit_box_size);
    initPhysics();
}

void Player::accelerate(const float dir_x, const float dir_y)
{
    // Acceleration
    velocity.x += dir_x * acceleration;

    // Limit velocity
    if (std::abs(velocity.x) > velocityMax)
    {
        velocity.x = velocityMax * ((velocity.x < 0.f) ? -1.f : 1.f);
    }
}

void Player::move(sf::Vector2f velocity)
{
    shape.move(velocity);
    hit_box.move(velocity);
}

void Player::updatePhysics()
{
    // Movement
    velocity *= drag;

    // Limit deceleration
    if (std::abs(velocity.x) < velocityMin)
        velocity.x = 0.f;
    if (std::abs(velocity.y) < velocityMin)
        velocity.y = 0.f;

    move(velocity);
}

void Player::updateMovement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        accelerate(-1.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        accelerate(1.f, 0.f);
    }
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(shape);
}
