#pragma once

#include "physical_object.hpp"
#include "animation.hpp"

class MovableObject;

using MovableObjectShPtr = std::shared_ptr<MovableObject>;

class MovableObject : public PhysicalObject
{
protected:
    sf::Vector2f displacement_;
    sf::Vector2f velocity_;
    sf::Vector2f acceleration_;

    float drag_;
    float gravity_acceleration_;
    float max_speed_;
    float speed_;

    //Animation
    std::unique_ptr<Animation> animation_;

    bool is_moving;
    std::pair<sf::Vector2f, float> directionTo(
        const MovableObjectShPtr &target);

public:
    //Init
    virtual void initAnimation() = 0;

    MovableObject(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~MovableObject();

    virtual void setNewAnimation(AnimStates current_state) = 0;

    virtual void move(const sf::Vector2f displacement);
    virtual void updateAnimation(float delta_time) = 0;
    virtual void updateMovement(const float delta_time) = 0;
    virtual void slowDown();

    // Setters
    void setVelocity(const sf::Vector2f &velocity);
    void setAcceleration(const sf::Vector2f &acceleration);
    void setDisplacement(const sf::Vector2f &displacement);

    // Getters
    sf::Vector2f getVelocity() const;
    sf::Vector2f getAcceleration() const;
    sf::Vector2f getDisplacement() const;
};

