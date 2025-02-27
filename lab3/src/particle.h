//
// Created by audigiem on 13/02/25.
//

#ifndef CPP_PARTICLES_H
#define CPP_PARTICLES_H

/*
 * Class particle : a class to represent a particles
 * contains a position, a velocity, a mass, an identifier, a category (type)
 * and a force
 */
class Particle {

private:
    double position[3];
    double velocity[3];
    double mass;
    int id;
    int category;
    double force[3];

public:
    Particle(double position[3], double velocity[3], double mass, int id, int category);

    Particle();


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

    // determine the gravitational attraction force between two Particles
    double* findForce(Particle p);

};


#endif //CPP_PARTICLES_H
