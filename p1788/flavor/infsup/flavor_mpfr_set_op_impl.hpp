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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_SET_OP_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_SET_OP_IMPL_HPP

#include <algorithm>

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::intersect(mpfr_flavor<T, SUBNORMALIZE>::representation const& x,
                          mpfr_flavor<T, SUBNORMALIZE>::representation const& y)
{
    if (are_disjoint(x, y))
        return static_method_empty();
    else
        return representation(std::max(x.first, y.first),
                              std::min(x.second, y.second));
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::intersect(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x,
                          mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::hull(mpfr_flavor<T, SUBNORMALIZE>::representation const& x,
                     mpfr_flavor<T, SUBNORMALIZE>::representation const& y)
{
    if (is_empty(x))
        return y;
    else if (is_empty(y))
        return x;
    else
        return representation(std::min(x.first, y.first),
                              std::max(x.second, y.second));
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::hull(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x,
                     mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire();
}


//TODO hull(s)   P1788/8.1 12.8.1

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_SET_OP_IMPL_HPP
