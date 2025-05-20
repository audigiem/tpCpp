#include "../include/particle.hpp"

template <std::size_t N>
Particle<N>::Particle(int id, const Vecteur<N>& position, const Vecteur<N>& velocity, double mass, std::string category)
    : id(id), position(position), velocity(velocity), mass(mass), category(std::move(category)), force() {
}

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
const Vecteur<N>& Particle<N>::getOldForce() const {
    return old_force;
}


template <std::size_t N>
void Particle<N>::saveForce(const Vecteur<N>& force) {
    old_force = force;
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
    constexpr double max_force = 1e4;
    constexpr double min_force = -1e4;
    double resultantNorm = (force + newForce).norm();
    if (resultantNorm < max_force && resultantNorm > min_force) {
        force += newForce;
    }

}

template <std::size_t N>
void Particle<N>::resetForce() {
    force = Vecteur<N>();
}

template <std::size_t N>
double Particle<N>::getDistance(const Particle<N>& other) const {
    // Compute the distance between two particles
    Vecteur<N> distance_vect = (other.getPosition() - position);
    return distance_vect.norm();
}

template <std::size_t N>
Vecteur<N> Particle<N>::getGravityForce(Particle<N>* p) const {
    Vecteur<N> distance_vect = p->getPosition() - position;
    double distance = distance_vect.norm();

    // Évite la division par zéro
    constexpr double min_dist = 1e-6;
    if (distance < min_dist) return Vecteur<N>();

    double factor = mass * p->getMass() / (distance * distance * distance); // G est pris à 1
    return factor * distance_vect;
}

template <std::size_t N>
Vecteur<N> Particle<N>::getLennardJonesForce(Particle<N>* p, float epsilon, float sigma) const {
    Vecteur<N> distance_vect = p->getPosition() - position;
    double distance = distance_vect.norm();

    constexpr double min_dist = 1e-6;
    if (distance < min_dist) return Vecteur<N>();

    double inv_r = sigma / distance;
    double inv_r6 = inv_r * inv_r * inv_r;
    inv_r6 *= inv_r6; // (sigma / r)^6

    double magnitude = 24 * epsilon / (distance * distance) * inv_r6 * (1 - 2 * inv_r6);
    return magnitude * distance_vect;
}

template <std::size_t N>
Vecteur<N> Particle<N>::getAllForces(Particle<N>* p, float epsilon, float sigma) const {
    Vecteur<N> distance_vect = p->getPosition() - position;
    double distance = distance_vect.norm();

    constexpr double min_dist = 1e-6;
    if (distance < min_dist) return Vecteur<N>();

    Vecteur<N> unit = distance_vect / distance;

    // Lennard-Jones
    double inv_r = sigma / distance;
    double inv_r6 = inv_r * inv_r * inv_r;
    inv_r6 *= inv_r6;
    double lennard_jones = 24 * epsilon * (2 * inv_r6 * inv_r6 - inv_r6) / (distance * distance);

    // Gravitation
    double gravity = mass * p->getMass() / (distance * distance * distance);

    return (lennard_jones + gravity) * unit;
}


template <std::size_t N>
Vecteur<N> Particle<N>::optimizedGetAllForces(Particle<N>* p, float epsilon_times_24, float sigma, ForceType force) const {
    Vecteur<N> distance_vect = (p->getPosition() - position);
    // Tolérance pour éviter la division par zéro
    constexpr double alpha = 1e-2;
    double distance = distance_vect.norm();
    if (distance < alpha) {
        // Éviter la division par zéro et l'explosion des forces
        return Vecteur<N>();
    }
    double distance_squared = distance * distance;

    switch (force) {
        case ForceType::Gravity: {
            Vecteur<N> unit = distance_vect / distance;
            double gravity = mass * p->getMass() / distance_squared;
            return gravity * unit;
        }
        case ForceType::LennardJones: {
            Vecteur<N> unit = distance_vect / distance;
            double tmp = sigma / distance;
            double pow_6 = tmp * tmp * tmp;
            pow_6 *= pow_6;
            double lj_force = epsilon_times_24 * (2 * pow_6 * pow_6 - pow_6) / distance_squared;
            return lj_force * unit;

        }
        case ForceType::Both: {
            Vecteur<N> unit = distance_vect / distance;
            double gravity = mass * p->getMass() / distance_squared;
            double tmp = sigma / distance;
            double pow_6 = tmp * tmp * tmp;
            pow_6 *= pow_6;
            double lj_force = epsilon_times_24 * (2 * pow_6 * pow_6 - pow_6) / distance_squared;
            return (gravity + lj_force) * unit;
        }
        default:
            // Retour par défaut si une valeur inattendue est passée
            return Vecteur<N>();
    }
}



template <std::size_t N>
std::array<int, N> Particle<N>::getCellIndexofParticle(double cellLength) const {
    std::array<int, N> cellIndex;
    for (std::size_t i = 0; i < N; ++i) {
        cellIndex[i] = static_cast<int>(std::floor(position.get(i) /cellLength));
    }
    return cellIndex;
}



template <std::size_t N>
bool Particle<N>::operator==(const Particle<N>& other) const {
    return id == other.id && position == other.position && velocity == other.velocity && mass == other.mass;
}

template <std::size_t N>
bool Particle<N>::operator!=(const Particle<N>& other) const {
    return !(*this == other);
}

template <std::size_t N>
double Particle<N>::getKineticEnergy() const {
    // Calculate the kinetic energy of the particle
    double norm_velocity = velocity.norm();
    return 0.5 * mass * norm_velocity * norm_velocity;
}

template <std::size_t N>
void Particle<N>::updateVelocityWithKineticEnergyControl(double targetedKineticEnergy) {
    // Update the particle's velocity based on the targeted kinetic energy
    double beta = sqrt(targetedKineticEnergy/getKineticEnergy());
    for (std::size_t i = 0; i < N; ++i) {
        velocity.set(i, beta * velocity.get(i));
    }
}

template<std::size_t N>
void Particle<N>::showParticle() {
    std::cout << "Particle: " << id << std::endl;
    std::cout << "Position: " << getPosition() << " Velocity: " << getVelocity() << " Force:" << getForce() << " Mass: " << mass << std::endl;
}

