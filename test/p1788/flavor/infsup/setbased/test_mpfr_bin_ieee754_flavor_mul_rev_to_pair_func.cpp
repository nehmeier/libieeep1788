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

#define BOOST_TEST_MODULE "Flavor: Two-output division [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include "p1788/exception/exception.hpp"
#include "p1788/decoration/decoration.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"
#include "test/util/mpfr_bin_ieee754_flavor_io_test_util.hpp"

#include <limits>

template<typename T>
using F = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>;

template<typename T>
using REP = typename F<T>::representation;

template<typename T>
using REP_DEC = typename F<T>::representation_dec;

typedef p1788::decoration::decoration DEC;

const double INF_D = std::numeric_limits<double>::infinity();
const double NaN_D = std::numeric_limits<double>::quiet_NaN();

const double INF_F = std::numeric_limits<float>::infinity();
const double NaN_F = std::numeric_limits<float>::quiet_NaN();



BOOST_AUTO_TEST_CASE(minimal_mul_rev_to_pair_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(F<double>::empty(), REP<double>(1.0, 2.0)).first ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(F<double>::empty(), REP<double>(1.0, 2.0)).second ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(REP<double>(1.0, 2.0), F<double>::empty()).first ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(REP<double>(1.0, 2.0), F<double>::empty()).second ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(F<double>::empty(), F<double>::empty()).first ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(F<double>::empty(), F<double>::empty()).second ) );


    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-2.1, -0.4)).first,  REP<double>(std::stod("0X1.999999999999AP-3"), std::stod("0X1.5P+4")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-2.1, -0.4)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-2.1, -0.4)).first,  REP<double>(std::stod("0X1.999999999999AP-3"), INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-2.1, -0.4)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-2.1, -0.4)).first,  REP<double>(-INF_D, std::stod("-0X1.745D1745D1745P-2")) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-2.1, -0.4)).second,  REP<double>(std::stod("0X1.999999999999AP-3"), INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-2.1, -0.4)).first,  REP<double>(-INF_D, std::stod("-0X1.745D1745D1745P-2")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-2.1, -0.4)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-2.1, -0.4)).first,  REP<double>(std::stod("-0X1.A400000000001P+7"), std::stod("-0X1.745D1745D1745P-2")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-2.1, -0.4)).second ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-2.1, -0.4)).first ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-2.1, -0.4)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-2.1, -0.4)).first,  REP<double>(0.0, std::stod("0X1.5P+4")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-2.1, -0.4)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-2.1, -0.4)).first,  REP<double>(0.0, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-2.1, -0.4)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-2.1, -0.4)).first,  REP<double>(-INF_D, std::stod("-0X1.745D1745D1745P-2")) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-2.1, -0.4)).second,  REP<double>(0.0, INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-2.1, -0.4)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-2.1, -0.4)).second,  REP<double>(std::stod("0X1.999999999999AP-3"), INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-2.1, -0.4)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-2.1, -0.4)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-2.1, -0.4)).first,  REP<double>(std::stod("-0X1.A400000000001P+7"), 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-2.1, -0.4)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-2.1, -0.4)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-2.1, -0.4)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-2.1, 0.0)).first,  REP<double>(0.0, std::stod("0X1.5P+4")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-2.1, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-2.1, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-2.1, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-2.1, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-2.1, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-2.1, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-2.1, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-2.1, 0.0)).first,  REP<double>(std::stod("-0X1.A400000000001P+7"), 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-2.1, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-2.1, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-2.1, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-2.1, 0.0)).first,  REP<double>(0.0, std::stod("0X1.5P+4")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-2.1, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-2.1, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-2.1, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-2.1, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-2.1, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-2.1, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-2.1, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-2.1, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-2.1, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-2.1, 0.0)).first,  REP<double>(std::stod("-0X1.A400000000001P+7"), 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-2.1, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-2.1, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-2.1, 0.0)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-2.1, 0.12)).first,  REP<double>(std::stod("-0X1.3333333333333P+0"), std::stod("0X1.5P+4")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-2.1, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-2.1, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-2.1, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-2.1, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-2.1, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-2.1, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-2.1, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-2.1, 0.12)).first,  REP<double>(std::stod("-0X1.A400000000001P+7 "), std::stod("0X1.8P+3")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-2.1, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-2.1, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-2.1, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-2.1, 0.12)).first,  REP<double>(std::stod("-0X1.3333333333333P+0"), std::stod("0X1.5P+4")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-2.1, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-2.1, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-2.1, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-2.1, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-2.1, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-2.1, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-2.1, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-2.1, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-2.1, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-2.1, 0.12)).first,  REP<double>(std::stod("-0X1.A400000000001P+7 "), std::stod("0X1.8P+3")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-2.1, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-2.1, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-2.1, 0.12)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(0.0, 0.12)).first,  REP<double>(std::stod("-0X1.3333333333333P+0"), 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(0.0, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(0.0, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(0.0, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(0.0, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(0.0, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(0.0, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(0.0, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(0.0, 0.12)).first,  REP<double>(0.0, std::stod("0X1.8P+3")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(0.0, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(0.0, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(0.0, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(0.0, 0.12)).first,  REP<double>(std::stod("-0X1.3333333333333P+0"), 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(0.0, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(0.0, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(0.0, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(0.0, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(0.0, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(0.0, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(0.0, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(0.0, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(0.0, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(0.0, 0.12)).first,  REP<double>(0.0, std::stod("0X1.8P+3")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(0.0, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(0.0, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(0.0, 0.12)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(0.01, 0.12)).first,  REP<double>(std::stod("-0X1.3333333333333P+0"), std::stod("-0X1.47AE147AE147BP-8")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(0.01, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(0.01, 0.12)).first,  REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-8")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(0.01, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(0.01, 0.12)).first,  REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-8")) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(0.01, 0.12)).second,  REP<double>(std::stod("0X1.29E4129E4129DP-7"), INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(0.01, 0.12)).first,  REP<double>(std::stod("0X1.29E4129E4129DP-7"), INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(0.01, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(0.01, 0.12)).first,  REP<double>(std::stod("0X1.29E4129E4129DP-7"), std::stod("0X1.8P+3")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(0.01, 0.12)).second ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(0.01, 0.12)).first ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(0.01, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(0.01, 0.12)).first,  REP<double>(std::stod("-0X1.3333333333333P+0"), 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(0.01, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(0.01, 0.12)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(0.01, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(0.01, 0.12)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(0.01, 0.12)).second,  REP<double>(std::stod("0X1.29E4129E4129DP-7"), INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(0.01, 0.12)).first,  REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-8")) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(0.01, 0.12)).second,  REP<double>(0.0, INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(0.01, 0.12)).first,  REP<double>(0.0, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(0.01, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(0.01, 0.12)).first,  REP<double>(0.0, std::stod("0X1.8P+3")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(0.01, 0.12)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(0.01, 0.12)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(0.01, 0.12)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(0.0, 0.0)).first,  REP<double>(0.0, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(0.0, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(0.0, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(0.0, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(0.0, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(0.0, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(0.0, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(0.0, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(0.0, 0.0)).first,  REP<double>(0.0, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(0.0, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(0.0, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(0.0, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(0.0, 0.0)).first,  REP<double>(0.0, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(0.0, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(0.0, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(0.0, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(0.0, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(0.0, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(0.0, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(0.0, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(0.0, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(0.0, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(0.0, 0.0)).first,  REP<double>(0.0, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(0.0, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(0.0, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(0.0, 0.0)).second ) );


    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-INF_D, -0.1)).first,  REP<double>(std::stod("0X1.999999999999AP-5"), INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-INF_D, -0.1)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-INF_D, -0.1)).first,  REP<double>(std::stod("0X1.999999999999AP-5") , INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-INF_D, -0.1)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-INF_D, -0.1)).first,  REP<double>(-INF_D , std::stod("-0X1.745D1745D1745P-4")) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-INF_D, -0.1)).second,  REP<double>(std::stod("0X1.999999999999AP-5") , INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-INF_D, -0.1)).first,  REP<double>(-INF_D, std::stod("-0X1.745D1745D1745P-4")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-INF_D, -0.1)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-INF_D, -0.1)).first,  REP<double>(-INF_D, std::stod("-0X1.745D1745D1745P-4")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-INF_D, -0.1)).second ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-INF_D, -0.1)).first ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-INF_D, -0.1)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-INF_D, -0.1)).first,  REP<double>(0.0, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-INF_D, -0.1)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-INF_D, -0.1)).first,  REP<double>(0.0, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-INF_D, -0.1)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-INF_D, -0.1)).first,  REP<double>(-INF_D, std::stod("-0X1.745D1745D1745P-4")) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-INF_D, -0.1)).second,  REP<double>(0.0, INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-INF_D, -0.1)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-INF_D, -0.1)).second,  REP<double>(std::stod("0X1.999999999999AP-5") , INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-INF_D, -0.1)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-INF_D, -0.1)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-INF_D, -0.1)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-INF_D, -0.1)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-INF_D, -0.1)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-INF_D, -0.1)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-INF_D, 0.0)).first,  REP<double>(0.0, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-INF_D, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-INF_D, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-INF_D, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-INF_D, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-INF_D, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-INF_D, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-INF_D, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-INF_D, 0.0)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-INF_D, 0.0)).second) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-INF_D, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-INF_D, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-INF_D, 0.0)).first,  REP<double>(0.0, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-INF_D, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-INF_D, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-INF_D, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-INF_D, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-INF_D, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-INF_D, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-INF_D, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-INF_D, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-INF_D, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-INF_D, 0.0)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-INF_D, 0.0)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-INF_D, 0.0)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-INF_D, 0.0)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-INF_D, 0.3)).first,  REP<double>(std::stod("-0X1.8P+1"), INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-INF_D, 0.3)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-INF_D, 0.3)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-INF_D, 0.3)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-INF_D, 0.3)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-INF_D, 0.3)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-INF_D, 0.3)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-INF_D, 0.3)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-INF_D, 0.3)).first,  REP<double>(-INF_D, std::stod("0X1.EP+4")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-INF_D, 0.3)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-INF_D, 0.3)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-INF_D, 0.3)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-INF_D, 0.3)).first,  REP<double>(std::stod("-0X1.8P+1"), INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-INF_D, 0.3)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-INF_D, 0.3)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-INF_D, 0.3)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-INF_D, 0.3)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-INF_D, 0.3)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-INF_D, 0.3)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-INF_D, 0.3)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-INF_D, 0.3)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-INF_D, 0.3)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-INF_D, 0.3)).first,  REP<double>(-INF_D, std::stod("0X1.EP+4")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-INF_D, 0.3)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-INF_D, 0.3)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-INF_D, 0.3)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-0.21, INF_D)).first,  REP<double>(-INF_D , std::stod("0X1.0CCCCCCCCCCCDP+1")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-0.21, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-0.21, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-0.21, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-0.21, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-0.21, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-0.21, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-0.21, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-0.21, INF_D)).first,  REP<double>(std::stod("-0X1.5P+4"), INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-0.21, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-0.21, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-0.21, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-0.21, INF_D)).first,  REP<double>(-INF_D, std::stod("0X1.0CCCCCCCCCCCDP+1")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-0.21, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-0.21, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-0.21, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-0.21, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-0.21, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-0.21, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-0.21, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-0.21, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-0.21, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-0.21, INF_D)).first,  REP<double>(std::stod("-0X1.5P+4"), INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-0.21, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-0.21, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-0.21, INF_D)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(0.0, INF_D)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(0.0, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(0.0, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(0.0, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(0.0, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(0.0, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(0.0, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(0.0, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(0.0, INF_D)).first,  REP<double>(0.0, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(0.0, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(0.0, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(0.0, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(0.0, INF_D)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(0.0, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(0.0, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(0.0, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(0.0, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(0.0, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(0.0, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(0.0, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(0.0, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(0.0, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(0.0, INF_D)).first,  REP<double>(0.0, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(0.0, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(0.0, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(0.0, INF_D)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(0.04, INF_D)).first,  REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-6")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(0.04, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(0.04, INF_D)).first,  REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-6")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(0.04, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(0.04, INF_D)).first,  REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-6")) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(0.04, INF_D)).second,  REP<double>(std::stod("0X1.29E4129E4129DP-5"), INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(0.04, INF_D)).first,  REP<double>(std::stod("0X1.29E4129E4129DP-5"), INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(0.04, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(0.04, INF_D)).first,  REP<double>(std::stod("0X1.29E4129E4129DP-5"), INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(0.04, INF_D)).second ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(0.04, INF_D)).first ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(0.04, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(0.04, INF_D)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(0.04, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(0.04, INF_D)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(0.04, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(0.04, INF_D)).first,  REP<double>(-INF_D, 0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(0.04, INF_D)).second,  REP<double>(std::stod("0X1.29E4129E4129DP-5"), INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(0.04, INF_D)).first,  REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-6")) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(0.04, INF_D)).second,  REP<double>(0.0, INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(0.04, INF_D)).first,  REP<double>(0.0, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(0.04, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(0.04, INF_D)).first,  REP<double>(0.0, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(0.04, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(0.04, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(0.04, INF_D)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-INF_D, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-INF_D, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-INF_D, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 0.0), REP<double>(-INF_D, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-INF_D, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(-INF_D, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-INF_D, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 1.1), REP<double>(-INF_D, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-INF_D, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-INF_D, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-INF_D, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, 0.0), REP<double>(-INF_D, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-INF_D, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, -0.1), REP<double>(-INF_D, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-INF_D, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 0.0), REP<double>(-INF_D, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-INF_D, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, 1.1), REP<double>(-INF_D, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-INF_D, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-2.0, INF_D), REP<double>(-INF_D, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-INF_D, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.0, INF_D), REP<double>(-INF_D, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-INF_D, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(0.01, INF_D), REP<double>(-INF_D, INF_D)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-INF_D, INF_D)).first,  REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(-INF_D, INF_D), REP<double>(-INF_D, INF_D)).second ) );


    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(1.0,-2.0), REP<double>(1.0,2.0)).first) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<double>(1.0,-2.0), REP<double>(1.0,2.0)).second) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::mul_rev_to_pair(REP<double>(1.0,2.0),REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}




BOOST_AUTO_TEST_CASE(minimal_mul_rev_to_pair_mixedtype_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(F<float>::empty(), REP<double>(1.0, 2.0)).first ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(F<float>::empty(), REP<double>(1.0, 2.0)).second ) );
    BOOST_CHECK( F<float>::is_empty( F<float>::mul_rev_to_pair(REP<double>(1.0, 2.0), F<double>::empty()).first ) );
    BOOST_CHECK( F<float>::is_empty( F<float>::mul_rev_to_pair(REP<double>(1.0, 2.0), F<double>::empty()).second ) );

    BOOST_CHECK_EQUAL( F<float>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-2.1, -0.4)).first,  REP<float>(std::stof("0X1.999998P-3"), std::stof("0X1.5P+4")) );
    BOOST_CHECK( F<float>::is_empty(F<float>::mul_rev_to_pair(REP<double>(-2.0, -0.1), REP<double>(-2.1, -0.4)).second ) );

    BOOST_CHECK_EQUAL( F<float>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-2.1, 0.0)).first,  REP<float>(std::stof("-0X1.A40002P+7"), 0.0f) );
    BOOST_CHECK( F<float>::is_empty(F<float>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-2.1, 0.0)).second ) );

    BOOST_CHECK_EQUAL( F<float>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-2.1, 0.12)).first,  REP<float>(std::stof("-0X1.A40002P+7 "), std::stof("0X1.8P+3")) );
    BOOST_CHECK( F<float>::is_empty(F<float>::mul_rev_to_pair(REP<double>(0.01, 1.1), REP<double>(-2.1, 0.12)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<float>(0.01f, INF_F), REP<float>(0.0f, 0.12f)).first,  REP<double>(0.0, std::stod("0X1.8P+3")) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP<float>(0.01f, INF_F), REP<float>(0.0f, 0.12f)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<float>(-2.0f, 1.1f), REP<float>(0.01f, 0.12f)).first,  REP<double>(-INF_D, std::stod("-0x1.47ae14p-8")) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<float>(-2.0f, 1.1f), REP<float>(0.01f, 0.12f)).second,  REP<double>(std::stod("0x1.29e411c238b3bp-7"), INF_D) );


    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<float>(-2.0f, 1.1f), REP<double>(-INF_D, -0.1)).first,  REP<double>(-INF_D , std::stod("-0x1.745d16be69c93p-4")) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP<float>(-2.0f, 1.1f), REP<double>(-INF_D, -0.1)).second,  REP<double>(std::stod("0X1.999999999999AP-5") , INF_D) );


    BOOST_CHECK_EQUAL( F<float>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(0.04, INF_D)).first,  REP<float>(-INF_F, std::stof("-0X1.47AE14P-6")) );
    BOOST_CHECK_EQUAL( F<float>::mul_rev_to_pair(REP<double>(-2.0, 1.1), REP<double>(0.04, INF_D)).second,  REP<float>(std::stof("0X1.29E412P-5"), INF_F) );


    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty(F<float>::mul_rev_to_pair(REP<double>(1.0,-2.0), REP<double>(1.0,2.0)).first) );
    BOOST_CHECK( F<float>::is_empty(F<float>::mul_rev_to_pair(REP<double>(1.0,-2.0), REP<double>(1.0,2.0)).second) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::mul_rev_to_pair(REP<double>(1.0,2.0),REP<float>(1.0f,-2.0f)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}




BOOST_AUTO_TEST_CASE(minimal_mul_rev_to_pair_dec_test)
{
    BOOST_CHECK( F<double>::is_nai( F<double>::mul_rev_to_pair(F<double>::nai(), REP_DEC<double>(REP<double>(1.0, 2.0),DEC::def)).first ) );
    BOOST_CHECK( F<double>::is_nai( F<double>::mul_rev_to_pair(F<double>::nai(), REP_DEC<double>(REP<double>(1.0, 2.0),DEC::def)).second ) );
    BOOST_CHECK( F<double>::is_nai( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0, 2.0),DEC::com), F<double>::nai()).first ) );
    BOOST_CHECK( F<double>::is_nai( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0, 2.0),DEC::com), F<double>::nai()).second ) );
    BOOST_CHECK( F<double>::is_nai( F<double>::mul_rev_to_pair(F<double>::nai(), F<double>::nai()).first ) );
    BOOST_CHECK( F<double>::is_nai( F<double>::mul_rev_to_pair(F<double>::nai(), F<double>::nai()).second ) );


    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(F<double>::empty_dec(), REP_DEC<double>(REP<double>(1.0, 2.0),DEC::def)).first ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(F<double>::empty_dec(), REP_DEC<double>(REP<double>(1.0, 2.0),DEC::def)).second ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0, 2.0),DEC::com), F<double>::empty_dec()).first ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0, 2.0),DEC::com), F<double>::empty_dec()).second ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(F<double>::empty_dec(), F<double>::empty_dec()).first ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(F<double>::empty_dec(), F<double>::empty_dec()).second ) );


    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::com), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::com)).first,  REP_DEC<double>(REP<double>(std::stod("0X1.999999999999AP-3"), std::stod("0X1.5P+4")),DEC::com) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::com), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::com)).first,  REP_DEC<double>(REP<double>(std::stod("0X1.999999999999AP-3"), INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::com), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0X1.745D1745D1745P-2")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::com), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::dac)).second,  REP_DEC<double>(REP<double>(std::stod("0X1.999999999999AP-3"), INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::trv), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::def)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0X1.745D1745D1745P-2")),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::trv), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::def)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::com), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::com)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.A400000000001P+7"), std::stod("-0X1.745D1745D1745P-2")),DEC::com) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::com), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::com)).second ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::def)).first ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::def)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::dac)).first,  REP_DEC<double>(REP<double>(0.0, std::stod("0X1.5P+4")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::def), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::com)).first,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::def), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::trv), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::def)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0X1.745D1745D1745P-2")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::trv), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::def)).second,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::dac)).second,  REP_DEC<double>(REP<double>(std::stod("0X1.999999999999AP-3"), INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::def), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::def), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::def), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::def)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.A400000000001P+7"), 0.0),DEC::def) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::def), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::def)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::dac)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(0.0, std::stod("0X1.5P+4")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.A400000000001P+7"), 0.0),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(0.0, std::stod("0X1.5P+4")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.A400000000001P+7"), 0.0),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::com)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.3333333333333P+0"), std::stod("0X1.5P+4")),DEC::def) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.A400000000001P+7 "), std::stod("0X1.8P+3")),DEC::def) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.3333333333333P+0"), std::stod("0X1.5P+4")),DEC::def) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.A400000000001P+7 "), std::stod("0X1.8P+3")),DEC::def) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::def), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.3333333333333P+0"), 0.0),DEC::com) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).first,  REP_DEC<double>(REP<double>(0.0, std::stod("0X1.8P+3")),DEC::com) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.3333333333333P+0"), 0.0),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).first,  REP_DEC<double>(REP<double>(0.0, std::stod("0X1.8P+3")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.12),DEC::com)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.3333333333333P+0"), std::stod("-0X1.47AE147AE147BP-8")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-8")),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-8")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).second,  REP_DEC<double>(REP<double>(std::stod("0X1.29E4129E4129DP-7"), INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("0X1.29E4129E4129DP-7"), INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("0X1.29E4129E4129DP-7"), std::stod("0X1.8P+3")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).second ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).first ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.3333333333333P+0"), 0.0),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).second,  REP_DEC<double>(REP<double>(std::stod("0X1.29E4129E4129DP-7"), INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-8")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).second,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(0.0, std::stod("0X1.8P+3")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.01, 0.12),DEC::dac)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, 0.0),DEC::com)).second ) );



    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("0X1.999999999999AP-5"), INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("0X1.999999999999AP-5") , INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D , std::stod("-0X1.745D1745D1745P-4")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second,  REP_DEC<double>(REP<double>(std::stod("0X1.999999999999AP-5") , INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0X1.745D1745D1745P-4")),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0X1.745D1745D1745P-4")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0X1.745D1745D1745P-4")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second,  REP_DEC<double>(REP<double>(std::stod("0X1.999999999999AP-5") , INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).first,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).second) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).first,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.8P+1"), INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("0X1.EP+4")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.8P+1"), INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("0X1.EP+4")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, 0.3),DEC::dac)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D , std::stod("0X1.0CCCCCCCCCCCDP+1")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.5P+4"), INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("0X1.0CCCCCCCCCCCDP+1")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("-0X1.5P+4"), INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-0.21, INF_D),DEC::dac)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-6")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-6")),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-6")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second,  REP_DEC<double>(REP<double>(std::stod("0X1.29E4129E4129DP-5"), INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("0X1.29E4129E4129DP-5"), INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(std::stod("0X1.29E4129E4129DP-5"), INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second,  REP_DEC<double>(REP<double>(std::stod("0X1.29E4129E4129DP-5"), INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0X1.47AE147AE147BP-6")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 0.0),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.0, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).second ) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, INF_D),DEC::dac)).second ) );


    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::com)).first) );
    BOOST_CHECK( F<double>::is_nai(F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::dac), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)).second) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0,2.0),DEC::dac),REP_DEC<double>(REP<double>(1.0,-2.0),DEC::ill)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}



