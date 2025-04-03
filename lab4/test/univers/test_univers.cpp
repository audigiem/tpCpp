#include <iostream>
#include "../include/univers.hpp"
#include "../include/particle.hpp"
#include "../include/vecteur.hpp"

int main() {
    const int numParticlesPerDimension = 4;
    const double spacing = 1.0 / (numParticlesPerDimension - 1);
    double caracteristicLength = 1.0;
    double cutOffRadius = 0.1;
    Univers<3> univers(caracteristicLength, cutOffRadius);

    int id = 0;
    for (int i = 0; i < numParticlesPerDimension; ++i) {
        for (int j = 0; j < numParticlesPerDimension; ++j) {
            for (int k = 0; k < numParticlesPerDimension; ++k) {
                Vecteur<3> position({i * spacing, j * spacing, k * spacing});
                Vecteur<3> velocity({0.0, 0.0, 0.0});
                double mass = 1.0;
                std::string category = "default";
                Particle<3> particle(id++, position, velocity, mass, category);
                univers.addParticle(particle);
            }
        }
    }

    univers.showUnivers();

    return 0;
}

    