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
    if (!is_valid(c) || !is_valid(x) || is_empty(c) || is_empty(x))
        return empty();

    representation p = sqrt(c);
    representation n = neg(p);

    return hull(intersect(p, x), intersect(n, x));
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
    if (!is_valid(c) || !is_valid(x))
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

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x))
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

    return hull(intersect(p, x), intersect(n, x));
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
    if (!is_valid(c) || !is_valid(x))
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

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x))
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
        return intersect(x, c);


    // even
    if (p % 2 == 0)
    {
        if (p < 0)  // negative even
        {
            if (c.second <= 0.0)
                return empty();

            mpfr_var::setup();

            mpfr_var cl(c.first <= 0.0 ? 0.0 : c.first, MPFR_RNDD);
            mpfr_var cu(c.second, MPFR_RNDU);

            cl.subnormalize(mpfr_root(cl(), cl(), -p, MPFR_RNDD), MPFR_RNDD);
            cl.subnormalize(mpfr_si_div(cl(), 1, cl(), MPFR_RNDU), MPFR_RNDU);  // 1 / root(lower, abs(p))

            cu.subnormalize(mpfr_root(cu(), cu(), -p, MPFR_RNDU), MPFR_RNDU);
            cu.subnormalize(mpfr_si_div(cu(), 1, cu(), MPFR_RNDD), MPFR_RNDD);  // 1 / root(upper, abs(p))

            return hull(intersect(x, representation(-cl.template get<T>(MPFR_RNDU), -cu.template get<T>(MPFR_RNDD))),
                        intersect(x, representation(cu.template get<T>(MPFR_RNDD), cl.template get<T>(MPFR_RNDU))));
        }
        else    // positive even
        {
            if (c.second < 0.0)
                return empty();

            mpfr_var::setup();

            if (c.first <= 0.0)
            {
                mpfr_var cu(c.second, MPFR_RNDU);

                cu.subnormalize(mpfr_root(cu(), cu(), p, MPFR_RNDU), MPFR_RNDU);

                return intersect(x, representation(-cu.template get<T>(MPFR_RNDU), cu.template get<T>(MPFR_RNDU)));
            }

            mpfr_var cl(c.first, MPFR_RNDD);
            mpfr_var cu(c.second, MPFR_RNDU);

            cl.subnormalize(mpfr_root(cl(), cl(), p, MPFR_RNDD), MPFR_RNDD);
            cu.subnormalize(mpfr_root(cu(), cu(), p, MPFR_RNDU), MPFR_RNDU);

            return hull(intersect(x, representation(-cu.template get<T>(MPFR_RNDU), -cl.template get<T>(MPFR_RNDD))),
                        intersect(x, representation(cl.template get<T>(MPFR_RNDD), cu.template get<T>(MPFR_RNDU))));
        }
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
                mpfr_var::setup();

                mpfr_var cl(c.first, MPFR_RNDD);
                mpfr_var cu(c.second, MPFR_RNDU);

                if (c.first != 0.0)
                {
                    cl.subnormalize(mpfr_root(cl(), cl(), -p, MPFR_RNDD), MPFR_RNDD);
                    cl.subnormalize(mpfr_si_div(cl(), 1, cl(), MPFR_RNDU), MPFR_RNDU);  // 1 / root(lower, abs(p))
                }

                if (c.second != 0.0)
                {
                    cu.subnormalize(mpfr_root(cu(), cu(), -p, MPFR_RNDU), MPFR_RNDU);
                    cu.subnormalize(mpfr_si_div(cu(), 1, cu(), MPFR_RNDD), MPFR_RNDD);  // 1 / root(upper, abs(p))
                }

                return intersect(x, representation(c.second != 0.0 ? cu.template get<T>(MPFR_RNDD) : -std::numeric_limits<T>::infinity(),
                                                   c.first != 0.0 ? cl.template get<T>(MPFR_RNDU) : std::numeric_limits<T>::infinity()));
            }
            else
            {
                mpfr_var::setup();

                mpfr_var cl(c.first, MPFR_RNDD);
                mpfr_var cu(c.second, MPFR_RNDU);

                cl.subnormalize(mpfr_root(cl(), cl(), -p, MPFR_RNDD), MPFR_RNDD);
                cl.subnormalize(mpfr_si_div(cl(), 1, cl(), MPFR_RNDU), MPFR_RNDU);  // 1 / root(lower, abs(p))

                cu.subnormalize(mpfr_root(cu(), cu(), -p, MPFR_RNDU), MPFR_RNDU);
                cu.subnormalize(mpfr_si_div(cu(), 1, cu(), MPFR_RNDD), MPFR_RNDD);  // 1 / root(upper, abs(p))

                return hull(intersect(x, representation(-std::numeric_limits<T>::infinity(), cl.template get<T>(MPFR_RNDU))),
                            intersect(x, representation(cu.template get<T>(MPFR_RNDD), std::numeric_limits<T>::infinity())));
            }
        }
        else     // positive odd
        {
            mpfr_var::setup();

            mpfr_var cl(c.first, MPFR_RNDD);
            mpfr_var cu(c.second, MPFR_RNDU);

            cl.subnormalize(mpfr_root(cl(), cl(), p, MPFR_RNDD), MPFR_RNDD);
            cu.subnormalize(mpfr_root(cu(), cu(), p, MPFR_RNDU), MPFR_RNDU);

            return intersect(x, representation(cl.template get<T>(MPFR_RNDD), cu.template get<T>(MPFR_RNDU)));
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
    if (!is_valid(c) || !is_valid(x))
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

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x))
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

    representation cc = intersect(c, representation(-1.0, 1.0));

    // c is disjoint with [-1,1]
    if (is_empty(cc))
        return cc;

    // c contains the whole range [-1,1]
    if (is_equal(cc, representation(-1.0, 1.0)))
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
            if ((n + i) % 2 == 0)     // n is even => move asin(x)
            {
                tmp.set(n + i, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.first < 0.0 ? piu() : pid(), cl(), MPFR_RNDD);
                mpfr_fma(ru(), tmp(), x.first < 0.0 ? pid() : piu(), cu(), MPFR_RNDU);

                lbox.first = rl.template get<T>(MPFR_RNDD);
                lbox.second = ru.template get<T>(MPFR_RNDU);
            }
            else    // n is even => move mirrored asin(x)
            {
                tmp.set(-n - i, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.first < 0.0 ? piu() : pid(), cu(), MPFR_RNDU);
                mpfr_fma(ru(), tmp(), x.first < 0.0 ? pid() : piu(), cl(), MPFR_RNDD);

                lbox.first = -rl.template get<T>(MPFR_RNDD);
                lbox.second = -ru.template get<T>(MPFR_RNDU);
            }

            lbox = intersect(lbox, x);
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
            if ((n - i) % 2 == 0)     // n is even => move asin(x)
            {
                tmp.set(n - i, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.second > 0.0 ? pid() : piu(), cl(), MPFR_RNDD);
                mpfr_fma(ru(), tmp(), x.second > 0.0 ? piu() : pid(), cu(), MPFR_RNDU);

                rbox.first = rl.template get<T>(MPFR_RNDD);
                rbox.second = ru.template get<T>(MPFR_RNDU);
            }
            else    // n is even => move mirrored asin(x)
            {
                tmp.set(-n + i, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.second > 0.0 ? pid() : piu(), cu(), MPFR_RNDU);
                mpfr_fma(ru(), tmp(), x.second > 0.0 ? piu() : pid(), cl(), MPFR_RNDD);

                rbox.first = -rl.template get<T>(MPFR_RNDD);
                rbox.second = -ru.template get<T>(MPFR_RNDU);
            }

            rbox = intersect(rbox, x);
        }
    }

    return hull(lbox, rbox);
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
    if (!is_valid(c) || !is_valid(x))
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

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x))
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

    representation cc = intersect(c, representation(-1.0, 1.0));

    // c is disjoint with [-1,1]
    if (is_empty(cc))
        return cc;

    // c contains the whole range [-1,1]
    if (is_equal(cc, representation(-1.0, 1.0)))
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
            if ((n + i) % 2 == 0)     // n is even => move acos(x)
            {
                tmp.set(n + i, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.first < 0.0 ? piu() : pid(), cl(), MPFR_RNDD);
                mpfr_fma(ru(), tmp(), x.first < 0.0 ? pid() : piu(), cu(), MPFR_RNDU);

                lbox.first = rl.template get<T>(MPFR_RNDD);
                lbox.second = ru.template get<T>(MPFR_RNDU);
            }
            else    // n is even => move mirrored acos(x)
            {
                tmp.set(-n - i - 1, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.first < 0.0 ? piu() : pid(), cu(), MPFR_RNDU);
                mpfr_fma(ru(), tmp(), x.first < 0.0 ? pid() : piu(), cl(), MPFR_RNDD);

                lbox.first = -rl.template get<T>(MPFR_RNDD);
                lbox.second = -ru.template get<T>(MPFR_RNDU);
            }

            lbox = intersect(lbox, x);
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
            if ((n - i) % 2 == 0)     // n is even => move acos(x)
            {
                tmp.set(n - i, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.second > 0.0 ? pid() : piu(), cl(), MPFR_RNDD);
                mpfr_fma(ru(), tmp(), x.second > 0.0 ? piu() : pid(), cu(), MPFR_RNDU);

                rbox.first = rl.template get<T>(MPFR_RNDD);
                rbox.second = ru.template get<T>(MPFR_RNDU);
            }
            else    // n is even => move mirrored acos(x)
            {
                tmp.set(-n + i - 1, MPFR_RNDN);

                mpfr_fma(rl(), tmp(), x.second > 0.0 ? pid() : piu(), cu(), MPFR_RNDU);
                mpfr_fma(ru(), tmp(), x.second > 0.0 ? piu() : pid(), cl(), MPFR_RNDD);

                rbox.first = -rl.template get<T>(MPFR_RNDD);
                rbox.second = -ru.template get<T>(MPFR_RNDU);
            }

            rbox = intersect(rbox, x);
        }
    }

    return hull(lbox, rbox);




