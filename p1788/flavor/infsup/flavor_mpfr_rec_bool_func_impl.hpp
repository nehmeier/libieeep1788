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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REC_BOOL_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REC_BOOL_FUNC_IMPL_HPP

#include <limits>
#include <cmath>

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T, subnormalize SUBNORMALIZE>
bool mpfr_flavor<T, SUBNORMALIZE>::is_common(mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    //TODO ist das in D8.1 7.2 so gemeint?
    return !is_empty(x)
        && x.first > -std::numeric_limits<T>::infinity()
        && x.second < std::numeric_limits<T>::infinity();
}

template<typename T, subnormalize SUBNORMALIZE>
bool mpfr_flavor<T, SUBNORMALIZE>::is_common(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x)
{
    //TODO ist das in D8.1 7.2 so gemeint? oder hier die decoration verwenden?
    return is_common(x.first);
}


template<typename T, subnormalize SUBNORMALIZE>
bool mpfr_flavor<T, SUBNORMALIZE>::is_singleton(mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    return x.first == x.second;
}

template<typename T, subnormalize SUBNORMALIZE>
bool mpfr_flavor<T, SUBNORMALIZE>::is_singleton(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x)
{
    return is_singleton(x.first);
}


template<typename T, subnormalize SUBNORMALIZE>
bool mpfr_flavor<T, SUBNORMALIZE>::is_member(T m, mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    return x.first <= m && m <= x.second
        && std::abs(m) != std::numeric_limits<T>::infinity();
}

template<typename T, subnormalize SUBNORMALIZE>
bool mpfr_flavor<T, SUBNORMALIZE>::is_member(T m, mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x)
{
    return is_member(m, x.first);
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REC_BOOL_FUNC_IMPL_HPP
