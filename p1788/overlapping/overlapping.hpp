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


#ifndef LIBIEEEP1788_P1788_OVERLAPPING_OVERLAPPING_HPP
#define LIBIEEEP1788_P1788_OVERLAPPING_OVERLAPPING_HPP

#include <iostream>

namespace p1788
{

namespace overlapping
{


// \brief Enum describing the 16 states of the interval overlapping
// see P1788/D7.0 Sect. 9.7.2 Table 6
//
enum class overlapping_state
{
    both_empty,
    first_empty,
    second_empty,
    before,
    meets,
    overlaps,
    starts,
    contained_by,
    finishes,
    equal,
    finished_by,
    contains,
    started_by,
    overlapped_by,
    met_by,
    after
};


template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os, overlapping_state o) {
    return os << static_cast<unsigned int>(o);

}



// TODO overlapping relation, finish implementation, functions ...


} // namespace overlapping

} // namespace p1788



#endif // LIBIEEEP1788_P1788_OVERLAPPING_OVERLAPPING_HPP
