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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_MUL_REV_TO_PAIR_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_MUL_REV_TO_PAIR_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{


// mul_rev_to_pair ( bare interval ) private
template<typename T>
std::pair<typename mpfr_bin_ieee754_flavor<T>::representation, typename mpfr_bin_ieee754_flavor<T>::representation>
mpfr_bin_ieee754_flavor<T>::mul_rev_to_pair(int& t_fl, int& t_fu, int& t_sl, int& t_su,
        mpfr_bin_ieee754_flavor<T>::representation const& b,
        mpfr_bin_ieee754_flavor<T>::representation const& c)
{
    t_fl = t_fu = t_sl = t_su = 0;
    if (!is_valid(b) || !is_valid(c) || is_empty(b) || is_empty(c))
        return std::pair<representation, representation>(empty(), empty());

    // c = [-oo,+oo]
    if (is_entire(c) || is_entire(b))
        return std::pair<representation, representation>(entire(), empty());    // ([-oo,+oo], empty)


    // c = [0,0]
    if (c.first == 0.0 && c.second == 0.0)
        return std::pair<representation, representation>(is_member(0.0, b) ? entire() : representation(0.0, 0.0),
                empty());


    mpfr_var::setup();

    mpfr_var bl(b.first, MPFR_RNDD);
    mpfr_var bu(b.second, MPFR_RNDU);

    mpfr_var cl(c.first, MPFR_RNDD);
    mpfr_var cu(c.second, MPFR_RNDU);



    // c <= 0
    if (c.second <= 0.0)
    {
        // b = [0,0]
        if (b.first == 0.0 && b.second == 0.0)
            return std::pair<representation, representation>(is_member(0.0, c) ? entire() : empty(),
                    empty());

        // b contains 0 interior and c < 0 => return pair
        if (b.first < 0.0 && b.second > 0.0 && c.second < 0.0)
        {
            mpfr_var f_u;
            mpfr_var s_l;

            t_fu = f_u.subnormalize(mpfr_div(f_u(), cu(), bu(), MPFR_RNDU), MPFR_RNDU);
            t_sl = s_l.subnormalize(mpfr_div(s_l(), cu(), bl(), MPFR_RNDD), MPFR_RNDD);

            return std::pair<representation, representation>(representation(-std::numeric_limits<T>::infinity(), f_u.template get<T>(MPFR_RNDU)),
                    representation(s_l.template get<T>(MPFR_RNDD), std::numeric_limits<T>::infinity()));
        }

        // b < 0.0
        if (b.second < 0.0)
        {
            mpfr_var l;
            mpfr_var u;

            t_fl = l.subnormalize(mpfr_div(l(), cu(), bl(), MPFR_RNDD), MPFR_RNDD);
            t_fu = u.subnormalize(mpfr_div(u(), cl(), bu(), MPFR_RNDU), MPFR_RNDU);

            return std::pair<representation, representation>(representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU)), empty());
        }

        // b = [x,0] and c < 0
        if (b.second == 0.0 && c.second < 0.0)
        {
            mpfr_var l;
            t_fl = l.subnormalize(mpfr_div(l(), cu(), bl(), MPFR_RNDD), MPFR_RNDD);

            return std::pair<representation, representation>(representation(l.template get<T>(MPFR_RNDD), std::numeric_limits<T>::infinity()), empty());
        }


        // b > 0.0
        if (b.first > 0.0)
        {
            mpfr_var l;
            mpfr_var u;

            t_fl = l.subnormalize(mpfr_div(l(), cl(), bl(), MPFR_RNDD), MPFR_RNDD);
            t_fu = u.subnormalize(mpfr_div(u(), cu(), bu(), MPFR_RNDU), MPFR_RNDU);

            return std::pair<representation, representation>(representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU)), empty());
        }

        // b = [0,x] and c < 0
        if (b.first == 0.0 && c.second < 0.0)
        {
            mpfr_var u;
            t_fu = u.subnormalize(mpfr_div(u(), cu(), bu(), MPFR_RNDU), MPFR_RNDU);

            return std::pair<representation, representation>(representation(-std::numeric_limits<T>::infinity(), u.template get<T>(MPFR_RNDU)), empty());
        }

        return std::pair<representation, representation>(entire(), empty());

    }   // c >= 0
    else if (c.first >= 0.0)
    {
        // b = [0,0]
        if (b.first == 0.0 && b.second == 0.0)
            return std::pair<representation, representation>(is_member(0.0, c) ? entire() : empty(),
                    empty());


        // b contains 0 interior and c > 0 => return pair
        if (b.first < 0.0 && b.second > 0.0 && c.first > 0.0)
        {
            mpfr_var f_u;
            mpfr_var s_l;

            t_fu = f_u.subnormalize(mpfr_div(f_u(), cl(), bl(), MPFR_RNDU), MPFR_RNDU);
            t_sl = s_l.subnormalize(mpfr_div(s_l(), cl(), bu(), MPFR_RNDD), MPFR_RNDD);

            return std::pair<representation, representation>(representation(-std::numeric_limits<T>::infinity(), f_u.template get<T>(MPFR_RNDU)),
                    representation(s_l.template get<T>(MPFR_RNDD), std::numeric_limits<T>::infinity()));
        }


        // b < 0.0
        if (b.second < 0.0)
        {
            mpfr_var l;
            mpfr_var u;

            t_fl = l.subnormalize(mpfr_div(l(), cu(), bu(), MPFR_RNDD), MPFR_RNDD);
            t_fu = u.subnormalize(mpfr_div(u(), cl(), bl(), MPFR_RNDU), MPFR_RNDU);

            return std::pair<representation, representation>(representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU)), empty());
        }

        // b = [x,0] and c > 0
        if (b.second == 0.0 && c.first > 0.0)
        {
            mpfr_var u;
            t_fu = u.subnormalize(mpfr_div(u(), cl(), bl(), MPFR_RNDU), MPFR_RNDU);

            return std::pair<representation, representation>(representation(-std::numeric_limits<T>::infinity(), u.template get<T>(MPFR_RNDU)), empty());
        }


        // b > 0.0
        if (b.first > 0.0)
        {
            mpfr_var l;
            mpfr_var u;

            t_fl = l.subnormalize(mpfr_div(l(), cl(), bu(), MPFR_RNDD), MPFR_RNDD);
            t_fu = u.subnormalize(mpfr_div(u(), cu(), bl(), MPFR_RNDU), MPFR_RNDU);

            return std::pair<representation, representation>(representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU)), empty());
        }

        // b = [0,x] and c > 0
        if (b.first == 0.0 && c.first > 0.0)
        {
            mpfr_var l;
            t_fl = l.subnormalize(mpfr_div(l(), cl(), bu(), MPFR_RNDD), MPFR_RNDD);

            return std::pair<representation, representation>(representation(l.template get<T>(MPFR_RNDD), std::numeric_limits<T>::infinity()), empty());
        }

        return std::pair<representation, representation>(entire(), empty());
    }



    // c contains 0

    // b = [0,0]
    if (b.first == 0.0 && b.second == 0.0)
        return std::pair<representation, representation>(entire(), empty());


    // b < 0
    if (b.second < 0.0)
    {
        mpfr_var l;
        mpfr_var u;

        t_fl = l.subnormalize(mpfr_div(l(), cu(), bu(), MPFR_RNDD), MPFR_RNDD);
        t_fu = u.subnormalize(mpfr_div(u(), cl(), bu(), MPFR_RNDU), MPFR_RNDU);

        return std::pair<representation, representation>(representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU)),
                empty());
    }

    // b > 0
    if (b.first > 0.0)
    {
        mpfr_var l;
        mpfr_var u;

        t_fl = l.subnormalize(mpfr_div(l(), cl(), bl(), MPFR_RNDD), MPFR_RNDD);
        t_fu = u.subnormalize(mpfr_div(u(), cu(), bl(), MPFR_RNDU), MPFR_RNDU);

        return std::pair<representation, representation>(representation(l.template get<T>(MPFR_RNDD), u.template get<T>(MPFR_RNDU)),
                empty());
    }

    return std::pair<representation, representation>(entire(), empty());
}

