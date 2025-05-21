//
// Created by audigiem on 5/21/25.
//


#include "../include/VTKconverter.hpp"
#include "../include/univers.hpp"
#include "../include/particle.hpp"
#include "../include/vecteur.hpp"
#include <chrono>


int main() {
    {
        auto start = std::chrono::high_resolution_clock::now();

        ForceType forceType = ForceType::LennardJones;
        LimitConditions limitConditions = LimitConditions::Reflective;
        std::string dirName;
        switch (forceType) {
            case ForceType::LennardJones:
                std::cout << "Collision simulation with Lennard-Jones forces" << std::endl;
                dirName = "collisionLennard";
                break;
            case ForceType::Gravity:
                std::cout << "Collision simulation with Gravity forces" << std::endl;
                dirName = "collisionGravity";
                break;
            case ForceType::Both:
                std::cout << "Collision simulation with both forces" << std::endl;
                dirName = "collisionBoth";
                break;

        }

        // initialize the parameters of the simulation
        double L1 = 250;
        double L2 = 180;
        float epsilon = 1;
        float sigma = 1.0;
        double mass = 1.0;
        // v initial speed of particles in the red square
        // !!! direction of the speed, see subject !!!!
        Vecteur<2> v({0.0, -10.0});
        Vecteur<2> v2({0.0, 0.0});
        int N1 = 395;
        int N2 = 17227;
        double cutOffRadius = 2.5 * sigma;

        bool kineticEnergyControl = true;
        int freqGenerateVTKFile = 1000;
        int freqUpdateKineticEnergy = 1000;
        double targetedKineticEnergy = 0.005;
        double dt = 0.0005;
        double tEnd = 29.5;

        double gravitationalConstant = -12;



        Univers<2> univers({L1, L2}, cutOffRadius);
        // particle of the circle
        // N1 particle in a circle equidistributed, distance between particles = (2^{1/6}/sigma)
        double spacing = std::pow(2.0, 1.0 / 6.0) / sigma;
        Vecteur<2> circleCenter({L1/2, 0.7*L2});
        for (int i = 0; i < N1; i++) {
            
        }




        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Universe creation with " << N1 * N1 + N1 * N2 << " particles took " << duration.count() << " seconds." << std::endl;

        // create the VTK converter
        VTKconverter<2> vtkConverter(dirName, "simulation");

        // start the simulation
        auto startSim = std::chrono::high_resolution_clock::now();
        univers.computeAllForcesOnParticle(epsilon, sigma, forceType);
        vtkConverter.createFile();
        vtkConverter.convertToVTK(univers);
        vtkConverter.closeFile();
        // run the simulation
        int step = 0;
        for (double t = 0; t < tEnd; t += dt) {
            step ++;
            univers.update(dt, epsilon, sigma, forceType, limitConditions);
            // generate VTK file each freqGenerateVTKFile time step
            if (step % freqGenerateVTKFile == 0) {
                std::cout << "Time step: " << step << std::endl;
                std::cout << "Percentage of simulation: " << (t / tEnd) * 100 << "%" << std::endl;
                vtkConverter.createFile();
                vtkConverter.convertToVTK(univers);
                vtkConverter.closeFile();
            }
            // update the kinetic energy each freqUpdateKineticEnergy time step
            if (step % freqUpdateKineticEnergy == 0 && kineticEnergyControl) {
                std::cout << "Velocity control by updating the kinetic energy" << std::endl;
                for (const auto& particle : univers.getParticles()) {
                    particle->updateVelocityWithKineticEnergyControl(targetedKineticEnergy);
                }
            }
        }

        auto endSim = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationSim = endSim - startSim;
        std::cout << "Simulation with " << N1 * N1 + N1 * N2 << " and " << step << " time steps particles took " << durationSim.count() << " seconds." << std::endl;


    }


    return 0;
}
