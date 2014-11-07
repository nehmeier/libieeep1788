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
#include <cmath>
#include "p1788/decoration/decoration.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"
#include "test/util/mpfr_bin_ieee754_flavor_io_test_util.hpp"

template<typename T>
using F = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>;

template<typename T>
using REP = typename F<T>::representation;

template<typename T>
using REP_DEC = typename F<T>::representation_dec;

typedef p1788::decoration::decoration DEC;

const double INF_D = std::numeric_limits<double>::infinity();
const float INF_F = std::numeric_limits<float>::infinity();
const double MAX_D = std::numeric_limits<double>::max();
const float MAX_F = std::numeric_limits<float>::max();
const double DNORM_MIN_D = std::numeric_limits<double>::denorm_min();
const float DNORM_MIN_F = std::numeric_limits<float>::denorm_min();

const double NAN_D = std::numeric_limits<double>::quiet_NaN();
const float NAN_F = std::numeric_limits<float>::quiet_NaN();


BOOST_AUTO_TEST_CASE(minimal_convert_rndd_test)
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

    BOOST_CHECK( std::isnan( F<double>::convert_rndd(NAN_D) ));
    BOOST_CHECK( std::isnan( F<float>::convert_rndd(NAN_D) ));
    BOOST_CHECK( std::isnan( F<double>::convert_rndd(NAN_F) ));
    BOOST_CHECK( std::isnan( F<float>::convert_rndd(NAN_F) ));
}


BOOST_AUTO_TEST_CASE(minimal_convert_rndn_test)
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

    BOOST_CHECK( std::isnan( F<double>::convert_rndn(NAN_D) ));
    BOOST_CHECK( std::isnan( F<float>::convert_rndn(NAN_D) ));
    BOOST_CHECK( std::isnan( F<double>::convert_rndn(NAN_F) ));
    BOOST_CHECK( std::isnan( F<float>::convert_rndn(NAN_F) ));
}


BOOST_AUTO_TEST_CASE(minimal_convert_rndu_test)
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

    BOOST_CHECK( std::isnan( F<double>::convert_rndu(NAN_D) ));
    BOOST_CHECK( std::isnan( F<float>::convert_rndu(NAN_D) ));
    BOOST_CHECK( std::isnan( F<double>::convert_rndu(NAN_F) ));
    BOOST_CHECK( std::isnan( F<float>::convert_rndu(NAN_F) ));
}


BOOST_AUTO_TEST_CASE(minimal_convert_hull_test)
{
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")) ), REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")) ), REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")) ), REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")) ), REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<float>(std::stof("-0X1.99999Cp+4"), std::stof("0x1.99999Ap-4")) ), REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")));

    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D) ), REP<double>(-DNORM_MIN_D, -DNORM_MIN_D));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<double>(-DNORM_MIN_D, DNORM_MIN_D) ), REP<double>(-DNORM_MIN_D, DNORM_MIN_D));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<double>(DNORM_MIN_D, DNORM_MIN_D) ), REP<double>(DNORM_MIN_D, DNORM_MIN_D));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<float>(DNORM_MIN_F, DNORM_MIN_F) ), REP<double>(DNORM_MIN_F, DNORM_MIN_F));

    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<double>(-MAX_D, -MAX_D) ), REP<double>(-MAX_D, -MAX_D));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<double>(-MAX_D, MAX_D) ), REP<double>(-MAX_D, MAX_D));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<double>(MAX_D, MAX_D) ), REP<double>(MAX_D, MAX_D));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<float>(MAX_F, MAX_F) ), REP<double>(MAX_F, MAX_F));

    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<double>(-INF_D, INF_D) ), REP<double>(-INF_D, INF_D));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP<float>(-INF_F, INF_F) ), REP<double>(-INF_D, INF_D));

    BOOST_CHECK( F<double>::is_empty(F<double>::convert_hull( REP<double>(NAN_D, NAN_D) )));
    BOOST_CHECK( F<double>::is_empty(F<double>::convert_hull( REP<float>(NAN_D, NAN_D) )));

    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")) ), REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")) ), REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")) ), REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")) ), REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<float>(std::stof("-0X1.99999Cp+4"), std::stof("0x1.99999Ap-4")) ), REP<float>(std::stof("-0X1.99999Cp+4"), std::stof("0x1.99999Ap-4")));

    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D) ), REP<float>(-DNORM_MIN_F,+0.0));
    BOOST_CHECK( !std::signbit( F<float>::convert_hull( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D) ).second ));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<double>(-DNORM_MIN_D, DNORM_MIN_D) ), REP<float>(-DNORM_MIN_F, DNORM_MIN_F));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<double>(DNORM_MIN_D, DNORM_MIN_D) ), REP<float>(-0.0, DNORM_MIN_F));
    BOOST_CHECK( std::signbit( F<float>::convert_hull( REP<double>(DNORM_MIN_D, DNORM_MIN_D) ).first ));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<float>(DNORM_MIN_F, DNORM_MIN_F) ), REP<float>(DNORM_MIN_F, DNORM_MIN_F));

    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<double>(-MAX_D, -MAX_D) ), REP<float>(-INF_F, -MAX_F));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<double>(-MAX_D, MAX_D) ), REP<float>(-INF_F, INF_F));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<double>(MAX_D, MAX_D) ), REP<float>(MAX_F, INF_F));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<float>(MAX_F, MAX_F) ), REP<float>(MAX_F, MAX_F));

    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<double>(-INF_D, INF_D) ), REP<float>(-INF_F, INF_F));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP<float>(-INF_F, INF_F) ), REP<float>(-INF_F, INF_F));

    BOOST_CHECK( F<float>::is_empty(F<float>::convert_hull( REP<double>(NAN_D, NAN_D) )));
    BOOST_CHECK( F<float>::is_empty(F<float>::convert_hull( REP<float>(NAN_D, NAN_D) )));
}


