//
// Created by audigiem on 20/02/25.
//

#ifndef CPP_VECTEUR_H
#define CPP_VECTEUR_H

#include <ostream>


/**
 * @brief Enable to manipulate a 3D vector
 */
class vecteur {
private:
    double x;
    double y;
    double z;
public:
    vecteur(double x, double y, double z);

    double getX() const;

    double getY() const;

    double getZ() const;

    void setX(double x);

    void setY(double y);

    void setZ(double z);

};

std::ostream &operator<<(std::ostream &out, const vecteur &v);


#endif //CPP_VECTEUR_H
