#include <gtest/gtest.h>
#include "../../include/cell.hpp"
#include "../../include/particle.hpp"

TEST(CellTest, GetParticles) {
    Cell<3> cell;

    Vecteur<3> position1({1.0, 2.0, 3.0});
    Vecteur<3> velocity1({0.1, 0.2, 0.3});
    Particle<3>* particle1 = new Particle<3>(1, position1, velocity1, 5.0, "test1");

    Vecteur<3> position2({4.0, 5.0, 6.0});
    Vecteur<3> velocity2({0.4, 0.5, 0.6});
    Particle<3>* particle2 = new Particle<3>(2, position2, velocity2, 10.0, "test2");

    cell.addParticle(particle1);
    cell.addParticle(particle2);

    auto particles = cell.getParticles();
    ASSERT_EQ(particles.size(), 2);

    EXPECT_EQ(particles.front()->getId(), 1);
    EXPECT_EQ(particles.back()->getId(), 2);
    EXPECT_EQ(particles.front()->getPosition(), position1);
    EXPECT_EQ(particles.back()->getPosition(), position2);
}