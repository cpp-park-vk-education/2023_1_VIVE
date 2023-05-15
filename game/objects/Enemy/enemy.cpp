#include "enemy.hpp"

void Enemy::spawnParticles()
{
    initParticles();
    // coin_particles_->setPosition(getCenter());
    // exp_particles_->setPosition(getCenter());
    coin_particles_->generate();
    exp_particles_->generate();
}

void Enemy::initSprite()
{
    sprite_.setFillColor(sf::Color::Red);
    sprite_.setSize(hitbox_.getSize());
    sprite_.setPosition(hitbox_.getPosition());
}

void Enemy::initPhysics()
{
    drag_ = 0.85;
    gravity_acceleration_ = 1000;

    max_speed_ = 200;
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

void Enemy::initStats()
{
    sight_radius_ = 200;

    hp_ = 100;
    hp_max_ = hp_;

    alive_ = true;
}

void Enemy::initParticles()
{
    int coin_particles_count = random_int(5, 10);
    int exp_particles_count = random_int(5, 10);
    coin_particles_ = new ParticleSet(coin_particles_count,
                                      sf::Vector2f(10, 10),
                                      getCenter(), TYPE::COIN);

    exp_particles_ = new ParticleSet(exp_particles_count,
                                     sf::Vector2f(10, 10),
                                     getCenter(), TYPE::EXP);
}

Enemy::Enemy(const sf::Vector2f size, const sf::Vector2f position)
    : Entity(size, position)
{
    initSprite();
    initPhysics();
    initStats();
    // initParticles();
}

Enemy::~Enemy()
{
    delete coin_particles_;
    delete exp_particles_;
}

ParticleSet *Enemy::getCoinParticles()
{
    return coin_particles_;
}

ParticleSet *Enemy::getExpParticles()
{
    return exp_particles_;
}

void Enemy::updateHP(const unsigned int damage)
{
    int new_hp = hp_ - damage;
    if (new_hp < 0)
    {
        hp_ = 0;
        alive_ = false;
        hitbox_.remove();
        spawnParticles();
    }
    else
    {
        hp_ = new_hp;
    }
}

void Enemy::updateAttack(const sf::Event &event, Entity *target,
                         const float delta_time)
{
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    if (isDead())
    {
        coin_particles_->draw(target, state);
        exp_particles_->draw(target, state);
    }
    else
    {
        target.draw(sprite_);
    }
}

void Enemy::update(const sf::Event &event, const float delta_time)
{
    // std::cout << "Enemy's helth: " << hp_ << "/" << hp_max_ << std::endl;
    if (isDead())
    {
        coin_particles_->update(event, delta_time);
        exp_particles_->update(event, delta_time);
    }
    else
    {
        updateMovement(delta_time);
    }
}

void Enemy::update(const sf::Event &event, const float delta_time,
                   Entity *target)
{
    std::cout << getHP() << "/" << getHPMax() << std::endl;
    if (isDead())
    {
        coin_particles_->update(event, delta_time);
        exp_particles_->update(event, delta_time);
    }
    else
    {
        updateMovement(delta_time, target);
    }
}

void Enemy::updateMovement(const float delta_time)
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

void Enemy::updateMovement(const float delta_time, Entity *target)
{
    // Calculate direction vector to target
    sf::Vector2f direction = target->getCenter() - getCenter();

    // Normalize direction vector
    float length = std::sqrt(direction.x * direction.x +
                             direction.y * direction.y);
    direction /= length;

    if (length < sight_radius_ && length > BASE_SIZE * 2)
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

int random_int(const int max, const int min)
{
    std::random_device rd; 
    std::mt19937 gen(rd()); // generator
    std::uniform_real_distribution<> dis(min, max); 
    return dis(gen);
}
