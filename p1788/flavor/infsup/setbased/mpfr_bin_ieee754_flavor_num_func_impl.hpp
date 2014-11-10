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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_NUM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_NUM_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{

// inf ( bare interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::inf(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return std::numeric_limits<T>::quiet_NaN();

    if (is_empty(x))
        return std::numeric_limits<T>::infinity();

    if (x.first == 0.0)
        return -0.0;

    return x.first;
}

// inf ( bare interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::inf(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return std::numeric_limits<T>::quiet_NaN();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding and downward rounding of the result
    return convert_rndd(
               mpfr_bin_ieee754_flavor<T_MAX>::inf(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}

// inf ( decorated interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::inf(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    // call of bare version
    return !is_valid(x) || is_nai(x) ? std::numeric_limits<T>::quiet_NaN() : inf(x.first);
}

// inf ( decorated interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::inf(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call of bare mixed type version
    return !mpfr_bin_ieee754_flavor<T_>::is_valid(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(x)
           ? std::numeric_limits<T>::quiet_NaN()
           : inf(x.first);
}

// sup ( bare interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::sup(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return std::numeric_limits<T>::quiet_NaN();

    if (is_empty(x))
        return -std::numeric_limits<T>::infinity();

    if (x.second == 0.0)
        return +0.0;

    return x.second;
}

// sup ( bare interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::sup(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return std::numeric_limits<T>::quiet_NaN();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding and upward rounding of the result
    return convert_rndu(
               mpfr_bin_ieee754_flavor<T_MAX>::sup(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}

// sup ( decorated interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::sup(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    // call of bare version
    return !is_valid(x) || is_nai(x) ? std::numeric_limits<T>::quiet_NaN() : sup(x.first);
}

// sup ( decorated interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::sup(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call of bare mixed type version
    return !mpfr_bin_ieee754_flavor<T_>::is_valid(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(x)
           ? std::numeric_limits<T>::quiet_NaN()
           : sup(x.first);
}




// mid ( bare interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::mid(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    if (is_entire(x))
        return +0.0;

    if (x.first == -std::numeric_limits<T>::infinity())
        return -std::numeric_limits<T>::max();

    if (x.second == std::numeric_limits<T>::infinity())
        return std::numeric_limits<T>::max();


    // extended EMIN for error free division by 2
    typedef p1788::util::mpfr_var<mpfr_var::PREC,
            mpfr_var::EMIN -1,
            mpfr_var::EMAX,
            false>  ext_mpfr_var;

    ext_mpfr_var::setup();

    ext_mpfr_var xl(x.first, MPFR_RNDD);
    ext_mpfr_var xu(x.second, MPFR_RNDU);

    // error free because of the extended EMIN
    mpfr_div_si(xl(),xl(),2, MPFR_RNDN);
    mpfr_div_si(xu(),xu(),2, MPFR_RNDN);

    int t = mpfr_add(xl(), xl(), xu(), MPFR_RNDN);

    mpfr_var::setup();

    xl.subnormalize(mpfr_check_range(xl(), t, MPFR_RNDN), MPFR_RNDN);

    T res = xl.template get<T>(MPFR_RNDN);
    return res == -0.0 ? +0.0 : res;
}

