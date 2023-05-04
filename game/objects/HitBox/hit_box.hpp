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

    sf::FloatRect getGlobalBounds();
    sf::Vector2f getPosition();
    void setPosition(const float x, const float y);
};
