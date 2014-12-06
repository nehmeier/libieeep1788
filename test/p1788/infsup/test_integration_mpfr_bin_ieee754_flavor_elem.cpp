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
    BOOST_CHECK_EQUAL( +DI<double>(MIN_D, 2.0, DEC::def), DI<double>(MIN_D, 2.0, DEC::def) );
    BOOST_CHECK_EQUAL( DI<double>::pos(DI<double>(MIN_D, 2.0)), DI<double>(MIN_D, 2.0) );
    BOOST_CHECK_EQUAL( DI<float>::pos(DI<double>(std::stod("-0X1.99999C0000000p+4"), MAX_D, DEC::com)), DI<float>(std::stof("-0X1.99999CP+4"), INF_F, DEC::dac) );
}


BOOST_AUTO_TEST_CASE(integration_neg_test)
{
    BOOST_CHECK_EQUAL( neg(I<double>(MIN_D, 2.0)), I<double>(-2.0, -MIN_D) );
    BOOST_CHECK_EQUAL( -I<double>(MIN_D, 2.0), I<double>(-2.0, -MIN_D) );
    BOOST_CHECK_EQUAL( I<double>::neg(I<double>(MIN_D, 2.0)), I<double>(-2.0, -MIN_D) );
    BOOST_CHECK_EQUAL( I<float>::neg(I<double>(std::stod("-0X1.99999C0000000p+4"), MAX_D)), I<float>(-INF_F, std::stof("0X1.99999CP+4")) );


    BOOST_CHECK_EQUAL( neg(DI<double>(MIN_D, 2.0)), DI<double>(-2.0, -MIN_D) );
    BOOST_CHECK_EQUAL( -DI<double>(MIN_D, 2.0, DEC::def), DI<double>(-2.0, -MIN_D, DEC::def) );
    BOOST_CHECK_EQUAL( DI<double>::neg(DI<double>(MIN_D, 2.0)), DI<double>(-2.0, -MIN_D) );
    BOOST_CHECK_EQUAL( DI<float>::neg(DI<double>(std::stod("-0X1.99999C0000000p+4"), MAX_D, DEC::com)), DI<float>(-INF_F, std::stof("0X1.99999CP+4"), DEC::dac) );
}
