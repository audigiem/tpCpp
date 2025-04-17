#include <gtest/gtest.h>
#include "../../include/particle.hpp"
#include "../../include/vecteur.hpp"

TEST(ParticleTest, GravityForce) {
    Vecteur<3> position1({0.0, 0.0, 0.0});
    Vecteur<3> position2({1.0, 0.0, 0.0});
    Particle<3>* particle1 = new Particle<3>(1, position1, Vecteur<3>(), 5.0, "test1");
    Particle<3>* particle2 = new Particle<3>(2, position2, Vecteur<3>(), 10.0, "test2");

    Vecteur<3> expectedForce({50.0, 0.0, 0.0}); // F = G * m1 * m2 / r^2
    EXPECT_EQ(particle1->getGravityForce(particle2), expectedForce);
}