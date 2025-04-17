#include "../include/univers.hpp"
#include <functional>

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
Univers<N>::~Univers() {
    // // Libérer la mémoire des particules
    // for (auto& particle : particles) {
    //     delete particle;
    // }
    // // Libérer la mémoire des cellules
    // for (auto& cell : cells) {
    //     delete cell.second;
    // }
    // cells.clear();
    // particles.clear();
}



/** * @brief Generate all the coordinates of the N-dimensional grid
 * @param gridSizePerDimension The size of the grid in each dimension
 */
template <std::size_t N>
std::vector<std::array<int, N>> generateAllGridCoordinates(const std::array<int, N>& gridSizePerDimension) {
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


/** * @brief Create the cells of the universe
 * This function creates the cells of the universe and initializes them
 * by computing their neighbours.
 * The cells are generated in a N-dimensional grid.
 * The cells are stored in a hash map with their index as key.
 *
 * In dimension 1 with M cells, the cells are generated from 0 to M-1.
 * In dimension 2 with M1 and M2 cells, the cells are generated from (0,0), to (M1-1,0), (0,1), (M1-1,1), ..., (M1-1,M2-1).
 */
template <std::size_t N>
void Univers<N>::createCells() {
    std::vector<std::array<int, N>> allCellsIndex = generateAllGridCoordinates(numberOfCells);
    for (const auto& index : allCellsIndex) {
        auto* cell = new Cell<N>(index, caracteristicLength, cutOffRadius);
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


/** * @brief Add a particle to the universe and to the corresponding cell
 * This function adds a particle to the universe and updates the cell configuration
 * @param particle The particle to add
 */
template <std::size_t N>
void Univers<N>::addParticle(Particle<N>*& particle) {
    std::array<int, N> cellIndex;
    cellIndex = particle->getCellIndexofParticle(cutOffRadius);
    auto cell = getCell(cellIndex);
    cell->addParticle(particle);
    // add the particle to the list of particles
    particles.push_back(particle);
    ++nbParticles;
}


/** * @brief Update the cells configuration according to the new position of the particle
 * IMPORTANT: This function does not update the particle position in the cell, it only updates the cells configuration
 * @param particle The particle to update
 * @param newPosition The new position of the particle
 */
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
            // std::cout << "No limit conditions, so the particle is out of the universe" << std::endl;
            // we remove the particle from the universe
            auto it = std::remove(particles.begin(), particles.end(), particle);
            if (it != particles.end()) {
                particles.erase(it, particles.end());
                --nbParticles;
            }
            // we remove the particle from the cells
            for (const auto& cell : cells) {
                cell.second->removeParticle(particle);
            }
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


/** * @brief Get the particles in the neighbourhood of a particle
 * this includes the particles in the same cell and the particles in the neighbouring cells
 * @param particle The particle to get the neighbourhood of
 * @return A list of particles in the neighbourhood of the particle
 */
template <std::size_t N>
std::vector<Particle<N>*> Univers<N>::getParticlesInNeighbourhood(Particle<N>* particle) const {
    std::vector<Particle<N>*> neighbourParticles;

    // Get the cell of the particle
    std::array<int, N> cellIndex = particle->getCellIndexofParticle(cutOffRadius);

    // Vérification que l'indice de la cellule est dans les limites valides
    for (int i = 0; i < N; ++i) {
        if (cellIndex[i] < 0 || cellIndex[i] >= numberOfCells[i]) {
            // Si un des indices est hors limites, on gère l'erreur (retourner un tableau vide ou autre)
            return neighbourParticles;
        }
    }

    // Si l'indice est valide, on récupère la cellule
    auto cell = getCell(cellIndex);

    // Si la cellule est valide (non nullptr)
    if (cell) {
        // On ajoute les particules de la même cellule
        for (const auto& p : cell->getParticles()) {
            if (p != particle) {
                neighbourParticles.push_back(p);
            }
        }

        // On ajoute les particules des cellules voisines
        std::vector<std::array<int, N>> neighbourCellsIndex = cell->getNeighbourCellsIndex();
        for (const auto& index : neighbourCellsIndex) {
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

template <std::size_t N>
void Univers<N>::update(double dt, float epsilon, float sigma) {
    // std::cout << "Updating universe..." << std::endl;
    // showUnivers();

    // we loop through the particles and update their position
    for (const auto& p : particles) {
        // update the position of the particle
        Vecteur<N> newPosition = p->getPosition() + p->getVelocity() * dt + (p->getForce() / p->getMass()) * (dt * dt) / 2;
        // update the cells configuration (of the original cells)
        updateParticlePositionInCell(p, newPosition);
        p->setPosition(newPosition);
        // p->showParticle();
        // std::cout << "is supposed to move to " << newPosition << std::endl;
        // showUnivers();


    }
    computeAllForcesOnParticle(epsilon, sigma);

    for (const auto& p : particles) {
        // update the velocity of the particle
        Vecteur<N> newVelocity = p->getVelocity() + dt * 0.5/p->getMass() * (p->getForce() + p->getOldForce());
        p->setVelocity(newVelocity);
    }



    // std::cout << "End of update: " << std::endl;
    // showUnivers();



}

