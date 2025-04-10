/**
 * @file KDTree.h
 * @brief Header file for KDTree class.
 * @details This class implements a KDTree for efficient nearest neighbor search.
 * @author matteo AUDIGIER
 * @date 2023-10-01
 */

#ifndef KDTREE_H
#define KDTREE_H

#include "particle.hpp"
#include <vector>


template <std::size_t N>
struct KdNode {
    Particle<N>* particle;
    int axis;
    std::unique_ptr<KdNode<N>> left;
    std::unique_ptr<KdNode<N>> right;
};



template <std::size_t N>
class KDTree {
private:
    std::unique_ptr<KdNode<N>> root;
    std::vector<Particle<N>*>* particles;
    std::unique_ptr<KdNode<N>> buildTree(std::vector<size_t>& indices, int depth);
    void searchInRadius(const std::unique_ptr<KdNode<N>>& node, Particle<N>* target,
                         float radius, std::vector<Particle<N>*> rawParticles) const;
public:
    KDTree();
    explicit KDTree(const std::vector<Particle<N>*>& rawParticles);
    ~KDTree();

    void freeTree(const std::unique_ptr<KdNode<N>>& node);
    std::unique_ptr<KdNode<N>> getRoot() const;

    std::vector<Particle<N>*> queryRadius(Particle<N>* target, float radius) const;

    void insert(Particle<N>* particle);
    void insertNode(const std::unique_ptr<KdNode<N>>& node, Particle<N>* particle, int depth);
    void remove(Particle<N>* particle);
    void removeNode(const std::unique_ptr<KdNode<N>>& node, Particle<N>* particle, int depth);

    void updateParticlePosition(Particle<N>* particle);

    void showTree();
    void showNode(const std::unique_ptr<KdNode<N>>& node);

};

#include "../src/KDTree.cpp"

#endif //KDTREE_H
