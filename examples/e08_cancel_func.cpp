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
    // 1) All elementary functions are implemented as (global) functions in namespace p1788::infsup
    std::cout << add( I<double>(1.0,2.0), I<double>(3.0,4.0) ) << std::endl;

    // 1.1) And as static functions of the interval type
    std::cout << I<double>::sub( I<double>(1.0,2.0), I<double>(3.0,4.0) )  << std::endl;

    // 1.2) The basic arithmetic operations (+, -, *, /) as well as the unary + and - are implemented as operators as well
    std::cout << I<double>(1.0,2.0) + I<double>(3.0,4.0) << std::endl;
    std::cout << I<double>(1.0,2.0) - I<double>(3.0,4.0) << std::endl;
    std::cout << I<double>(1.0,2.0) * I<double>(3.0,4.0) << std::endl;
    std::cout << I<double>(1.0,2.0) / I<double>(3.0,4.0) << std::endl;

    std::cout << + I<double>(3.0,4.0) << std::endl;
    std::cout << - I<double>(3.0,4.0) << std::endl;

    // 2) All elementary functions are implemented for bare and decorated intervals
    std::cout << mul( DI<double>(1.0,2.0), DI<double>(3.0,4.0) ) << std::endl;

    // 3) Mixed type functions are static only
    std::cout << I<float>::div( I<double>(1.0,2.0), I<float>(3.0f,4.0f) )  << std::endl;

    // 3) The remaining functions
    std::cout << pos( I<double>(1.0,2.0) )  << std::endl;
    std::cout << neg( I<double>(1.0,2.0) )  << std::endl;
    std::cout << recip( I<double>(1.0,2.0) )  << std::endl;
    std::cout << sqr( I<double>(1.0,2.0) )  << std::endl;
    std::cout << sqrt( I<double>(1.0,2.0) )  << std::endl;
    std::cout << fma( I<double>(1.0,2.0), I<double>(3.0,4.0), I<double>(5.0,6.0) )  << std::endl;
    std::cout << pown( I<double>(1.0,2.0), 3 )  << std::endl;
    std::cout << pow( I<double>(1.0,2.0), I<double>(3.0,4.0) )  << std::endl;
    std::cout << exp( I<double>(1.0,2.0) )  << std::endl;
    std::cout << exp2( I<double>(1.0,2.0) )  << std::endl;
    std::cout << exp10( I<double>(1.0,2.0) )  << std::endl;
    std::cout << log( I<double>(1.0,2.0) )  << std::endl;
    std::cout << log2( I<double>(1.0,2.0) )  << std::endl;
    std::cout << log10( I<double>(1.0,2.0) )  << std::endl;
    std::cout << sin( I<double>(1.0,2.0) )  << std::endl;
    std::cout << cos( I<double>(1.0,2.0) )  << std::endl;
    std::cout << tan( I<double>(1.0,2.0) )  << std::endl;
    std::cout << asin( I<double>(1.0,2.0) )  << std::endl;
    std::cout << acos( I<double>(1.0,2.0) )  << std::endl;
    std::cout << atan( I<double>(1.0,2.0) )  << std::endl;
    std::cout << atan2( I<double>(3.0,4.0), I<double>(1.0,2.0) )  << std::endl;
    std::cout << sinh( I<double>(1.0,2.0) )  << std::endl;
    std::cout << cosh( I<double>(1.0,2.0) )  << std::endl;
    std::cout << tanh( I<double>(1.0,2.0) )  << std::endl;
    std::cout << asinh( I<double>(1.0,2.0) )  << std::endl;
    std::cout << acosh( I<double>(1.0,2.0) )  << std::endl;
    std::cout << atanh( I<double>(1.0,2.0) )  << std::endl;
    std::cout << sign( I<double>(0.0,2.0) )  << std::endl;
    std::cout << ceil( I<double>(1.1,2.2) )  << std::endl;
    std::cout << floor( I<double>(1.1,2.2) )  << std::endl;
    std::cout << trunc( I<double>(1.1,2.2) )  << std::endl;
    std::cout << round_ties_to_even( I<double>(1.1,2.5) )  << std::endl;
    std::cout << round_ties_to_away( I<double>(1.1,2.5) )  << std::endl;
    std::cout << abs( I<double>(-1.0,2.0) )  << std::endl;
    std::cout << min( I<double>(1.0,8.0), I<double>(3.0,4.0) )  << std::endl;
    std::cout << max( I<double>(1.0,8.0), I<double>(3.0,4.0) )  << std::endl;

    return 0;
}

