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

#define BOOST_TEST_MODULE "Integration: Forward-mode elementary functions [infsup/interval, infsup/decorated_interval, p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include <limits>

#include "p1788/p1788.hpp"


const double INF_D = std::numeric_limits<double>::infinity();
const double NaN_D = std::numeric_limits<double>::quiet_NaN();
const double MAX_D = std::numeric_limits<double>::max();
const double MIN_D = std::numeric_limits<double>::min();

const double INF_F = std::numeric_limits<float>::infinity();
const double NaN_F = std::numeric_limits<float>::quiet_NaN();
const double MAX_F = std::numeric_limits<float>::max();
const double MIN_F = std::numeric_limits<float>::min();


template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

typedef p1788::decoration::decoration DEC;

BOOST_AUTO_TEST_CASE(integration_pos_test)
{
    BOOST_CHECK_EQUAL( pos(I<double>(MIN_D, 2.0)), I<double>(MIN_D, 2.0) );
    BOOST_CHECK_EQUAL( +I<double>(MIN_D, 2.0), I<double>(MIN_D, 2.0) );
    BOOST_CHECK_EQUAL( I<double>::pos(I<double>(MIN_D, 2.0)), I<double>(MIN_D, 2.0) );
    BOOST_CHECK_EQUAL( I<float>::pos(I<double>(std::stod("-0X1.99999C0000000p+4"), MAX_D)), I<float>(std::stof("-0X1.99999CP+4"), INF_F) );


    BOOST_CHECK_EQUAL( pos(DI<double>(MIN_D, 2.0)), DI<double>(MIN_D, 2.0) );
    BOOST_CHECK_EQUAL( decoration( pos(DI<double>(MIN_D, 2.0)) ), DEC::com );
    BOOST_CHECK_EQUAL( +DI<double>(MIN_D, 2.0, DEC::def), DI<double>(MIN_D, 2.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( +DI<double>(MIN_D, 2.0, DEC::def) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<double>::pos(DI<double>(MIN_D, 2.0)), DI<double>(MIN_D, 2.0) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::pos(DI<double>(MIN_D, 2.0))), DEC::com );
    BOOST_CHECK_EQUAL( decoration( DI<float>::pos(DI<double>(std::stod("-0X1.99999C0000000p+4"), MAX_D, DEC::com)) ), DEC::dac );
}


BOOST_AUTO_TEST_CASE(integration_neg_test)
{
    BOOST_CHECK_EQUAL( neg(I<double>(MIN_D, 2.0)), I<double>(-2.0, -MIN_D) );
    BOOST_CHECK_EQUAL( -I<double>(MIN_D, 2.0), I<double>(-2.0, -MIN_D) );
    BOOST_CHECK_EQUAL( I<double>::neg(I<double>(MIN_D, 2.0)), I<double>(-2.0, -MIN_D) );
    BOOST_CHECK_EQUAL( I<float>::neg(I<double>(std::stod("-0X1.99999C0000000p+4"), MAX_D)), I<float>(-INF_F, std::stof("0X1.99999CP+4")) );


    BOOST_CHECK_EQUAL( neg(DI<double>(MIN_D, 2.0)), DI<double>(-2.0, -MIN_D) );
    BOOST_CHECK_EQUAL( decoration( neg(DI<double>(MIN_D, 2.0)) ), DEC::com );
    BOOST_CHECK_EQUAL( -DI<double>(MIN_D, 2.0, DEC::def), DI<double>(-2.0, -MIN_D, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( -DI<double>(MIN_D, 2.0, DEC::def) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<double>::neg(DI<double>(MIN_D, 2.0)), DI<double>(-2.0, -MIN_D) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::neg(DI<double>(MIN_D, 2.0)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<float>::neg(DI<double>(std::stod("-0X1.99999C0000000p+4"), MAX_D, DEC::com)), DI<float>(-INF_F, std::stof("0X1.99999CP+4"), DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::neg(DI<double>(std::stod("-0X1.99999C0000000p+4"), MAX_D, DEC::com)) ), DEC::dac );
}


BOOST_AUTO_TEST_CASE(integration_add_test)
{
    BOOST_CHECK_EQUAL( add(I<double>(1.0, 2.0), I<double>(3.0, 4.0)), I<double>(4.0, 6.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0, 2.0) + I<double>(-3.0, 4.0), I<double>(-4.0, 6.0) );
    BOOST_CHECK_EQUAL( I<double>::add(I<double>(10.0, 12.0), I<double>(-3.0, -1.0)), I<double>(7.0, 11.0) );
    BOOST_CHECK_EQUAL( I<float>::add(I<double>(10.0, 12.0), I<float>(-3.0f, -1.0f)), I<float>(7.0f, 11.0f) );

    BOOST_CHECK_EQUAL( add(DI<double>(1.0, 2.0), DI<double>(3.0, 4.0)), DI<double>(4.0, 6.0, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( add(DI<double>(1.0, 2.0), DI<double>(3.0, 4.0)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>(-1.0, 2.0) + DI<double>(-MAX_D, 4.0), DI<double>(-INF_D, 6.0, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<double>(-1.0, 2.0) + DI<double>(-MAX_D, 4.0) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<double>::add(DI<double>(10.0, 12.0, DEC::def), DI<double>(-3.0, -1.0, DEC::dac)), DI<double>(7.0, 11.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::add(DI<double>(10.0, 12.0, DEC::def), DI<double>(-3.0, -1.0, DEC::dac)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::add(DI<double>(10.0, 12.0), DI<float>(-3.0f, -1.0f)), DI<float>(7.0f, 11.0f, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::add(DI<double>(10.0, 12.0), DI<float>(-3.0f, -1.0f)) ), DEC::com );
}

BOOST_AUTO_TEST_CASE(integration_sub_test)
{
    BOOST_CHECK_EQUAL( sub(I<double>(1.0, 2.0), I<double>(3.0, 4.0)), I<double>(-3.0, -1.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0, 2.0) - I<double>(-3.0, 4.0), I<double>(-5.0, 5.0) );
    BOOST_CHECK_EQUAL( I<double>::sub(I<double>(10.0, 12.0), I<double>(-3.0, -1.0)), I<double>(11.0, 15.0) );
    BOOST_CHECK_EQUAL( I<float>::sub(I<double>(10.0, 12.0), I<float>(-3.0f, -1.0f)), I<float>(11.0f, 15.0f) );

    BOOST_CHECK_EQUAL( sub(DI<double>(1.0, 2.0), DI<double>(3.0, 4.0)), DI<double>(-3.0, -1.0, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( sub(DI<double>(1.0, 2.0), DI<double>(3.0, 4.0)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>(-1.0, 2.0) - DI<double>(-MAX_D, 4.0), DI<double>(-5.0, INF_D, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<double>(-1.0, 2.0) - DI<double>(-MAX_D, 4.0) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<double>::sub(DI<double>(10.0, 12.0, DEC::def), DI<double>(-3.0, -1.0, DEC::dac)), DI<double>(11.0, 15.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::sub(DI<double>(10.0, 12.0, DEC::def), DI<double>(-3.0, -1.0, DEC::dac)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::sub(DI<double>(10.0, 12.0), DI<float>(-3.0f, -1.0f)), DI<float>(11.0f, 15.0f, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::sub(DI<double>(10.0, 12.0), DI<float>(-3.0f, -1.0f)) ), DEC::com );
}

BOOST_AUTO_TEST_CASE(integration_mul_test)
{
    BOOST_CHECK_EQUAL( mul(I<double>(1.0, 2.0), I<double>(3.0, 4.0)), I<double>(3.0, 8.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0, 2.0) * I<double>(-3.0, 4.0), I<double>(-6.0, 8.0) );
    BOOST_CHECK_EQUAL( I<double>::mul(I<double>(10.0, 12.0), I<double>(-3.0, -1.0)), I<double>(-36.0, -10.0) );
    BOOST_CHECK_EQUAL( I<float>::mul(I<double>(10.0, 12.0), I<float>(-3.0f, -1.0f)), I<float>(-36.0f, -10.0f) );

    BOOST_CHECK_EQUAL( mul(DI<double>(1.0, 2.0), DI<double>(3.0, 4.0)), DI<double>(3.0, 8.0, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( mul(DI<double>(1.0, 2.0), DI<double>(3.0, 4.0)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>(-1.0, 2.0) * DI<double>(-MAX_D, 4.0), DI<double>(-INF_D, MAX_D, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<double>(-1.0, 2.0) * DI<double>(-MAX_D, 4.0) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<double>::mul(DI<double>(10.0, 12.0, DEC::def), DI<double>(-3.0, -1.0, DEC::dac)), DI<double>(-36.0, -10.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::mul(DI<double>(10.0, 12.0, DEC::def), DI<double>(-3.0, -1.0, DEC::dac)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::mul(DI<double>(10.0, 12.0), DI<float>(-3.0f, -1.0f)), DI<float>(-36.0f, -10.0f, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::mul(DI<double>(10.0, 12.0), DI<float>(-3.0f, -1.0f)) ), DEC::com );
}

BOOST_AUTO_TEST_CASE(integration_div_test)
{
    BOOST_CHECK_EQUAL( div(I<double>(-0.0,30.0), I<double>(-5.0, -3.0)), I<double>(-10.0, 0.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(0.0, 3.0), I<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( I<double>::div(I<double>(-2.0,-1.0), I<double>(-10.0, -3.0)), I<double>(std::stod("0X1.9999999999999P-4"),std::stod("0X1.5555555555556P-1")) );
    BOOST_CHECK_EQUAL( I<float>::div(I<double>(-2.0,-1.0), I<float>(-10.0f, -3.0f)), I<float>(std::stof("0X1.999998P-4"),std::stof("0X1.555556P-1")) );

    BOOST_CHECK_EQUAL( div(DI<double>(-0.0,30.0), DI<double>(-5.0, -3.0)), DI<double>(-10.0, 0.0, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( div(DI<double>(-0.0,30.0), DI<double>(-5.0, -3.0)) ), DEC::com );
    BOOST_CHECK_EQUAL( div(DI<double>(-0.0,30.0), DI<double>(-5.0, -MIN_D)), DI<double>(-INF_D, 0.0, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( div(DI<double>(-0.0,30.0), DI<double>(-5.0, -MIN_D)) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<double>(-30.0,0.0) / DI<double>(0.0, 3.0), DI<double>(-INF_D,0.0, DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>(-30.0,0.0) / DI<double>(0.0, 3.0) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::div(DI<double>(-2.0,-1.0, DEC::def), DI<double>(-10.0, -3.0, DEC::dac)), DI<double>(std::stod("0X1.9999999999999P-4"),std::stod("0X1.5555555555556P-1"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::div(DI<double>(-2.0,-1.0, DEC::def), DI<double>(-10.0, -3.0, DEC::dac)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::div(DI<double>(-2.0,-1.0), DI<float>(-10.0f, -3.0f)), DI<float>(std::stof("0X1.999998P-4"),std::stof("0X1.555556P-1"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::div(DI<double>(-2.0,-1.0), DI<float>(-10.0f, -3.0f)) ), DEC::com );
}


BOOST_AUTO_TEST_CASE(integration_recip_test)
{
    BOOST_CHECK_EQUAL( recip(I<double>(-50.0, -10.0)), I<double>(std::stod("-0X1.999999999999AP-4"),std::stod("-0X1.47AE147AE147AP-6")) );
    BOOST_CHECK_EQUAL( I<double>::recip(I<double>(-10.0, 0.0)), I<double>(-INF_D,std::stod("-0X1.9999999999999P-4")) );
    BOOST_CHECK_EQUAL( I<float>::recip(I<double>(-INF_D, -10.0)), I<float>(std::stof("-0X1.99999AP-4"),0.0f) );

    BOOST_CHECK_EQUAL( recip(DI<double>(-10.0, 0.0)), DI<double>(-INF_D,std::stod("-0X1.9999999999999P-4"), DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( recip(DI<double>(-10.0, 0.0)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::recip(DI<double>(-MAX_D, -MIN_D)), DI<double>(std::stod("-0X1P+1022"),std::stod("-0X0.4P-1022"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::recip(DI<double>(-MAX_D, -MIN_D)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<float>::recip(DI<double>(-MAX_D, -MIN_D)), DI<float>(-INF_F, 0.0f, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::recip(DI<double>(-MAX_D, -MIN_D)) ), DEC::dac );
}

BOOST_AUTO_TEST_CASE(integration_sqr_test)
{
    BOOST_CHECK_EQUAL( sqr(I<double>(-5.0, -1.0)), I<double>(1.0,25.0) );
    BOOST_CHECK_EQUAL( I<double>::sqr(I<double>(-10.0, 0.0)), I<double>(0.0,100.0) );
    BOOST_CHECK_EQUAL( I<float>::sqr(I<double>(5.0, 2.0e19)), I<float>(25.0f, INF_F) );

    BOOST_CHECK_EQUAL( sqr(DI<double>(-5.0, -1.0)), DI<double>(1.0,25.0, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( sqr(DI<double>(-5.0, -1.0)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::sqr(DI<double>(-10.0, 0.0, DEC::def)), DI<double>(0.0,100.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::sqr(DI<double>(-10.0, 0.0, DEC::def)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::sqr(DI<double>(5.0, 2.0e19)), DI<float>(25.0f, INF_F, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::sqr(DI<double>(5.0, 2.0e19)) ), DEC::dac );
}


BOOST_AUTO_TEST_CASE(integration_sqrt_test)
{
    BOOST_CHECK_EQUAL( sqrt(I<double>(1.0,25.0)), I<double>(1.0,5.0) );
    BOOST_CHECK_EQUAL( I<double>::sqrt(I<double>(MIN_D, 100.0)), I<double>(std::stod("0x2p-512"),10.0) );
    BOOST_CHECK_EQUAL( I<float>::sqrt(I<double>(MIN_D, 100.0)), I<float>(0.0f, 10.0f) );

    BOOST_CHECK_EQUAL( sqrt(DI<double>(-5.0, 25.0)), DI<double>(0.0,5.0, DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( sqrt(DI<double>(-5.0, 25.0)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::sqrt(DI<double>(MIN_D, 100.0, DEC::def)), DI<double>(std::stod("0x2p-512"), 10.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::sqrt(DI<double>(MIN_D, 100.0, DEC::def)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::sqrt(DI<double>(MIN_D, 100.0)), DI<float>(0.0f, 10.0f, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::sqrt(DI<double>(MIN_D, 100.0)) ), DEC::com );
}

BOOST_AUTO_TEST_CASE(integration_fma_test)
{
    BOOST_CHECK_EQUAL( fma(I<double>(-0.5,-0.1), I<double>(-INF_D, 3.0), I<double>(-0.1,0.1)), I<double>(std::stod("-0X1.999999999999AP+0"),INF_D) );
    BOOST_CHECK_EQUAL( I<double>::fma(I<double>(1.0,2.0), I<double>(1.0, MAX_D), I<double>(0.0,1.0)), I<double>(1.0,INF_D ) );
    BOOST_CHECK_EQUAL( I<float>::fma(I<double>(0.1,0.5), I<double>(-5.0, 3.0), I<double>(-0.1,0.1)), I<float>(std::stof("-0X1.4CCCCEP+1"),std::stof("0X1.99999AP+0")) );

    BOOST_CHECK_EQUAL( fma(DI<double>(-0.5,-0.1, DEC::com), DI<double>(-INF_D, 3.0, DEC::dac), DI<double>(-0.1,0.1, DEC::com)), DI<double>(std::stod("-0X1.999999999999AP+0"),INF_D, DEC::dac)  );
    BOOST_CHECK_EQUAL( decoration( fma(DI<double>(-0.5,-0.1, DEC::com), DI<double>(-INF_D, 3.0, DEC::dac), DI<double>(-0.1,0.1, DEC::com)) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<double>::fma(DI<double>(1.0,2.0, DEC::com), DI<double>(1.0, MAX_D, DEC::com), DI<double>(0.0,1.0, DEC::com)), DI<double>(1.0,INF_D, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::fma(DI<double>(1.0,2.0, DEC::com), DI<double>(1.0, MAX_D, DEC::com), DI<double>(0.0,1.0, DEC::com)) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<float>::fma(DI<double>(0.1,0.5, DEC::com), DI<double>(-5.0, 3.0, DEC::dac), DI<double>(-0.1,0.1, DEC::def)), DI<float>(std::stof("-0X1.4CCCCEP+1"),std::stof("0X1.99999AP+0"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::fma(DI<double>(0.1,0.5, DEC::com), DI<double>(-5.0, 3.0, DEC::dac), DI<double>(-0.1,0.1, DEC::def)) ), DEC::def );
}



