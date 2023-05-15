#include "particle_set.hpp"

void ParticleSet::initParticles()
{
    for (int i{}; i < particles_count_; ++i)
    {
        // std::cout << "Particle #" << i;
        Particle *particle = new Particle(size_, position_, type_);
        particles_.push_back(particle);
        // std::cout << std::endl;
    }
}

ParticleSet::ParticleSet()
{
}

ParticleSet::ParticleSet(const unsigned int particles_count,
                         const sf::Vector2f size, const sf::Vector2f position,
                         TYPE type)
    : particles_count_(particles_count),
      position_(position),
      size_(size),
      type_(type)
{
    initParticles();
}

ParticleSet::~ParticleSet()
{
    for (const auto &particle : particles_)
    {
        delete particle;
    }
}

void ParticleSet::setPosition(const sf::Vector2f &position)
{
    for (auto &particle : particles_)
    {
        particle->setPosition(position);
    }
}

void ParticleSet::update(const sf::Event &event, const float delta_time)
{
    if (exists_)
    {
        for (const auto &particle : particles_)
        {
            particle->update(event, delta_time);
        }
    }
}

void ParticleSet::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    for (const auto &particle : particles_)
    {
        particle->draw(target, state);
    }
}

void ParticleSet::generate()
{
    for (const auto &particle : particles_)
    {
        particle->create();
    }
    exists_ = true;
}

bool ParticleSet::doesExist() const
{
    return exists_;
}

std::vector<Particle *>::iterator ParticleSet::begin()
{
    return particles_.begin();
}

std::vector<Particle *>::iterator ParticleSet::end()
{
    return particles_.end();
}
