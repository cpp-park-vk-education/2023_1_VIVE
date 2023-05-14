#pragma once

#include "entity.hpp"
#include "particle_set.hpp"

class Enemy : public Entity
{
protected:
    int type_;
    ParticleSet exp_particles_;
    ParticleSet coin_particles_;

public:
    Enemy(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~Enemy();

    ParticleSet getCoinParticles();
    ParticleSet getExpParticles();

    // Object overrides
    void update(const sf::Event &event, const float delta_time) override;
    void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

    // PhysicalObject overrides
    void setPosition(const sf::Vector2f size) override;
    sf::Vector2f getPosition() override;

    // MovableObject overrides
    void move(const sf::Vector2f displacement) override;
    void updateMovement(const float delta_time) override;
};
