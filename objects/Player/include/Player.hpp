#pragma once

#include "Entity.hpp"

class Player : public Entity
{
private:
    // Form

    // Physics

    // Initions

public:
    Player(sf::Vector2f hit_box_size, sf::Vector2f hit_box_position);

    // Movement functions

    // Functions
    void update() override;
    void render(sf::RenderTarget &target) override;
};
