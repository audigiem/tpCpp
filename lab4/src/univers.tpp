#include "../include/univers.hpp"
#include <functional>
#include <cmath>


/**
 * Constructor
 */
template <std::size_t N>
Univers<N>::Univers(std::array<double, N> caracteristicLength, double cutOffRadius)
    : caracteristicLength(caracteristicLength), cutOffRadius(cutOffRadius) {
    // assert that the caracteristic length is greater than the cut off radius
    for (std::size_t i = 0; i < N; ++i) {
        if (caracteristicLength[i] < cutOffRadius) {
            throw std::invalid_argument("Caracteristic length must be greater than cut off radius");
        }
    }

    for (std::size_t i = 0; i < N; ++i) {
        numberOfCells[i] = static_cast<int>(std::ceil(caracteristicLength[i] / cutOffRadius));
    }
    nbParticles = 0;

    // Initialize the cells
    createCells();
}

template <std::size_t N>
Univers<N>::Univers(const Univers& other)
    : caracteristicLength(other.caracteristicLength), cutOffRadius(other.cutOffRadius),
      numberOfCells(other.numberOfCells), nbParticles(other.nbParticles) {
    // Copy the cells
    for (const auto& cell : other.cells) {
        cells[cell.first] = new Cell<N>(*cell.second);
    }
}

template <std::size_t N>
Univers<N>::~Univers() {
    for (const auto& cell : cells) {
        delete cell.second;
    }
    for (const auto& particle : particles) {
        delete particle;
    }
    particles.clear();
    cells.clear();
}

template <std::size_t N>
Univers<N>& Univers<N>::operator=(const Univers& other) {
    if (this != &other) {
        caracteristicLength = other.caracteristicLength;
        cutOffRadius = other.cutOffRadius;
        numberOfCells = other.numberOfCells;
        nbParticles = other.nbParticles;

        // Clear the existing cells and particles
        for (const auto& cell : cells) {
            delete cell.second;
        }
        cells.clear();
        for (const auto& particle : particles) {
            delete particle;
        }
        particles.clear();

        // Copy the cells
        for (const auto& cell : other.cells) {
            cells[cell.first] = new Cell<N>(*cell.second);
        }
    }
    return *this;
}


template <std::size_t N>
std::vector<std::array<int, N>> Univers<N>::generateAllGridCoordinates(const std::array<int, N>& gridSizePerDimension) {
    std::vector<std::array<int, N>> allCoords;
    std::array<int, N> currentCoord;

    std::function<void(std::size_t)> recurse = [&](std::size_t dim) {
        if (dim == N) {
            allCoords.push_back(currentCoord);
            return;
        }

        for (int i = 0; i < gridSizePerDimension[dim]; ++i) {
            currentCoord[dim] = i;
            recurse(dim + 1);
        }
    };

    recurse(0);
    return allCoords;
}



template <std::size_t N>
void Univers<N>::createCells() {
    std::vector<std::array<int, N>> allCellsIndex = generateAllGridCoordinates(numberOfCells);
    for (const auto& index : allCellsIndex) {
        auto* cell = new Cell<N>(index, numberOfCells, cutOffRadius);
        cells[index] = cell;
    }
}

template <std::size_t N>
std::array<double, N> Univers<N>::getCaracteristicLength() const {
    return caracteristicLength;
}

template <std::size_t N>
double Univers<N>::getCutOffRadius() const {
    return cutOffRadius;
}

template <std::size_t N>
const std::unordered_map<std::array<int, N>, Cell<N>*, ArrayHash<N>>& Univers<N>::getCells() const {
    return cells;
}

template <std::size_t N>
std::array<int, N> Univers<N>::getnumberOfCells() const {
    return numberOfCells;
}

template <std::size_t N>
int Univers<N>::getNbParticles() const {
    return nbParticles;
}

template <std::size_t N>
std::vector<Particle<N>*> Univers<N>::getParticles() const {
    return particles;
}


template <std::size_t N>
void Univers<N>::setCaracteristicLength(std::array<double, N> caracteristicLength) {
    for (std::size_t i = 0; i < N; ++i) {
        numberOfCells[i] = static_cast<int>(std::ceil(caracteristicLength[i] / cutOffRadius));
    }
    this->caracteristicLength = caracteristicLength;
}

template <std::size_t N>
void Univers<N>::setCutOffRadius(double cutOffRadius) {
    this->cutOffRadius = cutOffRadius;
}

