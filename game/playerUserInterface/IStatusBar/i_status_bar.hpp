#pragma once

#include "SFML/Graphics.hpp"

class IStatusBar {
public:
    virtual bool changePositionSprites(sf::Window& window) = 0;
    virtual sf::Sprite getSprite() = 0;
    virtual bool setStatus(int status) = 0;
    virtual ~IStatusBar();
    IStatusBar();

protected:
    sf::Sprite icon_sprite_;
    int max_status_;
    sf::Text text_;
    int current_status_;
    sf::RectangleShape bar_bg_;
};
