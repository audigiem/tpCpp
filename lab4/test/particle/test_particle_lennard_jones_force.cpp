#include <gtest/gtest.h>
#include "../../include/particle.hpp"
#include "../../include/vecteur.hpp"

TEST(ParticleTest, LennardJonesForce) {
    Vecteur<3> position1({0.0, 0.0, 0.0});
    Vecteur<3> position2({1.0, 0.0, 0.0});
    Particle<3> particle1(1, position1, Vecteur<3>(), 5.0, "test1");
    Particle<3> particle2(2, position2, Vecteur<3>(), 10.0, "test2");

    float epsilon = 1.0;
    float sigma = 1.0;
    Vecteur<3> force = particle1.getLennardJonesForce(particle2, epsilon, sigma);

    // Check that the force is computed correctly (values depend on epsilon and sigma)
    EXPECT_NEAR(force.get(0), -23.0, 1.0); // Example value
    EXPECT_NEAR(force.get(1), 0.0, 1e-6);
    EXPECT_NEAR(force.get(2), 0.0, 1e-6);
}