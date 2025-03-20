//
// Created by matteo on 20/03/25.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

class Particle {
private:
    std::vector<double> position;
    std::vector<double> velocity;
    double mass;
    double charge;

public:
    Particle(const std::vector<double>& position, const std::vector<double>& velocity, double mass, double charge);

    // Getters
    std::vector<double> getPosition() const;
    std::vector<double> getVelocity() const;
    double getMass() const;
    double getCharge() const;

    // Setters
    void setPosition(const std::vector<double>& position);
    void setVelocity(const std::vector<double>& velocity);
    void setMass(double mass);
    void setCharge(double charge);
};

#endif //PARTICLE_H
