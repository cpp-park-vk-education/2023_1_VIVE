#include "enemy.hpp"

void Enemy::move(sf::Vector2f displacement)
{
}

Enemy::Enemy(const sf::Vector2f size, const sf::Vector2f position)
    : Entity(size, position)
{
}

Enemy::~Enemy()
{
}

ParticleSet Enemy::getCoinParticles()
{
    return ParticleSet();
}

ParticleSet Enemy::getExpParticles()
{
    return ParticleSet();
}

void Enemy::update()
{
}

void Enemy::render()
{
}

void Enemy::setPosition(const float x, const float y)
{
}

void Enemy::updateMovement(const float delta_time)
{
}
