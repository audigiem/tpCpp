# Créer un executable à partir de fichiers sources
add_executable(test_vecteur test_point.cxx)
add_executable(test_univers test_univers.cpp)

# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.
target_link_libraries(test_vecteur particle_lib)
target_link_libraries(test_univers particle_lib)