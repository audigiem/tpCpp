//
// Created by audigiem on 13/03/25.
//
#include "../include/univers.hpp"

int main() {
    // univers 2D 10x10 avec des cellules de 2x2, particules initialisées avec des positions aléatoires
    Univers<2> univers({10.0, 10.0}, 2.0);

    // Creation des particules
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            Vecteur<2> position({static_cast<double>(i), static_cast<double>(j)});
            Particle<2>* particle = new Particle<2>(i * 10 + j, position, Vecteur<2>({0.0, 0.0}), 1.0, "red");
            univers.addParticle(particle);
        }
    }

    // Affichage des cellules et de leurs particules
    univers.showUnivers();
    // Affichage des voisins de chaque cellule
    univers.showAllNeighbourhoods();





    return 0;
}