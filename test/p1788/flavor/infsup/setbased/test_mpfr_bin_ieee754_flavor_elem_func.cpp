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

#define BOOST_TEST_MODULE "Flavor: Forward-mode elementary functions [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
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
const double MAX_D = std::numeric_limits<double>::max();
const double MIN_D = std::numeric_limits<double>::min();



//BOOST_AUTO_TEST_CASE(minimal_pos_test)
//{
//    BOOST_CHECK_EQUAL( F<double>::pos(REP<double>(1.0,2.0)), REP<double>(1.0,2.0) );
//BOOST_CHECK( F<double>::is_empty( F<double>::pos(F<double>::empty()) ) );
//    BOOST_CHECK_EQUAL( F<double>::pos(F<double>::entire()), F<double>::entire() );
//    BOOST_CHECK_EQUAL( F<double>::pos(REP<double>(1.0,INF_D)), REP<double>(1.0,INF_D) );
//    BOOST_CHECK_EQUAL( F<double>::pos(REP<double>(-INF_D,-1.0)), REP<double>(-INF_D,-1.0) );
//    BOOST_CHECK_EQUAL( F<double>::pos(REP<double>(0.0,2.0)), REP<double>(0.0,2.0) );
//    BOOST_CHECK_EQUAL( F<double>::pos(REP<double>(-0.0,2.0)), REP<double>(0.0,2.0) );
//    BOOST_CHECK_EQUAL( F<double>::pos(REP<double>(-2.5,-0.0)), REP<double>(-2.5,0.0) );
//    BOOST_CHECK_EQUAL( F<double>::pos(REP<double>(-2.5,0.0)), REP<double>(-2.5,0.0) );
//    BOOST_CHECK_EQUAL( F<double>::pos(REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
//    BOOST_CHECK_EQUAL( F<double>::pos(REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
//}

BOOST_AUTO_TEST_CASE(minimal_neg_test)
{
    BOOST_CHECK_EQUAL( F<double>::neg(REP<double>(1.0,2.0)), REP<double>(-2.0,-1.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::neg(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::neg(F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::neg(REP<double>(1.0,INF_D)), REP<double>(-INF_D,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::neg(REP<double>(-INF_D,1.0)), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::neg(REP<double>(0.0,2.0)), REP<double>(-2.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::neg(REP<double>(-0.0,2.0)), REP<double>(-2.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::neg(REP<double>(-2.0,0.0)), REP<double>(0.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::neg(REP<double>(-2.0,-0.0)), REP<double>(0.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::neg(REP<double>(0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::neg(REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
}

BOOST_AUTO_TEST_CASE(minimal_add_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::add(F<double>::empty(), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::add(REP<double>(-1.0,1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::add(F<double>::empty(), REP<double>(-1.0,1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::add(F<double>::empty(), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::add(F<double>::entire(), F<double>::empty()) ) );

    BOOST_CHECK_EQUAL( F<double>::add(F<double>::entire(), REP<double>(-INF_D,1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::add(F<double>::entire(), REP<double>(-1.0,1.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::add(F<double>::entire(), REP<double>(-1.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::add(F<double>::entire(), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(-INF_D,1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(-1.0,1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(-1.0,INF_D), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(-INF_D,2.0), REP<double>(-INF_D,4.0)), REP<double>(-INF_D,6.0) );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(-INF_D,2.0), REP<double>(3.0,4.0)), REP<double>(-INF_D,6.0) );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(-INF_D,2.0), REP<double>(3.0,INF_D)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(1.0,2.0), REP<double>(-INF_D,4.0)), REP<double>(-INF_D,6.0) );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(1.0,2.0), REP<double>(3.0,4.0)), REP<double>(4.0,6.0) );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(1.0,2.0), REP<double>(3.0,INF_D)), REP<double>(4.0,INF_D) );

    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(1.0,INF_D), REP<double>(-INF_D,4.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(1.0,INF_D), REP<double>(3.0,4.0)), REP<double>(4.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(1.0,INF_D), REP<double>(3.0,INF_D)), REP<double>(4.0,INF_D) );

    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(1.0,MAX_D), REP<double>(3.0,4.0)), REP<double>(4.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(-MAX_D,2.0), REP<double>(-3.0,4.0)), REP<double>(-INF_D,6.0) );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(-MAX_D,2.0), REP<double>(-3.0,MAX_D)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(1.0,MAX_D), REP<double>(0.0,0.0)), REP<double>(1.0,MAX_D) );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(1.0,MAX_D), REP<double>(-0.0,-0.0)), REP<double>(1.0,MAX_D) );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(0.0,0.0), REP<double>(-3.0,4.0)), REP<double>(-3.0,4.0) );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(-0.0,-0.0), REP<double>(-3.0,MAX_D)), REP<double>(-3.0,MAX_D) );

    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(std::stod("0X1.FFFFFFFFFFFFP+0"),std::stod("0X1.FFFFFFFFFFFFP+0")), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("0X1.0CCCCCCCCCCC4P+1"),std::stod("0X1.0CCCCCCCCCCC5P+1")) );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(std::stod("0X1.FFFFFFFFFFFFP+0"),std::stod("0X1.FFFFFFFFFFFFP+0")), REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("-0X1.999999999999AP-4"))), REP<double>(std::stod("0X1.E666666666656P+0"),std::stod("0X1.E666666666657P+0")) );
    BOOST_CHECK_EQUAL( F<double>::add(REP<double>(std::stod("-0X1.FFFFFFFFFFFFP+0"),std::stod("0X1.FFFFFFFFFFFFP+0")), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("-0X1.E666666666657P+0"),std::stod("0X1.0CCCCCCCCCCC5P+1")) );
}

BOOST_AUTO_TEST_CASE(minimal_sub_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::sub(F<double>::empty(), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::sub(REP<double>(-1.0,1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::sub(F<double>::empty(), REP<double>(-1.0,1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::sub(F<double>::empty(), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::sub(F<double>::entire(), F<double>::empty()) ) );

    BOOST_CHECK_EQUAL( F<double>::sub(F<double>::entire(), REP<double>(-INF_D,1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::sub(F<double>::entire(), REP<double>(-1.0,1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::sub(F<double>::entire(), REP<double>(-1.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::sub(F<double>::entire(), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(-INF_D,1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(-1.0,1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(-1.0,INF_D), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(-INF_D,2.0), REP<double>(-INF_D,4.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(-INF_D,2.0), REP<double>(3.0,4.0)), REP<double>(-INF_D,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(-INF_D,2.0), REP<double>(3.0,INF_D)), REP<double>(-INF_D,-1.0) );

    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(1.0,2.0), REP<double>(-INF_D,4.0)), REP<double>(-3.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(1.0,2.0), REP<double>(3.0,4.0)), REP<double>(-3.0,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(1.0,2.0), REP<double>(3.0,INF_D)), REP<double>(-INF_D,-1.0) );

    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(1.0,INF_D), REP<double>(-INF_D,4.0)), REP<double>(-3.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(1.0,INF_D), REP<double>(3.0,4.0)), REP<double>(-3.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(1.0,INF_D), REP<double>(3.0,INF_D)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(1.0,MAX_D), REP<double>(-3.0,4.0)), REP<double>(-3.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(-MAX_D,2.0), REP<double>(3.0,4.0)), REP<double>(-INF_D,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(-MAX_D,2.0), REP<double>(-MAX_D,4.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(1.0,MAX_D), REP<double>(0.0,0.0)), REP<double>(1.0,MAX_D) );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(1.0,MAX_D), REP<double>(-0.0,-0.0)), REP<double>(1.0,MAX_D) );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(0.0,0.0), REP<double>(-3.0,4.0)), REP<double>(-4.0,3.0) );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(-0.0,-0.0), REP<double>(-3.0,MAX_D)), REP<double>(-MAX_D,3.0) );

    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(std::stod("0X1.FFFFFFFFFFFFP+0"),std::stod("0X1.FFFFFFFFFFFFP+0")), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("0X1.E666666666656P+0"),std::stod("0X1.E666666666657P+0")) );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(std::stod("0X1.FFFFFFFFFFFFP+0"),std::stod("0X1.FFFFFFFFFFFFP+0")), REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("-0X1.999999999999AP-4"))), REP<double>(std::stod("0X1.0CCCCCCCCCCC4P+1"),std::stod("0X1.0CCCCCCCCCCC5P+1")) );
    BOOST_CHECK_EQUAL( F<double>::sub(REP<double>(std::stod("-0X1.FFFFFFFFFFFFP+0"),std::stod("0X1.FFFFFFFFFFFFP+0")), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("-0X1.0CCCCCCCCCCC5P+1"),std::stod("0X1.E666666666657P+0")) );
}

