//
// Created by audigiem on 13/02/25.
//

#include "particle.h"
#include "particleCollection.h"
#include<set>
#include<list>
#include<deque>
#include<vector>
#include <chrono>
#include <iostream>
#include <cmath>



particleCollection::particleCollection(int nbElem) {
    for (int i = 0; i < nbElem; i++) {
        particle p = particle();
        p.set_id(particleVector.size());
        this->particleList.push_back(p);
        this->particleDeque.push_back(p);
        this->particleVector.push_back(p);
        // this->particleSet.insert(p);
    }
}

particleCollection::~particleCollection() {
        particleDeque.clear();
        particleList.clear();
        particleVector.clear();
        // particleSet.clear();

}

//std::set<particle> particleCollection::get_particleSet() {
//    return this->particleSet;
//}

std::list<particle> particleCollection::get_particleList() {
    return this->particleList;
}

std::deque<particle> particleCollection::get_particleDeque() {
    return this->particleDeque;
}

std::vector<particle> particleCollection::get_particleVector() {
    return this->particleVector;
}

void particleCollection::compareIteration() {
    auto start = std::chrono::steady_clock::now();
    for (particle p : this->particleList) {
        // do nothing
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "Time to iterate over a list: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;

    start = std::chrono::steady_clock::now();
    for (particle p : this->particleDeque) {
        // do nothing
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Time to iterate over a deque: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;

    start = std::chrono::steady_clock::now();
    for (particle p : this->particleVector) {
        // do nothing
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Time to iterate over a vector: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;

}

void particleCollection::compareInsertion() {
    // lets make a copy of each container
    std::list<particle> particleListCopy = this->particleList;
    std::deque<particle> particleDequeCopy = this->particleDeque;
    std::vector<particle> particleVectorCopy = this->particleVector;

    auto start = std::chrono::steady_clock::now();
    particleListCopy.push_back(particle());
    auto end = std::chrono::steady_clock::now();
    std::cout << "Time to insert at the end of a list: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;

    start = std::chrono::steady_clock::now();
    particleDequeCopy.push_back(particle());
    end = std::chrono::steady_clock::now();
    std::cout << "Time to insert at the end of a deque: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;

    start = std::chrono::steady_clock::now();
    particleVectorCopy.push_back(particle());
    end = std::chrono::steady_clock::now();
    std::cout << "Time to insert at the end of a vector: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << " ns" << std::endl;
}

void particleCollection::computeForce() {
    for (particle p : this->particleVector) {
        double forceVector[3] = {0, 0, 0};
        for (particle p1 : this->particleVector) {
            if (p.get_id() != p1.get_id()) {
                double* pos1 = p.get_position();
                double* pos2 = p1.get_position();
                double distance = sqrt(pow(pos1[0] - pos2[0], 2) + pow(pos1[1] - pos2[1], 2) + pow(pos1[2] - pos2[2], 2));
                double force = 1 / pow(distance, 2);
                forceVector[0] += force * (pos1[0] - pos2[0]) / distance;
                forceVector[1] += force * (pos1[1] - pos2[1]) / distance;
                forceVector[2] += force * (pos1[2] - pos2[2]) / distance;
            }
        }
        p.set_force(forceVector);
    }

}

std::vector<double[3]> particleCollection::stromerVerlet(float dt, float tEnd) {
    std::vector<double[3]> forces;
    float t = 0.0;
    computeForce();
    while (t < tEnd) {
        t += dt;
        for (particle p : this->particleVector) {

        }
    }
    return forces;
}



