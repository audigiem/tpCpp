//
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

// Constructeur
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

const std::unordered_map<std::tuple<int, int, int>, std::shared_ptr<Cell>>& Univers::getCells() const {
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
std::shared_ptr<Cell> Univers::getCell(const std::tuple<int, int, int>& cellIndex) const {
    auto it = cells.find(cellIndex);
    if (it != cells.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<std::tuple<int, int, int>> Univers::getCoordNeighbourCells(const std::tuple<int, int, int>& cellIndex) const {
    std::vector<std::tuple<int, int, int>> neighbours;

    // Définir les déplacements pour chaque dimension
    std::array<int, 3> dx = {-1, 0, 1};
    std::array<int, 3> dy = (dimension > 1) ? std::array<int, 3>{-1, 0, 1} : std::array<int, 3>{0, 0, 0};
    std::array<int, 3> dz = (dimension > 2) ? std::array<int, 3>{-1, 0, 1} : std::array<int, 3>{0, 0, 0};

    // Générer les voisins
    for (int i : dx) {
        for (int j : dy) {
            for (int k : dz) {
                if (i == 0 && j == 0 && k == 0) continue; // Ignorer la cellule elle-même
                neighbours.emplace_back(
                    std::get<0>(cellIndex) + i,
                    std::get<1>(cellIndex) + j,
                    std::get<2>(cellIndex) + k
                );
            }
        }
    }

    // Supprimer les doublons (nécessaire pour les dimensions inférieures à 3)
    std::sort(neighbours.begin(), neighbours.end());
    auto last = std::unique(neighbours.begin(), neighbours.end());
    neighbours.erase(last, neighbours.end());

    return neighbours;
}

void Univers::addParticle(const Particle& p) {
    std::vector<double> pos = p.getPosition();
    int i = static_cast<int>(pos[0] / cutOffRadius);
    int j = (dimension >= 2) ? static_cast<int>(pos[1] / cutOffRadius) : 0;
    int k = (dimension == 3) ? static_cast<int>(pos[2] / cutOffRadius) : 0;

    std::tuple<int, int, int> cellIndex = {i, j, k};

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
            // Récupérer les voisins de la cellule courante
            auto neighbors = it->second->getNeighborsCells(); // Copie des voisins

            // Parcourir chaque voisin
            for (const auto& n : neighbors) {
                auto neighbourCell = getCell(n);
                if (neighbourCell) {
                    // Récupérer les voisins du voisin
                    auto& neighbourNeighbors = neighbourCell->getNeighborsCells();

                    // Supprimer la cellule courante de la liste des voisins du voisin
                    neighbourNeighbors.erase(
                        std::remove(neighbourNeighbors.begin(), neighbourNeighbors.end(), it->first),
                        neighbourNeighbors.end()
                    );
                }
            }

            // Supprimer la cellule courante
            it = cells.erase(it);
        } else {
            ++it;
        }
    }
}

void Univers::fillUnivers(int nbParticles) {
    for (int i = 0; i < nbParticles; ++i) {
        std::vector<double> position;
        for (int d = 0; d < dimension; ++d) {
            position.push_back(caracteristicLength * (rand() / (double)RAND_MAX));
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
    std::cout << "Number of cells: " << nbCells_x * nbCells_y * nbCells_z << std::endl;
    std::cout << "Number of not empty cells: " << cells.size() << std::endl;

    // Afficher le nombre de particules dans l'univers
    size_t totalParticles = 0;
    for (const auto& cell : cells) {
        totalParticles += cell.second->getParticles().size();
    }
    std::cout << "Total particles: " << totalParticles << std::endl;

    // Afficher les coordonnées des cellules non vides
    std::cout << "Non-empty cells and their particle counts:" << std::endl;
    for (const auto& cell : cells) {
        if (!cell.second->isEmpty()) {
            std::cout << "  Cell (" << std::get<0>(cell.first) << ", "
                      << std::get<1>(cell.first) << ", "
                      << std::get<2>(cell.first) << "): "
                      << cell.second->getParticles().size() << " particles" << std::endl;
        }
    }
    std::cout << "=========================" << std::endl;
}

void Univers::showNeighbourCells(const std::tuple<int, int, int>& cellIndex) const {
    std::cout << "=== Neighbour Cells of Cell ("
              << std::get<0>(cellIndex) << ", "
              << std::get<1>(cellIndex) << ", "
              << std::get<2>(cellIndex) << ") ===" << std::endl;

    // Obtenir les coordonnées des cellules voisines
    auto neighbours = getCoordNeighbourCells(cellIndex);

    // Afficher les informations sur chaque cellule voisine
    for (const auto& neighbour : neighbours) {
        auto cell = getCell(neighbour);
        if (cell) {
            std::cout << "  Neighbour Cell ("
                      << std::get<0>(neighbour) << ", "
                      << std::get<1>(neighbour) << ", "
                      << std::get<2>(neighbour) << "): "
                      << cell->getParticles().size() << " particles" << std::endl;
        } else {
            std::cout << "  Neighbour Cell ("
                      << std::get<0>(neighbour) << ", "
                      << std::get<1>(neighbour) << ", "
                      << std::get<2>(neighbour) << "): empty" << std::endl;
        }
    }
    std::cout << "================================" << std::endl;
}