template <std::size_t N>
Cell<N>* Univers<N>::getCell(const std::array<int, N>& cellIndex) const {
    auto it = cells.find(cellIndex);
    if (it != cells.end()) {
        return it->second;
    }
    return nullptr;
}


template <std::size_t N>
void Univers<N>::addParticle(Particle<N>*& particle) {
    std::array<int, N> cellIndex;
    cellIndex = particle->getCellIndexofParticle(cutOffRadius);
    auto cell = getCell(cellIndex);
    if (!cell) {
        throw std::invalid_argument("trying to add a particle in a cell that doesn't exist, incorrect position !");
    }
    cell->addParticle(particle);
    // add the particle to the list of particles
    particles.push_back(particle);
    ++nbParticles;
}


template <std::size_t N>
void Univers<N>::updateParticlePositionInCell(Particle<N>* particle, const Vecteur<N> &newPosition) {
    std::array<int, N> oldCellIndex;
    for (std::size_t i = 0; i < N; ++i) {
        oldCellIndex[i] = static_cast<int>(std::floor(particle->getPosition().get(i) / cutOffRadius));
    }
    std::array<int, N> newCellIndex;
    for (std::size_t i = 0; i < N; ++i) {
        newCellIndex[i] = static_cast<int>(std::floor(newPosition.get(i) / cutOffRadius));
    }


    if (oldCellIndex != newCellIndex) {
        // remove the particle from the old cell
        auto oldCell = getCell(oldCellIndex);
        if (oldCell) {
            oldCell->removeParticle(particle);
        }
        // add the particle to the new cell
        auto newCell = getCell(newCellIndex);
        if (newCell) {
            newCell->addParticle(particle);
        }
        else {
            std::cout << "Old position: " << particle->getPosition() << std::endl;
            std::cout << "New position: " << newPosition << std::endl;
            std::cout << "Old cell index: " << oldCellIndex[0] << ", " << oldCellIndex[1] << std::endl;
            std::cout << "New cell index: " << newCellIndex[0] << ", " << newCellIndex[1] << std::endl;
            std::cout << "Number of cells: " << numberOfCells[0] << ", " << numberOfCells[1] << std::endl;
            std::cout << "Force applied to: " << particle->getForce() << std::endl;
            // throw error, not suppose to happen with reflective limit conditions
            throw std::runtime_error("Cell not found, this should not happen with reflective limit conditions");

        }
    }
}

template <std::size_t N>
void Univers<N>::fillUnivers(int nbParticles) {
    for (int i = 0; i < nbParticles; ++i) {
        // create a random position and velocity for the particle
        Vecteur<N> position;
        Vecteur<N> velocity;
        for (std::size_t j = 0; j < N; ++j) {
            position.set(j, static_cast<double>(rand()) / RAND_MAX * caracteristicLength);
            velocity.set(j, static_cast<double>(rand()) / RAND_MAX * caracteristicLength);
        }
        auto* particle = new Particle<N>(i, position, velocity, 1.0, "default");
        addParticle(particle);
    }
}

template <std::size_t N>
void Univers<N>::showUnivers() const {
    std::cout << "========== Univers ==========" << std::endl;
    for (const auto& cell : cells) {
        cell.second->showParticles();
    }
    std::cout << "=============================" << std::endl;
}



template <std::size_t N>
std::vector<Particle<N>*> Univers<N>::getParticlesInNeighbourhood(Particle<N>* particle) const {
    std::vector<Particle<N>*> neighbourParticles;

    // Get the cell of the particle
    std::array<int, N> cellIndex = particle->getCellIndexofParticle(cutOffRadius);

    // check if the cell index is valid
    for (size_t i = 0; i < N; ++i) {
        if (cellIndex[i] < 0 || cellIndex[i] >= numberOfCells[i]) {
            // if the cell index is invalid, return an empty vector
            return neighbourParticles;
        }
    }

    auto cell = getCell(cellIndex);

    // if the cell is not found, return an empty vector
    if (cell) {
        std::vector<std::array<int, N>> neighbourCellsIndex = cell->getNeighbourCellsIndex();

        // add the particles of the current cell
        for (const auto& p : cell->getParticles()) {
            if (p != particle) {
                neighbourParticles.push_back(p);
            }
        }

        // add the particles of the neighbour cells
        for (const auto& index : neighbourCellsIndex) {
            if (index == cellIndex) {
                continue; // Skip the current cell
            }

            auto neighbourCell = getCell(index);
            if (neighbourCell) {
                for (const auto& p : neighbourCell->getParticles()) {
                    if (p != particle) {
                        if (p->getDistance(*particle) < cutOffRadius) {
                            neighbourParticles.push_back(p);
                        }
                    }
                }
            }
        }
    }

    return neighbourParticles;
}


