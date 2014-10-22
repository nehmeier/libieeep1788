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

#define BOOST_TEST_MODULE "Flavor: Utility functions [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include <string>
#include <limits>
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"

template<typename T>
using F = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>;

const double INF_D = std::numeric_limits<double>::infinity();
const float INF_F = std::numeric_limits<float>::infinity();
const double MAX_D = std::numeric_limits<double>::max();
const float MAX_F = std::numeric_limits<float>::max();
const double DNORM_MIN_D = std::numeric_limits<double>::denorm_min();
const float DNORM_MIN_F = std::numeric_limits<float>::denorm_min();



BOOST_AUTO_TEST_CASE(minimal_convert_rndd)
{
    BOOST_CHECK_EQUAL(F<double>::convert_rndd(std::stod("0X1.9999999999999P-4")), std::stod("0X1.9999999999999P-4"));
    BOOST_CHECK_EQUAL(F<float>::convert_rndd(std::stod("0X1.9999999999999P-4")), std::stof("0X1.999998P-4"));
    BOOST_CHECK_EQUAL(F<double>::convert_rndd(std::stod("0x1.99999A0000000p-4")), std::stod("0x1.99999A0000000p-4"));
    BOOST_CHECK_EQUAL(F<double>::convert_rndd(std::stof("0x1.99999Ap-4")), std::stod("0x1.99999A0000000p-4"));
    BOOST_CHECK_EQUAL(F<float>::convert_rndd(std::stod("0x1.99999A0000000p-4")), std::stof("0X1.99999AP-4"));

    BOOST_CHECK_EQUAL(F<double>::convert_rndd(std::stod("-0x1.99999A842549Ap+4")), std::stod("-0x1.99999A842549Ap+4"));
    BOOST_CHECK_EQUAL(F<float>::convert_rndd(std::stod("-0x1.99999A842549Ap+4")), std::stof("-0X1.99999CP+4"));
    BOOST_CHECK_EQUAL(F<double>::convert_rndd(std::stod("-0X1.99999C0000000p+4")), std::stod("-0X1.99999C0000000p+4"));
    BOOST_CHECK_EQUAL(F<double>::convert_rndd(std::stof("-0X1.99999Cp+4")), std::stod("-0X1.99999C0000000p+4"));
    BOOST_CHECK_EQUAL(F<float>::convert_rndd(std::stod("-0X1.99999C0000000p+4")), std::stof("-0X1.99999CP+4"));


    BOOST_CHECK_EQUAL(F<double>::convert_rndd(DNORM_MIN_D), DNORM_MIN_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndd(DNORM_MIN_D), -0.0);
    BOOST_CHECK(std::signbit(F<float>::convert_rndd(DNORM_MIN_D)));
    BOOST_CHECK_EQUAL(F<double>::convert_rndd(-DNORM_MIN_D), -DNORM_MIN_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndd(-DNORM_MIN_D), -DNORM_MIN_F);

    BOOST_CHECK_EQUAL(F<double>::convert_rndd(MAX_D), MAX_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndd(MAX_D), MAX_F);
    BOOST_CHECK_EQUAL(F<double>::convert_rndd(-MAX_D), -MAX_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndd(-MAX_D), -INF_F);

    BOOST_CHECK_EQUAL(F<double>::convert_rndd(INF_D), INF_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndd(INF_D), INF_F);
    BOOST_CHECK_EQUAL(F<double>::convert_rndd(-INF_D), -INF_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndd(-INF_D), -INF_F);
    BOOST_CHECK_EQUAL(F<double>::convert_rndd(INF_F), INF_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndd(INF_F), INF_F);
    BOOST_CHECK_EQUAL(F<double>::convert_rndd(-INF_F), -INF_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndd(-INF_F), -INF_F);
}


