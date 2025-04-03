#include <gtest/gtest.h>
#include "../../include/cell.hpp"
#include "../../include/particle.hpp"

TEST(CellTest, AddParticle) {
    Cell<3> cell;

    Vecteur<3> position({1.0, 2.0, 3.0});
    Vecteur<3> velocity({0.1, 0.2, 0.3});
    Particle<3> particle(1, position, velocity, 5.0, "test");

    cell.addParticle(std::make_shared<Particle<3>>(particle));

    auto particles = cell.getParticles();
    ASSERT_EQ(particles.size(), 1);
    EXPECT_EQ(particles.front()->getId(), 1);
    EXPECT_EQ(particles.front()->getPosition(), position);
    EXPECT_EQ(particles.front()->getVelocity(), velocity);
    EXPECT_DOUBLE_EQ(particles.front()->getMass(), 5.0);
}