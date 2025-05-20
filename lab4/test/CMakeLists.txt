enable_testing()

# Register the subdirectory for the test
add_subdirectory(vecteur)
add_subdirectory(univers)
add_subdirectory(particle)
add_subdirectory(cell)

add_executable(testFillUnivers testFillUnivers.cpp)
add_executable(testUpdateNeighbourhood testNeighbourCells.cpp)

target_link_libraries(testFillUnivers univers cell particle vecteur)
target_link_libraries(testUpdateNeighbourhood univers cell particle vecteur)
