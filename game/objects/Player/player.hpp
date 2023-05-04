#pragma once

#include "entity.hpp"

#include <string>

class Player : public Entity
{
protected:
    std::string name_;

    int exp_;
    int exp_max_;
    int curr_lvl_;
    int coins_count_;

    // MovableObject overrides
    void move(sf::Vector2f displacement) override;

public:
    Player(const sf::Vector2f size, const sf::Vector2f position);
    virtual ~Player();

    int getExp();
    void updateExp();
    int getExpMax();
    int getCurrLvl();
    void updateCurrLvl();
    int getCoinsCount();
    void updateCoinsCount();

    // IObject overrides
    void update() override;
    void render() override;

    // PhysicalObject overrides
    void setPosition(const float x, const float y) override;

    // MovableObject overrides
    void updateMovement(const float delta_time) override;
};

