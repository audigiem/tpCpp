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
    std::vector<std::array<int, N>> neighbourCellsIndex;
    std::array<int, N> cellIndex;
    double length;
    int numberOfParticles = 0; // number of particles in the cell

    std::array<int, N> numberOfCells;

    std::vector<std::array<int, N>> computeNeighbourCellsIndex() const;

public:
    // constructor by copy
    Cell() = default;
    Cell(const Cell<N>& other);
    Cell(const std::array<int, N>& cellIndex, const std::array<int, N>& numberOfCells, double length);

    // getters
    std::vector<Particle<N>*> getParticles() const;
    std::vector<std::array<int, N>> getNeighbourCellsIndex() const;
    std::array<int, N> getCellIndex() const;
    int getNumberOfParticles() const { return numberOfParticles; }


    bool isEmpty() const;
    void showParticles() const;

    void addParticle(Particle<N>*& particle);
    void removeParticle(Particle<N>*& particle);



};

#include "../src/cell.tpp"

#endif // PARTICLE_H