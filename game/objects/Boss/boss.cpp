#include "boss.hpp"

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

    hp_ = 500;
    hp_max_ = hp_;

    alive_ = true;
    attacking_ = false;
    damage_ = 50;
    damage_radius_ = BASE_SIZE * 2;
    attack_cooldown_ = 3;
    sec_since_last_hit_ = attack_cooldown_;
}

Boss::Boss(const sf::Vector2f size, const sf::Vector2f position)
    : Entity(size, position)
{
    priority_ = Priority::BOSSES;
    initAnimation();
    initSprite();
    initPhysics();
    initStats();
}

Boss::~Boss()
{
}

void Boss::update(const sf::Event &event, const float delta_time,
                  EntityShPtr target)
{
    updateMovement(delta_time, target);
    // TODO remove shape
    shape_.setPosition(hitbox_.getPosition());
    updateAttack(event, target, delta_time);
    updateHP();
}

void Boss::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    if (!isDead())
    {
        // target.draw(sprite_);
        target.draw(shape_);
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

void Boss::updateAttack(const sf::Event &event, std::shared_ptr<Entity> target, const float delta_time)
{
    
}