//    if (is_empty(x))
//        return x;
//
//    representation cc = intersect(c, representation(-1.0, 1.0));
//
//    if (is_empty(cc))
//        return cc;
//
//    mpfr_var::setup();
//
//    mpfr_var xl(x.first, MPFR_RNDD);
//    mpfr_var xu(x.second, MPFR_RNDU);
//
//    mpfr_var cld(cc.second, MPFR_RNDU);
//    mpfr_var cuu(cc.first, MPFR_RNDD);
//
//    mpfr_acos(cld(), cld(), MPFR_RNDD);
//    mpfr_acos(cuu(), cuu(), MPFR_RNDU);
//
//    mpfr_var pid;
//    mpfr_var piu;
//    mpfr_const_pi(pid(), MPFR_RNDD);
//    mpfr_const_pi(piu(), MPFR_RNDU);
//
//    mpfr_var rl;
//    mpfr_var ru;
//
//    mpfr_var tmp;
//    long nu;
//
//    // left bound of x
//    mpfr_remquo(tmp(), &nu, xl(), pid(), MPFR_RNDD);
//
//    // normalize
//    if (tmp.template get<T>(MPFR_RNDA) < 0.0)
//        --nu;
//
//    if (nu % 2 == 0)
//    {
//        tmp.set(nu, MPFR_RNDN);
//        mpfr_fma(rl(), tmp(), piu(), cuu(), MPFR_RNDU);
//    }
//    else
//    {
//        tmp.set(nu + 1, MPFR_RNDN);
//        mpfr_fms(rl(), tmp(), piu(), cld(), MPFR_RNDU);
//    }
//
//    if (rl.template get<T>(MPFR_RNDU) >= x.first)
//    {
//        if (nu % 2 == 0)
//            mpfr_fma(rl(), tmp(), pid(), cld(), MPFR_RNDD);
//        else
//            mpfr_fms(rl(), tmp(), pid(), cuu(), MPFR_RNDD);
//
//        if (rl.template get<T>(MPFR_RNDD) > x.second)
//            return empty();
//
//        mpfr_max(rl(), rl(), xl(), MPFR_RNDD);
//    }
//    else
//    {
//        ++nu;
//
//        if (nu % 2 == 0)
//        {
//            tmp.set(nu, MPFR_RNDN);
//            mpfr_fma(rl(), tmp(), pid(), cld(), MPFR_RNDD);
//        }
//        else
//        {
//            tmp.set(nu + 1, MPFR_RNDN);
//            mpfr_fms(rl(), tmp(), pid(), cuu(), MPFR_RNDD);
//        }
//
//        if (rl.template get<T>(MPFR_RNDD) > x.second)
//            return empty();
//
//        mpfr_max(rl(), rl(), xl(), MPFR_RNDD);
//    }
//
//
//    // right bound of x
//    mpfr_remquo(tmp(), &nu, xu(), piu(), MPFR_RNDU);
//
//    // normalize
//    if (tmp.template get<T>(MPFR_RNDA) < 0.0)
//        --nu;
//
//    if (nu % 2 == 0)
//    {
//        tmp.set(nu, MPFR_RNDN);
//        mpfr_fma(ru(), tmp(), pid(), cld(), MPFR_RNDD);
//    }
//    else
//    {
//        tmp.set(nu + 1, MPFR_RNDN);
//        mpfr_fms(ru(), tmp(), pid(), cuu(), MPFR_RNDD);
//    }
//
//    if (ru.template get<T>(MPFR_RNDD) <= x.second)
//    {
//        if (nu % 2 == 0)
//            mpfr_fma(ru(), tmp(), piu(), cuu(), MPFR_RNDU);
//        else
//            mpfr_fms(ru(), tmp(), piu(), cld(), MPFR_RNDU);
//
//        mpfr_min(ru(), ru(), xu(), MPFR_RNDU);
//    }
//    else
//    {
//        --nu;
//
//        if (nu % 2 == 0)
//        {
//            tmp.set(nu, MPFR_RNDN);
//            mpfr_fma(ru(), tmp(), piu(), cuu(), MPFR_RNDU);
//        }
//        else
//        {
//            tmp.set(nu + 1, MPFR_RNDN);
//            mpfr_fms(ru(), tmp(), piu(), cld(), MPFR_RNDU);
//        }
//
//        mpfr_min(ru(), ru(), xu(), MPFR_RNDU);
//    }
//
//    return representation(rl.template get<T>(MPFR_RNDD), ru.template get<T>(MPFR_RNDU));
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
    if (!is_valid(c) || !is_valid(x))
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

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x))
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
    if (tmp.template get<T>(MPFR_RNDA) < 0.0)
        --nu;

    tmp.set(nu, MPFR_RNDN);

    mpfr_fma(rl(), tmp(), piu(), cuu(), MPFR_RNDU);

    if (rl.template get<T>(MPFR_RNDU) >= x.first)
    {
        mpfr_fma(rl(), tmp(), pid(), cld(), MPFR_RNDD);

        if (rl.template get<T>(MPFR_RNDD) > x.second)
            return empty();

        mpfr_max(rl(), rl(), xl(), MPFR_RNDD);
    }
    else
    {
        tmp.set(++nu, MPFR_RNDN);

        mpfr_fma(rl(), tmp(), piu(), cuu(), MPFR_RNDU);

        if (rl.template get<T>(MPFR_RNDU) < x.first)
            return empty();

        mpfr_fma(rl(), tmp(), pid(), cld(), MPFR_RNDD);

        mpfr_max(rl(), rl(), xl(), MPFR_RNDD);
    }


    // right bound of x
    mpfr_remquo(tmp(), &nu, xu(), piu(), MPFR_RNDU);

    // normalize
    if (tmp.template get<T>(MPFR_RNDA) > 0.0)
        ++nu;

    tmp.set(nu, MPFR_RNDN);

    mpfr_fma(ru(), tmp(), pid(), cld(), MPFR_RNDD);

    if (ru.template get<T>(MPFR_RNDD) <= x.second)
    {
        mpfr_fma(ru(), tmp(), piu(), cuu(), MPFR_RNDU);

        mpfr_min(ru(), ru(), xu(), MPFR_RNDU);
    }
    else
    {
        tmp.set(--nu, MPFR_RNDN);

        mpfr_fma(ru(), tmp(), piu(), cuu(), MPFR_RNDU);

        mpfr_min(ru(), ru(), xu(), MPFR_RNDU);
    }

    return representation(rl.template get<T>(MPFR_RNDD), ru.template get<T>(MPFR_RNDU));
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
    if (!is_valid(c) || !is_valid(x))
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

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x))
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
    if (is_empty(x))
        return x;

    representation p = acosh(c);
    representation n = neg(p);

    return hull(intersect(p, x), intersect(n, x));
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
    if (!is_valid(c) || !is_valid(x))
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

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(c) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x))
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



