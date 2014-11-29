#
#                              libieeep1788
#
#   An implementation of the preliminary IEEE P1788 standard for
#   interval arithmetic
#
#
#   Copyright 2013
#
#   Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
#   Institute of Computer Science,
#   University of Wuerzburg, Germany
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.

# setting user defined build type
if(DEFINED CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE string "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
else()
   set(CMAKE_BUILD_TYPE Debug CACHE string "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
endif()


# minimum cmake version required to carry out the build
cmake_minimum_required(VERSION 2.8)

# gives the project a name.
project(libieeep1788)

#TODO ueber GIT Tags auslesen
set (P1788_VERSION_MAJOR 0)
set (P1788_VERSION_MINOR 0)
set (P1788_VERSION_PATCH 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/p1788/version.hpp.in"
  "${PROJECT_BINARY_DIR}/p1788/version.hpp"
  )
install(FILES "${PROJECT_BINARY_DIR}/p1788/version.hpp" DESTINATION "include/p1788/")

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_BINARY_DIR}")

# build with code coverage
option(CODE_COVERAGE OFF)

if(NOT CMAKE_COMPILER_IS_GNUCC OR NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CODE_COVERAGE OFF)
endif()


# activates c++11 extensions for g++ compiler.
add_definitions(-std=c++11)

#  flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

# debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -DLIBIEEEP1788_NOT_IMPLEMENTED_ASSERT_LEVEL=0 -DNDEBUG")

# release flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DLIBIEEEP1788_NOT_IMPLEMENTED_ASSERT_LEVEL=1")

# library flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")


# use custom modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)


# find Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.54 COMPONENTS unit_test_framework)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()


# find MPFR
find_package(MPFR 3.1.2)
if(MPFR_FOUND)
    include_directories(${MPFR_INCLUDE_DIRS})
endif()

#find GMP
find_package(GMP 6.0.0)
if(GMP_FOUND)
    include_directories(${GMP_INCLUDE_DIRS})
endif()


# collect and install all header files
add_subdirectory(p1788)


# examples
add_subdirectory(examples)

# documentation
add_subdirectory(doc)

# tests
enable_testing()

if(CODE_COVERAGE)
     # debug flags
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")

    # library flags
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif(CODE_COVERAGE)

add_subdirectory(test)


if(CODE_COVERAGE)

ADD_CUSTOM_TARGET(coverage)
ADD_CUSTOM_COMMAND(TARGET coverage
    COMMAND rm -rf coverage
    COMMAND mkdir -p coverage
    COMMAND lcov --directory . --zerocounters
    COMMAND lcov --capture --initial --directory . --output-file coverage/p1788_base.info
    COMMAND make --keep-going test
    COMMAND lcov --capture --directory . --output-file coverage/p1788_test.info
    COMMAND lcov -a coverage/p1788_base.info -a coverage/p1788_test.info -o coverage/p1788_coverage.info
    COMMAND lcov --remove coverage/p1788_coverage.info 'opt/*' '/usr/*' --output-file coverage/p1788_coverage.info
    COMMAND genhtml coverage/p1788_coverage.info --output-directory coverage
    COMMAND
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

endif(CODE_COVERAGE)





