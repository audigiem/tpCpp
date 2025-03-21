//
// Created by matteo on 20/03/25.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>

class Particle {
private:
    std::array<double, 3> position;
    std::array<double, 3> velocity;
    double mass;
    double charge;

public:
    Particle(const std::array<double, 3>& position, const std::array<double, 3>& velocity, double mass, double charge);

    // Getters
    [[nodiscard]] std::array<double, 3> getPosition() const;
    [[nodiscard]] std::array<double, 3> getVelocity() const;
    [[nodiscard]] double getMass() const;
    [[nodiscard]] double getCharge() const;

    // Setters
    void setPosition(const std::array<double, 3>& position);
    void setVelocity(const std::array<double, 3>& velocity);
    void setMass(double mass);
    void setCharge(double charge);

    // Methods
    [[nodiscard]] double computeLennardJonesPotential(const Particle& other, double cutOffRadius, double sigma, double epsilon) const;
    [[nodiscard]] double computeSquaredDistance(const Particle& other) const;
    [[nodiscard]] std::array<double, 3> computeElementaryLennardJonesForce(const Particle& other, double cutOffRadius, double sigma, double epsilon) const;
};

#endif //PARTICLE_H
