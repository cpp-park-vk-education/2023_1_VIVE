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

Priority Object::getPriority() const
{
    return priority_;
}

sf::FloatRect Object::getGlobalBounds() const
{
    return sprite_.getGlobalBounds();
}

void Object::setTexture(const sf::Texture &texture, bool resetRect)
{
    sprite_.setTexture(texture, resetRect);
}

void Object::setScale(float factorX, float factorY)
{
    sprite_.setScale(factorX, factorY);
}

int random_int(const int min, const int max)
{
    std::random_device rd;
    std::mt19937 gen(rd()); // generator
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

float random_float(const float min, const float max)
{
    std::random_device rd;
    std::mt19937 gen(rd()); // generator
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}
