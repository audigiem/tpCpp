# Créer une bibliothèque à partir d'un ensemble de fichiers de définitions (.cxx) sans main.
# Ces fichiers ne contiennent pas de fonction main
# Remplacer ... par les fichiers nécessaires 
add_library(particle INTERFACE)
add_library(vecteur INTERFACE)
add_library(cell INTERFACE)
add_library(univers INTERFACE)
add_library(vtkconverter INTERFACE)
#add_library(kdtree INTERFACE)

target_include_directories(particle INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(vecteur INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(cell INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(univers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(vtkconverter INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
#target_include_directories(kdtree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})