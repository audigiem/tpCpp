/**
 * @file vecteur.hpp
 * @brief N-dimensional vector implementation with basic vector operations
 * @author Mattéo Audigier - Mattéo Gautier
 * @date 2025-05-19
 */

#ifndef VECTEUR_HPP
#define VECTEUR_HPP

#include <iostream>
#include <cmath>
#include <array>

/**
 * @class Vecteur
 * @brief A template class representing an N-dimensional mathematical vector
 * @tparam N The dimension of the vector (must be > 0)
 * 
 * This class provides basic vector operations like addition, subtraction,
 * scalar multiplication and division, as well as norm calculation.
 */
template <std::size_t N>
class Vecteur {
private:
    /** @brief Array containing the vector components */
    std::array<double, N> data;

public:
    /**
     * @brief Default constructor
     * @post Creates a zero vector (all components are 0)
     */
    Vecteur();
    
    /**
     * @brief Constructor from array of values
     * @param values Array of N double values representing vector components
     */
    Vecteur(const std::array<double, N>& values);
    
    /**
     * @brief Copy constructor
     * @param other Vector to copy
     */
    Vecteur(const Vecteur& other);
    
    /**
     * @brief Destructor
     */
    ~Vecteur();
    
    /**
     * @brief Assignment operator
     * @param other Vector to copy
     * @return Reference to this vector after assignment
     */
    Vecteur& operator=(const Vecteur& other);

    /**
     * @brief Get a component value
     * @param index Index of the component to retrieve (0-based)
     * @return Value of the component
     */
    inline double get(std::size_t index) const {
        return data[index];
    }

    /**
     * @brief Set a component value
     * @param index Index of the component to modify (0-based)
     * @param value New value for the component
     */
    inline void set(std::size_t index, double value) {
        data[index] = value;
    }

    /**
     * @brief Calculate the Euclidean norm (length) of the vector
     * @return The norm as a double
     */
    double norm() const;

    /**
     * @brief Stream insertion operator for printing vectors
     * @param os Output stream
     * @param v Vector to display
     * @return Reference to the output stream
     */
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

    /**
     * @brief Vector addition
     * @param v1 First vector
     * @param v2 Second vector
     * @return New vector representing the sum
     */
    friend Vecteur<N> operator+(const Vecteur<N>& v1, const Vecteur<N>& v2) {
        Vecteur<N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = v1.data[i] + v2.data[i];
        }
        return result;
    }

    /**
     * @brief Compound addition assignment
     * @param v1 Vector to modify
     * @param v2 Vector to add
     * @return Reference to the modified vector
     */
    friend Vecteur<N>& operator+=(Vecteur<N>& v1, const Vecteur<N>& v2) {
        for (std::size_t i = 0; i < N; ++i) {
            v1.data[i] += v2.data[i];
        }
        return v1;
    }

    /**
     * @brief Vector subtraction
     * @param v1 Vector to subtract from
     * @param v2 Vector to subtract
     * @return New vector representing the difference
     */
    friend Vecteur<N> operator-(const Vecteur<N>& v1, const Vecteur<N>& v2) {
        Vecteur<N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = v1.data[i] - v2.data[i];
        }
        return result;
    }

    /**
     * @brief Component-wise vector multiplication
     * @param v1 First vector
     * @param v2 Second vector
     * @return New vector with component-wise products
     */
    friend Vecteur<N> operator*(const Vecteur<N>& v1, const Vecteur<N>& v2) {
        Vecteur<N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = v1.data[i] * v2.data[i];
        }
        return result;
    }

    /**
     * @brief Scalar multiplication
     * @param v Vector to scale
     * @param f Scalar factor
     * @return New vector representing the scaled vector
     */
    friend Vecteur<N> operator*(const Vecteur<N>& v, float f) {
        Vecteur<N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = v.data[i] * f;
        }
        return result;
    }

    /**
     * @brief Scalar multiplication (commutative version)
     * @param f Scalar factor
     * @param v Vector to scale
     * @return New vector representing the scaled vector
     */
    friend Vecteur<N> operator*(float f, const Vecteur<N>& v) {
        return v * f;
    }

    /**
     * @brief Scalar division
     * @param v Vector to scale
     * @param d Scalar divisor
     * @return New vector representing the scaled vector
     */
    friend Vecteur<N> operator/(const Vecteur<N>& v, double d) {
        Vecteur<N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = v.data[i] / d;
        }
        return result;
    }

    /**
     * @brief Equality comparison
     * @param v1 First vector
     * @param v2 Second vector
     * @return True if all components are equal, false otherwise
     */
    friend bool operator==(const Vecteur<N>& v1, const Vecteur<N>& v2) {
        for (std::size_t i = 0; i < N; ++i) {
            if (v1.data[i] != v2.data[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Unary negation
     * @param v Vector to negate
     * @return New vector with all components negated
     */
    friend Vecteur<N> operator-(const Vecteur<N>& v) {
        Vecteur<N> result;
        for (std::size_t i = 0; i < N; ++i) {
            result.data[i] = -v.data[i];
        }
        return result;
    }
};

#include "../src/vecteur.tpp"

#endif // VECTEUR_HPP