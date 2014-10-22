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

template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_common(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    //TODO ist das in D8.1 7.2 so gemeint?
    return !is_empty(x)
        && x.first > -std::numeric_limits<T>::infinity()
        && x.second < std::numeric_limits<T>::infinity();
}

template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_common(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    //TODO ist das in D8.1 7.2 so gemeint? oder hier die decoration verwenden?
    return is_common(x.first);
}


template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_singleton(mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    return x.first == x.second;
}

template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_singleton(mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    return is_singleton(x.first);
}


template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_member(T m, mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    return x.first <= m && m <= x.second
        && std::abs(m) != std::numeric_limits<T>::infinity();
}

template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_member(T m, mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    return is_member(m, x.first);
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_REC_BOOL_FUNC_IMPL_HPP
