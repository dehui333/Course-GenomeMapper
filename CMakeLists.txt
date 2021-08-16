cmake_minimum_required(VERSION 3.14)

# set the project name and version
project(mist_mapper VERSION 0.0.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(mist_mapper src/mist_mapper.cpp)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h")

# directory to get the header files to include
target_include_directories(mist_mapper PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# add googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# add subdirectories
add_subdirectory(test)