BOOST_AUTO_TEST_CASE(minimal_convert_rndn)
{
    BOOST_CHECK_EQUAL(F<double>::convert_rndn(std::stod("0X1.9999999999999P-4")), std::stod("0X1.9999999999999P-4"));
    BOOST_CHECK_EQUAL(F<float>::convert_rndn(std::stod("0X1.9999999999999P-4")), std::stof("0X1.99999AP-4"));
    BOOST_CHECK_EQUAL(F<double>::convert_rndn(std::stod("0x1.99999A0000000p-4")), std::stod("0x1.99999A0000000p-4"));
    BOOST_CHECK_EQUAL(F<double>::convert_rndn(std::stof("0x1.99999Ap-4")), std::stod("0x1.99999A0000000p-4"));
    BOOST_CHECK_EQUAL(F<float>::convert_rndn(std::stod("0x1.99999A0000000p-4")), std::stof("0X1.99999AP-4"));

    BOOST_CHECK_EQUAL(F<double>::convert_rndn(std::stod("-0x1.99999A842549Ap+4")), std::stod("-0x1.99999A842549Ap+4"));
    BOOST_CHECK_EQUAL(F<float>::convert_rndn(std::stod("-0x1.99999A842549Ap+4")), std::stof("-0X1.99999AP+4"));
    BOOST_CHECK_EQUAL(F<double>::convert_rndn(std::stod("-0X1.99999C0000000p+4")), std::stod("-0X1.99999C0000000p+4"));
    BOOST_CHECK_EQUAL(F<double>::convert_rndn(std::stof("-0X1.99999Cp+4")), std::stod("-0X1.99999C0000000p+4"));
    BOOST_CHECK_EQUAL(F<float>::convert_rndn(std::stod("-0X1.99999C0000000p+4")), std::stof("-0X1.99999CP+4"));

    BOOST_CHECK_EQUAL(F<double>::convert_rndn(DNORM_MIN_D), DNORM_MIN_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndn(DNORM_MIN_D), 0.0);
    BOOST_CHECK(!std::signbit(F<float>::convert_rndn(DNORM_MIN_D)));
    BOOST_CHECK_EQUAL(F<double>::convert_rndn(-DNORM_MIN_D), -DNORM_MIN_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndn(-DNORM_MIN_D), 0.0);
    BOOST_CHECK(!std::signbit(F<float>::convert_rndn(-DNORM_MIN_D)));

    BOOST_CHECK_EQUAL(F<double>::convert_rndn(MAX_D), MAX_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndn(MAX_D), INF_F);
    BOOST_CHECK_EQUAL(F<double>::convert_rndn(-MAX_D), -MAX_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndn(-MAX_D), -INF_F);

    BOOST_CHECK_EQUAL(F<double>::convert_rndn(INF_D), INF_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndn(INF_D), INF_F);
    BOOST_CHECK_EQUAL(F<double>::convert_rndn(-INF_D), -INF_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndn(-INF_D), -INF_F);
    BOOST_CHECK_EQUAL(F<double>::convert_rndn(INF_F), INF_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndn(INF_F), INF_F);
    BOOST_CHECK_EQUAL(F<double>::convert_rndn(-INF_F), -INF_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndn(-INF_F), -INF_F);
}

BOOST_AUTO_TEST_CASE(minimal_convert_rndu)
{
    BOOST_CHECK_EQUAL(F<double>::convert_rndu(std::stod("0X1.9999999999999P-4")), std::stod("0X1.9999999999999P-4"));
    BOOST_CHECK_EQUAL(F<float>::convert_rndu(std::stod("0X1.9999999999999P-4")), std::stof("0X1.99999AP-4"));
    BOOST_CHECK_EQUAL(F<double>::convert_rndu(std::stod("0x1.99999A0000000p-4")), std::stod("0x1.99999A0000000p-4"));
    BOOST_CHECK_EQUAL(F<double>::convert_rndu(std::stof("0x1.99999Ap-4")), std::stod("0x1.99999A0000000p-4"));
    BOOST_CHECK_EQUAL(F<float>::convert_rndu(std::stod("0x1.99999A0000000p-4")), std::stof("0X1.99999AP-4"));

    BOOST_CHECK_EQUAL(F<double>::convert_rndu(std::stod("-0x1.99999A842549Ap+4")), std::stod("-0x1.99999A842549Ap+4"));
    BOOST_CHECK_EQUAL(F<float>::convert_rndu(std::stod("-0x1.99999A842549Ap+4")), std::stof("-0X1.99999AP+4"));
    BOOST_CHECK_EQUAL(F<double>::convert_rndu(std::stod("-0X1.99999C0000000p+4")), std::stod("-0X1.99999C0000000p+4"));
    BOOST_CHECK_EQUAL(F<double>::convert_rndu(std::stof("-0X1.99999Cp+4")), std::stod("-0X1.99999C0000000p+4"));
    BOOST_CHECK_EQUAL(F<float>::convert_rndu(std::stod("-0X1.99999C0000000p+4")), std::stof("-0X1.99999CP+4"));

    BOOST_CHECK_EQUAL(F<double>::convert_rndu(DNORM_MIN_D), DNORM_MIN_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndu(DNORM_MIN_D), DNORM_MIN_F);
    BOOST_CHECK_EQUAL(F<double>::convert_rndu(-DNORM_MIN_D), -DNORM_MIN_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndu(-DNORM_MIN_D), 0.0);
    BOOST_CHECK(!std::signbit(F<float>::convert_rndu(-DNORM_MIN_D)));

    BOOST_CHECK_EQUAL(F<double>::convert_rndu(MAX_D), MAX_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndu(MAX_D), INF_F);
    BOOST_CHECK_EQUAL(F<double>::convert_rndu(-MAX_D), -MAX_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndu(-MAX_D), -MAX_F);

    BOOST_CHECK_EQUAL(F<double>::convert_rndu(INF_D), INF_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndu(INF_D), INF_F);
    BOOST_CHECK_EQUAL(F<double>::convert_rndu(-INF_D), -INF_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndu(-INF_D), -INF_F);
    BOOST_CHECK_EQUAL(F<double>::convert_rndu(INF_F), INF_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndu(INF_F), INF_F);
    BOOST_CHECK_EQUAL(F<double>::convert_rndu(-INF_F), -INF_D);
    BOOST_CHECK_EQUAL(F<float>::convert_rndu(-INF_F), -INF_F);
}
