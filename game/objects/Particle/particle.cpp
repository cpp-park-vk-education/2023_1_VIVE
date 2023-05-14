#include "particle.hpp"

void Particle::move(const sf::Vector2f displacement)
{
}

Particle::Particle(const sf::Vector2f size, const sf::Vector2f position)
    : MovableObject(size, position), exists_(false)
{
}

Particle::~Particle()
{
}

void Particle::create()
{
}

void Particle::pop()
{
}

bool Particle::doesExist() const
{
    return false;
}

void Particle::update(const sf::Event &event, const float delta_time)
{
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
}

void Particle::setPosition(const sf::Vector2f size)
{
}

sf::Vector2f Particle::getPosition()
{
    return sf::Vector2f();
}

void Particle::updateMovement(const float delta_time)
{
}
