#pragma once

#include "movable_object.hpp"

#include <cstdlib>
#include <memory>
#include <ctime>
#include <random>
#include <chrono>
#include <iostream>

enum TYPE
{
    COIN,
    EXP
};

float random_float(const float max, const float min);

class Particle : public MovableObject
{
protected:
    TYPE type_;
    bool exists_;

    // Initions
    void initSprite() override;
    void initPhysics() override;

    // MovableObject overrides
    void updateMovement(const float delta_time) override;

public:
    Particle(const sf::Vector2f size, const sf::Vector2f position,
             const TYPE type);
    virtual ~Particle();

    void create();
    void pop();

    // Getters
    bool doesExist() const;
    TYPE getType() const;

    // Object overrides
    void update(const sf::Event &event, const float delta_time) override;
    void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

};

using ParticleShPtr = std::shared_ptr<Particle>;
