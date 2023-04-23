#include "Player.hpp"


void Player::initShape()
{
    shape.setFillColor(sf::Color::White);
    shape.setSize(sf::Vector2(50.f, 100.f));
}

Player::Player()
{
    initShape();
}
