//
// Created by audigiem on 13/02/25.
//

#include "Particle.h"

#include <random>


Particle::Particle(double position[3], double velocity[3], double mass, int id, int category) {
    for (int i = 0; i < 3; i++) {
        this->position[i] = position[i];
        this->velocity[i] = velocity[i];
    }
    this->mass = mass;
    this->id = id;
    this->category = category;
    for (int i = 0; i < 3; i++) {
        this->force[i] = 0;
    }
}

Particle::Particle() {
    for (int i = 0; i < 3; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);
        this->position[i] = dis(gen);
        this->velocity[i] = dis(gen);
        this->force[i] = dis(gen);
    }
    this->mass = 0;
    this->id = 0;
    this->category = 0;
}




void Particle::set_position(double position[3]) {
    for (int i = 0; i < 3; i++) {
        this->position[i] = position[i];
    }
}

void Particle::set_velocity(double velocity[3]) {
    for (int i = 0; i < 3; i++) {
        this->velocity[i] = velocity[i];
    }
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

void Particle::set_force(double force[3]) {
    for (int i = 0; i < 3; i++) {
        this->force[i] = force[i];
    }
}

double* Particle::get_position() {
    return this->position;
}

double* Particle::get_velocity() {
    return this->velocity;
}

double Particle::get_mass() {
    return this->mass;
}

int Particle::get_id() {
    return this->id;
}

int Particle::get_category() {
    return this->category;
}

double* Particle::get_force() {
    return this->force;
}

double* Particle::findForce(Particle p) {
    double forceVector[3] = {0, 0, 0};
    double distance = sqrt(pow(p.get_position()[0] - this->position[0], 2) +
                           pow(p.get_position()[1] - this->position[1], 2) +
                           pow(p.get_position()[2] - this->position[2], 2));
    double force = 1 / pow(distance, 2);
    forceVector[0] += force * (p.get_mass() * this->mass);
    forceVector[1] += force * (p.get_mass() * this->mass);
    forceVector[2] += force * (p.get_mass() * this->mass);
    return forceVector;
}
