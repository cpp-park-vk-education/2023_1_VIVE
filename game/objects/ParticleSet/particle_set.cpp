#include "particle_set.hpp"

void ParticleSet::clear()
{
    // Remove non-existent pfrticles from vector
    for (auto it = particles_.begin(); it != particles_.end();)
    {
        if (!(*it) || !(*it)->doesExist())
        {
            it = particles_.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void ParticleSet::initParticles()
{
    for (int i{}; i < particles_count_; ++i)
    {
        // std::cout << "Particle #" << i;
        ParticleShPtr particle = std::make_shared<Particle>(size_, position_, type_);
        particles_.push_back(particle);
        // std::cout << std::endl;
    }
}

ParticleSet::ParticleSet()
{
}

ParticleSet::ParticleSet(const unsigned int particles_count,
                         const sf::Vector2f size, const sf::Vector2f position,
                         ParticleType type)
    : particles_count_(particles_count),
      position_(position),
      size_(size),
      type_(type)
{
    initParticles();
}

ParticleSet::~ParticleSet()
{
    // for (const auto &particle : particles_)
    // {
    //     delete particle;
    // }
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
        clear();
        // std::cout << particles_.size() << std::endl;
        for (const auto &particle : particles_)
        {
            particle->update(event, delta_time);
        }

        if (particles_.empty())
        {
            exists_ = false;
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

std::vector<ParticleShPtr>::iterator ParticleSet::begin()
{
    return particles_.begin();
}

std::vector<ParticleShPtr>::iterator ParticleSet::end()
{
    return particles_.end();
}
