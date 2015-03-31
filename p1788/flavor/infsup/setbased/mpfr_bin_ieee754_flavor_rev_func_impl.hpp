//
//                              libieeep1788
//
//   An implementation of the preliminary IEEE P1788 standard for
//   interval arithmetic
//
//
//   Copyright 2013 - 2015
//
//   Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
//   Department of Computer Science,
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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_REV_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_REV_ELEM_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{

// sqr_rev

// bare version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sqr_rev(mpfr_bin_ieee754_flavor<T>::representation const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(c) || !is_valid(x) || is_empty(c) || is_empty(x) || c.second < 0.0)
        return empty();


    mpfr_var::setup();

    mpfr_var l;
    mpfr_var u;

    int t_l = 0;
    int t_u = 0;


    if (c.first < 0.0)
    {
        l.set(0.0, MPFR_RNDD);

        u.set(c.second, MPFR_RNDU);
        t_u = u.subnormalize(mpfr_sqrt(u(), u(), MPFR_RNDU), MPFR_RNDU);
    }
    else
    {
        l.set(c.first, MPFR_RNDD);
        u.set(c.second, MPFR_RNDU);

        t_l = l.subnormalize(mpfr_sqrt(l(), l(), MPFR_RNDD), MPFR_RNDD);
        t_u = u.subnormalize(mpfr_sqrt(u(), u(), MPFR_RNDU), MPFR_RNDU);
    }

    representation p = representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
    representation n = neg(p);

    if ((p.second == x.first && t_u != 0)
            || (x.second == p.first && t_l != 0))
        p = empty();


    if ((n.second == x.first && t_l != 0)
            || (x.second == n.first && t_u != 0))
        n = empty();

    return convex_hull(intersection(p, x), intersection(n, x));
}

// bare mixed type version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sqr_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)
            || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_empty(c)
            || mpfr_bin_ieee754_flavor<T2>::is_empty(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sqr_rev(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(c),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}

// decorated version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sqr_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(c) || !is_valid(x) || is_nai(c) || is_nai(x))
        return nai();

    // call bare version and set decoration to trv
    return representation_dec(sqr_rev(c.first, x.first), p1788::decoration::decoration::trv);
}

// decorated mixedtype version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sqr_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_nai(c) || mpfr_bin_ieee754_flavor<T2>::is_nai(x))
        return nai();

    // call bare mixedtype version and set decoration to trv
    return representation_dec(sqr_rev(c.first, x.first), p1788::decoration::decoration::trv);
}


// bare unary version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sqr_rev(mpfr_bin_ieee754_flavor<T>::representation const& c)
{
    // call bare binary version with x = entire
    return sqr_rev(c, entire());
}

// bare unary mixedtype version
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sqr_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& c)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call bare binary version with x = entire
    return sqr_rev(c, entire());
}

template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sqr_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c)
{
    // call decorated binary version with x = entire
    return sqr_rev(c, entire_dec());
}

template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sqr_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& c)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call decorated binary version with x = entire
    return sqr_rev(c, entire_dec());
}



// abs_rev

// bare version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::abs_rev(mpfr_bin_ieee754_flavor<T>::representation const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(c) || !is_valid(x) || is_empty(c) || is_empty(x))
        return empty();

    if (c.second < 0.0)
        return empty();

    representation p(std::max(0.0, c.first), c.second);
    representation n = neg(p);

    return convex_hull(intersection(p, x), intersection(n, x));
}

// bare mixed type version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::abs_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)
            || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_empty(c)
            || mpfr_bin_ieee754_flavor<T2>::is_empty(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::abs_rev(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(c),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}

// decorated version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::abs_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(c) || !is_valid(x) || is_nai(c) || is_nai(x))
        return nai();

    // call bare version and set decoration to trv
    return representation_dec(abs_rev(c.first, x.first), p1788::decoration::decoration::trv);
}

// decorated mixedtype version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::abs_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_nai(c) || mpfr_bin_ieee754_flavor<T2>::is_nai(x))
        return nai();

    // call bare mixedtype version and set decoration to trv
    return representation_dec(abs_rev(c.first, x.first), p1788::decoration::decoration::trv);
}


