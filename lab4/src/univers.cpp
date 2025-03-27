// Created by matteo on 09/03/25.
//

#include "../include/univers.h"
#include "../include/cell.h"
#include "../include/particle.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <memory>
#include <array>

Univers::Univers(int dimension, double caracteristicLength, double cutOffRadius)
    : dimension(dimension), caracteristicLength(caracteristicLength), cutOffRadius(cutOffRadius),
      cellLength(0), nbCells_x(0), nbCells_y(0), nbCells_z(0), cells() {
    nbCells_x = static_cast<int>(std::ceil(caracteristicLength / cutOffRadius));
    nbCells_y = (dimension >= 2) ? nbCells_x : 1;
    nbCells_z = (dimension >= 3) ? nbCells_x : 1;

    this->cellLength = static_cast<int>(std::ceil(caracteristicLength / nbCells_x));
}

// Getters
int Univers::getDimension() const {
    return dimension;
}

double Univers::getCaracteristicLength() const {
    return caracteristicLength;
}

double Univers::getCutOffRadius() const {
    return cutOffRadius;
}

const std::unordered_map<std::array<int, 3>, std::shared_ptr<Cell>>& Univers::getCells() const {
    return cells;
}

int Univers::getCellLength() const {
    return cellLength;
}

// Setters
void Univers::setDimension(int dimension) {
    this->dimension = dimension;
}

void Univers::setCaracteristicLength(double caracteristicLength) {
    this->caracteristicLength = caracteristicLength;
}

void Univers::setCutOffRadius(double cutOffRadius) {
    this->cutOffRadius = cutOffRadius;
}

// Methods
std::shared_ptr<Cell> Univers::getCell(const std::array<int, 3>& cellIndex) const {
    auto it = cells.find(cellIndex);
    if (it != cells.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<std::array<int, 3>> Univers::getCoordNeighbourCells(const std::array<int, 3>& cellIndex) const {
    std::vector<std::array<int, 3>> neighbours;

    for (int i = -1; i <= 1; ++i) {
        for (int j = (dimension > 1 ? -1 : 0); j <= (dimension > 1 ? 1 : 0); ++j) {
            for (int k = (dimension > 2 ? -1 : 0); k <= (dimension > 2 ? 1 : 0); ++k) {
                if (i == 0 && j == 0 && k == 0) continue;
                neighbours.push_back({cellIndex[0] + i, cellIndex[1] + j, cellIndex[2] + k});
            }
        }
    }
    return neighbours;
}

void Univers::addParticle(const Particle& p) {
    std::array<double,3> pos = p.getPosition();
    int i = static_cast<int>(pos[0] / cutOffRadius);
    int j = (dimension >= 2) ? static_cast<int>(pos[1] / cutOffRadius) : 0;
    int k = (dimension == 3) ? static_cast<int>(pos[2] / cutOffRadius) : 0;

    std::array<int, 3> cellIndex = {i, j, k};

    auto cell = getCell(cellIndex);
    if (!cell) {
        cell = std::make_shared<Cell>(getCellLength());
        cell->setCellCoordinates(cellIndex);
        cells[cellIndex] = cell;

        auto neighbours = getCoordNeighbourCells(cellIndex);
        for (const auto& n : neighbours) {
            auto neighbourCell = getCell(n);
            if (neighbourCell) {
                cell->getNeighborsCells().push_back(n);
                neighbourCell->getNeighborsCells().push_back(cellIndex);
            }
        }
    }
    cell->addParticle(p);
}

void Univers::removeEmptyCells() {
    for (auto it = cells.begin(); it != cells.end();) {
        if (it->second->isEmpty()) {
            auto neighbors = it->second->getNeighborsCells();
            for (const auto& n : neighbors) {
                auto neighbourCell = getCell(n);
                if (neighbourCell) {
                    auto& neighbourNeighbors = neighbourCell->getNeighborsCells();
                    neighbourNeighbors.erase(
                        std::remove(neighbourNeighbors.begin(), neighbourNeighbors.end(), it->first),
                        neighbourNeighbors.end()
                    );
                }
            }
            it = cells.erase(it);
        } else {
            ++it;
        }
    }
}

void Univers::fillUnivers(int nbParticles) {
    for (int i = 0; i < nbParticles; ++i) {
        std::array<double,3> position{};
        for (int d = 0; d < dimension; ++d) {
            position[d] = caracteristicLength * (rand() / (double)RAND_MAX);
        }
        Particle particle(position, {0, 0, 0}, 1, 1);
        addParticle(particle);
    }
}

void Univers::showUnivers() const {
    std::cout << "=== Univers Properties ===" << std::endl;
    std::cout << "Dimension: " << dimension << std::endl;
    std::cout << "Caracteristic length: " << caracteristicLength << std::endl;
    std::cout << "Cut off radius: " << cutOffRadius << std::endl;
    std::cout << "Cell length: " << cellLength << std::endl;
    std::cout << "Number of not empty cells: " << cells.size() << std::endl;
    std::cout << "================================" << std::endl;

}

void Univers::showNeighbourCells(const std::array<int, 3>& cellIndex) const {
    std::cout << "=== Neighbour Cells of Cell ("
              << cellIndex[0] << ", "
              << cellIndex[1] << ", "
              << cellIndex[2] << ") ===" << std::endl;
    auto neighbours = getCoordNeighbourCells(cellIndex);
    for (const auto& neighbour : neighbours) {
        auto cell = getCell(neighbour);
        if (cell) {
            std::cout << "  Neighbour Cell ("
                      << neighbour[0] << ", "
                      << neighbour[1] << ", "
                      << neighbour[2] << "): "
                      << cell->getParticles().size() << " particles" << std::endl;
        } else {
            std::cout << "  Neighbour Cell ("
                      << neighbour[0] << ", "
                      << neighbour[1] << ", "
                      << neighbour[2] << "): empty" << std::endl;
        }
    }
    std::cout << "================================" << std::endl;
}
