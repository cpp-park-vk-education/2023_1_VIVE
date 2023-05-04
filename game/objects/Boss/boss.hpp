#pragma once

#include "entity.hpp"
#include "particle_set.hpp"

class Boss
{
protected:
    int type_;
    ParticleSet exp_particles_;
    ParticleSet coin_particles_;

public:
    Boss(/* args */);
    virtual ~Boss();

    ParticleSet getCoinParticles();
    ParticleSet getExpParticles();
};
