//
// Created by matteo on 19/03/25.
//

#include "../include/univers.h"
#include "../include/cell.h"
#include <iostream>

int main() {
    // Création d'un univers 2D
    Univers univers2D(2, 10, 1.0);
    univers2D.showUnivers();

    // Remplir l'univers avec 50 particules
    univers2D.fillUnivers(50);
    univers2D.showUnivers();


    // Afficher les voisins d'une cellule
    std::tuple<int, int, int> cellIndex2D = {2, 2, 0};
    univers2D.showNeighbourCells(cellIndex2D);

    return 0;
}