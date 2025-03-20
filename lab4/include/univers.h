//
// Created by matteo on 09/03/25.
//

#ifndef CPP_UNIVERS_H
#define CPP_UNIVERS_H

#include <unordered_map>
#include <tuple>
#include <vector>
#include <memory>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "cell.h" // Inclure la définition complète de la classe Cell

// Spécialisation de std::hash pour std::tuple<int, int, int>
namespace std {
    template <>
    struct hash<std::tuple<int, int, int>> {
        size_t operator()(const std::tuple<int, int, int>& t) const {
            // Combinez les hachages des éléments du tuple
            size_t h1 = std::hash<int>{}(std::get<0>(t));
            size_t h2 = std::hash<int>{}(std::get<1>(t));
            size_t h3 = std::hash<int>{}(std::get<2>(t));
            return h1 ^ (h2 << 1) ^ (h3 << 2); // Combinaison simple des hachages
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
    std::unordered_map<std::tuple<int, int, int>, std::shared_ptr<Cell>> cells;
    int nbCells_x, nbCells_y, nbCells_z;

public:
    Univers(int dimension, double caracteristicLength, double cutOffRadius);

    // Getters et setters
    [[nodiscard]] int getDimension() const;
    [[nodiscard]] double getCaracteristicLength() const;
    [[nodiscard]] double getCutOffRadius() const;
    [[nodiscard]] const std::unordered_map<std::tuple<int, int, int>, std::shared_ptr<Cell>>& getCells() const;
    [[nodiscard]] int getCellLength() const;

    void setDimension(int dimension);
    void setCaracteristicLength(double caracteristicLength);
    void setCutOffRadius(double cutOffRadius);

    // Méthodes
    std::shared_ptr<Cell> getCell(const std::tuple<int, int, int>& cellIndex) const;
    std::vector<std::tuple<int, int, int>> getCoordNeighbourCells(const std::tuple<int, int, int>& cellIndex) const;

    void addParticle(const Particle& particle);
    void removeEmptyCells();
    void fillUnivers(int nbParticles);

    void showUnivers() const;
    void showNeighbourCells(const std::tuple<int, int, int>& cellIndex) const;
};

#endif // CPP_UNIVERS_H