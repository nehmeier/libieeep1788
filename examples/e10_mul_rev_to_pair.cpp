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
//                     Details about two-output division
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
    // 1) Two-output division is implemented as a (global) function in namespace p1788::infsup
    // Note that it is a reverse multiplication which means that mul_rev_to_pair(b,c) corresponds to c / b

    // result is returned as a std::pair
    std::pair<I<double>,I<double>> res = mul_rev_to_pair( I<double>(-1.0,2.0), I<double>(3.0,4.0) );
    std::cout << res.first << std::endl;
    std::cout << res.second << std::endl << std::endl;

    // 1.1) And as a static function of the interval type
    auto res2 = DI<double>::mul_rev_to_pair( DI<double>(0.0,2.0), DI<double>(3.0,4.0) );
    std::cout << res2.first << std::endl;
    std::cout << res2.second << std::endl;

    return 0;
}