// bare unary version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::abs_rev(mpfr_bin_ieee754_flavor<T>::representation const& c)
{
    // call bare binary version with x = entire
    return abs_rev(c, entire());
}

// bare unary mixedtype version
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::abs_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& c)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call bare binary version with x = entire
    return abs_rev(c, entire());
}

template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::abs_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c)
{
    // call decorated binary version with x = entire
    return abs_rev(c, entire_dec());
}

template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::abs_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& c)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call decorated binary version with x = entire
    return abs_rev(c, entire_dec());
}



// pown_rev

// bare version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::pown_rev(mpfr_bin_ieee754_flavor<T>::representation const& c,
                                     mpfr_bin_ieee754_flavor<T>::representation const& x,
                                     int p)
{
    if (!is_valid(c) || !is_valid(x) || is_empty(c) || is_empty(x))
        return empty();

    if (p == 0)
    {
        if (is_member(1.0, c))
            return x;
        else
            return empty();
    }

    if (p == 1)
        return intersection(x, c);


    mpfr_var::setup();

    mpfr_var cl(c.first, MPFR_RNDD);
    mpfr_var cu(c.second, MPFR_RNDU);

    mpfr_var xl, xu;
    int t_l = 0;
    int t_u = 0;

    // even
    if (p % 2 == 0)
    {
        if (p < 0)  // negative even
        {
            if (c.second <= 0.0)
                return empty();

            t_l = xl.subnormalize(util::mpfr_root_si(xl(), cu(), p, MPFR_RNDD), MPFR_RNDD);

            if (c.first <= 0)
                mpfr_set_inf(xu(), 1);
            else
                t_u = xu.subnormalize(util::mpfr_root_si(xu(), cl(), p, MPFR_RNDU), MPFR_RNDU);
        }
        else    // positive even
        {
            if (c.second < 0.0)
                return empty();

            if (c.first <= 0.0)
                mpfr_set_zero(xl(), -1);
            else
                t_l = xl.subnormalize(util::mpfr_root_si(xl(), cl(), p, MPFR_RNDD), MPFR_RNDD);

            t_u = xu.subnormalize(util::mpfr_root_si(xu(), cu(), p, MPFR_RNDU), MPFR_RNDU);
        }

        representation rp = representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
        representation rn = neg(rp);

        if ((rp.second == x.first && t_u != 0)
                || (x.second == rp.first && t_l != 0))
            rp = empty();

        if ((rn.second == x.first && t_l != 0)
                || (x.second == rn.first && t_u != 0))
            rn = empty();

        return convex_hull(intersection(rp, x), intersection(rn, x));
    }
    else    // odd
    {
        if (p < 0)  // negative odd
        {
            if (c.first == 0.0 && c.second == 0.0)
            {
                return empty();
            }
            else if (c.first >= 0.0 || c.second <= 0.0)
            {
                if (c.second == 0.0)
                    mpfr_set_inf(xl(), -1);
                else
                    t_l = xl.subnormalize(util::mpfr_root_si(xl(), cu(), p, MPFR_RNDD), MPFR_RNDD);

                if (c.first == 0.0)
                    mpfr_set_inf(xu(), 1);
                else
                    t_u = xu.subnormalize(util::mpfr_root_si(xu(), cl(), p, MPFR_RNDU), MPFR_RNDU);

                representation r = representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));

                if ((r.second == x.first && t_u != 0)
                        || (x.second == r.first && t_l != 0))
                    r = empty();

                return intersection(x, r);
            }
            else
            {
                t_u = xu.subnormalize(util::mpfr_root_si(xu(), cl(), p, MPFR_RNDU), MPFR_RNDU);
                representation rn = representation(-std::numeric_limits<T>::infinity(), xu.template get<T>(MPFR_RNDU));
                if (rn.second == x.first && t_u != 0)
                    rn = empty();

                t_l = xl.subnormalize(util::mpfr_root_si(xl(), cu(), p, MPFR_RNDD), MPFR_RNDD);
                representation rp = representation(xl.template get<T>(MPFR_RNDD), std::numeric_limits<T>::infinity());
                if (x.second == rp.first && t_l != 0)
                    rp = empty();

                return convex_hull(intersection(x, rn), intersection(x, rp));
            }
        }
        else     // positive odd
        {
            t_l = xl.subnormalize(util::mpfr_root_si(xl(), cl(), p, MPFR_RNDD), MPFR_RNDD);
            t_u = xu.subnormalize(util::mpfr_root_si(xu(), cu(), p, MPFR_RNDU), MPFR_RNDU);

            representation r = representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));

            if ((r.second == x.first && t_u != 0)
                    || (x.second == r.first && t_l != 0))
                r = empty();

            return intersection(x, r);
        }
    }
}

