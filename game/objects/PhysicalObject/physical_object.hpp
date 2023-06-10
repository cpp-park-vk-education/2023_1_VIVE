#pragma once

#include "object.hpp"
#include "hit_box.hpp"
#include "sound.hpp"

#include <memory>


class PhysicalObject : public Object
{
protected:
    HitBox hitbox_;
    SoundType sound_type_;

    // Initions
    void virtual initPhysics() = 0;

public:
    PhysicalObject(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~PhysicalObject();

    // Setters
    virtual void setPosition(const sf::Vector2f position);

    // Getters
    virtual sf::Vector2f getPosition() const;
    virtual sf::Vector2f getCenter() const;
    virtual sf::FloatRect getGlobalBounds() const;
    virtual bool doesExist() const;

    HitBox getHitBox() const;
};

using PhysicalObjectShPtr = std::shared_ptr<PhysicalObject>;
