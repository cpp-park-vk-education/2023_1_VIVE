#pragma once

#include "entity.hpp"

#include <string>

class Player : Entity
{
protected:
    std::string name_;

    int exp_;
    int exp_max_;
    int curr_lvl_;
    int coins_count_;

public:
    Player();
    virtual ~Player();

    int getExp();
    void updateExp();
    int getExpMax();
    int getCurrLvl();
    void updateCurrLvl();
    int getCoinsCount();
    void updateCoinsCount();
};

