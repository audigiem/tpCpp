//
// Created by audigiem on 13/03/25.
//

#include "../include/univers.h"
#include "cell.cpp"
#include <iostream>
#include <ostream>
#include <cmath>

Univers::Univers(int dimension, double caracteristicLength, double cutOffRadius) {
    this->dimension = dimension;
    this->caracteristicLength = caracteristicLength;
    this->cutOffRadius = cutOffRadius;

    // Determine the number of cells in each direction create the cells
    int nbCellPerDir = ceil(caracteristicLength / cutOffRadius);
    this->nbCellsPerDir = nbCellPerDir;

    // Assure qu'on a toujours 3 dimensions, avec des tailles adaptées
    int sizeX = nbCellsPerDir;
    int sizeY = (dimension > 1) ? nbCellsPerDir : 1;
    int sizeZ = (dimension > 2) ? nbCellsPerDir : 1;

    // Allocation propre sans if
    cells.resize(sizeX, std::vector<std::vector<Cell>>(
        sizeY, std::vector<Cell>(sizeZ, Cell(cutOffRadius))
    ));

}

int Univers::getDimension() const {
    return dimension;
}

double Univers::getCaracteristicLength() const {
    return caracteristicLength;
}

double Univers::getCutOffRadius() const {
    return cutOffRadius;
}

std::vector< std::vector<std::vector<Cell>>> Univers::getCells() const {
    return cells;
}

void Univers::setDimension(int dimension) {
    this->dimension = dimension;
}


void Univers::setCaracteristicLength(double caracteristicLength) {
    this->caracteristicLength = caracteristicLength;
}

void Univers::setCutOffRadius(double cutOffRadius) {
    this->cutOffRadius = cutOffRadius;
}

std::vector<std::vector<int>> Univers::getCoordNeighbourCells(const std::vector<int> &cellIndex) {
    std::vector<std::vector<int>> neighbours;

    // Vérifier que cellIndex a bien la bonne dimension
    if (cellIndex.size() != dimension) {
        throw std::invalid_argument("cellIndex size does not match universe dimension");
    }

    // Définir les décalages en fonction de la dimension
    std::vector<int> offsets = {-1, 0, 1};

    // Génération des voisins (en respectant la dimension)
    for (int dx : offsets) {
        for (int dy : (dimension > 1 ? offsets : std::vector<int>{0})) {
            for (int dz : (dimension > 2 ? offsets : std::vector<int>{0})) {
                if (dx == 0 && dy == 0 && dz == 0) continue; // Exclure la cellule centrale

                std::vector<int> neighbour = {cellIndex[0] + dx};
                if (dimension > 1) neighbour.push_back(cellIndex[1] + dy);
                if (dimension > 2) neighbour.push_back(cellIndex[2] + dz);

                // Vérification que les voisins restent dans les bornes
                bool isValid = true;
                for (int d = 0; d < dimension; ++d) {
                    if (neighbour[d] < 0 || neighbour[d] >= nbCellsPerDir) {
                        isValid = false;
                        break;
                    }
                }
                if (isValid) {
                    neighbours.push_back(neighbour);
                }
            }
        }
    }

    return neighbours;
}



void Univers::setCells(const std::vector<std::vector<std::vector<Cell>>> &cells) {
    this->cells = cells;
}




void Univers::addParticle(const Particle &particle) {
    std::vector<double> position = particle.getPosition();

    // check if the particle is in the universe
    if (position.size() != dimension) {
        throw std::invalid_argument("Particle position does not match universe dimension");
    }

    std::vector<int> cellIndex;
    for (int d = 0; d < dimension; ++d) {
        int index = static_cast<int>(std::floor(position[d]/cutOffRadius));
        if (index < 0 || index >= nbCellsPerDir) {
            throw std::invalid_argument("Particle position is out of universe bounds");
        }
        cellIndex.push_back(index);
    }

    if (dimension == 1) {
        cells[cellIndex[0]][0][0].addParticle(particle);
    }
    else if (dimension == 2) {
        cells[cellIndex[0]][cellIndex[1]][0].addParticle(particle);
    }
    else {
        cells[cellIndex[0]][cellIndex[1]][cellIndex[2]].addParticle(particle);
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
    std::cout << "Dimension: " << dimension << std::endl;
    std::cout << "Caracteristic length: " << caracteristicLength << std::endl;
    std::cout << "Cut off radius: " << cutOffRadius << std::endl;

    std::cout << "Number of cells per direction: " << nbCellsPerDir << std::endl;

    std::cout << "Cells: " << std::endl;

    for (int x = 0; x < nbCellsPerDir; ++x) {
        for (int y = 0; y < (dimension > 1 ? nbCellsPerDir : 1); ++y) {
            for (int z = 0; z < (dimension > 2 ? nbCellsPerDir : 1); ++z) {
                std::cout << "  Cell (" << x << ", " << y << ", " << z << ")" << std::endl;
                cells[x][y][z].showCell();
            }
        }
    }
}


void Univers::showNeighbourCells(const std::vector<int> &cellIndex) const {
    std::cout << "Neighbour cells of cell ";
    for (int i = 0; i < dimension; ++i) {
        std::cout << cellIndex[i] << " ";
    }
    std::cout << std::endl;

    std::vector<std::vector<int>> neighbours = const_cast<Univers*>(this)->getCoordNeighbourCells(cellIndex);
    for (const std::vector<int> &neighbour : neighbours) {
        std::cout << "Neighbour cell: ";
        for (int i = 0; i < dimension; ++i) {
            std::cout << neighbour[i] << " ";
        }
        std::cout << std::endl;
    }
}