//
// Created by matteo on 19/03/25.
//

#include "../include/univers.hpp"
#include "../include/cell.hpp"
#include <iostream>

int main() {
    // Création d'un univers 2D
    Univers univers2D(2, 10, 1.0);
    univers2D.showUnivers();

    // Remplir l'univers avec 50 particules
    univers2D.fillUnivers(50);
    univers2D.showUnivers();


    // Afficher les voisins d'une cellule
    std::array<int, 3> cellIndex2D = {2, 2, 0};
    univers2D.showNeighbourCells(cellIndex2D);

    return 0;
}