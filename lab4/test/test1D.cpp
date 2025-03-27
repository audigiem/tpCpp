//
// Created by matteo on 19/03/25.
//

#include "../include/univers.hpp"
#include "../include/cell.hpp"
#include <iostream>

int main() {
    // Création d'un univers 1D
    Univers univers1D(1, 10, 0.1);
    univers1D.showUnivers();

    // Remplir l'univers avec 100 particules
    std::cout << "Insertion of 100 particles in the universe" << std::endl;
    univers1D.fillUnivers(100);
    univers1D.showUnivers();
    

    // Afficher les voisins d'une cellule
    std::array<int, 3> cellIndex1D = {5, 0, 0};
    univers1D.showNeighbourCells(cellIndex1D);

    return 0;
}