#include <gtest/gtest.h>
#include "../../include/univers.hpp"
#include "../../include/particle.hpp"

TEST(UniversTest, Update) {
    Univers<3> univers({100.0, 100.0, 100.0}, 10.0);

    Vecteur<3> position1({5.0, 5.0, 5.0});
    Vecteur<3> position2({15.0, 5.0, 5.0});
    Particle<3>* particle1 = new Particle<3>(1, position1, Vecteur<3>(), 1.0, "test1");
    Particle<3>* particle2 = new Particle<3>(2, position2, Vecteur<3>(), 1.0, "test2");

    univers.addParticle(particle1);
    univers.addParticle(particle2);

    univers.update(0.1, 5.0, 1.0, ForceType::LennardJones, LimitConditions::Reflective);

    auto cell1 = univers.getCell({0, 0, 0});
    auto cell2 = univers.getCell({1, 0, 0});

    ASSERT_NE(cell1, nullptr);
    ASSERT_NE(cell2, nullptr);

    EXPECT_EQ(cell1->getParticles().size(), 1);
    EXPECT_EQ(cell2->getParticles().size(), 1);
}