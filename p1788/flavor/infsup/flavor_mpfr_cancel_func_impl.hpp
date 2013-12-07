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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_CANCEL_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_CANCEL_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::cancel_plus(mpfr_flavor<T, SUBNORMALIZE>::representation const& x,
                            mpfr_flavor<T, SUBNORMALIZE>::representation const& y)
{
    return cancel_minus(x, neg(y));
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::cancel_plus(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x,
                            mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(cancel_plus(x, y), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation
mpfr_flavor<T, SUBNORMALIZE>::cancel_minus(mpfr_flavor<T, SUBNORMALIZE>::representation const& x,
                             mpfr_flavor<T, SUBNORMALIZE>::representation const& y)
{
    if (is_empty(x)) {
        return x;
    } else {
        if (is_empty(y))
            return static_method_entire();

        if (x.first == -std::numeric_limits<T>::infinity()
                || x.second == +std::numeric_limits<T>::infinity()
                || y.first == -std::numeric_limits<T>::infinity()
                || y.second == +std::numeric_limits<T>::infinity())
            return static_method_entire();

        if (wid(x) < wid(y))
            return static_method_entire();

        mpfr_var::setup();

        mpfr_var xl(x.first, MPFR_RNDD);
        mpfr_var xu(x.second, MPFR_RNDU);

        mpfr_var yl(y.first, MPFR_RNDD);
        mpfr_var yu(y.second, MPFR_RNDU);


        mpfr_sub(xl(), xl(), yl(), MPFR_RNDD);
        mpfr_sub(xu(), xu(), yu(), MPFR_RNDU);

        return representation(xl.get(MPFR_RNDD), xu.get(MPFR_RNDU));
    }
}

template<typename T, subnormalize SUBNORMALIZE>
typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec
mpfr_flavor<T, SUBNORMALIZE>::cancel_minus(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x,
                             mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(cancel_minus(x, y), p1788::decoration::decoration::trv);
}


} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_CANCEL_FUNC_IMPL_HPP
