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
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes>;

template<typename T>
using I = p1788::infsup::decorated_interval<T, flavor>;


int main()
{

using namespace p1788::infsup;


    I<double> d_a(-1,2), d_b(3,4), d_c(1,6);
    I<float> f_a(1,2), f_b(3,4), f_c(5,6);


    std::cout << d_a << std::endl;
    std::cout << d_a.rad() << std::endl;
    std::cout << d_a.decoration() << std::endl;


//    p1788::decoration::decoration dec = p1788::decoration::decoration::trv;
//
//    std::cin >> dec;
//    std::cout << dec << std::endl;

    std::cout << intersect(d_a, d_b) << std::endl;
    std::cout << hull(d_a, d_b) << std::endl;

    std::cout << inf(d_a) << std::endl;
    std::cout << sup(d_a) << std::endl;
    std::cout << mid_rad(d_a).first << std::endl;
    std::cout << mid_rad(d_a).second << std::endl;
    std::cout << is_empty(d_a) << std::endl;
    std::cout << is_equal(d_a, d_b) << std::endl;
    std::cout << (d_a != d_b) << std::endl;
    std::cout << less(d_a, d_b) << std::endl;
    std::cout << contains(d_a, d_b) << std::endl;

    std::cout << d_a + d_b << std::endl;
    std::cout << div(d_a, d_b) << std::endl;
    std::cout << sin(d_a) << std::endl;

    std::cout << div_to_pair(d_a, d_b).first << std::endl;
    std::cout << div_to_pair(d_a, d_b).second << std::endl;
    std::cout << div_to_pair(d_b, d_a).first << std::endl;
    std::cout << div_to_pair(d_b, d_a).second << std::endl;

    std::cout << sqr_rev(d_b) << std::endl;
    std::cout << sin_rev(d_b) << std::endl;

    std::cout << cancel_plus(d_b, d_a) << std::endl;
    std::cout << cancel_minus(d_b, d_a) << std::endl;

    std::cout << is_singleton(d_b) << std::endl;
    std::cout << is_member(5.1, d_b) << std::endl;

    std::cout << rootn(d_b, 3) << std::endl;
    std::cout << expm1(d_b) << std::endl;
    std::cout << compoundm1(d_a, d_b) << std::endl;

    std::cout << static_cast<int>(overlap(d_a, d_b)) << std::endl;

    std::cout << log_slope2(d_a) << std::endl;
    std::cout << asin_slope3(d_a) << std::endl;


    return 0;
}

