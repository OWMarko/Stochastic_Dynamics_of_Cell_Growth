cmake_minimum_required(VERSION 3.10)
project(CellGrowthSimulation VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(cell_sim src/main.cpp src/simulation.cpp src/utils.cpp)

if(MSVC)
    target_compile_options(cell_sim PRIVATE /W4)
else()
    target_compile_options(cell_sim PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()

add_executable(run_tests tests/test_main.cpp src/simulation.cpp)

add_test(NAME BasicCheck COMMAND run_tests)