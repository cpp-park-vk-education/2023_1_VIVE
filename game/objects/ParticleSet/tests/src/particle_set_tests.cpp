#include <gtest/gtest.h>

#include "particle_set.hpp"

TEST(GenerateParticleSet, OnInit)
{
    ParticleSet particle_set;
    
    bool actual = particle_set.doesExist();
    
    EXPECT_FALSE(actual);
}

TEST(GenerateParticleSet, AfterGenerate)
{
    ParticleSet particle_set;
    particle_set.generate();
    
    bool actual = particle_set.doesExist();
    
    EXPECT_TRUE(actual);
}
