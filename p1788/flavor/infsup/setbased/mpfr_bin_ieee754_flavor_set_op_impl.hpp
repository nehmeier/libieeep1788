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

template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::intersect(mpfr_bin_ieee754_flavor<T>::representation const& x,
                          mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (are_disjoint(x, y))
        return empty();
    else
        return representation(std::max(x.first, y.first),
                              std::min(x.second, y.second));
}


template<typename T>
template<typename T1_, typename T2_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::intersect(mpfr_bin_ieee754_flavor<T>::representation_type<T1_> const& x,
                          mpfr_bin_ieee754_flavor<T>::representation_type<T2_> const& y)
{
        static_assert(std::numeric_limits<T1_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
        static_assert(std::numeric_limits<T2_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

        typedef typename p1788::util::max_precision_type<T,T1_,T2_>::type T_MAX;

        return convert_hull(
                   mpfr_bin_ieee754_flavor<T_MAX>::intersect(
                       mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(x),
                       mpfr_bin_ieee754_flavor<T_MAX>::convert_hull(y)
                   )
               );
}


template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::intersect(mpfr_bin_ieee754_flavor<T>::representation_dec const&,
                          mpfr_bin_ieee754_flavor<T>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_bin_ieee754_flavor<T>::entire_dec();
}


template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::hull(mpfr_bin_ieee754_flavor<T>::representation const& x,
                     mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (is_empty(x))
        return y;
    else if (is_empty(y))
        return x;
    else
        return representation(std::min(x.first, y.first),
                              std::max(x.second, y.second));
}

template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::hull(mpfr_bin_ieee754_flavor<T>::representation_dec const&,
                     mpfr_bin_ieee754_flavor<T>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_bin_ieee754_flavor<T>::entire_dec();
}


//TODO hull(s)   P1788/8.1 12.8.1


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_SET_OP_IMPL_HPP
