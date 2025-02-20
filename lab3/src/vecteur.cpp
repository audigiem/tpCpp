//
// Created by audigiem on 20/02/25.
//

#include "vecteur.h"

vecteur::vecteur(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

double vecteur::getX() const {
    return x;
}

double vecteur::getY() const {
    return y;
}

double vecteur::getZ() const {
    return z;
}

void vecteur::setX(double x) {
    this->x = x;
}

void vecteur::setY(double y) {
    this->y = y;
}

void vecteur::setZ(double z) {
    this->z = z;
}

std::ostream &operator<<(std::ostream &out, const vecteur &v) {
    out << "x: " << v.getX() << " y: " << v.getY() << " z: " << v.getZ();
    return out;
}