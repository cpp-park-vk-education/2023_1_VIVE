#pragma once

#include "particle.hpp"

#include <vector>
#include <iostream>

class ParticleSet
{
protected:
    std::vector<Particle *> particles_;
    unsigned int particles_count_;
    sf::Vector2f position_;
    sf::Vector2f size_;
    TYPE type_;
    bool exists_;

    // Initions
    void initParticles();

public:
    ParticleSet();
    
    ParticleSet(const unsigned int particles_count, const sf::Vector2f size,
                const sf::Vector2f position, TYPE type);
    virtual ~ParticleSet();

    void update(const sf::Event &event, const float delta_time);
    void draw(sf::RenderTarget &target, sf::RenderStates state) const;
    void generate();
    bool doesExist() const;

    // Iterators
    std::vector<Particle *>::iterator begin();
    std::vector<Particle *>::iterator end();
};

using ParticleSetShPtr = std::shared_ptr<ParticleSet>;
