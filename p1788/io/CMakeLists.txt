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


# relevant header files of this directory
set(P1788_HEADER_FILES
    io_manip.hpp
   )

# relative path of this directory
string(REGEX REPLACE "${PROJECT_SOURCE_DIR}" "" P1788_RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# prefix for custom target
string(REGEX REPLACE "/" "_" P1788_HEADERS_TARGET_SUFFIX ${P1788_RELATIVE_PATH})

# custom_target to include headers in IDE-project-managers
add_custom_target("header${P1788_HEADERS_TARGET_SUFFIX}" SOURCES ${P1788_HEADER_FILES})

# install header files
install(FILES ${P1788_HEADER_FILES} DESTINATION "include${P1788_RELATIVE_PATH}")

