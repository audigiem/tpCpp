//
// Created by matteo on 06/04/25.
//
#include "../include/VTKconverter.hpp"
#include "../include/univers.hpp"
#include "../include/particle.hpp"
#include "../include/vecteur.hpp"
#include <chrono>



int main() {
    {
        auto start = std::chrono::high_resolution_clock::now();

        // initialize the parameters of the simulation
        double L1 = 250;
        double L2 = 40;
        float epsilon = 5.0;
        float sigma = 2.0;
        double mass = 1.0;
        // v initial speed of particles in the red square
        // !!! direction of the speed, see subject !!!!
        Vecteur<2> v({0.0, -10.0});
        Vecteur<2> v2({0.0, 0.0});
        int N1 = 40;
        int N2 = 160;
        double cutOffRadius = 2.5 * sigma;
        double dt = 0.00005;
        double tEnd = 19.5;

        // To prevent memory leaks i didnt succeed to delete the particles
        // with the destructor of the univers
        std::vector<Particle<2>*> particles;

        Univers<2> univers({L1, L2}, cutOffRadius);
        // particle of the red square:
        // 40x40 particles equidistributed, distance between particles = (2^{1/6}/sigma)
        double spacing = std::pow(2.0, 1.0 / 6.0) / sigma;
        std::array<double, 2> offset = {L1/3, L2 - (N1 * spacing)};
        // std::cout << "offset: " << offset[0] << ", " << offset[1] << std::endl;
        int id = 0;
        for (int i = 0; i < N1; ++i) {
            for (int j = 0; j < N1; ++j) {
                Vecteur<2> position({(i+offset[0]) * spacing, (j + offset[1]) * spacing});
                // std::cout << "position: " << position << std::endl;
                Particle<2>* particle = new Particle<2>(id++, position, v, mass, "red");
                univers.addParticle(particle);
                particles.push_back(particle);

            }
        }

        // particle of the blue rectangle:
        // 160x40 particles equidistributed, distance between particles = (2^{1/6}/sigma)
        std::array<double, 2> offset2 = {L1/6, L2/6};

        for (int i = 0; i < N2; ++i) {
            for (int j = 0; j < N1; ++j) {
                Vecteur<2> position({(i+offset2[0]) * spacing, (j + offset2[1]) * spacing});
                Particle<2>* particle = new Particle<2>(id++, position, v2, mass, "blue");
                univers.addParticle(particle);
                particles.push_back(particle);
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Universe creation with " << N1 * N1 + N1 * N2 << " particles took " << duration.count() << " seconds." << std::endl;

        // create the VTK converter
        // VTKconverter<2> vtkConverter("collision", "simulation");

        // start the simulation
        auto startSim = std::chrono::high_resolution_clock::now();
        univers.computeAllForcesOnParticle(epsilon, sigma);
        // vtkConverter.createFile();
        // vtkConverter.convertToVTK(univers);
        // vtkConverter.closeFile();
        // run the simulation
        for (double t = 0; t < tEnd; t += dt) {
            univers.update(dt, epsilon, sigma);
            // vtkConverter.createFile();
            // vtkConverter.convertToVTK(univers);
            // vtkConverter.closeFile();
        }

        auto endSim = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationSim = endSim - startSim;
        int nbTimeSteps = static_cast<int>(tEnd / dt);
        std::cout << "Simulation with " << N1 * N1 + N1 * N2 << " and " << nbTimeSteps << " time steps particles took " << durationSim.count() << " seconds." << std::endl;

        for (Particle<2>* particle : particles) {
            delete particle;
        }
        particles.clear();
        for (auto& cell : univers.getCells()) {
            delete cell.second;
        }

    }


    return 0;
}
