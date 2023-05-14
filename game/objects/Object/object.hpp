#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Object : public sf::Drawable
{
protected:
    // TODO change to sf::Sprite
    sf::RectangleShape sprite_;

    unsigned int priority_;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const = 0;
    virtual void update(const sf::Event &event, const float delta_time) = 0;

    // Inits
    void virtual initSprite() = 0;

public:
    Object();
    virtual ~Object();

    unsigned int getPriority() const;
};
