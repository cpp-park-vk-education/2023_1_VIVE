#include "enemy.hpp"

void Enemy::spawnParticles()
{
    initParticles();
    coin_particles_->generate();
    exp_particles_->generate();
}

void Enemy::initAnimation() {
    animation_ = std::make_unique<Animation>("enemy_animation");
    animation_->updateSpriteSize(hitbox_.getSize());
}

void Enemy::initSprite()
{
    sprite_ = animation_->getSpriteAnimation();
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

    death_cooldown_ = 0.0f;
    death_anim_ = false;

    alive_ = true;
    attacking_ = false;
    damage_ = 10;
    damage_radius_ = BASE_SIZE;
    attack_cooldown_ = 2;
    sec_since_last_hit_ = attack_cooldown_;
}

void Enemy::initParticles()
{
    int coin_particles_count = random_int(5, 10);
    int exp_particles_count = random_int(5, 10);
    coin_particles_ = std::make_shared<ParticleSet>(coin_particles_count,
                                                    sf::Vector2f(10, 10),
                                                    getCenter(), ParticleType::COIN);

    exp_particles_ = std::make_shared<ParticleSet>(exp_particles_count,
                                                   sf::Vector2f(10, 10),
                                                   getCenter(), ParticleType::EXP);
}

Enemy::Enemy(const sf::Vector2f size, const sf::Vector2f position)
    : Entity(size, position)
{
    priority_ = Priority::ENEMIES;
    initAnimation();
    initSprite();
    initPhysics();
    initStats();
    // initParticles();
}

Enemy::~Enemy()
{
    // delete coin_particles_;
    // delete exp_particles_;
}

ParticleSetShPtr Enemy::getCoinParticles()
{
    return coin_particles_;
}

ParticleSetShPtr Enemy::getExpParticles()
{
    return exp_particles_;
}

bool Enemy::doesExist() const
{
    // if particles still exist
    if (isDead())
    {
        return coin_particles_->doesExist() || exp_particles_->doesExist();
    }
    else
    {
        return PhysicalObject::doesExist();
    }
}

void Enemy::updateHP()
{
    int new_hp = hp_ - damage_taken_;
    if (new_hp <= 0)
    {
        animation_->changeAnimation(AnimStates::DEATH_ANIM);
        SoundManager::getInstance()->playSoundEffect(SoundType::ENEMY_DEATH);
        hp_ = 0;
        alive_ = false;
        spawnParticles();
    }
    else
    {
        hp_ = new_hp;
    }
    damage_taken_ = 0;
}

void Enemy::updateAttack(const sf::Event &event, EntityShPtr target,
                         const float delta_time)
{
    if (sec_since_last_hit_ <= attack_cooldown_)
    {
        sec_since_last_hit_ += delta_time;
    }

    if (isInDamageRadius(target) && !attacking_ &&
        sec_since_last_hit_ > attack_cooldown_)
    {
        animation_->changeAnimation(AnimStates::ATTACK_ANIM);
        SoundManager::getInstance()->playSoundEffect(SoundType::ENEMY_CLOSE_ATTACK);
        attacking_ = true;
        attack(target);
        sec_since_last_hit_ = 0;
    }
    else if (attacking_)
    {
        attacking_ = false;
    }
}

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    if (isDead())
    {
        coin_particles_->draw(target, state);
        exp_particles_->draw(target, state);
    } 
    
    if (!death_anim_) {
        target.draw(sprite_);
    }
}

void Enemy::update(const sf::Event &event, const float delta_time,
                   EntityShPtr target)
{
    // std::cout << "Enemy exists" << std::endl;
    if (isDead())
    {
        death_cooldown_ += delta_time;

        if (death_cooldown_ <= 0.7f) {
            animation_->update(delta_time);
            sprite_ = animation_->getSpriteAnimation();
            sprite_.setPosition(hitbox_.getPosition());
        } else {
            death_anim_ = true;
            hitbox_.remove();
        }
        coin_particles_->update(event, delta_time);
        exp_particles_->update(event, delta_time);
    }
    else
    {
        // std::cout << "Enemy: " << getHP() << "/" << getHPMax() << std::endl;
        updateMovement(delta_time, target);
        updateAttack(event, target, delta_time);
        animation_->update(delta_time);
        sprite_ = animation_->getSpriteAnimation();
        sprite_.setPosition(hitbox_.getPosition());

        if (!isAttack())
            setStayAnnimation();

        updateHP();
    }
}

void Enemy::setNewAnimation(AnimStates current_state) {
    
}

void Enemy::updateAnimation(float delta_time)
{
}

void Enemy::updateMovement(const float delta_time)
{
    displacement_ = velocity_ * delta_time;
    move(displacement_);

    velocity_ = velocity_ + acceleration_ * delta_time;

    if (velocity_.x > 0) {
        animation_->changeAnimation(AnimStates::RIGHT_RUN_ANIM);
    } else if (velocity_.x < 0) {
        animation_->changeAnimation(AnimStates::LEFT_RUN_ANIM);
    }

    // Limit velocity.x
    if (std::abs(velocity_.x) > max_speed_)
    {
        velocity_.x = (velocity_.x / std::abs(velocity_.x)) * max_speed_;
    }
}

void Enemy::updateMovement(const float delta_time, EntityShPtr target)
{
    // Calculate direction vector to target
    sf::Vector2f direction = target->getCenter() - getCenter();

    // Normalize direction vector
    float length = std::sqrt(direction.x * direction.x +
                             direction.y * direction.y);
    direction /= length;

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

int random_int(const int min, const int max)
{
    std::random_device rd;
    std::mt19937 gen(rd()); // generator
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}
