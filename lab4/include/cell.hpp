#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>
#include <vector>
#include "particle.hpp"
#include <memory>


template <std::size_t N>
class Cell {
private:
    std::vector<Particle<N>*> particles;
    std::vector<Cell<N>*> neighbourCells;



public:
    // constructor by copy
    Cell() = default;
    Cell(const Cell<N>& other);


    void addParticle(Particle<N>*& particle);
    bool isEmpty() const;
    void showParticles() const;
    std::vector<Particle<N>*> getParticles() const;
    void removeParticle(Particle<N>*& particle);
    std::vector<Cell<N>*> getNeighbourCells() const {
        return neighbourCells;
    }


};

#include "../src/cell.tpp"

#endif // PARTICLE_H