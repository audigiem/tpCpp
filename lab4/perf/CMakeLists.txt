# Add the collision executable
add_executable(collision collision.cpp)

# Link with the main particle library
target_link_libraries(collision vtkconverter univers cell particle vecteur)
