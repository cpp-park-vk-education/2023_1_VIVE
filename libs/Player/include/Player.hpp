#pragma once

#include "Physics.hpp"

class Player : public Physics
{
private:
    // Form
    sf::RectangleShape shape;

    // Physics
    sf::Vector2f m_velocity;
    float m_speed = 200.0f;
    float m_jumpHeight = 500.0f;
    float m_friction = 0.9f;

    void move(float deltaTime) override;
    void handleCollisions() override;

    // Core
    void initShape();

public:
    Player(float gravity=9.8f);

    // Movement functions
    void moveLeft();
    void moveRight();
    void jump();
    void stop();

    void update(float deltaTime) override;
};
