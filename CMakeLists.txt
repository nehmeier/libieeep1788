# minimum cmake version required to carry out the build
cmake_minimum_required(VERSION 2.8)

# gives the project a name.
project(libieeep1788)

# activates c++11 extensions for g++ compiler.
add_definitions(-std=c++11)

# debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -DNDEBUG")

# release flags
set(CMAKE_CSS_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -DNDEBUG")

include_directories("${PROJECT_SOURCE_DIR}")

# collect all procject header files names in variable HEADER_FILES
add_subdirectory(p1788)

# examples
add_subdirectory(examples)


#TODO install HEADER_FILES
