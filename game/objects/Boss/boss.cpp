#include "boss.hpp"
#include <cmath>

void Boss::initAnimation()
{
    animation_ = std::make_unique<Animation>("player_animation", 0);
    animation_->updateSpriteSize(hitbox_.getSize());
}

void Boss::initSprite()
{
    // sprite_ = animation_->getSpriteAnimation();
    // sprite_.setPosition(hitbox_.getPosition());
    // TODO remove shape
    shape_.setSize(hitbox_.getSize());
    shape_.setFillColor(sf::Color::Red);
    shape_.setOutlineColor(sf::Color::Black);
    shape_.setOutlineThickness(2);
}

void Boss::initPhysics()
{
    drag_ = 0.65;
    gravity_acceleration_ = 1000;

    max_speed_ = 50;
    speed_ = 10;

    jump_speed_ = 50;

    jump_time_ = 0;
    jump_time_max_ = 0.1;

    is_jumping_ = false;
    is_moving = false;

    displacement_ = sf::Vector2f(0.f, 0.f);
    velocity_ = sf::Vector2f(0.f, 0.f);
    acceleration_ = sf::Vector2f(0.f, gravity_acceleration_);
}

void Boss::initStats()
{
    sight_radius_ = 500;
    // fireball_lifetime_ =

    hp_ = 500;
    hp_max_ = hp_;

    alive_ = true;
    attacking_ = false;
    damage_ = 50;
    damage_radius_ = 250;
    attack_cooldown_ = 3;
    sec_since_last_hit_ = attack_cooldown_;
}

void Boss::initFireBall()
{
    fireball_ = std::make_shared<Particle>(
        sf::Vector2f(BASE_SIZE, BASE_SIZE),
        // TODO think about initial position
        sf::Vector2f(0, 0), ParticeType::FIRE_BALL,
        500, 1000);
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
    : Entity(size, position)
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

void Boss::update(const sf::Event &event, const float delta_time,
                  EntityShPtr target)
{
    updateMovement(delta_time, target);
    // TODO remove shape
    shape_.setPosition(hitbox_.getPosition());
    updateAttack(event, target, delta_time);
    updateFireBall(event, delta_time);
    updateHP();
}

void Boss::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    if (!isDead())
    {
        // target.draw(sprite_);
        target.draw(shape_);
        if (fireball_->doesExist())
        {
            fireball_->draw(target, sf::RenderStates());
        }
    }
}

void Boss::updateMovement(const float delta_time)
{
    displacement_ = velocity_ * delta_time;
    move(displacement_);

    velocity_ = velocity_ + acceleration_ * delta_time;

    // Limit velocity.x
    if (std::abs(velocity_.x) > max_speed_)
    {
        velocity_.x = (velocity_.x / std::abs(velocity_.x)) * max_speed_;
    }
}

void Boss::updateMovement(const float delta_time, EntityShPtr target)
{
    // Calculate direction vector and distance to target
    auto dir_dist = directionTo(target);
    auto direction = dir_dist.first;
    auto length = dir_dist.second;

    if (length < sight_radius_ && length > damage_radius_)
    {
        acceleration_.x = (speed_ * direction.x) / delta_time;
        updateMovement(delta_time);
    }
    else
    {
        acceleration_.x = 0;
        slowDown();
        updateMovement(delta_time);
    }
}

void Boss::updateAttack(const sf::Event &event, std::shared_ptr<Entity> target, const float delta_time)
{
    if (fireball_->doesExist() &&
        intersects(getHitBox(), target->getHitBox()))
    {
        std::cout << "Damage" << std::endl;
        target->updateDamageTaken(damage_);
        fireball_->pop();
    }

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
        // animation_->changeAnimation('a');
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

    fireball_->shoot(getCenter(), attack_dir);
    curr_fireball_lifetime_ = 0;
}
