#include "../include/univers.hpp"
#include <functional>

template <std::size_t N>
Univers<N>::Univers(std::array<double, N> caracteristicLength, double cutOffRadius)
    : caracteristicLength(caracteristicLength), cutOffRadius(cutOffRadius) {
    for (std::size_t i = 0; i < N; ++i) {
        cellLength[i] = static_cast<int>(std::ceil(caracteristicLength[i] / cutOffRadius));
    }
    nbParticles = 0;
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
const std::unordered_map<std::array<int, N>, Cell<N>*>& Univers<N>::getCells() const {
    return cells;
}

template <std::size_t N>
std::array<int, N> Univers<N>::getCellLength() const {
    return cellLength;
}

template <std::size_t N>
int Univers<N>::getNbParticles() const {
    return nbParticles;
}

template <std::size_t N>
std::list<Particle<N>*> Univers<N>::getParticles() const {
    std::list<Particle<N>*> particles;
    for (const auto& cell : cells) {
        auto cellParticles = cell.second->getParticles();
        particles.insert(particles.end(), cellParticles.begin(), cellParticles.end());
    }
    return particles;
}


template <std::size_t N>
void Univers<N>::setCaracteristicLength(std::array<double, N> caracteristicLength) {
    for (std::size_t i = 0; i < N; ++i) {
        cellLength[i] = static_cast<int>(std::ceil(caracteristicLength[i] / cutOffRadius));
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
std::vector<Cell<N> *> Univers<N>::getCoordNeighbourCells(const std::array<int, N>& cellIndex) const {
    std::vector<Cell<N>*> neighbourCells;
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


template <std::size_t N>
void Univers<N>::addParticle(Particle<N>*& particle) {
    std::array<int, N> cellIndex;
    for (std::size_t i = 0; i < N; ++i) {
        cellIndex[i] = static_cast<int>(std::floor(particle->getPosition().get(i) / cutOffRadius));
    }
    auto cell = getCell(cellIndex);
    if (!cell) {
        cell = new Cell<N>();
        cells[cellIndex] = cell;
    }
    cell->addParticle(particle);
    ++nbParticles;
}


/** * @brief Update the cells configuration according to the new position of the particle
 * IMPORTANT: This function does not update the particle position in the cell, it only updates the cells configuration
 * @param particle The particle to update
 * @param newPosition The new position of the particle
 */
template <std::size_t N>
void Univers<N>::updateParticlePositionInCell(Particle<N>*& particle, const Vecteur<N> &newPosition) {
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
            newCell = new Cell<N>();
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
        Particle<N>* particle = new Particle<N>(i, position, velocity, 1.0, "default");
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


/** * @brief Get the particles in the neighbourhood of a particle
 * this includes the particles in the same cell and the particles in the neighbouring cells
 * @param particle The particle to get the neighbourhood of
 * @return A list of particles in the neighbourhood of the particle
 */
template <std::size_t N>
std::list<Particle<N>*> Univers<N>::getParticlesInNeighbourhood(Particle<N>*& particle) const {
    std::list<Particle<N>*> neighbourParticles;

    // Get the cell of the particle
    std::array<int, N> cellIndex = particle->getCellIndexofParticle(cellLength);
    auto cell = getCell(cellIndex);

    // Get the neighbouring cells
    for(auto & neighbourCell : getNeighbourCells(cellIndex)) {
        auto particlesInCell = neighbourCell->getParticles();
        neighbourParticles.insert(neighbourParticles.end(), particlesInCell.begin(), particlesInCell.end());
    }

    if (cell) {
        // Add the particles in the same cell, excluding the particle itself
        for (auto& p : cell->getParticles()) {
            if (p != particle) {
                neighbourParticles.push_back(p);
            }
        }
    }

    return neighbourParticles;
}


/**
* @brief Compute all the forces applied on each particle and store it in each particle
* !! this function overloads the forces already stored in the particle !!
* and saves the previous forces in the particle
 * we consider only the particles in the neighbourhood of the particle
 */
template <std::size_t N>
void Univers<N>::computeAllForcesOnParticle(float epsilon, float sigma) {
    for(const auto& particle : particles) {
        for(const auto& neighbourParticle : getParticlesInNeighbourhood(particle)) {
            particle->applyForce(neighbourParticle->optimizedGetAllForces(neighbourParticle, epsilon, sigma));
        }
    }
}

/** * @brief Clone the cells of the universe
 * @return A deep copy of the cells of the universe
 */
template<std::size_t N>
std::unordered_map<std::array<int, N>, Cell<N>* > Univers<N>::cloneCells() const {
    std::unordered_map<std::array<int, N>, Cell<N>*> clonedCells;
    for (const auto& [cellIndex, cell] : cells) {
        clonedCells[cellIndex] = new Cell<N>(*cell); // Deep copy of the cell
    }
    return clonedCells;
}




template <std::size_t N>
void Univers<N>::update(double dt, float epsilon, float sigma) {
    // std::cout << "Updating universe..." << std::endl;
    // showUnivers();

    // during the iterations, we will move particles and therefore modify the configuration
    // of the cells as particle will move in and out of them.
    // Consequently, we will iterate over a (deep) copy of the initial cells that will not be modified
    std::unordered_map<std::array<int, N>, Cell<N>*> currentCells = cloneCells();
    // we loop through the particles and update their position
    for (const auto& cell : currentCells) {
        for (auto& p : cell.second->getParticles()) {
            // update the position of the particle
            Vecteur<N> newPosition = p->getPosition() + p->getVelocity() * dt + (p->getForce() / p->getMass()) * (dt * dt) / 2;
            // update the cells configuration (of the original cells)
            updateParticlePositionInCell(p, newPosition);
            p->setPosition(newPosition);
            // p->showParticle();
            // std::cout << "is supposed to move to " << newPosition << std::endl;
            // showUnivers();

            // dont need to save the old forces as we have done it first line and they havent changed
            // we do it anyway to be sure
            p->saveForce(p->getForce());
        }
    }
    computeAllForcesOnParticle(epsilon, sigma);
    for (const auto& cell : currentCells) {
        for (const auto& p : cell.second->getParticles()) {
            // update the velocity of the particle
            Vecteur<N> newVelocity = p->getVelocity() + dt * 0.5/p->getMass() * (p->getForce() + p->getOldForce());
            p->setVelocity(newVelocity);
        }
    }
    removeEmptyCells();
    for (auto& [_, cellPtr] : currentCells) {
        delete cellPtr;
    }

    // std::cout << "End of update: " << std::endl;
    // showUnivers();



}

