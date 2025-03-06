//
// Created by audigiem on 27/02/25.
//


#include "../src/univers.cpp"
#include "../src/particle.cpp"
#include "../include/vecteur.h"

int main() {
    // Création d'un univers 3D
    Univers univers(3);

    // Ajout de particules
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                Vecteur position(i / 5.0, j / 5.0, k / 5.0);
                Vecteur vitesse(0, 0, 0); // Vitesse initiale nulle
                Particule particule(position, vitesse, 1.0); // Masse de 1.0
                univers.ajouterParticule(particule);
            }
        }
    }

    // Évolution de l'univers
    double dt = 0.001; // Pas de temps
    double t_end = 1.0; // Temps final
    univers.evoluer(dt, t_end);

    return 0;
}