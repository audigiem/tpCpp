#include "../include/univers.hpp"

template <std::size_t N>
Univers<N>::Univers(double caracteristicLength, double cutOffRadius)
    : caracteristicLength(caracteristicLength), cutOffRadius(cutOffRadius) {
    cellLength = static_cast<int>(std::ceil(caracteristicLength / cutOffRadius));
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

template <std::size_t N>
void Univers<N>::addParticle(const Particle<N>& particle) {
    std::array<int, N> cellIndex;
    for (std::size_t i = 0; i < N; ++i) {
        cellIndex[i] = static_cast<int>(std::floor(particle.getPosition().get(i) / cutOffRadius));
    }
    auto cell = getCell(cellIndex);
    if (!cell) {
        cell = std::make_shared<Cell<N>>();
        cells[cellIndex] = cell;
    }
    cell->addParticle(particle);
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
        Particle<N> particle;
        addParticle(particle);
    }
}

template <std::size_t N>
void Univers<N>::showUnivers() const {
    for (const auto& cell : cells) {
        std::cout << "Cell at index: ";
        for (const auto& index : cell.first) {
            std::cout << index << " ";
        }
        std::cout << std::endl;
        cell.second->showParticles();
    }
}

template <std::size_t N>
void Univers<N>::update(double dt) {
    for (auto& cell : cells) {
        for (auto& particle : cell.second->getParticles()) {
            Vecteur<N> force;
            for (const auto& otherCell : cells) {
                for (const auto& otherParticle : otherCell.second->getParticles()) {
                    if (particle.getId() != otherParticle.getId()) {
                        force = force + particle.optimizedGetAllForces(otherParticle, 24.0, 1.0);
                    }
                }
            }
            particle.applyForce(force);
        }
    }

    for (auto& cell : cells) {
        for (auto& particle : cell.second->getParticles()) {
            Vecteur<N> acceleration = particle.getForce() / particle.getMass();
            Vecteur<N> newVelocity = particle.getVelocity() + acceleration * dt;
            Vecteur<N> newPosition = particle.getPosition() + newVelocity * dt;
            particle.setPosition(newPosition);
            particle.setVelocity(newVelocity);
            particle.resetForce();
        }
    }

    removeEmptyCells();
}