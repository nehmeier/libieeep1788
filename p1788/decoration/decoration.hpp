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

namespace p1788
{

/// \brief Enum describing the 6 different interval decorations
/// see P1788/D7.0 Sect. 10.2 and 10.10
///
enum class decoration
{
    com,    ///< common, see P1788/D7.0 Sect. 10.10
    dac,    ///< defined and continuous
    def,    ///< defined
    trv,    ///< trivial
    emp,    ///< empty
    ill     ///< ill
};

// TODO decorations, finish implementation, functions ...

} // namespace p1788


#endif // LIBIEEEP1788_P1788_DECORATION_DECORATION_HPP
