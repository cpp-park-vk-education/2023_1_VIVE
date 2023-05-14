#include "boss.hpp"

void Boss::move(const sf::Vector2f displacement)
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

void Boss::update(const sf::Event &event, const float delta_time)
{
}

void Boss::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
}

void Boss::setPosition(const sf::Vector2f size)
{
}

void Boss::updateMovement(const float delta_time)
{
}
