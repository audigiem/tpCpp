#include "../include/particle.hpp"

template <std::size_t N>
Particle<N>::Particle(int id, const Vecteur<N>& position, const Vecteur<N>& velocity, double mass, std::string category)
    : id(id), position(position), velocity(velocity), mass(mass), category(std::move(category)), force() {}

template <std::size_t N>
int Particle<N>::getId() const {
    return id;
}

template <std::size_t N>
const Vecteur<N>& Particle<N>::getPosition() const {
    return position;
}

template <std::size_t N>
const Vecteur<N>& Particle<N>::getVelocity() const {
    return velocity;
}

template <std::size_t N>
double Particle<N>::getMass() const {
    return mass;
}

template <std::size_t N>
const std::string& Particle<N>::getCategory() const {
    return category;
}

template <std::size_t N>
const Vecteur<N>& Particle<N>::getForce() const {
    return force;
}

template <std::size_t N>
void Particle<N>::setPosition(const Vecteur<N>& newPos) {
    position = newPos;
}

template <std::size_t N>
void Particle<N>::setVelocity(const Vecteur<N>& newVel) {
    velocity = newVel;
}

template <std::size_t N>
void Particle<N>::applyForce(const Vecteur<N>& newForce) {
    force = newForce;
}

template <std::size_t N>
void Particle<N>::resetForce() {
    force = Vecteur<N>();
}

template <std::size_t N>
Vecteur<N> Particle<N>::getGravityForce(const Particle<N>& p) const {
    // Implement gravity force calculation
    return Vecteur<N>();
}

template <std::size_t N>
Vecteur<N> Particle<N>::getLennardJonesForce(const Particle<N>& p, float epsilon, float sigma) const {
    // Implement Lennard-Jones force calculation
    return Vecteur<N>();
}

template <std::size_t N>
Vecteur<N> Particle<N>::getAllForces(const Particle<N>& p, float epsilon, float sigma) const {
    // Combine all forces
    return getGravityForce(p) + getLennardJonesForce(p, epsilon, sigma);
}