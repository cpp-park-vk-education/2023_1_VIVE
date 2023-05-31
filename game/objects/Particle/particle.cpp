#include "particle.hpp"

void Particle::initAnimation() {
    
}

void Particle::initSprite()
{
    if (type_ == TYPE::COIN)
    {
        sprite_.setTexture(AssetManager::getInstance()->getTexture("money_particle"));
    }
    else if (type_ == TYPE::EXP)
    {
        sprite_.setTexture(AssetManager::getInstance()->getTexture("star_particle"));
    }
    sprite_.setScale(0.05f, 0.05f);
    sprite_.setPosition(hitbox_.getPosition());
}

void Particle::initPhysics()
{
    drag_ = 0.7;
    gravity_acceleration_ = 600;

    max_speed_ = 300;
    float init_velocity_x = random_float(-max_speed_, max_speed_);
    // std::cout << " x = " << init_velocity_x;
    float init_velocity_y = random_float(-max_speed_, max_speed_);
    // std::cout << " y = " << init_velocity_y;
    sf::Vector2f init_velocity(init_velocity_x, init_velocity_y);

    is_moving = false;

    displacement_ = sf::Vector2f(0.f, 0.f);
    velocity_ = init_velocity;
    acceleration_ = sf::Vector2f(0.f, gravity_acceleration_);
}

Particle::Particle(const sf::Vector2f size, const sf::Vector2f position,
                   const TYPE type)
    : MovableObject(size, position),
      exists_(false),
      type_(type)
{
    priority_ = PRIORITY::PARTICLES;
    initSprite();
    initPhysics();
}

Particle::~Particle()
{
}

void Particle::create()
{
    exists_ = true;
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

TYPE Particle::getType() const
{
    return type_;
}

void Particle::update(const sf::Event &event, const float delta_time)
{
    if (exists_)
    {
        updateMovement(delta_time);
    }
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    if (exists_)
    {
        target.draw(sprite_);
    }
}

void Particle::setNewAnimation(AnimStates current_state) {
    
}

void Particle::updateAnimation(float delta_time) {
}

void Particle::updateMovement(const float delta_time)
{
    displacement_ = velocity_ * delta_time;
    move(displacement_);

    velocity_ = velocity_ + acceleration_ * delta_time;
}
