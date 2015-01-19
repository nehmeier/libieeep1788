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


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//
//                           Details about decorations
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


#include <iostream>
#include <sstream>
#include <algorithm>

// libieeep1788 main header
#include "p1788/p1788.hpp"


// Template type alias to define a generic decorated infsup interval with a setbased
// infsup flavor based on mpfr supporting IEEE754 bound types.
template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;


int main()
{
    std::cout << std::boolalpha;    // activate textual output of boolean values



    // 1) There are five different decorations encoded into an enum class decoration in namespace p1788::decoration
    std::cout << p1788::decoration::decoration::ill << std::endl;
    std::cout << p1788::decoration::decoration::trv << std::endl;
    std::cout << p1788::decoration::decoration::def << std::endl;
    std::cout << p1788::decoration::decoration::dac << std::endl;
    std::cout << p1788::decoration::decoration::com << std::endl << std::endl;

    // 1.1) For the sake of convenience it is recommended to use a typedef
    typedef p1788::decoration::decoration DEC;

    // 2) Decorations are ordered:
    //          ill < trv < def < dac < com
    //    and the common comparisons are supported
    std::cout << (DEC::def < DEC::dac) << std::endl;
    std::cout << (DEC::com >= DEC::dac) << std::endl;
    std::cout << std::min(DEC::def, DEC::dac) << std::endl << std::endl;



    // 3) Additionally there are output manipulators

    // 3.1) Lower and upper case
    std::cout << p1788::io::upper_case;
    std::cout << DEC::trv << std::endl;

    std::cout << p1788::io::lower_case;     // default
    std::cout << DEC::dac << std::endl << std::endl;

    // 3.2) Numeric and alphabetic representation
    std::cout << p1788::io::dec_numeric;
    std::cout << DEC::trv << std::endl;

    std::cout << p1788::io::dec_alpha;     // default
    std::cout << DEC::dac << std::endl << std::endl;

    // 4) Input of decorations
    std::stringstream ss(" def   16");

    // 4.1) Input
    DEC d1;
    DEC d2;
    ss >> d1;       // def
    ss >> d2;       // 16 == com

    std::cout << d1 << std::endl;
    std::cout << d2 << std::endl << std::endl;

    return 0;
}

