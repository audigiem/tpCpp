#ifndef PARTICLE_H
#define PARTICLE_H

#include <array>
#include <list>
#include <particle.hpp>
#include <memory>


template <std::size_t N>
class Cell {
private:
    std::list<std::shared_ptr<Particle<N>>> particles;

public:
    void addParticle(const std::shared_ptr<Particle<N>>& particle);
    bool isEmpty() const;
    void showParticles() const;
    std::list<std::shared_ptr<Particle<N>>> getParticles() const;
    void removeParticle(const std::shared_ptr<Particle<N>>& particle);


};

#include "cell.tpp"

#endif // PARTICLE_H