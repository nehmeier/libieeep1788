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
using I = p1788::infsup::interval<T, flavor>;


template<typename T>
void ia_newton(I<T> (*f) (I<T> const&),
               I<T> (*df) (I<T> const&),
               I<T> const& y,
               T eps,
               bool unique)
{
    if ( !is_member(0.0, f(y)))
        return;

    I<T> c = I<T>(mid(y));

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

I<double> f1 (I<double> const& x)
{
    return x;
}

I<double> df1 (I<double> const&)
{
    return I<double>(1.0);
}

I<double> f2 (I<double> const& x)
{
    return x*x;
}

I<double> df2 (I<double> const& x)
{
    return I<double>(2.0) * x;
}


I<double> f3 (I<double> const& x)
{
    return -x*x + I<double>(2.0);
}

I<double> df3 (I<double> const& x)
{
    return I<double>(-2.0) * x;
}



int main()
{

//using namespace p1788::infsup;


    ia_newton(f1, df1, I<double>(-3,5), 0.0001, false);
    std::cout << std::endl;
    ia_newton(f2, df2, I<double>(-3,5), 0.0001, false);
    std::cout << std::endl;
    ia_newton(f3, df3, I<double>(-3,5), 0.0001, false);

    return 0;
}

