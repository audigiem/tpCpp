//
// Created by matteo on 09/03/25.
//

#include "../include/particle.h"

Particle::Particle(const std::vector<double>& position, const std::vector<double>& velocity, double mass, double charge)
    : position(position), velocity(velocity), mass(mass), charge(charge) {}

// Getters
std::vector<double> Particle::getPosition() const {
    return position;
}

std::vector<double> Particle::getVelocity() const {
    return velocity;
}

double Particle::getMass() const {
    return mass;
}

double Particle::getCharge() const {
    return charge;
}

// Setters
void Particle::setPosition(const std::vector<double>& position) {
    this->position = position;
}

void Particle::setVelocity(const std::vector<double>& velocity) {
    this->velocity = velocity;
}

void Particle::setMass(double mass) {
    this->mass = mass;
}

void Particle::setCharge(double charge) {
    this->charge = charge;
}