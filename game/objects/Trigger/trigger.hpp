#pragma once

#include "physical_object.hpp"

class Trigger : public PhysicalObject
{
protected:
    bool trigger;

    // Initions
    void initSprite() override;
    void initPhysics() override{};

public:
    Trigger(const sf::Vector2f size, const sf::Vector2f position);
    ~Trigger();

    // Object overrides
    void update(const sf::Event &event, const float delta_time) override;

    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates state) const override;

    void changeTrigger();
};

using TriggerShPtr = std::shared_ptr<Trigger>;
