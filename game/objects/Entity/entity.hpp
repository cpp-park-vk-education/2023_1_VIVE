#pragma once

#include "movable_object.hpp"

class Entity : public MovableObject
{
protected:
    int hp_;
    int hp_max_;
    int mana_;
    int mana_max_;

    float jump_time_max_;
    float jump_time_;
    float jump_speed_;
    bool is_jumping_;

public:
    Entity();
    virtual ~Entity();

    int getHP();
    int getHPMax();
    void updateHP(const int hp);
};
