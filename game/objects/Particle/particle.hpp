#pragma once

#include "movable_object.hpp"

#include <cstdlib>
#include <memory>
#include <iostream>

enum ParticleType
{
    COIN,
    EXP,
    FIRE_BALL,
    GEM,
};

float random_float(const float max, const float min);

class Particle : public MovableObject
{
protected:
    ParticleType type_;
    bool exists_;
    float life_time;
    float sec_since_creation;

    // Initions
    void initAnimation() override;
    void initSprite() override;
    void initVelocity(sf::Vector2f direction,
                      const float &init_velocity);

    void initPhysics() override;

    // MovableObject overrides
    void setNewAnimation(AnimStates current_state) override;
    void updateAnimation(float delta_time) override;
    void updateMovement(const float delta_time) override;

public:
    Particle(const sf::Vector2f &size, const sf::Vector2f &position,
             const ParticleType type);

    virtual ~Particle();

    void shoot(const sf::Vector2f &init_pos, sf::Vector2f direction);
    void create();
    void pop();

    // Getters
    bool doesExist() const;
    ParticleType getType() const;
    float getGravitiAcceleration() const;
    float getMaxSpeed() const;

    // Object overrides
    void update(const sf::Event &event, const float delta_time) override;
    void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
};

using ParticleShPtr = std::shared_ptr<Particle>;
