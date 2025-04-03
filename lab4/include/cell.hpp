#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>
#include <list>
#include <particle.hpp>


template <std::size_t N>
class Cell {
private:
    std::list<Particle<N>> particles;

public:
    void addParticle(const Particle<N>& particle);
    bool isEmpty() const;
    void showParticles() const;
    std::list<Particle<N>> getParticles() const;
    void removeParticle(const Particle<N>& particle);


};

#include "../src/cell.tpp"

#endif // PARTICLE_H