#pragma once

#include "i_action.hpp"
#include "physical_object.hpp"

#include <cmath>

class Attack : public IAction
{
private:
    float damage_radius_;
    unsigned int damage_;

    bool isInRadius(PhysicalObject *executor, PhysicalObject *target);

public:
    Attack(const unsigned int damage, float damage_radius_);
    virtual ~Attack();

    virtual void action(Entity *executor, Entity *target) override;
    virtual void update() override;
};
