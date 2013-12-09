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

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::sqr_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c,
                        mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return x;

    representation p = sqrt(c);
    representation n = neg(p);

    return hull(intersect(p, x), intersect(n, x));
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::sqr_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                        mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::sqr_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c)
{
    return sqr_rev(c, static_method_entire());
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::sqr_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::recip_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c,
                        mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return x;

    return intersect(recip(c), x);
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::recip_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                        mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::recip_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c)
{
    return inv_rev(c, static_method_entire());
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::recip_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::abs_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c,
                        mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return x;

    if (c.second < 0.0)
        return static_method_empty();

    representation p(std::max(0.0, c.first), c.second);
    representation n = neg(p);

    return hull(intersect(p, x), intersect(n, x));
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::abs_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                        mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::abs_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c)
{
    return abs_rev(c, static_method_entire());
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::abs_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::pown_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                         int)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::pown_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         int)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::pown_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c,
                         int p)
{
    return pown_rev(c, static_method_entire(), p);
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::pown_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         int)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::sin_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c,
                        mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return x;

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

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::sin_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                        mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::sin_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c)
{
    return sin_rev(c, static_method_entire());
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::sin_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::cos_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c,
                        mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return x;

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

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::cos_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                        mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::cos_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c)
{
    return cos_rev(c, static_method_entire());
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::cos_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::tan_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c,
                        mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return x;

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

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::tan_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                        mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::tan_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c)
{
    return tan_rev(c, static_method_entire());
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::tan_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::cosh_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return x;

    representation p = acosh(c);
    representation n = neg(p);

    return hull(intersect(p, x), intersect(n, x));
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::cosh_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::cosh_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& c)
{
    return cosh_rev(c, static_method_entire());
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::cosh_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::mul_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& b,
                        mpfr_flavor<T, SUBNORMALIZE>::representation const& c,
                        mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return x;

    if (is_empty(b))
        return b;

    if (is_empty(c))
        return c;

    // b == entire  or  c == entire
    if (is_entire(b) || is_entire(c))
        return x;                               // intersect(entire, x)

    // c contains 0.0
    if (c.first <= 0.0 && c.second >= 0.0) {
        // and b contains 0.0
        if (b.first <= 0.0 && b.second >= 0.0)
            return x;                           // intersect(entire, x)


        mpfr_var::setup();

        mpfr_var bl(b.first == 0.0 ? +0.0 : b.first , MPFR_RNDD);
        mpfr_var bu(b.second == 0.0 ? -0.0 : b.second, MPFR_RNDU);

        mpfr_var cl(c.first == 0.0 ? +0.0 : c.first , MPFR_RNDD);
        mpfr_var cu(c.second == 0.0 ? -0.0 : c.second, MPFR_RNDU);

        if (b.second < 0.0) {
            mpfr_div(cu(), cu(), bu(), MPFR_RNDD);
            mpfr_div(cl(), cl(), bu(), MPFR_RNDU);

            return intersect(representation(cu.get(MPFR_RNDD), cl.get(MPFR_RNDU)), x);
        }

        // b.first > 0.0
        mpfr_div(cl(), cl(), bl(), MPFR_RNDD);
        mpfr_div(cu(), cu(), bl(), MPFR_RNDU);

        return intersect(representation(cl.get(MPFR_RNDD), cu.get(MPFR_RNDU)), x);
    }


    if (c.second < 0.0) {
        if (b.first == 0.0 && b.second == 0.0)
            return static_method_empty();

        mpfr_var::setup();

        mpfr_var bl(b.first == 0.0 ? +0.0 : b.first , MPFR_RNDD);
        mpfr_var bu(b.second == 0.0 ? -0.0 : b.second, MPFR_RNDU);

        mpfr_var cl(c.first == 0.0 ? +0.0 : c.first , MPFR_RNDD);
        mpfr_var cu(c.second == 0.0 ? -0.0 : c.second, MPFR_RNDU);

        if (b.second <= 0.0) {
            mpfr_div(cu(), cu(), bl(), MPFR_RNDD);
            mpfr_div(cl(), cl(), bu(), MPFR_RNDU);

            return intersect(representation(cu.get(MPFR_RNDD), cl.get(MPFR_RNDU)), x);
        }

        if (b.first >= 0.0) {
            mpfr_div(cl(), cl(), bl(), MPFR_RNDD);
            mpfr_div(cu(), cu(), bu(), MPFR_RNDU);

            return intersect(representation(cl.get(MPFR_RNDD), cu.get(MPFR_RNDU)), x);
        }

        return x;                           // intersect(entire, x)
    }

    // c.first > 0.0
    if (b.first == 0.0 && b.second == 0.0)
        return static_method_empty();

    mpfr_var::setup();

    mpfr_var bl(b.first == 0.0 ? +0.0 : b.first , MPFR_RNDD);
    mpfr_var bu(b.second == 0.0 ? -0.0 : b.second, MPFR_RNDU);

    mpfr_var cl(c.first == 0.0 ? +0.0 : c.first , MPFR_RNDD);
    mpfr_var cu(c.second == 0.0 ? -0.0 : c.second, MPFR_RNDU);

    if (b.second <= 0.0) {
        mpfr_div(cu(), cu(), bu(), MPFR_RNDD);
        mpfr_div(cl(), cl(), bl(), MPFR_RNDU);

        return intersect(representation(cu.get(MPFR_RNDD), cl.get(MPFR_RNDU)), x);
    }

    if (b.first >= 0.0) {
        mpfr_div(cl(), cl(), bu(), MPFR_RNDD);
        mpfr_div(cu(), cu(), bl(), MPFR_RNDU);

        return intersect(representation(cl.get(MPFR_RNDD), cu.get(MPFR_RNDU)), x);
    }

    return x;                           // intersect(entire, x)
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::mul_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                        mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                        mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::mul_rev(mpfr_flavor<T, SUBNORMALIZE>::representation const& b,
                        mpfr_flavor<T, SUBNORMALIZE>::representation const& c)
{
    return mul_rev(b, c, static_method_entire());
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::mul_rev(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                        mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::div_rev1(mpfr_flavor<T, SUBNORMALIZE>::representation const& b,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const& c,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    // same as b * c, except b == 0.0 or c == 0.0 !!!!

    if (is_empty(x))
        return x;

    if (is_empty(b))
        return b;

    if (is_empty(c))
        return c;

    if (b.first == 0.0 && b.second == 0.0)
        return static_method_empty();

    if (c.first == 0.0 && c.second == 0.0)
        return intersect(c, x);

    // a == entire  or  c == entire
    if (is_entire(b) || is_entire(c))
        return x;                               // intersect(entire, x)


    mpfr_var::setup();
    mpfr_var l;
    mpfr_var u;

    if (c.second <= 0.0) {
        if (b.second <= 0.0) {
            mpfr_var bl(b.first, MPFR_RNDD);
            mpfr_var bu(b.second, MPFR_RNDU);

            mpfr_var cl(c.first, MPFR_RNDD);
            mpfr_var cu(c.second, MPFR_RNDU);

            mpfr_mul(l(), bu(), cu(), MPFR_RNDD);
            mpfr_mul(u(), bl(), cl(), MPFR_RNDU);
        } else if (b.first >= 0.0) {
            mpfr_var bl(b.first, MPFR_RNDD);
            mpfr_var bu(b.second, MPFR_RNDU);

            mpfr_var cl(c.first, MPFR_RNDD);
            mpfr_var cu(c.second, MPFR_RNDU);

            mpfr_mul(l(), bu(), cl(), MPFR_RNDD);
            mpfr_mul(u(), bl(), cu(), MPFR_RNDU);
        } else {
            mpfr_var bl(b.first, MPFR_RNDD);
            mpfr_var bu(b.second, MPFR_RNDU);

            mpfr_var cl(c.first, MPFR_RNDD);

            mpfr_mul(l(), bu(), cl(), MPFR_RNDD);
            mpfr_mul(u(), bl(), cl(), MPFR_RNDU);
        }
    } else if (c.first >= 0.0) {
        if (b.second <= 0.0) {
            mpfr_var bl(b.first, MPFR_RNDD);
            mpfr_var bu(b.second, MPFR_RNDU);

            mpfr_var cl(c.first, MPFR_RNDD);
            mpfr_var cu(c.second, MPFR_RNDU);

            mpfr_mul(l(), bl(), cu(), MPFR_RNDD);
            mpfr_mul(u(), bu(), cl(), MPFR_RNDU);
        } else if (b.first >= 0.0) {
            mpfr_var bl(b.first, MPFR_RNDD);
            mpfr_var bu(b.second, MPFR_RNDU);

            mpfr_var cl(c.first, MPFR_RNDD);
            mpfr_var cu(c.second, MPFR_RNDU);

            mpfr_mul(l(), bl(), cl(), MPFR_RNDD);
            mpfr_mul(u(), bu(), cu(), MPFR_RNDU);
        } else {
            mpfr_var bl(b.first, MPFR_RNDD);
            mpfr_var bu(b.second, MPFR_RNDU);

            mpfr_var cu(c.second, MPFR_RNDU);

            mpfr_mul(l(), bl(), cu(), MPFR_RNDD);
            mpfr_mul(u(), bu(), cu(), MPFR_RNDU);
        }
    } else {
        if (b.second <= 0.0) {
            mpfr_var bl(b.first, MPFR_RNDD);

            mpfr_var cl(c.first, MPFR_RNDD);
            mpfr_var cu(c.second, MPFR_RNDU);

            mpfr_mul(l(), bl(), cu(), MPFR_RNDD);
            mpfr_mul(u(), bl(), cl(), MPFR_RNDU);
        } else if (b.first >= 0.0) {
            mpfr_var bu(b.second, MPFR_RNDU);

            mpfr_var cl(c.first, MPFR_RNDD);
            mpfr_var cu(c.second, MPFR_RNDU);

            mpfr_mul(l(), bu(), cl(), MPFR_RNDD);
            mpfr_mul(u(), bu(), cu(), MPFR_RNDU);
        } else {
            mpfr_var bl(b.first, MPFR_RNDD);
            mpfr_var bu(b.second, MPFR_RNDU);

            mpfr_var cl(c.first, MPFR_RNDD);
            mpfr_var cu(c.second, MPFR_RNDU);

            mpfr_var tmp;

            mpfr_mul(l(), bl(), cu(), MPFR_RNDD);
            mpfr_mul(tmp(), bu(), cl(), MPFR_RNDD);
            mpfr_min(l(), l(), tmp(), MPFR_RNDD);

            mpfr_mul(u(), bl(), cl(), MPFR_RNDU);
            mpfr_mul(tmp(), bu(), cu(), MPFR_RNDU);
            mpfr_max(u(), u(), tmp(), MPFR_RNDU);
        }
    }

    return intersect(representation(l.get(MPFR_RNDD), u.get(MPFR_RNDU)), x);
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::div_rev1(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::div_rev1(mpfr_flavor<T, SUBNORMALIZE>::representation const& b,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const& c)
{
    return div_rev1(b, c, static_method_entire());
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::div_rev1(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::div_rev2(mpfr_flavor<T, SUBNORMALIZE>::representation const& a,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const& c,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    // TODO same as a/c ?????

    if (is_empty(x))
        return x;

    if (is_empty(a))
        return a;

    if (is_empty(c))
        return c;

    // a == entire  or  c == entire
    if (is_entire(a) || is_entire(c))
        return x;                               // intersect(entire, x)

    // c contains 0.0
    if (c.first <= 0.0 && c.second >= 0.0) {
        // and a contains 0.0
        if (a.first <= 0.0 && a.second >= 0.0)
            return x;                           // intersect(entire, x)

        // c == 0.0 and a !contains 0.0
        if (c.first == 0.0 && c.second == 0.0)
            return static_method_empty();


        if (a.second < 0.0 && c.second == 0.0) {
            mpfr_var::setup();

            mpfr_var au(a.second == 0.0 ? -0.0 : a.second, MPFR_RNDU);
            mpfr_var cl(c.first == 0.0 ? +0.0 : c.first, MPFR_RNDD);

            mpfr_div(au(), au(), cl(), MPFR_RNDD);

            return intersect(representation(au.get(MPFR_RNDD), std::numeric_limits<T>::infinity()), x);
        }

        if (a.second < 0.0 && c.first == 0.0) {
            mpfr_var::setup();

            mpfr_var au(a.second == 0.0 ? -0.0 : a.second, MPFR_RNDU);
            mpfr_var cu(c.second == 0.0 ? -0.0 : c.second, MPFR_RNDU);

            mpfr_div(au(), au(), cu(), MPFR_RNDU);

            return intersect(representation(-std::numeric_limits<T>::infinity(), au.get(MPFR_RNDU)), x);
        }

        if (a.first > 0.0 && c.second == 0.0) {
            mpfr_var::setup();

            mpfr_var al(a.first == 0.0 ? +0.0 : a.first, MPFR_RNDD);
            mpfr_var cl(c.first == 0.0 ? +0.0 : c.first, MPFR_RNDD);

            mpfr_div(al(), al(), cl(), MPFR_RNDU);

            return intersect(representation(-std::numeric_limits<T>::infinity(), al.get(MPFR_RNDU)), x);
        }

        if (a.first > 0.0 && c.first == 0.0) {
            mpfr_var::setup();

            mpfr_var al(a.first == 0.0 ? +0.0 : a.first, MPFR_RNDD);
            mpfr_var cu(c.second == 0.0 ? -0.0 : c.second, MPFR_RNDU);

            mpfr_div(al(), al(), cu(), MPFR_RNDD);

            return intersect(representation(al.get(MPFR_RNDD), std::numeric_limits<T>::infinity()), x);
        }

        return x;                               // intersect(entire, x)
    }


    if (c.second < 0.0) {
        if (a.first == 0.0 && a.second == 0.0)
            return static_method_empty();

        mpfr_var::setup();

        mpfr_var al(a.first == 0.0 ? +0.0 : a.first , MPFR_RNDD);
        mpfr_var au(a.second == 0.0 ? -0.0 : a.second, MPFR_RNDU);

        mpfr_var cl(c.first == 0.0 ? +0.0 : c.first , MPFR_RNDD);
        mpfr_var cu(c.second == 0.0 ? -0.0 : c.second, MPFR_RNDU);

        if (a.second <= 0.0) {
            mpfr_div(au(), au(), cl(), MPFR_RNDD);
            mpfr_div(al(), al(), cu(), MPFR_RNDU);

            return intersect(representation(au.get(MPFR_RNDD), al.get(MPFR_RNDU)), x);
        }

        if (a.first >= 0.0) {
            mpfr_div(au(), au(), cu(), MPFR_RNDD);
            mpfr_div(al(), al(), cl(), MPFR_RNDU);

            return intersect(representation(au.get(MPFR_RNDD), al.get(MPFR_RNDU)), x);
        }

        mpfr_div(au(), au(), cu(), MPFR_RNDD);
        mpfr_div(al(), al(), cu(), MPFR_RNDU);

        return intersect(representation(au.get(MPFR_RNDD), al.get(MPFR_RNDU)), x);
    }

    // c.first > 0.0
    if (a.first == 0.0 && a.second == 0.0)
        return static_method_empty();

    mpfr_var::setup();

    mpfr_var al(a.first == 0.0 ? +0.0 : a.first , MPFR_RNDD);
    mpfr_var au(a.second == 0.0 ? -0.0 : a.second, MPFR_RNDU);

    mpfr_var cl(c.first == 0.0 ? +0.0 : c.first , MPFR_RNDD);
    mpfr_var cu(c.second == 0.0 ? -0.0 : c.second, MPFR_RNDU);

    if (a.second <= 0.0) {
        mpfr_div(al(), al(), cl(), MPFR_RNDD);
        mpfr_div(au(), au(), cu(), MPFR_RNDU);

        return intersect(representation(al.get(MPFR_RNDD), au.get(MPFR_RNDU)), x);
    }

    if (a.first >= 0.0) {
        mpfr_div(al(), al(), cu(), MPFR_RNDD);
        mpfr_div(au(), au(), cl(), MPFR_RNDU);

        return intersect(representation(al.get(MPFR_RNDD), au.get(MPFR_RNDU)), x);
    }

    mpfr_div(al(), al(), cl(), MPFR_RNDD);
    mpfr_div(au(), au(), cl(), MPFR_RNDU);

    return intersect(representation(al.get(MPFR_RNDD), au.get(MPFR_RNDU)), x);
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::div_rev2(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::div_rev2(mpfr_flavor<T, SUBNORMALIZE>::representation const& a,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const& c)
{
    return div_rev2(a, c, static_method_entire());
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::div_rev2(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::pow_rev1(mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::pow_rev1(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::pow_rev1(mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::pow_rev1(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::pow_rev2(mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::pow_rev2(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::pow_rev2(mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::pow_rev2(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                         mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::atan2_rev1(mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                           mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                           mpfr_flavor<T, SUBNORMALIZE>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::atan2_rev1(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                           mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                           mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::atan2_rev1(mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                           mpfr_flavor<T, SUBNORMALIZE>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::atan2_rev1(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                           mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::atan2_rev2(mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                           mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                           mpfr_flavor<T, SUBNORMALIZE>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::atan2_rev2(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                           mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                           mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::atan2_rev2(mpfr_flavor<T, SUBNORMALIZE>::representation const&,
                           mpfr_flavor<T, SUBNORMALIZE>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::atan2_rev2(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&,
                           mpfr_flavor<T, SUBNORMALIZE>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE>::static_method_entire_dec();
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REV_ELEM_FUNC_IMPL_HPP