BOOST_AUTO_TEST_CASE(minimal_mul_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::mul(F<double>::empty(), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::mul(REP<double>(-1.0,1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::mul(F<double>::empty(), REP<double>(-1.0,1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::mul(F<double>::empty(), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::mul(F<double>::entire(), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::mul(REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::mul(F<double>::empty(), REP<double>(0.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::mul(REP<double>(-0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::mul(F<double>::empty(), REP<double>(-0.0,-0.0)) ) );

    BOOST_CHECK_EQUAL( F<double>::mul(F<double>::entire(), REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(F<double>::entire(), REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(F<double>::entire(), REP<double>(-5.0, -1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(F<double>::entire(), REP<double>(-5.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(F<double>::entire(), REP<double>(1.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(F<double>::entire(), REP<double>(-INF_D, -1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(F<double>::entire(), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(F<double>::entire(), REP<double>(-5.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(F<double>::entire(), REP<double>(1.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(F<double>::entire(), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,INF_D), REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,INF_D), REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,INF_D), REP<double>(-5.0, -1.0)), REP<double>(-INF_D,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,INF_D), REP<double>(-5.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,INF_D), REP<double>(1.0, 3.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,INF_D), REP<double>(-INF_D, -1.0)), REP<double>(-INF_D,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,INF_D), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,INF_D), REP<double>(-5.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,INF_D), REP<double>(1.0, INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,INF_D), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,INF_D), REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,INF_D), REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,INF_D), REP<double>(-5.0, -1.0)), REP<double>(-INF_D,5.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,INF_D), REP<double>(-5.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,INF_D), REP<double>(1.0, 3.0)), REP<double>(-3.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,INF_D), REP<double>(-INF_D, -1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,INF_D), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,INF_D), REP<double>(-5.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,INF_D), REP<double>(1.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,INF_D), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,3.0), REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,3.0), REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,3.0), REP<double>(-5.0, -1.0)), REP<double>(-15.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,3.0), REP<double>(-5.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,3.0), REP<double>(1.0, 3.0)), REP<double>(-INF_D,9.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,3.0), REP<double>(-INF_D, -1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,3.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,3.0), REP<double>(-5.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,3.0), REP<double>(1.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,3.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,-3.0), REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,-3.0), REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,-3.0), REP<double>(-5.0, -1.0)), REP<double>(3.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,-3.0), REP<double>(-5.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,-3.0), REP<double>(1.0, 3.0)), REP<double>(-INF_D,-3.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,-3.0), REP<double>(-INF_D, -1.0)), REP<double>(3.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,-3.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,-3.0), REP<double>(-5.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,-3.0), REP<double>(1.0, INF_D)), REP<double>(-INF_D,-3.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-INF_D,-3.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(0.0,0.0), REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(0.0,0.0), REP<double>(-5.0, -1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(0.0,0.0), REP<double>(-5.0, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(0.0,0.0), REP<double>(1.0, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(0.0,0.0), REP<double>(-INF_D, -1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(0.0,0.0), REP<double>(-INF_D, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(0.0,0.0), REP<double>(-5.0, INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(0.0,0.0), REP<double>(1.0, INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(0.0,0.0), F<double>::entire()), REP<double>(0.0,0.0) );

    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-0.0,-0.0), REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-0.0,-0.0), REP<double>(-5.0, -1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-0.0,-0.0), REP<double>(-5.0, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-0.0,-0.0), REP<double>(1.0, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-0.0,-0.0), REP<double>(-INF_D, -1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-0.0,-0.0), REP<double>(-INF_D, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-0.0,-0.0), REP<double>(-5.0, INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-0.0,-0.0), REP<double>(1.0, INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-0.0,-0.0), F<double>::entire()), REP<double>(0.0,0.0) );

    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,5.0), REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,5.0), REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,5.0), REP<double>(-5.0, -1.0)), REP<double>(-25.0,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,5.0), REP<double>(-5.0, 3.0)), REP<double>(-25.0,15.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,5.0), REP<double>(1.0, 3.0)), REP<double>(1.0,15.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,5.0), REP<double>(-INF_D, -1.0)), REP<double>(-INF_D,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,5.0), REP<double>(-INF_D, 3.0)), REP<double>(-INF_D,15.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,5.0), REP<double>(-5.0, INF_D)), REP<double>(-25.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,5.0), REP<double>(1.0, INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(1.0,5.0), F<double>::entire()), F<double>::entire() );


    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,5.0), REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,5.0), REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,5.0), REP<double>(-5.0, -1.0)), REP<double>(-25.0,5.0) );

    //min max
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,5.0), REP<double>(-5.0, 3.0)), REP<double>(-25.0,15.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-10.0,2.0), REP<double>(-5.0, 3.0)), REP<double>(-30.0,50.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,5.0), REP<double>(-1.0, 10.0)), REP<double>(-10.0,50.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-2.0,2.0), REP<double>(-5.0, 3.0)), REP<double>(-10.0,10.0) );
    //end min max

    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,5.0), REP<double>(1.0, 3.0)), REP<double>(-3.0,15.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,5.0), REP<double>(-INF_D, -1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,5.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,5.0), REP<double>(-5.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,5.0), REP<double>(1.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-1.0,5.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-10.0,-5.0), REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-10.0,-5.0), REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-10.0,-5.0), REP<double>(-5.0, -1.0)), REP<double>(5.0,50.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-10.0,-5.0), REP<double>(-5.0, 3.0)), REP<double>(-30.0,50.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-10.0,-5.0), REP<double>(1.0, 3.0)), REP<double>(-30.0,-5.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-10.0,-5.0), REP<double>(-INF_D, -1.0)), REP<double>(5.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-10.0,-5.0), REP<double>(-INF_D, 3.0)), REP<double>(-30.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-10.0,-5.0), REP<double>(-5.0, INF_D)), REP<double>(-INF_D,50.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-10.0,-5.0), REP<double>(1.0, INF_D)), REP<double>(-INF_D,-5.0) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(-10.0,-5.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.FFFFFFFFFFFFP+0")), REP<double>(std::stod("-0X1.FFFFFFFFFFFFP+0"), INF_D)), REP<double>(std::stod("-0X1.FFFFFFFFFFFE1P+1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("0X1.FFFFFFFFFFFFP+0")), REP<double>(std::stod("-0X1.FFFFFFFFFFFFP+0"),std::stod("-0X1.999999999999AP-4"))), REP<double>(std::stod("-0X1.FFFFFFFFFFFE1P+1"),std::stod("0X1.999999999998EP-3")) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4")), REP<double>(std::stod("-0X1.FFFFFFFFFFFFP+0"),std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("-0X1.999999999998EP-3"),std::stod("0X1.999999999998EP-3")) );
    BOOST_CHECK_EQUAL( F<double>::mul(REP<double>(std::stod("-0X1.FFFFFFFFFFFFP+0"),std::stod("-0X1.999999999999AP-4")), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.FFFFFFFFFFFFP+0"))), REP<double>(std::stod("-0X1.FFFFFFFFFFFE1P+1"),std::stod("-0X1.47AE147AE147BP-7")) );
}


BOOST_AUTO_TEST_CASE(minimal_div_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::div(F<double>::empty(), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-1.0,1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(F<double>::empty(), REP<double>(-1.0,1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(F<double>::empty(), REP<double>(0.1,1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(F<double>::empty(), REP<double>(-1.0,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(F<double>::empty(), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(F<double>::entire(), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(F<double>::empty(), REP<double>(0.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(F<double>::empty(), REP<double>(-0.0,-0.0)) ) );

    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(-5.0, -3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(3.0, 5.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(-INF_D, -3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(3.0,INF_D)), F<double>::entire() );
BOOST_CHECK( F<double>::is_empty( F<double>::div(F<double>::entire(), REP<double>(0.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(F<double>::entire(), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(-3.0, 0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(-3.0, -0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(0.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(-INF_D, 0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(-0.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(-INF_D, -0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(0.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), REP<double>(-0.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(F<double>::entire(), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(-5.0, -3.0)), REP<double>(3.0,10.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(3.0, 5.0)), REP<double>(-10.0,-3.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(-INF_D, -3.0)), REP<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(3.0,INF_D)), REP<double>(-10.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(-3.0, 0.0)), REP<double>(5.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(-3.0, -0.0)), REP<double>(5.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(0.0, 3.0)), REP<double>(-INF_D,-5.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(-INF_D, 0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(-0.0, 3.0)), REP<double>(-INF_D,-5.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(-INF_D, -0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(0.0, INF_D)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), REP<double>(-0.0, INF_D)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-15.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(-5.0, -3.0)), REP<double>(-5.0,10.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(3.0, 5.0)), REP<double>(-10.0,5.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(-INF_D, -3.0)), REP<double>(-5.0,10.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(3.0,INF_D)), REP<double>(-10.0,5.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-30.0,15.0), REP<double>(0.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-30.0,15.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(-3.0, 0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(-3.0, -0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(0.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(-INF_D, 0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(-0.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(-INF_D, -0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(0.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), REP<double>(-0.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,15.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(-5.0, -3.0)), REP<double>(-10.0,-3.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(3.0, 5.0)), REP<double>(3.0,10.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(-INF_D, -3.0)), REP<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(3.0,INF_D)), REP<double>(0.0,10.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(15.0,30.0), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(-3.0, 0.0)), REP<double>(-INF_D,-5.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(15.0,30.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(-3.0, -0.0)), REP<double>(-INF_D,-5.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(0.0, 3.0)), REP<double>(5.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(-INF_D, 0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(-0.0, 3.0)), REP<double>(5.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(-INF_D, -0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), REP<double>(-0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,30.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(-5.0, -3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(3.0, 5.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(-INF_D, -3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(3.0,INF_D)), REP<double>(0.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(0.0,0.0), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(-3.0, 0.0)), REP<double>(0.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(-3.0, -0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(-3.0, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(0.0, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(-INF_D, 0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(-0.0, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(-INF_D, -0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(-INF_D, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(-3.0, INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(0.0, INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), REP<double>(-0.0, INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,0.0), F<double>::entire()), REP<double>(0.0,0.0) );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(-5.0, -3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(3.0, 5.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(-INF_D, -3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(3.0,INF_D)), REP<double>(0.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(-3.0, 0.0)), REP<double>(0.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(-3.0, -0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(-3.0, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(0.0, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(-INF_D, 0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(-0.0, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(-INF_D, -0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(-INF_D, 3.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(-3.0, INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(0.0, INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), REP<double>(-0.0, INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,-0.0), F<double>::entire()), REP<double>(0.0,0.0) );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(-5.0, -3.0)), REP<double>(3.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(3.0, 5.0)), REP<double>(-INF_D,-3.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(-INF_D, -3.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(3.0,INF_D)), REP<double>(-INF_D,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(-3.0, 0.0)), REP<double>(5.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(-3.0, -0.0)), REP<double>(5.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(0.0, 3.0)), REP<double>(-INF_D,-5.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(-INF_D, 0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(-0.0, 3.0)), REP<double>(-INF_D,-5.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(-INF_D, -0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(0.0, INF_D)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), REP<double>(-0.0, INF_D)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-15.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(-5.0, -3.0)), REP<double>(-5.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(3.0, 5.0)), REP<double>(-INF_D,5.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(-INF_D, -3.0)), REP<double>(-5.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(3.0,INF_D)), REP<double>(-INF_D,5.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(-3.0, 0.0)), F<double>::entire() );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(-3.0, -0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(0.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(-INF_D, 0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(-0.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(-INF_D, -0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(0.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), REP<double>(-0.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,15.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(-5.0, -3.0)), REP<double>(-INF_D,5.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(3.0, 5.0)), REP<double>(-5.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(-INF_D, -3.0)), REP<double>(-INF_D,5.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(3.0,INF_D)), REP<double>(-5.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(-3.0, 0.0)), F<double>::entire() );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(-3.0, -0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(0.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(-INF_D, 0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(-0.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(-INF_D, -0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(0.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), REP<double>(-0.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-15.0,INF_D), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(-5.0, -3.0)), REP<double>(-INF_D,-3.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(3.0, 5.0)), REP<double>(3.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(-INF_D, -3.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(3.0,INF_D)), REP<double>(0.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(15.0,INF_D), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(-3.0, 0.0)), REP<double>(-INF_D,-5.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(15.0,INF_D), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(-3.0, -0.0)), REP<double>(-INF_D,-5.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(0.0, 3.0)), REP<double>(5.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(-INF_D, 0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(-0.0, 3.0)), REP<double>(5.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(-INF_D, -0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), REP<double>(-0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(15.0,INF_D), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(-5.0, -3.0)), REP<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(3.0, 5.0)), REP<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(-INF_D, -3.0)), REP<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(3.0,INF_D)), REP<double>(-10.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-30.0,0.0), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(-3.0, 0.0)), REP<double>(0.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-30.0,0.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(-3.0, -0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(0.0, 3.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(-INF_D, 0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(-0.0, 3.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(-INF_D, -0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(0.0, INF_D)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), REP<double>(-0.0, INF_D)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,0.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(-5.0, -3.0)), REP<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(3.0, 5.0)), REP<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(-INF_D, -3.0)), REP<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(3.0,INF_D)), REP<double>(-10.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(-3.0, 0.0)), REP<double>(0.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(-3.0, -0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(0.0, 3.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(-INF_D, 0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(-0.0, 3.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(-INF_D, -0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(0.0, INF_D)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), REP<double>(-0.0, INF_D)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-30.0,-0.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(-5.0, -3.0)), REP<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(3.0, 5.0)), REP<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(-INF_D, -3.0)), REP<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(3.0,INF_D)), REP<double>(0.0,10.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(0.0,30.0), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(-3.0, 0.0)), REP<double>(-INF_D,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(0.0,30.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(-3.0, -0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(0.0, 3.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(-INF_D, 0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(-0.0, 3.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(-INF_D, -0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), REP<double>(-0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,30.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(-5.0, -3.0)), REP<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(3.0, 5.0)), REP<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(-INF_D, -3.0)), REP<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(3.0,INF_D)), REP<double>(0.0,10.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-0.0,30.0), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(-3.0, 0.0)), REP<double>(-INF_D,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-0.0,30.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(-3.0, -0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(0.0, 3.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(-INF_D, 0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(-0.0, 3.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(-INF_D, -0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), REP<double>(-0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,30.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(-5.0, -3.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(3.0, 5.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(-INF_D, -3.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(3.0,INF_D)), REP<double>(-INF_D,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(-3.0, 0.0)), REP<double>(0.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(-3.0, -0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(0.0, 3.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(-INF_D, 0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(-0.0, 3.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(-INF_D, -0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(0.0, INF_D)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), REP<double>(-0.0, INF_D)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,0.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(-5.0, -3.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(3.0, 5.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(-INF_D, -3.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(3.0,INF_D)), REP<double>(-INF_D,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(-3.0, 0.0)), REP<double>(0.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(-3.0, -0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(-3.0, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(0.0, 3.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(-INF_D, 0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(-0.0, 3.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(-INF_D, -0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(0.0, INF_D)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), REP<double>(-0.0, INF_D)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-0.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(-5.0, -3.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(3.0, 5.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(-INF_D, -3.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(3.0,INF_D)), REP<double>(0.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(0.0,INF_D), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(-3.0, 0.0)), REP<double>(-INF_D,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(0.0,INF_D), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(-3.0, -0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(-3.0, 3.0)), F<double>::entire()  );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(0.0, 3.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(-INF_D, 0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(-0.0, 3.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(-INF_D, -0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), REP<double>(-0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(0.0,INF_D), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(-5.0, -3.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(3.0, 5.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(-INF_D, -3.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(3.0,INF_D)), REP<double>(0.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(0.0,0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(-3.0, 0.0)), REP<double>(-INF_D,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(-3.0, -0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(-3.0, 3.0)), F<double>::entire()  );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(0.0, 3.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(-INF_D, 0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(-0.0, 3.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(-INF_D, -0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(-INF_D, 3.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(-3.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), REP<double>(-0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-0.0,INF_D), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-2.0,-1.0), REP<double>(-10.0, -3.0)), REP<double>(std::stod("0X1.9999999999999P-4"),std::stod("0X1.5555555555556P-1")) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-2.0,-1.0), REP<double>(0.0, 10.0)), REP<double>(-INF_D,std::stod("-0X1.9999999999999P-4")) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-2.0,-1.0), REP<double>(-0.0, 10.0)), REP<double>(-INF_D,std::stod("-0X1.9999999999999P-4")) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-1.0,2.0), REP<double>(10.0,INF_D)), REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-3")) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(1.0,3.0), REP<double>(-INF_D, -10.0)), REP<double>(std::stod("-0X1.3333333333334P-2"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::div(REP<double>(-INF_D,-1.0), REP<double>(1.0, 3.0)), REP<double>(-INF_D,std::stod("-0X1.5555555555555P-2")) );
}

BOOST_AUTO_TEST_CASE(minimal_recip_test)
{
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(-50.0, -10.0)), REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("-0X1.47AE147AE147AP-6")) );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(10.0, 50.0)), REP<double>(std::stod("0X1.47AE147AE147AP-6"),std::stod("0X1.999999999999AP-4")) );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(-INF_D, -10.0)), REP<double>(std::stod("-0X1.999999999999AP-4"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(10.0,INF_D)), REP<double>(0.0,std::stod("0X1.999999999999AP-4")) );
BOOST_CHECK( F<double>::is_empty( F<double>::recip(REP<double>(0.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::recip(REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(-10.0, 0.0)), REP<double>(-INF_D,std::stod("-0X1.9999999999999P-4")) );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(-10.0, -0.0)), REP<double>(-INF_D,std::stod("-0X1.9999999999999P-4")) );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(-10.0, 10.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(0.0, 10.0)), REP<double>(std::stod("0X1.9999999999999P-4"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(-0.0, 10.0)), REP<double>(std::stod("0X1.9999999999999P-4"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(-INF_D, 0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(-INF_D, -0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(-INF_D, 10.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(-10.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::recip(REP<double>(-0.0, INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::recip(F<double>::entire()), F<double>::entire() );
}

BOOST_AUTO_TEST_CASE(minimal_sqr_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::sqr(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::sqr(F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::sqr(REP<double>(-INF_D,-MIN_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::sqr(REP<double>(-1.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr(REP<double>(0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr(REP<double>(-0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr(REP<double>(-5.0,3.0)), REP<double>(0.0,25.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr(REP<double>(-5.0,0.0)), REP<double>(0.0,25.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr(REP<double>(-5.0,-0.0)), REP<double>(0.0,25.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr(REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7")) );
    BOOST_CHECK_EQUAL( F<double>::sqr(REP<double>(std::stod("-0X1.FFFFFFFFFFFFP+0"),std::stod("0X1.999999999999AP-4"))), REP<double>(0.0,std::stod("0X1.FFFFFFFFFFFE1P+1")) );
    BOOST_CHECK_EQUAL( F<double>::sqr(REP<double>(std::stod("-0X1.FFFFFFFFFFFFP+0"),std::stod("-0X1.FFFFFFFFFFFFP+0"))), REP<double>(std::stod("0X1.FFFFFFFFFFFEP+1"),std::stod("0X1.FFFFFFFFFFFE1P+1")) );
}

BOOST_AUTO_TEST_CASE(minimal_sprt_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::sqrt(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::sqrt(F<double>::entire()), REP<double>(0.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::sqrt(REP<double>(-INF_D,-MIN_D)) ) );
    BOOST_CHECK_EQUAL( F<double>::sqrt(REP<double>(-1.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqrt(REP<double>(0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqrt(REP<double>(-0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqrt(REP<double>(-5.0,25.0)), REP<double>(0.0,5.0) );
    BOOST_CHECK_EQUAL( F<double>::sqrt(REP<double>(0.0,25.0)), REP<double>(0.0,5.0) );
    BOOST_CHECK_EQUAL( F<double>::sqrt(REP<double>(-0.0,25.0)), REP<double>(0.0,5.0) );
    BOOST_CHECK_EQUAL( F<double>::sqrt(REP<double>(-5.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::sqrt(REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("0X1.43D136248490FP-2"),std::stod("0X1.43D136248491P-2")) );
    BOOST_CHECK_EQUAL( F<double>::sqrt(REP<double>(std::stod("-0X1.FFFFFFFFFFFFP+0"),std::stod("0X1.999999999999AP-4"))), REP<double>(0.0,std::stod("0X1.43D136248491P-2")) );
    BOOST_CHECK_EQUAL( F<double>::sqrt(REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.FFFFFFFFFFFFP+0"))), REP<double>(std::stod("0X1.43D136248490FP-2"),std::stod("0X1.6A09E667F3BC7P+0")) );
}

BOOST_AUTO_TEST_CASE(minimal_fma_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), F<double>::empty(), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,1.0), F<double>::empty(), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(-1.0,1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), F<double>::entire(), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), F<double>::empty(), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), F<double>::empty(), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), F<double>::empty(), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(-0.0,-0.0), F<double>::empty()) ) );

BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), REP<double>(-0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), REP<double>(-5.0, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), REP<double>(-5.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), REP<double>(1.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), REP<double>(-INF_D, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), REP<double>(-INF_D, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), REP<double>(-5.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), REP<double>(1.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), F<double>::entire(), F<double>::empty()) ) );

BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(1.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-INF_D, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-INF_D, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(1.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,INF_D), F<double>::entire(), F<double>::empty()) ) );

BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(1.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-INF_D, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-INF_D, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(1.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,INF_D), F<double>::entire(), F<double>::empty()) ) );

BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(1.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-INF_D, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-INF_D, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(1.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,3.0), F<double>::entire(), F<double>::empty()) ) );

BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(1.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-INF_D, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-INF_D, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(1.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-INF_D,-3.0), F<double>::entire(), F<double>::empty()) ) );

BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), REP<double>(1.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-INF_D, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-INF_D, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), REP<double>(1.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), F<double>::entire(), F<double>::empty()) ) );

BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(1.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-INF_D, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-INF_D, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(1.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), F<double>::entire(), F<double>::empty()) ) );

BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,5.0), REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,5.0), REP<double>(1.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-INF_D, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-INF_D, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,5.0), REP<double>(1.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(1.0,5.0), F<double>::entire(), F<double>::empty()) ) );

BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, -1.0), F<double>::empty()) ) );
    //min max
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-10.0,2.0), REP<double>(-5.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-1.0, 10.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-2.0,2.0), REP<double>(-5.0, 3.0), F<double>::empty()) ) );
    //end min max
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(1.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-INF_D, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-INF_D, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(1.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,5.0), F<double>::entire(), F<double>::empty()) ) );

BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(1.0, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-INF_D, -1.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-INF_D, 3.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(1.0, INF_D), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-10.0,-5.0), F<double>::entire(), F<double>::empty()) ) );



BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), F<double>::empty(), REP<double>(-INF_D,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,1.0), F<double>::empty(), REP<double>(-INF_D,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(-1.0,1.0), REP<double>(-INF_D,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), F<double>::entire(), REP<double>(-INF_D,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), F<double>::empty(), REP<double>(-INF_D,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), F<double>::empty(), REP<double>(-INF_D,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), F<double>::empty(), REP<double>(-INF_D,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(0.0,0.0), REP<double>(-INF_D,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(-0.0,-0.0), REP<double>(-INF_D,2.0)) ) );

    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(0.0,0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-0.0,-0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-5.0, -1.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-5.0, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(1.0, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-INF_D, -1.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-INF_D, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-5.0, INF_D), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(1.0, INF_D), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), F<double>::entire(), REP<double>(-INF_D,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(0.0,0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-0.0,-0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, -1.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,1.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(1.0, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-INF_D, -1.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,1.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-INF_D, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, INF_D), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(1.0, INF_D), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), F<double>::entire(), REP<double>(-INF_D,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(0.0,0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-0.0,-0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, -1.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,7.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(1.0, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-INF_D, -1.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-INF_D, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, INF_D), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(1.0, INF_D), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), F<double>::entire(), REP<double>(-INF_D,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(0.0,0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-0.0,-0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, -1.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(1.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,11.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-INF_D, -1.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-INF_D, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, INF_D), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(1.0, INF_D), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), F<double>::entire(), REP<double>(-INF_D,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(0.0,0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-0.0,-0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, -1.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(1.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-INF_D, -1.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-INF_D, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, INF_D), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(1.0, INF_D), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), F<double>::entire(), REP<double>(-INF_D,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(0.0,0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, -1.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(1.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-INF_D, -1.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-INF_D, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, INF_D), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(1.0, INF_D), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), F<double>::entire(), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-0.0,-0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, -1.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(1.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-INF_D, -1.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-INF_D, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, INF_D), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(1.0, INF_D), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), F<double>::entire(), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(0.0,0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-0.0,-0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, -1.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,1.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,17.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(1.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,17.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-INF_D, -1.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,1.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-INF_D, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,17.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, INF_D), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(1.0, INF_D), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), F<double>::entire(), REP<double>(-INF_D,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(0.0,0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-0.0,-0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, -1.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,7.0) );
    //min max
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,17.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,2.0), REP<double>(-5.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,52.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-1.0, 10.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,52.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-2.0,2.0), REP<double>(-5.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,12.0) );
    //end min max
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(1.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,17.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-INF_D, -1.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-INF_D, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, INF_D), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(1.0, INF_D), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), F<double>::entire(), REP<double>(-INF_D,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(0.0,0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-0.0,-0.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, -1.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,52.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,52.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(1.0, 3.0), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,-3.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-INF_D, -1.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-INF_D, 3.0), REP<double>(-INF_D,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, INF_D), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,52.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(1.0, INF_D), REP<double>(-INF_D,2.0)), REP<double>(-INF_D,-3.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), F<double>::entire(), REP<double>(-INF_D,2.0)), F<double>::entire() );



BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), F<double>::empty(), REP<double>(-2.0,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,1.0), F<double>::empty(), REP<double>(-2.0,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(-1.0,1.0), REP<double>(-2.0,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), F<double>::entire(), REP<double>(-2.0,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), F<double>::empty(), REP<double>(-2.0,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), F<double>::empty(), REP<double>(-2.0,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), F<double>::empty(), REP<double>(-2.0,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(0.0,0.0), REP<double>(-2.0,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(-0.0,-0.0), REP<double>(-2.0,2.0)) ) );

    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(0.0,0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-0.0,-0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-5.0, -1.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-5.0, 3.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(1.0, 3.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-INF_D, -1.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-INF_D, 3.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-5.0, INF_D), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(1.0, INF_D), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), F<double>::entire(), REP<double>(-2.0,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(0.0,0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-0.0,-0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, -1.0), REP<double>(-2.0,2.0)), REP<double>(-INF_D,1.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, 3.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(1.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-INF_D, -1.0), REP<double>(-2.0,2.0)), REP<double>(-INF_D,1.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-INF_D, 3.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, INF_D), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(1.0, INF_D), REP<double>(-2.0,2.0)), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), F<double>::entire(), REP<double>(-2.0,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(0.0,0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-0.0,-0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, -1.0), REP<double>(-2.0,2.0)), REP<double>(-INF_D,7.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, 3.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(1.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-5.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-INF_D, -1.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-INF_D, 3.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, INF_D), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(1.0, INF_D), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), F<double>::entire(), REP<double>(-2.0,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(0.0,0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,2.0)), REP<double>(-17.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(1.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-INF_D,11.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(1.0, INF_D), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), F<double>::entire(), REP<double>(-2.0,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(0.0,0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,2.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(1.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-INF_D,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,2.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(1.0, INF_D), REP<double>(-2.0,2.0)), REP<double>(-INF_D,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), F<double>::entire(), REP<double>(-2.0,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(0.0,0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(1.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(1.0, INF_D), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), F<double>::entire(), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(1.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(1.0, INF_D), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), F<double>::entire(), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(0.0,0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,2.0)), REP<double>(-27.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-27.0,17.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(1.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-1.0,17.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,2.0)), REP<double>(-INF_D,1.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,2.0)), REP<double>(-INF_D,17.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,2.0)), REP<double>(-27.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(1.0, INF_D), REP<double>(-2.0,2.0)), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), F<double>::entire(), REP<double>(-2.0,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(0.0,0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,2.0)), REP<double>(-27.0,7.0) );
    //min max
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-27.0,17.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,2.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-32.0,52.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-1.0, 10.0), REP<double>(-2.0,2.0)), REP<double>(-12.0,52.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-2.0,2.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-12.0,12.0) );
    //end min max
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(1.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-5.0,17.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(1.0, INF_D), REP<double>(-2.0,2.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), F<double>::entire(), REP<double>(-2.0,2.0)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(0.0,0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,2.0)), REP<double>(3.0,52.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-32.0,52.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(1.0, 3.0), REP<double>(-2.0,2.0)), REP<double>(-32.0,-3.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,2.0)), REP<double>(3.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,2.0)), REP<double>(-32.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,2.0)), REP<double>(-INF_D,52.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(1.0, INF_D), REP<double>(-2.0,2.0)), REP<double>(-INF_D,-3.0) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), F<double>::entire(), REP<double>(-2.0,2.0)), F<double>::entire() );



BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), F<double>::empty(), REP<double>(-2.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,1.0), F<double>::empty(), REP<double>(-2.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(-1.0,1.0), REP<double>(-2.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), F<double>::entire(), REP<double>(-2.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), F<double>::empty(), REP<double>(-2.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), F<double>::empty(), REP<double>(-2.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), F<double>::empty(), REP<double>(-2.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(0.0,0.0), REP<double>(-2.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(-0.0,-0.0), REP<double>(-2.0,INF_D)) ) );

    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(0.0,0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-0.0,-0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-5.0, -1.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-5.0, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(1.0, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-INF_D, -1.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-INF_D, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-5.0, INF_D), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(1.0, INF_D), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), F<double>::entire(), REP<double>(-2.0,INF_D)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(0.0,0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-0.0,-0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, -1.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(1.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-INF_D, -1.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-INF_D, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, INF_D), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(1.0, INF_D), REP<double>(-2.0,INF_D)), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), F<double>::entire(), REP<double>(-2.0,INF_D)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(0.0,0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-0.0,-0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, -1.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(1.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-5.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-INF_D, -1.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-INF_D, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, INF_D), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(1.0, INF_D), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), F<double>::entire(), REP<double>(-2.0,INF_D)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(0.0,0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,INF_D)), REP<double>(-17.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(1.0, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(1.0, INF_D), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), F<double>::entire(), REP<double>(-2.0,INF_D)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(0.0,0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(1.0, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(1.0, INF_D), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), F<double>::entire(), REP<double>(-2.0,INF_D)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(0.0,0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(1.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(1.0, INF_D), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), F<double>::entire(), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(1.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(1.0, INF_D), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), F<double>::entire(), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(0.0,0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,INF_D)), REP<double>(-27.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-27.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(1.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,INF_D)), REP<double>(-27.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(1.0, INF_D), REP<double>(-2.0,INF_D)), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), F<double>::entire(), REP<double>(-2.0,INF_D)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(0.0,0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,INF_D)), REP<double>(-27.0,INF_D) );
    //min max
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-27.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,2.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-32.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-1.0, 10.0), REP<double>(-2.0,INF_D)), REP<double>(-12.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-2.0,2.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-12.0,INF_D) );
    //end min max
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(1.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-5.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(1.0, INF_D), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), F<double>::entire(), REP<double>(-2.0,INF_D)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(0.0,0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-0.0,-0.0), REP<double>(-2.0,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, -1.0), REP<double>(-2.0,INF_D)), REP<double>(3.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-32.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(1.0, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-32.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-INF_D, -1.0), REP<double>(-2.0,INF_D)), REP<double>(3.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-INF_D, 3.0), REP<double>(-2.0,INF_D)), REP<double>(-32.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, INF_D), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(1.0, INF_D), REP<double>(-2.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), F<double>::entire(), REP<double>(-2.0,INF_D)), F<double>::entire() );



BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), F<double>::empty(), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-1.0,1.0), F<double>::empty(), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(-1.0,1.0), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), F<double>::entire(), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::entire(), F<double>::empty(), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(0.0,0.0), F<double>::empty(), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(REP<double>(-0.0,-0.0), F<double>::empty(), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(0.0,0.0), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::fma(F<double>::empty(), REP<double>(-0.0,-0.0), F<double>::entire()) ) );

    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(0.0,0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-0.0,-0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-5.0, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-5.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(1.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-INF_D, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-INF_D, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(-5.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), REP<double>(1.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(F<double>::entire(), F<double>::entire(), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(0.0,0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-0.0,-0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(1.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-INF_D, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-INF_D, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(-5.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), REP<double>(1.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,INF_D), F<double>::entire(), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(0.0,0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-0.0,-0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(1.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-INF_D, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-INF_D, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(-5.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), REP<double>(1.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,INF_D), F<double>::entire(), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(0.0,0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-0.0,-0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(1.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-INF_D, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-INF_D, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(-5.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), REP<double>(1.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,3.0), F<double>::entire(), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(0.0,0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-0.0,-0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(1.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-INF_D, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-INF_D, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(-5.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), REP<double>(1.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-INF_D,-3.0), F<double>::entire(), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(0.0,0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(1.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-INF_D, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-INF_D, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(-5.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), REP<double>(1.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.0,0.0), F<double>::entire(), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-0.0,-0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(1.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-INF_D, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-INF_D, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(-5.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), REP<double>(1.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.0,-0.0), F<double>::entire(), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(0.0,0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-0.0,-0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(1.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-INF_D, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-INF_D, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(-5.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), REP<double>(1.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(1.0,5.0), F<double>::entire(), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(0.0,0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-0.0,-0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, -1.0), F<double>::entire()), F<double>::entire() );
    //min max
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,2.0), REP<double>(-5.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-1.0, 10.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-2.0,2.0), REP<double>(-5.0, 3.0), F<double>::entire()), F<double>::entire() );
    //end min max
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(1.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-INF_D, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-INF_D, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(-5.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), REP<double>(1.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-1.0,5.0), F<double>::entire(), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(0.0,0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-0.0,-0.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(1.0, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-INF_D, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-INF_D, 3.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(-5.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), REP<double>(1.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-10.0,-5.0), F<double>::entire(), F<double>::entire()), F<double>::entire() );


    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(0.1,0.5), REP<double>(-5.0, 3.0), REP<double>(-0.1,0.1)), REP<double>(std::stod("-0X1.4CCCCCCCCCCCDP+1"),std::stod("0X1.999999999999AP+0")) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.5,0.2), REP<double>(-5.0, 3.0), REP<double>(-0.1,0.1)), REP<double>(std::stod("-0X1.999999999999AP+0"),std::stod("0X1.4CCCCCCCCCCCDP+1")) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.5,-0.1), REP<double>(2.0, 3.0), REP<double>(-0.1,0.1)), REP<double>(std::stod("-0X1.999999999999AP+0"),std::stod("-0X1.999999999999AP-4")) );
    BOOST_CHECK_EQUAL( F<double>::fma(REP<double>(-0.5,-0.1), REP<double>(-INF_D, 3.0), REP<double>(-0.1,0.1)), REP<double>(std::stod("-0X1.999999999999AP+0"),INF_D) );
}



BOOST_AUTO_TEST_CASE(minimal_pown_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::pown(F<double>::empty(), 0) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(F<double>::entire(), 0), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,0.0), 0), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,-0.0), 0), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(13.1,13.1), 0), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-7451.145,-7451.145), 0), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), 0), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), 0), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,INF_D), 0), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,INF_D), 0), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,0.0), 0), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,-0.0), 0), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-324.3,2.5), 0), REP<double>(1.0,1.0) );

BOOST_CHECK( F<double>::is_empty( F<double>::pown(F<double>::empty(), 2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(F<double>::entire(), 2), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,0.0), 2), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,-0.0), 2), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(13.1,13.1), 2), REP<double>(std::stod("0X1.573851EB851EBP+7"),std::stod("0X1.573851EB851ECP+7")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-7451.145,-7451.145), 2), REP<double>(std::stod("0X1.A794A4E7CFAADP+25"),std::stod("0X1.A794A4E7CFAAEP+25")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), 2), REP<double>(MAX_D,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), 2), REP<double>(MAX_D,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,INF_D), 2), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,INF_D), 2), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,0.0), 2), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,-0.0), 2), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-324.3,2.5), 2), REP<double>(0.0,std::stod("0X1.9AD27D70A3D72P+16")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.01,2.33), 2), REP<double>(std::stod("0X1.A36E2EB1C432CP-14"),std::stod("0X1.5B7318FC50482P+2")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-1.9,-0.33), 2), REP<double>(std::stod("0X1.BE0DED288CE7P-4"),std::stod("0X1.CE147AE147AE1P+1")) );

BOOST_CHECK( F<double>::is_empty( F<double>::pown(F<double>::empty(), 8) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(F<double>::entire(), 8), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,0.0), 8), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,-0.0), 8), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(13.1,13.1), 8), REP<double>(std::stod("0X1.9D8FD495853F5P+29"),std::stod("0X1.9D8FD495853F6P+29")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-7451.145,-7451.145), 8), REP<double>(std::stod("0X1.DFB1BB622E70DP+102"),std::stod("0X1.DFB1BB622E70EP+102")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), 8), REP<double>(MAX_D,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), 8), REP<double>(MAX_D,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,INF_D), 8), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,INF_D), 8), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,0.0), 8), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,-0.0), 8), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-324.3,2.5), 8), REP<double>(0.0,std::stod("0X1.A87587109655P+66")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.01,2.33), 8), REP<double>(std::stod("0X1.CD2B297D889BDP-54"),std::stod("0X1.B253D9F33CE4DP+9")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-1.9,-0.33), 8), REP<double>(std::stod("0X1.26F1FCDD502A3P-13"),std::stod("0X1.53ABD7BFC4FC6P+7")) );


