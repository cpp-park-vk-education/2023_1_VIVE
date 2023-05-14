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

    void update(const sf::Event &event, const float delta_time);
    void draw() const;
    void generate();
    bool doesExist() const;
};
