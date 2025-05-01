#ifndef UNIVERS_HPP
#define UNIVERS_HPP

#include "particle.hpp"
#include "vecteur.hpp"
#include "cell.hpp"

#include <vector>
#include <unordered_map>
#include <memory>

template <std::size_t N>
struct ArrayHash {
    std::size_t operator()(const std::array<int, N>& values) const {
        std::size_t hash = 0;
        for (std::size_t i = 0; i < N; ++i) {
            hash ^= std::hash<int>{}(values[i]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

template <std::size_t N>
class Univers {
private:
    std::array<double, N> caracteristicLength;
    double cutOffRadius;
    std::array<int, N> numberOfCells;
    std::unordered_map<std::array<int, N>, Cell<N>*, ArrayHash<N>> cells;
    std::vector<Particle<N>*> particles;
    int nbParticles;

public:
    Univers(std::array<double, N> caracteristicLength, double cutOffRadius);
    ~Univers();

    // Getters and setters
    [[nodiscard]] std::array<double, N> getCaracteristicLength() const;
    [[nodiscard]] double getCutOffRadius() const;
    [[nodiscard]] const std::unordered_map<std::array<int, N>, Cell<N>*, ArrayHash<N>>& getCells() const;
    [[nodiscard]] std::array<int, N> getnumberOfCells() const;
    [[nodiscard]] int getNbParticles() const;
    [[nodiscard]] std::vector<Particle<N>*> getParticles() const;

    void setCaracteristicLength(std::array<double, N> caracteristicLength);
    void setCutOffRadius(double cutOffRadius);

    // Methods
    void createCells();
    Cell<N>* getCell(const std::array<int, N>& cellIndex) const;
    void addParticle(Particle<N>*& particle);
    void updateParticlePositionInCell(Particle<N>* particle, const Vecteur<N>& newPosition);
    void fillUnivers(int nbParticles);
    void showUnivers() const;
    void showAllNeighbourhoods() const;


    // Methods for different limit conditions
    Vecteur<N> applyReflectiveLimitConditions(Particle<N>* particle, const Vecteur<N>& newPosition);
    Vecteur<N> applyPeriodicLimitConditions(const Vecteur<N>& newPosition);
    Vecteur<N> applyAbsorbingLimitConditions(const Vecteur<N>& newPosition);

    std::vector<Particle<N>*> getParticlesInNeighbourhood(Particle<N>* particle) const;
    void computeAllForcesOnParticle(float epsilon, float sigma);

    void update(double dt, float epsilon, float sigma);
    // void stromerVerlet(double dt, float epsilon, float sigma);
};

#include "../src/univers.tpp"

#endif // UNIVERS_HPP