// bare mixed type version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::pown_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& c,
                                     mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& x,
                                     int p)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)
            || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_empty(c)
            || mpfr_bin_ieee754_flavor<T2>::is_empty(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::pown_rev(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(c),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   p
               )
           );
}

// decorated version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::pown_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c,
                                     mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                     int p)
{
    if (!is_valid(c) || !is_valid(x) || is_nai(c) || is_nai(x))
        return nai();

    // call bare version and set decoration to trv
    return representation_dec(pown_rev(c.first, x.first, p), p1788::decoration::decoration::trv);
}

// decorated mixedtype version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::pown_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& c,
                                     mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& x,
                                     int p)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_nai(c) || mpfr_bin_ieee754_flavor<T2>::is_nai(x))
        return nai();

    // call bare mixedtype version and set decoration to trv
    return representation_dec(pown_rev(c.first, x.first, p), p1788::decoration::decoration::trv);
}


// bare unary version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::pown_rev(mpfr_bin_ieee754_flavor<T>::representation const& c, int p)
{
    // call bare binary version with x = entire
    return pown_rev(c, entire(), p);
}

// bare unary mixedtype version
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::pown_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& c, int p)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call bare binary version with x = entire
    return pown_rev(c, entire(), p);
}

template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::pown_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c, int p)
{
    // call decorated binary version with x = entire
    return pown_rev(c, entire_dec(), p);
}

template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::pown_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& c, int p)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call decorated binary version with x = entire
    return pown_rev(c, entire_dec(), p);
}




// sin_rev

