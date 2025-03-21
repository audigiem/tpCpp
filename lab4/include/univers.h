///
// Created by matteo on 09/03/25.
///

#ifndef CPP_UNIVERS_H
#define CPP_UNIVERS_H

#include <unordered_map>
#include <array>
#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "cell.h"

// Spécialisation de std::hash pour std::array<int, 3>
namespace std {
    template <>
    struct hash<std::array<int, 3>> {
        size_t operator()(const std::array<int, 3>& arr) const {
            size_t h1 = std::hash<int>{}(arr[0]);
            size_t h2 = std::hash<int>{}(arr[1]);
            size_t h3 = std::hash<int>{}(arr[2]);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}

class Particle;  // Forward declaration

class Univers {
private:
    int dimension;
    double caracteristicLength;
    double cutOffRadius;
    int cellLength;
    std::unordered_map<std::array<int, 3>, std::shared_ptr<Cell>> cells;
    int nbCells_x, nbCells_y, nbCells_z;

public:
    Univers(int dimension, double caracteristicLength, double cutOffRadius);

    // Getters et setters
    [[nodiscard]] int getDimension() const;
    [[nodiscard]] double getCaracteristicLength() const;
    [[nodiscard]] double getCutOffRadius() const;
    [[nodiscard]] const std::unordered_map<std::array<int, 3>, std::shared_ptr<Cell>>& getCells() const;
    [[nodiscard]] int getCellLength() const;

    void setDimension(int dimension);
    void setCaracteristicLength(double caracteristicLength);
    void setCutOffRadius(double cutOffRadius);

    // Méthodes
    std::shared_ptr<Cell> getCell(const std::array<int, 3>& cellIndex) const;
    std::vector<std::array<int, 3>> getCoordNeighbourCells(const std::array<int, 3>& cellIndex) const;

    void addParticle(const Particle& particle);
    void removeEmptyCells();
    void fillUnivers(int nbParticles);

    void showUnivers() const;
    void showNeighbourCells(const std::array<int, 3>& cellIndex) const;
};

#endif // CPP_UNIVERS_H