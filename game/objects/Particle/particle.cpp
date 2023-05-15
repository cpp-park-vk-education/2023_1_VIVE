#include "particle.hpp"

void Particle::initSprite()
{
    sprite_.setFillColor(sf::Color::Yellow);
    sprite_.setSize(hitbox_.getSize());
    sprite_.setPosition(hitbox_.getPosition());
}

void Particle::initPhysics()
{
    drag_ = 0.9;
    gravity_acceleration_ = 1000;

    max_speed_ = 200;
    speed_ = 100;
    float init_velocity_x = random_float(-max_speed_, max_speed_);
    std::cout << " x = " << init_velocity_x;
    float init_velocity_y = random_float(-max_speed_, max_speed_);
    std::cout << " y = " << init_velocity_y;
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
}

bool Particle::doesExist() const
{
    return exists_;
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

void Particle::updateMovement(const float delta_time)
{
    displacement_ = velocity_ * delta_time;
    move(displacement_);

    velocity_ = velocity_ + acceleration_ * delta_time;
}


float random_float(const float max, const float min)
{
    // unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::random_device rd; 
    std::mt19937 gen(rd()); // создание генератора случайных чисел
    std::uniform_real_distribution<float> dis(min, max); 
    return dis(gen);
    // return min + float(rand()) / RAND_MAX * (max - min);
}
