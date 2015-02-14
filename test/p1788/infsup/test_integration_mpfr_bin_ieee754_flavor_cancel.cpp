//
//                              libieeep1788
//
//   An implementation of the preliminary IEEE P1788 standard for
//   interval arithmetic
//
//
//   Copyright 2013 - 2015
//
//   Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
//   Department of Computer Science,
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

#define BOOST_TEST_MODULE "Integration: Cancellative addition and subtraction [infsup/interval, infsup/decorated_interval, p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include "p1788/p1788.hpp"


template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

typedef p1788::decoration::decoration DEC;


BOOST_AUTO_TEST_CASE(integration_cancel_plus_test)
{
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-5.1,-0.9), I<double>(1.0,5.0)), I<double>(std::stod("-0X1.999999999998P-4"),std::stod("0X1.9999999999998P-4")) );
    BOOST_CHECK_EQUAL( I<double>::cancel_plus(I<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFFP-53")), I<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFEP-53"))), I<double>(std::stod("-0X1.FFFFFFFFFFFFFP-1"),std::stod("-0X1.FFFFFFFFFFFFEP-1")) );
    BOOST_CHECK_EQUAL( I<float>::cancel_plus(I<double>(-5.0,-0.9), I<double>(1.0,5.0)), I<float>(0.0f, std::stof("0X1.99999AP-4")) );

    BOOST_CHECK_EQUAL( cancel_plus(DI<double>(-5.1,0.0,DEC::com), DI<double>(0.0,5.0,DEC::com)), DI<double>(std::stod("-0X1.999999999998P-4"),0.0,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( cancel_plus(DI<double>(-5.1,0.0,DEC::com), DI<double>(0.0,5.0,DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::cancel_plus(DI<double>(0.9, 5.1,DEC::dac), DI<double>(-5.0,-1.0,DEC::com)), DI<double>(std::stod("-0X1.9999999999998P-4"),std::stod("0X1.999999999998P-4"), DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::cancel_plus(DI<double>(0.9, 5.1,DEC::dac), DI<double>(-5.0,-1.0,DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::cancel_plus(DI<double>(-5.0,-0.9), DI<double>(1.0,5.0)), DI<float>(0.0f, std::stof("0X1.99999AP-4"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::cancel_plus(DI<double>(-5.0,-0.9), DI<double>(1.0,5.0)) ), DEC::trv );
}

BOOST_AUTO_TEST_CASE(integration_cancel_minus_test)
{
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-5.1,-0.9), I<double>(-5.0,-1.0)), I<double>(std::stod("-0X1.999999999998P-4"),std::stod("0X1.9999999999998P-4")) );
    BOOST_CHECK_EQUAL( I<double>::cancel_minus(I<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFFP-53")), I<double>(std::stod("-0X1.FFFFFFFFFFFFEP-53"),std::stod("0X1P+0"))), I<double>(std::stod("-0X1.FFFFFFFFFFFFFP-1"),std::stod("-0X1.FFFFFFFFFFFFEP-1")) );
    BOOST_CHECK_EQUAL( I<float>::cancel_minus(I<double>(-5.0,-0.9), I<double>(-5.0,-1.0)), I<float>(0.0f, std::stof("0X1.99999AP-4")) );

    BOOST_CHECK_EQUAL( cancel_minus(DI<double>(-5.1,0.0,DEC::com), DI<double>(-5.0,0.0,DEC::com)), DI<double>(std::stod("-0X1.999999999998P-4"),0.0,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( cancel_minus(DI<double>(-5.1,0.0,DEC::com), DI<double>(-5.0,0.0,DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::cancel_minus(DI<double>(0.9, 5.1,DEC::dac), DI<double>(1.0,5.0,DEC::com)), DI<double>(std::stod("-0X1.9999999999998P-4"),std::stod("0X1.999999999998P-4"), DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::cancel_minus(DI<double>(0.9, 5.1,DEC::dac), DI<double>(1.0,5.0,DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::cancel_minus(DI<double>(-5.0,-0.9), DI<double>(-5.0,-1.0)), DI<float>(0.0f, std::stof("0X1.99999AP-4"), DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::cancel_minus(DI<double>(-5.0,-0.9), DI<double>(-5.0,-1.0)) ), DEC::trv );
}
