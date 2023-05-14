#pragma once

#include "physical_object.hpp"

class Tile : public PhysicalObject
{
protected:
    int type_;

    // Initions
    void initSprite() override;
    void  initPhysics() override;

public:
    Tile(const sf::Vector2f size, const sf::Vector2f position);
    ~Tile();

    // Object overrides
    void update(const sf::Event &event, const float delta_time) override;
    void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

    // PhysicalObject overrides
    void setPosition(const sf::Vector2f size) override;
};
