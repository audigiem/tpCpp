#include "../include/cell.hpp"
#include <cmath>
#include <iostream>
#include <functional>

template <std::size_t N>
Cell<N>::Cell(const Cell<N>& other) {
    this->particles = other.particles;
    this->neighbourCellsIndex = other.neighbourCellsIndex;
    this->cellIndex = other.cellIndex;
}

template<std::size_t N>
Cell<N>::~Cell() {
    // implements destructor
    particles.clear();
    neighbourCellsIndex.clear();
}

template <std::size_t N>
Cell<N>& Cell<N>::operator=(const Cell<N>& other) {
    if (this != &other) { // self-assignment check
        this->particles = other.particles;
        this->neighbourCellsIndex = other.neighbourCellsIndex;
        this->cellIndex = other.cellIndex;
        this->length = other.length;
        this->numberOfParticles = other.numberOfParticles;
        this->numberOfCells = other.numberOfCells;
    }
    return *this;
}




template <std::size_t N>
Cell<N>::Cell(const std::array<int, N>& cellIndex, const std::array<int, N>& numberOfCells, double length)
    : cellIndex(cellIndex), length(length), numberOfCells(numberOfCells)  // ← important
{
    neighbourCellsIndex = computeNeighbourCellsIndex();
}



template <std::size_t N>
void Cell<N>::addParticle(Particle<N>*& particle) {
    particles.push_back(particle);
    ++numberOfParticles;
}

template <std::size_t N>
bool Cell<N>::isEmpty() const {
    return particles.empty();
}

template <std::size_t N>
void Cell<N>::removeParticle(Particle<N>*& particle) {
    auto it = std::remove(particles.begin(), particles.end(), particle);
    if (it != particles.end()) {
        particles.erase(it, particles.end());
        --numberOfParticles;
    }

}

template <std::size_t N>
void Cell<N>::showParticles() const {
    // Affichage de l'indice de la cellule
    std::cout << "----------------------------------------\n";
    std::cout << "Cell at index: [";
    for (std::size_t i = 0; i < N; ++i) {
        std::cout << cellIndex[i];
        if (i != N - 1) std::cout << ", ";
    }
    std::cout << "]\n";

    // Affichage des cellules voisines
    std::cout << "Neighbouring cell indices:\n";
    for (const auto& index : neighbourCellsIndex) {
        std::cout << "  [";
        for (std::size_t i = 0; i < N; ++i) {
            std::cout << index[i];
            if (i != N - 1) std::cout << ", ";
        }
        std::cout << "]\n";
    }

    // Affichage des particules contenues
    std::cout << "Particles in this cell (" << particles.size() << "):\n";
    for (const auto& particle : particles) {
        std::cout << "  - Particle ID: " << particle->getId() << "\n";
        std::cout << "    Position: " << particle->getPosition() << "\n";
        // std::cout << "    Velocity: " << particle->getVelocity() << "\n";
        // std::cout << "    Mass: " << particle->getMass() << "\n";
        // std::cout << "    Category: " << particle->getCategory() << "\n";
    }
    std::cout << "----------------------------------------\n";
}


template <std::size_t N>
std::vector<Particle<N>*> Cell<N>::getParticles() const {
    return particles;
}

template <std::size_t N>
std::vector<std::array<int, N>> Cell<N>::getNeighbourCellsIndex() const {
    return neighbourCellsIndex;
}

template <std::size_t N>
std::array<int, N> Cell<N>::getCellIndex() const {
    return cellIndex;
}

template <std::size_t N>
std::vector<std::array<int, N>> Cell<N>::computeNeighbourCellsIndex() const {
    std::vector<std::array<int, N>> neighbours;

    std::function<void(std::size_t, std::array<int, N>)> recurse = [&](std::size_t dim, std::array<int, N> offset) {
        if (dim == N) {
            std::array<int, N> neighbourIndex;
            for (std::size_t i = 0; i < N; ++i) {
                neighbourIndex[i] = cellIndex[i] + offset[i];
                if (neighbourIndex[i] < 0 || neighbourIndex[i] >= numberOfCells[i]) {
                    return; // hors de la grille
                }
            }
            neighbours.push_back(neighbourIndex);
            return;
        }

        for (int d = -1; d <= 1; ++d) {
            offset[dim] = d;
            recurse(dim + 1, offset);  // offset est une copie
        }
    };

    std::array<int, N> offset{};
    recurse(0, offset);
    return neighbours;
}









