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

#ifndef LIBIEEEP1788_P1788_INFSUP_INTERVAL_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_INTERVAL_ELEM_FUNC_IMPL_HPP

#include <vector>
#include <algorithm>


namespace p1788
{

namespace infsup
{

// -----------------------------------------------------------------------------
// Forward elementary functions
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator+ ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::pos(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator- ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::neg(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator+ ( interval<T, Flavor> const& x, interval<T, Flavor> const& y )
{
    return interval<T, Flavor>(Flavor<T>::add(x.rep(), y.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator- ( interval<T, Flavor> const& x, interval<T, Flavor> const& y )
{
    return interval<T, Flavor>(Flavor<T>::sub(x.rep(), y.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator* ( interval<T, Flavor> const& x, interval<T, Flavor> const& y )
{
    return interval<T, Flavor>(Flavor<T>::mul(x.rep(), y.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator/ ( interval<T, Flavor> const& x, interval<T, Flavor> const& y )
{
    return interval<T, Flavor>(Flavor<T>::div(x.rep(), y.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> inv ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::inv(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sqrt ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::sqrt(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> fma ( interval<T, Flavor> const& x, interval<T, Flavor> const& y, interval<T, Flavor> const& z )
{
    return interval<T, Flavor>(Flavor<T>::fma(x.rep(), y.rep(), z.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> interval_case ( interval<T, Flavor> const& c, interval<T, Flavor> const& g, interval<T, Flavor> const& h )
{
    return interval<T, Flavor>(Flavor<T>::interval_case(c.rep(), g.rep(), h.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sqr ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::sqr(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> pown ( interval<T, Flavor> const& x, int p )
{
    return interval<T, Flavor>(Flavor<T>::pown(x.rep(), p));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> pow ( interval<T, Flavor> const& x, interval<T, Flavor> const& y )
{
    return interval<T, Flavor>(Flavor<T>::pow(x.rep(), y.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> exp ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::exp(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> exp2 ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::exp2(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> exp10 ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::exp10(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> log ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::log(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> log2 ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::log2(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> log10 ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::log10(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sin ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::sin(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cos ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::cos(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> tan ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::tan(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> asin ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::asin(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> acos ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::acos(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atan ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::atan(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atan2 ( interval<T, Flavor> const& y, interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::atan2(y.rep(), x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sinh ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::sinh(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cosh ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::cosh(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> tanh ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::tanh(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> asinh ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::asinh(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> acosh ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::acosh(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atanh ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::atanh(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sign ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::sign(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> ceil ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::ceil(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> floor ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::floor(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> trunc ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::trunc(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> round_ties_to_even ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::round_ties_to_even(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> round_ties_to_away ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::round_ties_to_away(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> abs ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::abs(x.rep()));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> min ( std::initializer_list< interval<T, Flavor>> intervals )
{
    std::vector<typename Flavor<T>::representation> v;

    std::transform(intervals.begin(), intervals.end(), std::back_inserter(v), [] (interval<T, Flavor> const & x) {
        return x.rep();
    } );

    typename std::vector<typename Flavor<T>::representation>::const_iterator first = v.begin();
    typename std::vector<typename Flavor<T>::representation>::const_iterator last = v.end();

    return interval<T, Flavor>(Flavor<T>::min(first, last));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> max ( std::initializer_list< interval<T, Flavor>> intervals )
{
    std::vector<typename Flavor<T>::representation> v;

    std::transform(intervals.begin(), intervals.end(), std::back_inserter(v), [] (interval<T, Flavor> const & x) {
        return x.rep();
    } );

    typename std::vector<typename Flavor<T>::representation>::const_iterator first = v.begin();
    typename std::vector<typename Flavor<T>::representation>::const_iterator last = v.end();

    return interval<T, Flavor>(Flavor<T>::max(first, last));
}




} // namespace infsup

} // namespace p1788

#endif // LIBIEEEP1788_P1788_INFSUP_INTERVAL_ELEM_FUNC_IMPL_HPP
