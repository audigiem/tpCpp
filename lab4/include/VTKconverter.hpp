/**
 * @file VTKconverter.hpp
 * @brief Header file for VTK converter class.
 * @details This class is responsible for converting data to VTK format.
 * it creates a directory in ../demo and writes the data for each time step
 * in a ".vtk" file.
 * @author matteo AUDIGIER
 * @date 2023-10-01
 */

#ifndef VTKCONVERTER_H
#define VTKCONVERTER_H

#include "univers.hpp"
#include "particle.hpp"
#include <fstream>

template <std::size_t N>
class VTKconverter {
public:
    std::ofstream currentFile;
    std::string fileName;
    std::string dirName;
    int nbFiles;
    VTKconverter(std::string dirName, std::string filesName);
    ~VTKconverter();


    void createFile();
    void closeFile();

    void convertToVTK(const Univers<N>& univers);
    void writeData(const std::vector<Particle<N>*>& particles, const std::string& dataType);
    void writeCells(const Univers<N>& univers);
};

#include "../src/VTKconverter.cpp"

#endif //VTKCONVERTER_H
