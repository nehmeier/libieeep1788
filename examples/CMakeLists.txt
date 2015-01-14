#
#                              libieeep1788
#
#   An implementation of the preliminary IEEE P1788 standard for
#   interval arithmetic
#
#
#   Copyright 2013 - 2015
#
#   Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
#   Department of Computer Science,
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

if(GMP_FOUND)

    if(MPFR_FOUND)

        # relevant example files of this directory
        set(P1788_EXAMPLE_FILES
		e01_helloworld.cpp
		e02_intervals.cpp
		e03_decorations.cpp
		e03_io.cpp
		e04_bool_func.cpp
		e05_num_func.cpp
		e06_set_op.cpp
		e07_elem_func.cpp
		e08_cancel_func.cpp
		e09_exceptions.cpp
		e10_bisection.cpp
		e11_newton.cpp
           )

        # relative path of this directory
        string(REGEX REPLACE "${PROJECT_SOURCE_DIR}/" "" P1788_RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

        # prefix for custom target
        string(REGEX REPLACE "/" "_" P1788_EXAMPLE_TARGET_PREFIX ${P1788_RELATIVE_PATH})

        # add executable and link with mpfr
        foreach(P1788_EXAMPLE ${P1788_EXAMPLE_FILES})
            string(REGEX REPLACE ".cpp" "" P1788_EXAMPLE_TARGET ${P1788_EXAMPLE})
            add_executable("${P1788_EXAMPLE_TARGET_PREFIX}_${P1788_EXAMPLE_TARGET}" ${P1788_EXAMPLE})
            target_link_libraries("${P1788_EXAMPLE_TARGET_PREFIX}_${P1788_EXAMPLE_TARGET}" ${MPFR_LIBRARIES} ${GMP_LIBRARIES})
        endforeach()

    else(MPFR_FOUND)
        message(WARNING "Unable to compile examples, requires MPFR!")
    endif(MPFR_FOUND)

else(GMP_FOUND)
    message(WARNING "Unable to compile tests, requires GMP!")
endif(GMP_FOUND)
