#pragma once

#include "object.hpp"
#include "SFML/Graphics.hpp"

class Item
{
protected:
    sf::Sprite sprite_;
    int type_;

public:
    Item();
    virtual ~Item();
};
