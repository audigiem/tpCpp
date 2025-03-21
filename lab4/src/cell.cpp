//
// Created by matteo on 09/03/25.
//

#include "../include/cell.h"
#include <iostream>

Cell::Cell(int length) : length(length) {}

// Getters
int Cell::getLength() const {
    return length;
}

std::vector<Particle> Cell::getParticles() const {
    return particles;
}

std::array<int, 3> Cell::getCellCoordinates() const {
    return cellCoordinates;
}

const std::vector<std::array<int, 3>>& Cell::getNeighborsCells() const {
    return coordNeighborsCells;
}

std::vector<std::array<int, 3> >& Cell::getNeighborsCells() {
    return coordNeighborsCells;
}


// Setters
void Cell::setLength(int length) {
    this->length = length;
}

void Cell::setParticles(const std::vector<Particle>& particles) {
    this->particles = particles;
}

void Cell::setCellCoordinates(const std::array<int, 3>& cellCoordinates) {
    this->cellCoordinates = cellCoordinates;
}

void Cell::setNeighborsCells(const std::vector<std::array<int, 3>>& neighborsCells) {
    this->coordNeighborsCells = neighborsCells;
}

// Methods
void Cell::addParticle(const Particle& particle) {
    particles.push_back(particle);
}

std::array<int, 3> Cell::computeBarycenter() const {
    std::array<int, 3> coordCell = getCellCoordinates();
    std::array<int, 3> barycenter = {coordCell[0] + getLength()/2, coordCell[1]+getLength()/2, coordCell[2] + getLength()/2};
    return barycenter;
}


bool Cell::isEmpty() const {
    return particles.empty();
}

void Cell::showCell() const {
    for (size_t i = 0; i < particles.size(); ++i) {
        std::cout << "      Particle " << i;
        std::cout << " Position: ";
        for (size_t j = 0; j < particles[i].getPosition().size(); ++j) {
            std::cout << particles[i].getPosition()[j] << " ";
        }
        std::cout << std::endl;
    }
}