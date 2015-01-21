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
//                        Details about boolean functions
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
    std::cout << std::boolalpha;    // activate textual output of boolean values



    // 1) All boolean functions are implemented as (global) functions in namespace p1788::infsup
    std::cout << is_empty( I<double>::empty() ) << std::endl;

    // 1.1) And as static functions of the interval type
    std::cout << I<double>::is_empty( I<double>::entire() ) << std::endl;

    // 2) All boolean functions are implemented for bare and decorated intervals
    std::cout << is_entire( DI<double>::entire() ) << std::endl;

    // 2.1) Excepted is is_nai, which is only implemented for decorated intervals
    std::cout << is_nai(DI<double>::nai())  << std::endl;


    // 3) All (binary) comparisons are mixed type functions
    std::cout << is_equal(I<double>::entire(), I<float>::entire())  << std::endl;

    // 4) is_equal is also implemented as an operator
    std::cout <<  ( I<double>::entire() != I<double>::empty() )  << std::endl;
    std::cout <<  ( I<double>::entire() == I<double>::empty() )  << std::endl;


    // 5) The remaining functions
    std::cout << subset(I<double>(2.0,3.0), I<double>(1.0,3.0)) << std::endl;
    std::cout << superset(I<double>(-1.0,3.0), I<float>(2.0f,3.0f)) << std::endl;
    std::cout << less(I<double>(2.0,4.5), I<double>(4.0,5.0)) << std::endl;
    std::cout << greater(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)) << std::endl;
    std::cout << precedes(I<double>(2.0,4.0), I<float>(4.0f,5.0f)) << std::endl;
    std::cout << succeeds(I<double>(-1.0,3.0), I<double>(-5.0,-1.0)) << std::endl;
    std::cout << is_interior(I<double>(2.0,3.0), I<float>(0.0f,5.0f)) << std::endl;
    std::cout << contains_interior(I<double>(-2.0,13.0), I<double>(0.0,5.0)) << std::endl;
    std::cout << strictly_less(I<double>(2.0,3.0), I<float>(4.0f,5.0f)) << std::endl;
    std::cout << strictly_greater(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)) << std::endl;
    std::cout << strictly_precedes(I<double>(2.0,3.0), I<float>(4.0f,5.0f)) << std::endl;
    std::cout << strictly_succeeds(I<double>(-1.0,3.0), I<double>(-5.0,-3.0)) << std::endl;
    std::cout << are_disjoint(DI<double>(-1.0,3.0), DI<float>(-5.0f,0.0f)) << std::endl;


    // 6) And the recommended boolean functions
    std::cout << is_common(I<double>(2.0,3.0)) << std::endl;
    std::cout << is_singleton(DI<double>(-1.0,3.0)) << std::endl;
    std::cout << is_member(-3.0, DI<float>(-5.0f,0.0f)) << std::endl;

    return 0;
}

