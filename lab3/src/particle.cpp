#ifndef PARTICULE_H
#define PARTICULE_H

#include "vecteur.h"

class Particule {
private:
    Vecteur position;
    Vecteur vitesse;
    double masse;

public:
    // Constructeur
    Particule(const Vecteur& pos, const Vecteur& vit, double masse)
        : position(pos), vitesse(vit), masse(masse) {}

    // Getters
    Vecteur getPosition() const { return position; }
    Vecteur getVitesse() const { return vitesse; }
    double getMasse() const { return masse; }

    // Mise à jour de la position et de la vitesse
    void mettreAJourPosition(const Vecteur& nouvellePosition) {
        position = nouvellePosition;
    }

    void mettreAJourVitesse(const Vecteur& nouvelleVitesse) {
        vitesse = nouvelleVitesse;
    }

    // Affichage
    void afficher() const {
        std::cout << "Position: " << position;
        std::cout << ", Vitesse: " << vitesse;
        std::cout << ", Masse: " << masse << std::endl;
    }
};

#endif
