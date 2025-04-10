//
// Created by matteo on 09/04/25.
//

#ifndef UNIVERSKDTREE_H
#define UNIVERSKDTREE_H

#include "particle.hpp"
#include "vecteur.hpp"
#include "KDTree.h"

#include <vector>


template <std::size_t N>
class UniversKDtree {
private:
    std::array<double, N> caracteristicLength;
    double cutOffRadius;
    std::array<int, N> cellLength;
    int nbParticles;
    std::vector<Particle<N>*> particles;
    KDTree<N> tree;

public:
    UniversKDtree(std::array<double, N> caracteristicLength, double cutOffRadius);

    ~UniversKDtree();

    // Getters and setters
    [[nodiscard]] std::array<double, N> getCaracteristicLength() const;
    [[nodiscard]] double getCutOffRadius() const;
    [[nodiscard]] std::array<int, N> getCellLength() const;
    [[nodiscard]] int getNbParticles() const;
    [[nodiscard]] std::vector<Particle<N>*> getParticles() const;

    void buildTree();

    void setCaracteristicLength(std::array<double, N> caracteristicLength);
    void setCutOffRadius(double cutOffRadius);

    // Methods
    void addParticle(Particle<N>* particle);
    void fillUnivers(int nbParticles);
    void showUnivers() const;

    void initUnivers(float epsilon, float sigma);
    void computeAllForcesOnParticle(float epsilon, float sigma, const KDTree<N>& kdTree);

    void update(double dt, float epsilon, float sigma);
    // void stromerVerlet(double dt, float epsilon, float sigma);
};

#include "../src/universKDtree.cpp"


#endif //UNIVERSKDTREE_H
