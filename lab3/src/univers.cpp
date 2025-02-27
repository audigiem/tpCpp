//
// Created by audigiem on 27/02/25.
//

#include "../include/univers.h"
#include <random>

Univers::Univers(int dimension, int nbParticles) {
    this->dimension = dimension;
    this->nbParticles = nbParticles;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    Vecteur randomSpeed = Vecteur(dis(gen), dis(gen), dis(gen));
    for (int i = 0; i < nbParticles; i++) {
        Vecteur position = Vecteur(dis(gen), dis(gen), dis(gen));
        Vecteur velocity = randomSpeed;
        double mass = dis(gen);
        int id = i;
        int category = i;
        Particle p = Particle(position, velocity, mass, id, category);
        this->particles.push_back(p);
    }
}

int Univers::get_dimension() const {
    return dimension;
}

int Univers::get_nbParticles() const {
    return nbParticles;
}

std::vector<Particle> Univers::get_particles() const {
    return particles;
}

void Univers::set_dimension(int dimension) {
    Univers::dimension = dimension;
}

void Univers::set_nbParticles(int nbParticles) {
    Univers::nbParticles = nbParticles;
}

void Univers::set_particles(const std::vector<Particle> &particles) {
    Univers::particles = particles;
}

void Univers::addParticle(const Particle &p) {
    this->particles.push_back(p);
}

void Univers::removeParticle(const Particle &p) {
    for (int i = 0; i < this->particles.size(); i++) {
        if (this->particles[i].get_id() == p.get_id()) {
            this->particles.erase(this->particles.begin() + i);
        }
    }
}

void Univers::removeParticle(int id) {
    for (int i = 0; i < this->particles.size(); i++) {
        if (this->particles[i].get_id() == id) {
            this->particles.erase(this->particles.begin() + i);
        }
    }
}

void Univers::moveParticles(float dt, float tEnd) {
    // use the Stromer Verlet method to move the particles
    float t = 0.0;
    computeInternalForces();
    while (t < tEnd) {
        Vecteur oldForces = Vecteur(0, 0, 0);
        t += dt;
        for (Particle p : this->particles) {
            Vecteur position = p.get_position();
            Vecteur velocity = p.get_velocity();
            Vecteur force = p.get_force();
            position += dt * (((0.5 * dt / p.get_mass()) * force ) + velocity);
            p.set_position(position);
            // save the old force
            oldForces = p.get_force();
        }
        computeInternalForces();
        for (Particle p : this->particles) {
            Vecteur velocity = p.get_velocity();
            velocity += (dt * 0.5/p.get_mass()) * (oldForces + p.get_force());
            p.set_velocity(velocity);
        }

        std::cout << "Time: " << t << std::endl;
        std::cout << *this << std::endl;
        }
}

void Univers::computeInternalForces() {
    for (Particle p : this->particles) {
        Vecteur force = p.get_force();
        for (Particle p1 : this->particles) {
            if (p.get_id() != p1.get_id()) {
                Vecteur force2 = p.findForce(p1);
                force += force2;
            }
        }
        p.set_force(force);
    }
}

std::ostream &operator<<(std::ostream &out, const Univers &u) {
    out << "Dimension: " << u.get_dimension() << " Number of particles: " << u.get_nbParticles() << std::endl;
    for (Particle p : u.get_particles()) {
        out << p.get_position() << std::endl;
    }
    return out;
}