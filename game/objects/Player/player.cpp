#include "player.hpp"

void Player::move(sf::Vector2f displacement)
{
}

Player::Player(const sf::Vector2f size, const sf::Vector2f position)
    : Entity(size, position)
{
}

Player::~Player()
{
}

int Player::getExp()
{
    return 0;
}

void Player::updateExp()
{
}

int Player::getExpMax()
{
    return 0;
}

int Player::getCurrLvl()
{
    return 0;
}

void Player::updateCurrLvl()
{
}

int Player::getCoinsCount()
{
    return 0;
}

void Player::updateCoinsCount()
{
}

void Player::update()
{
}

void Player::render()
{
}

void Player::setPosition(const float x, const float y)
{
}

void Player::updateMovement(const float delta_time)
{
}
