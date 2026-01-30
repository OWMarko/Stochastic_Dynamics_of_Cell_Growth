cmake_minimum_required(VERSION 3.10)
project(CellGrowthSimulation VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP Found! Parallelism enabled.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    message(WARNING "OpenMP not found. Code will run in serial.")
endif()

if(MSVC)
    add_compile_options(/W4 /O2)
else()
    add_compile_options(-Wall -Wextra -O3)
endif()

include_directories(include)

set(CORE_SOURCES
    src/utils.cpp
    src/models/inference.cpp
    src/models/cell_mass.cpp    
    src/models/yule_process.cpp 
    src/benchmark_runner.cpp
)

add_executable(cell_sim src/main.cpp ${CORE_SOURCES})

enable_testing()
add_test(NAME RandomCheck COMMAND test_random)