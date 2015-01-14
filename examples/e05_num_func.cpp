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

#include <iostream>

// libieeep1788 main header
#include "p1788/p1788.hpp"


// Template type alias to define a generic bare infsup interval with a setbased
// infsup flavor based on mpfr supporting IEEE754 bound types.
template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

// and the same for decorated intervals
template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;


int main()
{
    // 1) All numeric functions are implemented as (global) functions in namespace p1788::infsup
    std::cout << inf( I<double>(1.0,2.0) ) << std::endl;

    // 1.1) And as static functions of the interval type
    std::cout << I<double>::sup( I<double>(1.0,2.0) ) << std::endl;

    // 2) All numeric functions are implemented for bare and decorated intervals
    std::cout << mid( DI<double>(1.1,2.3) ) << std::endl;

    // 3) Mixed type functions are static only
    std::cout << I<float>::rad( I<double>(1.1,2.3) )  << std::endl;

    // The remaining functions
    std::cout << wid( I<double>(1.0,2.0) ) << std::endl;
    std::cout << mag( I<double>(1.0,2.0) ) << std::endl;
    std::cout << mig( I<double>(1.0,2.0) ) << std::endl;


    // midpoint and radius are provided as a combined function returning a pair (mid, rad)
    std::cout << mid_rad(I<double>(2.0,3.0)).first << std::endl;
    std::cout << mid_rad(I<double>(2.0,3.0)).second << std::endl;

    return 0;
}

