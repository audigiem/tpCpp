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
const std::unordered_map<std::array<int, N>, std::shared_ptr<Cell<N>>>& Univers<N>::getCells() const {
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
std::list<std::shared_ptr<Particle<N>>> Univers<N>::getParticles() const {
    std::list<std::shared_ptr<Particle<N>>> particles;
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
std::shared_ptr<Cell<N>> Univers<N>::getCell(const std::array<int, N>& cellIndex) const {
    auto it = cells.find(cellIndex);
    if (it != cells.end()) {
        return it->second;
    }
    return nullptr;
}


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
 */
template <std::size_t N>
void Univers<N>::updateParticlePositionInCell(const std::shared_ptr<Particle<N>>& particle, const Vecteur<N> &newPosition) {
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
        addParticle(std::make_shared<Particle<N>>(particle) );
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
std::list<std::shared_ptr<Particle<N>>> Univers<N>::getParticlesInNeighbourhood(const std::shared_ptr<Particle<N>>& particle) const {
    std::list<std::shared_ptr<Particle<N>>> neighbourParticles;
    std::array<int, N> centerCell = particle->getCellIndexofParticle(cellLength);

    // Calcul du nombre de couches de cellules à visiter dans chaque direction
    std::array<int, N> layers;
    for (std::size_t i = 0; i < N; ++i) {
        layers[i] = std::ceil(cutOffRadius / cellLength[i]);
    }

    // Générer les offsets dans l’hypercube [-layers[i], +layers[i]] pour chaque dimension
    std::vector<std::array<int, N>> offsets;

    std::function<void(std::array<int, N>&, int)> generateOffsets = [&](std::array<int, N>& current, int dim) {
        if (dim == N) {
            offsets.push_back(current);
            return;
        }
        for (int i = -layers[dim]; i <= layers[dim]; ++i) {
            current[dim] = centerCell[dim] + i;
            generateOffsets(current, dim + 1);
        }
    };

    std::array<int, N> currentOffset;
    generateOffsets(currentOffset, 0);

    // Parcours des cellules candidates
    for (const auto& offset : offsets) {
        auto it = cells.find(offset);
        if (it != cells.end()) {
            for (const auto& p : it->second->getParticles()) {
                if (p != particle && particle->getDistance(*p) < cutOffRadius) {
                    neighbourParticles.push_back(p);
                }
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
    std::list<Vecteur<N>> previousForcesOnParticles;
    for (const auto& cell : cells) {
        for (const auto& particle : cell.second->getParticles()) {
            particle->saveForce(particle->getForce());
            for (const auto& neighbour : getParticlesInNeighbourhood(particle)) {
                if (neighbour != particle) {
                    Vecteur<N> force = particle->optimizedGetAllForces(neighbour, epsilon, sigma);
                    particle->applyForce(force);
                }
            }
        }
    }
}


/** * @brief Clone the cells of the universe
 * @return A deep copy of the cells of the universe
 */
template<std::size_t N>
std::unordered_map<std::array<int, N>, std::shared_ptr<Cell<N> > > Univers<N>::cloneCells() const {
    std::unordered_map<std::array<int, N>, std::shared_ptr<Cell<N>>> clonedCells;
    for (const auto& [cellIndex, cell] : cells) {
        clonedCells[cellIndex] = std::make_shared<Cell<N>>(*cell);
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
    std::unordered_map<std::array<int, N>, std::shared_ptr<Cell<N>>> currentCells = cloneCells();
    // we loop through the particles and update their position
    for (const auto& cell : currentCells) {
        for (const auto& p : cell.second->getParticles()) {
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

    // std::cout << "End of update: " << std::endl;
    // showUnivers();



}

