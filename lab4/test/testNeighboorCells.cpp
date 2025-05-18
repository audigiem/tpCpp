//
// Created by audigiem on 13/03/25.
//
#include "../include/univers.hpp"
#include "../include/VTKconverter.hpp"
#include "../include/particle.hpp"
#include "../include/vecteur.hpp"



/** test file to check if the method used to determine the neighborhoods
 * of each particle using cells is working and is correctly updated after each paricles movement
**/
int main() {
    // initialize universe (square 10x10 with 4x4 cells)
    double caracteristicLength = 10;
    double cutOffRadius = 2.5;
    int nbCells = caracteristicLength / cutOffRadius;
    int nbParticlesInCell = 4;
    Univers<2> univ({caracteristicLength, caracteristicLength}, cutOffRadius);
    VTKconverter<2> converter("testNeighboorCells", "test");

    int nbParticles = 0;
    for (int i=0; i<nbCells; i++) {
        for (int j=0; j<nbCells; j++) {
            for (int k=0; k<nbParticlesInCell; k++) {
                // add a particle in Cell i,j
                double x = i*cutOffRadius + (k+0.5)*cutOffRadius/nbParticlesInCell;
                double y = j*cutOffRadius + (k+0.5)*cutOffRadius/nbParticlesInCell;
                Vecteur<2> position({x, y});
                Particle<2>* particle = new Particle<2>(nbParticles, position, Vecteur<2>({0, 0}), 1.0, "default");
                try {
                    univ.addParticle(particle);
                    nbParticles++;
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    // stop the simulation or handle the error, return exit(1);
                    exit(1);
                }
            }
        }
    }

    converter.createFile();
    converter.convertToVTK(univ);
    converter.closeFile();

    Particle<2>* p = univ.getParticles()[0];

    // show the neighbourhood
    univ.showNeighbourhoodsOfParticle(0);


    // now we move the particles 0 in cell 0,0 to cell 1,1
    Vecteur<2> newPos({1.5*cutOffRadius, 1.5*cutOffRadius});

    // update the neighbourhoods
    univ.updateParticlePositionInCell(p, newPos);
    p->setPosition(newPos);

    univ.showNeighbourhoodsOfParticle(0);





    return 0;
}