BOOST_AUTO_TEST_CASE(minimal_convert_hull_dec_test)
{
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")), DEC:trv) ), REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")), DEC:trv));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC:com) ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC:com));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")), DEC:dac) ), REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")), DEC:dac));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC:def) ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC:def));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<float>( REP<float>(std::stof("-0X1.99999Cp+4"), std::stof("0x1.99999Ap-4")), DEC:trv) ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC:trv));

    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<double>( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC:trv) ), REP_DEC<double>( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC:trv));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<double>( REP<double>(-DNORM_MIN_D, DNORM_MIN_D), DEC:trv) ), REP_DEC<double>( REP<double>(-DNORM_MIN_D, DNORM_MIN_D), DEC:trv));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<double>( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC:trv) ), REP_DEC<double>( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC:trv));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<float>( REP<float>(DNORM_MIN_F, DNORM_MIN_F), DEC:trv) ), REP_DEC<double>( REP<double>(DNORM_MIN_F, DNORM_MIN_F), DEC:trv));

    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<double>( REP<double>(-MAX_D, -MAX_D), DEC:trv) ), REP_DEC<double>( REP<double>(-MAX_D, -MAX_D), DEC:trv));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<double>( REP<double>(-MAX_D, MAX_D), DEC:trv) ), REP_DEC<double>( REP<double>(-MAX_D, MAX_D), DEC:trv));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<double>( REP<double>(MAX_D, MAX_D), DEC:trv) ), REP_DEC<double>( REP<double>(MAX_D, MAX_D), DEC:trv));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<float>( REP<float>(MAX_F, MAX_F), DEC:trv) ), REP_DEC<double>( REP<double>(MAX_F, MAX_F), DEC:trv));

    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC:trv) ), REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC:trv));
    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC:trv) ), REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC:trv));

    BOOST_CHECK( F<double>::is_empty(F<double>::convert_hull( REP_DEC<double>(REP<double>(NAN_D, NAN_D), DEC:trv) )));
    BOOST_CHECK( F<double>::is_empty(F<double>::convert_hull( REP_DEC<float>(REP<float>(NAN_D, NAN_D), DEC:trv) )));

    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")), DEC:trv) ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC:trv));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC:com) ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC:com));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")), DEC:dac) ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC:dac));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC:def) ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC:def));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<float>( REP<float>(std::stof("-0X1.99999Cp+4"), std::stof("0x1.99999Ap-4")), DEC:trv) ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999Cp+4"), std::stof("0x1.99999Ap-4")), DEC:trv));

    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC:trv) ), REP_DEC<float>( REP<float>(-DNORM_MIN_F,+0.0), DEC:trv));
    BOOST_CHECK( !std::signbit( F<float>::convert_hull( REP_DEC<double>( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC:trv) ).first.second ));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(-DNORM_MIN_D, DNORM_MIN_D), DEC:trv) ), REP_DEC<float>( REP<float>(-DNORM_MIN_F, DNORM_MIN_F), DEC:trv));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC:trv) ), REP_DEC<float>( REP<float>(-0.0, DNORM_MIN_F), DEC:trv));
    BOOST_CHECK( std::signbit( F<float>::convert_hull( REP_DEC<double>( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC:trv) ).first.first ));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<float>( REP<float>(DNORM_MIN_F, DNORM_MIN_F), DEC:trv) ), REP_DEC<float>( REP<float>(DNORM_MIN_F, DNORM_MIN_F), DEC:trv));

    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(-MAX_D, -MAX_D), DEC:def) ), REP_DEC<float>( REP<float>(-INF_F, -MAX_F), DEC:def));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(-MAX_D, MAX_D), DEC:trv) ), REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC:trv));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(MAX_D, MAX_D), DEC:dac) ), REP_DEC<float>( REP<float>(MAX_F, INF_F), DEC:dac));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<float>( REP<float>(MAX_F, MAX_F), DEC:trv) ), REP_DEC<float>( REP<float>(MAX_F, MAX_F), DEC:trv));

    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(-MAX_D, -MAX_D), DEC:com) ), REP_DEC<float>( REP<float>(-INF_F, -MAX_F), DEC:dac));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(-MAX_D, MAX_D), DEC:com) ), REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC:dac));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(MAX_D, MAX_D), DEC:com) ), REP_DEC<float>( REP<float>(MAX_F, INF_F), DEC:dac));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<float>( REP<float>(MAX_F, MAX_F), DEC:com) ), REP_DEC<float>( REP<float>(MAX_F, MAX_F), DEC:com));

    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC:trv) ), REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC:trv));
    BOOST_CHECK_EQUAL(F<float>::convert_hull( REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC:trv) ), REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC:trv));

    BOOST_CHECK( F<float>::is_empty(F<float>::convert_hull( REP_DEC<double>(REP<double>(NAN_D, NAN_D), DEC:trv) )));
    BOOST_CHECK( F<float>::is_empty(F<float>::convert_hull( REP_DEC<float>(REP<float>(NAN_D, NAN_D), DEC:trv) )));

    BOOST_CHECK_EQUAL(F<double>::convert_hull( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC:com) ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC:com));
}
