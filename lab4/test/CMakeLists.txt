# Créer un executable à partir de fichiers sources
add_executable(test_voisins testNeighboorCells.cpp)
add_executable(test1D test1D.cpp)
add_executable(test2D test2D.cpp)
add_executable(test3D test3D.cpp)

# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.
target_link_libraries(test_voisins univers)
target_link_libraries(test1D univers)
target_link_libraries(test2D univers)
target_link_libraries(test3D univers)