// bare version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sin_rev(mpfr_bin_ieee754_flavor<T>::representation const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(c) || !is_valid(x) || is_empty(x))
        return empty();

    representation cc = intersection(c, representation(-1.0, 1.0));

    // c is disjoint with [-1,1]
    if (is_empty(cc))
        return cc;

    // c contains the whole range [-1,1]
    if (equal(cc, representation(-1.0, 1.0)))
        return x;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_var cl(cc.first, MPFR_RNDD);
    mpfr_var cu(cc.second, MPFR_RNDU);

    // lower and the upper bound of asin(c), result is contained in [-1/2pi, 1/2pi]
    mpfr_asin(cl(), cl(), MPFR_RNDD);
    mpfr_asin(cu(), cu(), MPFR_RNDU);

    // lower and upper bound of pi
    mpfr_var pid;
    mpfr_var piu;
    mpfr_const_pi(pid(), MPFR_RNDD);
    mpfr_const_pi(piu(), MPFR_RNDU);

    mpfr_var rl;
    mpfr_var ru;
    mpfr_var tmp;
    long n;


    // move result of asin(c) to the left bound of x (pi-stepwise)
    // to compute the left box of the result


    representation lbox = empty();  // left box

    // if left bound of x is -oo then the left box is [-oo,-max]
    if (x.first == -std::numeric_limits<T>::infinity())
    {
        lbox.first = -std::numeric_limits<T>::infinity();
        lbox.second = -std::numeric_limits<T>::max();
    }
    else
    {
        // Compute max integer n with: n * pi <= lower bound of x
        mpfr_remquo(tmp(), &n, xl(), x.first < 0.0 ? pid() : piu(), MPFR_RNDD);
        if (mpfr_cmp_si(tmp(),0) < 0)
            --n;

        for (int i = 0; is_empty(lbox) && i <= 1; i++)
        {
            if ((n + i) % 2 == 0)     // n is even => move asin(c)
            {
                tmp.set(n + i, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.first < 0.0 ? piu() : pid(), cl(), MPFR_RNDD);
                mpfr_fma(ru(), tmp(), x.first < 0.0 ? pid() : piu(), cu(), MPFR_RNDU);

                lbox.first = rl.template get<T>(MPFR_RNDD);
                lbox.second = ru.template get<T>(MPFR_RNDU);
            }
            else    // n is even => move mirrored asin(c)
            {
                tmp.set(-n - i, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.first < 0.0 ? piu() : pid(), cu(), MPFR_RNDU);
                mpfr_fma(ru(), tmp(), x.first < 0.0 ? pid() : piu(), cl(), MPFR_RNDD);

                lbox.first = -rl.template get<T>(MPFR_RNDD);
                lbox.second = -ru.template get<T>(MPFR_RNDU);
            }

            lbox = intersection(lbox, x);
        }
    }



    // move result of asin(c) to the right bound of x (pi-stepwise)
    // to compute the right box of the result


    representation rbox = empty();  // right box

    // if right bound of x is +oo then the right box is [max,+oo]
    if (x.second == std::numeric_limits<T>::infinity())
    {
        rbox.first = std::numeric_limits<T>::max();
        rbox.second = std::numeric_limits<T>::infinity();
    }
    else
    {
        // Compute min integer n with: n * pi >= upper bound of x
        mpfr_remquo(tmp(), &n, xu(), x.second > 0.0 ? pid() : piu(), MPFR_RNDU);
        if (mpfr_cmp_si(tmp(),0) > 0)
            ++n;

        for (int i = 0; is_empty(rbox) && i <= 1; i++)
        {
            if ((n - i) % 2 == 0)     // n is even => move asin(c)
            {
                tmp.set(n - i, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.second > 0.0 ? pid() : piu(), cl(), MPFR_RNDD);
                mpfr_fma(ru(), tmp(), x.second > 0.0 ? piu() : pid(), cu(), MPFR_RNDU);

                rbox.first = rl.template get<T>(MPFR_RNDD);
                rbox.second = ru.template get<T>(MPFR_RNDU);
            }
            else    // n is even => move mirrored asin(c)
            {
                tmp.set(-n + i, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.second > 0.0 ? pid() : piu(), cu(), MPFR_RNDU);
                mpfr_fma(ru(), tmp(), x.second > 0.0 ? piu() : pid(), cl(), MPFR_RNDD);

                rbox.first = -rl.template get<T>(MPFR_RNDD);
                rbox.second = -ru.template get<T>(MPFR_RNDU);
            }

            rbox = intersection(rbox, x);
        }
    }

    return convex_hull(lbox, rbox);
}

// bare mixed type version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sin_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)
            || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_empty(c)
            || mpfr_bin_ieee754_flavor<T2>::is_empty(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sin_rev(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(c),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}

// decorated version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sin_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(c) || !is_valid(x) || is_nai(c) || is_nai(x))
        return nai();

    // call bare version and set decoration to trv
    return representation_dec(sin_rev(c.first, x.first), p1788::decoration::decoration::trv);
}

// decorated mixedtype version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sin_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_nai(c) || mpfr_bin_ieee754_flavor<T2>::is_nai(x))
        return nai();

    // call bare mixedtype version and set decoration to trv
    return representation_dec(sin_rev(c.first, x.first), p1788::decoration::decoration::trv);
}


// bare unary version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sin_rev(mpfr_bin_ieee754_flavor<T>::representation const& c)
{
    // call bare binary version with x = entire
    return sin_rev(c, entire());
}

// bare unary mixedtype version
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sin_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& c)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call bare binary version with x = entire
    return sin_rev(c, entire());
}

template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sin_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c)
{
    // call decorated binary version with x = entire
    return sin_rev(c, entire_dec());
}

