#pragma once

#include "movable_object.hpp"

#include <cstdint>
#include <cmath>

class Entity : public MovableObject
{
protected:
    // Stats
    uint16_t hp_;
    uint16_t hp_max_;
    uint16_t mana_;
    uint16_t mana_max_;

    // Attacks
    float attack_cooldown_;
    float sec_since_last_hit_;
    unsigned int damage_;
    float damage_radius_;
    bool attacking_;

    bool exists_;
    bool alive_;

    // Physics
    float jump_time_max_;
    float jump_time_;
    float jump_speed_;
    bool is_jumping_;

    // Initions
    virtual void initStats() = 0;

    bool isInDamageRadius(const PhysicalObject *target) const;

    virtual void attack(Entity *target);

public:
    Entity(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~Entity();

    // Getters
    bool isDead() const;
    virtual bool doesExist() const = 0;
    int getHP() const;
    int getHPMax() const;

    // Setters
    void spawn();

    virtual void updateHP(const unsigned int damage) = 0;
    virtual void updateAttack(const sf::Event &event, Entity *target, const float delta_time) = 0;
};