// mul_rev_to_pair ( bare interval )
template<typename T>
std::pair<typename mpfr_bin_ieee754_flavor<T>::representation, typename mpfr_bin_ieee754_flavor<T>::representation>
mpfr_bin_ieee754_flavor<T>::mul_rev_to_pair(mpfr_bin_ieee754_flavor<T>::representation const& b,
        mpfr_bin_ieee754_flavor<T>::representation const& c)
{
    int t_fl, t_fu, t_sl, t_su;
    return mul_rev_to_pair(t_fl, t_fu, t_sl, t_su, b, c);
}



// mul_rev_to_pair ( bare interval ) mixed type
template<typename T>
template<typename T1, typename T2>
std::pair<typename mpfr_bin_ieee754_flavor<T>::representation, typename mpfr_bin_ieee754_flavor<T>::representation>
mpfr_bin_ieee754_flavor<T>::mul_rev_to_pair(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& b,
        mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& c)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c))
        std::pair<representation, representation>(empty(), empty());

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision;
    auto res = mpfr_bin_ieee754_flavor<T_MAX>::mul_rev_to_pair(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(b),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(c)
               );

    // 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return std::pair<representation, representation>(convert_hull(res.first), convert_hull(res.second));
}


// mul_rev_to_pair ( decorated interval )
template<typename T>
std::pair<typename mpfr_bin_ieee754_flavor<T>::representation_dec, typename mpfr_bin_ieee754_flavor<T>::representation_dec>
mpfr_bin_ieee754_flavor<T>::mul_rev_to_pair(mpfr_bin_ieee754_flavor<T>::representation_dec const& b,
        mpfr_bin_ieee754_flavor<T>::representation_dec const& c)
{
    if (!is_valid(b) || !is_valid(c) || is_nai(b) || is_nai(c))
        return std::pair<representation_dec, representation_dec>(nai(), nai());

    // compute bare result
    auto bare = mul_rev_to_pair(b.first, c.first);

    // compute decoration
    p1788::decoration::decoration dec = std::min(
                                            std::min(b.second, c.second),
                                            is_member(0.0, b) || is_empty(bare.first) ?  p1788::decoration::decoration::trv :
                                            is_common_interval(bare.first) ? p1788::decoration::decoration::com :
                                            p1788::decoration::decoration::dac);

    return std::pair<representation_dec, representation_dec>(representation_dec(bare.first, dec), representation_dec(bare.second, p1788::decoration::decoration::trv));
}

// mul_rev_to_pair ( decorated interval ) mixed type
template<typename T>
template<typename T1, typename T2>
std::pair<typename mpfr_bin_ieee754_flavor<T>::representation_dec, typename mpfr_bin_ieee754_flavor<T>::representation_dec>
mpfr_bin_ieee754_flavor<T>::mul_rev_to_pair(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& b,
        mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& c)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T1>::is_valid(b) || !mpfr_bin_ieee754_flavor<T2>::is_valid(c)
            || mpfr_bin_ieee754_flavor<T1>::is_nai(b) || mpfr_bin_ieee754_flavor<T2>::is_nai(c))
        std::pair<representation_dec, representation_dec>(nai(), nai());

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision;
    auto res = mpfr_bin_ieee754_flavor<T_MAX>::mul_rev_to_pair(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(b),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(c)
               );

    // 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return std::pair<representation_dec, representation_dec>(convert_hull(res.first), convert_hull(res.second));
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_MUL_REV_TO_PAIR_FUNC_IMPL_HPP
