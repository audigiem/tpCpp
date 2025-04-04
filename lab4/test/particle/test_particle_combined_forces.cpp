#include <gtest/gtest.h>
#include "../../include/particle.hpp"
#include "../../include/vecteur.hpp"

TEST(ParticleTest, CombinedForces) {
    Vecteur<3> position1({0.0, 0.0, 0.0});
    Vecteur<3> position2({1.0, 0.0, 0.0});
    Particle<3> particle1(1, position1, Vecteur<3>(), 5.0, "test1");
    Particle<3> particle2(2, position2, Vecteur<3>(), 10.0, "test2");

    float epsilon = 1.0;
    float sigma = 1.0;
    Vecteur<3> combinedForces = particle1.getAllForces(std::make_shared<Particle<3>>(particle2), epsilon, sigma);
    Vecteur<3> optimizedForces = particle1.optimizedGetAllForces(std::make_shared<Particle<3>>(particle2), epsilon * 24.0, sigma);

    EXPECT_NEAR(combinedForces.get(0), optimizedForces.get(0), 1e-6);
    EXPECT_NEAR(combinedForces.get(1), optimizedForces.get(1), 1e-6);
    EXPECT_NEAR(combinedForces.get(2), optimizedForces.get(2), 1e-6);
}