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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_IO_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_IO_IMPL_HPP

#include <cassert>

namespace p1788
{

namespace flavor
{

namespace infsup
{


// IO
template< typename CharT, typename Traits >
std::basic_ostream<CharT, Traits>& ieee754_flavor<double>::operator_output ( std::basic_ostream<CharT, Traits>& os, ieee754_flavor<double>::representation const& x )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    os << "[" << x.first << "," << x.second << "]";
}

template< typename CharT, typename Traits >
std::basic_istream<CharT, Traits>& ieee754_flavor<double>::operator_input ( std::basic_istream<CharT, Traits>& is, ieee754_flavor<double>::representation& x )
{
// TODO (nehmeier#1#): Check
assert(!"not implemented");

    std::string str;
    std::getline(std::cin, str);

    x = constructor_infsup(str);

    return is;
}


} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_IO_IMPL_HPP
