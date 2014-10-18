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


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::neg(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    return representation(-x.second, -x.first);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::neg(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(neg(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::add(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
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


    xl.subnormalize(mpfr_add(xl(), xl(), yl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_add(xu(), xu(), yu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::add(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(add(x.first, y.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sub(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
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


    xl.subnormalize(mpfr_sub(xl(), xl(), yu(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_sub(xu(), xu(), yl(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sub(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(sub(x.first, y.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::mul(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
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

            l.subnormalize(mpfr_mul(l(), xu(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xl(), yl(), MPFR_RNDU), MPFR_RNDU);
        } else if (x.first >= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_mul(l(), xu(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xl(), yu(), MPFR_RNDU), MPFR_RNDU);
        } else {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);

            l.subnormalize(mpfr_mul(l(), xu(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xl(), yl(), MPFR_RNDU), MPFR_RNDU);
        }
    } else if (y.first >= 0.0) {
        if (x.second <= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_mul(l(), xl(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xu(), yl(), MPFR_RNDU), MPFR_RNDU);
        } else if (x.first >= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_mul(l(), xl(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xu(), yu(), MPFR_RNDU), MPFR_RNDU);
        } else {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_mul(l(), xl(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xu(), yu(), MPFR_RNDU), MPFR_RNDU);
        }
    } else {
        if (x.second <= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_mul(l(), xl(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xl(), yl(), MPFR_RNDU), MPFR_RNDU);
        } else if (x.first >= 0.0) {
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_mul(l(), xu(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xu(), yu(), MPFR_RNDU), MPFR_RNDU);
        } else {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var tmp;

            l.subnormalize(mpfr_mul(l(), xl(), yu(), MPFR_RNDD), MPFR_RNDD);
            tmp.subnormalize(mpfr_mul(tmp(), xu(), yl(), MPFR_RNDD), MPFR_RNDD);
            mpfr_min(l(), l(), tmp(), MPFR_RNDD);

            u.subnormalize(mpfr_mul(u(), xl(), yl(), MPFR_RNDU), MPFR_RNDU);
            tmp.subnormalize(mpfr_mul(tmp(), xu(), yu(), MPFR_RNDU), MPFR_RNDU);
            mpfr_max(u(), u(), tmp(), MPFR_RNDU);
        }
    }

    return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::mul(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(mul(x.first, y.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::div(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
{
    if (is_empty(x))
        return x;

    if (is_empty(y))
        return y;

    if (y.first == 0.0 && y.second == 0.0)
        return static_method_empty();

    if (x.first == 0.0 && x.second == 0.0)
        return x;

    if ((y.first < 0.0 && y.second > 0.0)
            || (x.first < 0.0 && x.second > 0.0
                && (y.first == 0.0 || y.second == 0.0)))
        return static_method_entire();

//    if ((x.second < 0.0 || x.first > 0.0) && y.first == 0.0 && y.second == 0.0)
//        return static_method_empty();

    mpfr_var::setup();
    mpfr_var l;
    mpfr_var u;

    if (x.second <= 0.0) {
        if (y.second < 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_div(l(), xu(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_div(u(), xl(), yu(), MPFR_RNDU), MPFR_RNDU);
        } else if (y.first > 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_div(l(), xl(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_div(u(), xu(), yu(), MPFR_RNDU), MPFR_RNDU);
        } else if (y.second == 0.0) {
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);

            l.subnormalize(mpfr_div(l(), xu(), yl(), MPFR_RNDD), MPFR_RNDD);
            mpfr_set_inf(u(), +1);
        } else if (y.first == 0.0) {
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_set_inf(l(), -1);
            u.subnormalize(mpfr_div(u(), xu(), yu(), MPFR_RNDU), MPFR_RNDU);
        }
    } else if (x.first >= 0.0) {
        if (y.second < 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_div(l(), xu(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_div(u(), xl(), yl(), MPFR_RNDU), MPFR_RNDU);
        } else if (y.first > 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_div(l(), xl(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_div(u(), xu(), yl(), MPFR_RNDU), MPFR_RNDU);
        } else if (y.second == 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);

            mpfr_var yl(y.first, MPFR_RNDD);

            mpfr_set_inf(l(), -1);
            u.subnormalize(mpfr_div(u(), xl(), yl(), MPFR_RNDU), MPFR_RNDU);
        } else if (y.first == 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);

            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_div(l(), xl(), yu(), MPFR_RNDD), MPFR_RNDD);
            mpfr_set_inf(u(), +1);
        }
    } else {
        if (y.second < 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_div(l(), xu(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_div(u(), xl(), yu(), MPFR_RNDU), MPFR_RNDU);
        } else if (y.first > 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);

            l.subnormalize(mpfr_div(l(), xl(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_div(u(), xu(), yl(), MPFR_RNDU), MPFR_RNDU);
        }
    }

    return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::div(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(div(x.first, y.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::recip(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    return div(representation(1.0, 1.0), x);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::recip(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(recip(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sqrt(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    if (x.second < 0.0)
        return static_method_empty();

    mpfr_var::setup();

    if (x.first < 0.0) {
        mpfr_var xu(x.second, MPFR_RNDU);

        xu.subnormalize(mpfr_sqrt(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

        return representation(0.0, xu.template get<T>(MPFR_RNDU));
    }

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_sqrt(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_sqrt(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sqrt(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(sqrt(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::fma(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& z)
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

            l.subnormalize(mpfr_fma(l(), xu(), yu(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xl(), yl(), zu(), MPFR_RNDU), MPFR_RNDU);
        } else if (x.first >= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xu(), yl(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xl(), yu(), zu(), MPFR_RNDU), MPFR_RNDU);
        } else {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xu(), yl(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xl(), yl(), zu(), MPFR_RNDU), MPFR_RNDU);
        }
    } else if (y.first >= 0.0) {
        if (x.second <= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xl(), yu(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xu(), yl(), zu(), MPFR_RNDU), MPFR_RNDU);
        } else if (x.first >= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xl(), yl(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xu(), yu(), zu(), MPFR_RNDU), MPFR_RNDU);
        } else {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xl(), yu(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xu(), yu(), zu(), MPFR_RNDU), MPFR_RNDU);
        }
    } else {
        if (x.second <= 0.0) {
            mpfr_var xl(x.first, MPFR_RNDD);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xl(), yu(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xl(), yl(), zu(), MPFR_RNDU), MPFR_RNDU);
        } else if (x.first >= 0.0) {
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xu(), yl(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xu(), yu(), zu(), MPFR_RNDU), MPFR_RNDU);
        } else {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            mpfr_var tmp;

            l.subnormalize(mpfr_fma(l(), xl(), yu(), zl(), MPFR_RNDD), MPFR_RNDD);
            tmp.subnormalize(mpfr_fma(tmp(), xu(), yl(), zl(), MPFR_RNDD), MPFR_RNDD);
            mpfr_min(l(), l(), tmp(), MPFR_RNDD);

            u.subnormalize(mpfr_fma(u(), xl(), yl(), zu(), MPFR_RNDU), MPFR_RNDU);
            tmp.subnormalize(mpfr_fma(tmp(), xu(), yu(), zu(), MPFR_RNDU), MPFR_RNDU);
            mpfr_max(u(), u(), tmp(), MPFR_RNDU);
        }
    }

    return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::fma(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& z)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(fma(x.first, y.first, z.first), p1788::decoration::decoration::trv);
}


//TODO notwendig?
//template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
//typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
//mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::interval_case(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& c,
//                              mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& g,
//                              mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& h)
//{
//    if (is_empty(c))
//        return c;
//
//    if (c.second < 0.0)
//        return g;
//
//    if (c.first > 0.0)
//        return h;
//
//    return hull(g, h);
//}
//
//TODO notwendig?
//template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
//typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
//mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::interval_case(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& c,
//                              mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& g,
//                              mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& h)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return representation_dec(interval_case(c.first, g.first, h.first), p1788::decoration::decoration::trv);
//}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sqr(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();

    if (x.first < 0.0 && x.second > 0.0) {
        mpfr_var u(std::abs(x.first) > x.second ? std::abs(x.first) : x.second, MPFR_RNDU);
        u.subnormalize(mpfr_sqr(u(), u(), MPFR_RNDU), MPFR_RNDU);

        return representation(0.0, u.template get<T>(MPFR_RNDU));
    }

    mpfr_var l(std::abs(x.first) < std::abs(x.second) ? std::abs(x.first) : std::abs(x.second), MPFR_RNDD);
    mpfr_var u(std::abs(x.first) > std::abs(x.second) ? std::abs(x.first) : std::abs(x.second), MPFR_RNDU);

    l.subnormalize(mpfr_sqr(l(), l(), MPFR_RNDD), MPFR_RNDD);
    u.subnormalize(mpfr_sqr(u(), u(), MPFR_RNDU), MPFR_RNDU);

    return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sqr(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(sqr(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::pown(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
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
                u.subnormalize(mpfr_pow_si(u(), u(), p, MPFR_RNDU), MPFR_RNDU);

                return representation(0.0, u.template get<T>(MPFR_RNDU));
            }

            mpfr_var l(std::abs(x.first) < std::abs(x.second) ? std::abs(x.first) : std::abs(x.second), MPFR_RNDD);
            mpfr_var u(std::abs(x.first) > std::abs(x.second) ? std::abs(x.first) : std::abs(x.second), MPFR_RNDU);

            l.subnormalize(mpfr_pow_si(l(), l(), p, MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_pow_si(u(), u(), p, MPFR_RNDU), MPFR_RNDU);

            return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
        }

        // odd
        mpfr_var l(x.first, MPFR_RNDD);
        mpfr_var u(x.second, MPFR_RNDU);

        l.subnormalize(mpfr_pow_si(l(), l(), p, MPFR_RNDD), MPFR_RNDD);
        u.subnormalize(mpfr_pow_si(u(), u(), p, MPFR_RNDU), MPFR_RNDU);

        return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
    }

    // negative
    if (p < 0) {
        if (x.first == 0.0 && x.second == 0.0)
            return static_method_empty();

        // even
        if (p % 2 == 0) {
            if (x.first < 0.0 && x.second > 0.0) {
                mpfr_var l(std::abs(x.first) > x.second ? std::abs(x.first) : x.second, MPFR_RNDU);
                l.subnormalize(mpfr_pow_si(l(), l(), p, MPFR_RNDD), MPFR_RNDD);

                return representation(l.template get<T>(MPFR_RNDD), std::numeric_limits<T>::infinity());
            }

            mpfr_var l(std::abs(x.first) > std::abs(x.second) ? std::abs(x.first) : std::abs(x.second), MPFR_RNDU);
            mpfr_var u(std::abs(x.first) < std::abs(x.second) ? std::abs(x.first) : std::abs(x.second), MPFR_RNDD);

            l.subnormalize(mpfr_pow_si(l(), l(), p, MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_pow_si(u(), u(), p, MPFR_RNDU), MPFR_RNDU);

            return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
        }


        // odd

        if (x.first < 0.0 && x.second > 0.0)
            return static_method_entire();

        if (x.first == 0.0) {
            mpfr_var l(x.second, MPFR_RNDU);
            l.subnormalize(mpfr_pow_si(l(), l(), p, MPFR_RNDD), MPFR_RNDD);

            return representation(l.template get<T>(MPFR_RNDD), std::numeric_limits<T>::infinity());
        }

        if (x.second == 0.0) {
            mpfr_var u(x.first, MPFR_RNDD);
            u.subnormalize(mpfr_pow_si(u(), u(), p, MPFR_RNDU), MPFR_RNDU);

            return representation(-std::numeric_limits<T>::infinity(), u.template get<T>(MPFR_RNDU));
        }


        mpfr_var l(x.second, MPFR_RNDU);
        mpfr_var u(x.first, MPFR_RNDD);

        l.subnormalize(mpfr_pow_si(l(), l(), p, MPFR_RNDD), MPFR_RNDD);
        u.subnormalize(mpfr_pow_si(u(), u(), p, MPFR_RNDU), MPFR_RNDU);

        return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
    }

    // p == 0.0
    return representation(1.0, 1.0);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::pown(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                                   int p)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(pown(x.first, p), p1788::decoration::decoration::trv);
}


// siehe heimlich pow1
//template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
//typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
//mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::pow(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
//                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
//{
//    representation xx = intersect(x, representation(0.0, std::numeric_limits<T>::infinity()));
//
//    if (is_empty(xx))
//        return xx;
//
//    if (is_empty(y))
//        return y;
//
//
//    mpfr_var::setup();
//
//    mpfr_var l_lower;
//    mpfr_var l_upper;
//
//    if (xx.first < 1.0 || 0.0 <= y.first || y.second <= 0.0) {
//        if (xx.first <= 0.0) {
//            l_lower.set(-std::numeric_limits<T>::infinity(), MPFR_RNDD);
//        } else {
//            l_lower.set(xx.first, MPFR_RNDD);
//            mpfr_log(l_lower(), l_lower(), MPFR_RNDD);
//        }
//    }
//
//    if (1.0 < xx.second || 0.0 <= y.first || y.second <= 0.0) {
//        l_upper.set(xx.second, MPFR_RNDU);
//        mpfr_log(l_upper(), l_upper(), MPFR_RNDU);
//    }
//
//    mpfr_var y_lower(y.first, MPFR_RNDD);
//    mpfr_var y_upper(y.second, MPFR_RNDU);
//    mpfr_var m_lower;
//    mpfr_var m_upper;
//
//	if (0.0 <= y.first) {
//		if (xx.second <= 1.0) {
//			if (y.second == 0.0) {
//				m_lower.set(0.0, MPFR_RNDD);
//			} else {
//			    mpfr_mul(m_lower(), y_upper(), l_lower(), MPFR_RNDD);
//			}
//            mpfr_mul(m_upper(), y_lower(), l_upper(), MPFR_RNDU);
//		} else if (1.0 <= xx.first) {
//		    mpfr_mul(m_lower(), y_lower(), l_lower(), MPFR_RNDD);
//			mpfr_mul(m_upper(), y_upper(), l_upper(), MPFR_RNDU);
//		} else { // xx.first < 1 && 1 < xx.second
//			if (y.second == 0) {
//				m_lower.set(0.0, MPFR_RNDD);
//			} else {
//			    mpfr_mul(m_lower(), y_upper(), l_lower(), MPFR_RNDD);
//			}
//			mpfr_mul(m_upper(), y_upper(), l_upper(), MPFR_RNDU);
//		}
//	} else if (y.second <= 0) {
//		if (xx.second <= 1) {
//            mpfr_mul(m_lower(), y_upper(), l_upper(), MPFR_RNDD);
//			mpfr_mul(m_upper(), y_lower(), l_lower(), MPFR_RNDU);
//		} else if (1 <= xx.first) {
//		    mpfr_mul(m_lower(), y_lower(), l_upper(), MPFR_RNDD);
//			mpfr_mul(m_upper(), y_upper(), l_lower(), MPFR_RNDU);
//		} else { // xx.first < 1 && 1 < xx.second
//		    mpfr_mul(m_lower(), y_lower(), l_upper(), MPFR_RNDD);
//			mpfr_mul(m_upper(), y_lower(), l_lower(), MPFR_RNDU);
//		}
//	} else { // y.first < 0 && 0 < y.second
//		if (xx.second <= 1) {
//            mpfr_mul(m_lower(), y_upper(), l_lower(), MPFR_RNDD);
//			mpfr_mul(m_upper(), y_lower(), l_lower(), MPFR_RNDU);
//		} else if (1 <= xx.first) {
//		    mpfr_mul(m_lower(), y_lower(), l_upper(), MPFR_RNDD);
//			mpfr_mul(m_upper(), y_upper(), l_upper(), MPFR_RNDU);
//		} else { // xx.first < 1 && 1 < xx.second
//		    mpfr_mul(m_lower(), y_upper(), l_lower(), MPFR_RNDD);
//		    mpfr_mul(m_upper(), y_lower(), l_upper(), MPFR_RNDD);
//		    mpfr_min(m_lower(), m_lower(), m_upper(), MPFR_RNDD);
//
//            mpfr_mul(y_lower(), y_lower(), l_lower(), MPFR_RNDU);
//            mpfr_mul(y_upper(), y_upper(), l_upper(), MPFR_RNDU);
//		    mpfr_max(m_upper(), y_lower(), y_upper(), MPFR_RNDU);
//		}
//	}
//
//    mpfr_var z_lower;
//    mpfr_var z_upper;
//
//    z_lower.subnormalize(mpfr_exp(z_lower(), m_lower(), MPFR_RNDD), MPFR_RNDD);
//    z_upper.subnormalize(mpfr_exp(z_upper(), m_upper(), MPFR_RNDU), MPFR_RNDU);
//
//    return xx.first == 0.0 && y.second > 0.0 ?
//        hull(representation(z_lower.get(MPFR_RNDD), z_upper.get(MPFR_RNDU)), representation(0.0, 0.0))
//        : representation(z_lower.get(MPFR_RNDD), z_upper.get(MPFR_RNDU));
//}

// siehe heimlich table 3.3 (S.36)
template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::pow(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
{
    representation xx = intersect(x, representation(0.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    if (is_empty(y))
        return y;

    if (xx.second == 0.0) {
        if (y.second <= 0.0) {
            return static_method_empty();
        } else {
            return representation(0.0, 0.0);
        }
    }

    // ab hier enthält xx werte > 0

    mpfr_var::setup();

    mpfr_var x_lower(xx.first == -0.0 ? 0.0 : xx.first, MPFR_RNDD);
    mpfr_var x_upper(xx.second, MPFR_RNDU);
    mpfr_var y_lower(y.first, MPFR_RNDD);
    mpfr_var y_upper(y.second, MPFR_RNDU);

    mpfr_var z_lower;
    mpfr_var z_upper;

    if (0.0 <= y.first) {
        if (xx.second <= 1.0) {
            // special cases: x_lower==0 && (y==[0.0] || y==[0.0,r])

            z_lower.subnormalize(mpfr_pow(z_lower(), x_lower(), y_upper(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_upper(), y_lower(), MPFR_RNDU), MPFR_RNDU);
        } else if (1.0 <= xx.first) {
            z_lower.subnormalize(mpfr_pow(z_lower(), x_lower(), y_lower(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_upper(), y_upper(), MPFR_RNDU), MPFR_RNDU);
        } else { // xx.first < 1 && 1 < xx.second
            // special cases: x_lower==0 && (y==[0.0] || y==[0.0,r])

            z_lower.subnormalize(mpfr_pow(z_lower(), x_lower(), y_upper(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_upper(), y_upper(), MPFR_RNDU), MPFR_RNDU);
        }
    } else if (y.second <= 0.0) {
        if (xx.second <= 1.0) {
            // special cases: x_lower==0 && (y==[0.0] || y==[-r,0.0])

            z_lower.subnormalize(mpfr_pow(z_lower(), x_upper(), y_upper(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_lower(), y_lower(), MPFR_RNDU), MPFR_RNDU);
        } else if (1.0 <= xx.first) {
            z_lower.subnormalize(mpfr_pow(z_lower(), x_upper(), y_lower(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_lower(), y_upper(), MPFR_RNDU), MPFR_RNDU);
        } else { // xx.first < 1 && 1 < xx.second
            // special cases: x_lower==0 && (y==[0.0] || y==[-r,0.0])

            z_lower.subnormalize(mpfr_pow(z_lower(), x_upper(), y_lower(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_lower(), y_lower(), MPFR_RNDU), MPFR_RNDU);
        }
    } else { // y.first < 0 && 0 < y.second
        if (xx.second <= 1.0) {
            // special cases: x_lower==0 && y==[-r,r]
            z_lower.subnormalize(mpfr_pow(z_lower(), x_lower(), y_upper(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_lower(), y_lower(), MPFR_RNDU), MPFR_RNDU);
        } else if (1.0 <= xx.first) {
            z_lower.subnormalize(mpfr_pow(z_lower(), x_upper(), y_lower(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_upper(), y_upper(), MPFR_RNDU), MPFR_RNDU);
        } else { // xx.first < 1 && 1 < xx.second
            // special cases: x_lower==0 && y==[-r,r]

            mpfr_var t_lower;
            mpfr_var t_upper;

            t_lower.subnormalize(mpfr_pow(t_lower(), x_lower(), y_upper(), MPFR_RNDD), MPFR_RNDD);
            t_upper.subnormalize(mpfr_pow(t_upper(), x_lower(), y_lower(), MPFR_RNDU), MPFR_RNDU);

            z_lower.subnormalize(mpfr_pow(z_lower(), x_upper(), y_lower(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_upper(), y_upper(), MPFR_RNDU), MPFR_RNDU);

            mpfr_min(z_lower(), z_lower(), t_lower(), MPFR_RNDD);
            mpfr_max(z_upper(), z_upper(), t_upper(), MPFR_RNDU);
        }
    }

    return representation(z_lower.template get<T>(MPFR_RNDD), z_upper.template get<T>(MPFR_RNDU));

//    return xx.first == 0.0 && y.second > 0.0 ?
//           hull(representation(z_lower.get(MPFR_RNDD), z_upper.get(MPFR_RNDU)), representation(0.0, 0.0))
//           : representation(z_lower.get(MPFR_RNDD), z_upper.get(MPFR_RNDU));
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::pow(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(pow(x.first, y.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::exp(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    l.subnormalize(mpfr_exp(l(), l(), MPFR_RNDD), MPFR_RNDD);
    u.subnormalize(mpfr_exp(u(), u(), MPFR_RNDU), MPFR_RNDU);

    return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::exp(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(exp(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::exp2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    l.subnormalize(mpfr_exp2(l(), l(), MPFR_RNDD), MPFR_RNDD);
    u.subnormalize(mpfr_exp2(u(), u(), MPFR_RNDU), MPFR_RNDU);

    return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::exp2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(exp2(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::exp10(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    l.subnormalize(mpfr_exp10(l(), l(), MPFR_RNDD), MPFR_RNDD);
    u.subnormalize(mpfr_exp10(u(), u(), MPFR_RNDU), MPFR_RNDU);

    return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::exp10(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(exp10(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::log(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    representation xx = intersect(x, representation(0.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    if (x.second <= 0.0)
        return static_method_empty();

    mpfr_var::setup();
    mpfr_var xl(x.first <= 0.0 ? 0.0 : x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_log(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_log(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::log(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(log(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::log2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    representation xx = intersect(x, representation(0.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    if (x.second <= 0.0)
        return static_method_empty();

    mpfr_var::setup();
    mpfr_var xl(x.first <= 0.0 ? 0.0 : x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_log2(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_log2(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::log2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(log2(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::log10(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    representation xx = intersect(x, representation(0.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    if (x.second <= 0.0)
        return static_method_empty();

    mpfr_var::setup();
    mpfr_var xl(x.first <= 0.0 ? 0.0 : x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_log10(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_log10(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::log10(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(log10(x.first), p1788::decoration::decoration::trv);
}


//TODO ueberarbeiten? die Null-Faelle zusammenfassen. Cos dann natuerlich auch
template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sin(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    // pi
//    mpfr_var pi(-1.0, MPFR_RNDD);
//    mpfr_acos(pi(), pi(), MPFR_RNDD);
    mpfr_var pi;
    mpfr_const_pi(pi(), MPFR_RNDD);


    mpfr_var w;
    mpfr_sub(w(), xu(), xl(), MPFR_RNDU);

    mpfr_var tmp;

    // cos(lower)
    tmp.subnormalize(mpfr_cos(tmp(), xl(), MPFR_RNDD), MPFR_RNDD);
    int df_lower = mpfr_sgn(tmp());

    // cos(upper)
    tmp.subnormalize(mpfr_cos(tmp(), xu(), MPFR_RNDU), MPFR_RNDU);
    int df_upper = mpfr_sgn(tmp());

    if (df_lower != df_upper) {
        if (df_lower == 0) {
            if (mpfr_cmp(w(), pi()) > 0)
                return representation(-1.0, 1.0);
        } else if (df_upper == 0) {
            if (mpfr_cmp(w(), pi()) > 0)
                return representation(-1.0, 1.0);
        } else {
            mpfr_var pi2;
            mpfr_mul_si(pi2(), pi(), 2, MPFR_RNDD);

            if (mpfr_cmp(w(), pi2()) > 0)
                return representation(-1.0, 1.0);

            if (df_lower > 0) {
                mpfr_var l1;
                mpfr_var l2;
                l1.subnormalize(mpfr_sin(l1(), xl(), MPFR_RNDD), MPFR_RNDD);
                l2.subnormalize(mpfr_sin(l2(), xu(), MPFR_RNDD), MPFR_RNDD);

                return representation(std::min(l1.template get<T>(MPFR_RNDD), l2.template get<T>(MPFR_RNDD)), 1.0);
            }

            mpfr_var u1;
            mpfr_var u2;
            u1.subnormalize(mpfr_sin(u1(), xl(), MPFR_RNDU), MPFR_RNDU);
            u2.subnormalize(mpfr_sin(u2(), xu(), MPFR_RNDU), MPFR_RNDU);

            return representation(-1.0, std::max(u1.template get<T>(MPFR_RNDU), u2.template get<T>(MPFR_RNDU)));
        }
    } else if (mpfr_cmp(w(), pi()) > 0)
        return representation(-1.0, 1.0);

    mpfr_var l1;
    mpfr_var l2;
    l1.subnormalize(mpfr_sin(l1(), xl(), MPFR_RNDD), MPFR_RNDD);
    l2.subnormalize(mpfr_sin(l2(), xu(), MPFR_RNDD), MPFR_RNDD);

    mpfr_var u1;
    mpfr_var u2;
    u1.subnormalize(mpfr_sin(u1(), xl(), MPFR_RNDU), MPFR_RNDU);
    u2.subnormalize(mpfr_sin(u2(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(std::min(l1.template get<T>(MPFR_RNDD), l2.template get<T>(MPFR_RNDD)),
                          std::max(u1.template get<T>(MPFR_RNDU), u2.template get<T>(MPFR_RNDU)));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sin(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(sin(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::cos(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    // pi
//    mpfr_var pi(-1.0, MPFR_RNDD);
//    mpfr_acos(pi(), pi(), MPFR_RNDD);
    mpfr_var pi;
    mpfr_const_pi(pi(), MPFR_RNDD);

    mpfr_var w;
    mpfr_sub(w(), xu(), xl(), MPFR_RNDU);

    mpfr_var tmp;

    // -sin(lower)
    tmp.subnormalize(mpfr_sin(tmp(), xl(), MPFR_RNDD), MPFR_RNDD);
    mpfr_neg(tmp(), tmp(), MPFR_RNDD);
    int df_lower = mpfr_sgn(tmp());

    // -sin(upper)
    tmp.subnormalize(mpfr_sin(tmp(), xu(), MPFR_RNDU), MPFR_RNDU);
    mpfr_neg(tmp(), tmp(), MPFR_RNDU);
    int df_upper = mpfr_sgn(tmp());

    if (df_lower != df_upper) {
        if (df_lower == 0) {
            if (mpfr_cmp(w(), pi()) > 0)
                return representation(-1.0, 1.0);
        } else if (df_upper == 0) {
            if (mpfr_cmp(w(), pi()) > 0)
                return representation(-1.0, 1.0);
        } else {
            mpfr_var pi2;
            mpfr_mul_si(pi2(), pi(), 2, MPFR_RNDD);

            if (mpfr_cmp(w(), pi2()) > 0)
                return representation(-1.0, 1.0);

            if (df_lower > 0) {
                mpfr_var l1;
                mpfr_var l2;
                l1.subnormalize(mpfr_cos(l1(), xl(), MPFR_RNDD), MPFR_RNDD);
                l2.subnormalize(mpfr_cos(l2(), xu(), MPFR_RNDD), MPFR_RNDD);

                return representation(std::min(l1.template get<T>(MPFR_RNDD), l2.template get<T>(MPFR_RNDD)), 1.0);
            }

            mpfr_var u1;
            mpfr_var u2;
            u1.subnormalize(mpfr_cos(u1(), xl(), MPFR_RNDU), MPFR_RNDU);
            u2.subnormalize(mpfr_cos(u2(), xu(), MPFR_RNDU), MPFR_RNDU);

            return representation(-1.0, std::max(u1.template get<T>(MPFR_RNDU), u2.template get<T>(MPFR_RNDU)));
        }
    } else if (mpfr_cmp(w(), pi()) > 0)
        return representation(-1.0, 1.0);

    mpfr_var l1;
    mpfr_var l2;
    l1.subnormalize(mpfr_cos(l1(), xl(), MPFR_RNDD), MPFR_RNDD);
    l2.subnormalize(mpfr_cos(l2(), xu(), MPFR_RNDD), MPFR_RNDD);

    mpfr_var u1;
    mpfr_var u2;
    u1.subnormalize(mpfr_cos(u1(), xl(), MPFR_RNDU), MPFR_RNDU);
    u2.subnormalize(mpfr_cos(u2(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(std::min(l1.template get<T>(MPFR_RNDD), l2.template get<T>(MPFR_RNDD)),
                          std::max(u1.template get<T>(MPFR_RNDU), u2.template get<T>(MPFR_RNDU)));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::cos(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(cos(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::tan(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
//    return div(sin(x), cos(x));

    if (is_empty(x))
        return x;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_var pi;
    mpfr_const_pi(pi(), MPFR_RNDD);

    mpfr_var w;
    mpfr_sub(w(), xu(), xl(), MPFR_RNDU);

    if (mpfr_cmp(w(), pi()) > 0)
        return static_method_entire();

    xl.subnormalize(mpfr_tan(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_tan(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    if (mpfr_cmp(xl(), xu()) > 0)
        return static_method_entire();

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::tan(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(tan(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::asin(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    representation xx = intersect(x, representation(-1.0, 1.0));

    if (is_empty(xx))
        return xx;

    mpfr_var::setup();

    mpfr_var xl(xx.first, MPFR_RNDD);
    mpfr_var xu(xx.second, MPFR_RNDU);

    xl.subnormalize(mpfr_asin(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_asin(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::asin(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(asin(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::acos(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    representation xx = intersect(x, representation(-1.0, 1.0));

    if (is_empty(xx))
        return xx;

    mpfr_var::setup();

    mpfr_var xl(xx.first, MPFR_RNDD);
    mpfr_var xu(xx.second, MPFR_RNDU);

    xu.subnormalize(mpfr_acos(xu(), xu(), MPFR_RNDD), MPFR_RNDD);
    xl.subnormalize(mpfr_acos(xl(), xl(), MPFR_RNDU), MPFR_RNDU);

    return representation(xu.template get<T>(MPFR_RNDD), xl.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::acos(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(acos(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::atan(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_atan(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_atan(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::atan(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(atan(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::atan2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y,
                                    mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;


    if (is_empty(y) || is_empty(x) ||
            (y.first == 0.0 && y.second == 0.0 && x.first == 0.0 && y.second == 0.0))
        return static_method_empty();

    return static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::atan2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y,
                                    mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(atan2(y.first, x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sinh(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_sinh(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_sinh(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sinh(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(sinh(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::cosh(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();

    if (x.first < 0.0 && x.second > 0.0) {
        mpfr_var xu(std::max(-x.first, x.second), MPFR_RNDU);

        mpfr_cosh(xu(), xu(), MPFR_RNDU);

        return representation(1.0, xu.template get<T>(MPFR_RNDU));
    }

    mpfr_var xl(std::min(std::abs(x.first), std::abs(x.second)), MPFR_RNDD);
    mpfr_var xu(std::max(std::abs(x.first), std::abs(x.second)), MPFR_RNDU);

    xl.subnormalize(mpfr_cosh(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_cosh(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::cosh(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(cosh(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::tanh(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_tanh(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_tanh(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::tanh(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(tanh(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::asinh(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_asinh(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_asinh(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::asinh(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(asinh(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::acosh(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x) || x.second < 1.0)
        return static_method_empty();

    mpfr_var::setup();

    mpfr_var xl(x.first < 1.0 ? 1.0 : x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_acosh(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_acosh(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::acosh(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(acosh(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::atanh(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x) || x.second <= -1.0 || x.first >= 1.0)
        return static_method_empty();

    mpfr_var::setup();

    mpfr_var xl(x.first < -1.0 ? -1.0 : x.first, MPFR_RNDD);
    mpfr_var xu(x.second > 1.0 ? 1.0 : x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_atanh(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_atanh(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::atanh(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(atanh(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sign(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    return representation((x.first < 0.0) ? -1.0 : ((x.first == 0.0) ? 0.0 : 1.0),
                          (x.second < 0.0) ? -1.0 : ((x.second == 0.0) ? 0.0 : 1.0));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sign(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(sign(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::ceil(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    return representation(std::ceil(x.first), std::ceil(x.second));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::ceil(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(ceil(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::floor(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    return representation(std::floor(x.first), std::floor(x.second));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::floor(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(floor(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::trunc(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    return representation(std::trunc(x.first), std::trunc(x.second));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::trunc(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(trunc(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::round_ties_to_even(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    class rnd_controll
    {
        int rnd_;
    public:
        rnd_controll() : rnd_(std::fegetround()) {
            std::fesetround(FE_TONEAREST);
        }

        ~rnd_controll() {
            std::fesetround(rnd_);
        }
    } rnd;

    return representation(std::nearbyint(x.first), std::nearbyint(x.second));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::round_ties_to_even(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(round_ties_to_even(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::round_ties_to_away(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return x;

    return representation(std::round(x.first), std::round(x.second));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::round_ties_to_away(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(round_ties_to_away(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::abs(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x) || x.first >= 0.0)
        return x;

    if (x.second <= 0.0)
        return representation(std::abs(x.second), std::abs(x.first));

    return representation(0.0, std::max(std::abs(x.first), x.second));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::abs(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(abs(x.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::min(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
{
    if (is_empty(x))
        return x;

    if (is_empty(y))
        return y;

    return representation(std::min(x.first, y.first), std::min(x.second, y.second));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::min(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(min(x.first, y.first), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::max(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& y)
{
    if (is_empty(x))
        return x;

    if (is_empty(y))
        return y;

    return representation(std::max(x.first, y.first), std::max(x.second, y.second));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::max(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x,
                                  mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(max(x.first, y.first), p1788::decoration::decoration::trv);
}


} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_ELEM_FUNC_IMPL_HPP