BOOST_CHECK( F<double>::is_empty( F<double>::pown(F<double>::empty(), 1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(F<double>::entire(), 1), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,0.0), 1), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,-0.0), 1), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(13.1,13.1), 1), REP<double>(13.1,13.1) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-7451.145,-7451.145), 1), REP<double>(-7451.145,-7451.145) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), 1), REP<double>(MAX_D,MAX_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), 1), REP<double>(-MAX_D,-MAX_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,INF_D), 1), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,INF_D), 1), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,0.0), 1), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,-0.0), 1), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-324.3,2.5), 1), REP<double>(-324.3,2.5) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.01,2.33), 1), REP<double>(0.01,2.33) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-1.9,-0.33), 1), REP<double>(-1.9,-0.33) );

BOOST_CHECK( F<double>::is_empty( F<double>::pown(F<double>::empty(), 3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(F<double>::entire(), 3), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,0.0), 3), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,-0.0), 3), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(13.1,13.1), 3), REP<double>(std::stod("0X1.1902E978D4FDEP+11"),std::stod("0X1.1902E978D4FDFP+11")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-7451.145,-7451.145), 3), REP<double>(std::stod("-0X1.81460637B9A3DP+38"),std::stod("-0X1.81460637B9A3CP+38")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), 3), REP<double>(MAX_D,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), 3), REP<double>(-INF_D,-MAX_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,INF_D), 3), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,INF_D), 3), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,0.0), 3), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,-0.0), 3), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-324.3,2.5), 3), REP<double>(std::stod("-0X1.0436D2F418938P+25"),std::stod("0X1.F4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.01,2.33), 3), REP<double>(std::stod("0X1.0C6F7A0B5ED8DP-20"),std::stod("0X1.94C75E6362A6P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-1.9,-0.33), 3), REP<double>(std::stod("-0X1.B6F9DB22D0E55P+2"),std::stod("-0X1.266559F6EC5B1P-5")) );

