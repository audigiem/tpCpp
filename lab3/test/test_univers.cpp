//
// Created by audigiem on 27/02/25.
//


#include "../include/univers.h"

int main() {
    Univers u = Univers(3, 4);
    std::cout << "Initial Univers: " << std::endl;
    std::cout << u << std::endl;

    std::cout << "Starting to move particles: " << std::endl;
    u.moveParticles(0.015, 468.5);
    std::cout << "Final Univers: " << std::endl;
    std::cout << u << std::endl;
    return 0;
}