#include "../include/univers.hpp"

template <std::size_t N>
Univers<N>::Univers(double caracteristicLength, double cutOffRadius)
    : caracteristicLength(caracteristicLength), cutOffRadius(cutOffRadius) {
    cellLength = static_cast<int>(std::ceil(caracteristicLength / cutOffRadius));
    nbParticles = 0;
}

template <std::size_t N>
double Univers<N>::getCaracteristicLength() const {
    return caracteristicLength;
}

template <std::size_t N>
double Univers<N>::getCutOffRadius() const {
    return cutOffRadius;
}

template <std::size_t N>
const std::unordered_map<std::array<int, N>, std::shared_ptr<Cell<N>>>& Univers<N>::getCells() const {
    return cells;
}

template <std::size_t N>
int Univers<N>::getCellLength() const {
    return cellLength;
}

template <std::size_t N>
int Univers<N>::getNbParticles() const {
    return nbParticles;
}

template <std::size_t N>
std::list<std::shared_ptr<Particle<N>>> Univers<N>::getParticles() const {
    std::list<std::shared_ptr<Particle<N>>> particles;
    for (const auto& cell : cells) {
        auto cellParticles = cell.second->getParticles();
        particles.insert(particles.end(), cellParticles.begin(), cellParticles.end());
    }
    return particles;
}


template <std::size_t N>
void Univers<N>::setCaracteristicLength(double caracteristicLength) {
    this->caracteristicLength = caracteristicLength;
}

template <std::size_t N>
void Univers<N>::setCutOffRadius(double cutOffRadius) {
    this->cutOffRadius = cutOffRadius;
}

template <std::size_t N>
std::shared_ptr<Cell<N>> Univers<N>::getCell(const std::array<int, N>& cellIndex) const {
    auto it = cells.find(cellIndex);
    if (it != cells.end()) {
        return it->second;
    }
    return nullptr;
}

/**
template <std::size_t N>
std::vector<std::shared_ptr<Cell<N>>> Univers<N>::getCoordNeighbourCells(const std::array<int, N>& cellIndex) const {
    std::vector<std::shared_ptr<Cell<N>>> neighbourCells;
    std::array<int, N> neighbourIndex;
    for (std::size_t i = 0; i < N; ++i) {
        for (int j = -1; j <= 1; ++j) {
            neighbourIndex[i] = cellIndex[i] + j;
            auto cell = getCell(neighbourIndex);
            if (cell) {
                neighbourCells.push_back(cell);
            }
        }
    }
    return neighbourCells;
}
*/

template <std::size_t N>
void Univers<N>::addParticle(const std::shared_ptr<Particle<N>>& particle) {
    std::array<int, N> cellIndex;
    for (std::size_t i = 0; i < N; ++i) {
        cellIndex[i] = static_cast<int>(std::floor(particle->getPosition().get(i) / cutOffRadius));
    }
    auto cell = getCell(cellIndex);
    if (!cell) {
        cell = std::make_shared<Cell<N>>();
        cells[cellIndex] = cell;
    }
    cell->addParticle(particle);
    ++nbParticles;
}


/** * @brief Update the cells configuration according to the new position of the particle
 * IMPORTANT: This function does not update the particle position in the cell, it only updates the cells configuration
 * @param particle The particle to update
 * @param newPosition The new position of the particle
 * @param newVelocity The new velocity of the particle
 */
template <std::size_t N>
void Univers<N>::updateParticlePositionInCell(const std::shared_ptr<Particle<N>>& particle, const Vecteur<N> &newPosition,
                                              const Vecteur<N> &newVelocity) {
    std::array<int, N> oldCellIndex;
    for (std::size_t i = 0; i < N; ++i) {
        oldCellIndex[i] = static_cast<int>(std::floor(particle->getPosition().get(i) / cutOffRadius));
    }
    std::array<int, N> newCellIndex;
    for (std::size_t i = 0; i < N; ++i) {
        newCellIndex[i] = static_cast<int>(std::floor(newPosition.get(i) / cutOffRadius));
    }
    if (oldCellIndex != newCellIndex) {
        auto oldCell = getCell(oldCellIndex);
        auto newCell = getCell(newCellIndex);
        // remove the particle from the old cell and add it to the new cell
        if (oldCell) {
            oldCell->removeParticle(particle);
        }
        if (!newCell) {
            newCell = std::make_shared<Cell<N>>();
            cells[newCellIndex] = newCell;
        }
        newCell->addParticle(particle);
    }
}


template <std::size_t N>
void Univers<N>::removeEmptyCells() {
    for (auto it = cells.begin(); it != cells.end();) {
        if (it->second->isEmpty()) {
            it = cells.erase(it);
        } else {
            ++it;
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
        Particle<N> particle(i, position, velocity, 1.0, "default");
        addParticle(particle);
    }
}

template <std::size_t N>
void Univers<N>::showUnivers() const {
    std::cout << "========== Univers ==========" << std::endl;
    for (const auto& cell : cells) {
        std::cout << "Cell at index: ";
        for (const auto& index : cell.first) {
            std::cout << index << " ";
        }
        std::cout << std::endl;
        cell.second->showParticles();
    }
    std::cout << "=============================" << std::endl;
}

template <std::size_t N>
void Univers<N>::update(double dt) {
    for (const auto& cell : cells) {
        // we look up for each particle in the neighbouring cells that are at a distance less than cutOffRadius
        for (const auto& particle : cell.second->getParticles()) {
            for (auto& otherParticle : cell.second->getParticles()) {
                if ((particle->getId() != otherParticle->getId()) and (particle->getPosition() - otherParticle->getPosition()).norm() < cutOffRadius) {
                    Vecteur<N> force = particle->getAllForces(otherParticle, 1.0, 1.0);
                    otherParticle->applyForce(force);
                }
            }
        }
    }

    for (const auto& cell : cells) {
        for (auto& particle : cell.second->getParticles()) {
            Vecteur<N> acceleration = particle->getForce() / particle->getMass();
            Vecteur<N> newVelocity = particle->getVelocity() + acceleration * dt;
            Vecteur<N> newPosition = particle->getPosition() + newVelocity * dt;
            // update particle position and velocity and modify the hashmap cells
            updateParticlePositionInCell(particle, newPosition, newVelocity);
            particle->setPosition(newPosition);
            particle->setVelocity(newVelocity);
        }
    }

    removeEmptyCells();
}