#pragma once

#include "movable_object.hpp"

enum TYPE
{
    COIN,
    EXP
};

class Particle : public MovableObject
{
protected:
    TYPE type_;

public:
    Particle(/* args */);
    virtual ~Particle();

    void create();
    void pop();
};
