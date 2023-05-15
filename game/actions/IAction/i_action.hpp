#pragma once

#include "entity.hpp"

class IAction
{
protected:
public:
    IAction();
    virtual ~IAction();

    virtual void action(Entity *executor, Entity *target) = 0;
    virtual void update() = 0;
};
