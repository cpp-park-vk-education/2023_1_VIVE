#pragma once

#include "entity.hpp"
#include "particle_set.hpp"

class Enemy : public Entity
{
protected:
    int type_;
    ParticleSet *exp_particles_;
    ParticleSet *coin_particles_;

    // Initions
    void initSprite() override;
    void initPhysics() override;
    void initParticles();

public:
    Enemy(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~Enemy();

    // Object overrides
    void update(const sf::Event &event, const float delta_time) override;

    // MovableObject overrides
    void updateMovement(const float delta_time) override;

    // Getters
    ParticleSet &getCoinParticles();
    ParticleSet &getExpParticles();
};

using EnemyShPtr = std::shared_ptr<Enemy>;
