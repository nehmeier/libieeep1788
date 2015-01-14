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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_SET_OP_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_SET_OP_IMPL_HPP


namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{

// intersect ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::intersect(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                      mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y))
        return empty();

    if (are_disjoint(x, y))
        return empty();
    else
        return representation(std::max(x.first, y.first),
                              std::min(x.second, y.second));
}

// intersect ( bare interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::intersect(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& x,
                                      mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !is_valid(y))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::intersect(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}

// intersect ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::intersect(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                      mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y))
        return nai();

    return is_nai(x) || is_nai(y) ? nai() : representation_dec(intersect(x.first, y.first),
            p1788::decoration::decoration::trv);
}

// intersect ( decorated interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::intersect(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& x,
                                      mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !is_valid(y))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::intersect(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}

// hull ( bare interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::hull(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                 mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (!is_valid(x) || !is_valid(y))
        return empty();

    if (is_empty(x))
        return y;
    else if (is_empty(y))
        return x;
    else
        return representation(std::min(x.first, y.first),
                              std::max(x.second, y.second));
}

// hull ( bare interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::hull(mpfr_bin_ieee754_flavor<T>::representation_type<T1> const& x,
                                 mpfr_bin_ieee754_flavor<T>::representation_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !is_valid(y))
        return empty();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::hull(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}

// hull ( decorated interval )
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::hull(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                 mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    if (!is_valid(x) || !is_valid(y))
        return nai();

    return is_nai(x) || is_nai(y) ? nai() : representation_dec(hull(x.first, y.first),
            p1788::decoration::decoration::trv);
}

// hull ( decorated interval ) mixed type
template<typename T>
template<typename T1, typename T2>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::hull(mpfr_bin_ieee754_flavor<T>::representation_dec_type<T1> const& x,
                                 mpfr_bin_ieee754_flavor<T>::representation_dec_type<T2> const& y)
{
    static_assert(std::numeric_limits<T1>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<T2>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x) || !is_valid(y))
        return nai();

    // determine max. precision
    typedef typename p1788::util::max_precision_type<T,T1,T2>::type T_MAX;

    // 1.) convert inputs to max precision; 2.) compute result in max precision; 3.) convert result to desired precision
    // Error free for floating point inf-sup intervals due to  outward rounding
    return convert_hull(
               mpfr_bin_ieee754_flavor<T_MAX>::hull(
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                   mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
               )
           );
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_SET_OP_IMPL_HPP
