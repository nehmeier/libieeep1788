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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_BOOL_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_BOOL_FUNC_IMPL_HPP

#include <cmath>
#include <limits>

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::is_empty(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    return std::isnan(x.first) && std::isnan(x.second);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::is_empty(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::is_entire(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    return x.first == -std::numeric_limits<T>::infinity()
           && x.second == std::numeric_limits<T>::infinity();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::is_entire(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::is_equal(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                         mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
{
    return (is_empty(x) && is_empty(y))
           || (x.first == y.first && x.second == y.second);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::is_equal(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::subset(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                             mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
{
    return is_empty(x) || (y.first <= x.first && x.second <= y.second);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::subset(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&,
                             mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::less(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                     mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
{
    return (is_empty(x) && is_empty(y))
           || (x.first <= y.first && x.second <= y.second);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::less(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&,
                     mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::precedes(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                         mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
{
    return is_empty(x) || is_empty(y) || x.second <= y.first;
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::precedes(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                         mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::is_interior(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                            mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
{
    return is_empty(x)
           || ((y.first < x.first
                || (y.first == -std::numeric_limits<T>::infinity()
                    && x.first == -std::numeric_limits<T>::infinity()))
               && (x.second < y.second
                   || (x.second == std::numeric_limits<T>::infinity()
                       && y.second == std::numeric_limits<T>::infinity())));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::is_interior(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                            mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::strictly_less(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                              mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
{
    return (is_empty(x) && is_empty(y))
           || ((x.first < y.first
                || (x.first == -std::numeric_limits<T>::infinity()
                    && y.first == -std::numeric_limits<T>::infinity()))
               && (x.second < y.second
                   || (x.second == std::numeric_limits<T>::infinity()
                       && y.second == std::numeric_limits<T>::infinity())));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::strictly_less(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                              mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::strictly_precedes(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
{
    return is_empty(x) || is_empty(y) || x.second < y.first;
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::strictly_precedes(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::are_disjoint(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                             mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
{
    return is_empty(x) || is_empty(y) || x.second < y.first || y.second < x.first;
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
bool
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::are_disjoint(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                             mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_BOOL_FUNC_IMPL_HPP
