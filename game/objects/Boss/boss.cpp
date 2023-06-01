#include "boss.hpp"
#include <cmath>

void Boss::initAnimation()
{
    animation_ = std::make_unique<Animation>("boss_animation");
    animation_->updateSpriteSize(hitbox_.getSize());
}

void Boss::initSprite()
{
    sprite_ = animation_->getSpriteAnimation();
    sprite_.setPosition(hitbox_.getPosition());
}

void Boss::initPhysics()
{
    drag_ = 0.65;
    gravity_acceleration_ = 1000;

    max_speed_ = 100;
    speed_ = 10;

    jump_speed_ = 50;

    jump_time_ = 0;
    jump_time_max_ = 0.1;

    is_jumping_ = false;
    is_moving = false;

    displacement_ = sf::Vector2f(0.f, 0.f);
    velocity_ = sf::Vector2f(0.f, 0.f);
    acceleration_ = sf::Vector2f(0.f, 0.f);
}

void Boss::initStats()
{
    sight_radius_ = 500;

    hp_ = 500;
    hp_max_ = hp_;

    death_cooldown_ = 0.0f;
    death_anim_ = false;

    alive_ = true;
    attacking_ = false;
    damage_ = 50;
    damage_radius_ = 250;
    attack_cooldown_ = 1.5;
    sec_since_last_hit_ = attack_cooldown_;
}

void Boss::initFireBall()
{
    fireball_ = std::make_shared<Particle>(
        sf::Vector2f(BASE_SIZE, BASE_SIZE),
        // TODO think about initial position
        sf::Vector2f(0, 0), ParticleType::FIRE_BALL);
}

void Boss::updateFireBall(const sf::Event &event, const float delta_time)
{
    if (fireball_->doesExist())
    {
        if (curr_fireball_lifetime_ > attack_cooldown_)
        {
            fireball_->pop();
            curr_fireball_lifetime_ = 0;
        }
        else
        {
            fireball_->update(event, delta_time);
            curr_fireball_lifetime_ += delta_time;
        }
    }
}

Boss::Boss(const sf::Vector2f size, const sf::Vector2f position)
    : Entity(size, position),
      droped_(false)
{
    priority_ = Priority::BOSSES;
    initAnimation();
    initSprite();
    initPhysics();
    initStats();
    initFireBall();
}

Boss::~Boss()
{
}

ParticleShPtr Boss::getFireBall() const
{
    return fireball_;
}

bool Boss::fireBallOut() const
{
    return fireball_->doesExist();
}

bool Boss::didDrop() const
{
    return droped_;
}

void Boss::update(const sf::Event &event, const float delta_time,
                  EntityShPtr target)
{
    if (!isDead())
    {
        updateMovement(delta_time, target);
        animation_->update(delta_time);
        sprite_ = animation_->getSpriteAnimation();
        sprite_.setPosition(hitbox_.getPosition());
        updateAttack(event, target, delta_time);
        updateFireBall(event, delta_time);

        if (damage_taken_ > 0) {
            animation_->changeAnimation(AnimStates::GET_DAMMAGE);
        }

        updateHP();
    }
    else if (fireBallOut())
    {
        updateFireBall(event, delta_time);
    }
    if (isDead()) {
        death_cooldown_ += delta_time;

        if (death_cooldown_ <= 1.5f) {
            animation_->update(delta_time);
            sprite_ = animation_->getSpriteAnimation();
            sprite_.setPosition(hitbox_.getPosition());
        } else {
            death_anim_ = true;
            hitbox_.remove();
        }
    }
}

void Boss::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    if (!isDead())
    {
        target.draw(sprite_);
        if (fireball_->doesExist())
        {
            fireball_->draw(target, sf::RenderStates());
        }
    }
    if (!death_anim_) {
        target.draw(sprite_);
    }
}

