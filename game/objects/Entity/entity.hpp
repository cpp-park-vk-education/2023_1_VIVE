#pragma once

#include "movable_object.hpp"

#include <cstdint>
#include <cmath>

class Entity;

using EntityShPtr = std::shared_ptr<Entity>;

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
    unsigned int damage_taken_;
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
    sf::Vector2f initial_pos_;

    bool isInDamageRadius(const PhysicalObjectShPtr target) const;

    virtual void attack(EntityShPtr target);

public:
    Entity(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~Entity();

    // Getters
    bool isDead() const;
    // virtual bool doesExist() const;
    int getHP() const;
    int getHPMax() const;
    unsigned int getDamage() const;

    // Setters
    void spawn();

    virtual void updateHP();
    virtual void updateAttack(const sf::Event &event, std::shared_ptr<Entity> target, const float delta_time) = 0;
    virtual void updateDamageTaken(const unsigned int damage);
};
