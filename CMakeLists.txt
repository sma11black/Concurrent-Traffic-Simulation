# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Concurrent Traffic Simulation")

# Include sub-projects.
add_subdirectory ("src")
