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

particleCollection::particleCollection(std::vector<particle> particles) {
    for (particle p : particles) {
        this->particleList.push_back(p);
        this->particleDeque.push_back(p);
        this->particleVector.push_back(p);
        // this->particleSet.insert(p);
    }

}

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

void particleCollection::computeForce(particle p) {
    double forceVector[3] = {0, 0, 0};
    for (particle p1 : this->particleVector) {
        if (p.get_id() != p1.get_id()) {
            double distance = sqrt(pow(p.get_position()[0] - p1.get_position()[0], 2) +
                                   pow(p.get_position()[1] - p1.get_position()[1], 2) +
                                   pow(p.get_position()[2] - p1.get_position()[2], 2));
            double force = 1 / pow(distance, 2);
            forceVector[0] += force * (p.get_mass() * p1.get_mass());
            forceVector[1] += force * (p.get_mass() * p1.get_mass());
            forceVector[2] += force * (p.get_mass() * p1.get_mass());
        }
    }
    p.set_force(forceVector);
}

void particleCollection::computeAllForces() {
    for (particle p : this->particleVector) {
        computeForce(p);
    }
}

void particleCollection::stromerVerlet(float dt, float tEnd) {
    float t = 0.0;
    computeAllForces();
    while (t < tEnd) {
        double oldForces[3] = {0, 0, 0};
        t += dt;
        for (particle p : this->particleVector) {
            double position[3] = {
                p.get_position()[0] + dt * (p.get_velocity()[0] + 0.5 / p.get_mass() * p.get_force()[0] * dt),
                p.get_position()[1] + dt * (p.get_velocity()[1] + 0.5 / p.get_mass() * p.get_force()[1] * dt),
                p.get_position()[2] + dt * (p.get_velocity()[2] + 0.5 / p.get_mass() * p.get_force()[2] * dt)
            };
            p.set_position(position);
            // save the old force
            oldForces[0] = p.get_force()[0];
            oldForces[1] = p.get_force()[1];
            oldForces[2] = p.get_force()[2];
        }
        computeAllForces();
        for (particle p : this->particleVector) {
            double velocity[3] = {
                p.get_velocity()[0] + dt * 0.5/p.get_mass() * (oldForces[0] + p.get_force()[0]),
                p.get_velocity()[1] + dt * 0.5/p.get_mass() * (oldForces[1] + p.get_force()[1]),
                p.get_velocity()[2] + dt * 0.5/p.get_mass() * (oldForces[2] + p.get_force()[2])
            };
            p.set_velocity(velocity);
        }

        // print position of each particle for each iteration on the same line
        for (particle p : this->particleVector) {
            std::cout << t << p.get_position()[0] << " " << p.get_position()[1] << " " << p.get_position()[2] << " ";
        }
        std::cout << std::endl;

    }
}



