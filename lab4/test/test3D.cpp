//
// Created by matteo on 19/03/25.
//

#include "../include/univers.h"
#include "../include/cell.h"
#include <iostream>

int main() {
    Univers univers3D(3, 5, 1.0);
    univers3D.showUnivers();

    univers3D.fillUnivers(20);
    univers3D.showUnivers();


    std::array<int, 3> cellIndex3D = {1, 1, 1};
    univers3D.showNeighbourCells(cellIndex3D);

    return 0;
}