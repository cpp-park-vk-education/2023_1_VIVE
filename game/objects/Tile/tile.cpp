#include "tile.hpp"

void Tile::initSprite()
{
    sprite_.setFillColor(sf::Color::Green);
    sprite_.setOutlineColor(sf::Color::Red);
    sprite_.setOutlineThickness(1);
    sprite_.setSize(hitbox_.getSize());
    sprite_.setPosition(hitbox_.getPosition());
}

void Tile::initPhysics()
{
}

Tile::Tile(const sf::Vector2f size, const sf::Vector2f position)
    : PhysicalObject(size, position)
{
    priority_ = PRIORITY::TILES;
    initSprite();
    initPhysics();
}

Tile::~Tile()
{
}

void Tile::update(const sf::Event &event, const float delta_time)
{
}

void Tile::setPosition(const sf::Vector2f size)
{
}

