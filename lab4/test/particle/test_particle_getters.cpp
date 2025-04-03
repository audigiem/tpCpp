#include <gtest/gtest.h>
#include "../../include/particle.hpp"
#include "../../include/vecteur.hpp"

TEST(ParticleTest, Getters) {
    Vecteur<3> position({1.0, 2.0, 3.0});
    Vecteur<3> velocity({0.1, 0.2, 0.3});
    Particle<3> particle(1, position, velocity, 5.0, "test");

    EXPECT_EQ(particle.getId(), 1);
    EXPECT_EQ(particle.getPosition(), position);
    EXPECT_EQ(particle.getVelocity(), velocity);
    EXPECT_DOUBLE_EQ(particle.getMass(), 5.0);
    EXPECT_EQ(particle.getCategory(), "test");
}