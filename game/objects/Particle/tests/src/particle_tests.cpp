#include <gtest/gtest.h>

#include "particle.hpp"

TEST(GetSetPositionParticleTest, GetEqualSetTo)
{
    Particle particle(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));

    sf::Vector2f set_to(5.f, 10.f);
    particle.setPosition(set_to.x, set_to.y);

    sf::Vector2f actual = particle.getPosition();
    sf::Vector2f expected = set_to;

    EXPECT_EQ(actual, expected);
}

TEST(MoveParticleTest, MoveDiagonally)
{
    Particle particle(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(1.f, 1.f);
    particle.move(displacement);

    sf::Vector2f actual = particle.getPosition();
    sf::Vector2f expected(1.f, 1.f);

    EXPECT_EQ(actual, expected);
}

TEST(MoveParticleTest, NoMove)
{
    Particle particle(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(0.f, 0.f);
    particle.move(displacement);

    sf::Vector2f actual = particle.getPosition();
    sf::Vector2f expected(0.f, 0.f);

    EXPECT_EQ(actual, expected);
}

TEST(MoveParticleTest, MoveAlongX)
{
    Particle particle(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(5.f, 0.f);
    particle.move(displacement);

    sf::Vector2f actual = particle.getPosition();
    sf::Vector2f expected(5.f, 0.f);

    EXPECT_EQ(actual, expected);
}

TEST(MoveParticleTest, MoveAlongY)
{
    Particle particle(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(0.f, 5.f);
    particle.move(displacement);

    sf::Vector2f actual = particle.getPosition();
    sf::Vector2f expected(0.f, 5.f);

    EXPECT_EQ(actual, expected);
}

TEST(CreatePopParticle, CreteParticle)
{
    Particle particle(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    particle.create();
    
    bool actual = particle.doesExist();
    
    EXPECT_TRUE(actual);
}

TEST(CreatePopParticle, PopParticle)
{
    Particle particle(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    particle.create();
    particle.pop();
    
    bool actual = particle.doesExist();
    
    EXPECT_FALSE(actual);
}

TEST(CreatePopParticle, ParticleOnInit)
{
    Particle particle(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    
    bool actual = particle.doesExist();
    
    EXPECT_FALSE(actual);
}
