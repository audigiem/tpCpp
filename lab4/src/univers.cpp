//
// Created by audigiem on 13/03/25.
//

#include "../include/univers.h"
#include "cell.cpp"
#include <iostream>
#include <ostream>

Univers::Univers(int dimension, std::vector<double> caracteristicLength, double cutOffRadius) {
    this->dimension = dimension;
    this->caracteristicLength = caracteristicLength;
    this->cutOffRadius = cutOffRadius;

    // Determine the number of cells in each direction create the cells and add them to the vector of cells
    std::vector<int> nbCells;
    std::vector< std::vector<Cell> > cells;
    std::vector<Cell> cellsInDirection;

    for (int i = 0; i < dimension; ++i) {
        nbCells.push_back(ceil(caracteristicLength[i] / cutOffRadius));
        
        for (int j = 0; j < nbCells[i]; ++j) {
            Cell cell(cutOffRadius);
            cellsInDirection.push_back(cell);
        }
        cells.push_back(cellsInDirection);
    }
    this->nbCells = nbCells;
    this->cells = cells;
}

int Univers::getDimension() const {
    return dimension;
}

std::vector<double> Univers::getCaracteristicLength() const {
    return caracteristicLength;
}

double Univers::getCutOffRadius() const {
    return cutOffRadius;
}

std::vector< std::vector<Cell> > Univers::getCells() const {
    return cells;
}

void Univers::setDimension(int dimension) {
    this->dimension = dimension;
}


void Univers::setCaracteristicLength(std::vector<double> caracteristicLength) {
    this->caracteristicLength = caracteristicLength;
}

void Univers::setCutOffRadius(double cutOffRadius) {
    this->cutOffRadius = cutOffRadius;
}

std::vector<std::vector<Cell>> Univers::getNeighbourCells(std::vector<int> cellIndex) {
    std::vector<std::vector<Cell>> neighbourCells;
    std::vector<Cell> neighbourCellsInDirection;

    for (int i = 0; i < dimension; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (cellIndex[i] + j >= 0 && cellIndex[i] + j < nbCells[i]) {
                neighbourCellsInDirection.push_back(cells[i][cellIndex[i] + j]);
            }
        }
        neighbourCells.push_back(neighbourCellsInDirection);
    }
    return neighbourCells;
}


void Univers::setCells(std::vector< std::vector<Cell> > cells) {
    this->cells = cells;
}

void Univers::showUnivers() const {
    std::cout << "Dimension: " << dimension << std::endl;
    std::cout << "Caracteristic length: ";
    for (int i = 0; i < dimension; ++i) {
        std::cout << caracteristicLength[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Cut off radius: " << cutOffRadius << std::endl;
    std::cout << "Number of cells: " << std::endl;
    for (int i = 0; i < dimension; ++i) {
        std::cout << "  dimension " << i << ": "<< nbCells[i] << std::endl;
    }
    std::cout << "Cells: " << std::endl;
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < nbCells[i]; ++j) {
            std::cout << "Cell " << i << " " << j << std::endl;
            cells[i][j].showCell();
        }
    }
}

void Univers::showNeighbourCells(std::vector<int> cellIndex) const {
    std::cout << "Neighbour cells of cell ";
    for (int i = 0; i < dimension; ++i) {
        std::cout << cellIndex[i] << " ";
    }
    std::cout << std::endl;
    // correct way to do it
    std::vector<std::vector<Cell>> neighbourCells = const_cast<Univers*>(this)->getNeighbourCells(cellIndex);
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << "Cell " << i << " " << j << std::endl;
            neighbourCells[i][j].showCell();
        }
    }
}