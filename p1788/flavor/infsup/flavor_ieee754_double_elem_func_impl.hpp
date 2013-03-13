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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_ELEM_FUNC_IMPL_HPP

#include <cassert>

namespace p1788
{

namespace flavor
{

namespace infsup
{

ieee754_flavor<double>::representation
ieee754_flavor<double>::pos(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::neg(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::add(ieee754_flavor<double>::representation const& x,
                            ieee754_flavor<double>::representation const& y)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return representation(x.first + y.first, x.second + y.second);
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::sub(ieee754_flavor<double>::representation const& x,
                            ieee754_flavor<double>::representation const& y)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::mul(ieee754_flavor<double>::representation const& x,
                            ieee754_flavor<double>::representation const& y)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::div(ieee754_flavor<double>::representation const& x,
                            ieee754_flavor<double>::representation const& y)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::inv(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::sqrt(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::fma(ieee754_flavor<double>::representation const& x,
                            ieee754_flavor<double>::representation const& y,
                            ieee754_flavor<double>::representation const& z)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::interval_case(ieee754_flavor<double>::representation const& c,
                                      ieee754_flavor<double>::representation const& g,
                                      ieee754_flavor<double>::representation const& h)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::sqr(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::pown(ieee754_flavor<double>::representation const& x,
                             int p)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::pow(ieee754_flavor<double>::representation const& x,
                            ieee754_flavor<double>::representation const& y)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::exp(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::exp2(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::exp10(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::log(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::log2(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::log10(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::sin(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::cos(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::tan(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::asin(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::acos(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::atan(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::atan2(ieee754_flavor<double>::representation const& y,
                              ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::sinh(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::cosh(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::tanh(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::asinh(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::acosh(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::atanh(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::sign(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::ceil(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::floor(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::trunc(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::round_ties_to_even(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::round_ties_to_away(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::abs(ieee754_flavor<double>::representation const& x)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

template<typename ConstRandomAccessIterator>
ieee754_flavor<double>::representation
ieee754_flavor<double>::min(ConstRandomAccessIterator first, ConstRandomAccessIterator last)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}

template<typename ConstRandomAccessIterator>
ieee754_flavor<double>::representation
ieee754_flavor<double>::max(ConstRandomAccessIterator first,
                            ConstRandomAccessIterator last)
{
// TODO (nehmeier#1#): Implement!
    assert(!"not implemented");

    return ieee754_flavor<double>::static_method_entire();
}


} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_ELEM_FUNC_IMPL_HPP
