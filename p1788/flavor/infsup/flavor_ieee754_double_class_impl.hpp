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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_CLASS_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_CLASS_IMPL_HPP

#include <algorithm>
#include <limits>

#include "p1788/util/assert.hpp"

namespace p1788
{

namespace flavor
{

namespace infsup
{


// Constructors

ieee754_flavor<double>::representation
ieee754_flavor<double>::constructor_infsup()
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return static_method_empty();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::constructor_infsup(double lower, double upper)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation(lower, upper);
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::constructor_infsup(double point)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation(point, point);
}

template<typename ConstRandomAccessIterator>
ieee754_flavor<double>::representation
ieee754_flavor<double>::constructor_infsup(ConstRandomAccessIterator first,
        ConstRandomAccessIterator last)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    auto result = std::minmax_element(first, last);

    return representation(*result.first, *result.second);
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::constructor_infsup(std::string const& str)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    std::string tmp = str;

    tmp.erase(remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);

    if (tmp == "ENTIRE")
        return static_method_entire();

    if (tmp == "EMPTY")
        return static_method_empty();

    return representation(0.0, 0.0);
}


ieee754_flavor<double>::representation
ieee754_flavor<double>::constructor_infsup(representation const& other)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return other;
}

template<typename T>
ieee754_flavor<double>::representation
ieee754_flavor<double>::constructor_infsup( representation_type<T> const& other)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return other;
}


// Methods

double
ieee754_flavor<double>::method_lower(ieee754_flavor<double>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return x.first;
}

double
ieee754_flavor<double>::method_upper(ieee754_flavor<double>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return x.second;
}

double
ieee754_flavor<double>::method_mid(ieee754_flavor<double>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return (x.first + x.second) / 2.0;
}

double
ieee754_flavor<double>::method_rad(ieee754_flavor<double>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return (x.second - x.first) / 2.0;
}

// Static Methods

ieee754_flavor<double>::representation
ieee754_flavor<double>::static_method_empty()
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation(std::numeric_limits<double>::quiet_NaN(),
                          std::numeric_limits<double>::quiet_NaN());
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::static_method_entire()
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation(-std::numeric_limits<double>::infinity(),
                          std::numeric_limits<double>::infinity());
}



} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_CLASS_IMPL_HPP
