#pragma once

#include "entity.hpp"
#include "particle_set.hpp"

#include <iostream>

class Enemy : public Entity
{
protected:
    int type_;
    ParticleSet *exp_particles_;
    ParticleSet *coin_particles_;
    float sight_radius_;

    void spawnParticles();

    // Initions
    void initSprite() override;
    void initPhysics() override;
    void initStats() override;
    void initParticles();

public:
    Enemy(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~Enemy();

    // Object overrides
    void update(const sf::Event &event, const float delta_time) override;
    void update(const sf::Event &event, const float delta_time, Entity *target);

    // MovableObject overrides
    void updateMovement(const float delta_time) override;
    void updateMovement(const float delta_time, Entity *target);

    // Entity overrides
    virtual void updateHP(const unsigned int damage) override;
    virtual void updateAttack(const sf::Event &event, Entity *target, const float delta_time);

    // Getters
    ParticleSet *getCoinParticles();
    ParticleSet *getExpParticles();
    virtual bool doesExist() const override;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
};

int random_int(const int max, const int min);

using EnemyShPtr = std::shared_ptr<Enemy>;
