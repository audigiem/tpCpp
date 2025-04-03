#include <gtest/gtest.h>
#include "../../include/cell.hpp"
#include "../../include/particle.hpp"

TEST(CellTest, IsEmpty) {
    Cell<3> cell;

    EXPECT_TRUE(cell.isEmpty()); // Cell should be empty initially

    Vecteur<3> position({1.0, 2.0, 3.0});
    Vecteur<3> velocity({0.1, 0.2, 0.3});
    Particle<3> particle(1, position, velocity, 5.0, "test");

    cell.addParticle(std::make_shared<Particle<3>>(particle));

    EXPECT_FALSE(cell.isEmpty()); // Cell should not be empty after adding a particle
}