#pragma once

#include "SFML/Graphics.hpp"

class HitBox
{
private:
    sf::RectangleShape shape_;

public:
    HitBox();
    ~HitBox();

    sf::FloatRect getGlobalBounds();
    sf::Vector2f getPosition();
    void setPosition(const float x, const float y);
};
