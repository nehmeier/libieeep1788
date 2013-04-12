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

    if ((x.second < 0.0 || x.first > 0.0) && y.first == 0.0 && y.second == 0.0)
        return static_method_empty();

    mpfr_var::setup();
    mpfr_var l;
    mpfr_var u;

    if (x.second <= 0.0) {
        if (y.second < 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_div(l(), xu(), yl(), MPFR_RNDD);
            mpfr_div(u(), xl(), yu(), MPFR_RNDU);
        } else if (y.first > 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_div(l(), xl(), yl(), MPFR_RNDD);
            mpfr_div(u(), xu(), yu(), MPFR_RNDU);
        } else if (y.second == 0.0) {
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);

            mpfr_div(l(), xu(), yl(), MPFR_RNDD);
            mpfr_set_inf(u(), +1);
        } else if (y.first == 0.0) {
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_set_inf(l(), -1);
            mpfr_div(u(), xu(), yu(), MPFR_RNDU);
        }
    } else if (x.first >= 0.0) {
        if (y.second < 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_div(l(), xu(), yu(), MPFR_RNDD);
            mpfr_div(u(), xl(), yl(), MPFR_RNDU);
        } else if (y.first > 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_div(l(), xl(), yu(), MPFR_RNDD);
            mpfr_div(u(), xu(), yl(), MPFR_RNDU);
        } else if (y.second == 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);

            mpfr_var yl(y.first, MPFR_RNDD);

            mpfr_set_inf(l(), -1);
            mpfr_div(u(), xl(), yl(), MPFR_RNDU);
        } else if (y.first == 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);

            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_div(l(), xl(), yu(), MPFR_RNDD);
            mpfr_set_inf(u(), +1);
        }
    } else {
        if (y.second < 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_div(l(), xu(), yu(), MPFR_RNDD);
            mpfr_div(u(), xl(), yu(), MPFR_RNDU);
        } else if (y.first > 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);

            mpfr_div(l(), xl(), yl(), MPFR_RNDD);
            mpfr_div(u(), xu(), yl(), MPFR_RNDU);
        }
    }

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
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

    if (x.first < 0.0) {
        mpfr_var xu(x.second, MPFR_RNDU);

        mpfr_sqrt(xu(), xu(), MPFR_RNDU);

        return representation(0.0, xu.get(MPFR_RNDU));
    }

    mpfr_var xl(x.first, MPFR_RNDD);
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

    if (x.first == 0.0 && x.second == 0.0)
        return z;

    if (y.first == 0.0 && y.second == 0.0)
        return z;

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

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            mpfr_fma(l(), xu(), yu(), zl(), MPFR_RNDD);
            mpfr_fma(u(), xl(), yl(), zu(), MPFR_RNDU);
        } else if (x.first >= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            mpfr_fma(l(), xu(), yl(), zl(), MPFR_RNDD);
            mpfr_fma(u(), xl(), yu(), zu(), MPFR_RNDU);
        } else {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            mpfr_fma(l(), xu(), yl(), zl(), MPFR_RNDD);
            mpfr_fma(u(), xl(), yl(), zu(), MPFR_RNDU);
        }
    } else if (y.first >= 0.0) {
        if (x.second <= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            mpfr_fma(l(), xl(), yu(), zl(), MPFR_RNDD);
            mpfr_fma(u(), xu(), yl(), zu(), MPFR_RNDU);
        } else if (x.first >= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            mpfr_fma(l(), xl(), yl(), zl(), MPFR_RNDD);
            mpfr_fma(u(), xu(), yu(), zu(), MPFR_RNDU);
        } else {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            mpfr_fma(l(), xl(), yu(), zl(), MPFR_RNDD);
            mpfr_fma(u(), xu(), yu(), zu(), MPFR_RNDU);
        }
    } else {
        if (x.second <= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            mpfr_fma(l(), xl(), yu(), zl(), MPFR_RNDD);
            mpfr_fma(u(), xl(), yl(), zu(), MPFR_RNDU);
        } else if (x.first >= 0.0) {
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            mpfr_fma(l(), xu(), yl(), zl(), MPFR_RNDD);
            mpfr_fma(u(), xu(), yu(), zu(), MPFR_RNDU);
        } else {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            mpfr_var tmp;

            mpfr_fma(l(), xl(), yu(), zl(), MPFR_RNDD);
            mpfr_fma(tmp(), xu(), yl(), zl(), MPFR_RNDD);
            mpfr_min(l(), l(), tmp(), MPFR_RNDD);

            mpfr_fma(u(), xl(), yl(), zu(), MPFR_RNDU);
            mpfr_fma(tmp(), xu(), yu(), zu(), MPFR_RNDU);
            mpfr_max(u(), u(), tmp(), MPFR_RNDU);
        }
    }

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::interval_case(mpfr_flavor<T>::representation const& c,
                              mpfr_flavor<T>::representation const& g,
                              mpfr_flavor<T>::representation const& h)
{
    if (is_empty(c))
        return c;

    if (c.second < 0.0)
        return g;

    if (c.first > 0.0)
        return h;

    return hull(g, h);
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::sqr(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();

    if (x.first < 0.0 && x.second > 0.0) {
        mpfr_var u(std::abs(x.first) > x.second ? std::abs(x.first) : x.second, MPFR_RNDU);
        mpfr_sqr(u(), u(), MPFR_RNDU);

        return representation(0.0, u.get(MPFR_RNDU));
    }

    mpfr_var l(std::abs(x.first) < std::abs(x.second) ? std::abs(x.first) : std::abs(x.second), MPFR_RNDD);
    mpfr_var u(std::abs(x.first) > std::abs(x.second) ? std::abs(x.first) : std::abs(x.second), MPFR_RNDU);

    mpfr_sqr(l(), l(), MPFR_RNDD);
    mpfr_sqr(u(), u(), MPFR_RNDU);

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::pown(mpfr_flavor<T>::representation const& x,
                     int p)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();

    // positive
    if (p > 0) {
        // even
        if (p % 2 == 0) {
            if (x.first < 0.0 && x.second > 0.0) {
                mpfr_var u(std::abs(x.first) > x.second ? std::abs(x.first) : x.second, MPFR_RNDU);
                mpfr_pow_si(u(), u(), p, MPFR_RNDU);

                return representation(0.0, u.get(MPFR_RNDU));
            }

            mpfr_var l(std::abs(x.first) < std::abs(x.second) ? std::abs(x.first) : std::abs(x.second), MPFR_RNDD);
            mpfr_var u(std::abs(x.first) > std::abs(x.second) ? std::abs(x.first) : std::abs(x.second), MPFR_RNDU);

            mpfr_pow_si(l(), l(), p, MPFR_RNDD);
            mpfr_pow_si(u(), u(), p, MPFR_RNDU);

            return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
        }

        // odd
        mpfr_var l(x.first, MPFR_RNDD);
        mpfr_var u(x.second, MPFR_RNDU);

        mpfr_pow_si(l(), l(), p, MPFR_RNDD);
        mpfr_pow_si(u(), u(), p, MPFR_RNDU);

        return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
    }

    // negative
    if (p < 0) {
        // even
        if (p % 2 == 0) {
            if (x.first < 0.0 && x.second > 0.0) {
                mpfr_var l(std::abs(x.first) > x.second ? std::abs(x.first) : x.second, MPFR_RNDU);
                mpfr_pow_si(l(), l(), p, MPFR_RNDD);

                return representation(l.get(MPFR_RNDD), std::numeric_limits<T>::infinity());
            }

            mpfr_var l(std::abs(x.first) > std::abs(x.second) ? std::abs(x.first) : std::abs(x.second), MPFR_RNDU);
            mpfr_var u(std::abs(x.first) < std::abs(x.second) ? std::abs(x.first) : std::abs(x.second), MPFR_RNDD);

            mpfr_pow_si(l(), l(), p, MPFR_RNDD);
            mpfr_pow_si(u(), u(), p, MPFR_RNDU);

            return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
        }

        // odd
        if (x.first < 0.0 && x.second > 0.0)
            return static_method_entire();

        if (x.first > 0.0) {
            mpfr_var l(x.second, MPFR_RNDU);
            mpfr_var u(x.first, MPFR_RNDD);

            mpfr_pow_si(l(), l(), p, MPFR_RNDD);
            mpfr_pow_si(u(), u(), p, MPFR_RNDU);

            return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
        } else {
            mpfr_var l(x.first, MPFR_RNDD);
            mpfr_var u(x.second, MPFR_RNDU);

            mpfr_pow_si(l(), l(), p, MPFR_RNDD);
            mpfr_pow_si(u(), u(), p, MPFR_RNDU);

            return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
        }
    }

    // p == 0.0
    return representation(1.0, 1.0);
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::pow(mpfr_flavor<T>::representation const& x,
                    mpfr_flavor<T>::representation const& y)
{
    representation xx = intersect(x, representation(0.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    if (is_empty(y))
        return y;

    return xx.first == 0.0 && y.second > 0.0 ? hull(exp(mul(y,log(xx))), representation(0.0, 0.0)) : exp(mul(y,log(xx)));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::exp(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    mpfr_exp(l(), l(), MPFR_RNDD);
    mpfr_exp(u(), u(), MPFR_RNDU);

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::exp2(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    mpfr_exp2(l(), l(), MPFR_RNDD);
    mpfr_exp2(u(), u(), MPFR_RNDU);

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::exp10(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    mpfr_exp10(l(), l(), MPFR_RNDD);
    mpfr_exp10(u(), u(), MPFR_RNDU);

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::log(mpfr_flavor<T>::representation const& x)
{
    representation xx = intersect(x, representation(0.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    mpfr_log(l(), l(), MPFR_RNDD);
    mpfr_log(u(), u(), MPFR_RNDU);

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::log2(mpfr_flavor<T>::representation const& x)
{
    representation xx = intersect(x, representation(0.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    mpfr_log2(l(), l(), MPFR_RNDD);
    mpfr_log2(u(), u(), MPFR_RNDU);

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::log10(mpfr_flavor<T>::representation const& x)
{
    representation xx = intersect(x, representation(0.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    mpfr_log10(l(), l(), MPFR_RNDD);
    mpfr_log10(u(), u(), MPFR_RNDU);

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
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
mpfr_flavor<T>::sign(mpfr_flavor<T>::representation const& x)
{
    return representation((x.first < 0.0) ? -1.0 : ((x.first == 0.0) ? 0.0 : 1.0),
                          (x.second < 0.0) ? -1.0 : ((x.second == 0.0) ? 0.0 : 1.0));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::ceil(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    return representation(std::ceil(x.first), std::ceil(x.second));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::floor(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    return representation(std::floor(x.first), std::floor(x.second));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::trunc(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    return representation(std::trunc(x.first), std::trunc(x.second));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::round_ties_to_even(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    class rnd_controll {
        int rnd_;

        rnd_controll() : rnd_(std::fegetround()) {
            std::fesetround(FE_TONEAREST);
        }

        ~rnd_controll() {
            std::fesetround(rnd_);
        }
    } rnd;

    return representation(std::nearbyint(x.first), std::nearbyint(x.second));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::round_ties_to_away(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    return representation(std::round(x.first), std::round(x.second));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::abs(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x) || x.first >= 0.0)
        return x;

    if (x.second <= 0.0)
        return representation(std::abs(x.second), std::abs(x.first));

    return representation(0.0, std::max(std::abs(x.first), x.second));
}

template<typename T>
template<typename ConstRandomAccessIterator>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::min(ConstRandomAccessIterator first, ConstRandomAccessIterator last)
{
    if (first >= last)
        return static_method_empty();

    representation r(std::numeric_limits<T>::max(), std::numeric_limits<T>::infinity());

    for(auto iter = first; iter != last; iter++) {
        r.first = std::min(r.first, iter.first);
        r.second = std::min(r.second, iter.second);
    }

    return r;
}

template<typename T>
template<typename ConstRandomAccessIterator>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::max(ConstRandomAccessIterator first,
                    ConstRandomAccessIterator last)
{
    if (first >= last)
        return static_method_empty();

    representation r(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::max());

    for(auto iter = first; iter != last; iter++) {
        r.first = std::max(r.first, iter.first);
        r.second = std::max(r.second, iter.second);
    }

    return r;
}


} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_ELEM_FUNC_IMPL_HPP
