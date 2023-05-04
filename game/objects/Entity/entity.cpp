#include "entity.hpp"

Entity::Entity(const sf::Vector2f size, const sf::Vector2f position)
    : MovableObject(size, position)
{
}

Entity::~Entity()
{
}

int Entity::getHP()
{
    return 0;
}

int Entity::getHPMax()
{
    return 0;
}

void Entity::updateHP(const int hp)
{
}