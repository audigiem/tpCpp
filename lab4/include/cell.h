//
// Created by matteo on 20/03/25.
//

#ifndef CELL_H
#define CELL_H

#include "particle.h"
#include <vector>
#include <tuple>
#include <iostream>

class Cell {
private:
    int length;
    std::vector<Particle> particles;
    std::tuple<int, int, int> cellCoordinates;
    std::vector<std::tuple<int, int, int>> coordNeighborsCells;

public:
    Cell(int length);

    // Getters
    int getLength() const;
    std::vector<Particle> getParticles() const;
    std::tuple<int, int, int> getCellCoordinates() const;
    const std::vector<std::tuple<int, int, int>>& getNeighborsCells() const;
    std::vector<std::tuple<int, int, int>>& getNeighborsCells();

    // Setters
    void setLength(int length);
    void setParticles(const std::vector<Particle>& particles);
    void setCellCoordinates(const std::tuple<int, int, int>& cellCoordinates);
    void setNeighborsCells(const std::vector<std::tuple<int, int, int>>& neighborsCells);

    // Methods
    void addParticle(const Particle& particle);
    bool isEmpty() const;
    void showCell() const;
};

#endif //CELL_H
