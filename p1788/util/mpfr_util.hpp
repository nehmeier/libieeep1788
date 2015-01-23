//   An implementation of the preliminary IEEE P1788 standard for
//   interval arithmetic
//
//
//   Copyright 2013 - 2015
//
//   Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
//   Department of Computer Science,
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

#ifndef LIBIEEEP1788_P1788_UTIL_EFT_HPP
#define LIBIEEEP1788_P1788_UTIL_EFT_HPP

#include <utility>

#include "p1788/util/mpfr_var.hpp"

namespace p1788
{

namespace util
{

template<typename T>
inline std::pair<T,T> two_sum(T const& a, T const& b)
{
    static_assert(std::numeric_limits<T>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // Typedef for the corresponding mpfr wrapper class representing the IEEE 754 binary floating point format of type T
    typedef p1788::util::mpfr_var<
    std::numeric_limits<T>::digits,
        std::numeric_limits<T>::has_denorm != std::denorm_present ? std::numeric_limits<T>::min_exponent
        : std::numeric_limits<T>::min_exponent - std::numeric_limits<T>::digits + 1,
        std::numeric_limits<T>::max_exponent,
        std::numeric_limits<T>::has_denorm == std::denorm_present
        >   mpfr_var;

    mpfr_var::setup();

    mpfr_var a_(a, MPFR_RNDN);
    mpfr_var b_(b, MPFR_RNDN);

    mpfr_var s;
    mpfr_var a_delta;
    mpfr_var b_delta;

    s.subnormalize(mpfr_add(s(), a_(), b_(), MPFR_RNDN), MPFR_RNDN);
    a_delta.subnormalize(mpfr_sub(a_delta(), s(), b_(), MPFR_RNDN), MPFR_RNDN);
    b_delta.subnormalize(mpfr_sub(b_delta(), s(), a_delta(), MPFR_RNDN), MPFR_RNDN);

    a_delta.subnormalize(mpfr_sub(a_delta(), a_(), a_delta(), MPFR_RNDN), MPFR_RNDN);
    b_delta.subnormalize(mpfr_sub(b_delta(), b_(), b_delta(), MPFR_RNDN), MPFR_RNDN);

    a_delta.subnormalize(mpfr_add(a_delta(), a_delta(), b_delta(), MPFR_RNDN), MPFR_RNDN);

    return std::pair<T,T>(s.template get<T>(MPFR_RNDN), a_delta.template get<T>(MPFR_RNDN));
}



} // namespace util

} // namespace p1788

#endif // LIBIEEEP1788_P1788_UTIL_EFT_HPP
