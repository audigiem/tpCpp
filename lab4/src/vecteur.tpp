#include "../include/vecteur.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

template <std::size_t N>
Vecteur<N>::Vecteur() {
    static_assert(N > 0, "Vecteur must have at least one dimension");
    data.fill(0.0);
}

template <std::size_t N>
Vecteur<N>::Vecteur(const std::array<double, N>& values) : data(values) {
    static_assert(N > 0, "Vecteur must have at least one dimension");
}

template <std::size_t N>
Vecteur<N>::Vecteur(const Vecteur& other) : data(other.data) {
    static_assert(N > 0, "Vecteur must have at least one dimension");
}

template <std::size_t N>
Vecteur<N>::~Vecteur() {}

template <std::size_t N>
double Vecteur<N>::get(std::size_t index) const {
    if (index >= N) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template <std::size_t N>
void Vecteur<N>::set(std::size_t index, double value) {
    if (index >= N) {
        throw std::out_of_range("Index out of bounds");
    }
    data[index] = value;
}

template <std::size_t N>
double Vecteur<N>::norm() const {
    double sum = 0.0;
    for (const auto& value : data) {
        sum += value * value;
    }
    return std::sqrt(sum);
}