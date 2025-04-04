//
// Created by matteo on 19/03/25.
//

#include "../include/univers.hpp"
#include "../include/cell.hpp"
#include <iostream>

int main() {
    // Création d'un univers 3D
    Univers univers3D(3, 5, 1.0);
    univers3D.showUnivers();

    // Remplir l'univers avec 20 particules
    univers3D.fillUnivers(20);
    univers3D.showUnivers();



    // Afficher les voisins d'une cellule
    std::array<int, 3> cellIndex3D = {1, 1, 1};
    univers3D.showNeighbourCells(cellIndex3D);

    return 0;
}