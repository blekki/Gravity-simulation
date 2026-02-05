#include <gtest/gtest.h>
#include "particle.h"

using namespace std;

TEST(ParticleTest, InitWithoutParameters) {
    Particle particle;
    EXPECT_EQ(particle.getPos(),   Coord(0, 0, 0));
    EXPECT_EQ(particle.getSpeed(), Coord(0, 0, 0));
    // mass init with default value 
}

TEST(ParticleTest, InitBaseParameters) {
    {
    Coord pos(0.0f, 0.0f, 0.0f);
    Coord speed(0.0f, 0.0f, 0.0f);
    Particle particle(pos, speed);
    EXPECT_EQ(particle.getPos(), pos);
    EXPECT_EQ(particle.getSpeed(), speed);
    }

    {
    Coord pos(100.0f, 100.0f, 100.0f);
    Coord speed(100.0f, 100.0f, 100.0f);
    Particle particle(pos, speed);
    EXPECT_EQ(particle.getPos(), pos);
    EXPECT_EQ(particle.getSpeed(), speed);
    }

    {
    Coord pos(-100.0f, -100.0f, -100.0f);
    Coord speed(-100.0f, -100.0f, -100.0f);
    Particle particle(pos, speed);
    EXPECT_EQ(particle.getPos(), pos);
    EXPECT_EQ(particle.getSpeed(), speed);
    }
}

TEST(ParticleTest, InitMass) {
    Coord pos(0.0f, 0.0f, 0.0f);
    Coord speed(0.0f, 0.0f, 0.0f);
    {
    float mass {0.0f};
    Particle particle(pos, speed, mass);
    float initMass = particle.getMass();
    EXPECT_EQ(initMass, mass);
    }

    {
    float mass {1001.0f};
    Particle particle(pos, speed, mass);
    float initMass = particle.getMass();
    EXPECT_EQ(initMass, mass);
    }

    {
    float mass {-9999.0f};
    Particle particle(pos, speed, mass);
    float initMass = particle.getMass();
    EXPECT_EQ(initMass, mass);
    }
}

int main(int nArgs, char** vArgs) {
    ::testing::InitGoogleTest(&nArgs, vArgs);
    return RUN_ALL_TESTS();
}