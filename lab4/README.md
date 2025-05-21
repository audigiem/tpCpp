# Simulation de Particules en N Dimensions

Ce projet implémente une simulation de particules dans un espace N-dimensionnel, en utilisant des structures de données efficaces comme des cellules de partitionnement spatial. Il est conçu pour des simulations physiques complexes, telles que les collisions de particules ou les interactions gravitationnelles.

## Fonctionnalités

- **Simulation multi-dimensionnelle** : Supporte des espaces de dimensions arbitraires.
- **Partitionnement spatial** : Gestion des particules via des cellules pour optimiser les calculs.
- **Tests unitaires** : Utilisation de GoogleTest pour assurer la fiabilité du code.
- **Génération de fichiers .vtk** : Exportation des résultats de simulation pour visualisation dans VTK.
- **Démos interactives** : Simulation de collisions et de systèmes planétaires.
- **Documentation Doxygen** : Génération automatique de la documentation API.

## Structure du Projet

- `include/` : Contient les fichiers d'en-tête pour les classes principales (`Particle`, `Cell`, etc.).
- `src/` : Implémentations des classes et des algorithmes.
- `test/` : Tests unitaires et fonctionnels pour valider le comportement du projet.
- `demo/` : Démos interactives pour visualiser les simulations.
- `CMakeLists.txt` : Configuration du projet avec CMake.

## Prérequis

- **Compilateur C++** : Supportant C++17 ou supérieur.
- **CMake** : Version 3.15 ou supérieure.
- **GoogleTest** : Pour les tests unitaires (téléchargé automatiquement via CMake).
- **Doxygen** (optionnel) : Pour générer la documentation.

## Installation et Utilisation

1. Clonez le dépôt :
   ```bash
   git clone git@github.com:audigiem/tpCpp.git
   cd tpCpp/lab4
   ```
   
2. Créez un répertoire de construction :
   ```bash
    mkdir build
    cd build
    ```
   
3. Configurez le projet avec CMake :
   ```bash
   cmake ..
   ```
   
4. Compilez le projet :
   ```bash
    make
    ```
5. Genérez la documentation (optionnel) :
   ```bash
   make doc
   ```
6. Exécutez les tests unitaires :
   ```bash
   make test
   ```
   
7. Exécutez des tests spécifiques :
   ```bash
   ./test/testFillUnivers
   ./test/testUpdateNeighbourhood
   ...
   ```
   
8. Exécutez les démo :
   ```bash
   ./demo/simulationCollision
   ./demo/simulationPlanet
   ./demo/simulationCollision2
   ```
   