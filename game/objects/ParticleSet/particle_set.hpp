#pragma once

#include "particle.hpp"

#include <vector>

class ParticleSet
{
protected:
    std::vector<Particle> particles_;
    bool exists_;

public:
    ParticleSet();
    virtual ~ParticleSet();

    void update();
    void render();
    void generate();
    bool doesExist() const;
};
