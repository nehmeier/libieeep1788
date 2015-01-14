//
//                              libieeep1788
//
//   An implementation of the preliminary IEEE P1788 standard for
//   interval arithmetic
//
//
//   Copyright 2013 - 2015
//
//   Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
//   Department of Computer Science,
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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_VALIDATION_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_VALIDATION_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{


// Check if x is a valid bare interval representation
template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_valid(representation const& x)
{
    if ((std::isnan(x.first) && std::isnan(x.second))
            || (x.first <= x.second
                &&  x.first != std::numeric_limits<T>::infinity()
                && x.second != -std::numeric_limits<T>::infinity()))
    {
        return true;
    }

    // invalid: signal invalid operand
    return !p1788::exception::signal_invalid_operand();
}

// Check if x is a valid decorated interval representation
template<typename T>
bool mpfr_bin_ieee754_flavor<T>::is_valid(representation_dec const& x)
{
    if ((std::isnan(x.first.first) && std::isnan(x.first.second)
            && (x.second == p1788::decoration::decoration::ill
                || x.second == p1788::decoration::decoration::trv))
            || (x.second != p1788::decoration::decoration::ill
                && (x.first.first <= x.first.second
                    &&  x.first.first != std::numeric_limits<T>::infinity()
                    && x.first.second != -std::numeric_limits<T>::infinity()
                    && (x.second != p1788::decoration::decoration::com
                        || (x.first.first != -std::numeric_limits<T>::infinity()
                            && x.first.second != std::numeric_limits<T>::infinity()))
                   )
               )
       )
    {
        return true;
    }

    // invalid: signal invalid operand
    return !p1788::exception::signal_invalid_operand();
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_VALIDATION_FUNC_IMPL_HPP
