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
#include <vector>
#include <iterator>

#include "p1788/p1788.hpp"

// Template type alias to define a generic bare infsup interval with a setbased
// infsup flavor based on mpfr supporting IEEE754 bound types.
template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;


// root finding method using bisection
template<typename T, class OutputIt>
void ia_bisect(I<T> (*f) (I<T> const&),     // function to be analyzed
               I<T> const& x,               // start interval
               T eps,                       // epsilon
               OutputIt it)                 // output iterator
{
    // compute interval y = f(x);
    I<T> y = f(x);

    // check if 0 is a member of y
    if (is_member(0.0, y))
    {
        // check if y is a tight enough enclosure of 0
        if (wid(y) < eps)
            *it++ = x;      // save root
        else
        {
            // recursive call with subintervals [inf(x),mid(x)] and [mid(x),sup(x)]
            ia_bisect(f, I<T>(inf(x), mid(x)), eps, it);
            ia_bisect(f, I<T>(mid(x), sup(x)), eps, it);
        }
    }
}

// f(x) = x^2 - 2
template<typename T>
I<T> f (I<T> const& x)
{
    return x * x - I<T>(2.0,2.0);
}


int main()
{
    std::vector<I<double>> roots;

    // start root finding
    ia_bisect(f, I<double>(-2.0,2.0), 0.00001, std::back_inserter(roots));

    std::cout << "roots of f(x) = x^2 - 2 (over the range [-2,2]):" << std::endl;
    for (auto i : roots)
        std::cout << "    " << i << std::endl;

    return 0;
}

