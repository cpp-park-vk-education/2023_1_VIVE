#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

class Entity
{
protected:
    // Hitbox
    sf::RectangleShape hit_box;

    // Physics
    sf::Vector2f velocity;
    float velocityMax;
    float velocityMin;
    float acceleration;
    float drag;

    // Initions
    virtual void initPhysics() = 0;
    void initHitBox(sf::Vector2f size, sf::Vector2f position);
    virtual void initShape(sf::Vector2f size) = 0;

public:
    Entity(sf::Vector2f hit_box_size, sf::Vector2f hit_box_position);
    virtual ~Entity();

    // Functions
    virtual void accelerate(const float dir_x, const float dir_y) = 0;
    virtual void move(sf::Vector2f velocity) = 0;

    virtual void updatePhysics() = 0;
    virtual void updateMovement() = 0;

    virtual void update();
    virtual void render(sf::RenderTarget &target) = 0;
};
