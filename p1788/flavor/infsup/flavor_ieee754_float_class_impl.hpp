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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_FLOAT_CLASS_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_FLOAT_CLASS_IMPL_HPP

#include <algorithm>
#include <limits>
#include <cassert>

namespace p1788
{

namespace flavor
{

namespace infsup
{


// Constructors

ieee754_flavor<float>::representation ieee754_flavor<float>::constructor_infsup ( )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    return static_method_empty();
}

ieee754_flavor<float>::representation ieee754_flavor<float>::constructor_infsup ( float lower, float upper )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    return representation(lower, upper);
}

ieee754_flavor<float>::representation ieee754_flavor<float>::constructor_infsup ( float point )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    return representation(point, point);
}

template<typename ConstRandomAccessIterator>
ieee754_flavor<float>::representation ieee754_flavor<float>::constructor_infsup ( ConstRandomAccessIterator first, ConstRandomAccessIterator last )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    auto lower = std::min_element(first, last);
    auto upper = std::max_element(first, last);

    return representation(*lower, *upper);
}

ieee754_flavor<float>::representation ieee754_flavor<float>::constructor_infsup ( std::string const& str )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    std::string tmp = str;

    tmp.erase(remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);

    if (tmp == "ENTIRE")
        return static_method_entire();

    if (tmp == "EMPTY")
        return static_method_empty();

    return representation(0.0, 0.0);
}


ieee754_flavor<float>::representation ieee754_flavor<float>::constructor_infsup ( representation const& other )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    return other;
}

template<typename T>
ieee754_flavor<float>::representation ieee754_flavor<float>::constructor_infsup ( representation_type<T> const& other )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    return other;
}


// Methods

float ieee754_flavor<float>::method_lower ( ieee754_flavor<float>::representation const& x )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    return x.first;
}

float ieee754_flavor<float>::method_upper ( ieee754_flavor<float>::representation const& x )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    return x.second;
}

float ieee754_flavor<float>::method_mid ( ieee754_flavor<float>::representation const& x )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    return (x.first + x.second) / 2.0;
}

float ieee754_flavor<float>::method_rad ( ieee754_flavor<float>::representation const& x )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    return (x.second - x.first) / 2.0;
}

// Static Methods

ieee754_flavor<float>::representation ieee754_flavor<float>::static_method_empty ( )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    return representation(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN());
}

ieee754_flavor<float>::representation ieee754_flavor<float>::static_method_entire ( )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    return representation(-std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
}



} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_FLOAT_CLASS_IMPL_HPP
