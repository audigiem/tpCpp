//
// Created by audigiem on 20/02/25.
//

#include "vecteur.h"

Vecteur::Vecteur(double x, double y, double z) {
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

