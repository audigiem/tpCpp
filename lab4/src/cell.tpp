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

template <std::size_t N>
Cell<N>::Cell(const std::array<int, N>& cellIndex, std::array<double, N> gridSize, double length) {
    neighbourCellsIndex = computeNeighbourCellsIndex();
    this->cellIndex = cellIndex;
    this->length = length;
    this->gridSize = gridSize;
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
    auto it = std::remove(particles.begin(), particles.end(), particle);
    if (it != particles.end()) {
        particles.erase(it, particles.end());
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
    std::array<int, N> offset{};

    std::function<void(std::size_t)> recurse = [&](std::size_t dim) {
        if (dim == N) {
            std::array<int, N> neighbourIndex;
            for (std::size_t i = 0; i < N; ++i) {
                neighbourIndex[i] = cellIndex[i] + offset[i];

                // Convertir en coordonnée physique (coin bas-gauche de la cellule voisine)
                double physicalPos = neighbourIndex[i] * length;

                // Vérification des bornes physiques du domaine [0, L_i]
                if (physicalPos < 0.0 || physicalPos >= gridSize[i]) {
                    return; // hors du domaine, on ignore cette cellule
                }
            }
            neighbours.push_back(neighbourIndex);
            return;
        }

        for (int d = -1; d <= 1; ++d) {
            offset[dim] = d;
            recurse(dim + 1);
        }
    };

    recurse(0);
    return neighbours;
}






