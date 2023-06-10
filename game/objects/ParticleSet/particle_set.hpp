#pragma once

#include "particle.hpp"

#include <vector>
#include <iostream>

class ParticleSet
{
protected:
    std::vector<ParticleShPtr> particles_;
    unsigned int particles_count_;
    sf::Vector2f position_;
    sf::Vector2f size_;
    ParticleType type_;
    bool exists_;

    void clear();

    // Initions
    void initParticles();

public:
    ParticleSet();

    ParticleSet(const unsigned int particles_count, const sf::Vector2f size,
                const sf::Vector2f position, ParticleType type);
    virtual ~ParticleSet();

    // Setters
    void setPosition(const sf::Vector2f &position);

    void update(const sf::Event &event, const float delta_time);
    void draw(sf::RenderTarget &target, sf::RenderStates state) const;
    void generate();
    bool doesExist() const;

    // Iterators
    std::vector<ParticleShPtr>::iterator begin();
    std::vector<ParticleShPtr>::iterator end();
};

using ParticleSetShPtr = std::shared_ptr<ParticleSet>;