template <std::size_t N>
void Univers<N>::computeAllForcesOnParticle(float epsilon, float sigma, ForceType forceType) {
    Vecteur<N> currentForce;
    epsilon *= 24;
    for (const auto& particle : particles) {
        // save the previous force for all the particles before the calculation
        particle->saveForce(particle->getForce());
        particle->resetForce();
    }

    for(const auto& particle : particles) {
        // we search for the particle's neighbourhood
        std::vector<Particle<N>*> neighbourParticles = getParticlesInNeighbourhood(particle);
        for(const auto& neighbourParticle : neighbourParticles) {
            // for each particle in the neighbourhood, we compare ID to do the calculation only once
            if (particle->getId() < neighbourParticle->getId()) {
                currentForce = particle->optimizedGetAllForces(neighbourParticle, epsilon, sigma, forceType);
                particle->applyForce(currentForce);
                neighbourParticle->applyForce(-currentForce);
            }
        }
    }
}


template<>
void Univers<2>::computeAllForcesOnParticleANDGravitationalPotential(float epsilon, float sigma, ForceType forceType, double gravitationalConstant) {
    Vecteur<2> currentForce;
    epsilon *= 24;
    Vecteur<2> gravityForce({0, gravitationalConstant});
    for (const auto& particle : particles) {
        // save the previous force for all the particles before the calculation
        particle->saveForce(particle->getForce());
        particle->resetForce();

        // apply the gravitational force
        particle->applyForce(gravityForce);
    }

    for(const auto& particle : particles) {
        // we search for the particle's neighbourhood
        std::vector<Particle<2>*> neighbourParticles = getParticlesInNeighbourhood(particle);
        for(const auto& neighbourParticle : neighbourParticles) {
            // for each particle in the neighbourhood, we compare ID to do the calculation only once
            if (particle->getId() < neighbourParticle->getId()) {
                currentForce = particle->optimizedGetAllForces(neighbourParticle, epsilon, sigma, forceType);
                particle->applyForce(currentForce);
                neighbourParticle->applyForce(-currentForce);
            }
        }
    }

}


template <std::size_t N>
Vecteur<N> Univers<N>::applyReflectiveLimitConditions(Particle<N>* particle, const Vecteur<N>& newPosition) {
    constexpr double epsilon = 1e-10;  // Tolerance for floating point comparisons
    double margin = cutOffRadius / 10; // Small margin to avoid sticking to boundaries

    Vecteur<N> velocity = particle->getVelocity();
    Vecteur<N> reflectedPosition = newPosition;

    for (std::size_t i = 0; i < N; ++i) {
        double pos = newPosition.get(i);
        double L = caracteristicLength[i];

        if (pos <= 0.0 + epsilon) {
            // Near or at the lower/left boundary
            reflectedPosition.set(i, margin);
            velocity.set(i, -velocity.get(i) / 2);
        }
        else if (pos >= L - epsilon) {
            // Near or at the upper/right boundary
            reflectedPosition.set(i, L - margin);
            velocity.set(i, -velocity.get(i) / 2);
        }
        else if (pos < 0 || pos > L) {
            // Position is out of bounds, apply reflection
            double reflectedValue = pos < 0
                ? std::fmod(-pos, L)
                : L - std::fmod(pos - L, L);

            // Clamp reflected value to stay strictly inside the domain
            if (reflectedValue <= epsilon) reflectedValue = margin;
            else if (reflectedValue >= L - epsilon) reflectedValue = L - margin;

            reflectedPosition.set(i, reflectedValue);
            velocity.set(i, -velocity.get(i) / 2);
        }
    }

    particle->setVelocity(velocity);
    return reflectedPosition;
}


