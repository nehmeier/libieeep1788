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

template<typename T>
using interval = p1788::infsup::interval<T, p1788::flavor::infsup::mpfr_flavor>;

int main()
{
    //typedef p1788::infsup::interval<double, p1788::flavor::infsup::ieee754_flavor>  interval;


    interval<double> a(0,5);
    std::cout << a << std::endl;
    std::cout << inf(a) << std::endl;
    std::cout << sup(a) << std::endl;
    std::cout << mid(a) << std::endl;
    std::cout << rad(a) << std::endl;
    std::cout << wid(a) << std::endl;
    std::cout << mag(a) << std::endl;
    std::cout << mig(a) << std::endl << std::endl;

    std::cout << sin(a) << std::endl;


//    interval i1(1.2);
//    interval i2(1.2, 3.4);
//    interval i3( {1,2,3,4,5,56,7,8,9,.9});
//    interval i4("[1.2,3.4]");
//    interval i5("EMPTY");
//    interval i6 = interval::empty();
//    interval i7 = interval::entire();
//
//    interval i8;
//    std::cin >> i8;
//
//    std::cout << std::endl;
//
//    std::cout << i1 << std::endl;
//    std::cout << i2 << std::endl;
//    std::cout << i3 << std::endl;
//    std::cout << i4 << std::endl;
//    std::cout << i5 << std::endl;
//    std::cout << i6 << std::endl;
//    std::cout << i7 << std::endl;
//    std::cout << i8 << std::endl << std::endl;
//
//    std::cout << i2.lower() << std::endl;
//    std::cout << i2.upper() << std::endl;
//    std::cout << i2.mid() << std::endl;
//    std::cout << i2.rad() << std::endl;

    return 0;
}
