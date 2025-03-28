#include <iostream>
#include <chrono>
#include "../include/univers.hpp"
#include "../include/particle.hpp"
#include "../include/vecteur.hpp"

void runSimulation(int numParticles) {
    const double spacing = 1.0 / (std::cbrt(numParticles) - 1);
    double caracteristicLength = 1.0;
    double cutOffRadius = 0.1;
    Univers<3> univers(caracteristicLength, cutOffRadius);

    int id = 0;
    int numParticlesPerDimension = std::cbrt(numParticles);
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

    // Run the simulation
    for (int i = 0; i < 100; ++i) {
        univers.update(0.01);
    }
}

int main() {
    std::cout << "Simulation parameters: 100 time steps, 0.01 time step size" << std::endl;
    for (int k = 3; k < 10; ++k) {
        int numParticles = std::pow(2, k);
        auto start = std::chrono::high_resolution_clock::now();
        runSimulation(numParticles);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Simulation with " << numParticles << " particles took " << duration.count() << " seconds." << std::endl;
    }

    return 0;
}