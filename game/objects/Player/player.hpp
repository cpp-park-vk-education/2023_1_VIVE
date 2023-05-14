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

    // Initions
    void initSprite() override;
    void initPhysics() override;

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

    // Object overrides
    void update(const sf::Event &event, const float delta_time) override;
    void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

    // PhysicalObject overrides
    void setPosition(const sf::Vector2f position) override;
    sf::Vector2f getPosition() override;

    // MovableObject overrides
    void move(const sf::Vector2f displacement) override;
    void updateMovement(const float delta_time) override;
};
