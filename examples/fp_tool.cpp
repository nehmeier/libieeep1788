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


//TODO BUG with GMP
#include <cstddef>

#include <iostream>
#include <stdio.h>
#include <string>
#include <mpfr.h>
#include <limits>

double readDouble()
{
    double x;
    std::string str;
    std::cin >> str;

    if (str == "max")
        return std::numeric_limits<double>::max();
    else if (str == "-max")
        return -std::numeric_limits<double>::max();
    else if (str == "min")
        return std::numeric_limits<double>::min();
    else if (str == "-min")
        return -std::numeric_limits<double>::min();
    else if (str == "dnormmin")
        return std::numeric_limits<double>::denorm_min();
    else if (str == "-dnormmin")
        return -std::numeric_limits<double>::denorm_min();
    else if (str == "lowest")
        return std::numeric_limits<double>::lowest();
    else if (str == "-lowest")
        return -std::numeric_limits<double>::lowest();
    else if (str == "inf")
        return std::numeric_limits<double>::infinity();
    else if (str == "-inf")
        return -std::numeric_limits<double>::infinity();
    else if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        sscanf(str.c_str(), "%lA", &x);
    else
        sscanf(str.c_str(), "%lf", &x);

    return x;
}



void perform()
{
    mpfr_t r, x, y, z;
    mpfr_inits2 (53, r, x, y, z, (mpfr_ptr) 0);

    std::string str;
    std::cin >> str;


    if (str == "pi") {

        mpfr_const_pi(r, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_const_pi(r, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_const_pi(r, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "id") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n\n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));
    }

    if (str == "succ") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_nextabove(x);
        printf("%f %A  \n\n",  mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));
    }

    if (str == "pred") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_nextbelow(x);
        printf("%f %A  \n\n",  mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));
    }



    if (str == "add") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);
        mpfr_set_d(y, readDouble(), MPFR_RNDN);


        printf("%f %A   %f %A : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(y, MPFR_RNDN), mpfr_get_d(y, MPFR_RNDN));

        mpfr_add(r, x, y, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_add(r, x, y, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_add(r, x, y, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }


    if (str == "sub") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);
        mpfr_set_d(y, readDouble(), MPFR_RNDN);


        printf("%f %A   %f %A : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(y, MPFR_RNDN), mpfr_get_d(y, MPFR_RNDN));

        mpfr_sub(r, x, y, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_sub(r, x, y, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_sub(r, x, y, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }


    if (str == "mul") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);
        mpfr_set_d(y, readDouble(), MPFR_RNDN);


        printf("%f %A   %f %A : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(y, MPFR_RNDN), mpfr_get_d(y, MPFR_RNDN));

        mpfr_mul(r, x, y, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_mul(r, x, y, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_mul(r, x, y, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }



    if (str == "div") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);
        mpfr_set_d(y, readDouble(), MPFR_RNDN);


        printf("%f %A   %f %A : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(y, MPFR_RNDN), mpfr_get_d(y, MPFR_RNDN));

        mpfr_div(r, x, y, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_div(r, x, y, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_div(r, x, y, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }


    if (str == "sqr") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_sqr(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_sqr(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_sqr(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }


    if (str == "sqrt") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_sqrt(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_sqrt(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_sqrt(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }


    if (str == "fma") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);
        mpfr_set_d(y, readDouble(), MPFR_RNDN);
        mpfr_set_d(z, readDouble(), MPFR_RNDN);

        printf("%f %A   %f %A  %f %A : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(y, MPFR_RNDN), mpfr_get_d(y, MPFR_RNDN), mpfr_get_d(z, MPFR_RNDN), mpfr_get_d(z, MPFR_RNDN));

        mpfr_fma(r, x, y, z, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_fma(r, x, y, z, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_fma(r, x, y, z, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }


    if (str == "log") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_log(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_log(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_log(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "log2") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_log2(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_log2(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_log2(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "log10") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_log10(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_log10(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_log10(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }


    if (str == "exp") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_exp(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_exp(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_exp(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "exp2") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_exp2(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_exp2(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_exp2(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "exp10") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_exp10(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_exp10(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_exp10(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }



    if (str == "sin") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_sin(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_sin(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_sin(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "cos") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_cos(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_cos(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_cos(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "tan") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_tan(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_tan(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_tan(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "asin") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_asin(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_asin(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_asin(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "acos") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_acos(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_acos(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_acos(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "atan") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_atan(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_atan(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_atan(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "sinh") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_sinh(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_sinh(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_sinh(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "cosh") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_cosh(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_cosh(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_cosh(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "tanh") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_tanh(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_tanh(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_tanh(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "asinh") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_asinh(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_asinh(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_asinh(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "acosh") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_acosh(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_acosh(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_acosh(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    if (str == "atanh") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);


        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_atanh(r, x, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_atanh(r, x, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_atanh(r, x, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }


    if (str == "pown") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);

        long p;
        std::cin >> p;

        printf("%f %A  : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN));

        mpfr_pow_si(r, x, p, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_pow_si(r, x, p, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_pow_si(r, x, p, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }


    if (str == "pow") {
        mpfr_set_d(x, readDouble(), MPFR_RNDN);
        mpfr_set_d(y, readDouble(), MPFR_RNDN);

        printf("%f %A   %f %A : \n", mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(x, MPFR_RNDN), mpfr_get_d(y, MPFR_RNDN), mpfr_get_d(y, MPFR_RNDN));

        mpfr_pow(r, x, y, MPFR_RNDD);
        printf("%f %A  ",  mpfr_get_d(r, MPFR_RNDD), mpfr_get_d(r, MPFR_RNDD));

        mpfr_pow(r, x, y, MPFR_RNDN);
        printf("%f %A  ", mpfr_get_d(r, MPFR_RNDN), mpfr_get_d(r, MPFR_RNDN));

        mpfr_pow(r, x, y, MPFR_RNDU);
        printf("%f %A\n\n", mpfr_get_d(r, MPFR_RNDU), mpfr_get_d(r, MPFR_RNDU));
    }

    mpfr_clears (r, x, y, z, (mpfr_ptr) 0);
}

int main()
{
    std::cout << std::numeric_limits<double>::denorm_min() << std::endl;
    printf("%f %A\n\n", std::numeric_limits<double>::denorm_min(), std::numeric_limits<double>::denorm_min());

    for(;;)
        perform();

    return 0;
}
