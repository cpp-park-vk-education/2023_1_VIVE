#include "hit_box.hpp"

HitBox::HitBox(const sf::Vector2f size, const sf::Vector2f position)
    : exists_(true)
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

sf::Vector2f HitBox::getCenter() const
{
    float x = getPosition().x + getGlobalBounds().width / 2;
    float y = getPosition().y + getGlobalBounds().height / 2;
    return sf::Vector2f(x, y);
}

void HitBox::remove()
{
    exists_ = false;
}

void HitBox::appear()
{
    exists_ = true;
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

bool HitBox::doesExist() const
{
    return exists_;
}

bool intersects(const HitBox &hitbox1, const HitBox &hitbox2)
{
    return hitbox1.getGlobalBounds().intersects(hitbox2.getGlobalBounds());
}
