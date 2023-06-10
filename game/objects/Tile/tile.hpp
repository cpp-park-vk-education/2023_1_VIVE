#pragma once

#include "physical_object.hpp"
#include "asset_manager.hpp"

class Tile : public PhysicalObject
{
protected:
    int type_;

    // Initions
    void initSprite() override;
    void initPhysics() override;

public:
    Tile(const sf::Vector2f size, const sf::Vector2f position);
    ~Tile();

    // Object overrides
    void update(const sf::Event &event, const float delta_time) override;

    // PhysicalObject overrides
    void setPosition(const sf::Vector2f size) override;
};

using TileShPtr = std::shared_ptr<Tile>;
