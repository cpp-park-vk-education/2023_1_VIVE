#pragma once

#include "movable_object.hpp"

enum TYPE
{
    COIN,
    EXP
};

class Particle : public MovableObject
{
protected:
    TYPE type_;
    bool exists_;

public:
    Particle(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~Particle();

    void create();
    void pop();
    bool doesExist() const;

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
