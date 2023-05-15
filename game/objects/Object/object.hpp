#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <memory>

const float BASE_SIZE = 24;

enum PRIORITY:uint8_t {
    BACKGROUND,
    TILES,
    ENEMIES,
    PARTICLES,
    PLAYER,
    PLAYER_USER_INTERFACE,
};

class Object : public sf::Drawable
{
protected:
    // TODO change to sf::Sprite
    sf::RectangleShape sprite_;

    uint8_t priority_;

    // Inits
    void virtual initSprite() = 0;

public:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const;
    virtual void update(const sf::Event &event, const float delta_time) = 0;
    Object();
    virtual ~Object();

    uint8_t getPriority() const;
};

using ObjectShPtr = std::shared_ptr<Object>;
using DrawableShPtr = std::shared_ptr<sf::Drawable>;