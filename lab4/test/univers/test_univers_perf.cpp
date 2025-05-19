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
    const double spacing = 1.0 / (std::cbrt(numParticles) - 1);
    std::array<double, 3> caracteristicLength = {1.0, 1.0, 1.0};
    double cutOffRadius = 0.1;
    Univers<3> univers(caracteristicLength, cutOffRadius);

    std::cout << "Strating to fill the universe with " << numParticles << " particles..." << std::endl;
    int id = 0;
    int numParticlesPerDimension = std::cbrt(numParticles);
    for (int i = 0; i < numParticlesPerDimension; ++i) {
        for (int j = 0; j < numParticlesPerDimension; ++j) {
            for (int k = 0; k < numParticlesPerDimension; ++k) {
                Vecteur<3> position({i * spacing, j * spacing, k * spacing});
                Vecteur<3> velocity({0.0, 0.0, 0.0});
                double mass = 1.0;
                std::string category = "default";
                Particle<3>* particle = new Particle<3>(id++, position, velocity, mass, category);
                univers.addParticle(particle);
            }
        }
    }

    std::cout << "Starting simulation with " << numParticles << " particles..." << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Universe creation with " << numParticles << " particles took " << duration.count() << " seconds." << std::endl;

    // Run the simulation
    auto startSim = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i) {
        univers.update(0.01, 1.0, 1.0);
        // create a file for the VTK converter
        vtkConverter.createFile();
        vtkConverter.convertToVTK(univers);
        vtkConverter.closeFile();
    }
    auto endSim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationSim = endSim - startSim;
    std::cout << "Simulation with " << numParticles << " particles took " << durationSim.count() << " seconds." << std::endl;
    std::cout << std::endl;



}

int main() {
    std::cout << "Simulation parameters: 100 time steps, 0.01 time step size" << std::endl;


    for (int k = 3; k < 15; ++k) {
        int numParticles = std::pow(2, k);
        // create a VTK converter
        VTKconverter<3> vtkConverter("testUnivers2_"+std::to_string(numParticles), "test");
        runSimulation(numParticles, vtkConverter);
        // detruire le VTK converter
        vtkConverter.~VTKconverter();

    }


    return 0;
}