/**
 * @file cell.hpp
 * @brief Spatial partitioning cell for efficient particle simulation
 * @author Mattéo Audigier - Mattéo Gautier
 * @date 2025-05-19
 */

#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>
#include <vector>
#include "particle.hpp"
#include <memory>

/**
 * @class Cell
 * @brief A template class representing a spatial partitioning cell
 * @tparam N The dimension of the space (must be > 0)
 * 
 * This class implements a cell for spatial partitioning in an N-dimensional space.
 * Each cell contains particles and knows about its neighboring cells for efficient
 * proximity queries and interaction calculations.
 */
template <std::size_t N>
class Cell {
private:
    /** @brief Vector of particle pointers contained in this cell */
    std::vector<Particle<N>*> particles;
    
    /** @brief Pre-calculated indices of neighboring cells */
    std::vector<std::array<int, N>> neighbourCellsIndex;
    
    /** @brief Index position of this cell in the grid */
    std::array<int, N> cellIndex;
    
    /** @brief Physical length of the cell */
    double length;
    
    /** @brief Number of particles currently in the cell */
    int numberOfParticles = 0;

    /** @brief Total number of cells in each dimension */
    std::array<int, N> numberOfCells;

    /**
     * @brief Calculate indices of all neighboring cells
     * @return Vector of index arrays for each neighbor cell
     * @details Computes all adjacent cells including diagonals in N dimensions
     */
    std::vector<std::array<int, N>> computeNeighbourCellsIndex() const;

public:
    /**
     * @brief Default constructor
     */
    Cell() = default;
    
    /**
     * @brief Copy constructor
     * @param other Cell to copy
     */
    Cell(const Cell<N>& other);
    
    /**
     * @brief Parameterized constructor
     * @param cellIndex Index position of this cell in the grid
     * @param numberOfCells Total number of cells in each dimension
     * @param length Physical length of the cell
     */
    Cell(const std::array<int, N>& cellIndex, const std::array<int, N>& numberOfCells, double length);
    
    /**
     * @brief Destructor
     */
    ~Cell();
    
    /**
     * @brief Assignment operator
     * @param other Cell to copy
     * @return Reference to this cell after assignment
     */
    Cell<N>& operator=(const Cell<N>& other);

    /**
     * @brief Get all particles in this cell
     * @return Vector of particle pointers
     */
    std::vector<Particle<N>*> getParticles() const;
    
    /**
     * @brief Get indices of all neighboring cells
     * @return Vector of index arrays for neighboring cells
     */
    std::vector<std::array<int, N>> getNeighbourCellsIndex() const;
    
    /**
     * @brief Get this cell's index in the grid
     * @return Array of indices representing cell position
     */
    std::array<int, N> getCellIndex() const;
    
    /**
     * @brief Get number of particles in this cell
     * @return Particle count
     */
    int getNumberOfParticles() const { return numberOfParticles; }

    /**
     * @brief Check if the cell contains no particles
     * @return True if the cell is empty, false otherwise
     */
    bool isEmpty() const;
    
    /**
     * @brief Display information about all particles in this cell
     */
    void showParticles() const;

    /**
     * @brief Add a particle to this cell
     * @param particle Pointer to the particle to add
     * @details Updates the internal particle count and adds the particle to the collection
     */
    void addParticle(Particle<N>*& particle);
    
    /**
     * @brief Remove a particle from this cell
     * @param particle Pointer to the particle to remove
     * @return True if the particle was found and removed, false otherwise
     */
    void removeParticle(Particle<N>*& particle);
};

#include "../src/cell.tpp"

#endif // PARTICLE_H