#include "hit_box.hpp"

HitBox::HitBox(const sf::Vector2f size, const sf::Vector2f position)
{
}

HitBox::~HitBox()
{
}

sf::FloatRect HitBox::getGlobalBounds()
{
    return sf::FloatRect();
}

sf::Vector2f HitBox::getPosition()
{
    return sf::Vector2f();
}

void HitBox::setPosition(const float x, const float y)
{
}
