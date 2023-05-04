#pragma once

#include "entity.hpp"
#include "particle_set.hpp"

class Boss : public Entity
{
protected:
    int type_;
    ParticleSet exp_particles_;
    ParticleSet coin_particles_;

public:
    Boss(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~Boss();

    ParticleSet getCoinParticles();
    ParticleSet getExpParticles();

    // IObject overrides
    void update() override;
    void render() override;

    // PhysicalObject overrides
    void setPosition(const float x, const float y) override;
    sf::Vector2f getPosition() override;

    // MovableObject overrides
    void move(sf::Vector2f displacement) override;
    void updateMovement(const float delta_time) override;
};
