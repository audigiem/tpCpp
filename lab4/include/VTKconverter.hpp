/**
 * @file VTKconverter.hpp
 * @brief Header file for VTK converter class.
 * @details This class is responsible for converting simulation data to VTK format
 * for visualization in ParaView. It creates a directory in ../demo and writes 
 * the data for each time step in a ".vtk" file.
 * @author Mattéo Audigier - Mattéo Gautier
 * @date 2025-05-19
 */

#ifndef VTKCONVERTER_H
#define VTKCONVERTER_H

#include "univers.hpp"
#include "particle.hpp"
#include <fstream>

/**
 * @class VTKconverter
 * @brief Converts N-dimensional particle simulation data to VTK format
 * @tparam N The dimension of the simulation space
 * 
 * This class handles the conversion of simulation data to the VTK file format,
 * which can then be visualized using tools like ParaView. It manages file creation,
 * data writing, and proper VTK formatting.
 */
template <std::size_t N>
class VTKconverter {
private:
    /** @brief Current output file stream for VTK data */
    std::ofstream currentFile;
    
    /** @brief Base name for the generated VTK files */
    std::string fileName;
    
    /** @brief Directory where VTK files will be stored */
    std::string dirName;
    
    /** @brief Counter for the number of files created */
    int nbFiles;
public:
    /**
     * @brief Constructor for the VTKconverter
     * @param dirName Directory where VTK files will be stored
     * @param filesName Base name for the generated VTK files
     * @details Creates the output directory if it doesn't exist
     */
    VTKconverter(std::string dirName, std::string filesName);
    
    /**
     * @brief Copy constructor
     * @param other VTKconverter instance to copy
     */
    VTKconverter(const VTKconverter& other);
    
    /**
     * @brief Destructor
     * @details Ensures any open file is properly closed
     */
    ~VTKconverter();
    
    /**
     * @brief Assignment operator
     * @param other VTKconverter instance to copy
     * @return Reference to this converter after assignment
     */
    VTKconverter& operator=(const VTKconverter& other);

    /**
     * @brief Create a new VTK file for the current time step
     * @details Generates a filename with incrementing counter and opens the file
     */
    void createFile();
    
    /**
     * @brief Close the current VTK file
     * @details Properly closes the file and flushes any buffered data
     */
    void closeFile();

    /**
     * @brief Convert universe state to VTK format
     * @param univers The universe containing particle data
     * @details Creates a new file, writes headers, particle data, and closes the file
     */
    void convertToVTK(const Univers<N>& univers);
    
    /**
     * @brief Write particle position data to VTK file
     * @param particles Vector of particle pointers
     * @details Writes the POINTS section of the VTK file
     */
    void writeDataPosition(const std::vector<Particle<N>*>& particles);
    
    /**
     * @brief Write particle velocity and mass data to VTK file
     * @param particles Vector of particle pointers
     * @details Writes the POINT_DATA section with velocity vectors and mass scalars
     */
    void writeDataVelocityMass(const std::vector<Particle<N>*>& particles);
    
    /**
     * @brief Write cell data to VTK file
     * @param univers The universe containing cell data
     * @param numberOfCells Total number of cells in the grid
     * @details Writes the CELLS section with cell connectivity information
     */
    void writeCells(const Univers<N>& univers, int numberOfCells);
};

#include "../src/VTKconverter.cpp"

#endif //VTKCONVERTER_H
