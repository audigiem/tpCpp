//
// Created by matteo on 18/05/25.
//


/**
 * test file to check if adding a Huge number of particles in the universe is working
 * We will create a universe in [0,1]^3 with (2^k)^3 particles for k = 3,4,5,6,7
*/

#include "../include/univers.hpp"
#include "../include/particle.hpp"
#include "../include/vecteur.hpp"
#include <chrono>

int main() {

    // add (2^k)^3 particles efficiently
    for (int exp=3; exp <= 7; ++exp) {
        auto start = std::chrono::high_resolution_clock::now();

        double L1 = 1;
        double L2 = 1;
        double L3 = 1;
        double cutOffRadius = 0.1;
        Univers<3> univers({L1, L2, L3}, cutOffRadius);

        int N = std::pow(2, exp);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    Vecteur<3> position({static_cast<double>(i)/N, static_cast<double>(j)/N, static_cast<double>(k)/N});
                    Particle<3>* particle = new Particle<3>(i*N*N + j*N + k, position, Vecteur<3>({0, 0, 0}), 1.0, "default");
                    try {
                        univers.addParticle(particle);
                    } catch (const std::runtime_error& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                        // stop the simulation or handle the error, return exit(1);
                        exit(1);
                    }
                }
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time taken to add " << N*N*N << " particles: " << elapsed.count() << " seconds" << std::endl;
        
    }

    return 0;
}