#include "hit_box.hpp"

HitBox::HitBox(const sf::Vector2f size, const sf::Vector2f position)
{
    shape_.setSize(size);
    setPosition(position);
}

HitBox::~HitBox()
{
}

sf::FloatRect HitBox::getGlobalBounds() const
{
    return shape_.getGlobalBounds();
}

sf::Vector2f HitBox::getPosition() const
{
    return shape_.getPosition();
}

sf::Vector2f HitBox::getSize() const
{
    return shape_.getSize();
}

sf::RectangleShape HitBox::getShape() const
{
    return shape_;
}

void HitBox::setPosition(const sf::Vector2f position)
{
    shape_.setPosition(position);
}

void HitBox::setSize(const sf::Vector2f size)
{
    shape_.setSize(size);
}

void HitBox::move(const sf::Vector2f displacement)
{
    shape_.move(displacement);
}
