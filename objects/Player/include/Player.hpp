#pragma once

#include "Entity.hpp"

class Player : public Entity
{
private:
    // Form
    sf::RectangleShape shape;

    // Physics

    // Initions
    void initShape(sf::Vector2f size) override;

public:
    Player(sf::Vector2f hit_box_size, sf::Vector2f hit_box_position);

    // Movement functions

    // Functions
    void update() override;
    void render(sf::RenderTarget &target) override;
};
