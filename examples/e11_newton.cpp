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


// root finding method using Interval Newton
template<typename T, class OutputIt>
void ia_newton(I<T> (*f) (I<T> const&),     // function to be analyzed
               I<T> (*df) (I<T> const&),    // derivative of f
               I<T> const& x,               // start interval
               T eps,                       // epsilon
               OutputIt it)                 // output iterator
{
    // check if 0 is a member of f(x)
    if ( !is_member(0.0, f(x)) )
        return;

    // Newton step
    T m = mid(x);
    I<T> c = I<T>(m,m);
    auto z = mul_rev_to_pair(df(x), f(c));      // z = f(c) / df(x)

    // pairwise intersection of z and x
    I<T> v1 = intersect(x, c - z.first);
    I<T> v2 = intersect(x, c - z.second);

    // bisection if v1 == x
    if (v1 == x)
    {
        v1 = I<T>(inf(x), m);
        v2 = I<T>(m, sup(x));
    }

    if (!is_empty(v1))
    {
        // check if v1 is a tight enough enclosure of 0
        if (wid(v1) < eps)
            *it++ = v1;     // save root
        else
            // recursive call with subinterval v1
            ia_newton(f, df, v1, eps, it);
    }

    if (!is_empty(v2))
    {
        // check if v2 is a tight enough enclosure of 0
        if (wid(v2) < eps)
            *it++ = v2;     // save root
        else
            // recursive call with subinterval v2
            ia_newton(f, df, v2, eps, it);
    }
}

// f(x) = x^2 - 2
template<typename T>
I<T> f (I<T> const& x)
{
    return x * x - I<T>(2.0,2.0);
}

// f'(x) = 2x
template<typename T>
I<T> df (I<T> const& x)
{
    return I<T>(2.0,2.0) * x  ;
}


int main()
{
    std::vector<I<double>> roots;

    // start root finding
    ia_newton(f, df, I<double>(-2.0,2.0), 0.00001, std::back_inserter(roots));

    std::cout << "roots of f(x) = x^2 - 2 (over the range [-2,2]):" << std::endl;
    for (auto i : roots)
        std::cout << "    " << i << std::endl;

    return 0;
}

