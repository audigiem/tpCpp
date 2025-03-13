//
// Created by matteo on 09/03/25.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>
#include <iostream>
#include <ostream>

class Particle {
private:
    std::vector<double> position;
    std::vector<double> velocity;
    double mass;
    double charge;
public:
    Particle(std::vector<double> position, std::vector<double> velocity, double mass, double charge)
        : position(position), velocity(velocity), mass(mass), charge(charge) {}


    std::vector<double> getPosition() const { return position; }
    std::vector<double> getVelocity() const { return velocity; }
    double getMass() const { return mass; }
    double getCharge() const { return charge; }


    void setPosition(std::vector<double> position) { this->position = position; }
    void setVelocity(std::vector<double> velocity) { this->velocity = velocity; }
    void setMass(double mass) { this->mass = mass; }
    void setCharge(double charge) { this->charge = charge; }

};

#endif //PARTICLE_H