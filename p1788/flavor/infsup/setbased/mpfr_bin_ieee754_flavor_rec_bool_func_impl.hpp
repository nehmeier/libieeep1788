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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_REC_BOOL_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_REC_BOOL_FUNC_IMPL_HPP


namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{

// is_common ( bare interval )
template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_common(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return false;

    return !is_empty(x)
           && x.first > -std::numeric_limits<T>::infinity()
           && x.second < std::numeric_limits<T>::infinity();
}

// is_common (decorated interval)
template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_common(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x))
        return false;

    // call bare version
    return is_common(x.first);
}

// is_singleton ( bare interval )
template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_singleton(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return false;

    return x.first == x.second;
}

// is_singleton (decorated interval)
template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_singleton(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x))
        return false;

    // call bare version
    return is_singleton(x.first);
}

// is_member (bare interval)
template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_member(T m, mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return false;

    // call bare mixed type
    return is_member<T>(m, x);
}

// is_member (decorated interval)
template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_member(T m, mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x))
        return false;

    // call bare mixed type version if not NaI
    return !is_nai(x) && is_member<T>(m, x.first);
}

// is_member (bare interval) mixed type
template<typename T>
template<typename T_>
bool mpfr_bin_ieee754_flavor<T>::is_member(T_ m, mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x))
        return false;

    return x.first <= m && m <= x.second
           && !std::isinf(m);
}

// is_member (decorated interval)  mixed type
template<typename T>
template<typename T_>
bool mpfr_bin_ieee754_flavor<T>::is_member(T_ m, mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!is_valid(x))
        return false;

    // call bare mixed type version if not NaI
    return !is_nai(x) && is_member(m, x.first);
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_REC_BOOL_FUNC_IMPL_HPP
