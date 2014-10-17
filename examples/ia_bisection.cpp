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
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes, p1788::flavor::infsup::auto_setup::yes>;

template<typename T>
using I = p1788::infsup::interval<T, flavor>;


template<typename T>
void ia_bisect(I<T> (*f) (I<T> const&),
               I<T> const& x,
               T eps,
               int& n
               )
{
    I<T> y = f(x);

    std::cout << "set object " << n++ << " rect from " << inf(x) << "," << inf(y)
              << " to " << sup(x) << "," << sup(y);

    if (wid(y) < eps)
        std::cout << " fs empty border rgb \"green\"" << std::endl;
    else {
        std::cout << " fs empty border rgb \"blue\"" << std::endl;
        ia_bisect(f, I<T>(inf(x), mid(x)), eps, n);
        ia_bisect(f, I<T>(mid(x), sup(x)), eps, n);
    }
}


I<double> f (I<double> const& x)
{
    return x*x + sin(x);
}


int main()
{

using namespace p1788::infsup;


//    ia_bisect(f1, I<double>(-3,5), 0.0001);
//    std::cout << std::endl;
//    ia_bisect(f2, I<double>(-3,5), 0.0001);
//    std::cout << std::endl;
    int n = 1;
    ia_bisect(f, I<double>(1.0,6.0), 0.2, n);

    return 0;
}

