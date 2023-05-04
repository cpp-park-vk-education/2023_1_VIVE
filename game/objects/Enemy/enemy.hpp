#pragma once

#include "entity.hpp"
#include "particle_set.hpp"

class Enemy
{
protected:
    int type_;
    ParticleSet exp_particles_;
    ParticleSet coin_particles_;

public:
    Enemy(/* args */);
    virtual ~Enemy();

    ParticleSet getCoinParticles();
    ParticleSet getExpParticles();
};
