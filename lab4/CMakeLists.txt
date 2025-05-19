## Indique qu'elle version de cmake minimale est utilisée.
cmake_minimum_required (VERSION 3.16.3)

## Specifie le nom du projet et le langage de programmation du projet
project(Lab4 CXX)

## Force le standard
set(CMAKE_CXX_STANDARD 17)



set(CMAKE_CXX_FLAGS "-Wall")

# Set optimization flags for Release builds
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Advanced optimization flags
set(OPTIMIZATION_FLAGS
    "-O3"                     # Highest standard optimization
    "-march=native"           # Optimize for local machine architecture
    "-mtune=native"           # Fine-tune for CPU-specific optimizations
    "-ffast-math"             # Aggressive math optimizations (note: may affect IEEE compliance)
    "-funroll-loops"          # Unroll loops for speed at cost of binary size
    "-fomit-frame-pointer"    # Free up a register by omitting frame pointer
    "-ftree-vectorize"        # Explicitly enable auto-vectorization
    "-fno-signed-zeros"       # Ignore sign of zero
    "-fno-trapping-math"      # Assume no IEEE exceptions
    "-freciprocal-math"       # Allow reciprocal instead of division when faster
    "-ffinite-math-only"      # No need to handle infinite/NaN
    "-fno-math-errno"         # Don't set errno after math functions
    "-fprefetch-loop-arrays"  # Prefetch memory in loops
    "-fopenmp"                # OpenMP support
)

# Combine all flags
string(REPLACE ";" " " OPTIMIZATION_FLAGS_STR "${OPTIMIZATION_FLAGS}")

# Debug build - minimal optimization with debug symbols
set(CMAKE_CXX_FLAGS_DEBUG "-g -Og -Wall -Wextra -pedantic")

# Release build - full optimization
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG ${OPTIMIZATION_FLAGS_STR}")

# RelWithDebInfo - optimization with debug info
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g -DNDEBUG ${OPTIMIZATION_FLAGS_STR}")

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Using optimization flags: ${OPTIMIZATION_FLAGS_STR}")

## Définir la localisation des entêtes.
## include_directories sera propager à l'ensemble du projet
include_directories(${CMAKE_SOURCE_DIR}/include)

## Parcours les sous répertoires contenant les définitions (.cxx)
## On commence par créer une bibliothèque
add_subdirectory(src)

add_subdirectory(demo)

## On créée les tests pour la bibliothèque.
## Ces tests sont unitaires ou fonctionnels
add_subdirectory(test)

## On ajoute la librairie de test GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
## Uncomment the following if errors on Windows
## set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

## Enable testing
enable_testing()

# Add custom demo targets
add_custom_target(demo_collision
    COMMAND simulationCollision
    DEPENDS simulationCollision
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running collision simulation demo"
)

add_custom_target(demo_planet
    COMMAND simulationPlanet
    DEPENDS simulationPlanet
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running palnet simulation demo"
)

# Default demo target
add_custom_target(demo
    COMMAND ${CMAKE_COMMAND} -E echo "Please specify which demo to run: 'make demo_collision' or 'make demo_planet'"
)