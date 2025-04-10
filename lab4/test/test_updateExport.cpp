//
// Created by matteo on 03/04/25.
//

#include <iostream>
#include <chrono>
#include "../include/univers.hpp"
#include "../include/particle.hpp"
#include "../include/vecteur.hpp"
#include "../include/VTKconverter.hpp"
#include <fstream>

void runSimulation(int numParticles, VTKconverter<3>& vtkConverter) {
    // Create the universe and show the time to create it
    auto start = std::chrono::high_resolution_clock::now();
    const double spacing = 0.001;
    std::array<double, 3> caracteristicLength = {1.0, 1.0, 1.0};
    double cutOffRadius = 0.5;
    float epsilon = 1.0;
    float sigma = 1.0;
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
                univers.addParticle(std::make_shared<Particle<3>>(particle));
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    // std::cout << "Universe creation with " << numParticles << " particles took " << duration.count() << " seconds." << std::endl;

    // Run the simulation
    auto startSim = std::chrono::high_resolution_clock::now();
    univers.computeAllForcesOnParticle(epsilon, sigma);
    //univers.showUnivers();
    for (int i = 0; i < 10; ++i) {
        univers.update(0.01, epsilon, sigma);
        // create a file for the VTK converter
        vtkConverter.createFile();
        vtkConverter.convertToVTK(univers);
        vtkConverter.closeFile();
        // std::cout << "Outiside Position particle 1: " << univers.getParticles().front()->getPosition() << std::endl;
        // std::cout << std::endl;
    }
   // univers.showUnivers();
    auto endSim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationSim = endSim - startSim;
    // std::cout << "Simulation with " << numParticles << " particles took " << durationSim.count() << " seconds." << std::endl;
    // std::cout << std::endl;
}

int main() {
    // std::cout << "Simulation parameters: 100 time steps, 0.01 time step size" << std::endl;

    for (int k = 2; k < 8; ++k) {
        int numParticles = std::pow(2, k);
        // create a VTK converter
        VTKconverter<3> vtkConverter("testUnivers2_"+std::to_string(numParticles), "test");
        runSimulation(numParticles, vtkConverter);

    }


    return 0;
}
