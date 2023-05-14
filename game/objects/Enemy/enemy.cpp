#include "enemy.hpp"

void Enemy::move(const sf::Vector2f displacement)
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

void Enemy::update(const sf::Event &event, const float delta_time)
{
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
}

void Enemy::setPosition(const sf::Vector2f size)
{
}

sf::Vector2f Enemy::getPosition()
{
    return sf::Vector2f();
}

void Enemy::updateMovement(const float delta_time)
{
}
