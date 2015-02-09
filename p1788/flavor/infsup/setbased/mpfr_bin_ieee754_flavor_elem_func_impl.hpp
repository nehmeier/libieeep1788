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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_ELEM_FUNC_IMPL_HPP


namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{

// pos

// pos ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::pos(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return empty();

    return x;
}

// pos ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::pos(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    return convert_hull(x);
}

// pos ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::pos(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x))
        return nai();

    return x;
}

// pos ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::pos(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    return convert_hull(x);
}


// neg

// neg ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::neg(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    return representation(-x.second, -x.first);
}


// neg ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::neg(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    return convert_hull(mpfr_bin_ieee754_flavor<T_>::neg(x));
}

// neg ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::neg(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    return representation_dec(neg(x.first), x.second);
}

// neg ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::neg(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    return convert_hull(mpfr_bin_ieee754_flavor<T_>::neg(x));
}




// add

// add ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::add(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y) ||  is_empty(x) || is_empty(y))
        return empty();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_var yl(y.first, MPFR_RNDD);
    mpfr_var yu(y.second, MPFR_RNDU);


    xl.subnormalize(mpfr_add(xl(), xl(), yl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_add(xu(), xu(), yu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}


// add ( bare interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::add(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::add(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}


// add ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::add(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return nai();

    // compute bare result
    representation bare = add(x.first, y.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            std::min(x.second, y.second),
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            is_empty(bare) ? p1788::decoration::decoration::trv :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// add ( decorated interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::add(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::add(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}





// sub

// sub ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sub(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y) ||  is_empty(x) || is_empty(y))
        return empty();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_var yl(y.first, MPFR_RNDD);
    mpfr_var yu(y.second, MPFR_RNDU);


    xl.subnormalize(mpfr_sub(xl(), xl(), yu(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_sub(xu(), xu(), yl(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

// sub ( bare interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sub(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sub(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}


// sub ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sub(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return nai();

    // compute bare result
    representation bare = sub(x.first, y.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            std::min(x.second, y.second),
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            is_empty(bare) ? p1788::decoration::decoration::trv :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// sub ( decorated interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sub(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sub(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}


// mul

// mul ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::mul(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y) ||  is_empty(x) || is_empty(y))
        return empty();

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


    if (y.second <= 0.0)
    {
        if (x.second <= 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_mul(l(), xu(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xl(), yl(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (x.first >= 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_mul(l(), xu(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xl(), yu(), MPFR_RNDU), MPFR_RNDU);
        }
        else
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);

            l.subnormalize(mpfr_mul(l(), xu(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xl(), yl(), MPFR_RNDU), MPFR_RNDU);
        }
    }
    else if (y.first >= 0.0)
    {
        if (x.second <= 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_mul(l(), xl(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xu(), yl(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (x.first >= 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_mul(l(), xl(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xu(), yu(), MPFR_RNDU), MPFR_RNDU);
        }
        else
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_mul(l(), xl(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xu(), yu(), MPFR_RNDU), MPFR_RNDU);
        }
    }
    else
    {
        if (x.second <= 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_mul(l(), xl(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xl(), yl(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (x.first >= 0.0)
        {
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_mul(l(), xu(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_mul(u(), xu(), yu(), MPFR_RNDU), MPFR_RNDU);
        }
        else
        {
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

// mul ( bare interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::mul(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::mul(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}


// mul ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::mul(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return nai();

    // compute bare result
    representation bare = mul(x.first, y.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            std::min(x.second, y.second),
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            is_empty(bare) ? p1788::decoration::decoration::trv :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// mul ( decorated interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::mul(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::mul(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}


// div

// div ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::div(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y) ||  is_empty(x) || is_empty(y))
        return empty();

    if (y.first == 0.0 && y.second == 0.0)
        return empty();

    if (x.first == 0.0 && x.second == 0.0)
        return x;

    if ((y.first < 0.0 && y.second > 0.0)
            || (x.first < 0.0 && x.second > 0.0
                && (y.first == 0.0 || y.second == 0.0)))
        return entire();

//    if ((x.second < 0.0 || x.first > 0.0) && y.first == 0.0 && y.second == 0.0)
//        return empty();

    mpfr_var::setup();
    mpfr_var l;
    mpfr_var u;

    if (x.second <= 0.0)
    {
        if (y.second < 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_div(l(), xu(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_div(u(), xl(), yu(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (y.first > 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_div(l(), xl(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_div(u(), xu(), yu(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (y.second == 0.0)
        {
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);

            l.subnormalize(mpfr_div(l(), xu(), yl(), MPFR_RNDD), MPFR_RNDD);
            mpfr_set_inf(u(), +1);
        }
        else if (y.first == 0.0)
        {
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_set_inf(l(), -1);
            u.subnormalize(mpfr_div(u(), xu(), yu(), MPFR_RNDU), MPFR_RNDU);
        }
    }
    else if (x.first >= 0.0)
    {
        if (y.second < 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_div(l(), xu(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_div(u(), xl(), yl(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (y.first > 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_div(l(), xl(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_div(u(), xu(), yl(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (y.second == 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);

            mpfr_var yl(y.first, MPFR_RNDD);

            mpfr_set_inf(l(), -1);
            u.subnormalize(mpfr_div(u(), xl(), yl(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (y.first == 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);

            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_div(l(), xl(), yu(), MPFR_RNDD), MPFR_RNDD);
            mpfr_set_inf(u(), +1);
        }
    }
    else
    {
        if (y.second < 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yu(y.second, MPFR_RNDU);

            l.subnormalize(mpfr_div(l(), xu(), yu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_div(u(), xl(), yu(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (y.first > 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);

            l.subnormalize(mpfr_div(l(), xl(), yl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_div(u(), xu(), yl(), MPFR_RNDU), MPFR_RNDU);
        }
    }

    return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
}

// div ( bare interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::div(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::div(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}


// div ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::div(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return nai();

    // compute bare result
    representation bare = div(x.first, y.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            std::min(x.second, y.second),
                                            is_member(0.0, y) || is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// div ( decorated interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::div(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::div(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}


// recip

// recip ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::recip(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return empty();

    return div(representation(1.0, 1.0), x);
}

// recip ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::recip(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::recip(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// recip ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::recip(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = recip(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_member(0.0, x) || is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// recip ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::recip(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::recip(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}



// sqr

// sqr ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sqr(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    mpfr_var::setup();

    if (x.first < 0.0 && x.second > 0.0)
    {
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

// sqr ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sqr(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sqr(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// sqr ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sqr(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = sqr(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// sqr ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sqr(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sqr(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}




// sqrt

// sqrt ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sqrt(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x) || x.second < 0.0)
        return empty();

    mpfr_var::setup();

    if (x.first < 0.0)
    {
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

// sqrt ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sqrt(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sqrt(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// sqrt ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sqrt(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = sqrt(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            x.first.first < 0.0 || is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// sqrt ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sqrt(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sqrt(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}



// fma

// fma ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::fma(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                mpfr_bin_ieee754_flavor<T>::representation const& y,
                                mpfr_bin_ieee754_flavor<T>::representation const& z)
{
    if (!is_valid(x) || !is_valid(y) || !is_valid(z)
            ||  is_empty(x) || is_empty(y) || is_empty(z))
        return empty();

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


    if (y.second <= 0.0)
    {
        if (x.second <= 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xu(), yu(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xl(), yl(), zu(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (x.first >= 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xu(), yl(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xl(), yu(), zu(), MPFR_RNDU), MPFR_RNDU);
        }
        else
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xu(), yl(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xl(), yl(), zu(), MPFR_RNDU), MPFR_RNDU);
        }
    }
    else if (y.first >= 0.0)
    {
        if (x.second <= 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xl(), yu(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xu(), yl(), zu(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (x.first >= 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xl(), yl(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xu(), yu(), zu(), MPFR_RNDU), MPFR_RNDU);
        }
        else
        {
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xl(), yu(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xu(), yu(), zu(), MPFR_RNDU), MPFR_RNDU);
        }
    }
    else
    {
        if (x.second <= 0.0)
        {
            mpfr_var xl(x.first, MPFR_RNDD);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xl(), yu(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xl(), yl(), zu(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (x.first >= 0.0)
        {
            mpfr_var xu(x.second, MPFR_RNDU);

            mpfr_var yl(y.first, MPFR_RNDD);
            mpfr_var yu(y.second, MPFR_RNDU);

            mpfr_var zl(z.first, MPFR_RNDD);
            mpfr_var zu(z.second, MPFR_RNDU);

            l.subnormalize(mpfr_fma(l(), xu(), yl(), zl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_fma(u(), xu(), yu(), zu(), MPFR_RNDU), MPFR_RNDU);
        }
        else
        {
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

// fma ( bare interval ) mixed type
template<typename T>
template<typename T1, typename T2, typename T3>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::fma(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& y,
                                mpfr_bin_ieee754_flavor<T>::representation_type<T3> const& z)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T3>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)
            || !mpfr_bin_ieee754_flavor<T2>::is_valid(y)
            || !mpfr_bin_ieee754_flavor<T3>::is_valid(z))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2,T3>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::fma(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(z)
               )
           );
}


// fma ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::fma(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec const& y,
                                mpfr_bin_ieee754_flavor<T>::representation_dec const& z)
{
    if (!is_valid(x) || !is_valid(y) || !is_valid(z)
            || is_nai(x) || is_nai(y) || is_nai(z))
        return nai();

    // compute bare result
    representation bare = fma(x.first, y.first, z.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            std::min(std::min(x.second, y.second), z.second),
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// fma ( decorated interval ) mixed type
template<typename T>
template<typename T1, typename T2, typename T3>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::fma(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& y,
                                mpfr_bin_ieee754_flavor<T>::representation_dec_type<T3> const& z)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T3>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x)
            || !mpfr_bin_ieee754_flavor<T2>::is_valid(y)
            || !mpfr_bin_ieee754_flavor<T3>::is_valid(z))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2,T3>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::fma(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(z)
               )
           );
}




// pown

// pown ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::pown(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                 int p)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    mpfr_var::setup();

    // positive
    if (p > 0)
    {
        // even
        if (p % 2 == 0)
        {
            if (x.first < 0.0 && x.second > 0.0)
            {
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
    if (p < 0)
    {
        if (x.first == 0.0 && x.second == 0.0)
            return empty();

        // even
        if (p % 2 == 0)
        {
            if (x.first < 0.0 && x.second > 0.0)
            {
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
            return entire();

        if (x.first == 0.0)
        {
            mpfr_var l(x.second, MPFR_RNDU);
            l.subnormalize(mpfr_pow_si(l(), l(), p, MPFR_RNDD), MPFR_RNDD);

            return representation(l.template get<T>(MPFR_RNDD), std::numeric_limits<T>::infinity());
        }

        if (x.second == 0.0)
        {
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

// pown ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::pown(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x,
                                 int p)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::pown(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   p
               )
           );
}


// pown ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::pown(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                 int p)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = pown(x.first, p);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            (p < 0 && is_member(0.0,x)) || is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// pown ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::pown(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x,
                                 int p)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::pown(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   p
               )
           );
}


// pow

// pow ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::pow(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_empty(y))
        return empty();

    representation xx = intersect(x, representation(0.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    if (xx.second == 0.0)
    {
        if (y.second <= 0.0)
        {
            return empty();
        }
        else
        {
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

    if (0.0 <= y.first)
    {
        if (xx.second <= 1.0)
        {
            // special cases: x_lower==0 && (y==[0.0] || y==[0.0,r])

            z_lower.subnormalize(mpfr_pow(z_lower(), x_lower(), y_upper(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_upper(), y_lower(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (1.0 <= xx.first)
        {
            z_lower.subnormalize(mpfr_pow(z_lower(), x_lower(), y_lower(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_upper(), y_upper(), MPFR_RNDU), MPFR_RNDU);
        }
        else     // xx.first < 1 && 1 < xx.second
        {
            // special cases: x_lower==0 && (y==[0.0] || y==[0.0,r])

            z_lower.subnormalize(mpfr_pow(z_lower(), x_lower(), y_upper(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_upper(), y_upper(), MPFR_RNDU), MPFR_RNDU);
        }
    }
    else if (y.second <= 0.0)
    {
        if (xx.second <= 1.0)
        {
            // special cases: x_lower==0 && (y==[0.0] || y==[-r,0.0])

            z_lower.subnormalize(mpfr_pow(z_lower(), x_upper(), y_upper(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_lower(), y_lower(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (1.0 <= xx.first)
        {
            z_lower.subnormalize(mpfr_pow(z_lower(), x_upper(), y_lower(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_lower(), y_upper(), MPFR_RNDU), MPFR_RNDU);
        }
        else     // xx.first < 1 && 1 < xx.second
        {
            // special cases: x_lower==0 && (y==[0.0] || y==[-r,0.0])

            z_lower.subnormalize(mpfr_pow(z_lower(), x_upper(), y_lower(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_lower(), y_lower(), MPFR_RNDU), MPFR_RNDU);
        }
    }
    else     // y.first < 0 && 0 < y.second
    {
        if (xx.second <= 1.0)
        {
            // special cases: x_lower==0 && y==[-r,r]
            z_lower.subnormalize(mpfr_pow(z_lower(), x_lower(), y_upper(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_lower(), y_lower(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (1.0 <= xx.first)
        {
            z_lower.subnormalize(mpfr_pow(z_lower(), x_upper(), y_lower(), MPFR_RNDD), MPFR_RNDD);
            z_upper.subnormalize(mpfr_pow(z_upper(), x_upper(), y_upper(), MPFR_RNDU), MPFR_RNDU);
        }
        else     // xx.first < 1 && 1 < xx.second
        {
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
}


// pow ( bare interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::pow(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::pow(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}


// pow ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::pow(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return nai();

    // compute bare result
    representation bare = pow(x.first, y.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            std::min(x.second, y.second),
                                            x.first.first < 0.0 || (is_member(0.0, x) && y.first.first <= 0.0) || is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// pow ( decorated interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::pow(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::pow(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}



// exp

// exp ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::exp(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    l.subnormalize(mpfr_exp(l(), l(), MPFR_RNDD), MPFR_RNDD);
    u.subnormalize(mpfr_exp(u(), u(), MPFR_RNDU), MPFR_RNDU);

    return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
}

// exp ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::exp(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::exp(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// exp ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::exp(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = exp(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// exp ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::exp(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::exp(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// exp2

// exp2 ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::exp2(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    l.subnormalize(mpfr_exp2(l(), l(), MPFR_RNDD), MPFR_RNDD);
    u.subnormalize(mpfr_exp2(u(), u(), MPFR_RNDU), MPFR_RNDU);

    return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
}

// exp2 ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::exp2(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::exp2(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// exp2 ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::exp2(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = exp2(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// exp2 ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::exp2(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::exp2(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// exp10

// exp10 ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::exp10(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    mpfr_var::setup();
    mpfr_var l(x.first, MPFR_RNDD);
    mpfr_var u(x.second, MPFR_RNDU);

    l.subnormalize(mpfr_exp10(l(), l(), MPFR_RNDD), MPFR_RNDD);
    u.subnormalize(mpfr_exp10(u(), u(), MPFR_RNDU), MPFR_RNDU);

    return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
}

// exp10 ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::exp10(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::exp10(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// exp10 ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::exp10(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = exp10(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// exp10 ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::exp10(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::exp10(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}



// log

// log ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::log(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return empty();

    representation xx = intersect(x, representation(0.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    if (x.second <= 0.0)
        return empty();

    mpfr_var::setup();
    mpfr_var xl(x.first <= 0.0 ? 0.0 : x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_log(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_log(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

// log ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::log(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::log(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// log ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::log(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = log(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            x.first.first <= 0.0 || is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// log ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::log(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::log(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}



// log2

// log2 ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::log2(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return empty();

    representation xx = intersect(x, representation(0.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    if (x.second <= 0.0)
        return empty();

    mpfr_var::setup();
    mpfr_var xl(x.first <= 0.0 ? 0.0 : x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_log2(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_log2(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

// log2 ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::log2(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::log2(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// log2 ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::log2(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = log2(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            x.first.first <= 0.0 || is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// log2 ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::log2(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::log2(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// log10

// log10 ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::log10(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return empty();

    representation xx = intersect(x, representation(0.0, std::numeric_limits<T>::infinity()));

    if (is_empty(xx))
        return xx;

    if (x.second <= 0.0)
        return empty();

    mpfr_var::setup();
    mpfr_var xl(x.first <= 0.0 ? 0.0 : x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_log10(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_log10(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

// log10 ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::log10(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::log10(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// log10 ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::log10(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = log10(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            x.first.first <= 0.0 || is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// log10 ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::log10(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::log10(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// sin

// sin ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sin(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    //TODO ueberarbeiten? die Null-Faelle zusammenfassen. Cos dann natuerlich auch

    if (!is_valid(x) || is_empty(x))
        return empty();

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

    if (df_lower != df_upper)
    {
        if (df_lower == 0)
        {
            if (mpfr_cmp(w(), pi()) > 0)
                return representation(-1.0, 1.0);
        }
        else if (df_upper == 0)
        {
            if (mpfr_cmp(w(), pi()) > 0)
                return representation(-1.0, 1.0);
        }
        else
        {
            mpfr_var pi2;
            mpfr_mul_si(pi2(), pi(), 2, MPFR_RNDD);

            if (mpfr_cmp(w(), pi2()) > 0)
                return representation(-1.0, 1.0);

            if (df_lower > 0)
            {
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
    }
    else if (mpfr_cmp(w(), pi()) > 0)
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

// sin ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sin(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sin(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// sin ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sin(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = sin(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// sin ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sin(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sin(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// cos

// cos ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cos(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

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

    if (df_lower != df_upper)
    {
        if (df_lower == 0)
        {
            if (mpfr_cmp(w(), pi()) > 0)
                return representation(-1.0, 1.0);
        }
        else if (df_upper == 0)
        {
            if (mpfr_cmp(w(), pi()) > 0)
                return representation(-1.0, 1.0);
        }
        else
        {
            mpfr_var pi2;
            mpfr_mul_si(pi2(), pi(), 2, MPFR_RNDD);

            if (mpfr_cmp(w(), pi2()) > 0)
                return representation(-1.0, 1.0);

            if (df_lower > 0)
            {
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
    }
    else if (mpfr_cmp(w(), pi()) > 0)
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

// cos ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cos(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::cos(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// cos ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cos(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = cos(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// cos ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cos(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::cos(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// tan

// tan ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::tan(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_var pi;
    mpfr_const_pi(pi(), MPFR_RNDD);

    mpfr_var w;
    mpfr_sub(w(), xu(), xl(), MPFR_RNDU);

    if (mpfr_cmp(w(), pi()) > 0)
        return entire();

    xl.subnormalize(mpfr_tan(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_tan(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    if (mpfr_cmp(xl(), xu()) > 0)
        return entire();

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}


// tan ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::tan(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::tan(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// tan ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::tan(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    if (is_empty(x))
        return empty_dec();

    mpfr_var::setup();

    mpfr_var xl(x.first.first, MPFR_RNDD);
    mpfr_var xu(x.first.second, MPFR_RNDU);

    mpfr_var pi;
    mpfr_const_pi(pi(), MPFR_RNDD);

    mpfr_var w;
    mpfr_sub(w(), xu(), xl(), MPFR_RNDU);

    if (mpfr_cmp(w(), pi()) > 0)
        return representation_dec(entire(), p1788::decoration::decoration::trv);

    xl.subnormalize(mpfr_tan(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_tan(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    if (mpfr_cmp(xl(), xu()) > 0)
        return representation_dec(entire(), p1788::decoration::decoration::trv);

    representation bare(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
    p1788::decoration::decoration dec  = std::min(x.second,
                                         is_common(bare) ? p1788::decoration::decoration::com :
                                         p1788::decoration::decoration::dac);

    return representation_dec(bare, dec);
}

// tan ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::tan(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::tan(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// asin

// asin ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::asin(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return empty();

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

// asin ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::asin(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::asin(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// asin ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::asin(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = asin(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            x.first.first < -1.0 || x.first.second > 1.0 || is_empty(bare) ?  p1788::decoration::decoration::trv
                                            : p1788::decoration::decoration::com);

    return representation_dec(bare, dec);
}

// asin ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::asin(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::asin(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// acos

// acos ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::acos(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return empty();

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


// acos ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::acos(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::acos(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// acos ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::acos(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = acos(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            x.first.first < -1.0 || x.first.second > 1.0 || is_empty(bare) ?  p1788::decoration::decoration::trv
                                            : p1788::decoration::decoration::com);

    return representation_dec(bare, dec);
}

// acos ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::acos(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::acos(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// atan

// atan ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::atan(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_atan(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_atan(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}


// atan ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::atan(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::atan(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// atan ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::atan(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = atan(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv : p1788::decoration::decoration::com);

    return representation_dec(bare, dec);
}

// atan ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::atan(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::atan(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}



// atan2

// atan2 ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::atan2(mpfr_bin_ieee754_flavor<T>::representation const& y,
                                  mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(y) || !is_valid(x) || is_empty(y) || is_empty(x) ||
            (y.first == 0.0 && y.second == 0.0 && x.first == 0.0 && x.second == 0.0))
        return empty();

    mpfr_var::setup();

    mpfr_var l;
    mpfr_var u;

    mpfr_var yl(y.first, MPFR_RNDD);
    mpfr_var yu(y.second, MPFR_RNDU);
    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    if (y.first >= 0.0 && y.second > 0.0)
    {
        if (x.first == 0.0 && x.second == 0.0)
        {
            l.subnormalize(mpfr_atan2(l(), yu(), xl(), MPFR_RNDD), MPFR_RNDD);  // pi/2
            u.subnormalize(mpfr_atan2(u(), yu(), xl(), MPFR_RNDU), MPFR_RNDU);  // pi/2
        }
        else if (x.first >= 0.0)
        {
            l.subnormalize(mpfr_atan2(l(), yl(), xu(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_atan2(u(), yu(), xl(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (x.second <= 0.0)
        {
            l.subnormalize(mpfr_atan2(l(), yu(), xu(), MPFR_RNDD), MPFR_RNDD);

            if (y.first == 0.0)
                u.subnormalize(mpfr_const_pi(u(), MPFR_RNDU), MPFR_RNDU);   // pi
            else
                u.subnormalize(mpfr_atan2(u(), yl(), xl(), MPFR_RNDU), MPFR_RNDU);
        }
        else
        {
            if (y.first == 0.0)
            {
                l.set(0.0, MPFR_RNDD);
                u.subnormalize(mpfr_const_pi(u(), MPFR_RNDU), MPFR_RNDU);   // pi
            }
            else
            {
                l.subnormalize(mpfr_atan2(l(), yl(), xu(), MPFR_RNDD), MPFR_RNDD);
                u.subnormalize(mpfr_atan2(u(), yl(), xl(), MPFR_RNDU), MPFR_RNDU);
            }
        }
    }
    else if (y.first < 0.0 && y.second <= 0.0)
    {
        if (x.first == 0.0 && x.second == 0.0)
        {
            l.subnormalize(mpfr_atan2(l(), yl(), xl(), MPFR_RNDD), MPFR_RNDD);  // -pi/2
            u.subnormalize(mpfr_atan2(u(), yl(), xl(), MPFR_RNDU), MPFR_RNDU);  // -pi/2
        }
        else if (x.first >= 0.0)
        {
            l.subnormalize(mpfr_atan2(l(), yl(), xl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_atan2(u(), yu(), xu(), MPFR_RNDU), MPFR_RNDU);
        }
        else if (x.second <= 0.0)
        {
            if (y.second == 0.0)
            {
                u.subnormalize(mpfr_const_pi(u(), MPFR_RNDU), MPFR_RNDU);   // pi
                l.subnormalize(mpfr_neg(l(), u(), MPFR_RNDD), MPFR_RNDD);   // -pi
            }
            else
            {
                l.subnormalize(mpfr_atan2(l(), yu(), xl(), MPFR_RNDD), MPFR_RNDD);
                u.subnormalize(mpfr_atan2(u(), yl(), xu(), MPFR_RNDU), MPFR_RNDU);
            }
        }
        else
        {
            if (y.second == 0.0)
            {
                l.subnormalize(mpfr_const_pi(l(), MPFR_RNDU), MPFR_RNDU);   // pi
                l.subnormalize(mpfr_neg(l(), l(), MPFR_RNDD), MPFR_RNDD);   // -pi
                u.set(0.0, MPFR_RNDU);
            }
            else
            {
                l.subnormalize(mpfr_atan2(l(), yu(), xl(), MPFR_RNDD), MPFR_RNDD);
                u.subnormalize(mpfr_atan2(u(), yu(), xu(), MPFR_RNDU), MPFR_RNDU);
            }
        }
    }
    else if (y.first == 0.0 && y.second == 0.0)
    {
        if (x.first >= 0.0)
        {
            l.set(0.0, MPFR_RNDD);
            u.set(0.0, MPFR_RNDU);
        }
        else if (x.second <= 0.0)
        {
            l.subnormalize(mpfr_const_pi(l(), MPFR_RNDD), MPFR_RNDD);   // pi
            u.subnormalize(mpfr_const_pi(u(), MPFR_RNDU), MPFR_RNDU);   // pi
        }
        else
        {
            l.set(0.0, MPFR_RNDD);
            u.subnormalize(mpfr_const_pi(u(), MPFR_RNDU), MPFR_RNDU);   // pi
        }
    }
    else
    {
        if (x.first >= 0.0)
        {
            l.subnormalize(mpfr_atan2(l(), yl(), xl(), MPFR_RNDD), MPFR_RNDD);
            u.subnormalize(mpfr_atan2(u(), yu(), xl(), MPFR_RNDU), MPFR_RNDU);
        }
        else
        {
            u.subnormalize(mpfr_const_pi(u(), MPFR_RNDU), MPFR_RNDU);   // pi
            l.subnormalize(mpfr_neg(l(), u(), MPFR_RNDD), MPFR_RNDD);   // -pi
        }
    }


    return representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU));
}

// atan2 ( bare interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::atan2(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& y,
                                  mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(y) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::atan2(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// atan2 ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::atan2(mpfr_bin_ieee754_flavor<T>::representation_dec const& y,
                                  mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(y) || !is_valid(x) || is_nai(y) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = atan2(y.first, x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            std::min(y.second, x.second),
                                            (is_member(0.0, y) && is_member(0.0, x)) || is_empty(bare) ? p1788::decoration::decoration::trv :
                                            is_member(0.0, y) && x.first.first < 0.0 ? p1788::decoration::decoration::def :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// atan2 ( decorated interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::atan2(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& y,
                                  mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& x)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(y) || !mpfr_bin_ieee754_flavor<T2>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::atan2(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// sinh

// sinh ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sinh(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_sinh(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_sinh(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}


// sinh ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sinh(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sinh(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// sinh ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sinh(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = sinh(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// sinh ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sinh(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sinh(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// cosh

// cosh ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cosh(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    mpfr_var::setup();

    if (x.first < 0.0 && x.second > 0.0)
    {
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

// cosh ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cosh(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::cosh(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// cosh ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cosh(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = cosh(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// cosh ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cosh(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::cosh(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// tanh

// tanh ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::tanh(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_tanh(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_tanh(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

// tanh ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::tanh(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::tanh(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// tanh ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::tanh(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = tanh(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv
                                            : p1788::decoration::decoration::com);
    return representation_dec(bare, dec);
}

// tanh ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::tanh(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::tanh(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// asinh

// asinh ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::asinh(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_asinh(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_asinh(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

// asinh ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::asinh(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::asinh(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// asinh ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::asinh(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = asinh(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// asinh ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::asinh(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::asinh(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// acosh

// acosh ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::acosh(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x) || x.second < 1.0)
        return empty();

    mpfr_var::setup();

    mpfr_var xl(x.first < 1.0 ? 1.0 : x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_acosh(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_acosh(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

// acosh ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::acosh(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::acosh(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// acosh ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::acosh(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = acosh(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            x.first.first < 1.0 || is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// acosh ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::acosh(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::acosh(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// atanh

// atanh ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::atanh(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x) || x.second <= -1.0 || x.first >= 1.0)
        return empty();

    mpfr_var::setup();

    mpfr_var xl(x.first < -1.0 ? -1.0 : x.first, MPFR_RNDD);
    mpfr_var xu(x.second > 1.0 ? 1.0 : x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_atanh(xl(), xl(), MPFR_RNDD), MPFR_RNDD);
    xu.subnormalize(mpfr_atanh(xu(), xu(), MPFR_RNDU), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

// atanh ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::atanh(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::atanh(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// atanh ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::atanh(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = atanh(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            x.first.first <= -1.0 || x.first.second >= 1.0 || is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// atanh ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::atanh(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::atanh(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// sign

// sign ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sign(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    return representation((x.first < 0.0) ? -1.0 : ((x.first == 0.0) ? 0.0 : 1.0),
                          (x.second < 0.0) ? -1.0 : ((x.second == 0.0) ? 0.0 : 1.0));
}

// sign ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::sign(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sign(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// sign ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sign(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = sign(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            !is_singleton(bare) ? p1788::decoration::decoration::def :
                                            is_member(0.0, x) ? p1788::decoration::decoration::dac :
                                            p1788::decoration::decoration::com);
    return representation_dec(bare, dec);
}

// sign ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::sign(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::sign(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}



// ceil

// ceil ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::ceil(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    return representation(std::ceil(x.first), std::ceil(x.second));
}

// ceil ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::ceil(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::ceil(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// ceil ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::ceil(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = ceil(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            !is_singleton(bare) ? p1788::decoration::decoration::def :
                                            x.first.second == bare.second ? p1788::decoration::decoration::dac :
                                            p1788::decoration::decoration::com);
    return representation_dec(bare, dec);
}

// ceil ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::ceil(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::ceil(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// floor

// floor ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::floor(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    return representation(std::floor(x.first), std::floor(x.second));
}

// floor ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::floor(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::floor(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// floor ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::floor(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = floor(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            !is_singleton(bare) ? p1788::decoration::decoration::def :
                                            x.first.first == bare.first ? p1788::decoration::decoration::dac :
                                            p1788::decoration::decoration::com);
    return representation_dec(bare, dec);
}

// floor ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::floor(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::floor(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// trunc

// trunc ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::trunc(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    return representation(std::trunc(x.first), std::trunc(x.second));
}

// trunc ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::trunc(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::trunc(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// trunc ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::trunc(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = trunc(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            !is_singleton(bare) ? p1788::decoration::decoration::def :
                                            (x.first.first != 0.0 && x.first.first == bare.first)
                                            || (x.first.second != 0.0 && x.first.second == bare.second) ? p1788::decoration::decoration::dac :
                                            p1788::decoration::decoration::com);
    return representation_dec(bare, dec);
}

// trunc ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::trunc(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::trunc(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// round_ties_to_even

// round_ties_to_even ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::round_ties_to_even(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    class rnd_controll
    {
        int rnd_;
    public:
        rnd_controll() : rnd_(std::fegetround())
        {
            std::fesetround(FE_TONEAREST);
        }

        ~rnd_controll()
        {
            std::fesetround(rnd_);
        }
    } rnd;

    return representation(std::nearbyint(x.first), std::nearbyint(x.second));
}

// round_ties_to_even ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::round_ties_to_even(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::round_ties_to_even(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// round_ties_to_even ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::round_ties_to_even(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = round_ties_to_even(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            !is_singleton(bare) ? p1788::decoration::decoration::def :
                                            std::abs(x.first.first) - std::trunc(std::abs(x.first.first)) == 0.5       // if x == 0.5 => trunc(x) == 0.0 => exact
                                            || std::abs(x.first.second) - std::trunc(std::abs(x.first.second)) == 0.5  // if x > 1  => trunc(x) > 1 => tunc(x) <= x <= 2 trunc(x) => exact
                                            ? p1788::decoration::decoration::dac : p1788::decoration::decoration::com);
    return representation_dec(bare, dec);
}

// round_ties_to_even ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::round_ties_to_even(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::round_ties_to_even(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// round_ties_to_away

// round_ties_to_away ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::round_ties_to_away(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    return representation(std::round(x.first), std::round(x.second));
}

// round_ties_to_away ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::round_ties_to_away(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::round_ties_to_away(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// round_ties_to_away ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::round_ties_to_away(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = round_ties_to_away(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            !is_singleton(bare) ? p1788::decoration::decoration::def :
                                            std::abs(x.first.first) - std::trunc(std::abs(x.first.first)) == 0.5      // if x == 0.5 => trunc(x) == 0.0 => exact
                                            || std::abs(x.first.second) - std::trunc(std::abs(x.first.second)) == 0.5 // if x > 1  => trunc(x) > 1 => tunc(x) <= x <= 2 * trunc(x) => exact
                                            ? p1788::decoration::decoration::dac : p1788::decoration::decoration::com);
    return representation_dec(bare, dec);
}

// round_ties_to_away ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::round_ties_to_away(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::round_ties_to_away(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// abs

// abs ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::abs(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return empty();

    if (x.first >= 0.0)
        return x;

    if (x.second <= 0.0)
        return representation(std::abs(x.second), std::abs(x.first));

    return representation(0.0, std::max(std::abs(x.first), x.second));
}

// abs ( bare interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::abs(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::abs(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// abs ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::abs(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x) || is_nai(x))
        return nai();

    // compute bare result
    representation bare = abs(x.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            x.second,
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// abs ( decorated interval ) mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::abs(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::abs(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


// min

// min ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::min(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_empty(x) || is_empty(y))
        return empty();

    return representation(std::min(x.first, y.first), std::min(x.second, y.second));
}

// min ( bare interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::min(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::min(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}


// min ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::min(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return nai();

    // compute bare result
    representation bare = min(x.first, y.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            std::min(x.second, y.second),
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// min ( decorated interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::min(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::min(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}



// max

// max ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::max(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_empty(x) || is_empty(y))
        return empty();

    return representation(std::max(x.first, y.first), std::max(x.second, y.second));
}

// max ( bare interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::max(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::max(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}


// max ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::max(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y) || is_nai(x) || is_nai(y))
        return nai();

    // compute bare result
    representation bare = max(x.first, y.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            std::min(x.second, y.second),
                                            is_empty(bare) ?  p1788::decoration::decoration::trv :
                                            is_common(bare) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);
    return representation_dec(bare, dec);
}

// max ( decorated interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::max(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& x,
                                mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(x) || !mpfr_bin_ieee754_flavor<T2>::is_valid(y))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::max(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_ELEM_FUNC_IMPL_HPP
