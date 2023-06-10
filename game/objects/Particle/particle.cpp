#include "particle.hpp"

void Particle::initAnimation()
{
    animation_ = std::make_unique<Animation>("fire_ball_animation");
    animation_->updateSpriteSize(hitbox_.getSize());
}

void Particle::initSprite()
{
    switch (type_)
    {
    case ParticleType::COIN:
        sprite_.setTexture(AssetManager::getInstance()->getTexture("money_particle"));
        break;

    case ParticleType::EXP:
        sprite_.setTexture(AssetManager::getInstance()->getTexture("star_particle"));
        break;

    case ParticleType::FIRE_BALL:
        initAnimation();
        sprite_ = animation_->getSpriteAnimation();
        break;

    case ParticleType::GEM:
        sprite_.setTexture(AssetManager::getInstance()->getTexture("ground_stone"));
        break;

    default:
        break;
    }

    if (type_ != ParticleType::GEM)
        sprite_.setScale(0.05f, 0.05f);
    else
        sprite_.setScale(0.10f, 0.10f);

    sprite_.setPosition(hitbox_.getPosition());
}

void Particle::initVelocity(sf::Vector2f direction,
                            const float &init_velocity)
{
    // Normalize direction vector
    float length = std::sqrt(direction.x * direction.x +
                             direction.y * direction.y);
    direction /= length;

    sf::Vector2f init_vector_velocity = direction * init_velocity;
    velocity_ = init_vector_velocity;
}

void Particle::initPhysics()
{
    drag_ = 0.1;
    life_time = 10;

    if (type_ == ParticleType::FIRE_BALL)
    {
        max_speed_ = 500;
        gravity_acceleration_ = 1000;
    }
    else
    {
        max_speed_ = 300;
        gravity_acceleration_ = 600;
    }

    displacement_ = sf::Vector2f(0.f, 0.f);
    acceleration_ = sf::Vector2f(0.f, gravity_acceleration_);
}

Particle::Particle(const sf::Vector2f &size, const sf::Vector2f &position,
                   const ParticleType type)
    : MovableObject(size, position),
      exists_(false),
      type_(type)
{
    hitbox_.remove();
    priority_ = Priority::PARTICLES;
    initSprite();
    initPhysics();
    // random initial direction
    sf::Vector2f direction(random_float(-1, 1), random_float(-1, 1));
    // random initial speed
    float init_speed = random_float(-max_speed_, max_speed_);
    initVelocity(direction, init_speed);
}

Particle::~Particle()
{
}

void Particle::shoot(const sf::Vector2f &init_pos, sf::Vector2f direction)
{
    animation_->changeAnimation(AnimStates::PARTICLE_ATTACK);
    create();
    setPosition(init_pos);
    initVelocity(direction, max_speed_);
}

void Particle::create()
{
    exists_ = true;
    hitbox_.appear();
    sec_since_creation = 0;
}

void Particle::pop()
{
    exists_ = false;
    hitbox_.remove();
}

bool Particle::doesExist() const
{
    return exists_;
}

ParticleType Particle::getType() const
{
    return type_;
}

float Particle::getGravitiAcceleration() const
{
    return gravity_acceleration_;
}

float Particle::getMaxSpeed() const
{
    return max_speed_;
}

void Particle::update(const sf::Event &event, const float delta_time)
{
    if (exists_)
    {
        // TODO remove shape_
        if (type_ == ParticleType::GEM)
        {
            sprite_.setPosition(hitbox_.getPosition());
        }
        updateMovement(delta_time);
        if (type_ == ParticleType::FIRE_BALL)
        {
            animation_->update(delta_time);
            sprite_ = animation_->getSpriteAnimation();
            sprite_.setPosition(hitbox_.getPosition());
        }

        // life time handle
        if (sec_since_creation > life_time)
        {
            pop();
        }
        else
        {
            sec_since_creation += delta_time;
        }
    }
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    if (exists_)
    {
        target.draw(sprite_);
    }
}

void Particle::setNewAnimation(AnimStates current_state)
{
}

void Particle::updateAnimation(float delta_time)
{
}

void Particle::updateMovement(const float delta_time)
{
    displacement_ = velocity_ * delta_time;
    move(displacement_);

    velocity_ = velocity_ + acceleration_ * delta_time;
}
