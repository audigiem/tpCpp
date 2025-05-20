/**
 * @file particle.hpp
 * @brief N-dimensional particle class for physics simulations
 * @author Mattéo Gautier
 * @date 2025-05-19
 */

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "vecteur.hpp"
#include "forceType.h"
#include <string>
#include <memory>


/**
 * @class Particle
 * @brief A template class representing a physical particle in N-dimensional space
 * @tparam N The dimension of the space (must be > 0)
 * 
 * This class provides methods for representing and simulating particles
 * with physical properties like position, velocity, mass, and forces.
 */
template <std::size_t N>
class Particle {
private:
    /** @brief Unique identifier for the particle */
    int id;
    
    /** @brief Position vector of the particle */
    Vecteur<N> position;
    
    /** @brief Velocity vector of the particle */
    Vecteur<N> velocity;
    
    /** @brief Mass of the particle */
    double mass;
    
    /** @brief Category/type of the particle (e.g., "electron", "planet") */
    std::string category;
    
    /** @brief Current force vector acting on the particle */
    Vecteur<N> force;
    
    /** @brief Previous force vector that acted on the particle */
    Vecteur<N> old_force;

public:
    /**
     * @brief Constructor for a particle
     * @param id Unique identifier for the particle
     * @param position Initial position vector
     * @param velocity Initial velocity vector
     * @param mass Mass of the particle
     * @param category Classification/type of the particle
     */
    Particle(int id, const Vecteur<N>& position, const Vecteur<N>& velocity, double mass, std::string category);

    /**
     * @brief Get the particle's unique identifier
     * @return The particle's ID
     */
    int getId() const;
    
    /**
     * @brief Get the particle's position vector
     * @return Constant reference to the position vector
     */
    const Vecteur<N>& getPosition() const;
    
    /**
     * @brief Get the particle's velocity vector
     * @return Constant reference to the velocity vector
     */
    const Vecteur<N>& getVelocity() const;
    
    /**
     * @brief Get the particle's mass
     * @return The mass value
     */
    double getMass() const;
    
    /**
     * @brief Get the particle's category
     * @return Constant reference to the category string
     */
    const std::string& getCategory() const;
    
    /**
     * @brief Get the current force vector acting on the particle
     * @return Constant reference to the force vector
     */
    const Vecteur<N>& getForce() const;
    
    /**
     * @brief Get the previous force vector that acted on the particle
     * @return Constant reference to the previous force vector
     */
    const Vecteur<N>& getOldForce() const;

    /**
     * @brief Save the current force as the old force
     * @param force Force vector to save
     */
    void saveForce(const Vecteur<N>& force);
    
    /**
     * @brief Update the particle's position
     * @param newPos New position vector
     */
    void setPosition(const Vecteur<N>& newPos);
    
    /**
     * @brief Update the particle's velocity
     * @param newVel New velocity vector
     */
    void setVelocity(const Vecteur<N>& newVel);
    
    /**
     * @brief Add a force to the current force acting on the particle
     * @param newForce Force vector to add
     */
    void applyForce(const Vecteur<N>& newForce);
    
    /**
     * @brief Reset the force acting on the particle to zero
     */
    void resetForce();

    /**
     * @brief Calculate the Euclidean distance to another particle
     * @param other The other particle
     * @return The distance between the particles
     */
    double getDistance(const Particle<N>& other) const;

    /**
     * @brief Equality comparison operator
     * @param other Particle to compare with
     * @return True if particles are equal, false otherwise
     */
    bool operator==(const Particle<N>& other) const;
    
    /**
     * @brief Inequality comparison operator
     * @param other Particle to compare with
     * @return True if particles are not equal, false otherwise
     */
    bool operator!=(const Particle<N>& other) const;

    /**
     * @brief Calculate gravitational force between this particle and another
     * @param p Pointer to the other particle
     * @return Force vector from gravity
     */
    Vecteur<N> getGravityForce(Particle<N>*& p) const;
    
    /**
     * @brief Calculate Lennard-Jones force between this particle and another
     * @param p Pointer to the other particle
     * @param epsilon Depth of the potential well
     * @param sigma Distance at which the potential is zero
     * @return Force vector from Lennard-Jones potential
     */
    Vecteur<N> getLennardJonesForce(Particle<N>*& p, float epsilon, float sigma) const;
    
    /**
     * @brief Calculate all forces (gravity and Lennard-Jones) between this particle and another
     * @param p Pointer to the other particle
     * @param epsilon Depth of the potential well for Lennard-Jones
     * @param sigma Distance at which the potential is zero for Lennard-Jones
     * @return Combined force vector
     */
    Vecteur<N> getAllForces(Particle<N>*& p, float epsilon, float sigma) const;
    
    /**
     * @brief Optimized version of getAllForces with pre-calculated parameters
     * @param p Pointer to the other particle
     * @param epsilon_times_24 Pre-calculated value of 24*epsilon
     * @param sigma Distance at which the potential is zero
     * @param force Type of force to calculate (gravity, Lennard-Jones, or both)
     * @return Combined force vector using optimized calculations
     */
    Vecteur<N> optimizedGetAllForces(Particle<N>* p, float epsilon_times_24, float sigma, ForceType force) const;


    /**
     * @brief Calculate the kinetic energy of the particle
     * @return The kinetic energy value
     */
    double getKineticEnergy() const;

    /**
     * @brief Update the particle's velocity based on the targeted kinetic energy
     * @param targetedKineticEnergy The desired kinetic energy value
     */
    void updateVelocityWithKineticEnergyControl(double targetedKineticEnergy);

    /**
     * @brief KD-tree optimized version of force calculation
     * @param p Pointer to the other particle
     * @param epsilon_times_24 Pre-calculated value of 24*epsilon
     * @param sigma Distance at which the potential is zero
     * @return Combined force vector using KD-tree optimization
     */
    Vecteur<N> optimizedGetAllForcesKDtree(Particle<N>* p, float epsilon_times_24, float sigma) const;
    
    /**
     * @brief Calculate the cell index for spatial partitioning
     * @param cellLength Length of each cell
     * @return Array of indices representing the cell containing the particle
     */
    std::array<int, N> getCellIndexofParticle(double cellLength) const;

    /**
     * @brief Friend implementation of equality operator
     * @param p1 First particle
     * @param p2 Second particle
     * @return True if particles have identical properties
     */
    friend bool operator==(const Particle<N>& p1, const Particle<N>& p2) {
        return p1.id == p2.id &&
               p1.position == p2.position &&
               p1.velocity == p2.velocity &&
               p1.mass == p2.mass &&
               p1.category == p2.category &&
               p1.force == p2.force;
    }

    /**
     * @brief Friend implementation of inequality operator
     * @param p1 First particle
     * @param p2 Second particle
     * @return True if particles differ in any property
     */
    friend bool operator!=(const Particle<N>& p1, const Particle<N>& p2) {
        return !(p1 == p2);
    }

    /**
     * @brief Print particle information to standard output
     */
    void showParticle();
};

#include "../src/particle.tpp"

#endif // PARTICLE_HPP