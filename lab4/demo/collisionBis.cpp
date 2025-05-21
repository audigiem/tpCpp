//
// Created by audigiem on 5/21/25.
//


#include "../include/VTKconverter.hpp"
#include "../include/univers.hpp"
#include "../include/particle.hpp"
#include "../include/vecteur.hpp"
#include <chrono>
#include <random>


std::vector<Vecteur<2>> generateParticlesInDisk(
    std::size_t numberOfParticles,
    float spacing,
    const Vecteur<2>& center
) {
    std::vector<Vecteur<2>> positions;
    float radius = spacing;

    while (positions.size() < numberOfParticles) {
        positions.clear();

        int steps = static_cast<int>(std::ceil((2 * radius) / spacing));
        for (int i = -steps; i <= steps; ++i) {
            for (int j = -steps; j <= steps; ++j) {
                float x = center.get(0) + i * spacing;
                float y = center.get(1) + j * spacing;

                float dx = x - center.get(0);
                float dy = y - center.get(1);

                if (dx * dx + dy * dy <= radius * radius) {
                    positions.emplace_back(Vecteur<2>({x, y}));
                }
            }
        }

        radius += spacing / 2.0f;
    }

    if (positions.size() > numberOfParticles) {
        std::shuffle(positions.begin(), positions.end(), std::mt19937{std::random_device{}()});
        positions.resize(numberOfParticles);
    }

    return positions;
}

std::vector<Vecteur<2>> generateParticlesInRectangle(
    std::size_t numberOfParticles,
    float spacing,
    const Vecteur<2>& bottomLeftCorner,
    const Vecteur<2>& size  // width (x), height (y)
) {
    std::vector<Vecteur<2>> positions;

    int nCols = static_cast<int>(size.get(0) / spacing);
    int nRows = static_cast<int>(size.get(1) / spacing);

    for (int i = 0; i < nCols && positions.size() < numberOfParticles; ++i) {
        for (int j = 0; j < nRows && positions.size() < numberOfParticles; ++j) {
            float x = bottomLeftCorner.get(0) + i * spacing;
            float y = bottomLeftCorner.get(1) + j * spacing;
            positions.emplace_back(Vecteur<2>({x, y}));
        }
    }

    return positions;
}


int main() {
    {
        auto start = std::chrono::high_resolution_clock::now();

        ForceType forceType = ForceType::LennardJones;
        LimitConditions limitConditions = LimitConditions::Reflective;
        std::string dirName;
        switch (forceType) {
            case ForceType::LennardJones:
                std::cout << "Collision simulation with Lennard-Jones forces" << std::endl;
                dirName = "collisionLennardCircle";
                break;
            case ForceType::Gravity:
                std::cout << "Collision simulation with Gravity forces" << std::endl;
                dirName = "collisionGravityCircle";
                break;
            case ForceType::Both:
                std::cout << "Collision simulation with both forces" << std::endl;
                dirName = "collisionBothCircle";
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

        int nbParticule = 0;

        Univers<2> univers({L1, L2}, cutOffRadius);
        // particle of the circle
        // N1 particle in a circle equidistributed, distance between particles = (2^{1/6}/sigma)
        double spacing = std::pow(2.0, 1.0 / 6.0) / sigma;
        Vecteur<2> circleCenter({L1/2, 0.4*L2});
        std::vector<Vecteur<2>> positions = generateParticlesInDisk(N1, spacing, circleCenter);
        for (const auto& pos : positions) {
            Particle<2>* p = new Particle<2>(nbParticule, pos, v, mass, "circle");
            univers.addParticle(p);
            nbParticule++;
        }

        // particle of the rectangle
        // N2 particle in a rectangle equidistributed, distance between particles = (2^{1/6}/sigma)
        Vecteur<2> rectOrigin({L1 / 5.0, 0.0});         // coin bas gauche du rectangle
        Vecteur<2> rectSize({L1 * 3.0 / 5.0, 0.3 * L2}); // largeur x hauteur
        std::vector<Vecteur<2>> rectPositions = generateParticlesInRectangle(N2, spacing, rectOrigin, rectSize);

        for (const auto& pos : rectPositions) {
            Particle<2>* p = new Particle<2>(nbParticule, pos, v2, mass, "rectangle");
            univers.addParticle(p);
            nbParticule++;
        }



        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Universe creation with " << N1 * N1 + N1 * N2 << " particles took " << duration.count() << " seconds." << std::endl;

        // create the VTK converter
        VTKconverter<2> vtkConverter(dirName, "simulation");

        // start the simulation
        auto startSim = std::chrono::high_resolution_clock::now();
        univers.computeAllForcesOnParticleANDGravitationalPotential(epsilon, sigma, forceType, gravitationalConstant);
        vtkConverter.createFile();
        vtkConverter.convertToVTK(univers);
        vtkConverter.closeFile();
        // run the simulation
        int step = 0;
        for (double t = 0; t < tEnd; t += dt) {
            step ++;
            univers.updateWithGravitationalPotential(dt, epsilon, sigma, forceType, limitConditions, gravitationalConstant);
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
                univers.updateKineticEnergy(targetedKineticEnergy);
            }
        }

        auto endSim = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationSim = endSim - startSim;
        std::cout << "Simulation with " << N1 + N2 << " and " << step << " time steps particles took " << durationSim.count() << " seconds." << std::endl;


    }


    return 0;
}