template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sin_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& c)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call decorated binary version with x = entire
    return sin_rev(c, entire_dec());
}





// cos_rev

// bare version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cos_rev(mpfr_bin_ieee754_flavor<T>::representation const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(c) || !is_valid(x) || is_empty(x))
        return empty();

    representation cc = intersection(c, representation(-1.0, 1.0));

    // c is disjoint with [-1,1]
    if (is_empty(cc))
        return cc;

    // c contains the whole range [-1,1]
    if (equal(cc, representation(-1.0, 1.0)))
        return x;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_var cl(cc.second, MPFR_RNDU);
    mpfr_var cu(cc.first, MPFR_RNDD);

    // lower and the upper bound of acos(c), result is contained in [0, pi]
    mpfr_acos(cl(), cl(), MPFR_RNDD);
    mpfr_acos(cu(), cu(), MPFR_RNDU);

    // lower and upper bound of pi
    mpfr_var pid;
    mpfr_var piu;
    mpfr_const_pi(pid(), MPFR_RNDD);
    mpfr_const_pi(piu(), MPFR_RNDU);

    mpfr_var rl;
    mpfr_var ru;
    mpfr_var tmp;
    long n;


    // move result of acos(c) to the left bound of x (pi-stepwise)
    // to compute the left box of the result


    representation lbox = empty();  // left box

    // if left bound of x is -oo then the left box is [-oo,-max]
    if (x.first == -std::numeric_limits<T>::infinity())
    {
        lbox.first = -std::numeric_limits<T>::infinity();
        lbox.second = -std::numeric_limits<T>::max();
    }
    else
    {
        // Compute max integer n with: n * pi <= lower bound of x
        mpfr_remquo(tmp(), &n, xl(), x.first < 0.0 ? pid() : piu(), MPFR_RNDD);
        if (mpfr_cmp_si(tmp(),0) < 0)
            --n;

        for (int i = 0; is_empty(lbox) && i <= 1; i++)
        {
            if ((n + i) % 2 == 0)     // n is even => move acos(c)
            {
                tmp.set(n + i, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.first < 0.0 ? piu() : pid(), cl(), MPFR_RNDD);
                mpfr_fma(ru(), tmp(), x.first < 0.0 ? pid() : piu(), cu(), MPFR_RNDU);

                lbox.first = rl.template get<T>(MPFR_RNDD);
                lbox.second = ru.template get<T>(MPFR_RNDU);
            }
            else    // n is even => move mirrored acos(c)
            {
                tmp.set(-n - i - 1, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.first < 0.0 ? piu() : pid(), cu(), MPFR_RNDU);
                mpfr_fma(ru(), tmp(), x.first < 0.0 ? pid() : piu(), cl(), MPFR_RNDD);

                lbox.first = -rl.template get<T>(MPFR_RNDD);
                lbox.second = -ru.template get<T>(MPFR_RNDU);
            }

            lbox = intersection(lbox, x);
        }
    }



    // move result of acos(c) to the right bound of x (pi-stepwise)
    // to compute the right box of the result


    representation rbox = empty();  // right box

    // if right bound of x is +oo then the right box is [max,+oo]
    if (x.second == std::numeric_limits<T>::infinity())
    {
        rbox.first = std::numeric_limits<T>::max();
        rbox.second = std::numeric_limits<T>::infinity();
    }
    else
    {
        // Compute max integer n with: n * pi <= upper bound of x
        mpfr_remquo(tmp(), &n, xu(), x.second > 0.0 ? pid() : piu(), MPFR_RNDU);
        if (mpfr_cmp_si(tmp(),0) < 0)
            --n;

        for (int i = 0; is_empty(rbox) && i <= 1; i++)
        {
            if ((n - i) % 2 == 0)     // n is even => move acos(c)
            {
                tmp.set(n - i, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.second > 0.0 ? pid() : piu(), cl(), MPFR_RNDD);
                mpfr_fma(ru(), tmp(), x.second > 0.0 ? piu() : pid(), cu(), MPFR_RNDU);

                rbox.first = rl.template get<T>(MPFR_RNDD);
                rbox.second = ru.template get<T>(MPFR_RNDU);
            }
            else    // n is even => move mirrored acos(c)
            {
                tmp.set(-n + i - 1, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.second > 0.0 ? pid() : piu(), cu(), MPFR_RNDU);
                mpfr_fma(ru(), tmp(), x.second > 0.0 ? piu() : pid(), cl(), MPFR_RNDD);

                rbox.first = -rl.template get<T>(MPFR_RNDD);
                rbox.second = -ru.template get<T>(MPFR_RNDU);
            }

            rbox = intersection(rbox, x);
        }
    }

    return convex_hull(lbox, rbox);
}

