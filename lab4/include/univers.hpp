/**
 * @file univers.hpp
 * @brief N-dimensional universe simulation for particle physics
 * @author Mattéo Audigier - Mattéo Gautier
 * @date 2025-05-19
 */

#ifndef UNIVERS_HPP
#define UNIVERS_HPP

#include "particle.hpp"
#include "vecteur.hpp"
#include "cell.hpp"

#include <vector>
#include <unordered_map>
#include <memory>

/**
 * @struct ArrayHash
 * @brief Hash function for std::array to use in unordered_map
 * @tparam N The dimension of the array
 * 
 * This structure implements a hash function for std::array<int, N>
 * to allow using arrays as keys in unordered_map containers.
 */
template <std::size_t N>
struct ArrayHash {
    /**
     * @brief Hash function operator for arrays
     * @param values The array to hash
     * @return Hash value of the array
     */
    std::size_t operator()(const std::array<int, N>& values) const {
        std::size_t hash = 0;
        for (std::size_t i = 0; i < N; ++i) {
            hash ^= std::hash<int>{}(values[i]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

/**
 * @class Univers
 * @brief A template class representing an N-dimensional universe for particle simulation
 * @tparam N The dimension of the space (must be > 0)
 * 
 * This class manages a collection of particles and cells for efficient spatial partitioning,
 * handles particle interactions, force calculations, and updates the simulation state.
 */
template <std::size_t N>
class Univers {
private:
    /** @brief Physical size of the universe in each dimension */
    std::array<double, N> caracteristicLength;
    
    /** @brief Cutoff radius for particle interactions and cell size */
    double cutOffRadius;
    
    /** @brief Number of cells in each dimension */
    std::array<int, N> numberOfCells;
    
    /** @brief Spatial hash map of cells for efficient neighbor lookups */
    std::unordered_map<std::array<int, N>, Cell<N>*, ArrayHash<N>> cells;
    
    /** @brief Container of all particles in the universe */
    std::vector<Particle<N>*> particles;
    
    /** @brief Total number of particles in the universe */
    int nbParticles;

public:
    /**
     * @brief Constructor for the universe
     * @param caracteristicLength Physical size in each dimension
     * @param cutOffRadius Interaction cutoff radius and cell size
     */
    Univers(std::array<double, N> caracteristicLength, double cutOffRadius);
    
    /**
     * @brief Copy constructor
     * @param other The universe to copy
     */
    Univers(const Univers&);
    
    /**
     * @brief Destructor
     */
    ~Univers();
    
    /**
     * @brief Assignment operator
     * @param other The universe to copy
     * @return Reference to this universe after assignment
     */
    Univers& operator=(const Univers&);

    // Getters and setters
    /**
     * @brief Get the physical size of the universe
     * @return Array containing the size in each dimension
     */
    [[nodiscard]] std::array<double, N> getCaracteristicLength() const;
    
    /**
     * @brief Get the cutoff radius
     * @return The cutoff radius value
     */
    [[nodiscard]] double getCutOffRadius() const;
    
    /**
     * @brief Get the cell hash map
     * @return Reference to the cell hash map
     */
    [[nodiscard]] const std::unordered_map<std::array<int, N>, Cell<N>*, ArrayHash<N>>& getCells() const;
    
    /**
     * @brief Get the number of cells in each dimension
     * @return Array containing the number of cells in each dimension
     */
    [[nodiscard]] std::array<int, N> getnumberOfCells() const;
    
    /**
     * @brief Get the total number of particles
     * @return The number of particles
     */
    [[nodiscard]] int getNbParticles() const;
    
    /**
     * @brief Get all particles in the universe
     * @return Vector of particle pointers
     */
    [[nodiscard]] std::vector<Particle<N>*> getParticles() const;

    /**
     * @brief Set the physical size of the universe
     * @param caracteristicLength New size in each dimension
     */
    void setCaracteristicLength(std::array<double, N> caracteristicLength);
    
    /**
     * @brief Set the cutoff radius
     * @param cutOffRadius New cutoff radius
     */
    void setCutOffRadius(double cutOffRadius);

    /**
     * @brief Initialize the spatial partitioning cells
     */
    void createCells();
    
    /**
     * @brief Get a specific cell by its index
     * @param cellIndex Array of indices specifying the cell position
     * @return Pointer to the cell, or nullptr if not found
     */
    Cell<N>* getCell(const std::array<int, N>& cellIndex) const;
    
    /**
     * @brief Add a particle to the universe
     * @param particle Pointer to the particle to add
     * @throw std::invalid_argument If the particle's position is invalid
     */
    void addParticle(Particle<N>*& particle);
    
    /**
     * @brief Update the cells configuration when a particle moves
     * @param particle Pointer to the particle
     * @param newPosition The new position vector
     * @throw std::runtime_error If the new position is outside universe bounds
     */
    void updateParticlePositionInCell(Particle<N>* particle, const Vecteur<N>& newPosition);
    
    /**
     * @brief Fill the universe with random particles
     * @param nbParticles Number of particles to create
     */
    void fillUnivers(int nbParticles);
    
    /**
     * @brief Display information about the universe and its particles
     */
    void showUnivers() const;
    
    /**
     * @brief Display neighborhood information for all particles
     */
    void showAllNeighbourhoods() const;
    
    /**
     * @brief Display neighborhood information for a specific particle
     * @param idOfParticle ID of the particle to show neighborhood for
     */
    void showNeighbourhoodsOfParticle(int idOfParticle) const;

    /**
     * @brief Apply reflective boundary conditions to a particle's position
     * @param particle The particle to check
     * @param newPosition The proposed new position
     * @return Modified position after applying boundary conditions
     */
    Vecteur<N> applyReflectiveLimitConditions(Particle<N>* particle, const Vecteur<N>& newPosition);
    
    /**
     * @brief Apply periodic boundary conditions to a position
     * @param newPosition The proposed new position
     * @return Modified position after applying boundary conditions
     */
    Vecteur<N> applyPeriodicLimitConditions(const Vecteur<N>& newPosition);
    
    /**
     * @brief Apply absorbing boundary conditions to a position
     * @param newPosition The proposed new position
     * @return Modified position after applying boundary conditions
     */
    Vecteur<N> applyAbsorbingLimitConditions(const Vecteur<N>& newPosition);

    /**
     * @brief Find all particles in the neighborhood of a given particle
     * @param particle The central particle
     * @return Vector of pointers to neighboring particles
     */
    std::vector<Particle<N>*> getParticlesInNeighbourhood(Particle<N>* particle) const;
    
    /**
     * @brief Compute and apply all forces between particles
     * @param epsilon Lennard-Jones potential depth parameter
     * @param sigma Lennard-Jones potential distance parameter
     */
    void computeAllForcesOnParticle(float epsilon, float sigma);

    /**
     * @brief Update the simulation state for one time step using the Stromer-Verlet method
     * @param dt Time step size
     * @param epsilon Lennard-Jones potential depth parameter
     * @param sigma Lennard-Jones potential distance parameter
     */
    void update(double dt, float epsilon, float sigma);
};

#include "../src/univers.tpp"

#endif // UNIVERS_HPP