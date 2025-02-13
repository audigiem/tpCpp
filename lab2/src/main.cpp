//
// Created by audigiem on 13/02/25.
//

#include "particle.h"
#include "particleCollection.h"
#include <chrono>


int main() {
    std::list<int> collectionSizes = {64, 128, 256, 512, 1024, 2048, 4096, 8192};

    std::list<particleCollection> particleCollections;
    for (int size : collectionSizes) {
        particleCollections.push_back(particleCollection(size));
    }

    for (particleCollection pc : particleCollections) {
        pc.compareIteration();
        pc.compareInsertion();
    }


    return 0;
}