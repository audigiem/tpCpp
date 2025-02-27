//
// Created by audigiem on 20/02/25.
//

#ifndef CPP_VECTEUR_H
#define CPP_VECTEUR_H

#include <ostream>
#include <iostream>


/**
 * @brief Enable to manipulate a 3D vector
 */
class Vecteur {
private:
    double x;
    double y;
    double z;
public:
    Vecteur(double x, double y, double z);

    double getX() const;

    double getY() const;

    double getZ() const;

    void setX(double x);

    void setY(double y);

    void setZ(double z);

    Vecteur operator*=(const Vecteur &v2);

    Vecteur operator+=(const Vecteur &v2);

    Vecteur operator-=(const Vecteur &v2);



};

std::ostream &operator<<(std::ostream &out, const Vecteur &v);

// overload * operator for scalar product of two vectors
Vecteur operator*(const Vecteur &v1, const Vecteur &v2);

// cross product of two vectors with operator ^
Vecteur operator^(const Vecteur &v1, const Vecteur &v2);

Vecteur operator+(const Vecteur &v1, const Vecteur &v2);
Vecteur operator-(const Vecteur &v1, const Vecteur &v2);



#endif //CPP_VECTEUR_H