//
//
//// mul_rev
//
//// bare version
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation const& b,
//                                    mpfr_bin_ieee754_flavor<T>::representation const& c,
//                                    mpfr_bin_ieee754_flavor<T>::representation const& x)
//{
//    if (is_empty(x))
//        return x;
//
//    if (is_empty(b))
//        return b;
//
//    if (is_empty(c))
//        return c;
//
//    // b == entire  or  c == entire
//    if (is_entire(b) || is_entire(c))
//        return x;                               // intersect(entire, x)
//
//    // c contains 0.0
//    if (c.first <= 0.0 && c.second >= 0.0)
//    {
//        // and b contains 0.0
//        if (b.first <= 0.0 && b.second >= 0.0)
//            return x;                           // intersect(entire, x)
//
//
//        mpfr_var::setup();
//
//        mpfr_var bl(b.first == 0.0 ? +0.0 : b.first , MPFR_RNDD);
//        mpfr_var bu(b.second == 0.0 ? -0.0 : b.second, MPFR_RNDU);
//
//        mpfr_var cl(c.first == 0.0 ? +0.0 : c.first , MPFR_RNDD);
//        mpfr_var cu(c.second == 0.0 ? -0.0 : c.second, MPFR_RNDU);
//
//        if (b.second < 0.0)
//        {
//            mpfr_div(cu(), cu(), bu(), MPFR_RNDD);
//            mpfr_div(cl(), cl(), bu(), MPFR_RNDU);
//
//            return intersect(representation(cu.template get<T>(MPFR_RNDD), cl.template get<T>(MPFR_RNDU)), x);
//        }
//
//        // b.first > 0.0
//        mpfr_div(cl(), cl(), bl(), MPFR_RNDD);
//        mpfr_div(cu(), cu(), bl(), MPFR_RNDU);
//
//        return intersect(representation(cl.template get<T>(MPFR_RNDD), cu.template get<T>(MPFR_RNDU)), x);
//    }
//
//
//    if (c.second < 0.0)
//    {
//        if (b.first == 0.0 && b.second == 0.0)
//            return empty();
//
//        mpfr_var::setup();
//
//        mpfr_var bl(b.first == 0.0 ? +0.0 : b.first , MPFR_RNDD);
//        mpfr_var bu(b.second == 0.0 ? -0.0 : b.second, MPFR_RNDU);
//
//        mpfr_var cl(c.first == 0.0 ? +0.0 : c.first , MPFR_RNDD);
//        mpfr_var cu(c.second == 0.0 ? -0.0 : c.second, MPFR_RNDU);
//
//        if (b.second <= 0.0)
//        {
//            mpfr_div(cu(), cu(), bl(), MPFR_RNDD);
//            mpfr_div(cl(), cl(), bu(), MPFR_RNDU);
//
//            return intersect(representation(cu.template get<T>(MPFR_RNDD), cl.template get<T>(MPFR_RNDU)), x);
//        }
//
//        if (b.first >= 0.0)
//        {
//            mpfr_div(cl(), cl(), bl(), MPFR_RNDD);
//            mpfr_div(cu(), cu(), bu(), MPFR_RNDU);
//
//            return intersect(representation(cl.template get<T>(MPFR_RNDD), cu.template get<T>(MPFR_RNDU)), x);
//        }
//
//        return x;                           // intersect(entire, x)
//    }
//
//    // c.first > 0.0
//    if (b.first == 0.0 && b.second == 0.0)
//        return empty();
//
//    mpfr_var::setup();
//
//    mpfr_var bl(b.first == 0.0 ? +0.0 : b.first , MPFR_RNDD);
//    mpfr_var bu(b.second == 0.0 ? -0.0 : b.second, MPFR_RNDU);
//
//    mpfr_var cl(c.first == 0.0 ? +0.0 : c.first , MPFR_RNDD);
//    mpfr_var cu(c.second == 0.0 ? -0.0 : c.second, MPFR_RNDU);
//
//    if (b.second <= 0.0)
//    {
//        mpfr_div(cu(), cu(), bu(), MPFR_RNDD);
//        mpfr_div(cl(), cl(), bl(), MPFR_RNDU);
//
//        return intersect(representation(cu.template get<T>(MPFR_RNDD), cl.template get<T>(MPFR_RNDU)), x);
//    }
//
//    if (b.first >= 0.0)
//    {
//        mpfr_div(cl(), cl(), bu(), MPFR_RNDD);
//        mpfr_div(cu(), cu(), bl(), MPFR_RNDU);
//
//        return intersect(representation(cl.template get<T>(MPFR_RNDD), cu.template get<T>(MPFR_RNDU)), x);
//    }
//
//    return x;                           // intersect(entire, x)
//}
//
//
//// bare mixed type version
//template<typename T>
//template<typename T1, typename T2, typename T3>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& b,
//                                    mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& c,
//                                    mpfr_bin_ieee754_flavor<T>::representation_type<T3> const& x)
//{
//    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
//    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
//    static_assert(std::numeric_limits<T3>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
//
//    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b)
//            ||!mpfr_bin_ieee754_flavor<T1>::is_valid(c)
//            || !mpfr_bin_ieee754_flavor<T2>::is_valid(x)
//            || mpfr_bin_ieee754_flavor<T2>::is_empty(x))
//        return empty();
//
//    // determine max. precision
//    typedef typename p1788::util::max_precision_type<T,T1,T2,T3>::type T_MAX;
//
//    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
//    // Error free for floating point inf-sup intervals due to  outward rounding
//    return convert_hull(
//               mpfr_bin_ieee754_flavor<T_MAX>::mul_rev(
//                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(b),
//                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(c),
//                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
//               )
//           );
//}
//
//
//// decorated version
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& b,
//mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
//{
//    if (!is_valid(b) || !is_valid(c) || !is_valid(x))
//        return nai();
//
//    // call bare version and set decoration to trv
//    return representation_dec(mul_rev(b.first, c.first, x.first), p1788::decoration::decoration::trv);
//}
//
//// decorated mixedtype version
//template<typename T>
//template<typename T1, typename T2, typename T3>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& b,
//mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& c,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec_type<T3> const& x)
//{
//    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
//    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
//    static_assert(std::numeric_limits<T3>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
//
//    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c) || !mpfr_bin_ieee754_flavor<T3>::is_valid(x))
//        return nai();
//
//    // call bare mixedtype version and set decoration to trv
//    return representation_dec(mul_rev(c.first, x.first), p1788::decoration::decoration::trv);
//}
//
//
//// bare unary version
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation const& c)
//{
//    // call bare binary version with x = entire
//    return mul_rev(c, entire());
//}
//
//// bare unary mixedtype version
//template<typename T>
//template<typename T_>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& c)
//{
//    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
//
//    // call bare binary version with x = entire
//    return mul_rev(c, entire());
//}
//
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_dec const& c)
//{
//    // call decorated binary version with x = entire
//    return mul_rev(c, entire_dec());
//}
//
//template<typename T>
//template<typename T_>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::mul_rev(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& c)
//{
//    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
//
//    // call decorated binary version with x = entire
//    return mul_rev(c, entire_dec());
//}
//
//
//// pow_rev1
//
//// bare version
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::pow_rev1(mpfr_bin_ieee754_flavor<T>::representation const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//template<typename T1, typename T2, typename T3>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::pow_rev1(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_type<T2> const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_type<T3> const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::pow_rev1(mpfr_bin_ieee754_flavor<T>::representation_dec const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//template<typename T>
//template<typename T1, typename T2, typename T3>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::pow_rev1(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1>  const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2>  const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec_type<T3>  const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::pow_rev1(mpfr_bin_ieee754_flavor<T>::representation const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//template<typename T1, typename T2>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::pow_rev1(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_type<T2> const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::pow_rev1(mpfr_bin_ieee754_flavor<T>::representation_dec const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//template<typename T>
//template<typename T1, typename T2>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::pow_rev1(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//
//// pow_rev2
//
//// bare version
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::pow_rev2(mpfr_bin_ieee754_flavor<T>::representation const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//template<typename T1, typename T2, typename T3>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::pow_rev2(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_type<T2> const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_type<T3> const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::pow_rev2(mpfr_bin_ieee754_flavor<T>::representation_dec const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//template<typename T>
//template<typename T1, typename T2, typename T3>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::pow_rev2(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1>  const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2>  const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec_type<T3>  const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::pow_rev2(mpfr_bin_ieee754_flavor<T>::representation const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//template<typename T1, typename T2>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::pow_rev2(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_type<T2> const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::pow_rev2(mpfr_bin_ieee754_flavor<T>::representation_dec const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//template<typename T>
//template<typename T1, typename T2>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::pow_rev2(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const&,
//                                     mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//
//// atan2_rev1
//
//// bare version
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::atan2_rev1(mpfr_bin_ieee754_flavor<T>::representation const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//template<typename T1, typename T2, typename T3>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::atan2_rev1(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_type<T2> const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_type<T3> const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::atan2_rev1(mpfr_bin_ieee754_flavor<T>::representation_dec const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_dec const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_dec const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//template<typename T>
//template<typename T1, typename T2, typename T3>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::atan2_rev1(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1>  const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2>  const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_dec_type<T3>  const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::atan2_rev1(mpfr_bin_ieee754_flavor<T>::representation const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//template<typename T1, typename T2>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::atan2_rev1(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_type<T2> const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::atan2_rev1(mpfr_bin_ieee754_flavor<T>::representation_dec const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_dec const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//template<typename T>
//template<typename T1, typename T2>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::atan2_rev1(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//// atan2_rev2
//
//// bare version
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::atan2_rev2(mpfr_bin_ieee754_flavor<T>::representation const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//template<typename T1, typename T2, typename T3>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::atan2_rev2(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_type<T2> const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_type<T3> const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::atan2_rev2(mpfr_bin_ieee754_flavor<T>::representation_dec const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_dec const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_dec const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//template<typename T>
//template<typename T1, typename T2, typename T3>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::atan2_rev2(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1>  const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2>  const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_dec_type<T3>  const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::atan2_rev2(mpfr_bin_ieee754_flavor<T>::representation const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//template<typename T1, typename T2>
//typename mpfr_bin_ieee754_flavor<T>::representation
//mpfr_bin_ieee754_flavor<T>::atan2_rev2(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_type<T2> const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire();
//}
//
//template<typename T>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::atan2_rev2(mpfr_bin_ieee754_flavor<T>::representation_dec const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_dec const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}
//
//template<typename T>
//template<typename T1, typename T2>
//typename mpfr_bin_ieee754_flavor<T>::representation_dec
//mpfr_bin_ieee754_flavor<T>::atan2_rev2(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const&,
//                                       mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const&)
//{
//    LIBIEEEP1788_NOT_IMPLEMENTED;
//
//    return mpfr_bin_ieee754_flavor<T>::entire_dec();
//}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_REV_ELEM_FUNC_IMPL_HPP
