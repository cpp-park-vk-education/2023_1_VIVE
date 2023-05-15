#include "object.hpp"

void Object::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    target.draw(sprite_);
}

Object::Object()
{
}

Object::~Object()
{
}

uint8_t Object::getPriority() const
{
    return priority_;
}
