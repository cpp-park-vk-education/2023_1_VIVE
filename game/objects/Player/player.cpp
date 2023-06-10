#include "player.hpp"

void Player::initAnimation()
{
    animation_ = std::make_unique<Animation>("player_animation");
    animation_->updateSpriteSize(hitbox_.getSize());
}

void Player::initSprite()
{
    sprite_ = animation_->getSpriteAnimation();
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
    alive_ = true;
    attacking_ = false;
    damage_ = 30;
    damage_radius_ = BASE_SIZE * 3;
    attack_cooldown_ = 0.25f;
    sec_since_last_hit_ = attack_cooldown_;

    death_freeze_ = 2.0f;
    last_death_count_ = 0.0f;

    hp_ = 100;
    hp_max_ = hp_;

    curr_lvl_ = 2;
    exp_max_ = 500;

    coins_count_ = 0;
    exp_ = 0;
}

Player::Player(const sf::Vector2f size, const sf::Vector2f position)
    : Entity(size, position)
{
    priority_ = Priority::PLAYERS;
    initAnimation();
    initSprite();
    initPhysics();
    initStats();
}

Player::~Player()
{
}

int Player::getExp()
{
    return exp_;
}

void Player::updateExp(const uint16_t exp)
{
    exp_ += exp;
}

int Player::getExpMax()
{
    return exp_max_;
}

int Player::getCurrLvl()
{
    return curr_lvl_;
}

void Player::updateCurrLvl()
{
}

int Player::getCoinsCount()
{
    return coins_count_;
}

void Player::updateCoinsCount(const uint16_t coins_count)
{
    coins_count_ += coins_count;
}

void Player::update(const sf::Event &event, const float delta_time)
{
    updateMovement(delta_time);
    updateHP();
}

void Player::update(const sf::Event &event, Entity *target,
                    const float delta_time)
{
    if (!isDead())
    {
        updateMovement(delta_time);
    }
}

void Player::setNewAnimation(AnimStates current_state)
{
    animation_->changeAnimation(current_state);
    sprite_.setPosition(hitbox_.getSize());
}

void Player::updateAnimation(float delta_time)
{
    animation_->update(delta_time);
    sprite_ = animation_->getSpriteAnimation();

    sprite_.setPosition(hitbox_.getPosition());
}

void Player::updateMovement(const float delta_time)
{
    displacement_ = sf::Vector2f(0.f, 0.f);

    is_moving = false;

    // Moving left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        SoundManager::getInstance()->playSoundEffect(SoundType::RUNNING);
        acceleration_.x = -speed_ / delta_time;

        // Ограничиваем скорость персонажа
        if (velocity_.x < -max_speed_)
        {
            velocity_.x = -max_speed_;
        }
        is_moving = true;
        animation_->changeAnimation(AnimStates::LEFT_RUN_ANIM);
    }

    // Moving right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        SoundManager::getInstance()->playSoundEffect(SoundType::RUNNING);
        acceleration_.x = speed_ / delta_time;

        // Ограничиваем скорость персонажа
        if (velocity_.x > max_speed_)
        {
            velocity_.x = max_speed_;
        }
        is_moving = true;
        animation_->changeAnimation(AnimStates::RIGHT_RUN_ANIM);
    }

    // Обрабатываем прыжок персонажа
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !is_jumping_)
    {
        // Проверяем, находится ли персонаж на земле
        if (velocity_.y == 0)
        {
            SoundManager::getInstance()->playSoundEffect(SoundType::JUMP);
            animation_->changeAnimation(AnimStates::JUMP_ANIM);
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

// void Player::updateHP(const unsigned int damage)
// {
//     int new_hp = hp_ - damage;
//     if (new_hp <= 0)
//     {
//         hp_ = 0;
//         alive_ = false;
//         // hitbox_.remove();
//     }
//     else
//     {
//         hp_ = new_hp;
//     }
// }

void Player::updateAttack(const sf::Event &event, EntityShPtr target,
                          const float delta_time)
{
    if (sec_since_last_hit_ <= attack_cooldown_)
    {
        sec_since_last_hit_ += delta_time;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !attacking_ &&
        sec_since_last_hit_ > attack_cooldown_)
    {
        SoundManager::getInstance()->playSoundEffect(SoundType::CLOSE_ATTACK);
        animation_->changeAnimation(AnimStates::ATTACK_ANIM);
        attacking_ = true;
        attack(target);
        sec_since_last_hit_ = 0;
    }
    else if (attacking_ && !sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        attacking_ = false;
    }
}

void Player::updateAttack(const sf::Event &event,
                          std::vector<EntityShPtr> &targets,
                          const float delta_time)
{
    for (auto &target : targets)
    {
        updateAttack(event, target, delta_time);
    }
}
