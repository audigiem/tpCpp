//
// Created by matteo on 19/03/25.
//

#include "../include/univers.hpp"
#include "../include/cell.hpp"
#include <iostream>

int main() {
    // initialize the parameters of the simulation
    double L1 = 250;
    double L2 = 40;
    float epsilon = 5.0;
    float sigma = 1.0;
    double mass = 1.0;
    // v initial speed of particles in the red square
    // !!! direction of the speed, see subject !!!!
    Vecteur<2> v({0.0, -10.0});
    Vecteur<2> v2({0.0, 0.0});
    int N1 = 4;
    int N2 = 16;
    double cutOffRadius = 2.5 * sigma;
    double dt = 0.005;
    double tEnd = 1.95;

    // To prevent memory leaks i didnt succeed to delete the particles
    // with the destructor of the univers
    std::vector<Particle<2>*> particles;

    Univers<2> univers({L1, L2}, cutOffRadius);
    // particle of the red square:
    // 40x40 particles equidistributed, distance between particles = (2^{1/6}/sigma)
    // double spacing = std::pow(2.0, 1.0 / 6.0) / sigma;
    double spacing = 0.25;
    double squareLength = N1*spacing;
    double rectangleLength = N2*spacing;
    std::array<double, 2> offset = {(L1 - squareLength)/2, (L2 - squareLength) - L2/3};
    // std::cout << "offset: " << offset[0] << ", " << offset[1] << std::endl;
    int id = 0;
    for (int i = 0; i < N1; ++i) {
        for (int j = 0; j < N1; ++j) {
            Vecteur<2> position({offset[0] + i * spacing, offset[1] + j * spacing});
            // std::cout << "position: " << position << std::endl;
            Particle<2>* particle = new Particle<2>(id++, position, v, mass, "red");
            univers.addParticle(particle);
            particles.push_back(particle);

        }
    }

    // particle of the blue rectangle:
    // 160x40 particles equidistributed, distance between particles = (2^{1/6}/sigma)
    std::array<double, 2> offset2 = {(L1 - rectangleLength)/2, L2/10};

    for (int i = 0; i < N2; ++i) {
        for (int j = 0; j < N1; ++j) {
            Vecteur<2> position({offset2[0] + i * spacing, offset2[1] + j * spacing});
            Particle<2>* particle = new Particle<2>(id++, position, v2, mass, "blue");
            univers.addParticle(particle);
            particles.push_back(particle);
        }
    }

    univers.showUnivers();
    univers.showAllNeighbourhoods();

    return 0;
}