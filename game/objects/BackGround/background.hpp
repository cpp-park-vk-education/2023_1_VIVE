#pragma once

#include "object.hpp"

class BackGround : public Object
{
private:
    void update(const sf::Event &event, const float delta_time) {}

public:
    BackGround();
    ~BackGround();

};

using BackGroundShPtr = std::shared_ptr<BackGround>;