template <std::size_t N>
Vecteur<N> Univers<N>::applyPeriodicLimitConditions(Particle<N>* particle, const Vecteur<N>& newPosition) {
    Vecteur<N> periodicPosition = newPosition;
    for (std::size_t i = 0; i < N; ++i) {
        if (newPosition.get(i) < 0) {
            periodicPosition.set(i, caracteristicLength[i] + newPosition.get(i));
        }
        else if (newPosition.get(i) > caracteristicLength[i]) {
            periodicPosition.set(i, newPosition.get(i) - caracteristicLength[i]);
        }
    }
    return periodicPosition;
}

template<std::size_t N>
Vecteur<N> Univers<N>::applyAbsorbingLimitConditions(Particle<N>* particle, const Vecteur<N> &newPosition) {
    // determine if the new position is out of bounds
    // if not, throw an error
    for (std::size_t i = 0; i < N; ++i) {
        if (newPosition.get(i) < 0 || newPosition.get(i) > caracteristicLength[i]) {
            // delete the particle from the universe, and from the all the cells
            std::cout << "Particle " << particle->getId() << " is out of bounds, deleting it." << std::endl;
            auto cellIndex = particle->getCellIndexofParticle(cutOffRadius);
            auto cell = getCell(cellIndex);
            if (cell) {
                cell->removeParticle(particle);
            }
            // remove the particle from the list of particles
            auto it = std::remove(particles.begin(), particles.end(), particle);
            if (it != particles.end()) {
                particles.erase(it);
                --nbParticles;
            }
            // delete the particle
            delete particle;
            particle = nullptr; // Set the pointer to nullptr to avoid dangling pointer
            throw std::runtime_error("Particle is out of bounds and has been removed from the universe.");
        }
    }
    return newPosition;

}



template <std::size_t N>
void Univers<N>::update(double dt, float epsilon, float sigma, ForceType forceType, LimitConditions limitCondition) {

    std::function<Vecteur<N>(Particle<N>*, const Vecteur<N>&)> applyLimitConditions;

    // Initialiser la fonction en fonction de la condition choisie
    switch (limitCondition) {
        case LimitConditions::Reflective:
            applyLimitConditions = [this](Particle<N>* p, const Vecteur<N>& pos) {
                return applyReflectiveLimitConditions(p, pos);
        };
        break;
        case LimitConditions::Periodic:
            applyLimitConditions = [this](Particle<N>* p, const Vecteur<N>& pos) {
                return applyPeriodicLimitConditions(p, pos);
        };
        break;
        case LimitConditions::Absorbing:
            applyLimitConditions = [this](Particle<N>* p, const Vecteur<N>& pos) {
                return applyAbsorbingLimitConditions(p, pos);
        };
        break;
    }

    // we loop through the particles and update their position
    for (const auto& p : particles) {
        // update the position of the particle
        Vecteur<N> newPosition = p->getPosition() + p->getVelocity() * dt + (p->getForce() / p->getMass()) * (dt * dt) / 2;
        // update the cells configuration (of the original cells)
        try {
            newPosition = applyLimitConditions(p, newPosition);
        } catch (const std::runtime_error& e) {
            // delete the particle from the universe
            std::cout << e.what() << std::endl;
            break;
        }

        try {
            updateParticlePositionInCell(p, newPosition);
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            // stop the simulation or handle the error, return exit(1);
            p->showParticle();
            exit(1);
        }
        p->setPosition(newPosition);

    }
    computeAllForcesOnParticle(epsilon, sigma, forceType);

    for (const auto& p : particles) {
        // update the velocity of the particle
        Vecteur<N> newVelocity = p->getVelocity() + dt * 0.5/p->getMass() * (p->getForce() + p->getOldForce());
        p->setVelocity(newVelocity);
    }
}

template <std::size_t N>
void Univers<N>::showAllNeighbourhoods() const {
    for (const auto& particle : particles) {
        // get the corresponding cell
        std::cout << "==========================================" << std::endl;
        std::array<int, N> cellIndex = particle->getCellIndexofParticle(cutOffRadius);
        std::cout << "Particle " << particle->getId() << " in cell " << cellIndex[0] << ", " << cellIndex[1] << std::endl;
        Cell<N>* cell = getCell(cellIndex);
        if (cell) {
            // get the particles in the neighbourhood
            std::vector<Particle<N>*> neighbourParticles = getParticlesInNeighbourhood(particle);
            std::cout << "Neighbourhood of particle " << particle->getId() << ":" << std::endl;
            for (const auto& neighbourParticle : neighbourParticles) {
                std::cout << "Particle " << neighbourParticle->getId() << " in cell " << neighbourParticle->getCellIndexofParticle(cutOffRadius)[0] << ", " << neighbourParticle->getCellIndexofParticle(cutOffRadius)[1] << std::endl;
            }
        }
        else {
            std::cout << "Cell not found" << std::endl;
        }
        std::cout << "==========================================" << std::endl;
    }
}

