//
// Created by audigiem on 13/02/25.
//

#ifndef LAB2_PARTICLES_H
#define LAB2_PARTICLES_H

/*
 * Class particle : a class to represent a particles
 * contains a position, a velocity, a mass, an identifier, a category (type)
 * and a force
 */
class particle {

private:
    double position[3];
    double velocity[3];
    double mass;
    int id;
    int category;
    double force[3];

public:
    particle(double position[3], double velocity[3], double mass, int id, int category);

    particle();


    void set_position(double position[3]);

    void set_velocity(double velocity[3]);

    void set_mass(double mass);

    void set_id(int id);

    void set_category(int category);

    void set_force(double force[3]);

    double* get_position();

    double* get_velocity();

    double get_mass();

    int get_id();

    int get_category();

    double* get_force();

};


#endif //LAB2_PARTICLES_H
