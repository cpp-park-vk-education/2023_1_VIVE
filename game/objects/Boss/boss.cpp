#include "boss.hpp"

void Boss::move(sf::Vector2f displacement)
{
}

Boss::Boss(const sf::Vector2f size, const sf::Vector2f position)
    : Entity(size, position)
{
}

Boss::~Boss()
{
}

ParticleSet Boss::getCoinParticles()
{
    return ParticleSet();
}

ParticleSet Boss::getExpParticles()
{
    return ParticleSet();
}

void Boss::update()
{
}

void Boss::render()
{
}

void Boss::setPosition(const float x, const float y)
{
}

sf::Vector2f Boss::getPosition()
{
    return sf::Vector2f();
}

void Boss::updateMovement(const float delta_time)
{
}
