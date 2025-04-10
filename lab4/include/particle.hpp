#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "vecteur.hpp"
#include <string>
#include <memory>

template <std::size_t N>
class Particle {
private:
    int id;
    Vecteur<N> position;
    Vecteur<N> velocity;
    double mass;
    std::string category;
    Vecteur<N> force;
    Vecteur<N> old_force;

public:
    Particle(int id, const Vecteur<N>& position, const Vecteur<N>& velocity, double mass, std::string category);

    int getId() const;
    const Vecteur<N>& getPosition() const;
    const Vecteur<N>& getVelocity() const;
    double getMass() const;
    const std::string& getCategory() const;
    const Vecteur<N>& getForce() const;
    const Vecteur<N>& getOldForce() const;

    void saveForce(const Vecteur<N>& force);
    void setPosition(const Vecteur<N>& newPos);
    void setVelocity(const Vecteur<N>& newVel);
    void applyForce(const Vecteur<N>& newForce);
    void resetForce();

    double getDistance(const Particle<N>& other) const;

    bool operator==(const Particle<N>& other) const;
    bool operator!=(const Particle<N>& other) const;

    Vecteur<N> getGravityForce(const std::shared_ptr<Particle<N>>& p) const;
    Vecteur<N> getLennardJonesForce(const std::shared_ptr<Particle<N>>& p, float epsilon, float sigma) const;
    Vecteur<N> getAllForces(const std::shared_ptr<Particle<N>>& p, float epsilon, float sigma) const;
    Vecteur<N> optimizedGetAllForces(const std::shared_ptr<Particle<N>>& p, float epsilon_times_24, float sigma) const;

    Vecteur<N> optimizedGetAllForcesKDtree(Particle<N>* p, float epsilon_times_24, float sigma) const;
    std::array<int, N> getCellIndexofParticle(std::array<int, N> cellLength) const;

    friend bool operator==(const Particle<N>& p1, const Particle<N>& p2) {
        return p1.id == p2.id &&
               p1.position == p2.position &&
               p1.velocity == p2.velocity &&
               p1.mass == p2.mass &&
               p1.category == p2.category &&
               p1.force == p2.force;
    }

    friend bool operator!=(const Particle<N>& p1, const Particle<N>& p2) {
        return !(p1 == p2);
    }

    void showParticle();

};

#include "../src/particle.tpp"

#endif // PARTICLE_HPP