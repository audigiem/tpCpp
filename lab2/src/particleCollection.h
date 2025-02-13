//
// Created by audigiem on 13/02/25.
//

#ifndef LAB2_PARTICLECOLLECTION_H
#define LAB2_PARTICLECOLLECTION_H

#include "particle.h"
#include<set>
#include<list>
#include<deque>
#include<vector>

class particleCollection {
private:
//    std::set<particle> particleSet;
    std::list<particle> particleList;
    std::deque<particle> particleDeque;
    std::vector<particle> particleVector;

public:
    explicit particleCollection(int nbElem);

    ~particleCollection();

//    std::set<particle> get_particleSet();

    std::list<particle> get_particleList();

    std::deque<particle> get_particleDeque();

    std::vector<particle> get_particleVector();

    // methods to compare performance (insert, erase, find, iterate) of different containers
    // once the particleCollection is filled with particles
    // we use chrono bibliotheca to measure time
    void compareIteration();

    void compareInsertion();

    // method to determine the movement of particles
    // depending on the force applied to them
    std::vector<double[3]> stromerVerlet(float dt, float tEnd);

    void computeForce();

};


#endif //LAB2_PARTICLECOLLECTION_H
