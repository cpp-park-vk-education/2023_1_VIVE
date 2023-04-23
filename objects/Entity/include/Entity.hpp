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
    float velocity_max;
    float velocity_min;
    float acceleration;
    float drag;
    float gravity;
    float velocity_max_y;

    // Initions
    virtual void initPhysics() = 0;
    void initHitBox(sf::Vector2f size, sf::Vector2f position);
    virtual void initShape(sf::Vector2f size) = 0;

public:
    Entity(sf::Vector2f hit_box_size, sf::Vector2f hit_box_position);
    virtual ~Entity();

    // Accessors
    const sf::FloatRect getGlobalBounds() const;
    const sf::Vector2f getPosition() const;

    // Modifiers
    virtual void setPosition(float const x, float const y) = 0;
    void resetVelocityY();

    // Functions
    virtual void accelerate(const float dir_x, const float dir_y);
    virtual void move(sf::Vector2f velocity) = 0;

    virtual void updatePhysics();
    virtual void updateMovement() = 0;

    virtual void update();
    virtual void render(sf::RenderTarget &target) = 0;
};
