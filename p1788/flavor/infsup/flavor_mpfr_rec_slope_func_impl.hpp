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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REC_SLOPE_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REC_SLOPE_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::exp_slope1(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::exp_slope1(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::exp_slope2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::exp_slope2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::log_slope1(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::log_slope1(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::log_slope2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::log_slope2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::cos_slope2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::cos_slope2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sin_slope3(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sin_slope3(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::asin_slope3(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::asin_slope3(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::atan_slope3(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::atan_slope3(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::cosh_slope2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::cosh_slope2(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire_dec();
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sinh_slope3(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::sinh_slope3(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire_dec();
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_REC_SLOPE_FUNC_IMPL_HPP
