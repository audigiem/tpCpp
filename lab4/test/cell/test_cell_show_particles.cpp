#include <gtest/gtest.h>
#include "../../include/cell.hpp"
#include "../../include/particle.hpp"
#include <sstream>

TEST(CellTest, ShowParticles) {
    Cell<3> cell({0, 0, 0}, {4, 4, 4}, 10.0);

    Vecteur<3> position({1.0, 2.0, 3.0});
    Vecteur<3> velocity({0.1, 0.2, 0.3});
    Particle<3>* particle = new Particle<3>(1, position, velocity, 5.0, "test");

    cell.addParticle(particle);

    std::ostringstream output;
    std::streambuf* oldCoutBuffer = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout

    cell.showParticles();

    std::cout.rdbuf(oldCoutBuffer); // Restore std::cout

    std::ostringstream expected;
    expected << "----------------------------------------\n";
    expected << "Cell at index: [0, 0, 0]\n";
    expected << "Neighbouring cell indices:\n  [0, 0, 0]\n  [0, 0, 1]\n  [0, 1, 0]\n  [0, 1, 1]\n  [1, 0, 0]\n  [1, 0, 1]\n  [1, 1, 0]\n  [1, 1, 1]\n";
    expected << "Particles in this cell (1):\n";
    expected << "  - Particle ID: 1\n";
    expected << "      - Position: (1, 2, 3)\n";
    expected << "      - Velocity: (0.1, 0.2, 0.3)\n";
    expected << "      - Mass: 5\n";
    expected << "      - Force: (0, 0, 0)\n";
    expected << "----------------------------------------\n";

    EXPECT_EQ(output.str(), expected.str());

    delete particle;
}
