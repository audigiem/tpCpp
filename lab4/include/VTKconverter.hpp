/**
 * @file VTKconverter.hpp
 * @brief Header file for VTK converter class.
 * @details This class is responsible for converting data to VTK format.
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
    std::ofstream file;
    std::string filename;
    VTKconverter(std::string filename);
    ~VTKconverter();



    void convertToVTK(const Univers<N>& univers);
    void writeData(const std::list<Particle<N>>& particles, const std::string& dataType);
    void writeCells(const Univers<N>& univers);
};

#include "VTKconverter.cpp"

#endif //VTKCONVERTER_H
