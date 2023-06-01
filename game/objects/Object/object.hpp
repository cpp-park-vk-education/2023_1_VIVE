#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <memory>
#include <random>

const float BASE_SIZE = 24;

enum Priority : uint8_t
{
    BACKGROUND,
    TILES,
    TRIGGERS,
    ENEMIES,
    BOSSES,
    PARTICLES,
    PLAYERS,
    PLAYER_USER_INTERFACE,
    BUTTONS,
};

class Object;

using DrawableShPtr = std::shared_ptr<sf::Drawable>;
using ObjectShPtr = std::shared_ptr<Object>;

class Object : public sf::Drawable
{
protected:
    sf::Sprite sprite_;

    Priority priority_;

    // Inits
    virtual void initSprite(){};

public:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const;
    virtual void update(const sf::Event &event, const float delta_time) = 0;
    Object();
    virtual ~Object();

    // Getters
    Priority getPriority() const;
    sf::FloatRect getGlobalBounds() const;

    // Setters
    void setTexture(const sf::Texture &texture, bool resetRect = false);
    void setScale(float factorX, float factorY);
};

using ObjectShPtr = std::shared_ptr<Object>;
using DrawableShPtr = std::shared_ptr<sf::Drawable>;

struct CompareObjectsShPtr
{
    bool operator()(const ObjectShPtr &left, const ObjectShPtr &right)
    {
        return left->getPriority() > right->getPriority();
    }
};

int random_int(const int max, const int min);

float random_float(const float min, const float max);
