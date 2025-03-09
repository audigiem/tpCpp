//
// Created by matteo on 09/03/25.
//

#ifndef UNIVERS_H
#define UNIVERS_H

#include "particle.cpp"
#include "cell.cpp"
#include <cmath>

class Univers {
private:
    int dimension;
    double caracteristicLength;
    double cutOffRadius;
    std::vector<Particle> particles;
    std::vector< std::vector<Cell> > cells;
    int nCells;
public:
    Univers(int dimension, double caracteristicLength, double cutOffRadius)
        : dimension(dimension), caracteristicLength(caracteristicLength), cutOffRadius(cutOffRadius) {

        nCells = int (caracteristicLength / cutOffRadius);
        }

    int getDimension() const { return dimension; }
    double getCaracteristicLength() const { return caracteristicLength; }
    double getCutOffRadius() const { return cutOffRadius; }
    std::vector<Particle> getParticles() const { return particles; }
    std::vector< std::vector<Cell> > getCells() const { return cells; }

    void setDimension(int dimension) { this->dimension = dimension; }
    void setCaracteristicLength(double caracteristicLength) { this->caracteristicLength = caracteristicLength; }
    void setCutOffRadius(double cutOffRadius) { this->cutOffRadius = cutOffRadius; }
    void setParticles(std::vector<Particle> particles) { this->particles = particles; }
    void setCells(std::vector< std::vector<Cell> > cells) { this->cells = cells; }

};

#endif //UNIVERS_H