BOOST_CHECK( F<double>::is_empty( F<double>::pown(F<double>::empty(), 7) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(F<double>::entire(), 7), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,0.0), 7), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,-0.0), 7), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(13.1,13.1), 7), REP<double>(std::stod("0X1.F91D1B185493BP+25"),std::stod("0X1.F91D1B185493CP+25")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-7451.145,-7451.145), 7), REP<double>(std::stod("-0X1.07B1DA32F9B59P+90"),std::stod("-0X1.07B1DA32F9B58P+90")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), 7), REP<double>(MAX_D,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), 7), REP<double>(-INF_D,-MAX_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,INF_D), 7), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,INF_D), 7), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,0.0), 7), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,-0.0), 7), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-324.3,2.5), 7), REP<double>(std::stod("-0X1.4F109959E6D7FP+58"),std::stod("0X1.312DP+9")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.01,2.33), 7), REP<double>(std::stod("0X1.6849B86A12B9BP-47"),std::stod("0X1.74D0373C76313P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-1.9,-0.33), 7), REP<double>(std::stod("-0X1.658C775099757P+6"),std::stod("-0X1.BEE30301BF47AP-12")) );


BOOST_CHECK( F<double>::is_empty( F<double>::pown(F<double>::empty(), -2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(F<double>::entire(), -2), REP<double>(0.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::pown(REP<double>(0.0,0.0), -2) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pown(REP<double>(-0.0,-0.0), -2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(13.1,13.1), -2), REP<double>(std::stod("0X1.7DE3A077D1568P-8"),std::stod("0X1.7DE3A077D1569P-8")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-7451.145,-7451.145), -2), REP<double>(std::stod("0X1.3570290CD6E14P-26"),std::stod("0X1.3570290CD6E15P-26")) );
//    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), -2), REP<double>(std::stod("0X0P+0"),std::stod("0X1P-1022")) );    //not F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), -2), REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")) );     // F<double>::subnormalized
//    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), -2), REP<double>(std::stod("0X0P+0"),std::stod("0X1P-1022")) );   not F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), -2), REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")) );   // F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,INF_D), -2), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,INF_D), -2), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,0.0), -2), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,-0.0), -2), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-324.3,2.5), -2), REP<double>(std::stod("0X1.3F0C482C977C9P-17"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.01,2.33), -2), REP<double>(std::stod("0X1.793D85EF38E47P-3"),std::stod("0X1.388P+13")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-1.9,-0.33), -2), REP<double>(std::stod("0X1.1BA81104F6C8P-2"),std::stod("0X1.25D8FA1F801E1P+3")) );

BOOST_CHECK( F<double>::is_empty( F<double>::pown(F<double>::empty(), -8) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(F<double>::entire(), -8), REP<double>(0.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::pown(REP<double>(0.0,0.0), -8) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pown(REP<double>(-0.0,-0.0), -8) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(13.1,13.1), -8), REP<double>(std::stod("0X1.3CEF39247CA6DP-30"),std::stod("0X1.3CEF39247CA6EP-30")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-7451.145,-7451.145), -8), REP<double>(std::stod("0X1.113D9EF0A99ACP-103"),std::stod("0X1.113D9EF0A99ADP-103")) );
//    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), -8), REP<double>(std::stod("0X0P+0"),std::stod("0X1P-1022")) );    not F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), -8), REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")) );    // F<double>::subnormalized
//    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), -8), REP<double>(std::stod("0X0P+0"),std::stod("0X1P-1022")) );   not F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), -8), REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")) );   // F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,INF_D), -8), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,INF_D), -8), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,0.0), -8), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,-0.0), -8), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-324.3,2.5), -8), REP<double>(std::stod("0X1.34CC3764D1E0CP-67"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.01,2.33), -8), REP<double>(std::stod("0X1.2DC80DB11AB7CP-10"),std::stod("0X1.1C37937E08P+53")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-1.9,-0.33), -8), REP<double>(std::stod("0X1.81E104E61630DP-8"),std::stod("0X1.BC64F21560E34P+12")) );


BOOST_CHECK( F<double>::is_empty( F<double>::pown(F<double>::empty(), -1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(F<double>::entire(), -1), F<double>::entire() );
BOOST_CHECK( F<double>::is_empty( F<double>::pown(REP<double>(0.0,0.0), -1) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pown(REP<double>(-0.0,-0.0), -1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(13.1,13.1), -1), REP<double>(std::stod("0X1.38ABF82EE6986P-4"),std::stod("0X1.38ABF82EE6987P-4")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-7451.145,-7451.145), -1), REP<double>(std::stod("-0X1.197422C9048BFP-13"),std::stod("-0X1.197422C9048BEP-13")) );
//    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), -1), REP<double>(std::stod("0X0P+0"),std::stod("0X1P-1022")) );   not F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), -1), REP<double>(std::stod("0X0.4P-1022"),std::stod("0X0.4000000000001P-1022")) );   // F<double>::subnormalized
//    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), -1), REP<double>(std::stod("-0X1P-1022"),std::stod("-0X0P+0")) );   not F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), -1), REP<double>(std::stod("-0X0.4000000000001P-1022"),std::stod("-0X0.4P-1022")) );   // F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,INF_D), -1), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,INF_D), -1), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,0.0), -1), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,-0.0), -1), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-324.3,2.5), -1), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.01,2.33), -1), REP<double>(std::stod("0X1.B77C278DBBE13P-2"),std::stod("0X1.9P+6")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-1.9,-0.33), -1), REP<double>(std::stod("-0X1.83E0F83E0F83EP+1"),std::stod("-0X1.0D79435E50D79P-1")) );

BOOST_CHECK( F<double>::is_empty( F<double>::pown(F<double>::empty(), -3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(F<double>::entire(), -3), F<double>::entire() );
BOOST_CHECK( F<double>::is_empty( F<double>::pown(REP<double>(0.0,0.0), -3) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pown(REP<double>(-0.0,-0.0), -3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(13.1,13.1), -3), REP<double>(std::stod("0X1.D26DF4D8B1831P-12"),std::stod("0X1.D26DF4D8B1832P-12")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-7451.145,-7451.145), -3), REP<double>(std::stod("-0X1.54347DED91B19P-39"),std::stod("-0X1.54347DED91B18P-39")) );
//    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), -3), REP<double>(std::stod("0X0P+0"),std::stod("0X1P-1022")) );   not F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), -3), REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")) );   // F<double>::subnormalized
//    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), -3), REP<double>(std::stod("-0X1P-1022"),std::stod("-0X0P+0")) );   not F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), -3), REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("-0X0P+0")) );   // F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,INF_D), -3), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,INF_D), -3), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,0.0), -3), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,-0.0), -3), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-324.3,2.5), -3), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.01,2.33), -3), REP<double>(std::stod("0X1.43CFBA61AACABP-4"),std::stod("0X1.E848P+19")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-1.9,-0.33), -3), REP<double>(std::stod("-0X1.BD393CE9E8E7CP+4"),std::stod("-0X1.2A95F6F7C066CP-3")) );

BOOST_CHECK( F<double>::is_empty( F<double>::pown(F<double>::empty(), -7) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(F<double>::entire(), -7), F<double>::entire() );
BOOST_CHECK( F<double>::is_empty( F<double>::pown(REP<double>(0.0,0.0), -7) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pown(REP<double>(-0.0,-0.0), -7) ) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(13.1,13.1), -7), REP<double>(std::stod("0X1.037D76C912DBCP-26"),std::stod("0X1.037D76C912DBDP-26")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-7451.145,-7451.145), -7), REP<double>(std::stod("-0X1.F10F41FB8858FP-91"),std::stod("-0X1.F10F41FB8858EP-91")) );
//    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), -7), REP<double>(std::stod("0X0P+0"),std::stod("0X1P-1022")) );   not F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(MAX_D,MAX_D), -7), REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")) );   // F<double>::subnormalized
//    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), -7), REP<double>(std::stod("-0X1P-1022"),std::stod("-0X0P+0")) );   not F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-MAX_D,-MAX_D), -7), REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("-0X0P+0")) );   // F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.0,INF_D), -7), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-0.0,INF_D), -7), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,0.0), -7), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-INF_D,-0.0), -7), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-324.3,2.5), -7), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(0.01,2.33), -7), REP<double>(std::stod("0X1.5F934D64162A9P-9"),std::stod("0X1.6BCC41E9P+46")) );
    BOOST_CHECK_EQUAL( F<double>::pown(REP<double>(-1.9,-0.33), -7), REP<double>(std::stod("-0X1.254CDD3711DDBP+11"),std::stod("-0X1.6E95C4A761E19P-7")) );
}

BOOST_AUTO_TEST_CASE(minimal_pow_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::pow(F<double>::empty(), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(F<double>::empty(), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(F<double>::empty(), REP<double>(-INF_D,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(F<double>::empty(), REP<double>(-INF_D,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(F<double>::empty(), REP<double>(-INF_D,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(F<double>::empty(), REP<double>(0.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(F<double>::empty(), REP<double>(-0.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(F<double>::empty(), REP<double>(1.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(F<double>::empty(), REP<double>(-3.0,5.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(F<double>::empty(), REP<double>(0.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(F<double>::empty(), REP<double>(-0.0,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(F<double>::empty(), REP<double>(-5.0,-5.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(F<double>::empty(), REP<double>(5.0,5.0)) ) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.1,0.5), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(0.0,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-0.0,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(0.0,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-0.0,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(0.1,0.1)), REP<double>(std::stod("0X1.96B230BCDC434P-1"),std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(0.1,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(0.1,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(0.1,INF_D)), REP<double>(0.0,std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(1.0,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(1.0,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),std::stod("0X1P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(1.0,INF_D)), REP<double>(0.0,std::stod("0X1P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(2.5,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),std::stod("0X1.6A09E667F3BCDP-3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(2.5,INF_D)), REP<double>(0.0,std::stod("0X1.6A09E667F3BCDP-3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-0.1,0.1)), REP<double>(std::stod("0X1.96B230BCDC434P-1"),std::stod("0X1.4248EF8FC2604P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-0.1,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.4248EF8FC2604P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-0.1,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),std::stod("0X1.4248EF8FC2604P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-0.1,INF_D)), REP<double>(0.0,std::stod("0X1.4248EF8FC2604P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-1.0,0.1)), REP<double>(std::stod("0X1.96B230BCDC434P-1"),std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-1.0,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-1.0,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-1.0,INF_D)), REP<double>(0.0,std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-2.5,0.1)), REP<double>(std::stod("0X1.96B230BCDC434P-1"),std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-2.5,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-2.5,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-2.5,INF_D)), REP<double>(0.0,std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-INF_D,0.1)), REP<double>(std::stod("0X1.96B230BCDC434P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-INF_D,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-INF_D,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-1.0,0.0)), REP<double>(1.0,std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-1.0,-0.0)), REP<double>(1.0,std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-2.5,0.0)), REP<double>(1.0,std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-2.5,-0.0)), REP<double>(1.0,std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-INF_D,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-INF_D,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-0.1,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),std::stod("0X1.4248EF8FC2604P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-1.0,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-2.5,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-INF_D,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-1.0,-1.0)), REP<double>(std::stod("0X1P+1"),std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-2.5,-1.0)), REP<double>(std::stod("0X1P+1"),std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-INF_D,-1.0)), REP<double>(std::stod("0X1P+1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-2.5,-2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP+2"),std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,0.5), REP<double>(-INF_D,-2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP+2"),INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.1,1.0), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(0.0,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-0.0,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(0.0,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-0.0,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(0.1,0.1)), REP<double>(std::stod("0X1.96B230BCDC434P-1"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(0.1,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(0.1,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(0.1,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(1.0,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(1.0,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(1.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(2.5,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(2.5,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-0.1,0.1)), REP<double>(std::stod("0X1.96B230BCDC434P-1"),std::stod("0X1.4248EF8FC2604P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-0.1,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.4248EF8FC2604P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-0.1,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),std::stod("0X1.4248EF8FC2604P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-0.1,INF_D)), REP<double>(0.0,std::stod("0X1.4248EF8FC2604P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-1.0,0.1)), REP<double>(std::stod("0X1.96B230BCDC434P-1"),std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-1.0,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-1.0,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-1.0,INF_D)), REP<double>(0.0,std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-2.5,0.1)), REP<double>(std::stod("0X1.96B230BCDC434P-1"),std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-2.5,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-2.5,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-2.5,INF_D)), REP<double>(0.0,std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-INF_D,0.1)), REP<double>(std::stod("0X1.96B230BCDC434P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-INF_D,1.0)), REP<double>(std::stod("0X1.999999999999AP-4"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-INF_D,2.5)), REP<double>(std::stod("0X1.9E7C6E43390B7P-9"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-0.1,0.0)), REP<double>(1.0,std::stod("0X1.4248EF8FC2604P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-0.1,-0.0)), REP<double>(1.0,std::stod("0X1.4248EF8FC2604P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-1.0,0.0)), REP<double>(1.0,std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-1.0,-0.0)), REP<double>(1.0,std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-2.5,0.0)), REP<double>(1.0,std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-2.5,-0.0)), REP<double>(1.0,std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-INF_D,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-INF_D,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-0.1,-0.1)), REP<double>(1.0,std::stod("0X1.4248EF8FC2604P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-1.0,-0.1)), REP<double>(1.0,std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-2.5,-0.1)), REP<double>(1.0,std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-INF_D,-0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-1.0,-1.0)), REP<double>(1.0,std::stod("0X1.4P+3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-2.5,-1.0)), REP<double>(1.0,std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-INF_D,-1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-2.5,-2.5)), REP<double>(1.0,std::stod("0X1.3C3A4EDFA9758P+8")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.1,1.0), REP<double>(-INF_D,-2.5)), REP<double>(1.0,INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.5,1.5), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(0.0,1.0)), REP<double>(0.5,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-0.0,1.0)), REP<double>(0.5,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(0.0,2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP-3"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-0.0,2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP-3"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(0.1,0.1)), REP<double>(std::stod("0X1.DDB680117AB12P-1"),std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(0.1,1.0)), REP<double>(0.5,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(0.1,2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP-3"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(1.0,1.0)), REP<double>(0.5,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(1.0,2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP-3"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(2.5,2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP-3"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-0.1,0.1)), REP<double>(std::stod("0X1.DDB680117AB12P-1"),std::stod("0X1.125FBEE250665P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-0.1,1.0)), REP<double>(std::stod("0X1P-1"),std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-0.1,2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP-3"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-0.1,INF_D)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-1.0,0.1)), REP<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-1.0,1.0)), REP<double>(std::stod("0X1P-1"),std::stod("0X1P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-1.0,2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP-3"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-1.0,INF_D)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-2.5,0.1)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.6A09E667F3BCDP+2")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-2.5,1.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.6A09E667F3BCDP+2")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-2.5,2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP-3"),std::stod("0X1.6A09E667F3BCDP+2")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-2.5,INF_D)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-INF_D,0.1)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-INF_D,1.0)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-INF_D,2.5)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), F<double>::entire()), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-1.0,0.0)), REP<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-1.0,-0.0)), REP<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-2.5,0.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.6A09E667F3BCDP+2")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-2.5,-0.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.6A09E667F3BCDP+2")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-INF_D,0.0)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-INF_D,-0.0)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-0.1,-0.1)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),std::stod("0X1.125FBEE250665P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-1.0,-0.1)), REP<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-2.5,-0.1)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.6A09E667F3BCDP+2")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-INF_D,-0.1)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-1.0,-1.0)), REP<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-2.5,-1.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.6A09E667F3BCDP+2")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-INF_D,-1.0)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-2.5,-2.5)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.6A09E667F3BCDP+2")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,1.5), REP<double>(-INF_D,-2.5)), REP<double>(std::stod("0X0P+0"),INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.5,INF_D), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(0.0,1.0)), REP<double>(0.5,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-0.0,1.0)), REP<double>(0.5,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(0.0,2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP-3"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-0.0,2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP-3"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(0.1,0.1)), REP<double>(std::stod("0X1.DDB680117AB12P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(0.1,1.0)), REP<double>(0.5,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(0.1,2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP-3"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(1.0,1.0)), REP<double>(0.5,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(1.0,2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP-3"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(2.5,2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP-3"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-1.0,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-2.5,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-2.5,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-INF_D,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-INF_D,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-INF_D,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-1.0,0.0)), REP<double>(0.0,std::stod("0X1P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-1.0,-0.0)), REP<double>(0.0,std::stod("0X1P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-2.5,0.0)), REP<double>(0.0,std::stod("0X1.6A09E667F3BCDP+2")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-2.5,-0.0)), REP<double>(0.0,std::stod("0X1.6A09E667F3BCDP+2")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-INF_D,0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-INF_D,-0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-0.1,-0.1)), REP<double>(0.0,std::stod("0X1.125FBEE250665P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-1.0,-0.1)), REP<double>(0.0,std::stod("0X1P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-2.5,-0.1)), REP<double>(0.0,std::stod("0X1.6A09E667F3BCDP+2")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-INF_D,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-1.0,-1.0)), REP<double>(0.0,std::stod("0X1P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-2.5,-1.0)), REP<double>(0.0,std::stod("0X1.6A09E667F3BCDP+2")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-INF_D,-1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-INF_D,-2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.5,INF_D), REP<double>(-2.5,-2.5)), REP<double>(0.0,std::stod("0X1.6A09E667F3BCDP+2")) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(1.0,1.5), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(0.0,1.0)), REP<double>(1.0,std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-0.0,1.0)), REP<double>(1.0,std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(0.0,2.5)), REP<double>(1.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-0.0,2.5)), REP<double>(1.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(0.1,0.1)), REP<double>(1.0,std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(0.1,1.0)), REP<double>(1.0,std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(0.1,2.5)), REP<double>(1.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(0.1,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(1.0,1.0)), REP<double>(1.0,std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(1.0,2.5)), REP<double>(1.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(1.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(2.5,2.5)), REP<double>(1.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(2.5,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-0.1,0.1)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-0.1,1.0)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-0.1,2.5)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-0.1,INF_D)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-1.0,0.1)), REP<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-1.0,1.0)), REP<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-1.0,2.5)), REP<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-1.0,INF_D)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-2.5,0.1)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-2.5,1.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-2.5,2.5)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-2.5,INF_D)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-INF_D,0.1)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-INF_D,1.0)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-INF_D,2.5)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), F<double>::entire()), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-1.0,0.0)), REP<double>(std::stod("0X1.5555555555555P-1"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-1.0,-0.0)), REP<double>(std::stod("0X1.5555555555555P-1"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-2.5,0.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-2.5,-0.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-INF_D,0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-INF_D,-0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-0.1,-0.1)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-1.0,-0.1)), REP<double>(std::stod("0X1.5555555555555P-1"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-2.5,-0.1)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-INF_D,-0.1)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-1.0,-1.0)), REP<double>(std::stod("0X1.5555555555555P-1"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-2.5,-1.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-INF_D,-1.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-2.5,-2.5)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,1.5), REP<double>(-INF_D,-2.5)), REP<double>(std::stod("0X0P+0"),1.0) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(1.0,INF_D), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(0.0,1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-0.0,1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(0.0,2.5)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-0.0,2.5)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(0.1,0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(0.1,1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(0.1,2.5)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(0.1,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(1.0,1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(1.0,2.5)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(1.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(2.5,2.5)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(2.5,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-0.1,0.1)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-0.1,1.0)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-0.1,2.5)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-0.1,INF_D)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-1.0,0.1)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-1.0,1.0)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-1.0,2.5)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-1.0,INF_D)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-2.5,0.1)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-2.5,1.0)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-2.5,2.5)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-2.5,INF_D)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-INF_D,0.1)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-INF_D,1.0)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-INF_D,2.5)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), F<double>::entire()), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-1.0,0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-1.0,-0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-2.5,0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-2.5,-0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-INF_D,0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-INF_D,-0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-0.1,-0.1)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-1.0,-0.1)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-2.5,-0.1)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-INF_D,-0.1)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-1.0,-1.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-2.5,-1.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-INF_D,-1.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-2.5,-2.5)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.0,INF_D), REP<double>(-INF_D,-2.5)), REP<double>(std::stod("0X0P+0"),1.0) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(1.1,1.5), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(0.0,1.0)), REP<double>(1.0,std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-0.0,1.0)), REP<double>(1.0,std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(0.0,2.5)), REP<double>(1.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-0.0,2.5)), REP<double>(1.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(0.1,0.1)), REP<double>(std::stod("0X1.02739C65D58BFP+0"),std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(0.1,1.0)), REP<double>(std::stod("0X1.02739C65D58BFP+0"),std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(0.1,2.5)), REP<double>(std::stod("0X1.02739C65D58BFP+0"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(0.1,INF_D)), REP<double>(std::stod("0X1.02739C65D58BFP+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(1.0,1.0)), REP<double>(std::stod("0X1.199999999999AP+0"),std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(1.0,2.5)), REP<double>(std::stod("0X1.199999999999AP+0"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(1.0,INF_D)), REP<double>(std::stod("0X1.199999999999AP+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(2.5,2.5)), REP<double>(std::stod("0X1.44E1080833B25P+0"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(2.5,INF_D)), REP<double>(std::stod("0X1.44E1080833B25P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-0.1,0.1)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-0.1,1.0)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-0.1,2.5)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-0.1,INF_D)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-1.0,0.1)), REP<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-1.0,1.0)), REP<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-1.0,2.5)), REP<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-1.0,INF_D)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-2.5,0.1)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-2.5,1.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-2.5,2.5)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-2.5,INF_D)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-INF_D,0.1)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-INF_D,1.0)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.8P+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-INF_D,2.5)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), F<double>::entire()), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-1.0,0.0)), REP<double>(std::stod("0X1.5555555555555P-1"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-1.0,-0.0)), REP<double>(std::stod("0X1.5555555555555P-1"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-2.5,0.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-2.5,-0.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-INF_D,0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-INF_D,-0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-0.1,-0.1)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),std::stod("0X1.FB24AF5281928P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-1.0,-0.1)), REP<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1.FB24AF5281928P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-2.5,-0.1)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.FB24AF5281928P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-INF_D,-0.1)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.FB24AF5281928P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-1.0,-1.0)), REP<double>(std::stod("0X1.5555555555555P-1"),std::stod("0X1.D1745D1745D17P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-2.5,-1.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.D1745D1745D17P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-INF_D,-1.0)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.D1745D1745D17P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-2.5,-2.5)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),std::stod("0X1.9372D999784C8P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,1.5), REP<double>(-INF_D,-2.5)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.9372D999784C8P-1")) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(1.1,INF_D), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(0.0,1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-0.0,1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(0.0,2.5)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-0.0,2.5)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(0.1,0.1)), REP<double>(std::stod("0X1.02739C65D58BFP+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(0.1,1.0)), REP<double>(std::stod("0X1.02739C65D58BFP+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(0.1,2.5)), REP<double>(std::stod("0X1.02739C65D58BFP+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(0.1,INF_D)), REP<double>(std::stod("0X1.02739C65D58BFP+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(1.0,1.0)), REP<double>(std::stod("0X1.199999999999AP+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(1.0,2.5)), REP<double>(std::stod("0X1.199999999999AP+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(1.0,INF_D)), REP<double>(std::stod("0X1.199999999999AP+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(2.5,2.5)), REP<double>(std::stod("0X1.44E1080833B25P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(2.5,INF_D)), REP<double>(std::stod("0X1.44E1080833B25P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-0.1,0.1)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-0.1,1.0)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-0.1,2.5)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-0.1,INF_D)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-1.0,0.1)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-1.0,1.0)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-1.0,2.5)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-1.0,INF_D)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-2.5,0.1)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-2.5,1.0)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-2.5,2.5)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-2.5,INF_D)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-INF_D,0.1)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-INF_D,1.0)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-INF_D,2.5)), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), F<double>::entire()), REP<double>(std::stod("0X0P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-1.0,0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-1.0,-0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-2.5,0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-2.5,-0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-INF_D,0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-INF_D,-0.0)), REP<double>(std::stod("0X0P+0"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-0.1,-0.1)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.FB24AF5281928P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-1.0,-0.1)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.FB24AF5281928P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-2.5,-0.1)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.FB24AF5281928P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-INF_D,-0.1)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.FB24AF5281928P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-1.0,-1.0)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.D1745D1745D17P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-2.5,-1.0)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.D1745D1745D17P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-INF_D,-1.0)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.D1745D1745D17P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-2.5,-2.5)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.9372D999784C8P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(1.1,INF_D), REP<double>(-INF_D,-2.5)), REP<double>(std::stod("0X0P+0"),std::stod("0X1.9372D999784C8P-1")) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.5), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(0.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-0.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(0.1,0.1)), REP<double>(0.0,std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(0.1,1.0)), REP<double>(0.0,std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(0.1,2.5)), REP<double>(0.0,std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(0.1,INF_D)), REP<double>(0.0,std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(1.0,1.0)), REP<double>(0.0,0.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(1.0,2.5)), REP<double>(0.0,0.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(1.0,INF_D)), REP<double>(0.0,0.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(2.5,2.5)), REP<double>(0.0,std::stod("0X1.6A09E667F3BCDP-3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(2.5,INF_D)), REP<double>(0.0,std::stod("0X1.6A09E667F3BCDP-3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-1.0,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-2.5,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-2.5,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-INF_D,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-INF_D,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-INF_D,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-1.0,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-1.0,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-2.5,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-2.5,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-INF_D,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-INF_D,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-0.1,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-1.0,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-2.5,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-INF_D,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-1.0,-1.0)), REP<double>(std::stod("0X1P+1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-2.5,-1.0)), REP<double>(std::stod("0X1P+1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-INF_D,-1.0)), REP<double>(std::stod("0X1P+1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-2.5,-2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP+2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.5), REP<double>(-INF_D,-2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP+2"),INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,1.0), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(0.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-0.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(0.1,0.1)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(0.1,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(0.1,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(0.1,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(1.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(1.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(1.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(2.5,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(2.5,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-1.0,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-2.5,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-2.5,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-INF_D,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-INF_D,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-INF_D,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-0.1,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-0.1,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-1.0,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-1.0,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-2.5,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-2.5,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-INF_D,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-INF_D,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-0.1,-0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-1.0,-0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-2.5,-0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-INF_D,-0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-1.0,-1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-2.5,-1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-INF_D,-1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-2.5,-2.5)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.0), REP<double>(-INF_D,-2.5)), REP<double>(1.0,INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,1.5), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(0.0,1.0)), REP<double>(0.0,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-0.0,1.0)), REP<double>(0.0,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(0.0,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-0.0,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(0.1,0.1)), REP<double>(0.0,std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(0.1,1.0)), REP<double>(0.0,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(0.1,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(1.0,1.0)), REP<double>(0.0,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(1.0,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(2.5,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-1.0,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-2.5,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-2.5,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-INF_D,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-INF_D,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-INF_D,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-1.0,0.0)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-1.0,-0.0)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-2.5,0.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-2.5,-0.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-INF_D,0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-INF_D,-0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-0.1,-0.1)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-1.0,-0.1)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-2.5,-0.1)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-INF_D,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-1.0,-1.0)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-2.5,-1.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-INF_D,-1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-2.5,-2.5)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,1.5), REP<double>(-INF_D,-2.5)), REP<double>(0.0,INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,INF_D), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(0.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-0.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(0.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-0.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-1.0,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-2.5,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-2.5,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-INF_D,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-INF_D,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-INF_D,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-1.0,0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-1.0,-0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-2.5,0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-2.5,-0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-INF_D,0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-INF_D,-0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-0.1,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-1.0,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-2.5,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-INF_D,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-1.0,-1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-2.5,-1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-INF_D,-1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-INF_D,-2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,INF_D), REP<double>(-2.5,-2.5)), REP<double>(0.0,INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.5), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(0.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-0.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(0.1,0.1)), REP<double>(0.0,std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(0.1,1.0)), REP<double>(0.0,std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(0.1,2.5)), REP<double>(0.0,std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(0.1,INF_D)), REP<double>(0.0,std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(1.0,1.0)), REP<double>(0.0,0.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(1.0,2.5)), REP<double>(0.0,0.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(1.0,INF_D)), REP<double>(0.0,0.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(2.5,2.5)), REP<double>(0.0,std::stod("0X1.6A09E667F3BCDP-3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(2.5,INF_D)), REP<double>(0.0,std::stod("0X1.6A09E667F3BCDP-3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-1.0,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-2.5,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-2.5,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-INF_D,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-INF_D,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-INF_D,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-1.0,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-1.0,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-2.5,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-2.5,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-INF_D,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-INF_D,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-0.1,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-1.0,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-2.5,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-INF_D,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-1.0,-1.0)), REP<double>(std::stod("0X1P+1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-2.5,-1.0)), REP<double>(std::stod("0X1P+1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-INF_D,-1.0)), REP<double>(std::stod("0X1P+1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-2.5,-2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP+2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.5), REP<double>(-INF_D,-2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP+2"),INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,1.0), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(0.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-0.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(0.1,0.1)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(0.1,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(0.1,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(0.1,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(1.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(1.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(1.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(2.5,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(2.5,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-1.0,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-2.5,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-2.5,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-INF_D,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-INF_D,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-INF_D,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-0.1,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-0.1,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-1.0,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-1.0,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-2.5,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-2.5,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-INF_D,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-INF_D,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-0.1,-0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-1.0,-0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-2.5,-0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-INF_D,-0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-1.0,-1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-2.5,-1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-INF_D,-1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-2.5,-2.5)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.0), REP<double>(-INF_D,-2.5)), REP<double>(1.0,INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,1.5), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(0.0,1.0)), REP<double>(0.0,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-0.0,1.0)), REP<double>(0.0,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(0.0,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-0.0,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(0.1,0.1)), REP<double>(0.0,std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(0.1,1.0)), REP<double>(0.0,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(0.1,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(1.0,1.0)), REP<double>(0.0,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(1.0,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(2.5,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-1.0,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-2.5,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-2.5,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-INF_D,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-INF_D,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-INF_D,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-1.0,0.0)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-1.0,-0.0)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-2.5,0.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-2.5,-0.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-INF_D,0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-INF_D,-0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-0.1,-0.1)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-1.0,-0.1)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-2.5,-0.1)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-INF_D,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-1.0,-1.0)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-2.5,-1.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-INF_D,-1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-2.5,-2.5)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,1.5), REP<double>(-INF_D,-2.5)), REP<double>(0.0,INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,INF_D), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(0.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-0.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(0.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-0.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-1.0,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-2.5,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-2.5,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-INF_D,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-INF_D,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-INF_D,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-1.0,0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-1.0,-0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-2.5,0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-2.5,-0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-INF_D,0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-INF_D,-0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-0.1,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-1.0,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-2.5,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-INF_D,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-1.0,-1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-2.5,-1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-INF_D,-1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-INF_D,-2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,INF_D), REP<double>(-2.5,-2.5)), REP<double>(0.0,INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.1,0.5), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(0.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-0.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(0.1,0.1)), REP<double>(0.0,std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(0.1,1.0)), REP<double>(0.0,std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(0.1,2.5)), REP<double>(0.0,std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(0.1,INF_D)), REP<double>(0.0,std::stod("0X1.DDB680117AB13P-1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(1.0,1.0)), REP<double>(0.0,0.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(1.0,2.5)), REP<double>(0.0,0.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(1.0,INF_D)), REP<double>(0.0,0.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(2.5,2.5)), REP<double>(0.0,std::stod("0X1.6A09E667F3BCDP-3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(2.5,INF_D)), REP<double>(0.0,std::stod("0X1.6A09E667F3BCDP-3")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-1.0,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-2.5,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-2.5,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-INF_D,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-INF_D,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-INF_D,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-1.0,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-1.0,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-2.5,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-2.5,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-INF_D,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-INF_D,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-0.1,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-1.0,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-2.5,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-INF_D,-0.1)), REP<double>(std::stod("0X1.125FBEE250664P+0"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-1.0,-1.0)), REP<double>(std::stod("0X1P+1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-2.5,-1.0)), REP<double>(std::stod("0X1P+1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-INF_D,-1.0)), REP<double>(std::stod("0X1P+1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-2.5,-2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP+2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,0.5), REP<double>(-INF_D,-2.5)), REP<double>(std::stod("0X1.6A09E667F3BCCP+2"),INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.1,1.0), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-0.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(0.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-0.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(0.1,0.1)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(0.1,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(0.1,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(0.1,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(1.0,1.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(1.0,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(1.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(2.5,2.5)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(2.5,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-1.0,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-2.5,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-2.5,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-INF_D,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-INF_D,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-INF_D,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-0.1,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-0.1,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-1.0,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-1.0,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-2.5,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-2.5,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-INF_D,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-INF_D,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-0.1,-0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-1.0,-0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-2.5,-0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-INF_D,-0.1)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-1.0,-1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-2.5,-1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-INF_D,-1.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-2.5,-2.5)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.0), REP<double>(-INF_D,-2.5)), REP<double>(1.0,INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.1,1.5), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(0.0,1.0)), REP<double>(0.0,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-0.0,1.0)), REP<double>(0.0,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(0.0,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-0.0,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(0.1,0.1)), REP<double>(0.0,std::stod("0X1.0A97DCE72A0CBP+0")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(0.1,1.0)), REP<double>(0.0,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(0.1,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(1.0,1.0)), REP<double>(0.0,1.5) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(1.0,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(2.5,2.5)), REP<double>(0.0,std::stod("0X1.60B9FD68A4555P+1")) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-1.0,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-2.5,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-2.5,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-INF_D,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-INF_D,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-INF_D,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-1.0,0.0)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-1.0,-0.0)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-2.5,0.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-2.5,-0.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-INF_D,0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-INF_D,-0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-0.1,-0.1)), REP<double>(std::stod("0X1.EBA7C9E4D31E9P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-1.0,-0.1)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-2.5,-0.1)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-INF_D,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-1.0,-1.0)), REP<double>(std::stod("0X1.5555555555555P-1"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-2.5,-1.0)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-INF_D,-1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-2.5,-2.5)), REP<double>(std::stod("0X1.7398BF1D1EE6FP-2"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,1.5), REP<double>(-INF_D,-2.5)), REP<double>(0.0,INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.1,INF_D), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(0.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-0.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(0.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-0.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-0.1,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-0.1,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-0.1,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-0.1,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-1.0,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-1.0,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-1.0,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-2.5,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-2.5,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-2.5,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-2.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-INF_D,0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-INF_D,1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-INF_D,2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-1.0,0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-1.0,-0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-2.5,0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-2.5,-0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-INF_D,0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-INF_D,-0.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-0.1,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-1.0,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-2.5,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-INF_D,-0.1)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-1.0,-1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-2.5,-1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-INF_D,-1.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-INF_D,-2.5)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.1,INF_D), REP<double>(-2.5,-2.5)), REP<double>(0.0,INF_D) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(0.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(0.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-0.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(0.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-0.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(0.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-0.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(0.1,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(0.1,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(0.1,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(0.1,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(1.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(1.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(2.5,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(2.5,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-0.1,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-0.1,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-0.1,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-0.1,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-1.0,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-1.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-1.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-2.5,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-2.5,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-2.5,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-2.5,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-INF_D,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-INF_D,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-INF_D,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,0.0), F<double>::entire()), REP<double>(0.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-1.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-1.0,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-2.5,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-2.5,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-INF_D,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-INF_D,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-0.1,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-1.0,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-2.5,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-INF_D,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-1.0,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-2.5,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-INF_D,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-INF_D,-2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,0.0), REP<double>(-2.5,-2.5)) ) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(0.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-0.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(0.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-0.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(0.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-0.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(0.1,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(0.1,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(0.1,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(0.1,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(1.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(1.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(2.5,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(2.5,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-0.1,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-0.1,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-0.1,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-0.1,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-1.0,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-1.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-1.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-2.5,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-2.5,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-2.5,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-2.5,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-INF_D,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-INF_D,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-INF_D,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,-0.0), F<double>::entire()), REP<double>(0.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-1.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-1.0,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-2.5,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-2.5,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-INF_D,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-INF_D,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-0.1,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-1.0,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-2.5,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-INF_D,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-1.0,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-2.5,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-INF_D,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-INF_D,-2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,-0.0), REP<double>(-2.5,-2.5)) ) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(0.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(0.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-0.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(0.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-0.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(0.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-0.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(0.1,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(0.1,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(0.1,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(0.1,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(1.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(1.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(2.5,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(2.5,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-0.1,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-0.1,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-0.1,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-0.1,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-1.0,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-1.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-1.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-2.5,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-2.5,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-2.5,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-2.5,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-INF_D,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-INF_D,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-INF_D,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-0.0,0.0), F<double>::entire()), REP<double>(0.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-1.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-1.0,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-2.5,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-2.5,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-INF_D,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-INF_D,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-0.1,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-1.0,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-2.5,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-INF_D,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-1.0,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-2.5,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-INF_D,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-INF_D,-2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-0.0,0.0), REP<double>(-2.5,-2.5)) ) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(0.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(0.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-0.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(0.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-0.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(0.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-0.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(0.1,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(0.1,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(0.1,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(0.1,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(1.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(1.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(2.5,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(2.5,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-0.1,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-0.1,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-0.1,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-0.1,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-1.0,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-1.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-1.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-2.5,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-2.5,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-2.5,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-2.5,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-INF_D,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-INF_D,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-INF_D,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(0.0,-0.0), F<double>::entire()), REP<double>(0.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-1.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-1.0,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-2.5,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-2.5,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-INF_D,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-INF_D,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-0.1,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-1.0,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-2.5,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-INF_D,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-1.0,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-2.5,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-INF_D,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-INF_D,-2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(0.0,-0.0), REP<double>(-2.5,-2.5)) ) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(0.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(0.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-0.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(0.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-0.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(0.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-0.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(0.1,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(0.1,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(0.1,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(0.1,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(1.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(1.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(2.5,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(2.5,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-0.1,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-0.1,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-0.1,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-0.1,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-1.0,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-1.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-1.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-2.5,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-2.5,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-2.5,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-2.5,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-INF_D,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-INF_D,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-INF_D,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,0.0), F<double>::entire()), REP<double>(0.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-1.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-1.0,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-2.5,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-2.5,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-INF_D,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-INF_D,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-0.1,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-1.0,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-2.5,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-INF_D,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-1.0,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-2.5,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-INF_D,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-INF_D,-2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,0.0), REP<double>(-2.5,-2.5)) ) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(0.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-0.0,-0.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(0.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-0.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(0.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-0.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(0.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-0.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(0.1,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(0.1,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(0.1,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(0.1,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(1.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(1.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(2.5,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(2.5,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-0.1,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-0.1,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-0.1,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-0.1,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-1.0,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-1.0,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-1.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-2.5,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-2.5,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-2.5,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-2.5,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-INF_D,0.1)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-INF_D,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-INF_D,2.5)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pow(REP<double>(-1.0,-0.0), F<double>::entire()), REP<double>(0.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-1.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-1.0,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-2.5,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-2.5,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-INF_D,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-INF_D,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-0.1,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-1.0,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-2.5,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-INF_D,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-1.0,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-2.5,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-INF_D,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-INF_D,-2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.0), REP<double>(-2.5,-2.5)) ) );


BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(0.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-0.0,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(0.0,1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-0.0,1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(0.0,2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-0.0,2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(0.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-0.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(0.1,0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(0.1,1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(0.1,2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(0.1,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(1.0,1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(1.0,2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(1.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(2.5,2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(2.5,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-0.1,0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-0.1,1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-0.1,2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-0.1,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-1.0,0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-1.0,1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-1.0,2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-1.0,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-2.5,0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-2.5,1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-2.5,2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-2.5,INF_D)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-INF_D,0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-INF_D,1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-INF_D,2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), F<double>::entire()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-1.0,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-1.0,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-2.5,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-2.5,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-INF_D,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-INF_D,-0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-0.1,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-1.0,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-2.5,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-INF_D,-0.1)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-1.0,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-2.5,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-INF_D,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-INF_D,-2.5)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::pow(REP<double>(-1.0,-0.1), REP<double>(-2.5,-2.5)) ) );
}

BOOST_AUTO_TEST_CASE(minimal_exp_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::exp(F<double>::empty()) ) );

    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(-INF_D,0.0)),REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(-INF_D,-0.0)),REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(-0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::exp(F<double>::entire()), REP<double>(0.0,INF_D) );

    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(-INF_D,std::stod("0X1.62E42FEFA39FP+9"))), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(std::stod("0X1.62E42FEFA39FP+9"),std::stod("0X1.62E42FEFA39FP+9"))), REP<double>( std::stod("0X1.FFFFFFFFFFFFFP+1023"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(0.0,std::stod("0X1.62E42FEFA39EP+9"))), REP<double>(1.0,std::stod("0X1.FFFFFFFFFC32BP+1023")) );
    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(-0.0,std::stod("0X1.62E42FEFA39EP+9"))), REP<double>(1.0,std::stod("0X1.FFFFFFFFFC32BP+1023")) );
//    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(std::stod("-0X1.6232BDD7ABCD3P+9"),std::stod("0X1.62E42FEFA39EP+9"))), REP<double>(0.0,std::stod("0X1.FFFFFFFFFC32BP+1023")) );   not F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(std::stod("-0X1.6232BDD7ABCD3P+9"),std::stod("0X1.62E42FEFA39EP+9"))), REP<double>(std::stod("0X0.FFFFFFFFFFE7BP-1022"),std::stod("0X1.FFFFFFFFFC32BP+1023")) );   // F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(std::stod("-0X1.6232BDD7ABCD3P+8"),std::stod("0X1.62E42FEFA39EP+9"))), REP<double>(std::stod("0X1.FFFFFFFFFFE7BP-512"),std::stod("0X1.FFFFFFFFFC32BP+1023")) );
    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(std::stod("-0X1.6232BDD7ABCD3P+8"),0.0)), REP<double>(std::stod("0X1.FFFFFFFFFFE7BP-512"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(std::stod("-0X1.6232BDD7ABCD3P+8"),-0.0)), REP<double>(std::stod("0X1.FFFFFFFFFFE7BP-512"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(std::stod("-0X1.6232BDD7ABCD3P+8"),1.0)), REP<double>(std::stod("0X1.FFFFFFFFFFE7BP-512"),std::stod("0X1.5BF0A8B14576AP+1")) );

    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(1.0,5.0)), REP<double>(std::stod("0X1.5BF0A8B145769P+1"),std::stod("0X1.28D389970339P+7")) );

    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(std::stod("-0X1.A934F0979A372P+1"),std::stod("0X1.CEAECFEA8085AP+0"))), REP<double>(std::stod("0X1.2797F0A337A5FP-5"),std::stod("0X1.86091CC9095C5P+2")) );
    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(std::stod("0X1.87F42B972949CP-1"),std::stod("0X1.8B55484710029P+6"))), REP<double>(std::stod("0X1.1337E9E45812AP+1"), std::stod("0X1.805A5C88021B6P+142")) );
    BOOST_CHECK_EQUAL( F<double>::exp(REP<double>(std::stod("0X1.78025C8B3FD39P+3"),std::stod("0X1.9FD8EEF3FA79BP+4"))), REP<double>(std::stod("0X1.EF461A783114CP+16"),std::stod("0X1.691D36C6B008CP+37"))  );
}

BOOST_AUTO_TEST_CASE(minimal_exp2_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::exp2(F<double>::empty()) ) );

    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(-INF_D,0.0)),REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(-INF_D,-0.0)),REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(-0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::exp2(F<double>::entire()), REP<double>(0.0,INF_D) );

    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(-INF_D,1024.0)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(1024.0,1024.0)), REP<double>(std::stod("0X1.FFFFFFFFFFFFFP+1023"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(0.0,1023.0)), REP<double>(1.0,std::stod("0X1P+1023")) );
    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(-0.0,1023.0)), REP<double>(1.0,std::stod("0X1P+1023")) );
    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(-1022.0,1023.0)), REP<double>(std::stod("0X1P-1022"),std::stod("0X1P+1023")) );
    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(-1022.0,0.0)), REP<double>(std::stod("0X1P-1022"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(-1022.0,-0.0)), REP<double>(std::stod("0X1P-1022"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(-1022.0,1.0)), REP<double>(std::stod("0X1P-1022"),2.0) );

    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(1.0,5.0)), REP<double>(2.0,32.0) );

    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(std::stod("-0X1.A934F0979A372P+1"),std::stod("0X1.CEAECFEA8085AP+0"))), REP<double>(std::stod("0X1.9999999999998P-4"),std::stod("0X1.C000000000001P+1")) );
    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(std::stod("0X1.87F42B972949CP-1"),std::stod("0X1.8B55484710029P+6"))), REP<double>(std::stod("0X1.B333333333332P+0"),std::stod("0X1.C81FD88228B4FP+98")) );
    BOOST_CHECK_EQUAL( F<double>::exp2(REP<double>(std::stod("0X1.78025C8B3FD39P+3"),std::stod("0X1.9FD8EEF3FA79BP+4"))), REP<double>(std::stod("0X1.AEA0000721857P+11"),std::stod("0X1.FCA0555555559P+25"))  );
}

BOOST_AUTO_TEST_CASE(minimal_exp10_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::exp10(F<double>::empty()) ) );

    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(-INF_D,0.0)),REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(-INF_D,-0.0)),REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(-0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::exp10(F<double>::entire()), REP<double>(0.0,INF_D) );

    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(-INF_D,std::stod("0X1.34413509F79FFP+8"))), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(std::stod("0X1.34413509F79FFP+8"),std::stod("0X1.34413509F79FFP+8"))), REP<double>(std::stod("0X1.FFFFFFFFFFFFFP+1023"),INF_D) );

    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(0.0,std::stod("0X1.34413509F79FEP+8"))), REP<double>(1.0,std::stod("0X1.FFFFFFFFFFBA1P+1023")) );
    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(-0.0,std::stod("0X1.34413509F79FEP+8"))), REP<double>(1.0,std::stod("0X1.FFFFFFFFFFBA1P+1023")) );
//    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(std::stod("-0X1.33A7146F72A42P+8"),std::stod("0X1.34413509F79FEP+8"))), REP<double>(0.0,std::stod("0X1.FFFFFFFFFFBA1P+1023")) );   not F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(std::stod("-0X1.33A7146F72A42P+8"),std::stod("0X1.34413509F79FEP+8"))), REP<double>(std::stod("0X0.FFFFFFFFFFFE3P-1022"),std::stod("0X1.FFFFFFFFFFBA1P+1023")) );   // F<double>::subnormalized
    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(std::stod("-0X1.22P+7"),std::stod("0X1.34413509F79FEP+8"))), REP<double>(std::stod("0X1.3FAAC3E3FA1F3P-482"),std::stod("0X1.FFFFFFFFFFBA1P+1023")) );
    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(std::stod("-0X1.22P+7"),0.0)), REP<double>(std::stod("0X1.3FAAC3E3FA1F3P-482"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(std::stod("-0X1.22P+7"),-0.0)), REP<double>(std::stod("0X1.3FAAC3E3FA1F3P-482"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(std::stod("-0X1.22P+7"),1.0)), REP<double>(std::stod("0X1.3FAAC3E3FA1F3P-482"),10.0) );

    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(1.0,5.0)), REP<double>(10.0,100000.0) );

    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(std::stod("-0X1.A934F0979A372P+1"),std::stod("0X1.CEAECFEA8085AP+0"))), REP<double>(std::stod("0X1.F3A8254311F9AP-12"),std::stod("0X1.00B18AD5B7D56P+6")) );
    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(std::stod("0X1.87F42B972949CP-1"),std::stod("0X1.8B55484710029P+6"))), REP<double>(std::stod("0X1.75014B7296807P+2"),std::stod("0X1.3EEC1D47DFB2BP+328")) );
    BOOST_CHECK_EQUAL( F<double>::exp10(REP<double>(std::stod("0X1.78025C8B3FD39P+3"),std::stod("0X1.9FD8EEF3FA79BP+4"))), REP<double>(std::stod("0X1.0608D2279A811P+39"),std::stod("0X1.43AF5D4271CB8P+86")) );
}

BOOST_AUTO_TEST_CASE(minimal_log_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::log(F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::log(REP<double>(-INF_D,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::log(REP<double>(-INF_D,-0.0)) ) );

    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(0.0,1.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(-0.0,1.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(1.0,INF_D)), REP<double>(0.0,INF_D) );

    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(0.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(-0.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::log(F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(0.0,MAX_D)), REP<double>(-INF_D,std::stod("0X1.62E42FEFA39FP+9")) );
    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(-0.0,MAX_D)), REP<double>(-INF_D,std::stod("0X1.62E42FEFA39FP+9")) );
    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(1.0,MAX_D)), REP<double>(0.0,std::stod("0X1.62E42FEFA39FP+9")) );
    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(MIN_D,MAX_D)), REP<double>(std::stod("-0X1.6232BDD7ABCD3P+9"),std::stod("0X1.62E42FEFA39FP+9")) );
    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(MIN_D,1.0)), REP<double>(std::stod("-0X1.6232BDD7ABCD3P+9"),0.0) );

    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(std::stod("0X1.5BF0A8B145769P+1"),std::stod("0X1.5BF0A8B145769P+1"))), REP<double>(std::stod("0X1.FFFFFFFFFFFFFP-1"),std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(std::stod("0X1.5BF0A8B14576AP+1"),std::stod("0X1.5BF0A8B14576AP+1"))), REP<double>(std::stod("0X1P+0"),std::stod("0X1.0000000000001P+0")) );

    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(MIN_D,std::stod("0X1.5BF0A8B14576AP+1"))), REP<double>(std::stod("-0X1.6232BDD7ABCD3P+9"),std::stod("0X1.0000000000001P+0")) );

    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(std::stod("0X1.5BF0A8B145769P+1"),32.0)), REP<double>(std::stod("0X1.FFFFFFFFFFFFFP-1"),std::stod("0X1.BB9D3BEB8C86CP+1")) );

    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.CP+1"))), REP<double>(std::stod("-0X1.26BB1BBB55516P+1"),std::stod("0X1.40B512EB53D6P+0")) );
    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(std::stod("0X1.B333333333333P+0"),std::stod("0X1.C81FD88228B2FP+98"))), REP<double>(std::stod("0X1.0FAE81914A99P-1"),std::stod("0X1.120627F6AE7F1P+6")) );
    BOOST_CHECK_EQUAL( F<double>::log(REP<double>(std::stod("0X1.AEA0000721861P+11"),std::stod("0X1.FCA055555554CP+25"))), REP<double>(std::stod("0X1.04A1363DB1E63P+3"),std::stod("0X1.203E52C0256B5P+4")) );
}


