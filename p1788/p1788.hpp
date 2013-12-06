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

#ifndef LIBIEEEP1788_P1788_P1788_HPP
#define LIBIEEEP1788_P1788_P1788_HPP


///
/// \brief This header includes all functionality provided by libieeep1788.
///

#include "p1788/version.hpp"


// Decorations, see P1788/D7.0 Sect. 10.2 and 10.10
#include "p1788/decoration/decoration.hpp"

// Interval overlapping, see P1788/D7.0 Sect. 9.7.2 Table 6
#include "p1788/overlapping/overlapping.hpp"


#include "p1788/infsup/interval.hpp"
#include "p1788/infsup/decorated_interval.hpp"
#include "p1788/infsup/compressed_interval.hpp"



//#include "p1788/flavor/infsup/flavor_ieee754.hpp"
#include "p1788/flavor/infsup/flavor_mpfr.hpp"

//TODO Dot product and Complete format, see P1788/D7.0 Sect. 9.6.11 and Sect. 11.11.11
//TODO interval type conversion, see P1788/D7.0 Sect. 11.8.3


#endif // LIBIEEEP1788_P1788_P1788_HPP
