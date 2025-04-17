#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>
#include <list>
#include "particle.hpp"
#include <memory>


template <std::size_t N>
class Cell {
private:
    std::list<Particle<N>*> particles;

public:
    // constructor by copy
    Cell() = default;
    Cell(const Cell<N>& other);


    void addParticle(Particle<N>*& particle);
    bool isEmpty() const;
    void showParticles() const;
    std::list<Particle<N>*> getParticles() const;
    void removeParticle(Particle<N>*& particle);


};

#include "../src/cell.tpp"

#endif // PARTICLE_H