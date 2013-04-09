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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_ELEM_FUNC_IMPL_HPP

#include "p1788/util/assert.hpp"

namespace p1788
{

namespace flavor
{

namespace infsup
{


template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::neg(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    return representation(-x.second, -x.first);
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::add(mpfr_flavor<T>::representation const& x,
                    mpfr_flavor<T>::representation const& y)
{
    if (is_empty(x))
        return x;

    if (is_empty(y))
        return y;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_var yl(y.first, MPFR_RNDD);
    mpfr_var yu(y.second, MPFR_RNDU);


    mpfr_add(xl(), xl(), yl(), MPFR_RNDD);
    mpfr_add(xu(), xu(), yu, MPFR_RNDU);

    return representation(xl.get(MPFR_RNDD), xu.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::sub(mpfr_flavor<T>::representation const& x,
                    mpfr_flavor<T>::representation const& y)
{
    if (is_empty(x))
        return x;

    if (is_empty(y))
        return y;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_var yl(y.first, MPFR_RNDD);
    mpfr_var yu(y.second, MPFR_RNDU);


    mpfr_sub(xl(), xl(), yu(), MPFR_RNDD);
    mpfr_sub(xu(), xu(), yl, MPFR_RNDU);

    return representation(xl.get(MPFR_RNDD), xu.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::mul(mpfr_flavor<T>::representation const& x,
                    mpfr_flavor<T>::representation const& y)
{
    if (is_empty(x))
        return x;

    if (is_empty(y))
        return y;

    if (x.first == 0.0 && x.second == 0.0)
        return x;

    if (y.first == 0.0 && y.second == 0.0)
        return y;

    if (is_entire(x))
        return x;

    if (is_entire(y))
        return y;


    mpfr_var::setup();
    mpfr_var l;
    mpfr_var u;


    if (y.second <= 0.0) {
        if (x.second <= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_mul(l(), xu(), yu(), MPFR_RNDD);
            mpfr_mul(u(), xl(), yl(), MPFR_RNDU);
        } else if (x.first >= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_mul(l(), xu(), yl(), MPFR_RNDD);
            mpfr_mul(u(), xl(), yu(), MPFR_RNDU);
        } else {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);

            mpfr_mul(l(), xu(), yl(), MPFR_RNDD);
            mpfr_mul(u(), xl(), yl(), MPFR_RNDU);
        }
    } else if (y.first >= 0.0) {
        if (x.second <= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_mul(l(), xl(), yu(), MPFR_RNDD);
            mpfr_mul(u(), xu(), yl(), MPFR_RNDU);
        } else if (x.first >= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_mul(l(), xl(), yl(), MPFR_RNDD);
            mpfr_mul(u(), xu(), yu(), MPFR_RNDU);
        } else {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_mul(l(), xl(), yu(), MPFR_RNDD);
            mpfr_mul(u(), xu(), yu(), MPFR_RNDU);
        }
    } else {
        if (x.second <= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_mul(l(), xl(), yu(), MPFR_RNDD);
            mpfr_mul(u(), xl(), yl(), MPFR_RNDU);
        } else if (x.first >= 0.0) {
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_mul(l(), xu(), yl(), MPFR_RNDD);
            mpfr_mul(u(), xu(), yu(), MPFR_RNDU);
        } else {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var tmp;

            mpfr_mul(l(), xl(), yu(), MPFR_RNDD);
            mpfr_mul(tmp(), xu(), yl(), MPFR_RNDD);
            mpfr_min(l(), l(), tmp(), MPFR_RNDD);

            mpfr_mul(u(), xl(), yl(), MPFR_RNDU);
            mpfr_mul(tmp(), xu(), yu(), MPFR_RNDU);
            mpfr_max(u(), u(), tmp(), MPFR_RNDU);
        }
    }

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::div(mpfr_flavor<T>::representation const& x,
                    mpfr_flavor<T>::representation const& y)
{
    if (is_empty(x))
        return x;

    if (is_empty(y))
        return y;

    if ((y.first < 0.0 && y.second > 0.0)
            || (x.first <= 0.0 && x.second >= 0.0
                && (y.first == 0.0 || y.second == 0.0)))
        return static_method_entire();


    if (x.second <= 0.0) {
        if (y.second < 0.0) {

        } else if (y.first > 0.0) {

        } else {
            return static_method_empty();
        }
    } else if (x.first >= 0.0) {
            if (y.second < 0.0) {

        } else if (y.first > 0.0) {

        } else {
            return static_method_empty();
        }
    } else {
            if (y.second < 0.0) {

        } else if (y.first > 0.0) {

        }
    }


    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::inv(mpfr_flavor<T>::representation const& x)
{
    return div(representation(1.0, 1.0), x);
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::sqrt(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    if (x.second < 0.0)
        return static_method_empty();

    mpfr_var::setup();

    mpfr_var xl(x.first < 0.0 ? 0.0 : x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_sqrt(xl(), xl(), MPFR_RNDD);
    mpfr_sqrt(xu(), xu(), MPFR_RNDU);

    return representation(xl.get(MPFR_RNDD), xu.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::fma(mpfr_flavor<T>::representation const& x,
                    mpfr_flavor<T>::representation const& y,
                    mpfr_flavor<T>::representation const& z)
{
    if (is_empty(x))
        return x;

    if (is_empty(y))
        return y;

    if (is_empty(z))
        return z;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::interval_case(mpfr_flavor<T>::representation const&,
                              mpfr_flavor<T>::representation const&,
                              mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::sqr(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::pown(mpfr_flavor<T>::representation const&,
                     int)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::pow(mpfr_flavor<T>::representation const&,
                    mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::exp(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::exp2(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::exp10(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::log(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::log2(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::log10(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::sin(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::cos(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::tan(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::asin(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::acos(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::atan(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::atan2(mpfr_flavor<T>::representation const&,
                      mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::sinh(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::cosh(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;
    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::tanh(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::asinh(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::acosh(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::atanh(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::sign(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::ceil(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::floor(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::trunc(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::round_ties_to_even(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::round_ties_to_away(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::abs(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
template<typename ConstRandomAccessIterator>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::min(ConstRandomAccessIterator, ConstRandomAccessIterator)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
template<typename ConstRandomAccessIterator>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::max(ConstRandomAccessIterator,
                    ConstRandomAccessIterator)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}


} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_ELEM_FUNC_IMPL_HPP
