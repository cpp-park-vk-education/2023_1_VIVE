#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

class Entity
{
protected:
    // Hitbox
    sf::RectangleShape hit_box;
    sf::Vector2f hit_box_size;
    sf::Vector2f hit_box_position;

public:
    Entity(sf::Vector2f hit_box_size, sf::Vector2f hit_box_position);
    virtual ~Entity();

    // Initions
    void initHitBox(sf::Vector2f size, sf::Vector2f position);

    // Functions
    virtual void update() = 0;
    virtual void render(sf::RenderTarget &target) = 0;
};
