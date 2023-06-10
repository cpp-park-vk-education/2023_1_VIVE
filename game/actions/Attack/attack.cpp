#include "attack.hpp"

bool Attack::isInRadius(PhysicalObject *executor, PhysicalObject *target)
{
    sf::Vector2f executor_pos = executor->getCenter();
    sf::Vector2f target_pos = target->getCenter();

    float distance = std::sqrt(std::pow(executor_pos.x - target_pos.x, 2) +
                               std::pow(executor_pos.y - target_pos.y, 2));

    return distance <= damage_radius_;
}

Attack::Attack(const unsigned int damage, float damage_radius)
    : damage_(damage),
      damage_radius_(damage_radius)
{
}

Attack::~Attack()
{
}

void Attack::action(Entity *executor, Entity *target)
{
    // if (isInRadius(executor, target))
    // {
    //     target->updateHP(damage_);
    // }
}

void Attack::update()
{
}
