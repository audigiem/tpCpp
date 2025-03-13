//
// Created by audigiem on 13/03/25.
//

#ifndef CPP_UNIVERS_H
#define CPP_UNIVERS_H



#include "../src/particle.cpp"
#include "../src/cell.cpp"
#include <cmath>

class Univers {
private:
    int dimension;
    std::vector<double> caracteristicLength;
    double cutOffRadius;
    std::vector< std::vector<Cell> > cells;
    std::vector<int> nbCells;
public:
    Univers(int dimension, std::vector<double> caracteristicLength, double cutOffRadius);

    int getDimension() const;
    std::vector<double> getCaracteristicLength() const;
    double getCutOffRadius() const;
    std::vector< std::vector<Cell> > getCells() const;

    void setDimension(int dimension);
    void setCaracteristicLength(std::vector<double> caracteristicLength);
    void setCutOffRadius(double cutOffRadius);
    void setCells(std::vector< std::vector<Cell> > cells);

    std::vector<std::vector<Cell>> getNeighbourCells(std::vector<int> cellIndex);

    void showUnivers() const;

    void showNeighbourCells(std::vector<int> cellIndex) const;

};



#endif //CPP_UNIVERS_H
