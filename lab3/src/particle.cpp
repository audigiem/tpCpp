//
// Created by audigiem on 13/02/25.
//

#include "../include/particle.h"
#include "../include/vecteur.h"
#include <random>


Particle::Particle(const Vecteur &position, const Vecteur &velocity, double mass, int id, int category) {
    this->position = position;
    this->velocity = velocity;
    this->mass = mass;
    this->id = id;
    this->category = category;
    this->force = Vecteur(0, 0, 0);
}

Particle::Particle() {
    // Random initialization
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    this->position = Vecteur(dis(gen), dis(gen), dis(gen));
    this->velocity = Vecteur(dis(gen), dis(gen), dis(gen));

    this->mass = 0;
    this->id = 0;
    this->category = 0;

    this->force = Vecteur(0, 0, 0);
}




void Particle::set_position(const Vecteur &position) {
    this->position = position;
}

void Particle::set_velocity(const Vecteur &velocity) {
    this->velocity = velocity;
}

void Particle::set_mass(double mass) {
    this->mass = mass;
}

void Particle::set_id(int id) {
    this->id = id;
}

void Particle::set_category(int category) {
    this->category = category;
}

void Particle::set_force(const Vecteur &force) {
    this->force = force;
}

Vecteur Particle::get_position() const {
    return this->position;
}

Vecteur Particle::get_velocity() const {
    return this->velocity;
}

double Particle::get_mass() const {
    return this->mass;
}

int Particle::get_id() const {
    return this->id;
}

int Particle::get_category() const {
    return this->category;
}

Vecteur Particle::get_force() const {
    return this->force;
}

Vecteur Particle::findForce(const Particle &p) const {
    double distance = this->position.distance(p.position);
    double force = 1 / pow(distance, 2);
    Vecteur forceVector = Vecteur(force * (p.get_mass() * this->mass), force * (p.get_mass() * this->mass), force * (p.get_mass() * this->mass));
    return forceVector;
}

std::ostream &operator<<(std::ostream &out, const Particle &p) {
    out << "Position: " << p.get_position() << std::endl;
    out << "Velocity: " << p.get_velocity() << std::endl;
    out << "Mass: " << p.get_mass() << std::endl;
    out << "Id: " << p.get_id() << std::endl;
    out << "Category: " << p.get_category() << std::endl;
    return out;
}
