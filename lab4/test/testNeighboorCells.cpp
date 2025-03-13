//
// Created by audigiem on 13/03/25.
//
#include "../include/univers.h"

int main() {
    // Création d'un univers 3D
    Univers univers(3, {1.0, 1.0, 1.0}, 0.1);

    univers.showUnivers();

//    // Ajout de particules
//    for (int i = 0; i < 5; ++i) {
//        for (int j = 0; j < 5; ++j) {
//            for (int k = 0; k < 5; ++k) {
//                std::vector<double> position = {i / 5.0, j / 5.0, k / 5.0};
//                std::vector<double> velocity = {0, 0, 0}; // Vitesse initiale nulle
//                Particle particle(position, velocity, 1.0, 1.0); // Masse de 1.0
//                univers.addParticle(particle);
//            }
//        }
//    }
//
//    // Évolution de l'univers
//    double dt = 0.001; // Pas de temps
//    double t_end = 1.0; // Temps final
//    univers.showUnivers();
//    univers.showNeighbourCells({0, 0, 0});
//    univers.showNeighbourCells({1, 1, 1});
//    univers.showNeighbourCells({2, 2, 2});
//    univers.showNeighbourCells({3, 3, 3});
//    univers.showNeighbourCells({4, 4, 4});
//    univers.evoluer(dt, t_end);

    return 0;
}