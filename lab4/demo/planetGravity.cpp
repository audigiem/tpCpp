//
// Created by matteo on 17/05/25.
//

#include "../include/VTKconverter.hpp"
#include "../include/univers.hpp"
#include "../include/particle.hpp"
#include "../include/vecteur.hpp"
#include <chrono>

int main() {

    auto start = std::chrono::high_resolution_clock::now();
    // initialize the parameters of the simulation
    double L1 = 10000;
    double L2 = 10000;
    double cutOffRadius = 10000;
    Univers<2> univers({L1, L2}, cutOffRadius);
    double dt = 0.15;
    double tEnd = 468.5;

    int freqGenerateVTKFile = 100;

    std::vector<Particle<2>*> particles;
    // initialize the planets
    Particle<2>* sun = new Particle<2>(0, Vecteur<2>({5000,5000}), Vecteur<2>({0.0, 0.0}), 1.0, "sun");
    Particle<2>* earth = new Particle<2>(1, Vecteur<2>({5000,5001}), Vecteur<2>({-1,0}), 0.000003, "earth");
    Particle<2>* jupiter = new Particle<2>(2, Vecteur<2>({5000,5005.36}), Vecteur<2>({-0.425,0}), 0.000955, "jupiter");
    Particle<2>* halley = new Particle<2>(3, Vecteur<2>({5034.75, 5000}), Vecteur<2>({0, 0.296}), 0.00000000000001, "halley");

    particles.push_back(sun);
    particles.push_back(earth);
    particles.push_back(jupiter);
    particles.push_back(halley);
    univers.addParticle(sun);
    univers.addParticle(earth);
    univers.addParticle(jupiter);
    univers.addParticle(halley);
    // initialize the VTK converter
    VTKconverter<2> vtk("planetGravity", "planetGravity");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken to initialize: " << duration.count() << " milliseconds" << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    univers.computeAllForcesOnParticle(1.0, 1.0);
    vtk.createFile();
    vtk.convertToVTK(univers);
    vtk.closeFile();

    int step = 0;
    for (double t = 0; t < tEnd; t += dt) {
        univers.update(dt, 1.0, 1.0);
        if (step % freqGenerateVTKFile == 0) {
            std::cout << "Time step: " << step << std::endl;
            univers.computeAllForcesOnParticle(1.0, 1.0);
            vtk.createFile();
            vtk.convertToVTK(univers);
            vtk.closeFile();
        }
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
    std::cout << "Time taken to run the simulation: " << duration2.count() << " milliseconds" << std::endl;
    std::cout << "Number of time steps: " << step << std::endl;

    return 0;
}