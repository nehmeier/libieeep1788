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

#include <limits>

template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

typedef p1788::decoration::decoration DEC;

const double INF_D = std::numeric_limits<double>::infinity();

BOOST_AUTO_TEST_CASE(integration_mul_rev_to_pair_test)
{
    BOOST_CHECK_EQUAL( mul_rev_to_pair(I<double>(-2.0, -0.1), I<double>(-2.1, -0.4)).first, I<double>(std::stod("0X1.999999999999AP-3"), std::stod("0X1.5P+4")) );
    BOOST_CHECK( is_empty( mul_rev_to_pair(I<double>(-2.0, -0.1), I<double>(-2.1, -0.4)).second ) );

    BOOST_CHECK_EQUAL( I<double>::mul_rev_to_pair(I<double>(-2.0, 1.1), I<double>(-2.1, -0.4)).first, I<double>(-INF_D, std::stod("-0X1.745D1745D1745P-2")) );
    BOOST_CHECK_EQUAL( I<double>::mul_rev_to_pair(I<double>(-2.0, 1.1), I<double>(-2.1, -0.4)).second, I<double>(std::stod("0X1.999999999999AP-3"), INF_D) );

    BOOST_CHECK_EQUAL( I<float>::mul_rev_to_pair(I<double>(-2.0, -0.1), I<double>(-2.1, -0.4)).first, I<float>(std::stof("0X1.999998P-3"), std::stof("0X1.5P+4")) );
    BOOST_CHECK( is_empty( I<float>::mul_rev_to_pair(I<double>(-2.0, -0.1), I<double>(-2.1, -0.4)).second ) );


    BOOST_CHECK_EQUAL( mul_rev_to_pair(DI<double>(-2.0, -0.1,DEC::com), DI<double>(-2.1, -0.4,DEC::com)).first, DI<double>(std::stod("0X1.999999999999AP-3"), std::stod("0X1.5P+4"),DEC::com) );
    BOOST_CHECK_EQUAL( decoration( mul_rev_to_pair(DI<double>(-2.0, -0.1,DEC::com), DI<double>(-2.1, -0.4,DEC::com)).first), DEC::com );
    BOOST_CHECK( is_empty( mul_rev_to_pair(DI<double>(-2.0, -0.1,DEC::com), DI<double>(-2.1, -0.4,DEC::com)).second ) );

    BOOST_CHECK_EQUAL( DI<double>::mul_rev_to_pair(DI<double>(-2.0, 1.1,DEC::com), DI<double>(-2.1, -0.4,DEC::dac)).first, DI<double>(-INF_D, std::stod("-0X1.745D1745D1745P-2"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::mul_rev_to_pair(DI<double>(-2.0, 1.1,DEC::com), DI<double>(-2.1, -0.4,DEC::dac)).first ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::mul_rev_to_pair(DI<double>(-2.0, 1.1,DEC::com), DI<double>(-2.1, -0.4,DEC::dac)).second, DI<double>(std::stod("0X1.999999999999AP-3"), INF_D, DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::mul_rev_to_pair(DI<double>(-2.0, 1.1,DEC::com), DI<double>(-2.1, -0.4,DEC::dac)).second ), DEC::trv );

    BOOST_CHECK_EQUAL( DI<float>::mul_rev_to_pair(DI<double>(-2.0, -0.1,DEC::com), DI<double>(-2.1, -0.4,DEC::def)).first, DI<float>(std::stof("0X1.999998P-3"), std::stof("0X1.5P+4"),DEC::def) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::mul_rev_to_pair(DI<double>(-2.0, -0.1,DEC::com), DI<double>(-2.1, -0.4,DEC::def)).first ), DEC::def );
    BOOST_CHECK( is_empty( DI<float>::mul_rev_to_pair(DI<double>(-2.0, -0.1,DEC::com), DI<double>(-2.1, -0.4,DEC::def)).second ) );
}

