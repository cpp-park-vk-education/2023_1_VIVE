#pragma once

#include "entity.hpp"
#include "particle_set.hpp"

#include <iostream>

class Enemy : public Entity
{
protected:
    int type_;
    ParticleSetShPtr exp_particles_;
    ParticleSetShPtr coin_particles_;
    float sight_radius_;

    void spawnParticles();

    // Initions
    void initAnimation() override;
    void initSprite() override;
    void initPhysics() override;
    void initStats() override;
    void initParticles();

public:
    Enemy(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~Enemy();

    // Object overrides
    void update(const sf::Event &event, const float delta_time) override;
    void update(const sf::Event &event, const float delta_time, EntityShPtr target);

    // MovableObject overrides
    void setNewAnimation(char current_state) override;
    void updateAnimation(float delta_time) override;
    void updateMovement(const float delta_time) override;
    void updateMovement(const float delta_time, EntityShPtr target);

    // Entity overrides
    virtual void updateHP(const unsigned int damage) override;
    virtual void updateAttack(const sf::Event &event, EntityShPtr target, const float delta_time);

    // Getters
    ParticleSetShPtr getCoinParticles();
    ParticleSetShPtr getExpParticles();
    virtual bool doesExist() const override;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

    bool isAttack() const {
        return attacking_;
    }

    void setStayAnnimation() {
        animation_->changeAnimation('s');
    }
};


using EnemyShPtr = std::shared_ptr<Enemy>;
