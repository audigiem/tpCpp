//
// Created by audigiem on 27/02/25.
//

#ifndef CPP_UNIVERS_H
#define CPP_UNIVERS_H

#include "particle.h"
#include "vecteur.h"
#include <vector>
#include <iostream>
#include <ostream>

class Univers {
private:
    int dimension;
    int nbParticles;
    std::vector<Particle> particles;

public:
    Univers() = default;

    Univers(int dimension, int nbParticles);

    int get_dimension() const;

    int get_nbParticles() const;

    std::vector<Particle> get_particles() const;

    void set_dimension(int dimension);

    void set_nbParticles(int nbParticles);

    void set_particles(const std::vector<Particle> &particles);

    void addParticle(const Particle &p);

    void removeParticle(const Particle &p);

    void removeParticle(int id);

    void moveParticles(float dt, float tEnd);

    void computeInternalForces();

};

std::ostream &operator<<(std::ostream &out, const Univers &u);


#endif //CPP_UNIVERS_H
