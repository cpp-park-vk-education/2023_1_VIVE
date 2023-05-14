#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class HitBox
{
private:
    sf::RectangleShape shape_;

public:
    HitBox(const sf::Vector2f size, const sf::Vector2f position);
    ~HitBox();

    // Getters
    sf::FloatRect getGlobalBounds() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    sf::RectangleShape getShape() const;

    // Setters
    void setPosition(const sf::Vector2f position);
    void setSize(const sf::Vector2f size);
    void move(const sf::Vector2f displacement);
};

bool intersects(const HitBox& hitbox1, const HitBox& hitbox2);
