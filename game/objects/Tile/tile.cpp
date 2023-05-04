#include "tile.hpp"

Tile::Tile(const sf::Vector2f size, const sf::Vector2f position)
    : PhysicalObject(size, position)
{
}

Tile::~Tile()
{
}

void Tile::update()
{
}

void Tile::render()
{
}

void Tile::setPosition(const float x, const float y)
{
}

sf::Vector2f Tile::getPosition()
{
    return sf::Vector2f();
}
