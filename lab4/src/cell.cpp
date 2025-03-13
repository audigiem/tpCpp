//
// Created by matteo on 09/03/25.
//

#ifndef CELL_H
#define CELL_H

#include "particle.cpp"
#include <iostream>
#include <ostream>

class Cell {
private:
    int length;
    std::vector<Particle> particles;
public:
    Cell(int length) : length(length) {}

    int getLength() const { return length; }
    std::vector<Particle> getParticles() const { return particles; }

    void setLength(int length) { this->length = length; }
    void setParticles(std::vector<Particle> particles) { this->particles = particles; }

    void addParticle(Particle particle) { particles.push_back(particle); }

    void showCell() const {
        std::cout << "Cell length: " << length << std::endl;
        for (int i = 0; i < particles.size(); ++i) {
            std::cout << "Particle " << i << std::endl;
            std::cout << "Position: ";
            for (int j = 0; j < particles[i].getPosition().size(); ++j) {
                std::cout << particles[i].getPosition()[j] << " ";
            }
//            std::cout << std::endl;
//            std::cout << "Velocity: ";
//            for (int j = 0; j < particles[i].getVelocity().size(); ++j) {
//                std::cout << particles[i].getVelocity()[j] << " ";
//            }
//            std::cout << std::endl;
//            std::cout << "Mass: " << particles[i].getMass() << std::endl;
//            std::cout << "Charge: " << particles[i].getCharge() << std::endl;
        }
    }


};

#endif //CELL_H
