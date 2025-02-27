//
// Created by audigiem on 13/02/25.
//

#ifndef CPP_PARTICLES_H
#define CPP_PARTICLES_H

#include "vecteur.h"
#include <iostream>
#include <ostream>

/*
 * Class particle : a class to represent a particles
 * contains a position, a velocity, a mass, an identifier, a category (type)
 * and a force
 */
class Particle {

private:
    Vecteur position;
    Vecteur velocity;
    double mass;
    int id;
    int category;
    Vecteur force;

public:
    Particle(const Vecteur &position, const Vecteur &velocity, double mass, int id, int category);

    Particle();


    void set_position(const Vecteur &position);

    void set_velocity(const Vecteur &velocity);

    void set_mass(double mass);

    void set_id(int id);

    void set_category(int category);

    void set_force(const Vecteur &force);

    Vecteur get_position() const;

    Vecteur get_velocity() const;

    double get_mass() const;

    int get_id() const;

    int get_category() const;

    Vecteur get_force() const;

    // determine the gravitational attraction force between two Particles
    Vecteur findForce(const Particle &p) const;
};


std::ostream &operator<<(std::ostream &out, const Particle &p);


#endif //CPP_PARTICLES_H
