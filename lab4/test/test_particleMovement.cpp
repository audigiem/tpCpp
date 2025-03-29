/**
 * @file test_particleMovement.cpp
 * @brief Test the particle movement and how the hash table is updated
 * @author matteo
 * @date 2025-03-29
 */

#include <iostream>
#include "../include/univers.hpp"
#include "../include/particle.hpp"
#include "../include/vecteur.hpp"


int main() {
    // Create a 3D universe
    Univers<3> univers(1.0, 0.1);

    // Fill the universe with 10 particles
    univers.fillUnivers(10);
    univers.showUnivers();
    std::cout << std::endl;

    // Move the first particle encountered in the hashtable and update its position in the cell
    Vecteur<3> newPosition({0.5, 0.5, 0.5});
    Vecteur<3> newVelocity({0.1, 0.1, 0.1});
    Particle<3> particle = univers.getCells().begin()->second->getParticles().front();
    std::cout << "Before moving the particle: " << particle.getId() << particle.getPosition() << std::endl;
    univers.updateParticlePositionInCell(particle, newPosition, newVelocity);
    std::cout << "After moving the particle: " << particle.getPosition() << std::endl;
    univers.showUnivers();


    return 0;
}