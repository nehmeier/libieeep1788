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


if(Boost_FOUND)

    include_directories(${Boost_INCLUDE_DIRS})

    if(GMP_FOUND)

        if(MPFR_FOUND)

            if(CODE_COVERAGE)

            endif(CODE_COVERAGE)


            if(NOT Boost_USE_STATIC_LIBS)
                add_definitions(-DBOOST_TEST_DYN_LINK)
            endif(NOT Boost_USE_STATIC_LIBS)

            # relevant test files of this directory
            set(P1788_TEST_FILES
                    test_integration_mpfr_bin_ieee754_flavor_class.cpp
                    test_integration_mpfr_bin_ieee754_flavor_io.cpp
                    test_integration_mpfr_bin_ieee754_flavor_bool.cpp
                    test_integration_mpfr_bin_ieee754_flavor_rec_bool.cpp
                    test_integration_mpfr_bin_ieee754_flavor_num.cpp
                    test_integration_mpfr_bin_ieee754_flavor_set_op.cpp
                    test_integration_mpfr_bin_ieee754_flavor_elem.cpp
		    test_integration_mpfr_bin_ieee754_flavor_cancel.cpp
                    test_integration_mpfr_bin_ieee754_flavor_mul_rev_to_pair.cpp
		    test_integration_mpfr_bin_ieee754_flavor_rev.cpp
               )

            # relative path of this directory
            string(REGEX REPLACE "${PROJECT_SOURCE_DIR}/" "" P1788_RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

            # prefix for custom target
            string(REGEX REPLACE "/" "_" P1788_TEST_TARGET_PREFIX ${P1788_RELATIVE_PATH})

            # add executable/test and link with mpfr and boost
            foreach(P1788_TEST ${P1788_TEST_FILES})
                string(REGEX REPLACE ".cpp" "" P1788_TEST_TARGET ${P1788_TEST})
                add_executable("${P1788_TEST_TARGET_PREFIX}_${P1788_TEST_TARGET}" ${P1788_TEST})
                target_link_libraries("${P1788_TEST_TARGET_PREFIX}_${P1788_TEST_TARGET}" ${MPFR_LIBRARIES} ${GMP_LIBRARIES} ${Boost_LIBRARIES})
                add_test("${P1788_TEST_TARGET_PREFIX}_${P1788_TEST_TARGET}" "${P1788_TEST_TARGET_PREFIX}_${P1788_TEST_TARGET}")
            endforeach(P1788_TEST ${P1788_TEST_FILES})

        else(MPFR_FOUND)
            message(WARNING "Unable to compile tests, requires MPFR!")
        endif(MPFR_FOUND)

    else(GMP_FOUND)
        message(WARNING "Unable to compile tests, requires GMP!")
    endif(GMP_FOUND)

else(Boost_FOUND)
    message(WARNING "Unable to compile tests, requires Boost!")
endif(Boost_FOUND)
