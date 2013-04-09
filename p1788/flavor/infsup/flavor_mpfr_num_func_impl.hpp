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
T
mpfr_flavor<T>::inf(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::infinity();

    return method_lower(x);
}

template<typename T>
T
mpfr_flavor<T>::sup(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return -std::numeric_limits<T>::infinity();

    return method_upper(x);
}

template<typename T>
T
mpfr_flavor<T>::mid(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    if (is_entire(x))
        return 0;

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_add(xl(), xl(), xu(), MPFR_RNDN);
    mpfr_div_si(xl(), xl(), 2l, MPFR_RNDN);
    return xl.get(MPFR_RNDN);
}

template<typename T>
T
mpfr_flavor<T>::rad(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_sub(xl(), xu(), xl(), MPFR_RNDU);
    mpfr_div_si(xl(), xl(), 2l, MPFR_RNDU);

    return xl.get(MPFR_RNDU);
}

template<typename T>
std::pair<T, T>
mpfr_flavor<T>::mid_rad(mpfr_flavor<T>::representation const& x)
{
    return std::pair<T,T>(mid(x), rad(x));
}

template<typename T>
T
mpfr_flavor<T>::wid(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_sub(xl(), xu(), xl(), MPFR_RNDU);

    return xl.get(MPFR_RNDU);
}

template<typename T>
T
mpfr_flavor<T>::mag(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    T xl = std::abs(x.first);
    T xu = std::abs(x.second);

    return xl > xu ? xl : xu;
}

template<typename T>
T
mpfr_flavor<T>::mig(mpfr_flavor<T>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    T xl = std::abs(x.first);
    T xu = std::abs(x.second);

    return xl < xu ? xl : xu;
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_NUM_FUNC_IMPL_HPP