template<std::size_t N>
void Univers<N>::showNeighbourhoodsOfParticle(int idOfParticle) const {
    Particle<N>* p = particles[idOfParticle];
    std::cout << "==========================================" << std::endl;
    std::array<int, N> cellIndex = p->getCellIndexofParticle(cutOffRadius);
    std::cout << "Particle " << p->getId() << " in cell " << cellIndex[0] << ", " << cellIndex[1] << std::endl;
    Cell<N>* cell = getCell(cellIndex);
    if (cell) {
        // get the particles in the neighbourhood
        std::vector<Particle<N>*> neighbourParticles = getParticlesInNeighbourhood(p);
        std::cout << "Neighbourhood of particle " << p->getId() << ":" << std::endl;
        for (const auto& neighbourParticle : neighbourParticles) {
            std::cout << "Particle " << neighbourParticle->getId() << " in cell " << neighbourParticle->getCellIndexofParticle(cutOffRadius)[0] << ", " << neighbourParticle->getCellIndexofParticle(cutOffRadius)[1] << std::endl;
        }
    }
    else {
        std::cout << "Cell not found" << std::endl;
    }

}


template <std::size_t N>
double Univers<N>::computeKineticEnergy() const {
    double totalKineticEnergy = 0.0;
    for (const auto& particle : particles) {
        double speed = particle->getVelocity().norm();
        double kineticEnergy = 0.5 * particle->getMass() * speed * speed;
        totalKineticEnergy += kineticEnergy;
    }
    return totalKineticEnergy;
}


template <std::size_t N>
void Univers<N>::updateKineticEnergy(double targetedKineticEnergy) {
    double currentKineticEnergy = computeKineticEnergy();
    double betaFactor = sqrt(targetedKineticEnergy / currentKineticEnergy);
    // update the velocity of the particles
    for (const auto& particle : particles) {
        Vecteur<N> newVelocity = particle->getVelocity() * betaFactor;
        particle->setVelocity(newVelocity);
    }
}


template <>
void Univers<2>::updateWithGravitationalPotential(double dt, float epsilon, float sigma, ForceType forceType, LimitConditions limitCondition, double gravitationalConstant) {

    std::function<Vecteur<2>(Particle<2>*, const Vecteur<2>&)> applyLimitConditions;

    // Initialiser la fonction en fonction de la condition choisie
    switch (limitCondition) {
        case LimitConditions::Reflective:
            applyLimitConditions = [this](Particle<2>* p, const Vecteur<2>& pos) {
                return applyReflectiveLimitConditions(p, pos);
        };
        break;
        case LimitConditions::Periodic:
            applyLimitConditions = [this](Particle<2>* p, const Vecteur<2>& pos) {
                return applyPeriodicLimitConditions(p, pos);
        };
        break;
        case LimitConditions::Absorbing:
            applyLimitConditions = [this](Particle<2>* p, const Vecteur<2>& pos) {
                return applyAbsorbingLimitConditions(p, pos);
        };
        break;
    }

    // we loop through the particles and update their position
    for (const auto& p : particles) {
        // update the position of the particle
        Vecteur<2> newPosition = p->getPosition() + p->getVelocity() * dt + (p->getForce() / p->getMass()) * (dt * dt) / 2;
        // update the cells configuration (of the original cells)
        try {
            newPosition = applyLimitConditions(p, newPosition);
        } catch (const std::runtime_error& e) {
            // delete the particle from the universe
            std::cout << e.what() << std::endl;
            break;
        }

        try {
            updateParticlePositionInCell(p, newPosition);
        } catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            // stop the simulation or handle the error, return exit(1);
            p->showParticle();
            exit(1);
        }
        p->setPosition(newPosition);

    }
    computeAllForcesOnParticleANDGravitationalPotential(epsilon, sigma, forceType, gravitationalConstant);

    for (const auto& p : particles) {
        // update the velocity of the particle
        Vecteur<2> newVelocity = p->getVelocity() + dt * 0.5/p->getMass() * (p->getForce() + p->getOldForce());
        p->setVelocity(newVelocity);
    }
}

