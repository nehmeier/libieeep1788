# minimum cmake version required to carry out the build
cmake_minimum_required(VERSION 2.8)

# gives the project a name.
project(libieeep1788)

# activates c++11 extensions for g++ compiler.
add_definitions(-std=c++11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -DNDEBUG")

set(CMAKE_CSS_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")


include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(p1788)
add_subdirectory(examples)
