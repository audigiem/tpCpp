//
// Created by matteo on 19/03/25.
//

#include "../include/univers.h"
#include "../include/cell.h"
#include <iostream>

int main() {
    Univers univers1D(1, 10, 0.1);
    univers1D.showUnivers();

    std::cout << "Insertion of 100 particles in the universe" << std::endl;
    univers1D.fillUnivers(100);
    univers1D.showUnivers();
    

    std::array<int, 3> cellIndex1D = {5, 0, 0};
    univers1D.showNeighbourCells(cellIndex1D);

    return 0;
}