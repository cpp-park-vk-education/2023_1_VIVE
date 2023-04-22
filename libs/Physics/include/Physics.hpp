#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

class Physics
{
protected:
    // Parametres
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    float m_gravity;

    // Physics functions
    virtual void applyGravity(float deltaTime);
    virtual void move(float deltaTime) = 0;
    virtual void handleCollisions() = 0;

public:
    Physics(float gravity=9.8f);

    // Accessors
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

    // Modifiers
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);

    // Functions
    virtual void update(float deltaTime);
};
