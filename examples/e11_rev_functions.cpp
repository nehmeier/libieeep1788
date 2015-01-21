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
//                     Details about reverse mode functions
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


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
    // 1) All reverse mode elementary functions are implemented as (global) functions in namespace p1788::infsup
    std::cout << sqr_rev( I<double>(1.0,4.0), I<double>(1.5,2.5) ) << std::endl << std::endl;

    // 1.1) And as static functions of the interval type
    std::cout << I<double>::abs_rev( I<double>(1.0,2.0), I<double>(-5.0,1.1) )  << std::endl << std::endl;

    // 2) All reverse mode elementary functions are implemented for bare and decorated intervals
    std::cout << pown_rev( DI<double>(1.0,2.0), DI<double>(0.0,4.0), 2 ) << std::endl << std::endl;

    // 3) Mixed type functions are static only
    std::cout << I<float>::sin_rev( I<double>(0.1,0.2), I<float>(0.0f,4.0f) )  << std::endl << std::endl;

    // 4) There exist unary and binary reverse mode functions for unary (forward) functions
    std::cout << I<double>::sqr_rev( I<double>(0.1,0.2) )  << std::endl;
    std::cout << I<double>::sqr_rev( I<double>(0.1,0.2),  I<double>(-1.0,0.0) )  << std::endl << std::endl;

    // 4.1) and binary and ternary reverse mode functions for binary (forward) functions
    std::cout << I<double>::mul_rev( I<double>(0.1,0.2), I<double>(1.1,2.2) )  << std::endl;
    std::cout << I<double>::mul_rev( I<double>(0.1,0.2), I<double>(1.1,2.2),  I<double>(-1.0,17.0) )  << std::endl << std::endl;

    // 5) The remaining functions
    std::cout << I<double>::cos_rev( I<double>(0.1,0.2), I<double>(0.0,4.0) )  << std::endl;
    std::cout << I<double>::tan_rev( I<double>(0.1,0.2), I<double>(0.0,4.0) )  << std::endl;
    std::cout << I<double>::cosh_rev( I<double>(1.0,1.0), I<double>(0.0,4.0) )  << std::endl << std::endl;

    return 0;
}

