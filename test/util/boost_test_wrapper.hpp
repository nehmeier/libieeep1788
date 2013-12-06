//
//                              libieeep1788
//
//   An implementation of the preliminary IEEE P1788 standard for
//   interval arithmetic
//
//
//   Copyright 2013
//
//   Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
//   Institute of Computer Science,
//   University of Wuerzburg, Germany
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#ifndef LIBIEEEP1788_TEST_UTIL_BOOST_TEST_WRAPPER_HPP
#define LIBIEEEP1788_TEST_UTIL_BOOST_TEST_WRAPPER_HPP

// Ignore effective C++ warnings
// on GCC  push the last diagnostic state and disable -Weffc++
//FIXME support other compiler
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

#include <boost/test/unit_test.hpp>

// on GCC  enable the diagnostic state -Weffc++ again
#pragma GCC diagnostic pop

#endif // LIBIEEEP1788_TEST_UTIL_BOOST_TEST_WRAPPER_HPP
