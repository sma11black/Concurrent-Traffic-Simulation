# CMakeList.txt : CMake project for Concurrent Traffic Simulation, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(OpenCV REQUIRED)

# Find all executables
file(GLOB project_SRCS *.cpp) #*.h

# Add source to this project's executable.
add_executable (traffic_simulation ${project_SRCS})

target_link_libraries(traffic_simulation PRIVATE opencv_ml opencv_dnn opencv_core opencv_flann)