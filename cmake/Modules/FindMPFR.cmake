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


#  MPFR_FOUND - found MPFR
#  MPFR_INCLUDE_DIRS - include directories
#  MPFR_LIBRARIES - libraries
#  MPFR_DEFINITIONS - compiler switches
#  MPFR_VERSION_STRING - version

find_package(PkgConfig)

pkg_check_modules(PC_MPFR QUIET mpfr)
set(MPFR_DEFINITIONS ${PC_MPFR_CFLAGS_OTHER})

find_path(MPFR_INCLUDE_DIR mpfr.h HINTS ${PC_MPFR_INCLUDEDIR} ${PC_MPFR_INCLUDE_DIRS})

find_library(MPFR_LIBRARY NAMES mpfr HINTS ${PC_MPFR_LIBDIR} ${PC_MPFR_LIBRARY_DIRS} )

set(MPFR_LIBRARIES ${MPFR_LIBRARY} )
set(MPFR_INCLUDE_DIRS ${MPFR_INCLUDE_DIR} )

if(MPFR_INCLUDE_DIR AND EXISTS "${MPFR_INCLUDE_DIR}/mpfr.h")
    file(STRINGS "${MPFR_INCLUDE_DIR}/mpfr.h" MPFR_VERSION_STR REGEX "^#define[\t ]+MPFR_VERSION_STRING[\t ]+\".*\"")
    string(REGEX REPLACE "^.*MPFR_VERSION_STRING[\t ]+\"([^\"]*)\".*$" "\\1" MPFR_VERSION_STRING "${MPFR_VERSION_STR}")
endif(MPFR_INCLUDE_DIR AND EXISTS "${MPFR_INCLUDE_DIR}/mpfr.h")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(MPFR  REQUIRED_VARS MPFR_LIBRARY MPFR_INCLUDE_DIR VERSION_VAR MPFR_VERSION_STRING)

mark_as_advanced(MPFR_INCLUDE_DIR MPFR_LIBRARY )
