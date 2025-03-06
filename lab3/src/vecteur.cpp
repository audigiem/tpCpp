//
// Created by audigiem on 20/02/25.
//

#include "../include/vecteur.h"

Vecteur::Vecteur(const double x, const double y, const double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

double Vecteur::getX() const {
    return x;
}

double Vecteur::getY() const {
    return y;
}

double Vecteur::getZ() const {
    return z;
}

void Vecteur::setX(double x) {
    this->x = x;
}

void Vecteur::setY(double y) {
    this->y = y;
}

void Vecteur::setZ(double z) {
    this->z = z;
}

double Vecteur::norm() const {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

std::ostream &operator<<(std::ostream &out, const Vecteur &v) {
    out << "x: " << v.getX() << " y: " << v.getY() << " z: " << v.getZ();
    return out;
}

Vecteur operator*(const Vecteur &v1, const Vecteur &v2) {
    return Vecteur(v1.getX() * v2.getX(), v1.getY() * v2.getY(), v1.getZ() * v2.getZ());
}

Vecteur operator+(const Vecteur &v1, const Vecteur &v2) {
    return Vecteur(v1.getX() + v2.getX(), v1.getY() + v2.getY(), v1.getZ() + v2.getZ());
}

Vecteur operator-(const Vecteur &v1, const Vecteur &v2) {
    return Vecteur(v1.getX() - v2.getX(), v1.getY() - v2.getY(), v1.getZ() - v2.getZ());
}

Vecteur Vecteur::operator*=(const Vecteur &v2) {
    this->x *= v2.getX();
    this->y *= v2.getY();
    this->z *= v2.getZ();
    return *this;
}

Vecteur Vecteur::operator+=(const Vecteur &v2) {
    this->x += v2.getX();
    this->y += v2.getY();
    this->z += v2.getZ();
    return *this;
}

Vecteur Vecteur::operator-=(const Vecteur &v2) {
    this->x -= v2.getX();
    this->y -= v2.getY();
    this->z -= v2.getZ();
    return *this;
}

Vecteur operator^(const Vecteur &v1, const Vecteur &v2) {
    return Vecteur(v1.getY() * v2.getZ() - v1.getZ() * v2.getY(),
                   v1.getZ() * v2.getX() - v1.getX() * v2.getZ(),
                   v1.getX() * v2.getY() - v1.getY() * v2.getX());
}

double Vecteur::distance(const Vecteur &v2) const {
    return sqrt(pow(v2.getX() - this->x, 2) + pow(v2.getY() - this->y, 2) + pow(v2.getZ() - this->z, 2));
}

Vecteur operator*(double scalar, const Vecteur &v) {
    return Vecteur(scalar * v.getX(), scalar * v.getY(), scalar * v.getZ());
}

