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

// constant for the value +oo
const double INF = std::numeric_limits<double>::infinity();

int main()
{
    // 1) Default constructors create empty intervals
    std::cout << I<double>() << std::endl;
    std::cout << DI<double>() << std::endl << std::endl;

    // 1.1) The same could be achieved by static functions
    std::cout << I<double>::empty() << std::endl;
    std::cout << DI<double>::empty() << std::endl << std::endl;

    // 2) There are also static functions to create entire intervals
    std::cout << I<double>::entire() << std::endl;
    std::cout << DI<double>::entire() << std::endl << std::endl;

    // 2.1) The same can be achieved by using the constructor with two parameters
    std::cout << I<double>(-INF, INF) << std::endl;
    std::cout << DI<double>(-INF, INF) << std::endl << std::endl;

    // 3) The parameter constructor can be used to create all kinds of intervals
    std::cout << I<double>(-3.0, INF) << std::endl;
    std::cout << DI<double>(5.0, 27.7) << std::endl << std::endl;

    // 3.1) For decorated intervals it is also possible to specify a decoration
    std::cout << DI<double>(5.0, 27.7, p1788::decoration::decoration::def) << std::endl << std::endl;

    // 3.2) But take care: the parameters are number literals which are computed and rounded by the compiler
    //      Hence the following interval is not an enclosure of 1/10
    //      This is also a reasopn why a constructor with one floating point parameter is not supported
    std::cout << I<double>(0.1, 0.1) << std::endl << std::endl;

    // 4) To ensure enclosure you can use the string constructor
    //    Notice the difference in the output compared to the constructor above
    std::cout << I<double>("[0.1, 0.1]") << std::endl;
    std::cout << I<double>("[0.1, 1/10]") << std::endl;
    std::cout << DI<double>("[0.1]_trv") << std::endl;
    std::cout << I<double>("[1/10]_dac") << std::endl;
    std::cout << DI<double>("0.1000000?") << std::endl << std::endl;

    // 5) Additionally it is possible to convert interval types
    I<double> i("[0.1, 0.1]");
    DI<double> di("[0.1, 1.1]_dac");

    std::cout << p1788::io::precision(10);  // increase the precision of the output to see a difference

    // 5.1) Different bound types
    std::cout << i << std::endl;
    std::cout << I<float>( i ) << std::endl;
    std::cout << di << std::endl;
    std::cout << DI<float>( di ) << std::endl << std::endl;

    // 5.2) Bare interval <-> decorated interval
    std::cout << I<double>( di ) << std::endl;
    std::cout << I<float>( di ) << std::endl;
    std::cout << DI<double>( i ) << std::endl;
    std::cout << DI<float>( i ) << std::endl << std::endl;

    // 5.4) And the same for casts
    std::cout << static_cast< I<float> >( i ) << std::endl;
    std::cout << static_cast< I<double> >( di ) << std::endl;
    std::cout << static_cast< DI<double> >( i ) << std::endl << std::endl;

    // 6) Set a decoration
    std::cout << DI<double>( i, p1788::decoration::decoration::def ) << std::endl;
    std::cout << DI<float>( i, p1788::decoration::decoration::trv ) << std::endl << std::endl;

    // 6.1) And get a decoration
    std::cout << decoration( di ) << std::endl;     // function
    std::cout << DI<double>::decoration( di ) << std::endl << std::endl;    // static

    // 7) In case of invalid input an empty interval (bare interval constructor)
    //    or a NaI (decorated interval constructor) will be created
    std::cout << I<double>(5.0,0.0) << std::endl;
    std::cout << I<double>("foo") << std::endl;
    std::cout << DI<double>("[1.0,inf]_com") << std::endl << std::endl;

    // 7.1) and of course
    std::cout << DI<double>::nai() << std::endl;

    return 0;
}

