#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>
#include <vector>
#include "particle.hpp"


template <std::size_t N>
class Cell {
private:
    std::vector<Particle<N>> particles;

public:
    void addParticle(const Particle<N>& particle);
    bool isEmpty() const;
    void showParticles() const;
    std::vector<Particle<N>> getParticles() const;
};

#include "../src/cell.tpp"

#endif // PARTICLE_H