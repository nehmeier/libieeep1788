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

    interval<double> d_a(-2,1), d_b(0,4), d_c(5,6);
    interval<float> f_a(1,2), f_b(3,4), f_c(5,6);


// Boolean functions



    return 0;
}
