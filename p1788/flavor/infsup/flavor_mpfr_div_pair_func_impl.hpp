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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_DIV_PAIR_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_DIV_PAIR_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T, subnormalize SUBNORMALIZE>
std::pair<typename mpfr_flavor<T, SUBNORMALIZE>::representation, typename mpfr_flavor<T, SUBNORMALIZE>::representation>
mpfr_flavor<T, SUBNORMALIZE>::div_to_pair(mpfr_flavor<T, SUBNORMALIZE>::representation const& x,
                    mpfr_flavor<T, SUBNORMALIZE>::representation const& y)
{
    if (y.first < 0.0 && y.second > 0.0)
        return std::pair<typename mpfr_flavor<T, SUBNORMALIZE>::representation, typename mpfr_flavor<T, SUBNORMALIZE>::representation>
            (div(x, representation(y.first, 0.0)), div(x, representation(0.0, y.second)));

        return std::pair<typename mpfr_flavor<T, SUBNORMALIZE>::representation, typename mpfr_flavor<T, SUBNORMALIZE>::representation>
            (div(x, y), static_method_empty());
}

template<typename T, subnormalize SUBNORMALIZE>
std::pair<typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec, typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec>
mpfr_flavor<T, SUBNORMALIZE>::div_to_pair(mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& x,
                    mpfr_flavor<T, SUBNORMALIZE>::representation_dec const& y)
{
    if (y.first.first < 0.0 && y.first.second > 0.0)
        return std::pair<typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec, typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec>
            (div(x, representation_dec(representation(y.first.first, 0.0), y.second)),
              div(x, representation_dec(representation(0.0, y.first.second), y.second)));

        return std::pair<typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec, typename mpfr_flavor<T, SUBNORMALIZE>::representation_dec>
            (div(x, y), static_method_empty());
}


} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_DIV_PAIR_FUNC_IMPL_HPP
