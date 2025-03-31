cmake_minimum_required(VERSION 3.10)
project(RayTracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g")

set(SRC_FILES src/camera.cc src/image.cc src/main.cc src/ray.cc src/screen.cc src/sphere.cc)
include_directories(include)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  # For executables
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # For shared libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # For static libraries

# Ensure all object files go to build/
set(CMAKE_OBJECT_PATH_MAX 260) # Prevent long path issues on Windows
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


add_executable(out ${SRC_FILES})

# Specify the build directory
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
