//
// Created by matteo on 20/03/25.
//

#ifndef CELL_H
#define CELL_H

#include "particle.h"
#include <vector>
#include <tuple>

class Cell {
private:
    int length;
    std::vector<Particle> particles;
    std::array<int, 3> cellCoordinates;
    std::vector<std::array<int, 3>> coordNeighborsCells;

public:
    explicit Cell(int length);

    // Getters
    [[nodiscard]] int getLength() const;
    [[nodiscard]] std::vector<Particle> getParticles() const;
    [[nodiscard]] std::array<int, 3> getCellCoordinates() const;
    [[nodiscard]] const std::vector<std::array<int, 3>>& getNeighborsCells() const;
    std::vector<std::array<int, 3>>& getNeighborsCells();

    // Setters
    void setLength(int length);
    void setParticles(const std::vector<Particle>& particles);
    void setCellCoordinates(const std::array<int, 3>& cellCoordinates);
    void setNeighborsCells(const std::vector<std::array<int, 3>>& neighborsCells);

    // Methods
    void addParticle(const Particle& particle);
    [[nodiscard]] std::array<int, 3> computeBarycenter() const;
    [[nodiscard]] bool isEmpty() const;
    void showCell() const;
};

#endif //CELL_H
