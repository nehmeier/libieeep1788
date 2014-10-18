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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_IO_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_IO_IMPL_HPP

#include <iostream>

#include "p1788/util/assert.hpp"


namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{

// IO
template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
template< typename CharT, typename Traits >
std::basic_ostream<CharT, Traits>&
mpfr_bin_ieee754_flavor<T, SUBNORMALIZE, AUTOSETUP>::operator_output(std::basic_ostream<CharT, Traits>& os,
                                mpfr_bin_ieee754_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    if (is_empty(x))
        return os << "[Empty]";

    if (is_entire(x))
        return os << "[Entire]";

    mpfr_var::setup();
    mpfr_var xl(x.first , MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    return os << "[" << xl.get_str(MPFR_RNDD) << "," << xu.get_str(MPFR_RNDU) << "]";
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
template< typename CharT, typename Traits >
std::basic_ostream<CharT, Traits>&
mpfr_bin_ieee754_flavor<T, SUBNORMALIZE, AUTOSETUP>::operator_output(std::basic_ostream<CharT, Traits>& os,
                                mpfr_bin_ieee754_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    operator_output(os, x.first);

    return os << "_" << x.second;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
template< typename CharT, typename Traits >
std::basic_istream<CharT, Traits>&
mpfr_bin_ieee754_flavor<T, SUBNORMALIZE, AUTOSETUP>::operator_input(std::basic_istream<CharT, Traits>& is,
                               mpfr_bin_ieee754_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    std::string str;
    std::getline(std::cin, str);

    x = constructor_infsup(str);

    return is;
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
template< typename CharT, typename Traits >
std::basic_istream<CharT, Traits>&
mpfr_bin_ieee754_flavor<T, SUBNORMALIZE, AUTOSETUP>::operator_input(std::basic_istream<CharT, Traits>& is,
                               mpfr_bin_ieee754_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    std::string str;
    std::getline(std::cin, str);

    x = constructor_infsup_dec(str);

    return is;
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_IO_IMPL_HPP
