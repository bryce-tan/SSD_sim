cmake_minimum_required(VERSION 3.10)

project(SSDSimulator VERSION 1.0)

# C++ stantard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Included header directory
include_directories(include)

# Compile all the files in the src directory into a library - SSDSim
file(GLOB SOURCES "src/*.cpp")
add_library(SSDSim ${SOURCES})

# Add an executable
add_executable(SSDSimulator main.cpp)

# Link library file
target_link_libraries(SSDSimulator PUBLIC SSDSim)

# Test on the simulator
enable_testing()
add_subdirectory(test)