BOOST_AUTO_TEST_CASE(minimal_log2_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::log2(F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::log2(REP<double>(-INF_D,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::log2(REP<double>(-INF_D,-0.0)) ) );

    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(0.0,1.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(-0.0,1.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(1.0,INF_D)), REP<double>(0.0,INF_D) );

    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(0.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(-0.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::log2(F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(0.0,MAX_D)), REP<double>(-INF_D,1024.0) );
    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(-0.0,MAX_D)), REP<double>(-INF_D,1024.0) );
    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(1.0,MAX_D)), REP<double>(0.0,1024.0) );
    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(MIN_D,MAX_D)), REP<double>(-1022.0,1024.0) );
    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(MIN_D,1.0)), REP<double>(-1022.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(MIN_D,2.0)), REP<double>(-1022.0,1.0) );

    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(2.0,32.0)), REP<double>(1.0,5.0) );

    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.CP+1"))), REP<double>(std::stod("-0X1.A934F0979A372P+1"),std::stod("0X1.CEAECFEA8085AP+0")) );
    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(std::stod("0X1.B333333333333P+0"),std::stod("0X1.C81FD88228B2FP+98"))), REP<double>(std::stod("0X1.87F42B972949CP-1"),std::stod("0X1.8B55484710029P+6")) );
    BOOST_CHECK_EQUAL( F<double>::log2(REP<double>(std::stod("0X1.AEA0000721861P+11"),std::stod("0X1.FCA055555554CP+25"))), REP<double>(std::stod("0X1.78025C8B3FD39P+3"),std::stod("0X1.9FD8EEF3FA79BP+4")) );
}

