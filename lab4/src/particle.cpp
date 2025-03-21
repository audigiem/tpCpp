//
// Created by matteo on 09/03/25.
//

#include "../include/particle.h"
#include <cmath>

Particle::Particle(const std::array<double, 3>& position, const std::array<double, 3>& velocity, double mass, double charge)
    : position(position), velocity(velocity), mass(mass), charge(charge) {}

// Getters
std::array<double, 3> Particle::getPosition() const {
    return position;
}

std::array<double, 3> Particle::getVelocity() const {
    return velocity;
}

double Particle::getMass() const {
    return mass;
}

double Particle::getCharge() const {
    return charge;
}

// Setters
void Particle::setPosition(const std::array<double, 3>& position) {
    this->position = position;
}

void Particle::setVelocity(const std::array<double, 3>& velocity) {
    this->velocity = velocity;
}

void Particle::setMass(double mass) {
    this->mass = mass;
}

void Particle::setCharge(double charge) {
    this->charge = charge;
}

double Particle::computeLennardJonesPotential(const Particle& other, double cutOffRadius, double sigma, double epsilon) const {
    double distance = sqrt(computeSquaredDistance(other));
    if (distance > cutOffRadius) {
        return 0;
    }
    return 4*epsilon*(std::pow(sigma/distance, 12) - std::pow(sigma/distance, 6));

}

double Particle::computeSquaredDistance(const Particle &other) const {
    return std::pow(position[0] - other.position[0], 2) +
           std::pow(position[1] - other.position[1], 2) +
           std::pow(position[2] - other.position[2], 2);
}

std::array<double, 3> Particle::computeElementaryLennardJonesForce(const Particle &other, double cutOffRadius, double sigma, double epsilon) const {
    double distance2 = computeSquaredDistance(other);
    double lennardJonesPotential = computeLennardJonesPotential(other, cutOffRadius, sigma, epsilon);
    std::array<double, 3> direction = {other.position[0] - position[0], other.position[1] - position[1], other.position[2] - position[2]};
    return { (1/distance2 * lennardJonesPotential) * direction[0], (1/distance2 * lennardJonesPotential) * direction[1],(1/distance2 * lennardJonesPotential) * direction[2] };
}
