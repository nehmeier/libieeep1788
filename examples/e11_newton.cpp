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
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;


template<typename T, class OutputIt>
void ia_newton(I<T> (*f) (I<T> const&),
               I<T> (*df) (I<T> const&),
               I<T> const& x,
               T eps,
               OutputIt it)
{
    if ( !is_member(0.0, f(x)) )
        return;

    I<T> c = I<T>(mid(x));

    auto z = div_to_pair(f(c), df(y));
    I<T> z1 = c - z.first;
    I<T> z2 = c - z.second;

    I<T> v1 = intersect(y, z1);
    I<T> v2 = intersect(y, z2);

    if (v1 == y) {
        v1 = I<T>(inf(y), mid(y));
        v2 = I<T>(mid(y), sup(y));
    }

    if (!is_empty(v1) && is_empty(v2))
        unique = unique || is_interior(v1, y);

    if (!is_empty(v1)) {
        if (wid(v1) < eps)
            std::cout << v1 << " " << unique << std::endl;
        else
            ia_newton(f, df, v1, eps, unique);
    }

    if (!is_empty(v2)) {
        if (wid(v2) < eps)
            std::cout << v2 << " " << unique << std::endl;
        else
            ia_newton(f, df, v2, eps, unique);
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

