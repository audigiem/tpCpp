#ifndef VECTEUR_HPP
#define VECTEUR_HPP

#include <iostream>
#include <cmath>
#include <array>

template <std::size_t N>
class Vecteur {
private:
    std::array<double, N> data;

public:
    Vecteur();
    Vecteur(const std::array<double, N>& values);
    Vecteur(const Vecteur& other);
    ~Vecteur();

    inline double get(std::size_t index) const {
        return data[index];
    }

    inline void set(std::size_t index, double value) {
        data[index] = value;
    }

    double norm() const;

    friend std::ostream& operator<<(std::ostream& os, const Vecteur<N>& v) {
        os << "(";
        for (std::size_t i = 0; i < N; ++i) {
            os << v.data[i];
            if (i < N - 1) {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }

    friend Vecteur<N> operator+(const Vecteur<N>& v1, const Vecteur<N>& v2) {
        Vecteur<N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = v1.data[i] + v2.data[i];
        }
        return result; // Rely on RVO
    }

    friend Vecteur<N>& operator+=(Vecteur<N>& v1, const Vecteur<N>& v2) {
        for (std::size_t i = 0; i < N; ++i) {
            v1.data[i] += v2.data[i];
        }
        return v1;
    }

    friend Vecteur<N> operator-(const Vecteur<N>& v1, const Vecteur<N>& v2) {
        Vecteur<N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = v1.data[i] - v2.data[i];
        }
        return result;
    }

    friend Vecteur<N> operator*(const Vecteur<N>& v1, const Vecteur<N>& v2) {
        Vecteur<N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = v1.data[i] * v2.data[i];
        }
        return result;
    }

    friend Vecteur<N> operator*(const Vecteur<N>& v, float f) {
        Vecteur<N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = v.data[i] * f;
        }
        return result;
    }

    friend Vecteur<N> operator*(float f, const Vecteur<N>& v) {
        return v * f;
    }

    friend Vecteur<N> operator/(const Vecteur<N>& v, double d) {
        Vecteur<N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = v.data[i] / d;
        }
        return result;
    }

    friend bool operator==(const Vecteur<N>& v1, const Vecteur<N>& v2) {
        for (std::size_t i = 0; i < N; ++i) {
            if (v1.data[i] != v2.data[i]) {
                return false;
            }
        }
        return true;
    }
};

#include "../src/vecteur.tpp"

#endif // VECTEUR_HPP