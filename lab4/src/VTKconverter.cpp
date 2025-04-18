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
    std::cout << "VTK files created in /user/8/audigiem/2A/S8/cpp/lab4/demo/" << dirName << std::endl;
}

template <std::size_t N>
void VTKconverter<N>::createFile() {
    std::string fullDirPath = "/user/8/audigiem/2A/S8/cpp/lab4/demo/" + dirName;

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
    writeDataPosition(particles);
    writeDataVelocityMass(particles);
    writeCells(univers);


    currentFile << "</Piece>" << std::endl;
    currentFile << "</UnstructuredGrid>" << std::endl;
    currentFile << "</VTKFile>" << std::endl;

    std::cout << "VTK conversion complete." << std::endl;
}

template <std::size_t N>
void VTKconverter<N>::writeDataPosition(const std::vector<Particle<N>*>& particles) {
    if (!currentFile.is_open()) {
        std::cerr << "Error: Attempt to write data to a file that is not open!" << std::endl;
        return;
    }

    int nbComponents = N;
    currentFile << "<Points>" << std::endl;
    currentFile << "<DataArray name='Position' type='Float32' NumberOfComponents='" << nbComponents << "' format='ascii'>" << std::endl;
    for (const auto& particle : particles) {
        Vecteur<N> position = particle->getPosition();
        for (int i = 0; i < N; ++i) {
            currentFile << position.get(i) << " ";
        }
    }
    currentFile << std::endl;
    currentFile << "</DataArray>" << std::endl;
    currentFile << "</Points>" << std::endl;

}

template <std::size_t N>
void VTKconverter<N>::writeDataVelocityMass(const std::vector<Particle<N>*>& particles) {
    if (!currentFile.is_open()) {
        std::cerr << "Error: Attempt to write data to a file that is not open!" << std::endl;
        return;
    }

    int nbComponents = N;
    currentFile << "<PointData Vectors='vector'>" << std::endl;
    currentFile << "<DataArray type='Float32' Name='Velocity' NumberOfComponents='" << nbComponents << "' format='ascii'>" << std::endl;
    for (const auto& particle : particles) {
        Vecteur<N> velocity = particle->getVelocity();
        for (int i = 0; i < N; ++i) {
            currentFile << velocity.get(i) << " ";
        }
    }
    currentFile << std::endl;
    currentFile << "</DataArray>" << std::endl;
    currentFile << "<DataArray type='Float32' Name='Mass' format='ascii'>" << std::endl;
    for (const auto& particle : particles) {
        currentFile << particle->getMass() << " ";
    }
    currentFile << std::endl;
    currentFile << "</DataArray>" << std::endl;
    currentFile << "</PointData>" << std::endl;
}

template <std::size_t N>
void VTKconverter<N>::writeCells(const Univers<N>& univers) {
    if (!currentFile.is_open()) {
        std::cerr << "Error: Attempt to write cells to a file that is not open!" << std::endl;
        return;
    }

    std::vector<int> connectivity;
    std::vector<int> offsets;
    int types;

    for (const auto& cellPair : univers.getCells()) {
        const Cell<N>* cell = cellPair.second;
        const std::vector<Particle<N>*>& particles = cell->getParticles();
        int cellIndex = 0; // Assuming a single type of cell for simplicity

        for (const auto& particle : particles) {
            connectivity.push_back(particle->getId());
        }
        offsets.push_back(connectivity.size());
    }

    switch (N) {
        case 1:
            types = 3; // VTK_VERTEX
            break;
        case 2:
            types = 9; // VTK_QUAD
            break;
        case 3:
            types = 12; // VTK_TETRA
            break;
        default:
            std::cerr << "Error: Unsupported dimension " << N << std::endl;
            return;
    }

    currentFile << "<Cells>" << std::endl;
    currentFile << "<DataArray type='Int32' Name='connectivity' format='ascii'>" << std::endl;
    for (const auto& id : connectivity) {
        currentFile << id << " ";
    }
    currentFile << "</DataArray>" << std::endl;
    currentFile << "<DataArray type='Int32' Name='offsets' format='ascii'>" << std::endl;
    for (const auto& offset : offsets) {
        currentFile << offset << " ";
    }
    currentFile << "</DataArray>" << std::endl;
    currentFile << "<DataArray type='UInt8' Name='types' format='ascii'>" << std::endl;
    currentFile << types << std::endl;
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
