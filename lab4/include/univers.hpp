#ifndef UNIVERS_HPP
#define UNIVERS_HPP

#include "particle.hpp"
#include "vecteur.hpp"
#include "cell.hpp"

#include <vector>
#include <limits>
#include <iostream>
#include <unordered_map>
#include <memory>

// Specialization of std::hash for std::array<int, N>
namespace std {
    template <std::size_t N>
    struct hash<std::array<int, N>> {
        std::size_t operator()(const std::array<int, N>& values) const {
            std::size_t hash = 0;
            for (std::size_t i = 0; i < N; ++i) {
                hash ^= std::hash<int>{}(values[i]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            }
            return hash;
        }
    };
}

template <std::size_t N>
class Univers {
private:
    double caracteristicLength;
    double cutOffRadius;
    int cellLength;
    std::unordered_map<std::array<int, N>, std::shared_ptr<Cell<N>>> cells;

public:
    Univers(double caracteristicLength, double cutOffRadius);

    // Getters and setters
    [[nodiscard]] double getCaracteristicLength() const;
    [[nodiscard]] double getCutOffRadius() const;
    [[nodiscard]] const std::unordered_map<std::array<int, N>, std::shared_ptr<Cell<N>>>& getCells() const;
    [[nodiscard]] int getCellLength() const;

    void setCaracteristicLength(double caracteristicLength);
    void setCutOffRadius(double cutOffRadius);

    // Methods
    std::shared_ptr<Cell<N>> getCell(const std::array<int, N>& cellIndex) const;

    void addParticle(const Particle<N>& particle);
    void removeEmptyCells();
    void fillUnivers(int nbParticles);

    void showUnivers() const;

    void update(double dt);
};

#include "../src/univers.tpp"

#endif // UNIVERS_HPP