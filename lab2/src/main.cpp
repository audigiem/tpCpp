//
// Created by audigiem on 13/02/25.
//

#include "particle.h"
#include "particleCollection.h"
#include <chrono>
#include <cmath>


int main() {
//    std::list<int> collectionSizes = {64, 128, 256, 512, 1024, 2048, 4096, 8192};
//
//    std::list<particleCollection> particleCollections;
//    for (int size : collectionSizes) {
//        particleCollections.push_back(particleCollection(size));
//    }
//
//    for (particleCollection pc : particleCollections) {
//        pc.compareIteration();
//        pc.compareInsertion();
//    }


    double position0[3] = {0, 0, 0};
    double velocity0[3] = {0, 0, 0};
    double position1[3] = {0, 1, 0};
    double velocity1[3] = {-1, 0, 0};
    double position2[3] = {0, 5.36, 0};
    double velocity2[3] = {-0.425, 0, 0};
    double position3[3] = {34.75, 0, 0};
    double velocity3[3] = {0, 0.0296, 0};

    particle soleil = particle(position0, velocity0, 1, 0, 0);
    particle terre = particle(position1, velocity1, 3*pow(10, -6), 1, 1);
    particle jupiter = particle(position2, velocity2, 9.55*pow(10, -4), 2, 2);
    particle haley = particle(position3, velocity3, 1*pow(10, -14), 3, 3);

    std::vector<particle> particles = {soleil, terre, jupiter, haley};
    particleCollection pc = particleCollection(particles);
    pc.stromerVerlet(0.015, 468.5);

    return 0;
}