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
    sf::Vector2f displacement;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    // Speed
    float speed;
    float max_speed;
    bool moving;

    // Gravity
    float gravity_acceleration;
    float jump_speed;
    bool is_jumping;
    float jump_time;
    float max_jump_time;

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
    // void resetVelocityY();

    // Functions
    // virtual void accelerate(const float dir_x, const float dir_y);
    virtual void move(sf::Vector2f velocity) = 0;

    // virtual void updatePhysics();
    virtual void updateMovement(const float delta_time, sf::RenderWindow &window) = 0;
    virtual void updateCollision(sf::RenderWindow &window) = 0;

    virtual void update(const float delta_time, sf::RenderWindow &window) = 0;
    virtual void render(sf::RenderTarget &target) = 0;
};
