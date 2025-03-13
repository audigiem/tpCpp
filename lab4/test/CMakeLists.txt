# Créer un executable à partir de fichiers sources
add_executable(test_voisins testNeighboorCells.cpp)

# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.
target_link_libraries(test_voisins univers)
