#pragma once

#include "SFML/Graphics.hpp"

#include <memory>

class IObject;

using IObjectShPtr = std::shared_ptr<IObject>;
using DrawableShPtr = std::shared_ptr<sf::Drawable>;

class IObject : public sf::Drawable {
public:
    unsigned int getPriority() const;
    virtual void update(const sf::Event& event) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

private:
    unsigned int priority_;
};
