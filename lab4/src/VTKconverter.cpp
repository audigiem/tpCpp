//
// Created by matteo on 01/04/25.
//

#include "../include/VTKconverter.hpp"
#include <iostream>

template <std::size_t N>
VTKconverter<N>::VTKconverter(std::string filename) : filename(std::move(filename)) {
    // Ouvre le fichier en mode écriture
    file.open(this->filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << this->filename << " !" << std::endl;
    }
}

template <std::size_t N>
VTKconverter<N>::~VTKconverter() {
    if (file.is_open()) {
        file.close();
    }
}

template <std::size_t N>
void VTKconverter<N>::convertToVTK(const Univers<N>& univers) {
    file << "<VTKFile type='UnstructuredGrid' version='0.1' byte_order='LittleEndian'>" << std::endl;
    file << "<UnstructuredGrid>" << std::endl;
    file << "<Piece NumberOfPoints='" << univers.getNbParticles() << "' NumberOfCells='" << univers.getCells().size() << ">" << std::endl;
    std::list<Particle<N>> particles = univers.getParticles();
    writeData(particles, "Points");
    writeData(particles, "Velocity");
    writeData(particles, "Masse");
    writeCells(univers);
    file << "</Piece>" << std::endl;
    file << "</UnstructuredGrid>" << std::endl;
    file << "</VTKFile>" << std::endl;
}



template <std::size_t N>
void VTKconverter<N>::writeData(const std::list<Particle<N>>& particles, const std::string& dataType) {

    file << "<" + dataType + ">" << std::endl;
    int nbComponents = N;
    if (dataType == "Masse") {
        file << "<DataArray name='" << dataType << "' type='Float32' format='ascii'>" << std::endl;
        for (const auto& particle : particles) {
            particle.getMass();
        }
        file << "</DataArray>" << std::endl;
    }
    else {
        file << "<DataArray name='" << dataType << "' type='Float32' NumberOfComponents=' " << nbComponents << "' format='ascii'>" << std::endl;
        for (const auto& particle : particles) {
            for (int i = 0; i < N; ++i) {
                file << particle.getPosition().get(i) << " ";
            }
        }
        file << "</DataArray>" << std::endl;
    }
    file << "</" + dataType + ">" << std::endl;
}

template <std::size_t N>
void VTKconverter<N>::writeCells(const Univers<N>& univers) {
    file << "<Cells>" << std::endl;
    file << "<DataArray type='Int32' Name='connectivity' format='ascii'>" << std::endl;
    file << "</DataArray>" << std::endl;
    file << "</Cells>" << std::endl;
}
