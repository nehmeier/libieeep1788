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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_FLOAT_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_FLOAT_ELEM_FUNC_IMPL_HPP

#include "p1788/util/assert.hpp"

namespace p1788
{

namespace flavor
{

namespace infsup
{

ieee754_flavor<float>::representation
ieee754_flavor<float>::pos(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::neg(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::add(ieee754_flavor<float>::representation const&,
                           ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::sub(ieee754_flavor<float>::representation const&,
                           ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::mul(ieee754_flavor<float>::representation const&,
                           ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::div(ieee754_flavor<float>::representation const&,
                           ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::inv(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::sqrt(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::fma(ieee754_flavor<float>::representation const&,
                           ieee754_flavor<float>::representation const&,
                           ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::interval_case(ieee754_flavor<float>::representation const&,
                                     ieee754_flavor<float>::representation const&,
                                     ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::sqr(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::pown(ieee754_flavor<float>::representation const&,
                            int)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::pow(ieee754_flavor<float>::representation const&,
                           ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::exp(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::exp2(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::exp10(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::log(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::log2(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::log10(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::sin(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::cos(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::tan(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::asin(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::acos(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::atan(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::atan2(ieee754_flavor<float>::representation const&,
                             ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::sinh(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::cosh(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;
    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::tanh(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::asinh(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::acosh(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::atanh(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::sign(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::ceil(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::floor(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::trunc(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::round_ties_to_even(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::round_ties_to_away(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

ieee754_flavor<float>::representation
ieee754_flavor<float>::abs(ieee754_flavor<float>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

template<typename ConstRandomAccessIterator>
ieee754_flavor<float>::representation
ieee754_flavor<float>::min(ConstRandomAccessIterator, ConstRandomAccessIterator)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}

template<typename ConstRandomAccessIterator>
ieee754_flavor<float>::representation
ieee754_flavor<float>::max(ConstRandomAccessIterator,
                           ConstRandomAccessIterator)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<float>::static_method_entire();
}


} // namespace infsup

} // namespace flavor

} // namespace p1788

#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_FLOAT_ELEM_FUNC_IMPL_HPP
