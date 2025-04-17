#include "../include/cell.hpp"
#include <cmath>
#include <iostream>


template <std::size_t N>
Cell<N>::Cell(const Cell<N>& other) {
    particles = other.particles;
}

template <std::size_t N>
void Cell<N>::addParticle(Particle<N>*& particle) {
    particles.push_back(particle);
}

template <std::size_t N>
bool Cell<N>::isEmpty() const {
    return particles.empty();
}

template <std::size_t N>
void Cell<N>::removeParticle(Particle<N>*& particle) {
    particles.remove(particle);
}

template <std::size_t N>
void Cell<N>::showParticles() const {
    std::cout << "Particles in this cell:" << std::endl;
    for (const auto& particle : particles) {
        std::cout << "Particle ID: " << particle->getId() << ", Position: " << particle->getPosition() << ", Force: " << particle->getForce() << std::endl;
    }
}

template <std::size_t N>
std::list<Particle<N>*> Cell<N>::getParticles() const {
    return particles;
}