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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_NUM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_NUM_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T>
double
mpfr_flavor<T>::inf(mpfr_flavor<T>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return method_lower(x);
}

template<typename T>
double
mpfr_flavor<T>::sup(mpfr_flavor<T>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return method_upper(x);
}

template<typename T>
double
mpfr_flavor<T>::mid(mpfr_flavor<T>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return method_mid(x);
}

template<typename T>
double
mpfr_flavor<T>::wid(mpfr_flavor<T>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return x.second - x.first;
}

template<typename T>
double
mpfr_flavor<T>::rad(mpfr_flavor<T>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return method_rad(x);
}

template<typename T>
double
mpfr_flavor<T>::mag(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return 0.;
}

template<typename T>
double
mpfr_flavor<T>::mig(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return 0.;
}

template<typename T>
std::pair<double, double>
mpfr_flavor<T>::mid_rad(mpfr_flavor<T>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return mpfr_flavor<T>::static_method_entire();
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_NUM_FUNC_IMPL_HPP
