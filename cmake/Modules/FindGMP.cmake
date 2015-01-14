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


#  GMP_FOUND - found GMP
#  GMP_INCLUDE_DIRS - include directories
#  GMP_LIBRARIES - libraries
#  GMP_DEFINITIONS - compiler switches
#  GMP_VERSION_STRING - version

find_package(PkgConfig)

pkg_check_modules(PC_GMP QUIET gmp)
set(GMP_DEFINITIONS ${PC_GMP_CFLAGS_OTHER})

find_path(GMP_INCLUDE_DIR gmp.h HINTS ${PC_GMP_INCLUDEDIR} ${PC_GMP_INCLUDE_DIRS})

find_library(GMP_LIBRARY NAMES gmp HINTS ${PC_GMP_LIBDIR} ${PC_GMP_LIBRARY_DIRS} )

set(GMP_LIBRARIES ${GMP_LIBRARY} )
set(GMP_INCLUDE_DIRS ${GMP_INCLUDE_DIR} )

if(GMP_INCLUDE_DIR AND EXISTS "${GMP_INCLUDE_DIR}/gmp.h")
    file(STRINGS "${GMP_INCLUDE_DIR}/gmp.h" GMP_VERSION_STR_MAJ REGEX "^#define[\t ]+__GNU_MP_VERSION[\t ]+[0-9]+")
    file(STRINGS "${GMP_INCLUDE_DIR}/gmp.h" GMP_VERSION_STR_MIN REGEX "^#define[\t ]+__GNU_MP_VERSION_MINOR[\t ]+[0-9]+")
    file(STRINGS "${GMP_INCLUDE_DIR}/gmp.h" GMP_VERSION_STR_PAT REGEX "^#define[\t ]+__GNU_MP_VERSION_PATCHLEVEL[\t ]+[0-9]+")
    string(REGEX REPLACE "^#define[\t ]+__GNU_MP_VERSION[\t ]+([0-9]+)" "\\1" GMP_VERSION_STR_MAJ "${GMP_VERSION_STR_MAJ}")
    string(REGEX REPLACE "^#define[\t ]+__GNU_MP_VERSION_MINOR[\t ]+([0-9]+)" "\\1" GMP_VERSION_STR_MIN "${GMP_VERSION_STR_MIN}")
    string(REGEX REPLACE "^#define[\t ]+__GNU_MP_VERSION_PATCHLEVEL[\t ]+([0-9]+)" "\\1" GMP_VERSION_STR_PAT "${GMP_VERSION_STR_PAT}")
    set(GMP_VERSION_STRING "${GMP_VERSION_STR_MAJ}.${GMP_VERSION_STR_MIN}.${GMP_VERSION_STR_PAT}")
endif(GMP_INCLUDE_DIR AND EXISTS "${GMP_INCLUDE_DIR}/gmp.h")

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(GMP  REQUIRED_VARS GMP_LIBRARY GMP_INCLUDE_DIR VERSION_VAR GMP_VERSION_STRING)

mark_as_advanced(GMP_INCLUDE_DIR GMP_LIBRARY )
