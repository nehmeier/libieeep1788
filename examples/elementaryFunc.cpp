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
using interval = p1788::infsup::interval<T, p1788::flavor::infsup::mpfr_flavor>;

int main()
{

    typedef p1788::flavor::infsup::mpfr_flavor<double> flav;

    flav a;
    a = a;

    interval<double> d_a(1,2), d_b(3,4), d_c(5,6);
    interval<float> f_a(1,2), f_b(3,4), f_c(5,6);


// Elementary functions

    std::cout << "pos: " << pos(d_a) << std::endl;
    std::cout << "+x: " << +d_a << std::endl;
    std::cout << "pos mt: " << p1788::infsup::pos<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "neg: " << neg(d_a) << std::endl;
    std::cout << "-x: " << -d_a << std::endl;
    std::cout << "neg mt: " << p1788::infsup::neg<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "add: " << add(d_a, d_b) << std::endl;
    std::cout << "x + y: " << d_a + d_b << std::endl;
    std::cout << "add mt: " << p1788::infsup::add<interval<float>>(d_a, f_b) << std::endl << std::endl;

    std::cout << "sub: " << sub(d_a, d_b) << std::endl;
    std::cout << "x - y: " << d_a - d_b << std::endl;
    std::cout << "sub mt: " << p1788::infsup::sub<interval<float>>(d_a, f_b) << std::endl << std::endl;

    std::cout << "mul: " << mul(d_a, d_b) << std::endl;
    std::cout << "x * y: " << d_a * d_b << std::endl;
    std::cout << "mul mt: " << p1788::infsup::mul<interval<float>>(d_a, f_b) << std::endl << std::endl;

    std::cout << "div: " << div(d_a, d_b) << std::endl;
    std::cout << "x / y: " << d_a / d_b << std::endl;
    std::cout << "div mt: " << p1788::infsup::div<interval<float>>(d_a, f_b) << std::endl << std::endl;

    std::cout << "inv: " << inv(d_a) << std::endl;
    std::cout << "inv mt: " << p1788::infsup::inv<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "sqrt: " << sqrt(d_a) << std::endl;
    std::cout << "sqrt mt: " << p1788::infsup::sqrt<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "fma: " << fma(d_a, d_b, d_c) << std::endl;
    std::cout << "fma mt: " << p1788::infsup::fma<interval<float>>(d_a, f_b, d_c) << std::endl << std::endl;

    std::cout << "case: " << interval_case(d_a, d_b, d_c) << std::endl;
    std::cout << "case mt: " << p1788::infsup::interval_case<interval<float>>(d_a, f_b, d_c) << std::endl << std::endl;

    std::cout << "sqr: " << sqr(d_a) << std::endl;
    std::cout << "sqr mt: " << p1788::infsup::sqr<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "pown: " << pown(d_a, 3) << std::endl;
    std::cout << "pown mt: " << p1788::infsup::pown<interval<float>>(d_a, 3) << std::endl << std::endl;

    std::cout << "pow: " << pow(d_a, d_b) << std::endl;
    std::cout << "pow mt: " << p1788::infsup::pow<interval<float>>(d_a, f_b) << std::endl << std::endl;

    std::cout << "exp: " << exp(d_a) << std::endl;
    std::cout << "exp mt: " << p1788::infsup::exp<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "exp2: " << exp2(d_a) << std::endl;
    std::cout << "exp2 mt: " << p1788::infsup::exp2<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "exp10: " << exp10(d_a) << std::endl;
    std::cout << "exp10 mt: " << p1788::infsup::exp10<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "log: " << log(d_a) << std::endl;
     std::cout << "log mt: " << p1788::infsup::log<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "log2: " << log2(d_a) << std::endl;
    std::cout << "log2 mt: " << p1788::infsup::log2<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "log10: " << log10(d_a) << std::endl;
    std::cout << "log10 mt: " << p1788::infsup::log10<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "sin: " << sin(d_a) << std::endl;
    std::cout << "sin mt: " << p1788::infsup::sin<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "cos: " << cos(d_a) << std::endl;
    std::cout << "cos mt: " << p1788::infsup::cos<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "tan: " << tan(d_a) << std::endl;
    std::cout << "tan mt: " << p1788::infsup::tan<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "asin: " << asin(d_a) << std::endl;
    std::cout << "asin mt: " << p1788::infsup::asin<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "acos: " << acos(d_a) << std::endl;
    std::cout << "acos mt: " << p1788::infsup::acos<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "atan: " << atan(d_a) << std::endl;
    std::cout << "atan mt: " << p1788::infsup::atan<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "atan2: " << atan2(d_b, d_a) << std::endl;
    std::cout << "atan2 mt: " << p1788::infsup::atan2<interval<float>>(d_b, d_a) << std::endl << std::endl;

    std::cout << "sinh: " << sinh(d_a) << std::endl;
    std::cout << "sinh mt: " << p1788::infsup::sinh<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "cosh: " << cosh(d_a) << std::endl;
    std::cout << "cosh mt: " << p1788::infsup::cosh<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "tanh: " << tanh(d_a) << std::endl;
    std::cout << "tanh mt: " << p1788::infsup::tanh<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "asinh: " << asinh(d_a) << std::endl;
    std::cout << "asinh mt: " << p1788::infsup::asinh<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "acosh: " << acosh(d_a) << std::endl;
    std::cout << "acosh mt: " << p1788::infsup::acosh<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "atanh: " << atanh(d_a) << std::endl;
    std::cout << "atanh mt: " << p1788::infsup::atanh<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "sign: " << sign(d_a) << std::endl;
    std::cout << "sign mt: " << p1788::infsup::sign<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "ceil: " << ceil(d_a) << std::endl;
    std::cout << "ceil mt: " << p1788::infsup::ceil<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "floor: " << floor(d_a) << std::endl;
    std::cout << "floor mt: " << p1788::infsup::floor<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "trunc: " << trunc(d_a) << std::endl;
    std::cout << "trunc mt: " << p1788::infsup::trunc<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "round_ties_to_even: " << round_ties_to_even(d_a) << std::endl;
    std::cout << "round_ties_to_even mt: " << p1788::infsup::round_ties_to_even<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "round_ties_to_away: " << round_ties_to_away(d_a) << std::endl;
    std::cout << "round_ties_to_away mt: " << p1788::infsup::round_ties_to_away<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "abs: " << abs(d_a) << std::endl;
    std::cout << "abs mt: " << p1788::infsup::abs<interval<float>>(d_a) << std::endl << std::endl;

    std::cout << "min: " << min( d_a, d_b, d_c, d_b) << std::endl;
    std::cout << "min mt: " << p1788::infsup::min<interval<float>>( d_a, f_b, d_c) << std::endl << std::endl;

    std::cout << "max: " << p1788::infsup::max( d_a, d_b, d_c) << std::endl;
    std::cout << "max mt: " << p1788::infsup::max<interval<float>>( d_a, f_b, d_c) << std::endl;


    return 0;
}
