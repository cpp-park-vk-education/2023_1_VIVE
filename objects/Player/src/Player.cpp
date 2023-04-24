#include "Player.hpp"

void Player::initShape(sf::Vector2f size)
{
    shape.setFillColor(sf::Color::White);
    shape.setSize(size);
}

void Player::initPhysics()
{
    velocity_max = 15.f;
    velocity_min = 1.f;
    acceleration = 2.f;
    drag = 0.8f;
    gravity = 9.8f;
    velocity_max_y = 20.f;
}

Player::Player(sf::Vector2f hit_box_size, sf::Vector2f hit_box_position)
    : Entity(hit_box_size, hit_box_position)
{
    initShape(hit_box_size);
    initPhysics();
}

void Player::setPosition(float const x, float const y)
{
    hit_box.setPosition(x, y);
    shape.setPosition(x, y);
}

void Player::move(sf::Vector2f velocity)
{
    shape.move(velocity);
    hit_box.move(velocity);
}

void Player::updateMovement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        accelerate(-1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        accelerate(1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        accelerate(0.f, -2.f);
    }
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(shape);
    target.draw(hit_box);
}
