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
