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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REC_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REC_ELEM_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::rootn(mpfr_flavor<T>::representation const&, int)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::expm1(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::exp2m1(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::exp10m1(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::logp1(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::log2p1(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::log10p1(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::compoundm1(mpfr_flavor<T>::representation const&,
                           mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::hypot(mpfr_flavor<T>::representation const&,
                      mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::r_sqrt(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::sin_pi(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::cos_pi(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::tan_pi(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::asin_pi(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::acos_pi(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::atan_pi(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::atan2_pi(mpfr_flavor<T>::representation const&,
                         mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REC_ELEM_FUNC_IMPL_HPP
