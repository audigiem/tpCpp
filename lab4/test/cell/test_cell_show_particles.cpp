#include <gtest/gtest.h>
#include "../../include/cell.hpp"
#include "../../include/particle.hpp"
#include <sstream>

TEST(CellTest, ShowParticles) {
    Cell<3> cell;

    Vecteur<3> position({1.0, 2.0, 3.0});
    Vecteur<3> velocity({0.1, 0.2, 0.3});
    Particle<3> particle(1, position, velocity, 5.0, "test");

    cell.addParticle(std::make_shared<Particle<3>>(particle));

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout

    cell.showParticles();

    std::cout.rdbuf(oldCoutBuffer); // Restore std::cout

    std::string expectedOutput = "Particles in this cell:\nParticle ID: 1, Position: (1, 2, 3)\n";
    EXPECT_EQ(output.str(), expectedOutput);
}