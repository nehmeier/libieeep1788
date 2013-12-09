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

#ifndef LIBIEEEP1788_P1788_DECORATION_DECORATION_HPP
#define LIBIEEEP1788_P1788_DECORATION_DECORATION_HPP

#include <algorithm>

#include "p1788/util/assert.hpp"

namespace p1788
{

namespace decoration
{

/// \brief Enum describing the 6 different interval decorations
/// see P1788/D7.0 Sect. 10.2 and 10.10
///
enum class decoration
{
    ill = 0,    ///< ill
    trv = 1,    ///< trivial
    def = 2,    ///< defined
    dac = 3,    ///< defined and continuous
    com = 4    ///< common, see P1788/D7.0 Sect. 10.10
};

std::string decoration_map[] = { "ill", "trv", "def", "dac", "com" };



template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os,
    decoration dec)
{
    return os << decoration_map[static_cast<typename std::underlying_type<decoration>::type>(dec)];

}

template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>& operator>>(
    std::basic_istream<CharT, Traits>& is,
    decoration& dec )
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    std::string s;
    s.resize(3);

    is.read(&s[0], 3);

    auto i = std::find(begin(decoration_map), end(decoration_map), s);

    if (i != end(decoration_map))
        dec =  static_cast<decoration>(i - begin(decoration_map));
    else
        dec = decoration::trv;

    return is;
}


} // namespace decoration

} // namespace p1788


#endif // LIBIEEEP1788_P1788_DECORATION_DECORATION_HPP