BOOST_AUTO_TEST_CASE(minimal_log10_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::log10(F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::log10(REP<double>(-INF_D,0.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::log10(REP<double>(-INF_D,-0.0)) ) );

    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(0.0,1.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(-0.0,1.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(1.0,INF_D)), REP<double>(0.0,INF_D) );

    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(0.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(-0.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::log10(F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(0.0,MAX_D)), REP<double>(-INF_D,std::stod("0X1.34413509F79FFP+8")) );
    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(-0.0,MAX_D)), REP<double>(-INF_D,std::stod("0X1.34413509F79FFP+8")) );
    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(1.0,MAX_D)), REP<double>(0.0,std::stod("0X1.34413509F79FFP+8")) );
    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(MIN_D,MAX_D)), REP<double>(std::stod("-0X1.33A7146F72A42P+8") ,std::stod("0X1.34413509F79FFP+8")) );
    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(MIN_D,1.0)), REP<double>(std::stod("-0X1.33A7146F72A42P+8") ,0.0) );
    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(MIN_D,10.0)), REP<double>(std::stod("-0X1.33A7146F72A42P+8") ,1.0) );

    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(10.0,100000.0)), REP<double>(1.0,5.0) );

    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.CP+1"))), REP<double>(std::stod("-0X1P+0"),std::stod("0X1.1690163290F4P-1")) );
    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")) );
    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(std::stod("0X1.B333333333333P+0"),std::stod("0X1.C81FD88228B2FP+98"))), REP<double>(std::stod("0X1.D7F59AA5BECB9P-3"),std::stod("0X1.DC074D84E5AABP+4")) );
    BOOST_CHECK_EQUAL( F<double>::log10(REP<double>(std::stod("0X1.AEA0000721861P+11"),std::stod("0X1.FCA055555554CP+25"))), REP<double>(std::stod("0X1.C4C29DD829191P+1"),std::stod("0X1.F4BAEBBA4FA4P+2")) );
}

