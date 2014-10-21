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
#include <stdio.h>

#include "p1788/p1788.hpp"

template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;





template<typename T>
T f_nat(T x)
{
    return x * x + sin(x);
}

template<typename T>
I<T> f_ex(I<T> x)
{
    return I<T>(x.lower() * x.lower() + sin(x.lower()), x.upper() * x.upper() + sin(x.upper())) ;
}

template<typename T>
I<T> f_cen(I<T> x)
{
    return f_nat(I<T>(mid(x))) + (x - I<T>(mid(x))) * (I<T>(2.0) * x + cos(x)) ;
}

template<typename T>
I<T> f_tay(I<T> x)
{
    return f_nat(I<T>(mid(x))) + (x - I<T>(mid(x))) * (I<T>(2.0) * I<T>(mid(x)) + cos(I<T>(mid(x))))
    + ((x - I<T>(mid(x))) * (x - I<T>(mid(x))) / (I<T>(2.0)))  * ((I<T>(2.0) - sin(x))) ;
}

template<typename T>
I<T> f_intersect(I<T> x)
{
    return intersect(intersect(f_nat(x), f_cen(x)), f_tay(x));
}


template<typename T>
I<T> f_bisect(I<T> (*f) (I<T>),
               I<T> x,
               int steps
               //int& n
               )
{
    I<T> y = f(x);



    if (steps == 0) {
             std::cout << "X" << std::endl;

//        std::cout << "set object " << n++ << " rect from " << inf(x) << "," << inf(y)
//              << " to " << sup(x) << "," << sup(y);
//    std::cout << " fs empty border rgb \"black\"" << std::endl;
        return y;
    }



    //std::cout << " fs empty border rgb \"blue\"" << std::endl;
    return hull(f_bisect(f, I<T>(inf(x), mid(x)), steps -1),
        f_bisect(f, I<T>(mid(x), sup(x)), steps -1));
}



int main()
{

//    std::cout << f_nat(5.0) << std::endl;
//    std::cout << f_nat(I<double>(5.0)) << std::endl << std::endl;

    int steps = 3;
//int i = 30;
    // [2pi / 3, 4pi / 3]
    I<double> x1(2.0943951, 4.1887902);
    // [99pi / 100, 101pi / 100]
    I<double> x2(3.1101767, 3.1730086);

    std::cout << "x1 = " << x1 << std::endl;
    std::cout << "F_e(x1) = " << f_ex(x1) << std::endl;
    std::cout << "F_n(x1) = " << f_nat(x1) << " d = " <<  wid(f_nat(x1)) - wid(f_ex(x1)) << " " << wid(f_nat(x1)) / wid(f_ex(x1)) << std::endl;
    std::cout << "F_c(x1) = " << f_cen(x1) << " d = " <<  wid(f_cen(x1)) - wid(f_ex(x1)) << " " << wid(f_cen(x1)) / wid(f_ex(x1)) << std::endl;
    std::cout << "F_t(x1) = " << f_tay(x1) << " d = " <<  wid(f_tay(x1)) - wid(f_ex(x1)) << " " << wid(f_tay(x1)) / wid(f_ex(x1)) << std::endl;

    //std::cout << f_intersect(x1) << " " <<  wid(f_intersect(x1)) - wid(f_ex(x1)) << std::endl;

    std::cout << "bisect F_n(x1) = " << f_bisect(f_nat, x1, steps); //<< " d = " <<  wid(f_bisect(f_nat, x1, steps)) - wid(f_ex(x1)) << " " << wid(f_bisect(f_nat, x1, steps)) / wid(f_ex(x1)) << std::endl;
//    std::cout << "bisect F_c(x1) = " << f_bisect(f_cen, x1, steps) << " d = " <<  wid(f_bisect(f_cen, x1, steps)) - wid(f_ex(x1)) << " " << wid(f_bisect(f_cen, x1, steps)) / wid(f_ex(x1)) << std::endl;
//    std::cout << "bisect F_t(x1) = " << f_bisect(f_tay, x1, steps) << " d = " <<  wid(f_bisect(f_tay, x1, steps)) - wid(f_ex(x1)) << " " << wid(f_bisect(f_tay, x1, steps)) / wid(f_ex(x1)) << std::endl;
//
//    //std::cout << f_bisect(f_intersect, x1, steps) << " " <<  wid(f_bisect(f_intersect, x1, steps)) - wid(f_ex(x1)) << std::endl << std::endl;
//    //int i = 10;
//    //f_bisect(f_nat, x1, steps, i); //<< std::endl; // " " <<  wid(f_bisect(f_intersect, x1, steps)) - wid(f_ex(x1)) << std::endl << std::endl;
//
//    std::cout << "x2 = " << x2 << std::endl;
//    std::cout << "F_e(x2) = " << f_ex(x2) << std::endl;
//    std::cout << "F_n(x2) = " << f_nat(x2) << " d = " <<  wid(f_nat(x2)) - wid(f_ex(x2)) << " " << wid(f_nat(x2)) / wid(f_ex(x2)) << std::endl;
//    std::cout << "F_c(x2) = " << f_cen(x2) << " d = " <<  wid(f_cen(x2)) - wid(f_ex(x2)) << " " << wid(f_cen(x2)) / wid(f_ex(x2)) << std::endl;
//    std::cout << "F_t(x2) = " << f_tay(x2) << " d = " <<  wid(f_tay(x2)) - wid(f_ex(x2)) << " " << wid(f_tay(x2)) / wid(f_ex(x2)) << std::endl;
//
//    //std::cout << f_intersect(x1) << " " <<  wid(f_intersect(x1)) - wid(f_ex(x1)) << std::endl;
//
//    std::cout << "bisect F_n(x2) = " << f_bisect(f_nat, x2, steps) << " d = " <<  wid(f_bisect(f_nat, x2, steps)) - wid(f_ex(x2)) << " " << wid(f_bisect(f_nat, x2, steps)) / wid(f_ex(x2)) << std::endl;
//    std::cout << "bisect F_c(x2) = " << f_bisect(f_cen, x2, steps) << " d = " <<  wid(f_bisect(f_cen, x2, steps)) - wid(f_ex(x2)) << " " << wid(f_bisect(f_cen, x2, steps)) / wid(f_ex(x2)) << std::endl;
//    std::cout << "bisect F_t(x2) = " << f_bisect(f_tay, x2, steps) << " d = " <<  wid(f_bisect(f_tay, x2, steps)) - wid(f_ex(x2)) << " " << wid(f_bisect(f_tay, x2, steps)) / wid(f_ex(x2)) << std::endl;

    //std::cout <<
    //f_bisect(f_ex, x2, steps, i); // << " " <<  wid(f_bisect(f_intersect, x2, steps, i)) - wid(f_ex(x2)) << std::endl << std::endl;




//    I<double> x(-1.0, 1.0);
//
//    std::cout << x * (x + I<double>(1.0)) << std::endl;
//    std::cout << x * x + x << std::endl;
//    std::cout << sqr(x) + x << std::endl;
//    std::cout << sqr(x + I<double>(0.5)) - I<double>(0.25) << std::endl << std::endl;
//
//
//    std::cout << I<double>(9.0) * pown(I<double>(10864.0), 4) + I<double>(1.0) - sqr(sqr(I<double>(18817.0))  - I<double>(1.0)) << std::endl;

    //std::cout << std::hexfloat << 3.14 << std::endl;
     printf("17.0625 in hexadecimal is: %A\n", 3.14);
    std::cout << 0X1.91EB851EB851FP+1 << std::endl;
    return 0;
}
