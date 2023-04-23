#include "Player.hpp"

void Player::initShape(sf::Vector2f size)
{
    shape.setFillColor(sf::Color::White);
    shape.setSize(size);
}

Player::Player(sf::Vector2f hit_box_size, sf::Vector2f hit_box_position)
    : Entity(hit_box_size, hit_box_position)
{
    initShape(hit_box_size);
}

void Player::update()
{
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(hit_box);
}
