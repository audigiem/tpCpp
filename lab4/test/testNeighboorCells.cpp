//
// Created by audigiem on 13/03/25.
//
#include "../include/univers.h"

int main() {
    // Création d'un univers 3D
    Univers univers3D(3, 1, 0.1);

    Univers univers2D(2, 1, 0.1);

    Univers univers1D(1, 1, 0.1);

    univers3D.showUnivers();
    univers2D.showUnivers();
    univers1D.showUnivers();

    std::array<int, 3> cellIndex = {0, 0, 0};
    std::array<int, 3> cellIndex3D = {5, 5, 5};

    std::array<int, 3> cellIndex1D = {2, 0, 0};
    std::array<int, 3> cellIndex2D = {2, 2, 0};

    univers3D.showNeighbourCells(cellIndex);
    univers3D.showNeighbourCells(cellIndex3D);

    univers2D.showNeighbourCells(cellIndex2D);
    univers1D.showNeighbourCells(cellIndex1D);

    return 0;
}