// bare mixed type version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cos_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)
            || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_empty(c)
            || mpfr_bin_ieee754_flavor<T2>::is_empty(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::cos_rev(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(c),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}

// decorated version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cos_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(c) || !is_valid(x) || is_nai(c) || is_nai(x))
        return nai();

    // call bare version and set decoration to trv
    return representation_dec(cos_rev(c.first, x.first), p1788::decoration::decoration::trv);
}

// decorated mixedtype version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cos_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_nai(c) || mpfr_bin_ieee754_flavor<T2>::is_nai(x))
        return nai();

    // call bare mixedtype version and set decoration to trv
    return representation_dec(cos_rev(c.first, x.first), p1788::decoration::decoration::trv);
}


// bare unary version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cos_rev(mpfr_bin_ieee754_flavor<T>::representation const& c)
{
    // call bare binary version with x = entire
    return cos_rev(c, entire());
}

// bare unary mixedtype version
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cos_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& c)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call bare binary version with x = entire
    return cos_rev(c, entire());
}

template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cos_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c)
{
    // call decorated binary version with x = entire
    return cos_rev(c, entire_dec());
}

template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cos_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& c)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call decorated binary version with x = entire
    return cos_rev(c, entire_dec());
}


// tan_rev

// bare version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::tan_rev(mpfr_bin_ieee754_flavor<T>::representation const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(c) || !is_valid(x) || is_empty(c) || is_empty(x))
        return empty();


    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_var cl(c.first, MPFR_RNDD);
    mpfr_var cu(c.second, MPFR_RNDU);

    // lower and the upper bound of atan(c), result is contained in [-1/2pi, 1/2pi]
    mpfr_atan(cl(), cl(), MPFR_RNDD);
    mpfr_atan(cu(), cu(), MPFR_RNDU);

    // lower and upper bound of pi
    mpfr_var pid;
    mpfr_var piu;
    mpfr_const_pi(pid(), MPFR_RNDD);
    mpfr_const_pi(piu(), MPFR_RNDU);

    mpfr_var rl;
    mpfr_var ru;
    mpfr_var tmp;
    long n;


    // move result of atan(c) to the left bound of x (pi-stepwise)
    // to compute the left box of the result


    representation lbox = empty();  // left box

    // if left bound of x is -oo then the left box is [-oo,-max]
    if (x.first == -std::numeric_limits<T>::infinity())
    {
        lbox.first = -std::numeric_limits<T>::infinity();
        lbox.second = -std::numeric_limits<T>::max();
    }
    else
    {
        // Compute max integer n with: n * pi <= lower bound of x
        mpfr_remquo(tmp(), &n, xl(), x.first < 0.0 ? pid() : piu(), MPFR_RNDD);
        if (mpfr_cmp_si(tmp(),0) < 0)
            --n;

        // move atan(c)
        for (int i = 0; is_empty(lbox) && i <= 1; i++)
        {
            tmp.set(n + i, MPFR_RNDN);

            mpfr_fma(rl(), tmp(), x.first < 0.0 ? piu() : pid(), cl(), MPFR_RNDD);
            mpfr_fma(ru(), tmp(), x.first < 0.0 ? pid() : piu(), cu(), MPFR_RNDU);

            lbox.first = rl.template get<T>(MPFR_RNDD);
            lbox.second = ru.template get<T>(MPFR_RNDU);

            lbox = intersection(lbox, x);
        }
    }



    // move result of atan(c) to the right bound of x (pi-stepwise)
    // to compute the right box of the result


    representation rbox = empty();  // right box

    // if right bound of x is +oo then the right box is [max,+oo]
    if (x.second == std::numeric_limits<T>::infinity())
    {
        rbox.first = std::numeric_limits<T>::max();
        rbox.second = std::numeric_limits<T>::infinity();
    }
    else
    {
        // Compute min integer n with: n * pi >= upper bound of x
        mpfr_remquo(tmp(), &n, xu(), x.second > 0.0 ? pid() : piu(), MPFR_RNDU);
        if (mpfr_cmp_si(tmp(),0) > 0)
            ++n;

        // move atan(c)
        for (int i = 0; is_empty(rbox) && i <= 1; i++)
        {
            tmp.set(n - i, MPFR_RNDN);

            mpfr_fma(rl(), tmp(), x.second > 0.0 ? pid() : piu(), cl(), MPFR_RNDD);
            mpfr_fma(ru(), tmp(), x.second > 0.0 ? piu() : pid(), cu(), MPFR_RNDU);

            rbox.first = rl.template get<T>(MPFR_RNDD);
            rbox.second = ru.template get<T>(MPFR_RNDU);

            rbox = intersection(rbox, x);
        }
    }

    return convex_hull(lbox, rbox);
}