// mid ( bare interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::mid(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    // Same code as the non mixed type version. Only the type precision is adapted...
    // Necessary to avoid double rounding???

    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x) || mpfr_bin_ieee754_flavor<T_>::is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    if (mpfr_bin_ieee754_flavor<T_>::is_entire(x))
        return +0.0;

    if (x.first == -std::numeric_limits<T_>::infinity())
        return -std::numeric_limits<T>::max();

    if (x.second == std::numeric_limits<T_>::infinity())
        return std::numeric_limits<T>::max();


    // precision of T_ and extended EMIN for error free division by 2
    typedef p1788::util::mpfr_var<mpfr_bin_ieee754_flavor<T_>::mpfr_var::PREC,
            mpfr_bin_ieee754_flavor<T_>::mpfr_var::EMIN -1,
            mpfr_bin_ieee754_flavor<T_>::mpfr_var::EMAX,
            false>  ext_mpfr_var;

    ext_mpfr_var::setup();

    ext_mpfr_var xl(x.first, MPFR_RNDD);
    ext_mpfr_var xu(x.second, MPFR_RNDU);

    // error free because of the extended EMIN
    mpfr_div_si(xl(),xl(),2, MPFR_RNDN);
    mpfr_div_si(xu(),xu(),2, MPFR_RNDN);


    mpfr_var m;

    // compute midpoint in precision of T
    int t = mpfr_add(m(), xl(), xu(), MPFR_RNDN);

    // Adjust ranges and subnormalize
    mpfr_var::setup();
    m.subnormalize(mpfr_check_range(m(), t, MPFR_RNDN), MPFR_RNDN);

    T res = m.template get<T>(MPFR_RNDN);
    return res == -0.0 ? +0.0 : res;
}

// mid ( decorated interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::mid(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    // call of bare version
    return !is_valid(x) || is_nai(x) ? std::numeric_limits<T>::quiet_NaN() : mid(x.first);
}

// mid ( decorated interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::mid(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call of bare mixed type version
    return !mpfr_bin_ieee754_flavor<T_>::is_valid(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(x)
           ? std::numeric_limits<T>::quiet_NaN()
           : mid(x.first);
}





// rad ( bare interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::rad(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    return mid_rad(x).second;
}

// rad ( bare interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::rad(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    return mid_rad(x).second;
}

// rad ( decorated interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::rad(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    // call of bare version
    return !is_valid(x) || is_nai(x) ? std::numeric_limits<T>::quiet_NaN() : rad(x.first);
}

// rad ( decorated interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::rad(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call of bare mixed type version
    return !mpfr_bin_ieee754_flavor<T_>::is_valid(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(x)
           ? std::numeric_limits<T>::quiet_NaN()
           : rad(x.first);
}




// mid_rad ( bare interval )
template<typename T>
std::pair<T, T>
mpfr_bin_ieee754_flavor<T>::mid_rad(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return std::pair<T,T>(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN());

    // compute mid point
    std::pair<T,T> mr(mid(x), 0.0);

    mpfr_var::setup();

    mpfr_var m(mr.first, MPFR_RNDN);

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    // compute the maximum distance of the midpoint to the lower and the upper bound
    // rad(x) = (xu - xl) / 2 does not guarantee that [mid(x) - rad(x), mid(x) + rad(x)] encloses x (if computed exactly)
    mpfr_sub(xl(), m(), xl(), MPFR_RNDU);
    mpfr_sub(xu(), xu(), m(), MPFR_RNDU);

    mr.second = mpfr_cmp(xl(), xu()) > 0 ? xl.template get<T>(MPFR_RNDU) : xu.template get<T>(MPFR_RNDU);

    if (mr.second == -0.0)
    {
        mr.second = +0.0;
    }
    return mr;
}

// mid_rad ( bare interval ) mixed type
template<typename T>
template<typename T_>
std::pair<T, T>
mpfr_bin_ieee754_flavor<T>::mid_rad(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    // Same code as the non mixed type version. Only the rad precision is adapted...
    // Necessary to guarantee that [mid(x) - rad(x), mid(x) + rad(x)] encloses x (if computed exactly)

    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x) || mpfr_bin_ieee754_flavor<T_>::is_empty(x) )
        return std::pair<T,T>(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN());

    // call of mixed type version of mid
    std::pair<T,T> mr(mid(x), 0.0);

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;
    typedef typename mpfr_bin_ieee754_flavor<T_MAX>::mpfr_var mpfr_var_max;

    mpfr_var_max::setup();

    // Error free because T_MAX precision >= T precision
    mpfr_var_max m(mr.first, MPFR_RNDN);
    mpfr_var_max xl(x.first, MPFR_RNDD);
    mpfr_var_max xu(x.second, MPFR_RNDU);

    // compute the maximum distance of the midpoint to the lower and the upper bound
    // rad(x) = (xu - xl) / 2 does not guarantee that [mid(x) - rad(x), mid(x) + rad(x)] encloses x (if computed exactly)
    mpfr_sub(xl(), m(), xl(), MPFR_RNDU);
    mpfr_sub(xu(), xu(), m(), MPFR_RNDU);

    mr.second = mpfr_cmp(xl(), xu()) > 0 ? xl.template get<T>(MPFR_RNDU) : xu.template get<T>(MPFR_RNDU);

    if (mr.second == -0.0)
    {
        mr.second = +0.0;
    }
    return mr;
}

