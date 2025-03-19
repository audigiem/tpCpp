//
// Created by audigiem on 13/03/25.
//

#ifndef CPP_UNIVERS_H
#define CPP_UNIVERS_H



#include "../src/particle.cpp"
#include "../src/cell.cpp"

class Univers {
private:
    int dimension;
    double caracteristicLength;
    double cutOffRadius;
    std::vector< std::vector< std::vector<Cell>> > cells;
    int nbCellsPerDir;
public:
    Univers(int dimension, double caracteristicLength, double cutOffRadius);

    [[nodiscard]] int getDimension() const;
    [[nodiscard]] double getCaracteristicLength() const;
    [[nodiscard]] double getCutOffRadius() const;
    [[nodiscard]] std::vector< std::vector< std::vector<Cell>> > getCells() const;

    void setDimension(int dimension);
    void setCaracteristicLength(double caracteristicLength);
    void setCutOffRadius(double cutOffRadius);
    void setCells(const std::vector< std::vector< std::vector<Cell>> > &cells);

    std::vector<std::vector<int>> getCoordNeighbourCells(const std::vector<int> &cellIndex);

    void addParticle(const Particle &particle);

    void fillUnivers(int nbParticles);

    void showUnivers() const;

    void showNeighbourCells(const std::vector<int> &cellIndex) const;

};



#endif //CPP_UNIVERS_H
