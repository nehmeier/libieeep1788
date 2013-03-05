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

#include "p1788/p1788.hpp"

int main()
{
    typedef p1788::infsup::interval<double, p1788::flavor::infsup::ieee754_flavor>  interval;

    interval a(1,2), b(3,4), c(5,6);

// Elementary functions

    std::cout << "pos: " << +a << std::endl;
    std::cout << "neg: " << -a << std::endl;
    std::cout << "add: " << a + b << std::endl;
    std::cout << "sub: " << a - b << std::endl;
    std::cout << "mul: " << a * b << std::endl;
    std::cout << "div: " << a / b << std::endl;
    std::cout << "inv: " << inv(a) << std::endl;
    std::cout << "sqrt: " << sqrt(a) << std::endl;
    std::cout << "fma: " << fma(a,b,c) << std::endl;
    std::cout << "case: " << interval_case(a,b,c) << std::endl;
    std::cout << "sqr: " << sqr(a) << std::endl;
    std::cout << "pown: " << pown(a, 3) << std::endl;
    std::cout << "pow: " << pow(a,b) << std::endl;
    std::cout << "exp: " << exp(a) << std::endl;
    std::cout << "exp2: " << exp2(a) << std::endl;
    std::cout << "exp10: " << exp10(a) << std::endl;
    std::cout << "log: " << log(a) << std::endl;
    std::cout << "log2: " << log2(a) << std::endl;
    std::cout << "log10: " << log10(a) << std::endl;
    std::cout << "sin: " << sin(a) << std::endl;
    std::cout << "cos: " << cos(a) << std::endl;
    std::cout << "tan: " <<tan(a) << std::endl;
    std::cout << "asin: " << asin(a) << std::endl;
    std::cout << "acos: " << acos(a) << std::endl;
    std::cout << "atan: " << atan(a) << std::endl;
    std::cout << "atan2: " << atan2(b, a) << std::endl;
    std::cout << "sinh: " << sinh(a) << std::endl;
    std::cout << "cosh: " << cosh(a) << std::endl;
    std::cout << "tanh: " << tanh(a) << std::endl;
    std::cout << "asinh: " << asinh(a) << std::endl;
    std::cout << "acosh: " << acosh(a) << std::endl;
    std::cout << "atanh: " << atanh(a) << std::endl;
    std::cout << "sign: " << sign(a) << std::endl;
    std::cout << "ceil: " << ceil(a) << std::endl;
    std::cout << "floor: " << floor(a) << std::endl;
    std::cout << "trunc: " << trunc(a) << std::endl;
    std::cout << "round_ties_to_even: " << round_ties_to_even(a) << std::endl;
    std::cout << "round_ties_to_away: " << round_ties_to_away(a) << std::endl;
    std::cout << "abs: " << abs(a) << std::endl;
    std::cout << "min: " << p1788::infsup::min( {a, b, c}) << std::endl;
    std::cout << "max: " << p1788::infsup::max( {a, b, c}) << std::endl;



    return 0;
}
