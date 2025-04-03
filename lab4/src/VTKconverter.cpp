//
// Created by matteo on 01/04/25.
//

#include "../include/VTKconverter.hpp"
#include <iostream>
#include <filesystem>

template <std::size_t N>
VTKconverter<N>::VTKconverter(std::string dirName, std::string filesName) : dirName(std::move(dirName)), nbFiles(0), fileName(std::move(filesName)) {
    // create a directory named dirName if it doesn't exist in ../demo
    std::string command = "mkdir -p ../demo/" + dirName;
    system(command.c_str());

}

template <std::size_t N>
VTKconverter<N>::~VTKconverter() {
    if (currentFile.is_open()) {
        currentFile.close();
    }
    std::cout << "VTK converter destroyed" << std::endl;
    std::cout << "VTK files created in ../demo/" + dirName << std::endl;
}


/** * @brief Create a file in the specified directory corresponding to the current time step.
 * @param fileName The name of the file to create.
 * @details This function creates a file in the specified directory and opens it for writing.
 */
template <std::size_t N>
void VTKconverter<N>::createFile() {
    // check if the directory exists
    if (!std::filesystem::exists("../demo/" + dirName)) {
        std::cerr << "Error: Directory " << dirName << " does not exist." << std::endl;
        // create the directory
        std::string command = "mkdir -p ../demo/" + dirName;
        system(command.c_str());

    }
    nbFiles ++;
    std::string fullPath = "../demo/" + dirName + "/" + fileName +"_"+ std::to_string(nbFiles) + ".vtu";
    // create the file and open it for writing
    currentFile.open(fullPath);
    if (!currentFile.is_open()) {
        std::cerr << "Error: Could not create file " << fullPath << std::endl;
        return;
    }

}

template <std::size_t N>
void VTKconverter<N>::convertToVTK(const Univers<N>& univers) {
    currentFile << "<VTKFile type='UnstructuredGrid' version='0.1' byte_order='LittleEndian'>" << std::endl;
    currentFile << "<UnstructuredGrid>" << std::endl;
    currentFile << "<Piece NumberOfPoints='" << univers.getNbParticles() << "' NumberOfCells='" << univers.getCells().size() << ">" << std::endl;
    std::list<std::shared_ptr<Particle<N>>> particles = univers.getParticles();
    writeData(particles, "Points");
    writeData(particles, "Velocity");
    writeData(particles, "Masse");
    writeCells(univers);
    currentFile << "</Piece>" << std::endl;
    currentFile << "</UnstructuredGrid>" << std::endl;
    currentFile << "</VTKFile>" << std::endl;
}



template <std::size_t N>
void VTKconverter<N>::writeData(const std::list<std::shared_ptr<Particle<N>>>& particles, const std::string& dataType) {

    currentFile << "<" + dataType + ">" << std::endl;
    int nbComponents = N;
    if (dataType == "Masse") {
        currentFile << "<DataArray name='" << dataType << "' type='Float32' format='ascii'>" << std::endl;
        for (const auto& particle : particles) {
            particle->getMass();
        }
        currentFile << "</DataArray>" << std::endl;
    }
    else {
        currentFile << "<DataArray name='" << dataType << "' type='Float32' NumberOfComponents=' " << nbComponents << "' format='ascii'>" << std::endl;
        for (const auto& particle : particles) {
            for (int i = 0; i < N; ++i) {
                currentFile << particle->getPosition().get(i) << " ";
            }
        }
        currentFile << "</DataArray>" << std::endl;
    }
    currentFile << "</" + dataType + ">" << std::endl;
}

template <std::size_t N>
void VTKconverter<N>::writeCells(const Univers<N>& univers) {
    currentFile << "<Cells>" << std::endl;
    currentFile << "<DataArray type='Int32' Name='connectivity' format='ascii'>" << std::endl;
    currentFile << "</DataArray>" << std::endl;
    currentFile << "</Cells>" << std::endl;
}

template <std::size_t N>
void VTKconverter<N>::closeFile() {
    if (currentFile.is_open()) {
        currentFile.close();
    }
}