BOOST_AUTO_TEST_CASE(minimal_sin_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::sin(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(0.0,INF_D)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(-0.0,INF_D)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(-INF_D,0.0)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(-INF_D,-0.0)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(F<double>::entire()), REP<double>(-1.0,1.0) );

    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );

    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D18P+0"))), REP<double>(std::stod("0X1.FFFFFFFFFFFFFP-1"),std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+0"))), REP<double>(std::stod("0X1.FFFFFFFFFFFFFP-1"),std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+0"))), REP<double>(std::stod("0X1.FFFFFFFFFFFFFP-1"),std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(0.0,std::stod("0X1.921FB54442D18P+0"))), REP<double>(0.0,std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(-0.0,std::stod("0X1.921FB54442D18P+0"))), REP<double>(0.0,std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(0.0,std::stod("0X1.921FB54442D19P+0"))), REP<double>(0.0,std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(-0.0,std::stod("0X1.921FB54442D19P+0"))), REP<double>(0.0,std::stod("0X1P+0")) );

    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("0X1.921FB54442D18P+1"),std::stod("0X1.921FB54442D18P+1"))), REP<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("0X1.921FB54442D19P+1"),std::stod("0X1.921FB54442D19P+1"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-52"),std::stod("-0X1.72CECE675D1FCP-52")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("0X1.921FB54442D18P+1"),std::stod("0X1.921FB54442D19P+1"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-52"),std::stod("0X1.1A62633145C07P-53")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(0.0,std::stod("0X1.921FB54442D18P+1"))), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(-0.0,std::stod("0X1.921FB54442D18P+1"))), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(0.0,std::stod("0X1.921FB54442D19P+1"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-52"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(-0.0,std::stod("0X1.921FB54442D19P+1"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-52"),1.0) );

    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D18P+1"))), REP<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+1"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-52"),std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D18P+1"))), REP<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+1"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-52"),std::stod("0X1P+0")) );

    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D18P+0"),std::stod("-0X1.921FB54442D18P+0"))), REP<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("-0X1.921FB54442D19P+0"))), REP<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("-0X1.921FB54442D18P+0"))), REP<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D18P+0"),0.0)), REP<double>(std::stod("-0X1P+0"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D18P+0"),-0.0)), REP<double>(std::stod("-0X1P+0"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D19P+0"),0.0)), REP<double>(std::stod("-0X1P+0"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D19P+0"),-0.0)), REP<double>(std::stod("-0X1P+0"),0.0) );

    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D18P+1"),std::stod("-0X1.921FB54442D18P+1"))), REP<double>(std::stod("-0X1.1A62633145C07P-53"),std::stod("-0X1.1A62633145C06P-53")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D19P+1"),std::stod("-0X1.921FB54442D19P+1"))), REP<double>(std::stod("0X1.72CECE675D1FCP-52"),std::stod("0X1.72CECE675D1FDP-52")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D19P+1"),std::stod("-0X1.921FB54442D18P+1"))), REP<double>(std::stod("-0X1.1A62633145C07P-53"),std::stod("0X1.72CECE675D1FDP-52")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D18P+1"),0.0)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D18P+1"),-0.0)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D19P+1"),0.0)), REP<double>(-1.0,std::stod("0X1.72CECE675D1FDP-52")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D19P+1"),-0.0)), REP<double>(-1.0,std::stod("0X1.72CECE675D1FDP-52")) );

    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D18P+1"),std::stod("-0X1.921FB54442D18P+0"))), REP<double>(std::stod("-0X1P+0"),std::stod("-0X1.1A62633145C06P-53")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D19P+1"),std::stod("-0X1.921FB54442D18P+0"))), REP<double>(std::stod("-0X1P+0"),std::stod("0X1.72CECE675D1FDP-52")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D18P+1"),std::stod("-0X1.921FB54442D19P+0"))), REP<double>(std::stod("-0X1P+0"),std::stod("-0X1.1A62633145C06P-53")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D19P+1"),std::stod("-0X1.921FB54442D19P+0"))), REP<double>(std::stod("-0X1P+0"),std::stod("0X1.72CECE675D1FDP-52")) );

    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D18P+0"))), REP<double>(std::stod("-0X1P+0"),std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+0"))), REP<double>(std::stod("-0X1P+0"),std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D18P+0"))), REP<double>(std::stod("-0X1P+0"),std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+0"))), REP<double>(std::stod("-0X1P+0"),std::stod("0X1P+0")) );

    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(-0.7,0.1)), REP<double>(std::stod("-0X1.49D6E694619B9P-1"),std::stod("0X1.98EAECB8BCB2DP-4")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(1.0,2.0)), REP<double>(std::stod("0X1.AED548F090CEEP-1"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(-3.2,-2.9)), REP<double>(std::stod("-0X1.E9FB8D64830E3P-3"),std::stod("0X1.DE33739E82D33P-5")) );
    BOOST_CHECK_EQUAL( F<double>::sin(REP<double>(2.0,3.0)), REP<double>(std::stod("0X1.210386DB6D55BP-3"),std::stod("0X1.D18F6EAD1B446P-1")) );
}

BOOST_AUTO_TEST_CASE(minimal_cos_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::cos(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(0.0,INF_D)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(-0.0,INF_D)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(-INF_D,0.0)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(-INF_D,-0.0)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(F<double>::entire()), REP<double>(-1.0,1.0) );

    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );

    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D18P+0"))), REP<double>(std::stod("0X1.1A62633145C06P-54"),std::stod("0X1.1A62633145C07P-54")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+0"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-53"),std::stod("-0X1.72CECE675D1FCP-53")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+0"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-53"),std::stod("0X1.1A62633145C07P-54")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(0.0,std::stod("0X1.921FB54442D18P+0"))), REP<double>(std::stod("0X1.1A62633145C06P-54"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(-0.0,std::stod("0X1.921FB54442D18P+0"))), REP<double>(std::stod("0X1.1A62633145C06P-54"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(0.0,std::stod("0X1.921FB54442D19P+0"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-53"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(-0.0,std::stod("0X1.921FB54442D19P+0"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-53"),1.0) );

    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("0X1.921FB54442D18P+1"),std::stod("0X1.921FB54442D18P+1"))), REP<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("0X1.921FB54442D19P+1"),std::stod("0X1.921FB54442D19P+1"))), REP<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("0X1.921FB54442D18P+1"),std::stod("0X1.921FB54442D19P+1"))), REP<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(0.0,std::stod("0X1.921FB54442D18P+1"))), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(-0.0,std::stod("0X1.921FB54442D18P+1"))), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(0.0,std::stod("0X1.921FB54442D19P+1"))), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(-0.0,std::stod("0X1.921FB54442D19P+1"))), REP<double>(-1.0,1.0) );

    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D18P+1"))), REP<double>(-1.0,std::stod("0X1.1A62633145C07P-54")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+1"))), REP<double>(-1.0,std::stod("0X1.1A62633145C07P-54")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D18P+1"))), REP<double>(-1.0,std::stod("-0X1.72CECE675D1FCP-53")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+1"))), REP<double>(-1.0,std::stod("-0X1.72CECE675D1FCP-53")) );

    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D18P+0"),std::stod("-0X1.921FB54442D18P+0"))), REP<double>(std::stod("0X1.1A62633145C06P-54"),std::stod("0X1.1A62633145C07P-54")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("-0X1.921FB54442D19P+0"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-53"),std::stod("-0X1.72CECE675D1FCP-53")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("-0X1.921FB54442D18P+0"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-53"),std::stod("0X1.1A62633145C07P-54")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D18P+0"),0.0)), REP<double>(std::stod("0X1.1A62633145C06P-54"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D18P+0"),-0.0)), REP<double>(std::stod("0X1.1A62633145C06P-54"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D19P+0"),0.0)), REP<double>(std::stod("-0X1.72CECE675D1FDP-53"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D19P+0"),-0.0)), REP<double>(std::stod("-0X1.72CECE675D1FDP-53"),1.0) );

    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D18P+1"),std::stod("-0X1.921FB54442D18P+1"))), REP<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D19P+1"),std::stod("-0X1.921FB54442D19P+1"))), REP<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D19P+1"),std::stod("-0X1.921FB54442D18P+1"))), REP<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D18P+1"),0.0)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D18P+1"),-0.0)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D19P+1"),0.0)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D19P+1"),-0.0)), REP<double>(-1.0,1.0) );

    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D18P+1"),std::stod("-0X1.921FB54442D18P+0"))), REP<double>(-1.0,std::stod("0X1.1A62633145C07P-54")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D19P+1"),std::stod("-0X1.921FB54442D18P+0"))), REP<double>(-1.0,std::stod("0X1.1A62633145C07P-54")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D18P+1"),std::stod("-0X1.921FB54442D19P+0"))), REP<double>(-1.0,std::stod("-0X1.72CECE675D1FCP-53")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D19P+1"),std::stod("-0X1.921FB54442D19P+0"))), REP<double>(-1.0,std::stod("-0X1.72CECE675D1FCP-53")) );

    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D18P+0"))), REP<double>(std::stod("0X1.1A62633145C06P-54"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+0"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-53"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D18P+0"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-53"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+0"))), REP<double>(std::stod("-0X1.72CECE675D1FDP-53"),1.0) );

    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(-0.7,0.1)), REP<double>(std::stod("0X1.87996529F9D92P-1"),1.0) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(1.0,2.0)), REP<double>(std::stod("-0X1.AA22657537205P-2"),std::stod("0X1.14A280FB5068CP-1")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(-3.2,-2.9)), REP<double>(-1.0,std::stod("-0X1.F1216DBA340C8P-1")) );
    BOOST_CHECK_EQUAL( F<double>::cos(REP<double>(2.0,3.0)), REP<double>(std::stod("-0X1.FAE04BE85E5D3P-1"),std::stod("-0X1.AA22657537204P-2")) );
}

BOOST_AUTO_TEST_CASE(minimal_tan_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::tan(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(0.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(-0.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(-INF_D,0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(-INF_D,-0.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D18P+0"))), REP<double>(std::stod("0X1.D02967C31CDB4P+53"),std::stod("0X1.D02967C31CDB5P+53")) );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+0"))), REP<double>(std::stod("-0X1.617A15494767BP+52"),std::stod("-0X1.617A15494767AP+52")) );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+0"))), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("0X1.921FB54442D18P+1"),std::stod("0X1.921FB54442D18P+1"))), REP<double>(std::stod("-0X1.1A62633145C07P-53"),std::stod("-0X1.1A62633145C06P-53")) );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("0X1.921FB54442D19P+1"),std::stod("0X1.921FB54442D19P+1"))), REP<double>(std::stod("0X1.72CECE675D1FCP-52"),std::stod("0X1.72CECE675D1FDP-52")) );

    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(0.0,std::stod("0X1.921FB54442D18P+0"))), REP<double>(0.0,std::stod("0X1.D02967C31CDB5P+53")) );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(-0.0,std::stod("0X1.921FB54442D18P+0"))), REP<double>(0.0,std::stod("0X1.D02967C31CDB5P+53")) );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(0.0,std::stod("0X1.921FB54442D19P+0"))), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(-0.0,std::stod("0X1.921FB54442D19P+0"))), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(0.0,std::stod("0X1.921FB54442D18P+1"))), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(-0.0,std::stod("0X1.921FB54442D18P+1"))), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(0.0,std::stod("0X1.921FB54442D19P+1"))), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(-0.0,std::stod("0X1.921FB54442D19P+1"))), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("0X1P-51"),std::stod("0X1.921FB54442D18P+1"))), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("0X1P-51"),std::stod("0X1.921FB54442D19P+1"))), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("0X1P-52"),std::stod("0X1.921FB54442D18P+1"))), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("0X1P-52"),std::stod("0X1.921FB54442D19P+1"))), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("-0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D18P+0"))), REP<double>(std::stod("-0X1.D02967C31CDB5P+53"),std::stod("0X1.D02967C31CDB5P+53")) );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("-0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+0"))), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D18P+0"))), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+0"))), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("-0X1.555475A31A4BEP-2"),std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("-0X1.628F4FD931FEFP-2"),std::stod("0X1.9AF8877430B81P-4")) );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("0X1.4E18E147AE148P+12"),std::stod("0X1.4E2028F5C28F6P+12"))), REP<double>(std::stod("-0X1.D6D67B035B6B4P+2"),std::stod("-0X1.7E42B0760E3F3P+0")) );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("0X1.4E18E147AE148P+12"),std::stod("0X1.546028F5C28F6P+12"))), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::tan(REP<double>(std::stod("0X1.FAE147AE147AEP-1"),std::stod("0X1.028F5C28F5C29P+0"))), REP<double>(std::stod("0X1.860FADCC59064P+0"),std::stod("0X1.979AD0628469DP+0")) );
}

BOOST_AUTO_TEST_CASE(minimal_asin_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::asin(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(0.0,INF_D)), REP<double>(0.0,std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(-0.0,INF_D)), REP<double>(0.0,std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(-INF_D,0.0)), REP<double>(std::stod("-0X1.921FB54442D19P+0"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(-INF_D,-0.0)), REP<double>(std::stod("-0X1.921FB54442D19P+0"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::asin(F<double>::entire()), REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(-1.0,1.0)), REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(-INF_D,-1.0)), REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("-0X1.921FB54442D18P+0")) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(1.0,INF_D)), REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(-1.0,-1.0)), REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("-0X1.921FB54442D18P+0")) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(1.0,1.0)), REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::asin(REP<double>(-INF_D,std::stod("-0X1.0000000000001P+0"))) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::asin(REP<double>(std::stod("0X1.0000000000001P+0"),INF_D)) ) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("-0X1.9A49276037885P-4"),std::stod("0X1.9A49276037885P-4")) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(std::stod("-0X1.51EB851EB851FP-2"),std::stod("0X1.FFFFFFFFFFFFFP-1"))), REP<double>(std::stod("-0X1.585FF6E341C3FP-2"),std::stod("0X1.921FB50442D19P+0")) );
    BOOST_CHECK_EQUAL( F<double>::asin(REP<double>(std::stod("-0X1.FFFFFFFFFFFFFP-1"),std::stod("0X1.FFFFFFFFFFFFFP-1"))), REP<double>(std::stod("-0X1.921FB50442D19P+0"),std::stod("0X1.921FB50442D19P+0")) );
}

BOOST_AUTO_TEST_CASE(minimal_acos_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::acos(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(0.0,INF_D)), REP<double>(0.0,std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(-0.0,INF_D)), REP<double>(0.0,std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(-INF_D,0.0)), REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+1")) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(-INF_D,-0.0)), REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+1")) );
    BOOST_CHECK_EQUAL( F<double>::acos(F<double>::entire()), REP<double>(0.0,std::stod("0X1.921FB54442D19P+1")) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(-1.0,1.0)), REP<double>(0.0,std::stod("0X1.921FB54442D19P+1")) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(-INF_D,-1.0)), REP<double>(std::stod("0X1.921FB54442D18P+1"),std::stod("0X1.921FB54442D19P+1")) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(1.0,INF_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(-1.0,-1.0)), REP<double>(std::stod("0X1.921FB54442D18P+1"),std::stod("0X1.921FB54442D19P+1")) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(0.0,0.0)), REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(-0.0,-0.0)), REP<double>(std::stod("0X1.921FB54442D18P+0"),std::stod("0X1.921FB54442D19P+0")) );
