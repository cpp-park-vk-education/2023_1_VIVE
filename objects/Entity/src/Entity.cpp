#include "Entity.hpp"

Entity::Entity(sf::Vector2f hit_box_size, sf::Vector2f hit_box_position)
{
    initHitBox(hit_box_size, hit_box_position);
}

Entity::~Entity()
{
}

const sf::FloatRect Entity::getGlobalBounds() const
{
    return hit_box.getGlobalBounds();
}

const sf::Vector2f Entity::getPosition() const
{
    return hit_box.getPosition();
}

void Entity::resetVelocityY()
{
    velocity.y = 0.f;
}

void Entity::accelerate(const float dir_x, const float dir_y)
{
    // Acceleration
    velocity.x += dir_x * acceleration;

    // Limit velocity
    if (std::abs(velocity.x) > velocity_max)
    {
        velocity.x = velocity_max * ((velocity.x < 0.f) ? -1.f : 1.f);
    }
}
void Entity::initHitBox(sf::Vector2f size, sf::Vector2f position)
{
    hit_box.setSize(size);
    hit_box.setPosition(position);
    hit_box.setOutlineColor(sf::Color::Green);
    hit_box.setOutlineThickness(2);
}

void Entity::updatePhysics()
{
    // Gravity
    velocity.y += 1.f * gravity;

    // Limit gravity
    if (std::abs(velocity.y) > velocity_max_y)
    {
        velocity.y = velocity_max_y * ((velocity.y < 0.f) ? -1.f : 1.f);
    }

    // Movement
    velocity *= drag;

    // Limit deceleration
    if (std::abs(velocity.x) < velocity_min)
        velocity.x = 0.f;
    if (std::abs(velocity.y) < velocity_min)
        velocity.y = 0.f;

    move(velocity);
}

void Entity::update()
{
    updateMovement();
    updatePhysics();
}
