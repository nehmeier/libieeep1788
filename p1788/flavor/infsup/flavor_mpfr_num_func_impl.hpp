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

template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::inf(mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::infinity();

    if (x.first == 0.0)
        return -0.0;

    return x.first;
}

template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::inf(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x)
{
    return inf(x.first);
}


template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::sup(mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return -std::numeric_limits<T>::infinity();

    if (x.second == 0.0)
        return 0.0;

    return x.second;
}

template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::sup(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x)
{
    return sup(x.first);
}


template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::mid(mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    if (is_entire(x))
        return 0.0;

    if (x.first == -std::numeric_limits<T>::infinity())
        return -std::numeric_limits<T>::max();

    if (x.second == std::numeric_limits<T>::infinity())
        return std::numeric_limits<T>::max();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_add(xl(), xl(), xu(), MPFR_RNDN), MPFR_RNDN);
    xl.subnormalize(mpfr_div_si(xl(), xl(), 2l, MPFR_RNDN), MPFR_RNDN);

    T res = xl.template get<T>(MPFR_RNDN);
    return res == -0.0 ? 0.0 : res;
}

template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::mid(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x)
{
    return mid(x.first);
}


template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::rad(mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_sub(xl(), xu(), xl(), MPFR_RNDU), MPFR_RNDU);
    xl.subnormalize(mpfr_div_si(xl(), xl(), 2l, MPFR_RNDU), MPFR_RNDU);

    return xl.template get<T>(MPFR_RNDU);
}

template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::rad(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x)
{
    return rad(x.first);
}


template<typename T, subnormalize SUBNORMALIZE>
std::pair<T, T>
mpfr_flavor<T, SUBNORMALIZE>::mid_rad(mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    return std::pair<T,T>(mid(x), rad(x));
}

template<typename T, subnormalize SUBNORMALIZE>
std::pair<T, T>
mpfr_flavor<T, SUBNORMALIZE>::mid_rad(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x)
{
    return std::pair<T,T>(mid(x), rad(x));
}


template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::wid(mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    xl.subnormalize(mpfr_sub(xl(), xu(), xl(), MPFR_RNDU), MPFR_RNDU);

    return xl.template get<T>(MPFR_RNDU);
}

template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::wid(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x)
{
    return wid(x.first);
}


template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::mag(mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    T xl = std::abs(x.first);
    T xu = std::abs(x.second);

    return xl > xu ? xl : xu;
}

template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::mag(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x)
{
    return mag(x.first);
}


template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::mig(mpfr_flavor<T, SUBNORMALIZE>::representation const& x)
{
    if (is_empty(x))
        return std::numeric_limits<T>::quiet_NaN();

    if (x.first < 0.0 && x.second > 0.0)
        return 0.0;


    T xl = std::abs(x.first);
    T xu = std::abs(x.second);

    return xl < xu ? xl : xu;
}

template<typename T, subnormalize SUBNORMALIZE>
T
mpfr_flavor<T, SUBNORMALIZE>::mig(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x)
{
    return mig(x.first);
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_NUM_FUNC_IMPL_HPP
