cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(mist_mapper VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(mist_mapper src/mist_mapper.cpp)

# directory to get the header files to include
target_include_directories(mist_mapper PUBLIC "${PROJECT_BINARY_DIR}/include")
