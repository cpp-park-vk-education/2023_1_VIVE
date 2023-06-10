#include "movable_object.hpp"

std::pair<sf::Vector2f, float> MovableObject::directionTo(
    const MovableObjectShPtr &target)
{
    // Calculate direction vector to target
    sf::Vector2f direction = target->getCenter() - getCenter();

    // Normalize direction vector
    float length = std::sqrt(direction.x * direction.x +
                             direction.y * direction.y);
    direction /= length;

    std::pair<sf::Vector2f, float> res{direction, length};
    return res;
}

MovableObject::MovableObject(const sf::Vector2f size,
                             const sf::Vector2f position)
    : PhysicalObject(size, position)
{
}

MovableObject::~MovableObject()
{
}

void MovableObject::move(const sf::Vector2f displacement)
{
    const float MAX_DISPLACEMENT = max_speed_ * 0.1;
    float distance = std::sqrt(
        std::pow(displacement.x, 2) +
        std::pow(displacement.y, 2));

    if (distance > MAX_DISPLACEMENT)
    {
        sf::Vector2f new_displacement = displacement / distance;
        new_displacement *= MAX_DISPLACEMENT;
        sprite_.move(new_displacement);
        hitbox_.move(new_displacement);
    }
    else
    {
        sprite_.move(displacement);
        hitbox_.move(displacement);
    }
}

void MovableObject::slowDown()
{
    if (std::abs(velocity_.x) > 0.01 * max_speed_)
    {
        velocity_.x *= drag_;
    }
    else
    {
        velocity_.x = 0;
    }
}

void MovableObject::setVelocity(const sf::Vector2f &velocity)
{
    velocity_ = velocity;
}

void MovableObject::setAcceleration(const sf::Vector2f &acceleration)
{
    acceleration_ = acceleration;
}

void MovableObject::setDisplacement(const sf::Vector2f &displacement)
{
    displacement_ = displacement;
}

sf::Vector2f MovableObject::getVelocity() const
{
    return velocity_;
}

sf::Vector2f MovableObject::getAcceleration() const
{
    return acceleration_;
}

sf::Vector2f MovableObject::getDisplacement() const
{
    return displacement_;
}
