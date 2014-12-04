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
#include <sstream>

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

    // IO supports inf-sup and uncertain form
    // Both bare and decorated interval literals work with or without a decoration specifier
    std::stringstream ss("[1.0,inf]_def   [5.0]   1.234567?12de+3_dac   [,]");

    // 1) IO is provided by the common stream operator

    // 1.1) Input
    I<double> i;
    I<double> i2;
    ss >> i;        // [1.0,inf]_def
    ss >> i2;       // [5.0]

    // 1.2) Output
    std::cout << i << std::endl;
    std::cout << i2 << std::endl;


    // 2) And for decorated intervals

    // 2.1) Input
    DI<double> di;
    DI<double> di2;
    ss >> di;       // 1.234567?12de+3_dac
    ss >> di2;      // [,]

    // 2.2) Output
    std::cout << di << std::endl;
    std::cout << di2 << std::endl << std::endl;


    // 3) Additionally there are a lot of output manipulators

    // 3.1) Lower and upper case
    std::cout << p1788::io::upper_case;
    std::cout << di << std::endl;

    std::cout << p1788::io::lower_case;     // default
    std::cout << di << std::endl << std::endl;

    // 3.2) Overall string width
    std::cout << p1788::io::string_width(25);
    std::cout << di << std::endl;

    std::cout << p1788::io::string_width(0);     // default
    std::cout << di << std::endl << std::endl;

    // 3.3) Inf-sup and uncertain form
    std::cout << p1788::io::uncertain_form;
    std::cout << di << std::endl;

    std::cout << p1788::io::uncertain_up_form;
    std::cout << di << std::endl;

    std::cout << p1788::io::uncertain_down_form;
    std::cout << di << std::endl;

    std::cout << p1788::io::inf_sup_form;     // default
    std::cout << di << std::endl << std::endl;


    // 3.4) Decimal, scientific, hex and decimal_scientific number representations
    std::cout << p1788::io::decimal;
    std::cout << di << std::endl;

    std::cout << p1788::io::scientific;
    std::cout << di << std::endl;

    std::cout << p1788::io::hex;
    std::cout << di << std::endl;

    std::cout << p1788::io::decimal_scientific;     // default
    std::cout << di << std::endl << std::endl;

    // 3.5) Width of a number
    std::cout << p1788::io::width(17);
    std::cout << di << std::endl;

    std::cout << p1788::io::width(0);     // default
    std::cout << di << std::endl << std::endl;

    // 3.6) Precision of a number
    std::cout << p1788::io::precision(10);
    std::cout << di << std::endl;

    std::cout << p1788::io::precision(0);     // default
    std::cout << di << std::endl << std::endl;

    // 3.7) Representation of special numbers and intervals
    std::cout << p1788::io::special_bounds;
    std::cout << I<double>::empty() << std::endl;
    std::cout << I<double>::entire() << std::endl;
    std::cout << i << std::endl;

    std::cout << p1788::io::special_no_bounds;
    std::cout << I<double>::empty() << std::endl;
    std::cout << I<double>::entire() << std::endl;
    std::cout << i << std::endl;

    std::cout << p1788::io::special_text;   // default
    std::cout << I<double>::empty() << std::endl;
    std::cout << I<double>::entire() << std::endl;
    std::cout << i << std::endl << std::endl;

    // 3.8) Disable punctuation
    std::cout << p1788::io::no_punctuation;
    std::cout << di << std::endl;

    std::cout << p1788::io::punctuation;     // default
    std::cout << di << std::endl << std::endl;

    // 3.9) Uncertain form with exponent
    std::cout << p1788::io::uncertain_form;
    std::cout << p1788::io::uncertain_exponent;
    std::cout << di << std::endl;

    std::cout << p1788::io::no_uncertain_exponent;     // default
    std::cout << di << std::endl << std::endl;

    // 3.10) Decoration as text or numbers
    std::cout << p1788::io::inf_sup_form;
    std::cout << p1788::io::dec_numeric;
    std::cout << di << std::endl;

    std::cout << p1788::io::dec_alpha;     // default
    std::cout << di << std::endl << std::endl;

    return 0;
}

