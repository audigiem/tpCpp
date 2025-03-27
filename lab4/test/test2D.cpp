//
// Created by matteo on 19/03/25.
//

#include "../include/univers.h"
#include "../include/cell.h"
#include <iostream>

int main() {
    Univers univers2D(2, 10, 1.0);
    univers2D.showUnivers();

    univers2D.fillUnivers(50);
    univers2D.showUnivers();


    std::array<int, 3> cellIndex2D = {2, 2, 0};
    univers2D.showNeighbourCells(cellIndex2D);

    return 0;
}