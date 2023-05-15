#include "enemy.hpp"

void Enemy::initSprite()
{
    sprite_.setFillColor(sf::Color::Red);
    sprite_.setSize(hitbox_.getSize());
    sprite_.setPosition(hitbox_.getPosition());
}

void Enemy::initPhysics()
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

void Enemy::initParticles()
{
    coin_particles_ = new ParticleSet(5, sf::Vector2f(10, 10),
                                      sf::Vector2f(400.f, 200.f), TYPE::COIN);

    exp_particles_ = new ParticleSet(5, sf::Vector2f(10, 10),
                                      sf::Vector2f(400.f, 200.f), TYPE::EXP);
}

Enemy::Enemy(const sf::Vector2f size, const sf::Vector2f position)
    : Entity(size, position)
{
    initSprite();
    initPhysics();
}

Enemy::~Enemy()
{
    delete coin_particles_;
    delete exp_particles_;
}

ParticleSet &Enemy::getCoinParticles()
{
    return *coin_particles_;
}

ParticleSet &Enemy::getExpParticles()
{
    return *exp_particles_;
}

void Enemy::update(const sf::Event &event, const float delta_time)
{
    updateMovement(delta_time);
}

void Enemy::updateMovement(const float delta_time)
{
    displacement_ = velocity_ * delta_time;
    move(displacement_);

    velocity_ = velocity_ + acceleration_ * delta_time;
}