// bare mixed type version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::tan_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)
            || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_empty(c)
            || mpfr_bin_ieee754_flavor<T2>::is_empty(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::tan_rev(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(c),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}

// decorated version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::tan_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(c) || !is_valid(x) || is_nai(c) || is_nai(x))
        return nai();

    // call bare version and set decoration to trv
    return representation_dec(tan_rev(c.first, x.first), p1788::decoration::decoration::trv);
}

// decorated mixedtype version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::tan_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_nai(c) || mpfr_bin_ieee754_flavor<T2>::is_nai(x))
        return nai();

    // call bare mixedtype version and set decoration to trv
    return representation_dec(tan_rev(c.first, x.first), p1788::decoration::decoration::trv);
}


// bare unary version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::tan_rev(mpfr_bin_ieee754_flavor<T>::representation const& c)
{
    // call bare binary version with x = entire
    return tan_rev(c, entire());
}

// bare unary mixedtype version
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::tan_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& c)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call bare binary version with x = entire
    return tan_rev(c, entire());
}

template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::tan_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c)
{
    // call decorated binary version with x = entire
    return tan_rev(c, entire_dec());
}

template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::tan_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& c)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call decorated binary version with x = entire
    return tan_rev(c, entire_dec());
}


// cosh_rev

// bare version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cosh_rev(mpfr_bin_ieee754_flavor<T>::representation const& c,
                                     mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(c) || !is_valid(x) || is_empty(c) || is_empty(x) || c.second < 1.0)
        return empty();


    mpfr_var::setup();

    mpfr_var l;
    mpfr_var u;

    int t_l = 0;
    int t_u = 0;


    if (c.first < 1.0)
    {
        l.set(0.0, MPFR_RNDD);

        u.set(c.second, MPFR_RNDU);
        t_u = u.subnormalize(mpfr_acosh(u(), u(), MPFR_RNDU), MPFR_RNDU);
    }
    else
    {
        l.set(c.first, MPFR_RNDD);
        u.set(c.second, MPFR_RNDU);

        t_l = l.subnormalize(mpfr_acosh(l(), l(), MPFR_RNDD), MPFR_RNDD);
        t_u = u.subnormalize(mpfr_acosh(u(), u(), MPFR_RNDU), MPFR_RNDU);
    }

    representation p = representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
    representation n = neg(p);

    if ((p.second == x.first && t_u != 0)
            || (x.second == p.first && t_l != 0))
        p = empty();


    if ((n.second == x.first && t_l != 0)
            || (x.second == n.first && t_u != 0))
        n = empty();

    return convex_hull(intersection(p, x), intersection(n, x));
}

