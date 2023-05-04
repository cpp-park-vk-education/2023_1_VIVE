#pragma once

#include "SFML/Graphics.hpp"

class IStatus {
public:
    virtual bool changePositionSprites(sf::Window& window) = 0;
    virtual bool setStatus(int status) = 0;
    virtual sf::Sprite getSprite() = 0;
    virtual ~IStatus();
    IStatus();
protected:
    sf::Sprite icon_sprite_;
    int max_status_;
    int current_status_;
    sf::Text text_;
};
