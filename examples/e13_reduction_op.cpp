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
//                     Details about reduction operations
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


#include <iostream>

// libieeep1788 main header
#include "p1788/p1788.hpp"


int main()
{
    double a[] = {1.2, 3.1, -17.3};
    double b[] = {1.1, -0.3, 2.1};

    // 1) Reduction operations are implemented as (global) functions in namespace p1788::reduction
    //    using initializer lists for the input
    //    and a value of enum class  p1788::reduction::rnd_mode for the rounding mode
    std::cout << p1788::reduction::sum( {1.2, 3.1, -17.3, 12.1}, p1788::reduction::rnd_mode::to_nearest ) << std::endl;

    // 2) Reduction operations are implemented for iterators (and of course pointers) as well
    std::cout << p1788::reduction::sum_abs( std::begin(a), std::end(a), p1788::reduction::rnd_mode::downward ) << std::endl;
    std::cout << p1788::reduction::sum_sqr( b, b + 3, p1788::reduction::rnd_mode::upward ) << std::endl;

    // 3) The function dot uses two initializer lists
    std::cout << p1788::reduction::dot( {1.2, 2.5, 4.5}, {0.2, 1.0, 0.5}, p1788::reduction::rnd_mode::to_zero ) << std::endl;

    // 3.1) Or two iterators
    //      Note that for the second iterator, like in the STL, only the start is specified and the user is responsible for the correct length
    std::cout << p1788::reduction::dot( std::begin(a), std::end(a), std::begin(b), p1788::reduction::rnd_mode::to_nearest ) << std::endl;

    return 0;
}

