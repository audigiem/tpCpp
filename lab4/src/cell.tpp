#include "../include/cell.hpp"
#include <cmath>
#include <iostream>

template <std::size_t N>
void Cell<N>::addParticle(const Particle<N>& particle) {
    particles.push_back(particle);
}

template <std::size_t N>
bool Cell<N>::isEmpty() const {
    return particles.empty();
}

template <std::size_t N>
void Cell<N>::showParticles() const {
    for (const Particle<N>& p : particles) {
        std::cout << "Particle " << p.getId() << " at " << p.getPosition() << " with velocity " << p.getVelocity() << std::endl;
    }
}

template <std::size_t N>
std::vector<Particle<N>> Cell<N>::getParticles() const {
    return particles;
}