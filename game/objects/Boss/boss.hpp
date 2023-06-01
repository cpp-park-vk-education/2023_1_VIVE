#pragma once

#include "entity.hpp"
#include "particle.hpp"

class Boss : public Entity
{
protected:
    // int type_;
    // ParticleSet exp_particles_;
    // ParticleSet coin_particles_;
    float sight_radius_;
    float curr_fireball_lifetime_;
    float death_cooldown_;
    bool death_anim_;

    bool droped_;

    ParticleShPtr fireball_;

    // Initions
    void initAnimation() override;
    void initSprite() override;
    void initPhysics() override;
    void initStats() override;
    void initFireBall();
    // void initParticles();

    void updateFireBall(const sf::Event &event, const float delta_time);

public:
    Boss(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~Boss();

    // ParticleSet getCoinParticles();
    // ParticleSet getExpParticles();
    ParticleShPtr getFireBall() const;
    bool fireBallOut() const;
    bool didDrop() const;

    // Object overrides
    void update(const sf::Event &event, const float delta_time) override {};
    void update(const sf::Event &event, const float delta_time,
                EntityShPtr target);


    void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

    virtual void setNewAnimation(AnimStates current_state) override {};
    void drop();

    virtual void updateHP() override;

    // MovableObject overrides
    void updateMovement(const float delta_time) override;
    void updateMovement(const float delta_time, EntityShPtr target);
    virtual void updateAnimation(float delta_time) override {};

    virtual void updateAttack(const sf::Event &event, std::shared_ptr<Entity> target, const float delta_time) override;

    virtual void attack(EntityShPtr target) override;
};

using BossShPtr = std::shared_ptr<Boss>;


