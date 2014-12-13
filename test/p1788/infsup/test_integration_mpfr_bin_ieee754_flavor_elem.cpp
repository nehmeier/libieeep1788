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


BOOST_AUTO_TEST_CASE(integration_pown_test)
{
    BOOST_CHECK_EQUAL( pown(I<double>(1.0,5.0), 3), I<double>(1.0,125.0) );
    BOOST_CHECK_EQUAL( I<double>::pown(I<double>(-1.0, 100.0), -7), I<double>(-INF_D, INF_D) );
    BOOST_CHECK_EQUAL( I<float>::pown(I<double>(0.01,2.33), 2), I<float>(std::stof("0x1.a36e2ep-14"),std::stof("0x1.5b731ap+2")) );

    BOOST_CHECK_EQUAL( pown(DI<double>(-5.0, 25.0, DEC::def), 2), DI<double>(0.0,625.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( pown(DI<double>(-5.0, 25.0, DEC::def), 2) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<double>::pown(DI<double>(MIN_D, 1.0, DEC::com), -8), DI<double>(1.0, INF_D, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::pown(DI<double>(MIN_D, 1.0, DEC::com), -8) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<float>::pown(DI<double>(-1.0, 1.0), -3), DI<float>(-INF_D, INF_D, DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::pown(DI<double>(-1.0, 1.0), -3) ), DEC::trv );
}



BOOST_AUTO_TEST_CASE(integration_pow_test)
{
    BOOST_CHECK_EQUAL( pow(I<double>(0.1,0.5), I<double>(0.0,1.0)), I<double>(std::stod("0X1.999999999999AP-4"),1.0) );
    BOOST_CHECK_EQUAL( I<double>::pow(I<double>(0.5,1.5), I<double>(-1.0,0.0)), I<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1P+1")) );
    BOOST_CHECK_EQUAL( I<float>::pow(I<double>(0.5,1.5), I<double>(-0.1,0.1)), I<float>(std::stof("0X1.DDB680P-1"),std::stof("0X1.125FCP+0")) );

    BOOST_CHECK_EQUAL( pow(DI<double>(0.1,1.0, DEC::com), DI<double>(0.0,2.5, DEC::com)), DI<double>(std::stod("0X1.9E7C6E43390B7P-9"),1.0, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( pow(DI<double>(0.1,1.0, DEC::com), DI<double>(0.0,2.5, DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::pow(DI<double>(0.0,1.5, DEC::com), DI<double>(0.1,2.5, DEC::dac)), DI<double>(0.0,std::stod("0X1.60B9FD68A4555P+1"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::pow(DI<double>(0.0,1.5, DEC::com), DI<double>(0.1,2.5, DEC::dac)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::pow(DI<double>(-0.0,0.5), DI<double>(0.1,0.1)), DI<float>(0.0f,std::stof("0X1.DDB682P-1"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::pow(DI<double>(-0.0,0.5), DI<double>(0.1,0.1)) ), DEC::def );
}



BOOST_AUTO_TEST_CASE(integration_exp_test)
{
    BOOST_CHECK_EQUAL( exp(I<double>(-INF_D,0.0)), I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( I<double>::exp(I<double>(std::stod("0X1.62E42FEFA39FP+9"),std::stod("0X1.62E42FEFA39FP+9"))), I<double>(std::stod("0X1.FFFFFFFFFFFFFP+1023"), INF_D) );
    BOOST_CHECK_EQUAL( I<float>::exp(I<double>(std::stod("0X1.62E42FEFA39FP+9"),std::stod("0X1.62E42FEFA39FP+9"))), I<float>(MAX_F,INF_F) );

    BOOST_CHECK_EQUAL( exp(DI<double>(std::stod("0X1.62E42FEFA39FP+9"),std::stod("0X1.62E42FEFA39FP+9"), DEC::com)), DI<double>(std::stod("0X1.FFFFFFFFFFFFFP+1023"),INF_D, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( exp(DI<double>(std::stod("0X1.62E42FEFA39FP+9"),std::stod("0X1.62E42FEFA39FP+9"), DEC::com)) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<double>::exp(DI<double>(0.0,std::stod("0X1.62E42FEFA39EP+9"), DEC::def)), DI<double>(1.0,std::stod("0X1.FFFFFFFFFC32BP+1023"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::exp(DI<double>(0.0,std::stod("0X1.62E42FEFA39EP+9"), DEC::def)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::exp(DI<double>(std::stod("0X1.62E42FEFA39FP+9"),std::stod("0X1.62E42FEFA39FP+9"))), DI<float>(MAX_F,INF_F, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::exp(DI<double>(std::stod("0X1.62E42FEFA39FP+9"),std::stod("0X1.62E42FEFA39FP+9"))) ), DEC::dac );
}


BOOST_AUTO_TEST_CASE(integration_exp2_test)
{
    BOOST_CHECK_EQUAL( exp2(I<double>(-INF_D,1024.0)), I<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( I<double>::exp2(I<double>(-1022.0,1023.0)), I<double>(std::stod("0X1P-1022"),std::stod("0X1P+1023")) );
    BOOST_CHECK_EQUAL( I<float>::exp2(I<double>(1024.0,1024.0)), I<float>(MAX_F,INF_F) );

    BOOST_CHECK_EQUAL( exp2(DI<double>(1024.0,1024.0, DEC::com)), DI<double>(std::stod("0X1.FFFFFFFFFFFFFP+1023"),INF_D, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( exp2(DI<double>(1024.0,1024.0, DEC::com)) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<double>::exp2(DI<double>(std::stod("0X1.87F42B972949CP-1"),std::stod("0X1.8B55484710029P+6"), DEC::def)), DI<double>(std::stod("0X1.B333333333332P+0"),std::stod("0X1.C81FD88228B4FP+98"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::exp2(DI<double>(std::stod("0X1.87F42B972949CP-1"),std::stod("0X1.8B55484710029P+6"), DEC::def)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::exp2(DI<double>(1024.0,1024.0)), DI<float>(MAX_F,INF_F, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::exp2(DI<double>(1024.0,1024.0)) ), DEC::dac );
}


BOOST_AUTO_TEST_CASE(integration_exp10_test)
{
    BOOST_CHECK_EQUAL( exp10(I<double>(std::stod("0X1.34413509F79FFP+8"),std::stod("0X1.34413509F79FFP+8"))), I<double>(std::stod("0X1.FFFFFFFFFFFFFP+1023"),INF_D) );
    BOOST_CHECK_EQUAL( I<double>::exp10(I<double>(std::stod("-0X1.22P+7"),0.0)), I<double>(std::stod("0X1.3FAAC3E3FA1F3P-482"),1.0) );
    BOOST_CHECK_EQUAL( I<float>::exp10(I<double>(std::stod("0X1.34413509F79FFP+8"),std::stod("0X1.34413509F79FFP+8"))), I<float>(MAX_F,INF_F) );

    BOOST_CHECK_EQUAL( exp10(DI<double>(std::stod("0X1.34413509F79FFP+8"),std::stod("0X1.34413509F79FFP+8"), DEC::com)), DI<double>(std::stod("0X1.FFFFFFFFFFFFFP+1023"),INF_D, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( exp10(DI<double>(std::stod("0X1.34413509F79FFP+8"),std::stod("0X1.34413509F79FFP+8"), DEC::com)) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<double>::exp10(DI<double>(std::stod("0X1.87F42B972949CP-1"),std::stod("0X1.8B55484710029P+6"), DEC::def)), DI<double>(std::stod("0X1.75014B7296807P+2"),std::stod("0X1.3EEC1D47DFB2BP+328"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::exp10(DI<double>(std::stod("0X1.87F42B972949CP-1"),std::stod("0X1.8B55484710029P+6"), DEC::def)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::exp10(DI<double>(std::stod("0X1.34413509F79FFP+8"),std::stod("0X1.34413509F79FFP+8"))), DI<float>(MAX_F, INF_D, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::exp10(DI<double>(std::stod("0X1.34413509F79FFP+8"),std::stod("0X1.34413509F79FFP+8"))) ), DEC::dac );
}


BOOST_AUTO_TEST_CASE(integration_log_test)
{
    BOOST_CHECK_EQUAL( log(I<double>(std::stod("0X1.5BF0A8B145769P+1"),std::stod("0X1.5BF0A8B145769P+1"))), I<double>(std::stod("0X1.FFFFFFFFFFFFFP-1"),std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( I<double>::log(I<double>(std::stod("0X1.5BF0A8B145769P+1"),32.0)), I<double>(std::stod("0X1.FFFFFFFFFFFFFP-1"),std::stod("0X1.BB9D3BEB8C86CP+1")) );
    BOOST_CHECK_EQUAL( I<float>::log(I<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.CP+1"))), I<float>(std::stof("-0x1.26bb1cp+1"),std::stof("0x1.40b514p+0")) );

    BOOST_CHECK_EQUAL( log(DI<double>(MIN_D,MAX_D, DEC::com)), DI<double>(std::stod("-0X1.6232BDD7ABCD3P+9"),std::stod("0X1.62E42FEFA39FP+9"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( log(DI<double>(MIN_D,MAX_D, DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::log(DI<double>(0.0,1.0, DEC::com)), DI<double>(-INF_D,0.0, DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::log(DI<double>(0.0,1.0, DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::log(DI<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.CP+1"))), DI<float>(std::stof("-0x1.26bb1cp+1"),std::stof("0x1.40b514p+0"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::log(DI<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.CP+1"))) ), DEC::com );
}


BOOST_AUTO_TEST_CASE(integration_log2_test)
{
    BOOST_CHECK_EQUAL( log2(I<double>(MIN_D,MAX_D)), I<double>(-1022.0,1024.0) );
    BOOST_CHECK_EQUAL( I<double>::log2(I<double>(std::stod("0X1.B333333333333P+0"),std::stod("0X1.C81FD88228B2FP+98"))), I<double>(std::stod("0X1.87F42B972949CP-1"),std::stod("0X1.8B55484710029P+6")) );
    BOOST_CHECK_EQUAL( I<float>::log2(I<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.CP+1"))), I<float>(std::stof("-0x1.a934f2p+1"),std::stod("0x1.ceaedp+0")) );

    BOOST_CHECK_EQUAL( log2(DI<double>(MIN_D,MAX_D, DEC::com)), DI<double>(-1022.0,1024.0, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( log2(DI<double>(MIN_D,MAX_D, DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::log2(DI<double>(2.0,32.0, DEC::def)), DI<double>(1.0, 5.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::log2(DI<double>(2.0,32.0, DEC::def)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::log2(DI<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.CP+1"))), DI<float>(std::stof("-0x1.a934f2p+1"),std::stod("0x1.ceaedp+0"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::log2(DI<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.CP+1"))) ), DEC::com );
}


BOOST_AUTO_TEST_CASE(integration_log10_test)
{
    BOOST_CHECK_EQUAL( log10(I<double>(MIN_D,MAX_D)), I<double>(std::stod("-0X1.33A7146F72A42P+8") ,std::stod("0X1.34413509F79FFP+8")) );
    BOOST_CHECK_EQUAL( I<double>::log10(I<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4"))), I<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")) );
    BOOST_CHECK_EQUAL( I<float>::log10(I<double>(MIN_D,MAX_D)), I<float>(std::stof("-0x1.33a716p+8") ,std::stod("0x1.344136p+8")) );

    BOOST_CHECK_EQUAL( log10(DI<double>(MIN_D,MAX_D, DEC::def)), DI<double>(std::stod("-0X1.33A7146F72A42P+8") ,std::stod("0X1.34413509F79FFP+8"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( log10(DI<double>(MIN_D,MAX_D, DEC::def)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<double>::log10(DI<double>(0.0,MAX_D, DEC::com)), DI<double>(-INF_D,std::stod("0X1.34413509F79FFP+8"), DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::log10(DI<double>(0.0,MAX_D, DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::log10(DI<double>(MIN_D,MAX_D)), DI<float>(std::stof("-0x1.33a716p+8") ,std::stod("0x1.344136p+8"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::log10(DI<double>(MIN_D,MAX_D)) ), DEC::com );
}


BOOST_AUTO_TEST_CASE(integration_sin_test)
{
    BOOST_CHECK_EQUAL( sin(I<double>(0.0,INF_D)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( I<double>::sin(I<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D18P+0"))), I<double>(std::stod("0X1.FFFFFFFFFFFFFP-1"),std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( I<float>::sin(I<double>(std::stod("0X1.921FB54442D18P+1"),std::stod("0X1.921FB54442D19P+1"))), I<float>(std::stof("-0x1.72cedp-52"),std::stof("0x1.1a6264p-53")) );

    BOOST_CHECK_EQUAL( sin(DI<double>(std::stod("-0X1.921FB54442D18P+1"),std::stod("-0X1.921FB54442D18P+0"), DEC::def)), DI<double>(std::stod("-0X1P+0"),std::stod("-0X1.1A62633145C06P-53"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( sin(DI<double>(std::stod("-0X1.921FB54442D18P+1"),std::stod("-0X1.921FB54442D18P+0"), DEC::def)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<double>::sin(DI<double>(-INF_D,-0.0, DEC::dac)), DI<double>(-1.0,1.0, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::sin(DI<double>(-INF_D,-0.0, DEC::dac)) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<float>::sin(DI<double>(std::stod("0X1.921FB54442D18P+1"),std::stod("0X1.921FB54442D19P+1"))), DI<float>(std::stof("-0x1.72cedp-52"),std::stof("0x1.1a6264p-53"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::sin(DI<double>(std::stod("0X1.921FB54442D18P+1"),std::stod("0X1.921FB54442D19P+1"))) ), DEC::com );
}

BOOST_AUTO_TEST_CASE(integration_cos_test)
{
    BOOST_CHECK_EQUAL( cos(I<double>(-INF_D,0.0)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( I<double>::cos(I<double>(0.0,std::stod("0X1.921FB54442D18P+0"))), I<double>(std::stod("0X1.1A62633145C06P-54"),1.0) );
    BOOST_CHECK_EQUAL( I<float>::cos(I<double>(std::stod("-0X1.921FB54442D18P+0"),std::stod("-0X1.921FB54442D18P+0"))), I<float>(std::stof("0X1.1A6262P-54"),std::stof("0X1.1A6264P-54")) );

    BOOST_CHECK_EQUAL( cos(DI<double>(std::stod("-0X1.921FB54442D18P+0"),std::stod("-0X1.921FB54442D18P+0"), DEC::def)), DI<double>(std::stod("0X1.1A62633145C06P-54"),std::stod("0X1.1A62633145C07P-54"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( cos(DI<double>(std::stod("-0X1.921FB54442D18P+0"),std::stod("-0X1.921FB54442D18P+0"), DEC::def)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<double>::cos(DI<double>(0.0,MAX_D, DEC::com)), DI<double>(-1.0,1.0, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::cos(DI<double>(0.0,MAX_D, DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<float>::cos(DI<double>(std::stod("-0X1.921FB54442D18P+0"),std::stod("-0X1.921FB54442D18P+0"))), DI<float>(std::stod("0X1.1A6262P-54"),std::stod("0X1.1A6264P-54"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::cos(DI<double>(std::stod("-0X1.921FB54442D18P+0"),std::stod("-0X1.921FB54442D18P+0"))) ), DEC::com );
}


BOOST_AUTO_TEST_CASE(integration_tan_test)
{
    BOOST_CHECK_EQUAL( tan(I<double>(0.0,INF_D)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::tan(I<double>(0.0,std::stod("0X1.921FB54442D18P+0"))), I<double>(0.0,std::stod("0X1.D02967C31CDB5P+53")) );
    BOOST_CHECK_EQUAL( I<float>::tan(I<double>(std::stod("0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+0"))), I<float>(std::stof("-0x1.617a16p+52"),std::stof("-0x1.617a14p+52")) );

    BOOST_CHECK_EQUAL( tan(DI<double>(0.0,std::stod("0X1.921FB54442D18P+0"),DEC::com)), DI<double>(0.0,std::stod("0X1.D02967C31CDB5P+53"),DEC::com) );
    BOOST_CHECK_EQUAL( decoration( tan(DI<double>(0.0,std::stod("0X1.921FB54442D18P+0"),DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::tan(DI<double>(std::stod("0X1P-51"),std::stod("0X1.921FB54442D19P+1"),DEC::com)), DI<double>(-INF_D,INF_D, DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::tan(DI<double>(std::stod("0X1P-51"),std::stod("0X1.921FB54442D19P+1"),DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::tan(DI<double>(std::stod("0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+0"))), DI<float>(std::stof("-0x1.617a16p+52"),std::stof("-0x1.617a14p+52"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::tan(DI<double>(std::stod("0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+0"))) ), DEC::com );
}



BOOST_AUTO_TEST_CASE(integration_asin_test)
{
    BOOST_CHECK_EQUAL( asin(I<double>(0.0,INF_D)), I<double>(0.0,std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( I<double>::asin(I<double>(std::stod("-0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4"))), I<double>(std::stod("-0X1.9A49276037885P-4"),std::stod("0X1.9A49276037885P-4")) );
    BOOST_CHECK_EQUAL( I<float>::asin(I<double>(-1.0,1.0)), I<float>(std::stof("-0X1.921FB6P+0"),std::stof("0X1.921FB6P+0")) );

    BOOST_CHECK_EQUAL( asin(DI<double>(0.0,INF_D, DEC::dac)), DI<double>(0.0,std::stod("0X1.921FB54442D19P+0"), DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( asin(DI<double>(0.0,INF_D, DEC::dac)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::asin(DI<double>(std::stod("-0X1.51EB851EB851FP-2"),std::stod("0X1.FFFFFFFFFFFFFP-1"), DEC::def)), DI<double>(std::stod("-0X1.585FF6E341C3FP-2"),std::stod("0X1.921FB50442D19P+0"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::asin(DI<double>(std::stod("-0X1.51EB851EB851FP-2"),std::stod("0X1.FFFFFFFFFFFFFP-1"), DEC::def)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::asin(DI<double>(-1.0,1.0)), DI<float>(std::stof("-0X1.921FB6P+0"),std::stof("0X1.921FB6P+0"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::asin(DI<double>(-1.0,1.0)) ), DEC::com );
}

BOOST_AUTO_TEST_CASE(integration_acos_test)
{
    BOOST_CHECK_EQUAL( acos(I<double>(-INF_D,0.0)), I<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+1")) );
    BOOST_CHECK_EQUAL( I<double>::acos(I<double>(-1.0,-1.0)), I<double>(std::stod("0X1.921FB54442D18P+1"),std::stod("0X1.921FB54442D19P+1")) );
    BOOST_CHECK_EQUAL( I<float>::acos(I<double>(-1.0,1.0)), I<float>(0.0f,std::stof("0X1.921FB6P+1")) );

    BOOST_CHECK_EQUAL( acos(DI<double>(0.0,INF_D, DEC::dac)), DI<double>(0.0,std::stod("0X1.921FB54442D19P+0"), DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( acos(DI<double>(0.0,INF_D, DEC::dac)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::acos(DI<double>(std::stod("-0X1.51EB851EB851FP-2"),std::stod("0X1.FFFFFFFFFFFFFP-1"), DEC::def)), DI<double>(std::stod("0X1P-26"),std::stod("0X1.E837B2FD13428P+0"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::acos(DI<double>(std::stod("-0X1.51EB851EB851FP-2"),std::stod("0X1.FFFFFFFFFFFFFP-1"), DEC::def)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::acos(DI<double>(-1.0,1.0)), DI<float>(0.0f,std::stof("0X1.921FB6P+1"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::acos(DI<double>(-1.0,1.0)) ), DEC::com );
}


BOOST_AUTO_TEST_CASE(integration_atan_test)
{
    BOOST_CHECK_EQUAL( atan(I<double>(0.0,INF_D)), I<double>(0.0,std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( I<double>::atan(I<double>(1.0,std::stod("0X1.4C2463567C5ACP+25"))), I<double>(std::stod("0X1.921FB54442D18P-1"),std::stod("0X1.921FB4E19ABD7P+0")) );
    BOOST_CHECK_EQUAL( I<float>::atan(I<double>::entire()), I<float>(std::stof("-0X1.921FB6P+0"),std::stod("0X1.921FB6P+0")) );

    BOOST_CHECK_EQUAL( atan(DI<double>(1.0,std::stod("0X1.4C2463567C5ACP+25"),DEC::trv)), DI<double>(std::stod("0X1.921FB54442D18P-1"),std::stod("0X1.921FB4E19ABD7P+0"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( atan(DI<double>(1.0,std::stod("0X1.4C2463567C5ACP+25"),DEC::trv)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::atan(DI<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"),DEC::com)), DI<double>(std::stod("-0X1.921FB54440CEBP+0"),std::stod("-0X1.91ABE5C1E4C6DP+0"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::atan(DI<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"),DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<float>::atan(DI<double>::entire()), DI<float>(std::stof("-0X1.921FB6P+0"),std::stod("0X1.921FB6P+0"), DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::atan(DI<double>::entire()) ), DEC::dac );
}

BOOST_AUTO_TEST_CASE(integration_atan2_test)
{
    BOOST_CHECK_EQUAL( atan2(I<double>(-2.0, -0.1), I<double>(0.0, 0.0)), I<double>(std::stod("-0X1.921FB54442D19P+0"), std::stod("-0X1.921FB54442D18P+0")) );
    BOOST_CHECK_EQUAL( I<double>::atan2(I<double>(0.0, 1.0), I<double>(0.0, 1.0)), I<double>(0.0,std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( I<float>::atan2(I<double>(-2.0, 0.0), I<double>(-2.0, 0.0)), I<float>(std::stof("-0X1.921FB6P+1"), std::stof("-0X1.921FB4P+0")) );

    BOOST_CHECK_EQUAL( atan2(DI<double>(0.0,0.0,DEC::dac), DI<double>(-2.0,0.0) ), DI<double>(std::stod("0X1.921FB54442D18P+1"), std::stod("0X1.921FB54442D19P+1"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( atan2(DI<double>(0.0,0.0,DEC::dac), DI<double>(-2.0,0.0) ) ), DEC::trv );
    BOOST_CHECK_EQUAL( atan2(DI<double>(-2.0,0.0), DI<double>(-2.0,0.0) ), DI<double>(std::stod("-0X1.921FB54442D19P+1"), std::stod("-0X1.921FB54442D18P+0"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( atan2(DI<double>(-2.0,0.0), DI<double>(-2.0,0.0) ) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::atan2(DI<double>(-2.0, -0.1), DI<double>(-2.0,0.0) ), DI<float>(std::stof("-0X1.8BBAACP+1"), std::stof("-0X1.921FB4P+0"),DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::atan2(DI<double>(-2.0, -0.1), DI<double>(-2.0,0.0) ) ), DEC::com );
}

BOOST_AUTO_TEST_CASE(integration_sinh_test)
{
    BOOST_CHECK_EQUAL( sinh(I<double>(0.0,INF_D)), I<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( I<double>::sinh(I<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"))), I<double>(std::stod("0X1.2CD9FC44EB982P+0"),std::stod("0X1.89BCA168970C6P+432")) );
    BOOST_CHECK_EQUAL( I<float>::sinh(I<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), I<float>(std::stof("-0x1.55edp+0"),std::stof("0x1.3bf73p+2")) );

    BOOST_CHECK_EQUAL( sinh(DI<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"), DEC::com)), DI<double>(std::stod("0X1.2CD9FC44EB982P+0"),std::stod("0X1.89BCA168970C6P+432"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( sinh(DI<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"), DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::sinh(DI<double>(0.0,INF_D, DEC::dac)), DI<double>(0.0,INF_D, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::sinh(DI<double>(0.0,INF_D, DEC::dac)) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<float>::sinh(DI<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"),DEC::trv)), DI<float>(std::stof("-0x1.55edp+0"),std::stof("0x1.3bf73p+2"), DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::sinh(DI<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"),DEC::trv)) ), DEC::trv );
}

BOOST_AUTO_TEST_CASE(integration_cosh_test)
{
    BOOST_CHECK_EQUAL( cosh(I<double>(0.0,INF_D)), I<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( I<double>::cosh(I<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"))), I<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432")) );
    BOOST_CHECK_EQUAL( I<float>::cosh(I<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), I<float>(1.0f,std::stof("0X1.4261D4P+2")) );

    BOOST_CHECK_EQUAL( cosh(DI<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"), DEC::def)), DI<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( cosh(DI<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"), DEC::def)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<double>::cosh(DI<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"), DEC::com)), DI<double>(std::stod("0X1.53045B4F849DEP+815"),INF_D, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::cosh(DI<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"), DEC::com)) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<float>::cosh(DI<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), DI<float>(1.0f,std::stof("0X1.4261D4P+2"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::cosh(DI<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))) ), DEC::com );
}


BOOST_AUTO_TEST_CASE(integration_tanh_test)
{
    BOOST_CHECK_EQUAL( tanh(I<double>(0.0,INF_D)), I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( I<double>::tanh(I<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"))), I<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")) );
    BOOST_CHECK_EQUAL( I<float>::tanh(I<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), I<float>(std::stof("-0X1.99DB02P-1"),std::stof("0X1.F5CF32P-1")) );

    BOOST_CHECK_EQUAL( tanh(DI<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"),DEC::com)), DI<double>(std::stod("0X1.85EFAB514F394P-1"),std::stod("0X1P+0"),DEC::com) );
    BOOST_CHECK_EQUAL( decoration( tanh(DI<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"),DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::tanh(DI<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"),DEC::trv)), DI<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1"), DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::tanh(DI<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"),DEC::trv)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::tanh(DI<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), DI<float>(std::stof("-0X1.99DB02P-1"),std::stof("0X1.F5CF32P-1"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::tanh(DI<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))) ), DEC::com );
}



BOOST_AUTO_TEST_CASE(integration_asinh_test)
{
    BOOST_CHECK_EQUAL( asinh(I<double>(0.0,INF_D)), I<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( I<double>::asinh(I<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"))), I<double>(std::stod("0X1.C34366179D426P-1"),std::stod("0X1.9986127438A87P+2")) );
    BOOST_CHECK_EQUAL( I<float>::asinh(I<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), I<float>(std::stof("-0X1.E693EP-1"),std::stof("0X1.91FDC8P+0")) );

    BOOST_CHECK_EQUAL( asinh(DI<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"), DEC::com)), DI<double>(std::stod("0X1.C34366179D426P-1"),std::stod("0X1.9986127438A87P+2"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( asinh(DI<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"), DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::asinh(DI<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"), DEC::dac)), DI<double>(std::stod("-0X1.BB86380A6CC45P+4"),std::stod("-0X1.C204D8EB20827P+2"), DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::asinh(DI<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"), DEC::dac)) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<float>::asinh(DI<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), DI<float>(std::stof("-0X1.E693EP-1"),std::stof("0X1.91FDC8P+0"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::asinh(DI<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))) ), DEC::com );
}

BOOST_AUTO_TEST_CASE(integration_acosh_test)
{
    BOOST_CHECK_EQUAL( acosh(I<double>(0.0,INF_D)), I<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( I<double>::acosh(I<double>(std::stod("0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), I<double>(std::stod("0X1.C636C1A882F2CP-2"),std::stod("0X1.799C88E79140DP+0")) );
    BOOST_CHECK_EQUAL( I<float>::acosh(I<double>(std::stod("0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), I<float>(std::stof("0X1.C636CP-2"),std::stof("0X1.799C8AP+0")) );

    BOOST_CHECK_EQUAL( acosh(DI<double>(0.9,std::stod("0X1.2C903022DD7AAP+8"), DEC::com)), DI<double>(0.0,std::stod("0X1.9985FB3D532AFP+2"), DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( acosh(DI<double>(0.9,std::stod("0X1.2C903022DD7AAP+8"), DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::acosh(DI<double>(1.0,1.0, DEC::com)), DI<double>(0.0,0.0, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::acosh(DI<double>(1.0,1.0, DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<float>::acosh(DI<double>(std::stod("0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), DI<float>(std::stof("0X1.C636CP-2"),std::stof("0X1.799C8AP+0"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::acosh(DI<double>(std::stod("0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))) ), DEC::com );
}


BOOST_AUTO_TEST_CASE(integration_atanh_test)
{
    BOOST_CHECK_EQUAL( atanh(I<double>(0.0,INF_D)), I<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( I<double>::atanh(I<double>(std::stod("-0X1.FFB88E9EB6307P-1"),std::stod("0X1.999999999999AP-4"))), I<double>(std::stod("-0X1.06A3A97D7979CP+2"),std::stod("0X1.9AF93CD234413P-4")) );
    BOOST_CHECK_EQUAL( I<float>::atanh(I<double>(std::stod("0X1.4C0420F6F08CCP-2"),std::stod("0X1.FFFFFFFFFFFFFP-1"))), I<float>(std::stof("0X1.5871DCP-2"),std::stof("0X1.2B708AP+4")) );

    BOOST_CHECK_EQUAL( atanh(DI<double>(-1.0,std::stod("0X1.FFFFFFFFFFFFFP-1"),DEC::com)), DI<double>(-INF_D,std::stod("0X1.2B708872320E2P+4"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( atanh(DI<double>(-1.0,std::stod("0X1.FFFFFFFFFFFFFP-1"),DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::atanh(DI<double>(std::stod("-0X1.FFB88E9EB6307P-1"),std::stod("0X1.999999999999AP-4"),DEC::def)), DI<double>(std::stod("-0X1.06A3A97D7979CP+2"),std::stod("0X1.9AF93CD234413P-4"), DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::atanh(DI<double>(std::stod("-0X1.FFB88E9EB6307P-1"),std::stod("0X1.999999999999AP-4"),DEC::def)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::atanh(DI<double>(std::stod("0X1.4C0420F6F08CCP-2"),std::stod("0X1.FFFFFFFFFFFFFP-1"))), DI<float>(std::stof("0X1.5871DCP-2"),std::stof("0X1.2B708AP+4"), DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::atanh(DI<double>(std::stod("0X1.4C0420F6F08CCP-2"),std::stod("0X1.FFFFFFFFFFFFFP-1"))) ), DEC::com );
}


BOOST_AUTO_TEST_CASE(integration_sign_test)
{
    BOOST_CHECK_EQUAL( sign(I<double>(1.0,2.0)), I<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( I<double>::sign(I<double>(-0.0,2.0)), I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( I<float>::sign(I<double>(-1.0,2.0)), I<float>(-1.0f,1.0f) );

    BOOST_CHECK_EQUAL( sign(DI<double>(1.0,2.0,DEC::com)), DI<double>(1.0,1.0,DEC::com) );
    BOOST_CHECK_EQUAL( decoration( sign(DI<double>(1.0,2.0,DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::sign(DI<double>(-0.0,2.0,DEC::dac)), DI<double>(0.0,1.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::sign(DI<double>(-0.0,2.0,DEC::dac)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::sign(DI<double>(-1.0,2.0)), DI<float>(-1.0f,1.0f, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::sign(DI<double>(-1.0,2.0)) ), DEC::def );
}

BOOST_AUTO_TEST_CASE(integration_ceil_test)
{
    BOOST_CHECK_EQUAL( ceil(I<double>(1.1,2.0)), I<double>(2.0,2.0) );
    BOOST_CHECK_EQUAL( I<double>::ceil(I<double>(-1.9,2.1)), I<double>(-1.0,3.0) );
    BOOST_CHECK_EQUAL( I<float>::ceil(I<double>(-1.5,2.2)), I<float>(-1.0f,3.0f) );

    BOOST_CHECK_EQUAL( ceil(DI<double>(1.1,2.0,DEC::com)), DI<double>(2.0,2.0,DEC::com) );
    BOOST_CHECK_EQUAL( decoration( ceil(DI<double>(1.1,2.0,DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::ceil(DI<double>(-0.1,2.1,DEC::dac)), DI<double>(0.0,3.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::ceil(DI<double>(-0.1,2.1,DEC::dac)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::ceil(DI<double>(-1.5,0.1)), DI<float>(-1.0f,1.0f, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::ceil(DI<double>(-1.5,0.1)) ), DEC::def );
}

BOOST_AUTO_TEST_CASE(integration_floor_test)
{
    BOOST_CHECK_EQUAL( floor(I<double>(1.1,2.0)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( I<double>::floor(I<double>(-1.9,2.1)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( I<float>::floor(I<double>(-1.5,2.2)), I<float>(-2.0f,2.0f) );

    BOOST_CHECK_EQUAL( floor(DI<double>(1.1,1.9,DEC::com)), DI<double>(1.0,1.0,DEC::com) );
    BOOST_CHECK_EQUAL( decoration( floor(DI<double>(1.1,1.9,DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::floor(DI<double>(-0.1,2.1,DEC::dac)), DI<double>(-1.0,2.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::floor(DI<double>(-0.1,2.1,DEC::dac)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::floor(DI<double>(-1.5,0.1)), DI<float>(-2.0f,0.0f, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::floor(DI<double>(-1.5,0.1)) ), DEC::def );
}

BOOST_AUTO_TEST_CASE(integration_trunc_test)
{
    BOOST_CHECK_EQUAL( trunc(I<double>(1.1,2.2)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( I<double>::trunc(I<double>(-1.9,2.1)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( I<float>::trunc(I<double>(-1.5,2.2)), I<float>(-1.0f,2.0f) );

    BOOST_CHECK_EQUAL( trunc(DI<double>(1.1,1.9,DEC::com)), DI<double>(1.0,1.0,DEC::com) );
    BOOST_CHECK_EQUAL( decoration( trunc(DI<double>(1.1,1.9,DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::trunc(DI<double>(-0.1,2.1,DEC::dac)), DI<double>(0.0,2.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::trunc(DI<double>(-0.1,2.1,DEC::dac)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::trunc(DI<double>(-1.5,0.1)), DI<float>(-1.0f,0.0f, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::trunc(DI<double>(-1.5,0.1)) ), DEC::def );
}

BOOST_AUTO_TEST_CASE(integration_round_ties_to_even_test)
{
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(1.1,2.2)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( I<double>::round_ties_to_even(I<double>(-1.9,2.5)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( I<float>::round_ties_to_even(I<double>(-1.5,2.2)), I<float>(-2.0f,2.0f) );

    BOOST_CHECK_EQUAL( round_ties_to_even(DI<double>(1.5,1.9,DEC::com)), DI<double>(2.0,2.0,DEC::com) );
    BOOST_CHECK_EQUAL( decoration( round_ties_to_even(DI<double>(1.5,1.9,DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::round_ties_to_even(DI<double>(-0.1,2.1,DEC::dac)), DI<double>(0.0,2.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::round_ties_to_even(DI<double>(-0.1,2.1,DEC::dac)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::round_ties_to_even(DI<double>(-1.5,0.1)), DI<float>(-2.0f,0.0f, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::round_ties_to_even(DI<double>(-1.5,0.1)) ), DEC::def );
}

BOOST_AUTO_TEST_CASE(integration_round_ties_to_away_test)
{
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(1.1,2.2)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( I<double>::round_ties_to_away(I<double>(-1.9,2.5)), I<double>(-2.0,3.0) );
    BOOST_CHECK_EQUAL( I<float>::round_ties_to_away(I<double>(-1.5,2.2)), I<float>(-2.0f,2.0f) );

    BOOST_CHECK_EQUAL( round_ties_to_away(DI<double>(1.5,1.9,DEC::com)), DI<double>(2.0,2.0,DEC::com) );
    BOOST_CHECK_EQUAL( decoration( round_ties_to_away(DI<double>(1.5,1.9,DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::round_ties_to_away(DI<double>(-0.1,2.1,DEC::dac)), DI<double>(0.0,2.0, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::round_ties_to_away(DI<double>(-0.1,2.1,DEC::dac)) ), DEC::def );
    BOOST_CHECK_EQUAL( DI<float>::round_ties_to_away(DI<double>(-2.5,0.1)), DI<float>(-3.0f,0.0f, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::round_ties_to_away(DI<double>(-2.5,0.1)) ), DEC::def );
}

BOOST_AUTO_TEST_CASE(integration_abs_test)
{
    BOOST_CHECK_EQUAL( abs(I<double>(1.1,2.2)), I<double>(1.1,2.2) );
    BOOST_CHECK_EQUAL( I<double>::abs(I<double>(-1.9,0.5)), I<double>(0.0,1.9) );
    BOOST_CHECK_EQUAL( I<float>::abs(I<double>(-1.5,2.2)), I<float>(0.0,2.2) );

    BOOST_CHECK_EQUAL( abs(DI<double>(1.5,1.9,DEC::com)), DI<double>(1.5,1.9,DEC::com) );
    BOOST_CHECK_EQUAL( decoration( abs(DI<double>(1.5,1.9,DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::abs(DI<double>(-0.1,2.1,DEC::dac)), DI<double>(0.0,2.1, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::abs(DI<double>(-0.1,2.1,DEC::dac)) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<float>::abs(DI<double>(-2.5,0.1)), DI<float>(0.0f,2.5f, DEC::com) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::abs(DI<double>(-2.5,0.1)) ), DEC::com );
}

BOOST_AUTO_TEST_CASE(integration_min_test)
{
    BOOST_CHECK_EQUAL( min(I<double>(1.1,2.2), I<double>(1.9,2.0)), I<double>(1.1,2.0) );
    BOOST_CHECK_EQUAL( I<double>::min(I<double>(-1.9,0.5), I<double>(-2.9,2.0)), I<double>(-2.9,0.5) );
    BOOST_CHECK_EQUAL( I<float>::min(I<double>(-1.5,2.2), I<double>(0.9,1.9)), I<float>(-1.5,1.9) );

    BOOST_CHECK_EQUAL( min(DI<double>(1.5,1.9,DEC::com), DI<double>(1.0,5.9,DEC::com)), DI<double>(1.0,1.9,DEC::com) );
    BOOST_CHECK_EQUAL( decoration( min(DI<double>(1.5,1.9,DEC::com), DI<double>(1.0,5.9,DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::min(DI<double>(-0.1,2.1,DEC::dac), DI<double>(1.0,5.9,DEC::com)), DI<double>(-0.1,2.1, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::min(DI<double>(-0.1,2.1,DEC::dac), DI<double>(1.0,5.9,DEC::com)) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<float>::min(DI<double>(-2.5,3.1), DI<double>(1.0,1.5,DEC::def)), DI<float>(-2.5f, 1.5f, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::min(DI<double>(-2.5,3.1), DI<double>(1.0,1.5,DEC::def)) ), DEC::def );
}

BOOST_AUTO_TEST_CASE(integration_max_test)
{
    BOOST_CHECK_EQUAL( max(I<double>(1.1,2.2), I<double>(1.9,2.0)), I<double>(1.9,2.2) );
    BOOST_CHECK_EQUAL( I<double>::max(I<double>(-1.9,0.5), I<double>(-2.9,2.0)), I<double>(-1.9,2.0) );
    BOOST_CHECK_EQUAL( I<float>::max(I<double>(-1.5,2.2), I<double>(0.9,1.9)), I<float>(0.9,2.2) );

    BOOST_CHECK_EQUAL( max(DI<double>(1.5,1.9,DEC::com), DI<double>(1.0,5.9,DEC::com)), DI<double>(1.5,5.9,DEC::com) );
    BOOST_CHECK_EQUAL( decoration( max(DI<double>(1.5,1.9,DEC::com), DI<double>(1.0,5.9,DEC::com)) ), DEC::com );
    BOOST_CHECK_EQUAL( DI<double>::max(DI<double>(-0.1,2.1,DEC::dac), DI<double>(1.0,5.9,DEC::com)), DI<double>(1.0,5.9, DEC::dac) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::max(DI<double>(-0.1,2.1,DEC::dac), DI<double>(1.0,5.9,DEC::com)) ), DEC::dac );
    BOOST_CHECK_EQUAL( DI<float>::max(DI<double>(-2.5,3.5), DI<double>(1.0,1.5,DEC::def)), DI<float>(1.0f, 3.5f, DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::max(DI<double>(-2.5,3.5), DI<double>(1.0,1.5,DEC::def)) ), DEC::def );
}
