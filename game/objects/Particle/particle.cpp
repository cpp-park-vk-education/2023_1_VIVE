#include "particle.hpp"

void Particle::initAnimation()
{
}

void Particle::initSprite()
{
    switch (type_)
    {
    case ParticeType::COIN:
        sprite_.setTexture(AssetManager::getInstance()->getTexture("money_particle"));
        break;

    case ParticeType::EXP:
        sprite_.setTexture(AssetManager::getInstance()->getTexture("star_particle"));
        break;

    case ParticeType::FIRE_BALL:
        // TODO remove shape
        shape_.setFillColor(sf::Color::Yellow);
        shape_.setOutlineColor(sf::Color::Red);
        shape_.setOutlineThickness(1);
        shape_.setSize(hitbox_.getSize());
        shape_.setPosition(hitbox_.getPosition());
        break;

    default:
        break;
    }

    if (type_ != ParticeType::FIRE_BALL)
    {
        sprite_.setScale(0.05f, 0.05f);
        sprite_.setPosition(hitbox_.getPosition());
    }
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

    displacement_ = sf::Vector2f(0.f, 0.f);
    acceleration_ = sf::Vector2f(0.f, gravity_acceleration_);
}

Particle::Particle(const sf::Vector2f &size, const sf::Vector2f &position,
                   const ParticeType type, const float max_speed,
                   const float gravity_acceleration)
    : MovableObject(size, position),
      exists_(false),
      type_(type)
{
    hitbox_.remove();
    priority_ = Priority::PARTICLES;
    max_speed_ = max_speed;
    gravity_acceleration_ = gravity_acceleration;
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
    create();
    setPosition(init_pos);
    initVelocity(direction, max_speed_);
}

void Particle::create()
{
    exists_ = true;
    hitbox_.appear();
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

ParticeType Particle::getType() const
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
        updateMovement(delta_time);
        if (type_ == ParticeType::FIRE_BALL)
        {
            shape_.setPosition(hitbox_.getPosition());
        }
    }
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    if (exists_)
    {
        if (type_ != ParticeType::FIRE_BALL)
        {
            target.draw(sprite_);
        }
        else
        {
            target.draw(shape_);
        }
    }
}

void Particle::setNewAnimation(char current_state)
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
