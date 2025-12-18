cmake_minimum_required(VERSION 3.10)
project(CellularGrowthSim VERSION 1.0)

# Standard C++17 requis pour <random> et filesystem
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Dossier des headers
include_directories(include)

# Fichiers sources
set(SOURCES
    src/main.cpp
    src/Simulation.cpp
    src/Estimator.cpp
)

# Création de l'exécutable
add_executable(growth_sim ${SOURCES})

# Optimisations pour la release (HPC)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")
