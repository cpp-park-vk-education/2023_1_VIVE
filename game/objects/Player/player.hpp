#pragma once

#include "entity.hpp"

#include <string>
#include <memory>
#include <iostream>

class Player : public Entity
{
protected:
    std::string name_;

    bool was_event_;
    int exp_;
    int exp_max_;
    int curr_lvl_;
    int coins_count_;

    float death_freeze_;
    float last_death_count_;

    // Initions
    void initSprite() override;
    void initPhysics() override;
    void initStats() override;
    void initAnimation() override;

public:
    Player(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~Player();

    bool isRunning() const
    {
        return is_moving;
    }

    bool isJumping() const
    {
        return is_jumping_;
    }

    bool isAttack() const
    {
        return attacking_;
    }

    bool checkDeathFreeze(float delta_time)
    {
        last_death_count_ += delta_time;

        if (last_death_count_ >= death_freeze_)
        {
            last_death_count_ = 0;
            return true;
        }

        return false;
    }

    void setStayAnimation() const
    {
        animation_->changeAnimation(AnimStates::STAY_ANIM);
    }

    AnimStates getCurrentState() const {
        return animation_->getCurrentState();
    }

    bool isLeftRun() const {
        return animation_->isLeftRun();
    }

    // Getters
    int getExp();
    int getExpMax();
    int getCurrLvl();
    int getCoinsCount();

    // Updates
    void updateExp(const uint16_t exp);
    void updateCurrLvl();
    void updateCoinsCount(const uint16_t coins_count);

    // Object overrides
    void update(const sf::Event &event, const float delta_time) override;
    void update(const sf::Event &event, Entity *target, const float delta_time);

    // MovableObject overrides
    void setNewAnimation(AnimStates current_state) override;
    void updateAnimation(float delta_time) override;
    void updateMovement(const float delta_time) override;

    // Entity overrides
    virtual void updateAttack(const sf::Event &event, EntityShPtr target,
                              const float delta_time) override;

    void updateAttack(const sf::Event &event,
                      std::vector<EntityShPtr> &targets,
                      const float delta_time);
    // virtual void updateHP(const unsigned int damage);
};

using PlayerShPtr = std::shared_ptr<Player>;
