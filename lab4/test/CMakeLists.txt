# Créer un executable à partir de fichiers sources
#add_executable(test_voisins testNeighboorCells.cpp)
#add_executable(test1D test1D.cpp)
#add_executable(test2D test2D.cpp)
#add_executable(test3D test3D.cpp)

# add_executable(test_univers1 test_univers1.cpp)
add_executable(test_univers2 test_univers2.cpp)
# add_executable(test_vecteur test_vecteur.cpp)
# add_executable(test_mouv test_particleMovement.cpp)

# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.
#target_link_libraries(test_voisins univers)
#target_link_libraries(test1D univers)
#target_link_libraries(test2D univers)
#target_link_libraries(test3D univers)

# target_link_libraries(test_univers1 univers)
target_link_libraries(test_univers2 univers vtkconverter)
# target_link_libraries(test_vecteur vecteur)
# target_link_libraries(test_mouv univers)
