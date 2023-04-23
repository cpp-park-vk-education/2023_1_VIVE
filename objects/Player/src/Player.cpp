#include "Player.hpp"




Player::Player(sf::Vector2f hit_box_size, sf::Vector2f hit_box_position)
    :   Entity(hit_box_size, hit_box_position)
{
    hit_box.setFillColor(sf::Color::White);
}

void Player::update()
{
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(hit_box);
}
