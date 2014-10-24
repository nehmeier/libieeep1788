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

    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

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
    return is_nai(x) ? std::numeric_limits<T>::quiet_NaN() : inf(x.first);
}

// inf ( decorated interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::inf(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    return convert_rndd(
               mpfr_bin_ieee754_flavor<T_MAX>::inf(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}

// sup ( bare interval )
template<typename T>
T
mpfr_bin_ieee754_flavor<T>::sup(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
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

    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

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
    return is_nai(x) ? std::numeric_limits<T>::quiet_NaN() : sup(x.first);
}

// sup ( decorated interval ) mixed type
template<typename T>
template<typename T_>
T
mpfr_bin_ieee754_flavor<T>::sup(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    typedef typename p1788::util::max_precision_type<T,T_>::type T_MAX;

    return convert_rndu(
               mpfr_bin_ieee754_flavor<T_MAX>::sup(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x)
               )
           );
}


template<typename T>
T
mpfr_bin_ieee754_flavor<T>::mid(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (is_empty(x))
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

template<typename T>
T
mpfr_bin_ieee754_flavor<T>::mid(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    return mid(x.first);
}


template<typename T>
T
mpfr_bin_ieee754_flavor<T>::rad(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    T dm = mid(x);

    mpfr_var::setup();

    mpfr_var m(dm, MPFR_RNDN);

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_sub(xl(), m(), xl(), MPFR_RNDU);
    mpfr_sub(xu(), xu(), m(), MPFR_RNDU);

    T res = mpfr_cmp(xl(), xu()) > 0 ? xl.template get<T>(MPFR_RNDU) : xu.template get<T>(MPFR_RNDU);
    return res == -0.0 ? +0.0 : res;
}

template<typename T>
T
mpfr_bin_ieee754_flavor<T>::rad(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    return rad(x.first);
}


template<typename T>
std::pair<T, T>
mpfr_bin_ieee754_flavor<T>::mid_rad(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    return std::pair<T,T>(mid(x), rad(x));
}

template<typename T>
std::pair<T, T>
mpfr_bin_ieee754_flavor<T>::mid_rad(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    return std::pair<T,T>(mid(x), rad(x));
}


template<typename T>
T
mpfr_bin_ieee754_flavor<T>::wid(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_sub(xl(), xu(), xl(), MPFR_RNDU), MPFR_RNDU);

    T res = xl.template get<T>(MPFR_RNDU);
    return res == -0.0 ? +0.0 : res;
}

template<typename T>
T
mpfr_bin_ieee754_flavor<T>::wid(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    return wid(x.first);
}


template<typename T>
T
mpfr_bin_ieee754_flavor<T>::mag(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    T xl = std::abs(x.first);
    T xu = std::abs(x.second);

    return xl > xu ? xl : xu;
}

template<typename T>
T
mpfr_bin_ieee754_flavor<T>::mag(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    return mag(x.first);
}


template<typename T>
T
mpfr_bin_ieee754_flavor<T>::mig(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    if (x.first < 0.0 && x.second > 0.0)
        return +0.0;


    T xl = std::abs(x.first);
    T xu = std::abs(x.second);

    return xl < xu ? xl : xu;
}

template<typename T>
T
mpfr_bin_ieee754_flavor<T>::mig(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    return mig(x.first);
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_NUM_FUNC_IMPL_HPP
