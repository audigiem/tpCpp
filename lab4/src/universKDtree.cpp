//
// Created by matteo on 09/04/25.
//


#include "../include/universKDtree.h"
#include <iostream>
#include "../include/particle.hpp"
#include "../include/KDTree.h"

template <std::size_t N>
UniversKDtree<N>::UniversKDtree(std::array<double, N> caracteristicLength, double cutOffRadius)
    : caracteristicLength(caracteristicLength), cutOffRadius(cutOffRadius) {
    for (std::size_t i = 0; i < N; ++i) {
        cellLength[i] = static_cast<int>(std::ceil(caracteristicLength[i] / cutOffRadius));
    }
    nbParticles = 0;
}

template <std::size_t N>
UniversKDtree<N>::~UniversKDtree() {
    // Destructor logic if needed
    for (auto particle : particles) {
        delete particle; // Assuming particles are dynamically allocated
    }
}

template <std::size_t N>
std::array<double, N> UniversKDtree<N>::getCaracteristicLength() const {
    return caracteristicLength;
}

template <std::size_t N>
double UniversKDtree<N>::getCutOffRadius() const {
    return cutOffRadius;
}

template <std::size_t N>
std::array<int, N> UniversKDtree<N>::getCellLength() const {
    return cellLength;
}

template <std::size_t N>
int UniversKDtree<N>::getNbParticles() const {
    return nbParticles;
}

template <std::size_t N>
std::vector<Particle<N>*> UniversKDtree<N>::getParticles() const {
    return particles;
}


template <std::size_t N>
void UniversKDtree<N>::setCaracteristicLength(std::array<double, N> caracteristicLength) {
    for (std::size_t i = 0; i < N; ++i) {
        cellLength[i] = static_cast<int>(std::ceil(caracteristicLength[i] / cutOffRadius));
    }
    this->caracteristicLength = caracteristicLength;
}

template <std::size_t N>
void UniversKDtree<N>::setCutOffRadius(double cutOffRadius) {
    this->cutOffRadius = cutOffRadius;
}

template <std::size_t N>
void UniversKDtree<N>::buildTree() {
    KDTree<N> kdTree(particles);
    this->tree = kdTree;
}




template <std::size_t N>
void UniversKDtree<N>::addParticle(Particle<N>* particle) {
    particles.push_back(particle);
}



template <std::size_t N>
void UniversKDtree<N>::fillUnivers(int nbParticles) {
    for (int i = 0; i < nbParticles; ++i) {
        // create a random position and velocity for the particle
        Vecteur<N> position;
        Vecteur<N> velocity;
        for (std::size_t j = 0; j < N; ++j) {
            position.set(j, static_cast<double>(rand()) / RAND_MAX * caracteristicLength);
            velocity.set(j, static_cast<double>(rand()) / RAND_MAX * caracteristicLength);
        }
        Particle<N>* particle = new Particle<N>(i, position, velocity, 1.0, "default");
        addParticle(particle);
    }
}

template <std::size_t N>
void UniversKDtree<N>::showUnivers() const {
    std::cout << "========== UniversKDtree ==========" << std::endl;
    for (const auto& p : particles) {
        std::cout << "Particle ID: " << p->getId() << ", Position: " << p->getPosition() << ", Velocity: " << p->getVelocity() << std::endl;
    }
    std::cout << "=============================" << std::endl;
}




/**
* @brief Compute all the forces applied on each particle and store it in each particle
* !! this function overloads the forces already stored in the particle !!
* and saves the previous forces in the particle
 * we consider only the particles in the neighbourhood of the particle
 */
template <std::size_t N>
void UniversKDtree<N>::computeAllForcesOnParticle(float epsilon, float sigma, const KDTree<N>& kdTree) {
    std::vector<Vecteur<N>> previousForcesOnParticles;

    for (const auto& particle : particles) {
        particle->saveForce(particle->getForce());
        auto neighbourParticles = kdTree.queryRadius(particle, cutOffRadius);
        for (const auto& neighbour : neighbourParticles) {
            if (neighbour != particle) {
                Vecteur<N> force = particle->optimizedGetAllForcesKDtree(neighbour, epsilon, sigma);
                particle->applyForce(force);
            }
        }
    }

}

template <std::size_t N>
void UniversKDtree<N>::initUnivers(float epsilon, float sigma) {
    computeAllForcesOnParticle(epsilon, sigma, tree);
}




template <std::size_t N>
void UniversKDtree<N>::update(double dt, float epsilon, float sigma) {
    // std::cout << "Updating UniversKDtreee..." << std::endl;
    // showUniversKDtree();

    // we loop through the particles and update their position
    for (const auto& p : particles) {
        // update the position of the particle
        Vecteur<N> newPosition = p->getPosition() + p->getVelocity() * dt + (p->getForce() / p->getMass()) * (dt * dt) / 2;
        // update the cells configuration (of the original cells)
        p->setPosition(newPosition);
        tree.updateParticlePosition(p);
        // p->showParticle();
        // std::cout << "is supposed to move to " << newPosition << std::endl;
        // showUniversKDtree();

        // dont need to save the old forces as we have done it first line and they havent changed
        // we do it anyway to be sure
        p->saveForce(p->getForce());
    }


    computeAllForcesOnParticle(epsilon, sigma, tree);
    for (const auto& p : particles) {
        // update the velocity of the particle
        Vecteur<N> newVelocity = p->getVelocity() + dt * 0.5/p->getMass() * (p->getForce() + p->getOldForce());
        p->setVelocity(newVelocity);
    }

    // std::cout << "End of update: " << std::endl;
    // showUniversKDtree();



}

