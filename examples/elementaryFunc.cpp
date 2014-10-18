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

//template<typename T>
//using interval = p1788::infsup::interval<T, p1788::flavor::infsup::ieee754_flavor>;

template<typename T>
using F = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T, p1788::flavor::infsup::setbased::subnormalize::yes, p1788::flavor::infsup::setbased::auto_setup::yes>;

template<typename T>
using I = p1788::infsup::interval<T, F>;

using namespace p1788::infsup;

int main()
{
    I<double> d_a(-1.0,2.0), d_b(3.0,4.0), d_c(5.0,6.0);
    I<float> f_a(1.0f,2.0f), f_b(3.0f,4.0f), f_c(5.0f,6.0f);


// Elementary functions

    std::cout << "pos: " << pos(d_a) << std::endl;
    std::cout << "+x: " << +d_a << std::endl;

    std::cout << "neg: " << neg(d_a) << std::endl;
    std::cout << "-x: " << -d_a << std::endl;

    std::cout << "add: " << add(d_a, d_b) << std::endl;
    std::cout << "x + y: " << d_a + d_b << std::endl;
//    std::cout << "add mt: " << add<I<float>>(d_a, f_b) << std::endl << std::endl;

    std::cout << "sub: " << sub(d_a, d_b) << std::endl;
    std::cout << "x - y: " << d_a - d_b << std::endl;
//    std::cout << "sub mt: " << sub<I<float>>(d_a, f_b) << std::endl << std::endl;

    std::cout << "mul: " << mul(d_a, d_b) << std::endl;
    std::cout << "x * y: " << d_a * d_b << std::endl;
//    std::cout << "mul mt: " << mul<I<float>>(d_a, f_b) << std::endl << std::endl;

    std::cout << "div: " << div(d_a, d_b) << std::endl;
    std::cout << "x / y: " << d_a / d_b << std::endl;
//    std::cout << "div mt: " << div<I<float>>(d_a, f_b) << std::endl << std::endl;

    std::cout << "recip: " << recip(d_a) << std::endl;
//    std::cout << "recip mt: " << recip<I<float>>(d_a) << std::endl << std::endl;

    std::cout << "sqr: " << sqr(d_a) << std::endl;
//    std::cout << "sqr mt: " << sqr<I<float>>(d_a) << std::endl << std::endl;

    std::cout << "sqrt: " << sqrt(d_a) << std::endl;
//    std::cout << "sqrt mt: " << sqrt<I<float>>(d_a) << std::endl << std::endl;

    std::cout << "fma: " << fma(d_a, d_b, d_c) << std::endl;
//    std::cout << "fma mt: " << fma<I<float>>(d_a, f_b, d_c) << std::endl << std::endl;

//    std::cout << "case: " << interval_case(d_a, d_b, d_c) << std::endl;

    std::cout << "pown: " << pown(d_a, 3) << std::endl;

    std::cout << "pow: " << pow(d_a, d_b) << std::endl;

    std::cout << "exp: " << exp(d_a) << std::endl;

    std::cout << "exp2: " << exp2(d_a) << std::endl;

    std::cout << "exp10: " << exp10(d_a) << std::endl;

    std::cout << "log: " << log(d_a) << std::endl;

    std::cout << "log2: " << log2(d_a) << std::endl;

    std::cout << "log10: " << log10(d_a) << std::endl;

    std::cout << "sin: " << sin(d_a) << std::endl;

    std::cout << "cos: " << cos(d_a) << std::endl;

    std::cout << "tan: " << tan(d_a) << std::endl;

    std::cout << "asin: " << asin(d_a) << std::endl;

    std::cout << "acos: " << acos(d_a) << std::endl;

    std::cout << "atan: " << atan(d_a) << std::endl;

    std::cout << "atan2: " << atan2(d_b, d_a) << std::endl;

    std::cout << "sinh: " << sinh(d_a) << std::endl;

    std::cout << "cosh: " << cosh(d_a) << std::endl;

    std::cout << "tanh: " << tanh(d_a) << std::endl;

    std::cout << "asinh: " << asinh(d_a) << std::endl;

    std::cout << "acosh: " << acosh(d_a) << std::endl;

    std::cout << "atanh: " << atanh(d_a) << std::endl;

    std::cout << "sign: " << sign(d_a) << std::endl;

    std::cout << "ceil: " << ceil(d_a) << std::endl;

    std::cout << "floor: " << floor(d_a) << std::endl;

    std::cout << "trunc: " << trunc(d_a) << std::endl;

    std::cout << "round_ties_to_even: " << round_ties_to_even(d_a) << std::endl;

    std::cout << "round_ties_to_away: " << round_ties_to_away(d_a) << std::endl;

    std::cout << "abs: " << abs(d_a) << std::endl;

    std::cout << "min: " << min( d_a, d_b) << std::endl;

    std::cout << "max: " << max( d_a, d_b) << std::endl;

    std::cout << "sqr_rev: " << sqr_rev( d_a) << std::endl;

    return 0;
}

