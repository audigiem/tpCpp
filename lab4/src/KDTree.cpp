//
// Created by matteo on 09/04/25.
//


#include "../include/KDTree.h"
#include <iostream>
#include <numeric>

template <std::size_t N>
KDTree<N>::KDTree() : root(nullptr), particles(nullptr) {}

template <std::size_t N>
KDTree<N>::KDTree(const std::vector<Particle<N>*>& particles)
    : particles(particles) {
    std::vector<size_t> indices(particles.size());
    std::iota(indices.begin(), indices.end(), 0); // Fill indices with 0, 1, ..., particles.size() - 1
    root = buildTree(indices, 0);
}

template <std::size_t N>
KDTree<N>::~KDTree() {
    freeTree(root);
}

template <std::size_t N>
void KDTree<N>::freeTree(const std::unique_ptr<KdNode<N>>& node) {
    if (node) {
        freeTree(node->left);
        freeTree(node->right);
    }

}

template <std::size_t N>
std::unique_ptr<KdNode<N>> KDTree<N>::buildTree(std::vector<size_t>& indices, int depth) {
    if (indices.empty()) return nullptr;

    int axis = depth % N;
    std::sort(indices.begin(), indices.end(), [&](size_t a, size_t b) {
        return particles[a]->getPosition().get(axis) < particles[b]->getPosition().get(axis);
    });

    size_t mid = indices.size() / 2;
    std::unique_ptr<KdNode<N>> node = std::make_unique<KdNode<N>>();
    node->axis = axis;
    node->particleIndex = indices[mid];

    std::vector<size_t> left(indices.begin(), indices.begin() + mid);
    std::vector<size_t> right(indices.begin() + mid + 1, indices.end());

    node->left = buildTree(left, depth + 1);
    node->right = buildTree(right, depth + 1);

    return node;
}


template <std::size_t N>
void KDTree<N>::showNode(const std::unique_ptr<KdNode<N>>& node) {
    if (!node) {
        return;
    }

    std::cout << "Node axis: " << node->axis << ", Particle ID: " << particles[node->particleIndex]->getId() << std::endl;
    showNode(node->left);
    showNode(node->right);
}

template <std::size_t N>
void KDTree<N>::showTree() {
    std::cout << "KDTree:" << std::endl;
    showNode(root);
    std::cout << "End of KDTree" << std::endl;

}

template <std::size_t N>
void KDTree<N>::searchInRadius(const std::unique_ptr<KdNode<N>>& node,
                               Particle<N>* target,
                               float radius,
                               std::vector<Particle<N>*> rawParticles) const {
    if (!node) return;

    float dist = target->getDistance(node->particle);
    if (dist <= radius) {
        rawParticles.push_back(node->particle);
    }

    int axis = node->axis;
    float diff = target->position()[axis] - node->particle->position()[axis];

    // Choisir l'enfant à visiter en premier (optimisation)
    const auto& first = diff < 0 ? node->left : node->right;
    const auto& second = diff < 0 ? node->right : node->left;

    // Rechercher dans le sous-arbre principal
    searchInRadius(first, target, radius, rawParticles);

    // Vérifie si on doit aussi explorer l'autre sous-arbre
    if (std::abs(diff) <= radius) {
        searchInRadius(second, target, radius, rawParticles);
    }
}


template <std::size_t N>
void KDTree<N>::insert(Particle<N>* particle) {
    insertNode(root, particle, 0);
}

template <std::size_t N>
void KDTree<N>::insertNode(const std::unique_ptr<KdNode<N>>& node, Particle<N>* particle, int depth) {
    if (!node) {
        node = std::make_unique<KdNode<N>>();
        node->particle = particle;
        node->axis = depth % N;
        return;
    }

    int axis = node->axis;
    if (particle->getPosition().get(axis) < node->particle->getPosition().get(axis)) {
        insertNode(node->left, particle, depth + 1);
    } else {
        insertNode(node->right, particle, depth + 1);
    }
}


template <std::size_t N>
void KDTree<N>::remove(Particle<N>* particle) {
    removeNode(root, particle, 0);
}

template <std::size_t N>
void KDTree<N>::removeNode(const std::unique_ptr<KdNode<N>>& node, Particle<N>* particle, int depth) {
    if (!node) return;

    if (node->particle == particle) {
        // Handle removal logic here
        // For simplicity, we will just set the node to nullptr
        node->particle = nullptr;
        return;
    }

    int axis = depth % N;
    if (particle->getPosition().get(axis) < node->particle->getPosition().get(axis)) {
        removeNode(node->left, particle, depth + 1);
    } else {
        removeNode(node->right, particle, depth + 1);
    }
}

template <std::size_t N>
std::unique_ptr<KdNode<N>> KDTree<N>::getRoot() const {
    return root;
}

template <std::size_t N>
void KDTree<N>::updateParticlePosition(Particle<N>* particle) {
    // Update the position of the particle in the KDTree
    remove(particle);
    insert(particle);
}


template <std::size_t N>
std::vector<Particle<N>*> KDTree<N>::queryRadius(Particle<N>* target, float radius) const {
    std::vector<Particle<N>*> results;
    searchInRadius(root, target, radius, results);
    return results;
}