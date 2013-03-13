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

#ifndef LIBIEEEP1788_P1788_UTIL_MIXED_TYPE_TRAITS_HPP
#define LIBIEEEP1788_P1788_UTIL_MIXED_TYPE_TRAITS_HPP

#include <type_traits>

#include "p1788/infsup/interval.hpp"

namespace p1788
{

namespace util
{

//------------------------------------------------------------------------------
//  Traits type_precision_order and max_precision_type
//------------------------------------------------------------------------------



/// \brief Trait to determine the precision oder of the type T
///
/// The order should be realized by an enum class for each group of coherent
/// types, e.g. IEEE 754 binary floating point {float, double, long double}.
/// Hence, only types of the same group are comparable.
///
/// \param T type
/// \return field value contains the order
///
///
template<typename T>
class type_precision_order
    : public std::integral_constant<int, 0>
{
    static_assert(!std::is_same<T,T>::value,
                  "Type is not supported!");
};


template<typename... Types> class max_precision_type
{
    static_assert(sizeof...(Types) > 0,
                  "max_precision_type for an empty argument list!");
};


template<typename First, typename Second, typename... Tail>
class max_precision_type<First, Second, Tail...>
{
public:
    static_assert(std::is_same<typename type_precision_order<First>::value_type,
                  typename type_precision_order<Second>::value_type>::value,
                  "Different type groups!");

    typedef typename max_precision_type<
    typename std::conditional<
    (type_precision_order<First>::value > type_precision_order<Second>::value),
    First,
    Second
    >::type,
    Tail...
    >::type type;
};

template<typename Type>
class max_precision_type<Type>
{
public:
    typedef Type type;
};





//------------------------------------------------------------------------------
//  IEEE 754 Binary specialization for type_precision_order
//------------------------------------------------------------------------------

enum class ieee754_binary_precision_order : unsigned int
{
    float_type,
    double_type,
    long_double_type
};


template<>
class type_precision_order<float>
    : public std::integral_constant<ieee754_binary_precision_order,
      ieee754_binary_precision_order::float_type>
{ };

template<>
class type_precision_order<double>
    : public std::integral_constant<ieee754_binary_precision_order,
      ieee754_binary_precision_order::double_type>
{ };

template<>
class type_precision_order<long double>
    : public std::integral_constant<ieee754_binary_precision_order,
      ieee754_binary_precision_order::long_double_type>
{ };


} // namespace util

} // namespace p1788

#endif // LIBIEEEP1788_P1788_UTIL_MIXED_TYPE_TRAITS_HPP
