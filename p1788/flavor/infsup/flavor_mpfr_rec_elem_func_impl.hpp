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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REC_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REC_ELEM_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::rootn(mpfr_flavor<T>::representation const& x, int q)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();

    if (q > 0) {
        if (q % 2 == 1) {
            mpfr_var xl(x.first , MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_root(xl(), xl(), q, MPFR_RNDD);
            mpfr_root(xu(), xu(), q, MPFR_RNDU);

            return representation(xl.get(MPFR_RNDD), xu.get(MPFR_RNDU));
        } else {
            if (x.second < 0.0)
                return mpfr_flavor<T>::static_method_empty();

            mpfr_var xl(x.first < 0.0 ? 0.0 : x.first , MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_root(xl(), xl(), q, MPFR_RNDD);
            mpfr_root(xu(), xu(), q, MPFR_RNDU);

            return representation(xl.get(MPFR_RNDD), xu.get(MPFR_RNDU));
        }
    } else if (q < 0) {
        return inv(rootn(x, -q));
    }

    // TODO, check ?
    // In case of q == 0, function not defined
    return mpfr_flavor<T>::static_method_empty();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::expm1(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    mpfr_expm1(l(), l(), MPFR_RNDD);
    mpfr_expm1(u(), u(), MPFR_RNDU);

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::exp2m1(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    mpfr_exp2(l(), l(), MPFR_RNDD);
    mpfr_sub_si(l(), l(), 1, MPFR_RNDD);
    mpfr_exp2(u(), u(), MPFR_RNDU);
    mpfr_sub_si(u(), u(), 1, MPFR_RNDU);

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::exp10m1(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    mpfr_exp10(l(), l(), MPFR_RNDD);
    mpfr_sub_si(l(), l(), 1, MPFR_RNDD);
    mpfr_exp10(u(), u(), MPFR_RNDU);
    mpfr_sub_si(u(), u(), 1, MPFR_RNDU);

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::logp1(mpfr_flavor<T>::representation const& x)
{
    representation xx = intersect(x, representation(-1.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    mpfr_log1p(l(), l(), MPFR_RNDD);
    mpfr_log1p(u(), u(), MPFR_RNDU);

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::log2p1(mpfr_flavor<T>::representation const& x)
{
    representation xx = intersect(x, representation(-1.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    mpfr_add_si(l(), l(), 1, MPFR_RNDD);
    mpfr_add_si(u(), u(), 1, MPFR_RNDU);

    mpfr_log2(l(), l(), MPFR_RNDD);
    mpfr_log2(u(), u(), MPFR_RNDU);

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::log10p1(mpfr_flavor<T>::representation const& x)
{
    representation xx = intersect(x, representation(-1.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    mpfr_add_si(l(), l(), 1, MPFR_RNDD);
    mpfr_add_si(u(), u(), 1, MPFR_RNDU);

    mpfr_log10(l(), l(), MPFR_RNDD);
    mpfr_log10(u(), u(), MPFR_RNDU);

    return representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::compoundm1(mpfr_flavor<T>::representation const&,
                           mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::hypot(mpfr_flavor<T>::representation const& x,
                      mpfr_flavor<T>::representation const& y)
{
    if (is_empty(x))
        return x;

    if (is_empty(y))
        return y;

    mpfr_var::setup();

    mpfr_var xl((x.first < 0.0 && x.second > 0.0) ? 0.0 : std::min(std::abs(x.first), std::abs(x.second)), MPFR_RNDD);
    mpfr_var xu(std::max(std::abs(x.first), std::abs(x.second)), MPFR_RNDU);

    mpfr_var yl((y.first < 0.0 && y.second > 0.0) ? 0.0 : std::min(std::abs(y.first), std::abs(y.second)), MPFR_RNDD);
    mpfr_var yu(std::max(std::abs(y.first), std::abs(y.second)), MPFR_RNDU);


    mpfr_hypot(xl(), xl(), yl(), MPFR_RNDD);
    mpfr_hypot(xu(), xu(), yu(), MPFR_RNDU);

    return representation(xl.get(MPFR_RNDD), xu.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::r_sqrt(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return x;

    if (x.second < 0.0)
        return static_method_empty();

    mpfr_var::setup();

    if (x.first < 0.0) {
        mpfr_var xu(x.second, MPFR_RNDU);

        mpfr_rec_sqrt(xu(), xu(), MPFR_RNDD);

        return representation(xu.get(MPFR_RNDD), std::numeric_limits<T>::infinity());
    }

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_rec_sqrt(xu(), xu(), MPFR_RNDD);
    mpfr_rec_sqrt(xl(), xl(), MPFR_RNDU);

    return representation(xu.get(MPFR_RNDD), xl.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::sin_pi(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::cos_pi(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::tan_pi(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::asin_pi(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::acos_pi(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::atan_pi(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::atan2_pi(mpfr_flavor<T>::representation const&,
                         mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REC_ELEM_FUNC_IMPL_HPP
