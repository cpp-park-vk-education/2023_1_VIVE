#include "player.hpp"

void Player::initSprite()
{
    sprite_.setFillColor(sf::Color::White);
    sprite_.setSize(hitbox_.getSize());
    sprite_.setPosition(hitbox_.getPosition());
}

void Player::initPhysics()
{
    drag_ = 0.8;
    gravity_acceleration_ = 1000;

    max_speed_ = 400;
    speed_ = 50;

    jump_speed_ = 200;

    jump_time_ = 0;
    jump_time_max_ = 0.1;

    is_jumping_ = false;
    is_moving = false;

    displacement_ = sf::Vector2f(0.f, 0.f);
    velocity_ = sf::Vector2f(0.f, 0.f);
    acceleration_ = sf::Vector2f(0.f, gravity_acceleration_);
}

void Player::initStats()
{
}

Player::Player(const sf::Vector2f size, const sf::Vector2f position)
    : Entity(size, position)
{
    initSprite();
    initPhysics();
    initStats();
}

Player::~Player()
{
}

int Player::getExp()
{
    return 0;
}

void Player::updateExp()
{
}

int Player::getExpMax()
{
    return 0;
}

int Player::getCurrLvl()
{
    return 0;
}

void Player::updateCurrLvl()
{
}

int Player::getCoinsCount()
{
    return 0;
}

void Player::updateCoinsCount()
{
}

void Player::update(const sf::Event &event, const float delta_time)
{
    updateMovement(delta_time);
}

void Player::updateMovement(const float delta_time)
{
    displacement_ = sf::Vector2f(0.f, 0.f);

    is_moving = false;

    // Moving left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        acceleration_.x = -speed_ / delta_time;

        // Ограничиваем скорость персонажа
        if (velocity_.x < -max_speed_)
        {
            velocity_.x = -max_speed_;
        }
        is_moving = true;
    }

    // Moving right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        acceleration_.x = speed_ / delta_time;

        // Ограничиваем скорость персонажа
        if (velocity_.x > max_speed_)
        {
            velocity_.x = max_speed_;
        }
        is_moving = true;
    }

    // Обрабатываем торможение персонажа
    // if (!is_moving)
    // {
    //     velocity_.x = 0;
    // }

    // Обрабатываем прыжок персонажа
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !is_jumping_)
    {
        // Проверяем, находится ли персонаж на земле
        if (velocity_.y == 0)
        {
            is_jumping_ = true;
            jump_time_ = 0;
            velocity_.y = -jump_speed_;
        }
    }

    if (is_jumping_)
    {
        jump_time_ += delta_time;
        if (jump_time_ < jump_time_max_)
        {
            acceleration_.y = gravity_acceleration_ - jump_speed_ / jump_time_max_;
        }
        else
        {
            is_jumping_ = false;
            acceleration_.y = gravity_acceleration_;
        }
    }

    // Обновляем ускорение, скорость и позицию персонажа
    velocity_ += acceleration_ * delta_time;
    displacement_ = velocity_ * delta_time;

    move(displacement_);

    acceleration_.x = 0;
}
