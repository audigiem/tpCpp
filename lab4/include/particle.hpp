#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "vecteur.hpp"
#include <string>

template <std::size_t N>
class Particle {
private:
    int id;
    Vecteur<N> position;
    Vecteur<N> velocity;
    double mass;
    std::string category;
    Vecteur<N> force;

public:
    Particle(int id, const Vecteur<N>& position, const Vecteur<N>& velocity, double mass, std::string category);

    int getId() const;
    const Vecteur<N>& getPosition() const;
    const Vecteur<N>& getVelocity() const;
    double getMass() const;
    const std::string& getCategory() const;
    const Vecteur<N>& getForce() const;

    void setPosition(const Vecteur<N>& newPos);
    void setVelocity(const Vecteur<N>& newVel);
    void applyForce(const Vecteur<N>& newForce);
    void resetForce();

    Vecteur<N> getGravityForce(const Particle<N>& p) const;
    Vecteur<N> getLennardJonesForce(const Particle<N>& p, float epsilon, float sigma) const;
    Vecteur<N> getAllForces(const Particle<N>& p, float epsilon, float sigma) const;
    Vecteur<N> optimizedGetAllForces(const Particle<N>& p, float epsilon_times_24, float sigma) const;
};

#include "particle.tpp"

#endif // PARTICLE_HPP