void Boss::updateHP() {
    int new_hp = hp_ - damage_taken_;

    if (damage_taken_ > 0) {
        SoundManager::getInstance()->playSoundEffect(SoundType::ENEMY_GET_DAMAGE);
    }

    if (new_hp <= 0)
    {
        animation_->changeAnimation(AnimStates::DEATH_ANIM);
        SoundManager::getInstance()->playWinningMusic();
        hp_ = 0;
        alive_ = false;
    }
    else
    {
        hp_ = new_hp;
    }
    damage_taken_ = 0;
}

void Boss::drop()
{
    droped_ = true;
}

void Boss::updateMovement(const float delta_time)
{
    displacement_ = velocity_ * delta_time;
    move(displacement_);

    velocity_ = velocity_ + acceleration_ * delta_time;

    if (velocity_.x < 0)
        animation_->changeAnimation(AnimStates::LEFT_RUN_ANIM);
    else
        animation_->changeAnimation(AnimStates::RIGHT_RUN_ANIM);

    // Limit velocity.x
    if (std::abs(velocity_.x) > max_speed_)
    {
        velocity_.x = (velocity_.x / std::abs(velocity_.x)) * max_speed_;
    }

    if (std::abs(velocity_.y) > max_speed_)
    {
        velocity_.y = (velocity_.y / std::abs(velocity_.y)) * max_speed_;
    }
}

void Boss::updateMovement(const float delta_time, EntityShPtr target)
{
    // Calculate direction vector and distance to target
    auto dir_dist = directionTo(target);
    auto direction = dir_dist.first;
    auto length = dir_dist.second;

    if (/* length < sight_radius_ &&  */ length > damage_radius_)
    {
        acceleration_.x = (speed_ * direction.x) / delta_time;
        acceleration_.y = (speed_ * direction.y) / delta_time;
        updateMovement(delta_time);
    }
    else if (length < damage_radius_ * 0.9)
    {
        acceleration_.x = -(speed_ * direction.x) / delta_time;
        updateMovement(delta_time);
    }
    else
    {
        acceleration_.x = 0;
        acceleration_.y = 0;
        slowDown();
        updateMovement(delta_time);
    }
}

void Boss::updateAttack(const sf::Event &event, std::shared_ptr<Entity> target, const float delta_time)
{
    if (sec_since_last_hit_ <= attack_cooldown_)
    {
        sec_since_last_hit_ += delta_time;
    }

    if (isInDamageRadius(target) && !attacking_ &&
        sec_since_last_hit_ > attack_cooldown_)
    {
        attacking_ = true;
        attack(target);
        sec_since_last_hit_ = 0;
    }
    else if (attacking_)
    {
        attacking_ = false;
    }
}

void Boss::attack(EntityShPtr target)
{
    // fireball params
    float gravity_acceleration = fireball_->getGravitiAcceleration();
    float speed = fireball_->getMaxSpeed();

    // real difference between coords of target and Boss
    float dy = target->getPosition().y - getCenter().y;
    float dx = target->getPosition().x - getCenter().x;

    // solve quadratic equasion
    // a * tan(alpha)^2 + b * tan(alpha) + c = 0
    float a = (gravity_acceleration * std::pow(dx, 2)) /
              (2 * std::pow(speed, 2));
    float b = dx;
    float c = a - dy;

    float D = std::pow(b, 2) - 4 * a * c;

    float tan_1 = (b + std::sqrt(D)) / (2 * a);
    float tan_2 = (b - std::sqrt(D)) / (2 * a);

    float alpha_1 = std::atan(tan_1);
    float alpha_2 = std::atan(tan_2);

    auto attack_dir_dist = directionTo(target);

    float dir_x, dir_y;
    if (attack_dir_dist.first.x > 0)
    {
        dir_x = std::cos(alpha_1);
        dir_y = -std::sin(alpha_1);
    }
    else
    {
        dir_x = -std::cos(alpha_2);
        dir_y = std::sin(alpha_2);
    }

    sf::Vector2f attack_dir(dir_x, dir_y);

    SoundManager::getInstance()->playSoundEffect(SoundType::ENEMY_FIRE_ATTACK);
    animation_->changeAnimation(AnimStates::ATTACK_ANIM);
    fireball_->shoot(getCenter(), attack_dir);
    curr_fireball_lifetime_ = 0;
}
