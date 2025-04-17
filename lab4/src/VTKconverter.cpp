//
// Created by matteo on 01/04/25.
//

#include "../include/VTKconverter.hpp"
#include <iostream>
#include <filesystem>

template <std::size_t N>
VTKconverter<N>::VTKconverter(std::string dirName, std::string filesName)
    : dirName(std::move(dirName)), nbFiles(0), fileName(std::move(filesName)) {

    std::string fullPath = "../demo/" + dirName;
    std::filesystem::create_directories(fullPath);

    if (!std::filesystem::exists(fullPath)) {
        std::cerr << "Error: Directory " << fullPath << " was not created!" << std::endl;
    } else {
        std::cout << "Directory successfully created: " << fullPath << std::endl;
    }

    std::cout << "VTK converter created" << std::endl;
}

template <std::size_t N>
VTKconverter<N>::~VTKconverter() {
    if (currentFile.is_open()) {
        currentFile.close();
    }
    std::cout << "VTK converter destroyed" << std::endl;
    std::cout << "VTK files created in ../demo/" << dirName << std::endl;
}

template <std::size_t N>
void VTKconverter<N>::createFile() {
    std::string fullDirPath = "/home/matteo/Bureau/ENSIMAG/2A/S8/cpp/tpCpp/lab4/demo/" + dirName;

    // Vérifie et crée le répertoire si nécessaire
    if (!std::filesystem::exists(fullDirPath)) {
        std::cerr << "Warning: Directory " << fullDirPath << " does not exist. Creating it now." << std::endl;
        std::filesystem::create_directories(fullDirPath);

        if (!std::filesystem::exists(fullDirPath)) {
            std::cerr << "Error: Failed to create directory " << fullDirPath << std::endl;
            return;
        }
    }

    nbFiles++;
    std::string fullPath = fullDirPath + "/" + fileName + "_" + std::to_string(nbFiles) + ".vtu";

    // Création et ouverture du fichier
    currentFile.open(fullPath);
    if (!currentFile.is_open()) {
        std::cerr << "Error: Could not create file " << fullPath << std::endl;
    } else {
        std::cout << "File successfully created: " << fullPath << std::endl;
    }
}

template <std::size_t N>
void VTKconverter<N>::convertToVTK(const Univers<N>& univers) {
    if (!currentFile.is_open()) {
        std::cerr << "Error: Attempt to write to a file that is not open!" << std::endl;
        return;
    }

    std::cout << "Converting universe to VTK..." << std::endl;

    currentFile << "<VTKFile type='UnstructuredGrid' version='0.1' byte_order='LittleEndian'>" << std::endl;
    currentFile << "<UnstructuredGrid>" << std::endl;
    int numberOfCells = 0;
    std::array<int, N> numberOfCellsArray = univers.getnumberOfCells();
    for (int i = 0; i < N; ++i) {
        numberOfCells += numberOfCellsArray[i];
    }
    currentFile << "<Piece NumberOfPoints='" << univers.getNbParticles() << "' NumberOfCells='" << numberOfCells << "'>" << std::endl;

    std::vector<Particle<N>*> particles = univers.getParticles();
    writeData(particles, "Points");
    writeCells(univers);
    writeData(particles, "Velocity");
    writeData(particles, "Masse");


    currentFile << "</Piece>" << std::endl;
    currentFile << "</UnstructuredGrid>" << std::endl;
    currentFile << "</VTKFile>" << std::endl;

    std::cout << "VTK conversion complete." << std::endl;
}

template <std::size_t N>
void VTKconverter<N>::writeData(const std::vector<Particle<N>*>& particles, const std::string& dataType) {
    if (!currentFile.is_open()) {
        std::cerr << "Error: Attempt to write data to a file that is not open!" << std::endl;
        return;
    }

    currentFile << "<" + dataType + ">" << std::endl;
    int nbComponents = N;

    if (dataType == "Masse") {
        currentFile << "<DataArray name='" << dataType << "' type='Float32' format='ascii'>" << std::endl;
        for (const auto& particle : particles) {
            currentFile << particle->getMass() << " ";
        }
        currentFile << std::endl;
        currentFile << "</DataArray>" << std::endl;
    } else {
        currentFile << "<DataArray name='" << dataType << "' type='Float32' NumberOfComponents='" << nbComponents << "' format='ascii'>" << std::endl;
        for (const auto& particle : particles) {
            for (int i = 0; i < N; ++i) {
                currentFile << particle->getPosition().get(i) << " ";
            }
            currentFile << std::endl;
        }
        currentFile << "</DataArray>" << std::endl;
    }

    currentFile << "</" + dataType + ">" << std::endl;
}

template <std::size_t N>
void VTKconverter<N>::writeCells(const Univers<N>& univers) {
    if (!currentFile.is_open()) {
        std::cerr << "Error: Attempt to write cells to a file that is not open!" << std::endl;
        return;
    }

    currentFile << "<Cells>" << std::endl;
    currentFile << "<DataArray type='Int32' Name='connectivity' format='ascii'>" << std::endl;
    currentFile << "</DataArray>" << std::endl;
    currentFile << "<DataArray type='Int32' Name='offsets' format='ascii'>" << std::endl;
    currentFile << "</DataArray>" << std::endl;
    currentFile << "<DataArray type='UInt8' Name='types' format='ascii'>" << std::endl;
    currentFile << "</DataArray>" << std::endl;
    currentFile << "</Cells>" << std::endl;
}

template <std::size_t N>
void VTKconverter<N>::closeFile() {
    if (currentFile.is_open()) {
        currentFile.close();
        std::cout << "File closed successfully." << std::endl;
    } else {
        std::cerr << "Warning: Attempted to close a file that was not open." << std::endl;
    }
}