// mid_rad ( decorated interval )
template<typename T>
std::pair<T, T>
mpfr_bin_ieee754_flavor<T>::mid_rad(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    // call of bare version
    return !is_valid(x) || is_nai(x)
           ? std::pair<T, T>(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN())
           : mid_rad(x.first);
}


// mid_rad ( decorated interval ) mixed type
template<typename T>
template<typename T_>
std::pair<T, T>
mpfr_bin_ieee754_flavor<T>::mid_rad(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call of bare mixed type version
    return !mpfr_bin_ieee754_flavor<T_>::is_valid(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(x)
           ? std::pair<T, T>(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN())
           : mid_rad(x.first);
}




// wid ( bare interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::wid(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_sub(xl(), xu(), xl(), MPFR_RNDU), MPFR_RNDU);

    T res = xl.template get<T>(MPFR_RNDU);
    return res == -0.0 ? +0.0 : res;
}

// wid ( bare interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::wid(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return std::numeric_limits<T>::quiet_NaN();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding and upward rounding of the result
    return convert_rndu(
               mpfr_bin_ieee754_flavor<T_MAX>::wid(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}

// wid ( decorated interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::wid(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    // call of bare version
    return !is_valid(x) || is_nai(x) ? std::numeric_limits<T>::quiet_NaN() : wid(x.first);
}


// wid ( decorated interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::wid(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call of bare mixed type version
    return !mpfr_bin_ieee754_flavor<T_>::is_valid(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(x)
           ? std::numeric_limits<T>::quiet_NaN()
           : wid(x.first);
}




// mag ( bare interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::mag(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    T xl = std::abs(x.first);
    T xu = std::abs(x.second);

    return xl > xu ? xl : xu;
}


// mag ( bare interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::mag(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return std::numeric_limits<T>::quiet_NaN();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding and upward rounding of the result
    return convert_rndu(
               mpfr_bin_ieee754_flavor<T_MAX>::mag(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}

// mag ( decorated interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::mag(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    // call of bare version
    return !is_valid(x) || is_nai(x) ? std::numeric_limits<T>::quiet_NaN() : mag(x.first);
}


// mag ( decorated interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::mag(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call of bare mixed type version
    return !mpfr_bin_ieee754_flavor<T_>::is_valid(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(x)
           ? std::numeric_limits<T>::quiet_NaN()
           : mag(x.first);
}





// mig ( bare interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::mig(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x) || is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    if (x.first < 0.0 && x.second > 0.0)
        return +0.0;


    T xl = std::abs(x.first);
    T xu = std::abs(x.second);

    return xl < xu ? xl : xu;
}

// mig ( bare interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::mig(mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(x))
        return std::numeric_limits<T>::quiet_NaN();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding and downward rounding of the result
    T res = convert_rndd(
                mpfr_bin_ieee754_flavor<T_MAX>::mig(
                    mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
                )
            );

    // remove signbit (see convert_rndd)
    return res == -0.0 ? +0.0 : res;
}

// mig ( decorated interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::mig(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    // call of bare version
    return !is_valid(x) || is_nai(x) ? std::numeric_limits<T>::quiet_NaN() : mig(x.first);
}


// mig ( decorated interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::mig(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // call of bare mixed type version
    return !mpfr_bin_ieee754_flavor<T_>::is_valid(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(x)
           ? std::numeric_limits<T>::quiet_NaN()
           : mig(x.first);
}



} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_NUM_FUNC_IMPL_HPP
