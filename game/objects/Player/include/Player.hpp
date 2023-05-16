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
    void initPhysics();

public:
    Player(sf::Vector2f hit_box_size, sf::Vector2f hit_box_position);

    // Modifiers
    void setPosition(float const x, float const y) override;

    // Functions
    void move(sf::Vector2f velocity) override;

    void updateMovement(const float delta_time, sf::RenderWindow &window) override;
    void updateCollision(sf::RenderWindow &window);

    void update(const float delta_time, sf::RenderWindow &window) override;
    void render(sf::RenderTarget &target) override;
};