BOOST_AUTO_TEST_CASE(minimal_mul_rev_to_pair_dec_mixedtype_test)
{
    BOOST_CHECK( F<double>::is_nai( F<double>::mul_rev_to_pair(F<float>::nai(), REP_DEC<double>(REP<double>(1.0, 2.0),DEC::dac)).first ) );
    BOOST_CHECK( F<double>::is_nai( F<double>::mul_rev_to_pair(F<float>::nai(), REP_DEC<double>(REP<double>(1.0, 2.0),DEC::dac)).second ) );
    BOOST_CHECK( F<float>::is_nai( F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0, 2.0),DEC::dac), F<double>::nai()).first ) );
    BOOST_CHECK( F<float>::is_nai( F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0, 2.0),DEC::dac), F<double>::nai()).second ) );


    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(F<float>::empty_dec(), REP_DEC<double>(REP<double>(1.0, 2.0),DEC::dac)).first ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::mul_rev_to_pair(F<float>::empty_dec(), REP_DEC<double>(REP<double>(1.0, 2.0),DEC::dac)).second ) );
    BOOST_CHECK( F<float>::is_empty( F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0, 2.0),DEC::dac), F<double>::empty_dec()).first ) );
    BOOST_CHECK( F<float>::is_empty( F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0, 2.0),DEC::dac), F<double>::empty_dec()).second ) );

    BOOST_CHECK_EQUAL( F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::dac)).first,  REP_DEC<float>(REP<float>(std::stof("0X1.999998P-3"), std::stof("0X1.5P+4")),DEC::dac) );
    BOOST_CHECK( F<float>::is_empty(F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, -0.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, -0.4),DEC::dac)).second ) );

    BOOST_CHECK_EQUAL( F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::dac)).first,  REP_DEC<float>(REP<float>(std::stof("-0X1.A40002P+7"), 0.0f),DEC::dac) );
    BOOST_CHECK( F<float>::is_empty(F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.0),DEC::dac)).second ) );

    BOOST_CHECK_EQUAL( F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).first,  REP_DEC<float>(REP<float>(std::stof("-0X1.A40002P+7 "), std::stof("0X1.8P+3")),DEC::dac) );
    BOOST_CHECK( F<float>::is_empty(F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(0.01, 1.1),DEC::dac), REP_DEC<double>(REP<double>(-2.1, 0.12),DEC::dac)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<float>(REP<float>(0.01f, INF_F),DEC::dac), REP_DEC<float>(REP<float>(0.0f, 0.12f),DEC::dac)).first,  REP_DEC<double>(REP<double>(0.0, std::stod("0X1.8P+3")),DEC::dac) );
    BOOST_CHECK( F<double>::is_empty(F<double>::mul_rev_to_pair(REP_DEC<float>(REP<float>(0.01f, INF_F),DEC::dac), REP_DEC<float>(REP<float>(0.0f, 0.12f),DEC::dac)).second ) );

    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<float>(REP<float>(-2.0f, 1.1f),DEC::dac), REP_DEC<float>(REP<float>(0.01f, 0.12f),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D, std::stod("-0x1.47ae14p-8")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<float>(REP<float>(-2.0f, 1.1f),DEC::dac), REP_DEC<float>(REP<float>(0.01f, 0.12f),DEC::dac)).second,  REP_DEC<double>(REP<double>(std::stod("0x1.29e411c238b3bp-7"), INF_D),DEC::trv) );


    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<float>(REP<float>(-2.0f, 1.1f),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).first,  REP_DEC<double>(REP<double>(-INF_D , std::stod("-0x1.745d16be69c93p-4")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::mul_rev_to_pair(REP_DEC<float>(REP<float>(-2.0f, 1.1f),DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -0.1),DEC::dac)).second,  REP_DEC<double>(REP<double>(std::stod("0X1.999999999999AP-5") , INF_D),DEC::trv) );


    BOOST_CHECK_EQUAL( F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).first,  REP_DEC<float>(REP<float>(-INF_F, std::stof("-0X1.47AE14P-6")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(-2.0, 1.1),DEC::dac), REP_DEC<double>(REP<double>(0.04, INF_D),DEC::dac)).second,  REP_DEC<float>(REP<float>(std::stof("0X1.29E412P-5"), INF_F),DEC::trv) );


    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai(F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::dac), REP_DEC<double>(REP<double>(1.0,2.0),DEC::dac)).first) );
    BOOST_CHECK( F<float>::is_nai(F<float>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::dac), REP_DEC<double>(REP<double>(1.0,2.0),DEC::dac)).second) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::mul_rev_to_pair(REP_DEC<double>(REP<double>(1.0,2.0),DEC::dac),REP_DEC<float>(REP<float>(1.0f,-2.0f),DEC::dac)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

