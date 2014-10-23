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

#ifndef LIBIEEEP1788_TEST_UTIL_MPFR_BIN_IEEE754_FLAVOR_IO_TEST_UTIL_HPP
#define LIBIEEEP1788_TEST_UTIL_MPFR_BIN_IEEE754_FLAVOR_IO_TEST_UTIL_HPP

#include <iostream>

#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"

namespace std
{
    ostream& operator<<(ostream& s, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<float>::representation const& r)
    {
        s << '<' << r.first << ',' << r.second << '>';
        return s;
    }

    ostream& operator<<(ostream& s, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<double>::representation const& r)
    {
        s << '<' << r.first << ',' << r.second << '>';
        return s;
    }

    ostream& operator<<(ostream& s, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<long double>::representation const& r)
    {
        s << '<' << r.first << ',' << r.second << '>';
        return s;
    }

    ostream& operator<<(ostream& s, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<float>::representation_dec const& r)
    {
        s << r.first << '_' << r.second;
        return s;
    }

    ostream& operator<<(ostream& s, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<double>::representation_dec const& r)
    {
        s << r.first << '_' << r.second;
        return s;
    }

    ostream& operator<<(ostream& s, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<long double>::representation_dec const& r)
    {
        s << r.first << '_' << r.second;
        return s;
    }
}

#endif // LIBIEEEP1788_TEST_UTIL_MPFR_BIN_IEEE754_FLAVOR_IO_TEST_UTIL_HPP
