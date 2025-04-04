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
Vecteur<N> Particle<N>::getGravityForce(const std::shared_ptr<Particle<N>>& p) const {
    // Compute the gravity force between two particles
    Vecteur<N> distance_vect = (p->getPosition() - position);
    double distance = distance_vect.norm();
    double force = mass * p->getMass() / std::pow(distance, 3);
    return (distance_vect) * force;
}

template <std::size_t N>
Vecteur<N> Particle<N>::getLennardJonesForce(const std::shared_ptr<Particle<N>>& p, float epsilon, float sigma) const {
    // Compute the Lennard-Jones force between two particles
    Vecteur<N> distance_vect = (p->getPosition() - position);
    double distance = distance_vect.norm();
    double pow_6 = std::pow(sigma / distance, 6);
    return 24 * epsilon / std::pow(distance, 2) * pow_6 * (1 - 2 * pow_6) * distance_vect;
}

template <std::size_t N>
Vecteur<N> Particle<N>::getAllForces(const std::shared_ptr<Particle<N>>& p, float epsilon, float sigma) const {
    // Combine all forces
    Vecteur<N>distance_vect = (p->getPosition() - position);
    double distance = distance_vect.norm();
    double pow_6 = std::pow(sigma / distance, 6);
    double lennard_jones = 24 * epsilon / (distance * distance) * pow_6 * (1 - 2 * pow_6);
    double gravity = mass * p->getMass() / (distance * distance * distance);
    return (lennard_jones + gravity) * distance_vect;
}

template <std::size_t N>
Vecteur<N> Particle<N>::optimizedGetAllForces(const std::shared_ptr<Particle<N>>& p, float epsilon_times_24, float sigma) const {
    // Combine all forces
    Vecteur<N>distance_vect = (p->getPosition() - position);
    double distance = distance_vect.norm();
    double distance_squared = distance * distance;
    double tmp = sigma / distance;
    double pow_6 = tmp * tmp * tmp;
    pow_6 *= pow_6;
    double lennard_jones = epsilon_times_24 / (distance_squared) * pow_6 * (1 - 2 * pow_6);
    double gravity = mass * p->getMass() / (distance_squared * distance);
    return (lennard_jones + gravity) * distance_vect;
}

template <std::size_t N>
bool Particle<N>::operator==(const Particle<N>& other) const {
    return id == other.id && position == other.position && velocity == other.velocity && mass == other.mass;
}
