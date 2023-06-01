#include "tile.hpp"

void Tile::initSprite()
{
    sprite_.setTexture(AssetManager::getInstance()->getTexture("ground_world_level"));
    sprite_.setTextureRect(sf::IntRect(54, 42, 37, 38));
    sprite_.setScale(hitbox_.getSize().x / sprite_.getGlobalBounds().width, hitbox_.getSize().y / sprite_.getGlobalBounds().height);
    sprite_.setPosition(hitbox_.getPosition());
}

void Tile::initPhysics()
{
}

Tile::Tile(const sf::Vector2f size, const sf::Vector2f position)
    : PhysicalObject(size, position)
{
    priority_ = Priority::TILES;
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

