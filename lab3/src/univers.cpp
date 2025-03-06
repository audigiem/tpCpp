#ifndef UNIVERS_H
#define UNIVERS_H

#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <cstddef> // Pour size_t
#include "particle.cpp"

class Univers {
private:
    int dimension;
    std::vector<Particule> particules;
    std::vector<Vecteur> forces;
    std::vector<Vecteur> old_forces;

public:
    // Constructeur
    Univers(int dim) : dimension(dim) {}

    void appliquerConditionsLimitesReflechissantes(Particule& particule) {
        Vecteur position = particule.getPosition();
        Vecteur vitesse = particule.getVitesse();
        double x = position.getX();
        double y = position.getY();
        double z = position.getZ();

        // Rebond sur les bords du cube
        if (x < 0 || x > 1.0) {
            vitesse.setX(-vitesse.getX()/2); // Rebond élastique
            x = std::max(0.0, std::min(x, 1.0)); // Maintenir la position dans le cube
        }
        if (y < 0 || y > 1.0) {
            vitesse.setY(-vitesse.getY()/2);
            y = std::max(0.0, std::min(y, 1.0));
        }
        if (z < 0 || z > 1.0) {
            vitesse.setZ(-vitesse.getZ()/2);
            z = std::max(0.0, std::min(z, 1.0));
        }

        particule.mettreAJourPosition(Vecteur(x, y, z));
        particule.mettreAJourVitesse(vitesse);
    }

    // Ajouter une particule
    void ajouterParticule(const Particule& particule) {
        particules.push_back(particule);
        forces.push_back(Vecteur(0, 0, 0));
        old_forces.push_back(Vecteur(0, 0, 0));
    }

    // Calcul des forces gravitationnelles
    void calculerForces() {
        const double G = 1.0; // Constante gravitationnelle (simplifiée)
        const double epsilon = 1e-10; // Petite valeur pour éviter les divisions par zéro

        for (size_t i = 0; i < particules.size(); ++i) {
            forces[i] = Vecteur(0, 0, 0);
            for (size_t j = 0; j < particules.size(); ++j) {
                if (i != j) {
                    Vecteur r_ij = particules[j].getPosition() - particules[i].getPosition();
                    double distance = r_ij.norm();
                    if (distance < epsilon) distance = epsilon; // Éviter la division par zéro

                    double force_magnitude = G * particules[i].getMasse() * particules[j].getMasse() / (distance * distance * distance);
                    forces[i] = forces[i] + force_magnitude * r_ij ;

                    // Vérification des valeurs
                    if (std::isnan(forces[i].getX()) || std::isnan(forces[i].getY()) || std::isnan(forces[i].getZ())) {
                        std::cerr << "Erreur : force invalide détectée entre les particules " << i << " et " << j << std::endl;
                        std::cerr << "Distance : " << distance << std::endl;
                        std::cerr << "Force : ";
                        std::cerr << forces[i] << std::endl;
                        std::cerr << std::endl;
                    }
                }
            }
        }
    }

    // Évolution de l'univers avec l'algorithme de Störmer-Verlet
    void evoluer(double dt, double t_end) {
//        auto start = std::chrono::steady_clock::now();

        // Initialisation des forces
        calculerForces();

        double t = 0;
        while (t < t_end) {
            t += dt;

            // Mise à jour des positions
            for (size_t i = 0; i < particules.size(); ++i) {
                Vecteur vitesse = particules[i].getVitesse();
                Vecteur position = particules[i].getPosition();
                Vecteur force = forces[i];
                double masse = particules[i].getMasse();

                Vecteur nouvelle_position = position + dt * (vitesse + (0.5 / masse)* dt * force );
                particules[i].mettreAJourPosition(nouvelle_position);

                // Appliquer les conditions limites
                appliquerConditionsLimitesReflechissantes(particules[i]);
                old_forces[i] = force;
            }

            // Calcul des nouvelles forces
            calculerForces();

            // Mise à jour des vitesses
            for (size_t i = 0; i < particules.size(); ++i) {
                Vecteur vitesse = particules[i].getVitesse();
                Vecteur force = forces[i];
                Vecteur old_force = old_forces[i];
                double masse = particules[i].getMasse();

                Vecteur nouvelle_vitesse = vitesse + dt * (0.5 / masse) * (force + old_force);
                particules[i].mettreAJourVitesse(nouvelle_vitesse);
            }

            // Affichage des quantités (optionnel)
//            std::cout << "Temps: " << t << std::endl;
            afficherPython();
            std::cout << std::endl;
        }

//        auto end = std::chrono::steady_clock::now();
//        std::chrono::duration<double> elapsed_seconds = end - start;
//        std::cout << "Temps écoulé: " << elapsed_seconds.count() << "s\n";
    }

    // Affichage de l'univers
    void afficher() const {
        for (const auto& particule : particules) {
            particule.afficher();
        }
    }

    // Affichage pour python
    void afficherPython() const {
        for (const auto& particule : particules) {
            std::cout << particule.getPosition().getX() << " " << particule.getPosition().getY() << " " << particule.getPosition().getZ() << " ";
            std::cout << particule.getVitesse().getX() << " " << particule.getVitesse().getY() << " " << particule.getVitesse().getZ() << std::endl;
        }
    }
};

#endif
