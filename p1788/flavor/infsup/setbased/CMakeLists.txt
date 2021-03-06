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


# relevant header files of this directory
set(P1788_HEADER_FILES
	mpfr_bin_ieee754_flavor.hpp
	mpfr_bin_ieee754_flavor_bool_func_impl.hpp
	mpfr_bin_ieee754_flavor_cancel_func_impl.hpp
	mpfr_bin_ieee754_flavor_class_impl.hpp
        mpfr_bin_ieee754_flavor_mul_rev_to_pair_func_impl.hpp
	mpfr_bin_ieee754_flavor_elem_func_impl.hpp
	mpfr_bin_ieee754_flavor_io_impl.hpp
	mpfr_bin_ieee754_flavor_num_func_impl.hpp
	mpfr_bin_ieee754_flavor_rec_bool_func_impl.hpp
	mpfr_bin_ieee754_flavor_rec_overlap_impl.hpp
	mpfr_bin_ieee754_flavor_rev_func_impl.hpp
	mpfr_bin_ieee754_flavor_set_op_impl.hpp
	mpfr_bin_ieee754_flavor_setup_func_impl.hpp
	mpfr_bin_ieee754_flavor_util_func_impl.hpp
	mpfr_bin_ieee754_flavor_validation_func_impl.hpp
   )

# relative path of this directory
string(REGEX REPLACE "${PROJECT_SOURCE_DIR}" "" P1788_RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# prefix for custom target
string(REGEX REPLACE "/" "_" P1788_HEADERS_TARGET_SUFFIX ${P1788_RELATIVE_PATH})

# custom_target to include headers in IDE-project-managers
add_custom_target("header${P1788_HEADERS_TARGET_SUFFIX}" SOURCES ${P1788_HEADER_FILES})

# install header files
install(FILES ${P1788_HEADER_FILES} DESTINATION "include${P1788_RELATIVE_PATH}")


