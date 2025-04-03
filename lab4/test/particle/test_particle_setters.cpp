#include <gtest/gtest.h>
#include "../../include/particle.hpp"
#include "../../include/vecteur.hpp"

TEST(ParticleTest, Setters) {
    Vecteur<3> position({1.0, 2.0, 3.0});
    Vecteur<3> velocity({0.1, 0.2, 0.3});
    Particle<3> particle(1, position, velocity, 5.0, "test");

    Vecteur<3> newPosition({4.0, 5.0, 6.0});
    Vecteur<3> newVelocity({0.4, 0.5, 0.6});
    particle.setPosition(newPosition);
    particle.setVelocity(newVelocity);

    EXPECT_EQ(particle.getPosition(), newPosition);
    EXPECT_EQ(particle.getVelocity(), newVelocity);
}