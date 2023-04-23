#include "Entity.hpp"

Entity::Entity(sf::Vector2f hit_box_size, sf::Vector2f hit_box_position)
{
    initHitBox(hit_box_size, hit_box_position);
}

Entity::~Entity()
{
}

void Entity::initHitBox(sf::Vector2f size, sf::Vector2f position)
{
    hit_box.setSize(size);
    hit_box.setPosition(position);
}

void Entity::update()
{
    updateMovement();
    updatePhysics();
}