// bare mixed type version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cosh_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& c,
                                     mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c)
            || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_empty(c)
            || mpfr_bin_ieee754_flavor<T2>::is_empty(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::cosh_rev(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(c),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}

// decorated version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cosh_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c,
                                     mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(c) || !is_valid(x) || is_nai(c) || is_nai(x))
        return nai();

    // call bare version and set decoration to trv
    return representation_dec(cosh_rev(c.first, x.first), p1788::decoration::decoration::trv);
}

// decorated mixedtype version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cosh_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& c,
                                     mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_nai(c) || mpfr_bin_ieee754_flavor<T2>::is_nai(x))
        return nai();

    // call bare mixedtype version and set decoration to trv
    return representation_dec(cosh_rev(c.first, x.first), p1788::decoration::decoration::trv);
}


// bare unary version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cosh_rev(mpfr_bin_ieee754_flavor<T>::representation const& c)
{
    // call bare binary version with x = entire
    return cosh_rev(c, entire());
}

// bare unary mixedtype version
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cosh_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& c)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call bare binary version with x = entire
    return cosh_rev(c, entire());
}

template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cosh_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c)
{
    // call decorated binary version with x = entire
    return cosh_rev(c, entire_dec());
}

template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cosh_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& c)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call decorated binary version with x = entire
    return cosh_rev(c, entire_dec());
}




// mul_rev

// bare version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation const& b,
                                    mpfr_bin_ieee754_flavor<T>::representation const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(b) || !is_valid(c) || !is_valid(x))
        return empty();

    int t_fl, t_fu, t_sl, t_su;
    auto tmp = mul_rev_to_pair(t_fl, t_fu, t_sl, t_su, b, c);

    if ((tmp.first.second == x.first && t_fu != 0)
            || (x.second == tmp.first.first && t_fl != 0))
        tmp.first = empty();

    if ((tmp.second.second == x.first && t_su != 0)
            || (x.second == tmp.second.first && t_sl != 0))
        tmp.second = empty();


    return convex_hull(intersection(tmp.first, x), intersection(tmp.second, x));
}

// bare mixed type version
template<typename T>
template<typename T1, typename T2, typename T3>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& b,
                                    mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_type<T3> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T3>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b)
            || !mpfr_bin_ieee754_flavor<T2>::is_valid(c)
            || !mpfr_bin_ieee754_flavor<T3>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2,T3>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::mul_rev(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(b),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(c),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}

// decorated version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& b,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(b) || !is_valid(c) || !is_valid(x) || is_nai(b) || is_nai(c) || is_nai(x))
        return nai();

    // call bare version and set decoration to trv
    return representation_dec(mul_rev(b.first, c.first, x.first), p1788::decoration::decoration::trv);
}

// decorated mixedtype version
template<typename T>
template<typename T1, typename T2, typename T3>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& b,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& c,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec_type<T3> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T3>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || !mpfr_bin_ieee754_flavor<T3>::is_valid(x)
            || mpfr_bin_ieee754_flavor<T1>::is_nai(b) || mpfr_bin_ieee754_flavor<T2>::is_nai(c) || mpfr_bin_ieee754_flavor<T3>::is_nai(x))
        return nai();

    // call bare mixedtype version and set decoration to trv
    return representation_dec(mul_rev(b.first, c.first, x.first), p1788::decoration::decoration::trv);
}


// bare unary version
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation const& b,
                                    mpfr_bin_ieee754_flavor<T>::representation const& c)
{
    // call bare ternary version with x = entire
    return mul_rev(b, c, entire());
}

// bare unary mixedtype version
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& b,
                                    mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& c)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call bare ternary version with x = entire
    return mul_rev(b, c, entire());
}

template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& b,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec const& c)
{
    // call decorated ternary version with x = entire
    return mul_rev(b, c, entire_dec());
}

template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& b,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& c)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call decorated ternary version with x = entire
    return mul_rev(b, c, entire_dec());
}




} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_REV_ELEM_FUNC_IMPL_HPP
