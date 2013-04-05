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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_REC_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_REC_ELEM_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

ieee754_flavor<double>::representation
ieee754_flavor<double>::rootn(ieee754_flavor<double>::representation const&, int)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::expm1(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::exp2m1(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::exp10m1(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::logp1(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::log2p1(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::log10p1(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::compoundm1(ieee754_flavor<double>::representation const&,
                                   ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::hypot(ieee754_flavor<double>::representation const&,
                              ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::r_sqrt(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::sin_pi(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::cos_pi(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::tan_pi(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::asin_pi(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::acos_pi(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::atan_pi(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::atan2_pi(ieee754_flavor<double>::representation const&,
                                 ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_REC_ELEM_FUNC_IMPL_HPP
