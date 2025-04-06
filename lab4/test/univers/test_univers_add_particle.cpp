#include <gtest/gtest.h>
#include "../../include/univers.hpp"
#include "../../include/particle.hpp"

TEST(UniversTest, AddParticle) {
    Univers<3> univers({100, 100, 100}, 10.0);

    Vecteur<3> position({5.0, 5.0, 5.0});
    Particle<3> particle(1, position, Vecteur<3>(), 1.0, "test");

    univers.addParticle(std::make_shared<Particle<3>>(particle));

    auto cellIndex = std::array<int, 3>{0, 0, 0};
    auto cell = univers.getCell(cellIndex);

    ASSERT_NE(cell, nullptr);
    EXPECT_EQ(cell->getParticles().size(), 1);
    EXPECT_EQ(cell->getParticles().front()->getId(), 1);
}