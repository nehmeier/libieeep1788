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

#ifndef LIBIEEEP1788_P1788_UTIL_IO_HPP
#define LIBIEEEP1788_P1788_UTIL_IO_HPP

#include <iostream>
#include <cctype>
#include <ctype.h>
#include <string>
#include <algorithm>

namespace p1788
{

namespace util
{

// Remove whitespace character from input stream
template<typename CharT, typename Traits>
inline void remove_ws(std::basic_istream<CharT, Traits>& is)
{
    while (is && std::isspace(is.peek()))
        is.get();

}


// transform all ASCII characters to lowercase
inline void ascii_to_lower(std::string& s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](int const c)
    {
        return (c >= 0 && c < 128 ) ? std::tolower(c) : c;
    }
                  );
}

} // namespace util

} // namespace p1788

#endif // LIBIEEEP1788_P1788_UTIL_IO_HPP