BOOST_CHECK( F<double>::is_empty( F<double>::acos(REP<double>(-INF_D,std::stod("-0X1.0000000000001P+0"))) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::acos(REP<double>(std::stod("0X1.0000000000001P+0"),INF_D)) ) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("0X1.787B22CE3F59P+0"),std::stod("0X1.ABC447BA464A1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(std::stod("-0X1.51EB851EB851FP-2"),std::stod("0X1.FFFFFFFFFFFFFP-1"))), REP<double>(std::stod("0X1P-26"),std::stod("0X1.E837B2FD13428P+0")) );
    BOOST_CHECK_EQUAL( F<double>::acos(REP<double>(std::stod("-0X1.FFFFFFFFFFFFFP-1"),std::stod("0X1.FFFFFFFFFFFFFP-1"))), REP<double>(std::stod("0X1P-26"),std::stod("0X1.921FB52442D19P+1")) );
}

BOOST_AUTO_TEST_CASE(minimal_atan_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::atan(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::atan(REP<double>(0.0,INF_D)), REP<double>(0.0,std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( F<double>::atan(REP<double>(-0.0,INF_D)), REP<double>(0.0,std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( F<double>::atan(REP<double>(-INF_D,0.0)), REP<double>(std::stod("-0X1.921FB54442D19P+0"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::atan(REP<double>(-INF_D,-0.0)), REP<double>(std::stod("-0X1.921FB54442D19P+0"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::atan(F<double>::entire()), REP<double>(std::stod("-0X1.921FB54442D19P+0"),std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( F<double>::atan(REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::atan(REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::atan(REP<double>(1.0,std::stod("0X1.4C2463567C5ACP+25"))), REP<double>(std::stod("0X1.921FB54442D18P-1"),std::stod("0X1.921FB4E19ABD7P+0")) );
    BOOST_CHECK_EQUAL( F<double>::atan(REP<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"))), REP<double>(std::stod("-0X1.921FB54440CEBP+0"),std::stod("-0X1.91ABE5C1E4C6DP+0")) );
}

BOOST_AUTO_TEST_CASE(minimal_atan2_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_sinh_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::sinh(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::sinh(REP<double>(0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::sinh(REP<double>(-0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::sinh(REP<double>(-INF_D,0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::sinh(REP<double>(-INF_D,-0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::sinh(F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::sinh(REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::sinh(REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::sinh(REP<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"))), REP<double>(std::stod("0X1.2CD9FC44EB982P+0"),std::stod("0X1.89BCA168970C6P+432")) );
    BOOST_CHECK_EQUAL( F<double>::sinh(REP<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"))), REP<double>(-INF_D,std::stod("-0X1.53045B4F849DEP+815")) );
    BOOST_CHECK_EQUAL( F<double>::sinh(REP<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), REP<double>(std::stod("-0X1.55ECFE1B2B215P+0"),std::stod("0X1.3BF72EA61AF1BP+2")) );
}

BOOST_AUTO_TEST_CASE(minimal_cosh_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::cosh(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::cosh(REP<double>(0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::cosh(REP<double>(-0.0,INF_D)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::cosh(REP<double>(-INF_D,0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::cosh(REP<double>(-INF_D,-0.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::cosh(F<double>::entire()), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::cosh(REP<double>(0.0,0.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::cosh(REP<double>(-0.0,-0.0)), REP<double>(1.0,1.0) );

    BOOST_CHECK_EQUAL( F<double>::cosh(REP<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"))), REP<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432")) );
    BOOST_CHECK_EQUAL( F<double>::cosh(REP<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"))), REP<double>(std::stod("0X1.53045B4F849DEP+815"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::cosh(REP<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), REP<double>(1.0,std::stod("0X1.4261D2B7D6181P+2")) );
}

BOOST_AUTO_TEST_CASE(minimal_tanh_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::tanh(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::tanh(REP<double>(0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::tanh(REP<double>(-0.0,INF_D)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::tanh(REP<double>(-INF_D,0.0)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::tanh(REP<double>(-INF_D,-0.0)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::tanh(F<double>::entire()), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::tanh(REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::tanh(REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::tanh(REP<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"))), REP<double>(std::stod("0X1.85EFAB514F394P-1"),std::stod("0X1P+0")) );
    BOOST_CHECK_EQUAL( F<double>::tanh(REP<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"))), REP<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")) );
    BOOST_CHECK_EQUAL( F<double>::tanh(REP<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), REP<double>(std::stod("-0X1.99DB01FDE2406P-1"),std::stod("0X1.F5CF31E1C8103P-1")) );
}

BOOST_AUTO_TEST_CASE(minimal_asinh_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::asinh(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::asinh(REP<double>(0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::asinh(REP<double>(-0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::asinh(REP<double>(-INF_D,0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::asinh(REP<double>(-INF_D,-0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::asinh(F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::asinh(REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::asinh(REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::asinh(REP<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"))), REP<double>(std::stod("0X1.C34366179D426P-1"),std::stod("0X1.9986127438A87P+2")) );
    BOOST_CHECK_EQUAL( F<double>::asinh(REP<double>(std::stod("-0X1.FD219490EAAC1P+38"),std::stod("-0X1.1AF1C9D74F06DP+9"))), REP<double>(std::stod("-0X1.BB86380A6CC45P+4"),std::stod("-0X1.C204D8EB20827P+2")) );
    BOOST_CHECK_EQUAL( F<double>::asinh(REP<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), REP<double>(std::stod("-0X1.E693DF6EDF1E7P-1"),std::stod("0X1.91FDC64DE0E51P+0")) );
}

BOOST_AUTO_TEST_CASE(minimal_acosh_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::acosh(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::acosh(REP<double>(0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::acosh(REP<double>(-0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::acosh(REP<double>(1.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::acosh(REP<double>(-INF_D,1.0)), REP<double>(0.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::acosh(REP<double>(-INF_D,std::stod("0X1.FFFFFFFFFFFFFP-1"))) ) );
    BOOST_CHECK_EQUAL( F<double>::acosh(F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::acosh(REP<double>(1.0,1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::acosh(REP<double>(1.0,std::stod("0X1.2C903022DD7AAP+8"))), REP<double>(0.0,std::stod("0X1.9985FB3D532AFP+2")) );
    BOOST_CHECK_EQUAL( F<double>::acosh(REP<double>(std::stod("0X1.199999999999AP+0"),std::stod("0X1.2666666666666P+1"))), REP<double>(std::stod("0X1.C636C1A882F2CP-2"),std::stod("0X1.799C88E79140DP+0")) );
    BOOST_CHECK_EQUAL( F<double>::acosh(REP<double>(std::stod("0X1.14D4E82B2B26FP+15"),std::stod("0X1.72DBE91C837B5P+29"))), REP<double>(std::stod("0X1.656510B4BAEC3P+3"),std::stod("0X1.52A415EE8455AP+4")) );
}

BOOST_AUTO_TEST_CASE(minimal_atanh_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::atanh(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::atanh(REP<double>(0.0,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::atanh(REP<double>(-0.0,INF_D)), REP<double>(0.0,INF_D) );
BOOST_CHECK( F<double>::is_empty( F<double>::atanh(REP<double>(1.0,INF_D)) ) );
    BOOST_CHECK_EQUAL( F<double>::atanh(REP<double>(-INF_D,0.0)), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::atanh(REP<double>(-INF_D,-0.0)), REP<double>(-INF_D,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::atanh(REP<double>(-INF_D,-1.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::atanh(REP<double>(-1.0,1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::atanh(REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::atanh(REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
BOOST_CHECK( F<double>::is_empty( F<double>::atanh(REP<double>(-1.0,-1.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::atanh(REP<double>(1.0,1.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::atanh(F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::atanh(REP<double>(std::stod("0X1.4C0420F6F08CCP-2"),std::stod("0X1.FFFFFFFFFFFFFP-1"))), REP<double>(std::stod("0X1.5871DD2DF9102P-2"),std::stod("0X1.2B708872320E2P+4")) );
    BOOST_CHECK_EQUAL( F<double>::atanh(REP<double>(std::stod("-0X1.FFB88E9EB6307P-1"),std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("-0X1.06A3A97D7979CP+2"),std::stod("0X1.9AF93CD234413P-4")) );
}

BOOST_AUTO_TEST_CASE(minimal_sign_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::sign(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::sign(REP<double>(1.0,2.0)), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sign(REP<double>(-1.0,2.0)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sign(REP<double>(-1.0,0.0)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::sign(REP<double>(0.0,2.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sign(REP<double>(-0.0,2.0)), REP<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sign(REP<double>(-5.0,-2.0)), REP<double>(-1.0,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::sign(REP<double>(0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::sign(REP<double>(-0.0,-0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::sign(REP<double>(-0.0,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::sign(F<double>::entire()), REP<double>(-1.0,1.0) );
}

BOOST_AUTO_TEST_CASE(minimal_ceil_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::ceil(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::ceil(F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::ceil(REP<double>(1.1,2.0)), REP<double>(2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::ceil(REP<double>(-1.1,2.0)), REP<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::ceil(REP<double>(-1.1,0.0)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::ceil(REP<double>(-1.1,-0.0)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::ceil(REP<double>(-1.1,-0.4)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::ceil(REP<double>(-1.9,2.2)), REP<double>(-1.0,3.0) );
    BOOST_CHECK_EQUAL( F<double>::ceil(REP<double>(-1.0,2.2)), REP<double>(-1.0,3.0) );
    BOOST_CHECK_EQUAL( F<double>::ceil(REP<double>(0.0,2.2)), REP<double>(0.0,3.0) );
    BOOST_CHECK_EQUAL( F<double>::ceil(REP<double>(-0.0,2.2)), REP<double>(0.0,3.0) );
    BOOST_CHECK_EQUAL( F<double>::ceil(REP<double>(-1.5,INF_D)), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::ceil(REP<double>(-INF_D,2.2)), REP<double>(-INF_D,3.0) );
}

BOOST_AUTO_TEST_CASE(minimal_floor_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::floor(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::floor(F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::floor(REP<double>(1.1,2.0)), REP<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::floor(REP<double>(-1.1,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::floor(REP<double>(-1.1,0.0)), REP<double>(-2.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::floor(REP<double>(-1.1,-0.0)), REP<double>(-2.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::floor(REP<double>(-1.1,-0.4)), REP<double>(-2.0,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::floor(REP<double>(-1.9,2.2)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::floor(REP<double>(-1.0,2.2)), REP<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::floor(REP<double>(0.0,2.2)), REP<double>(0.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::floor(REP<double>(-0.0,2.2)), REP<double>(0.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::floor(REP<double>(-1.5,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::floor(REP<double>(-INF_D,2.2)), REP<double>(-INF_D,2.0) );
}

BOOST_AUTO_TEST_CASE(minimal_trunc_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::trunc(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::trunc(F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::trunc(REP<double>(1.1,2.1)), REP<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::trunc(REP<double>(-1.1,2.0)), REP<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::trunc(REP<double>(-1.1,0.0)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::trunc(REP<double>(-1.1,-0.0)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::trunc(REP<double>(-1.1,-0.4)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::trunc(REP<double>(-1.9,2.2)), REP<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::trunc(REP<double>(-1.0,2.2)), REP<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::trunc(REP<double>(0.0,2.2)), REP<double>(0.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::trunc(REP<double>(-0.0,2.2)), REP<double>(0.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::trunc(REP<double>(-1.5,INF_D)), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::trunc(REP<double>(-INF_D,2.2)), REP<double>(-INF_D,2.0) );
}

BOOST_AUTO_TEST_CASE(minimal_round_ties_to_even_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::round_ties_to_even(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(1.1,2.1)), REP<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(-1.1,2.0)), REP<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(-1.1,-0.4)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(-1.1,0.0)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(-1.1,-0.0)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(-1.9,2.2)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(-1.0,2.2)), REP<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(1.5,2.1)), REP<double>(2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(-1.5,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(-1.1,-0.5)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(-1.9,2.5)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(0.0,2.5)), REP<double>(0.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(-0.0,2.5)), REP<double>(0.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(-1.5,2.5)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(-1.5,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_even(REP<double>(-INF_D,2.2)), REP<double>(-INF_D,2.0) );
}

BOOST_AUTO_TEST_CASE(minimal_round_ties_to_away_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::round_ties_to_away(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(1.1,2.1)), REP<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(-1.1,2.0)), REP<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(-1.1,0.0)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(-1.1,-0.0)), REP<double>(-1.0,-0.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(-1.1,-0.4)), REP<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(-1.9,2.2)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(-1.0,2.2)), REP<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(0.5,2.1)), REP<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(-2.5,2.0)), REP<double>(-3.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(-1.1,-0.5)), REP<double>(-1.0,-1.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(-1.9,2.5)), REP<double>(-2.0,3.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(-1.5,2.5)), REP<double>(-2.0,3.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(0.0,2.5)), REP<double>(0.0,3.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(-0.0,2.5)), REP<double>(0.0,3.0) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(-1.5,INF_D)), REP<double>(-2.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::round_ties_to_away(REP<double>(-INF_D,2.2)), REP<double>(-INF_D,2.0) );
}

BOOST_AUTO_TEST_CASE(minimal_abs_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::abs(F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::abs(F<double>::entire()), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::abs(REP<double>(1.1,2.1)), REP<double>(1.1,2.1) );
    BOOST_CHECK_EQUAL( F<double>::abs(REP<double>(-1.1,2.0)), REP<double>(0.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::abs(REP<double>(-1.1,0.0)), REP<double>(0.0,1.1) );
    BOOST_CHECK_EQUAL( F<double>::abs(REP<double>(-1.1,-0.0)), REP<double>(0.0,1.1) );
    BOOST_CHECK_EQUAL( F<double>::abs(REP<double>(-1.1,-0.4)), REP<double>(0.4,1.1) );
    BOOST_CHECK_EQUAL( F<double>::abs(REP<double>(-1.9,0.2)), REP<double>(0.0,1.9) );
    BOOST_CHECK_EQUAL( F<double>::abs(REP<double>(0.0,0.2)), REP<double>(0.0,0.2) );
    BOOST_CHECK_EQUAL( F<double>::abs(REP<double>(-0.0,0.2)), REP<double>(0.0,0.2) );
    BOOST_CHECK_EQUAL( F<double>::abs(REP<double>(-1.5,INF_D)), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::abs(REP<double>(-INF_D,-2.2)), REP<double>(2.2,INF_D) );
}

BOOST_AUTO_TEST_CASE(minimal_min_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::min(F<double>::empty(),REP<double>(1.0,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::min(REP<double>(1.0,2.0),F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::min(F<double>::empty(),F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::min(F<double>::entire(),REP<double>(1.0,2.0)), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::min(REP<double>(1.0,2.0),F<double>::entire()), REP<double>(-INF_D,2.0) );
    BOOST_CHECK_EQUAL( F<double>::min(F<double>::entire(),F<double>::entire()), F<double>::entire() );
BOOST_CHECK( F<double>::is_empty( F<double>::min(F<double>::empty(),F<double>::entire()) ) );
    BOOST_CHECK_EQUAL( F<double>::min(REP<double>(1.0,5.0),REP<double>(2.0,4.0)), REP<double>(1.0,4.0) );
    BOOST_CHECK_EQUAL( F<double>::min(REP<double>(0.0,5.0),REP<double>(2.0,4.0)), REP<double>(0.0,4.0) );
    BOOST_CHECK_EQUAL( F<double>::min(REP<double>(-0.0,5.0),REP<double>(2.0,4.0)), REP<double>(0.0,4.0) );
    BOOST_CHECK_EQUAL( F<double>::min(REP<double>(1.0,5.0),REP<double>(2.0,8.0)), REP<double>(1.0,5.0) );
    BOOST_CHECK_EQUAL( F<double>::min(REP<double>(1.0,5.0),F<double>::entire()), REP<double>(-INF_D,5.0) );
    BOOST_CHECK_EQUAL( F<double>::min(REP<double>(-7.0,-5.0),REP<double>(2.0,4.0)), REP<double>(-7.0,-5.0) );
    BOOST_CHECK_EQUAL( F<double>::min(REP<double>(-7.0,0.0),REP<double>(2.0,4.0)), REP<double>(-7.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::min(REP<double>(-7.0,-0.0),REP<double>(2.0,4.0)), REP<double>(-7.0,0.0) );
}

BOOST_AUTO_TEST_CASE(minimal_max_test)
{
BOOST_CHECK( F<double>::is_empty( F<double>::max(F<double>::empty(),REP<double>(1.0,2.0)) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::max(REP<double>(1.0,2.0),F<double>::empty()) ) );
BOOST_CHECK( F<double>::is_empty( F<double>::max(F<double>::empty(),F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::max(F<double>::entire(),REP<double>(1.0,2.0)), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::max(REP<double>(1.0,2.0),F<double>::entire()), REP<double>(1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::max(F<double>::entire(),F<double>::entire()), F<double>::entire() );
BOOST_CHECK( F<double>::is_empty( F<double>::max(F<double>::empty(),F<double>::entire()) ) );
    BOOST_CHECK_EQUAL( F<double>::max(REP<double>(1.0,5.0),REP<double>(2.0,4.0)), REP<double>(2.0,5.0) );
    BOOST_CHECK_EQUAL( F<double>::max(REP<double>(1.0,5.0),REP<double>(2.0,8.0)), REP<double>(2.0,8.0) );
    BOOST_CHECK_EQUAL( F<double>::max(REP<double>(-1.0,5.0),F<double>::entire()), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::max(REP<double>(-7.0,-5.0),REP<double>(2.0,4.0)), REP<double>(2.0,4.0) );
    BOOST_CHECK_EQUAL( F<double>::max(REP<double>(-7.0,-5.0),REP<double>(0.0,4.0)), REP<double>(0.0,4.0) );
    BOOST_CHECK_EQUAL( F<double>::max(REP<double>(-7.0,-5.0),REP<double>(-0.0,4.0)), REP<double>(0.0,4.0) );
    BOOST_CHECK_EQUAL( F<double>::max(REP<double>(-7.0,-5.0),REP<double>(-2.0,0.0)), REP<double>(-2.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::max(REP<double>(-7.0,-5.0),REP<double>(-2.0,-0.0)), REP<double>(-2.0,0.0) );
}

