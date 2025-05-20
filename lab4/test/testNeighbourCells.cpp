//
// Created by audigiem on 13/03/25.
//
#include "../include/univers.hpp"
#include "../include/VTKconverter.hpp"
#include "../include/particle.hpp"
#include "../include/vecteur.hpp"



/** test file to check if the method used to determine the neighborhoods
 * of each particle using cells is working and is correctly updated after each particle movement
**/
int main() {
    // initialize universe (square 10x10 with 4x4 cells)
    double caracteristicLength = 10;
    double cutOffRadius = 2.5;
    int nbCells = caracteristicLength / cutOffRadius;
    int nbParticlesInCell = 4;
    Univers<2> univ({caracteristicLength, caracteristicLength}, cutOffRadius);
    VTKconverter<2> converter("testNeighbourCells", "test");

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

    // univ.showUnivers();

    Particle<2>* p = univ.getParticles()[0];

    // show cell 0,0
    std::cout << "Cell 0,0" << std::endl;
    std::array<int, 2> cellIndex = {0, 0};
    Cell<2>* cell = univ.getCell(cellIndex);
    if (cell) {
        cell->showParticles();
    } else {
        std::cout << "Cell not found" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "We are going to move the particle 0 in cell 0,0 to cell 1,1" << std::endl;
    // now we move the particles 0 in cell 0,0 to cell 1,1
    Vecteur<2> newPos({1.5*cutOffRadius, 1.5*cutOffRadius});

    std::cout << "New position of particle 0: " << newPos << std::endl;

    // update the neighbourhoods
    univ.updateParticlePositionInCell(p, newPos);
    p->setPosition(newPos);

    std::cout << "New neighbourhoods of particle 0" << std::endl;
    // univ.showNeighbourhoodsOfParticle(0);

    // show cell 1,1
    std::cout << "Cell 1,1" << std::endl;
    cellIndex = {1, 1};
    cell = univ.getCell(cellIndex);
    if (cell) {
        cell->showParticles();
    } else {
        std::cout << "Cell not found" << std::endl;
    }





    return 0;
}