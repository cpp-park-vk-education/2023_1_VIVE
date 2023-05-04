#pragma once

#include "physical_object.hpp"

class Tile : public PhysicalObject
{
protected:
    int type_;
public:
    Tile(const sf::Vector2f size, const sf::Vector2f position);
    ~Tile();

    // IObject overrides
    void update() override;
    void render() override;

    // PhysicalObject overrides
    void setPosition(const float x, const float y) override;
    sf::Vector2f getPosition() override;
};
