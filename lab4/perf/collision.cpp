//
// Created by matteo on 17/05/25.
//

#include "../include/VTKconverter.hpp"
#include "../include/univers.hpp"
#include "../include/particle.hpp"
#include "../include/vecteur.hpp"
#include <chrono>
#include <string>
#include <cstdlib>
#include <iostream>

void print_usage() {
    std::cout << "Usage: collision [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --force=TYPE       Force type (LennardJones, Gravity, Both). Default: Both" << std::endl;
    std::cout << "  --freq=N           Frequency to generate VTK files. Default: 100" << std::endl;
    std::cout << "  --dt=VALUE         Time step. Default: 0.0005" << std::endl;
    std::cout << "  --cutoff=VALUE     Cutoff radius. Default: 2.5*sigma" << std::endl;
    std::cout << "  --help             Display this help message" << std::endl;
}

int main(int argc, char* argv[]) {
    // Default values
    ForceType forceType = ForceType::Both;
    int freqGenerateVTKFile = 100;
    double dt = 0.005;
    float sigma = 1.0;
    double cutOffRadius = 2.5 * sigma;
    
    // Parse command-line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        
        // Help option
        if(arg == "--help" || arg == "-h") {
            print_usage();
            return 0;
        }
        // Force type
        else if (arg.substr(0, 8) == "--force=") {
            std::string type = arg.substr(8);
            if (type == "LennardJones") {
                forceType = ForceType::LennardJones;
            } else if (type == "Gravity") {
                forceType = ForceType::Gravity;
            } else if (type == "Both") {
                forceType = ForceType::Both;
            } else {
                std::cerr << "Invalid force type: " << type << std::endl;
                print_usage();
                return 1;
            }
        }
        // Frequency for VTK generation
        else if (arg.substr(0, 7) == "--freq=") {
            try {
                freqGenerateVTKFile = std::stoi(arg.substr(7));
                if (freqGenerateVTKFile <= 0) {
                    throw std::invalid_argument("Frequency must be positive");
                }
            } catch (const std::exception& e) {
                std::cerr << "Invalid frequency value: " << arg.substr(7) << std::endl;
                print_usage();
                return 1;
            }
        }
        // Time step
        else if (arg.substr(0, 5) == "--dt=") {
            try {
                dt = std::stod(arg.substr(5));
                if (dt <= 0) {
                    throw std::invalid_argument("Time step must be positive");
                }
            } catch (const std::exception& e) {
                std::cerr << "Invalid time step value: " << arg.substr(5) << std::endl;
                print_usage();
                return 1;
            }
        }
        // Cutoff radius
        else if (arg.substr(0, 9) == "--cutoff=") {
            try {
                cutOffRadius = std::stod(arg.substr(9));
                if (cutOffRadius <= 0) {
                    throw std::invalid_argument("Cutoff radius must be positive");
                }
            } catch (const std::exception& e) {
                std::cerr << "Invalid cutoff radius value: " << arg.substr(9) << std::endl;
                print_usage();
                return 1;
            }
        }
        else {
            std::cerr << "Unknown option: " << arg << std::endl;
            print_usage();
            return 1;
        }
    }
    
    {
        auto start = std::chrono::high_resolution_clock::now();

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
 
        bool kineticEnergyControl = false;
        int freqUpdateKineticEnergy = 1000;
        double targetedKineticEnergy = 0.005;
        double tEnd = 19.5;

        // Print the parameters being used
        std::cout << "Simulation parameters:" << std::endl;
        std::cout << "  Force type: " << (forceType == ForceType::LennardJones ? "LennardJones" : 
                                         (forceType == ForceType::Gravity ? "Gravity" : "Both")) << std::endl;
        std::cout << "  VTK generation frequency: " << freqGenerateVTKFile << std::endl;
        std::cout << "  Time step (dt): " << dt << std::endl;
        std::cout << "  Cutoff radius: " << cutOffRadius << std::endl;

        // initialize the parameters of the simulation
        double L1 = 250;
        double L2 = 150;
        float epsilon = 5.0;
        double mass = 1.0;
        // v initial speed of particles in the red square
        // !!! direction of the speed, see subject !!!!
        Vecteur<2> v({0.0, -10.0});
        Vecteur<2> v2({0.0, 0.0});
        int N1 = 40; //40
        int N2 = 160; //160

        Univers<2> univers({L1, L2}, cutOffRadius);
        // particle of the red square:
        // 40x40 particles equidistributed, distance between particles = (2^{1/6}/sigma)
        double spacing = std::pow(2.0, 1.0 / 6.0) / sigma;
        double squareLength = N1*spacing;
        double rectangleLength = N2*spacing;
        std::array<double, 2> offset = {(L1 - squareLength)/2, (L2 - 1.1*squareLength)};
        int id = 0;
        for (int i = 0; i < N1; ++i) {
            for (int j = 0; j < N1; ++j) {
                Vecteur<2> position({offset[0] + i * spacing, offset[1] + j * spacing});
                // std::cout << "position: " << position << std::endl;
                Particle<2>* particle = new Particle<2>(id++, position, v, mass, "red");
                try {
                    univers.addParticle(particle);
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    // stop the simulation or handle the error, return exit(1);
                    exit(1);
                }

            }
        }

        // particle of the blue rectangle:
        // 160x40 particles equidistributed, distance between particles = (2^{1/6}/sigma)
        std::array<double, 2> offset2 = {(L1 - rectangleLength)/2, L2 - 2.2*squareLength};

        for (int i = 0; i < N2; ++i) {
            for (int j = 0; j < N1; ++j) {
                Vecteur<2> position({offset2[0] + i * spacing, offset2[1] + j * spacing});
                Particle<2>* particle = new Particle<2>(id++, position, v2, mass, "blue");
                try {
                    univers.addParticle(particle);
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    // stop the simulation or handle the error, return exit(1);
                    exit(1);
                }
            }
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
