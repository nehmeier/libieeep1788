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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REV_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REV_ELEM_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::sqr_rev(mpfr_flavor<T>::representation const& c,
                        mpfr_flavor<T>::representation const& x)
{
    representation p = sqrt(c);
    representation n = neg(p);

    return hull(intersect(p, x), intersect(n, x));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::sqr_rev(mpfr_flavor<T>::representation const& c)
{
    return sqrt_rev(c, static_method_entire());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::inv_rev(mpfr_flavor<T>::representation const& c,
                        mpfr_flavor<T>::representation const& x)
{
    return intersect(inv(c), x);
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::inv_rev(mpfr_flavor<T>::representation const& c)
{
    return inv_rev(c, static_method_entire());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::abs_rev(mpfr_flavor<T>::representation const& c,
                        mpfr_flavor<T>::representation const& x)
{
    if (c.second < 0.0)
        return static_method_empty();

    representation p(std::max(0.0, c.first), c.second);
    representation n = neg(p);

    return hull(intersect(p, x), intersect(n, x));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::abs_rev(mpfr_flavor<T>::representation const& c)
{

    return abs_rev(c, static_method_entire());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::pown_rev(mpfr_flavor<T>::representation const&,
                         mpfr_flavor<T>::representation const&,
                         int)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::pown_rev(mpfr_flavor<T>::representation const& c,
                         int p)
{
    return pown_rev(c, static_method_entire(), p);
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::sin_rev(mpfr_flavor<T>::representation const& c,
                        mpfr_flavor<T>::representation const& x)
{
    representation cc = intersect(c, representation(-1.0, 1.0));

    if (is_empty(cc))
        return cc;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_var cld(cc.first, MPFR_RNDD);
    mpfr_var cuu(cc.second, MPFR_RNDU);

    mpfr_asin(cld(), cld(), MPFR_RNDD);
    mpfr_asin(cuu(), cuu(), MPFR_RNDU);

    mpfr_var pid;
    mpfr_var piu;
    mpfr_const_pi(pid(), MPFR_RNDD);
    mpfr_const_pi(piu(), MPFR_RNDU);

    mpfr_var rl;
    mpfr_var ru;

    mpfr_var tmp;
    long nu;

    // left bound of x
    mpfr_remquo(tmp(), &nu, xl(), pid(), MPFR_RNDD);

    // normalize
    if (tmp.get(MPFR_RNDA) < 0.0)
        --nu;

    tmp.set(nu, MPFR_RNDN);

    if (nu % 2 == 0)
        mpfr_fma(rl(), tmp(), piu(), cuu(), MPFR_RNDU);
    else
        mpfr_fms(rl(), tmp(), piu(), cld(), MPFR_RNDU);

    if (rl.get(MPFR_RNDU) >= x.first) {
        if (nu % 2 == 0)
            mpfr_fma(rl(), tmp(), pid(), cld(), MPFR_RNDD);
        else
            mpfr_fms(rl(), tmp(), pid(), cuu(), MPFR_RNDD);

        if (rl.get(MPFR_RNDD) > x.second)
            return static_method_empty();

        mpfr_max(rl(), rl(), xl(), MPFR_RNDD);
    } else {
        tmp.set(++nu, MPFR_RNDN);

        if (nu % 2 == 0)
            mpfr_fma(rl(), tmp(), piu(), cuu(), MPFR_RNDU);
        else
            mpfr_fms(rl(), tmp(), piu(), cld(), MPFR_RNDU);

        if (rl.get(MPFR_RNDU) < x.first)
            return static_method_empty();

        if (nu % 2 == 0)
            mpfr_fma(rl(), tmp(), pid(), cld(), MPFR_RNDD);
        else
            mpfr_fms(rl(), tmp(), pid(), cuu(), MPFR_RNDD);

        mpfr_max(rl(), rl(), xl(), MPFR_RNDD);
    }


    // right bound of x
    mpfr_remquo(tmp(), &nu, xu(), piu(), MPFR_RNDU);

    // normalize
    if (tmp.get(MPFR_RNDA) > 0.0)
        ++nu;

    tmp.set(nu, MPFR_RNDN);

    if (nu % 2 == 0)
        mpfr_fma(ru(), tmp(), pid(), cld(), MPFR_RNDD);
    else
        mpfr_fms(ru(), tmp(), pid(), cuu(), MPFR_RNDD);

    if (ru.get(MPFR_RNDD) <= x.second) {
        if (nu % 2 == 0)
            mpfr_fma(ru(), tmp(), piu(), cuu(), MPFR_RNDU);
        else
            mpfr_fms(ru(), tmp(), piu(), cld(), MPFR_RNDU);

        mpfr_min(ru(), ru(), xu(), MPFR_RNDU);
    } else {
        tmp.set(--nu, MPFR_RNDN);

        if (nu % 2 == 0)
            mpfr_fma(ru(), tmp(), piu(), cuu(), MPFR_RNDU);
        else
            mpfr_fms(ru(), tmp(), piu(), cld(), MPFR_RNDU);

        mpfr_min(ru(), ru(), xu(), MPFR_RNDU);
    }

    return representation(rl.get(MPFR_RNDD), ru.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::sin_rev(mpfr_flavor<T>::representation const& c)
{
    return sin_rev(c, static_method_entire());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::cos_rev(mpfr_flavor<T>::representation const& c,
                        mpfr_flavor<T>::representation const& x)
{
   representation cc = intersect(c, representation(-1.0, 1.0));

    if (is_empty(cc))
        return cc;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_var cld(cc.second, MPFR_RNDU);
    mpfr_var cuu(cc.first, MPFR_RNDD);

    mpfr_acos(cld(), cld(), MPFR_RNDD);
    mpfr_acos(cuu(), cuu(), MPFR_RNDU);

    mpfr_var pid;
    mpfr_var piu;
    mpfr_const_pi(pid(), MPFR_RNDD);
    mpfr_const_pi(piu(), MPFR_RNDU);

    mpfr_var rl;
    mpfr_var ru;

    mpfr_var tmp;
    long nu;

    // left bound of x
    mpfr_remquo(tmp(), &nu, xl(), pid(), MPFR_RNDD);

    // normalize
    if (tmp.get(MPFR_RNDA) < 0.0)
        --nu;

    if (nu % 2 == 0) {
        tmp.set(nu, MPFR_RNDN);
        mpfr_fma(rl(), tmp(), piu(), cuu(), MPFR_RNDU);
    } else {
        tmp.set(nu + 1, MPFR_RNDN);
        mpfr_fms(rl(), tmp(), piu(), cld(), MPFR_RNDU);
    }

    if (rl.get(MPFR_RNDU) >= x.first) {
        if (nu % 2 == 0)
            mpfr_fma(rl(), tmp(), pid(), cld(), MPFR_RNDD);
        else
            mpfr_fms(rl(), tmp(), pid(), cuu(), MPFR_RNDD);

        if (rl.get(MPFR_RNDD) > x.second)
            return static_method_empty();

        mpfr_max(rl(), rl(), xl(), MPFR_RNDD);
    } else {
        ++nu;

        if (nu % 2 == 0) {
            tmp.set(nu, MPFR_RNDN);
            mpfr_fma(rl(), tmp(), pid(), cld(), MPFR_RNDD);
        } else {
            tmp.set(nu + 1, MPFR_RNDN);
            mpfr_fms(rl(), tmp(), pid(), cuu(), MPFR_RNDD);
        }

        if (rl.get(MPFR_RNDD) > x.second)
            return static_method_empty();

        mpfr_max(rl(), rl(), xl(), MPFR_RNDD);
    }


    // right bound of x
    mpfr_remquo(tmp(), &nu, xu(), piu(), MPFR_RNDU);

    // normalize
    if (tmp.get(MPFR_RNDA) < 0.0)
        --nu;

    if (nu % 2 == 0) {
        tmp.set(nu, MPFR_RNDN);
        mpfr_fma(ru(), tmp(), pid(), cld(), MPFR_RNDD);
    } else {
        tmp.set(nu + 1, MPFR_RNDN);
        mpfr_fms(ru(), tmp(), pid(), cuu(), MPFR_RNDD);
    }

    if (ru.get(MPFR_RNDD) <= x.second) {
        if (nu % 2 == 0)
            mpfr_fma(ru(), tmp(), piu(), cuu(), MPFR_RNDU);
        else
            mpfr_fms(ru(), tmp(), piu(), cld(), MPFR_RNDU);

        mpfr_min(ru(), ru(), xu(), MPFR_RNDU);
    } else {
        --nu;

        if (nu % 2 == 0) {
            tmp.set(nu, MPFR_RNDN);
            mpfr_fma(ru(), tmp(), piu(), cuu(), MPFR_RNDU);
        } else {
            tmp.set(nu + 1, MPFR_RNDN);
            mpfr_fms(ru(), tmp(), piu(), cld(), MPFR_RNDU);
        }

        mpfr_min(ru(), ru(), xu(), MPFR_RNDU);
    }

    return representation(rl.get(MPFR_RNDD), ru.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::cos_rev(mpfr_flavor<T>::representation const& c)
{
    return cos_rev(c, static_method_entire());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::tan_rev(mpfr_flavor<T>::representation const& c,
                        mpfr_flavor<T>::representation const& x)
{
    if (is_empty(c))
        return c;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_var cld(c.first, MPFR_RNDD);
    mpfr_var cuu(c.second, MPFR_RNDU);

    mpfr_atan(cld(), cld(), MPFR_RNDD);
    mpfr_atan(cuu(), cuu(), MPFR_RNDU);

    mpfr_var pid;
    mpfr_var piu;
    mpfr_const_pi(pid(), MPFR_RNDD);
    mpfr_const_pi(piu(), MPFR_RNDU);

    mpfr_var rl;
    mpfr_var ru;

    mpfr_var tmp;
    long nu;

    // left bound of x
    mpfr_remquo(tmp(), &nu, xl(), pid(), MPFR_RNDD);

    // normalize
    if (tmp.get(MPFR_RNDA) < 0.0)
        --nu;

    tmp.set(nu, MPFR_RNDN);

    mpfr_fma(rl(), tmp(), piu(), cuu(), MPFR_RNDU);

    if (rl.get(MPFR_RNDU) >= x.first) {
        mpfr_fma(rl(), tmp(), pid(), cld(), MPFR_RNDD);

        if (rl.get(MPFR_RNDD) > x.second)
            return static_method_empty();

        mpfr_max(rl(), rl(), xl(), MPFR_RNDD);
    } else {
        tmp.set(++nu, MPFR_RNDN);

        mpfr_fma(rl(), tmp(), piu(), cuu(), MPFR_RNDU);

        if (rl.get(MPFR_RNDU) < x.first)
            return static_method_empty();

        mpfr_fma(rl(), tmp(), pid(), cld(), MPFR_RNDD);

        mpfr_max(rl(), rl(), xl(), MPFR_RNDD);
    }


    // right bound of x
    mpfr_remquo(tmp(), &nu, xu(), piu(), MPFR_RNDU);

    // normalize
    if (tmp.get(MPFR_RNDA) > 0.0)
        ++nu;

    tmp.set(nu, MPFR_RNDN);

    mpfr_fma(ru(), tmp(), pid(), cld(), MPFR_RNDD);

    if (ru.get(MPFR_RNDD) <= x.second) {
        mpfr_fma(ru(), tmp(), piu(), cuu(), MPFR_RNDU);

        mpfr_min(ru(), ru(), xu(), MPFR_RNDU);
    } else {
        tmp.set(--nu, MPFR_RNDN);

        mpfr_fma(ru(), tmp(), piu(), cuu(), MPFR_RNDU);

        mpfr_min(ru(), ru(), xu(), MPFR_RNDU);
    }

    return representation(rl.get(MPFR_RNDD), ru.get(MPFR_RNDU));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::tan_rev(mpfr_flavor<T>::representation const& c)
{
    return tan_rev(c, static_method_entire());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::cosh_rev(mpfr_flavor<T>::representation const& c,
                         mpfr_flavor<T>::representation const& x)
{
    representation p = acosh(c);
    representation n = neg(p);

    return hull(intersect(p, x), intersect(n, x));
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::cosh_rev(mpfr_flavor<T>::representation const& c)
{
    return cosh_rev(c, static_method_entire());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::mul_rev(mpfr_flavor<T>::representation const&,
                        mpfr_flavor<T>::representation const&,
                        mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::mul_rev(mpfr_flavor<T>::representation const& b,
                        mpfr_flavor<T>::representation const& c)
{
    return mul_rev(b, c, static_method_entire());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::div_rev1(mpfr_flavor<T>::representation const&,
                         mpfr_flavor<T>::representation const&,
                         mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::div_rev1(mpfr_flavor<T>::representation const& b,
                         mpfr_flavor<T>::representation const& c)
{
    return div_rev1(b, c, static_method_entire());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::div_rev2(mpfr_flavor<T>::representation const&,
                         mpfr_flavor<T>::representation const&,
                         mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::div_rev2(mpfr_flavor<T>::representation const& a,
                         mpfr_flavor<T>::representation const& c)
{
    return div_rev2(a, c, static_method_entire());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::pow_rev1(mpfr_flavor<T>::representation const&,
                         mpfr_flavor<T>::representation const&,
                         mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::pow_rev1(mpfr_flavor<T>::representation const& b,
                         mpfr_flavor<T>::representation const& c)
{
    return pow_rev1(b, c, static_method_entire());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::pow_rev2(mpfr_flavor<T>::representation const&,
                         mpfr_flavor<T>::representation const&,
                         mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::pow_rev2(mpfr_flavor<T>::representation const& a,
                         mpfr_flavor<T>::representation const& c)
{
    return pow_rev2(a, c, static_method_entire());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::atan2_rev1(mpfr_flavor<T>::representation const&,
                           mpfr_flavor<T>::representation const&,
                           mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::atan2_rev1(mpfr_flavor<T>::representation const& b,
                           mpfr_flavor<T>::representation const& c)
{
    return atan2_rev1(b, c, static_method_entire());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::atan2_rev2(mpfr_flavor<T>::representation const&,
                           mpfr_flavor<T>::representation const&,
                           mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::atan2_rev2(mpfr_flavor<T>::representation const& a,
                           mpfr_flavor<T>::representation const& c)
{
    return atan2_rev2(a, c, static_method_entire());
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REV_ELEM_FUNC_IMPL_HPP
