#pragma once

#include "entity.hpp"

#include <string>
#include <memory>
#include <iostream>

class Player : public Entity
{
protected:
    std::string name_;

    int exp_;
    int exp_max_;
    int curr_lvl_;
    int coins_count_;

    // Initions
    void initSprite() override;
    void initPhysics() override;
    void initStats() override;

public:
    Player(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~Player();

    int getExp();
    void updateExp(const uint16_t exp);
    int getExpMax();
    int getCurrLvl();
    void updateCurrLvl();
    int getCoinsCount();
    void updateCoinsCount(const uint16_t coins_count);

    // Object overrides
    void update(const sf::Event &event, const float delta_time) override;
    void update(const sf::Event &event, Entity *target, const float delta_time);

    // MovableObject overrides
    void updateMovement(const float delta_time) override;

    // Entity overrides
    virtual void updateAttack(const sf::Event &event, Entity *target, const float delta_time);
    virtual void updateHP(const unsigned int damage);
};

using PlayerShPtr = std::shared_ptr<Player>;
