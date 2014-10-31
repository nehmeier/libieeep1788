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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_UTIL_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_UTIL_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{

// convert T_ to T with rounding to -oo
template<typename T>
template<typename T_>
T mpfr_bin_ieee754_flavor<T>::convert_rndd(T_ x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    mpfr_var::setup();

    mpfr_var xx(x, MPFR_RNDD);

    T res = xx.template get<T>(MPFR_RNDD);

    return res == 0.0 ? -0.0 : res;     // maps +-0.0 to -0.0
}

// convert T_ to T with rounding to nearest
template<typename T>
template<typename T_>
T mpfr_bin_ieee754_flavor<T>::convert_rndn(T_ x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    mpfr_var::setup();

    mpfr_var xx(x, MPFR_RNDN);

    T res = xx.template get<T>(MPFR_RNDN);

    return res == 0.0 ? +0.0 : res;     // maps +-0.0 to +0.0
}

// convert T_ to T with rounding to +oo
template<typename T>
template<typename T_>
T mpfr_bin_ieee754_flavor<T>::convert_rndu(T_ x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    mpfr_var::setup();

    mpfr_var xx(x, MPFR_RNDU);

    T res = xx.template get<T>(MPFR_RNDU);

    return res == 0.0 ? +0.0 : res;     // maps +-0.0 to +0.0
}


// convert bare interval with bounds T_ to bare interval with bounds T with outward rounding
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::convert_hull(representation_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    return representation(convert_rndd(x.first), convert_rndu(x.second));
}

// convert decorated interval with bounds T_ to decorated interval with bounds T with outward rounding
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::convert_hull(representation_dec_type<T_> const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    representation bare(convert_rndd(x.first.first), convert_rndu(x.first.second));

    if (x.second == p1788::decoration::decoration::com
            && (bare.first == -std::numeric_limits<T>::infinity() || bare.second == std::numeric_limits<T>::infinity()))
    {
        return representation_dec(bare, p1788::decoration::decoration::dac);
    }
    else
    {
        return representation_dec(bare, x.second);
    }
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_UTIL_FUNC_IMPL_HPP
