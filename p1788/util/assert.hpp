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

#ifndef LIBIEEEP1788_P1788_UTIL_ASSERT_HPP
#define LIBIEEEP1788_P1788_UTIL_ASSERT_HPP

#include <cassert>

#ifndef LIBIEEEP1788_NOT_IMPLEMENTED_ASSERT_LEVEL
#define LIBIEEEP1788_NOT_IMPLEMENTED_ASSERT_LEVEL 0
#endif

#if LIBIEEEP1788_NOT_IMPLEMENTED_ASSERT_LEVEL == 0
#define LIBIEEEP1788_NOT_IMPLEMENTED
#elif LIBIEEEP1788_NOT_IMPLEMENTED_ASSERT_LEVEL == 1
#define LIBIEEEP1788_NOT_IMPLEMENTED \
    assert(false, "not implemented!")
#elif LIBIEEEP1788_NOT_IMPLEMENTED_ASSERT_LEVEL == 2
#define LIBIEEEP1788_NOT_IMPLEMENTED \
    static_assert(false, "not implemented!")
#endif

#endif // LIBIEEEP1788_P1788_UTIL_ASSERT_HPP
