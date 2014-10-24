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
//   UnF<double>::less required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#define BOOST_TEST_MODULE "Flavor: Boolean functions of intervals [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

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

const double INF = std::numeric_limits<double>::infinity();
const double NaN = std::numeric_limits<double>::quiet_NaN();

BOOST_AUTO_TEST_CASE(minimal_is_empty_test)
{
    BOOST_CHECK( F<double>::is_empty(REP<double>(NaN,NaN)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-INF,+INF)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-3.0,-2.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-INF,2.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-INF,0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-INF,-0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(0.0,INF)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-0.0,INF)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(0.0,-0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-0.0,-0.0)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_empty_dec_test)
{
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(NaN,NaN), DEC::ill)) );
    BOOST_CHECK( F<double>::is_empty(REP_DEC<double>(REP<double>(NaN,NaN), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-INF,+INF), DEC::def)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(1.0,2.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-1.0,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-3.0,-2.0), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-INF,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-INF,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-INF,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(0.0,INF), DEC::def)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-0.0,INF), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_entire_test)
{
    BOOST_CHECK( !F<double>::is_entire(REP<double>(NaN,NaN)) );
    BOOST_CHECK( F<double>::is_entire(REP<double>(-INF,+INF)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-3.0,-2.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-INF,2.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-INF,0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-INF,-0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(0.0,INF)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-0.0,INF)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(0.0,-0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-0.0,-0.0)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_entire_dec_test)
{
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(NaN,NaN), DEC::ill)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(NaN,NaN), DEC::trv)) );
    BOOST_CHECK( F<double>::is_entire(REP_DEC<double>(REP<double>(-INF,+INF), DEC::trv)) );
    BOOST_CHECK( F<double>::is_entire(REP_DEC<double>(REP<double>(-INF,+INF), DEC::def)) );
    BOOST_CHECK( F<double>::is_entire(REP_DEC<double>(REP<double>(-INF,+INF), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(1.0,2.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-1.0,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-3.0,-2.0), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-INF,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-INF,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-INF,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(0.0,INF), DEC::def)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-0.0,INF), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_nai_dec_test)
{
    BOOST_CHECK( F<double>::is_nai(REP_DEC<double>(REP<double>(NaN,NaN), DEC::ill)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(NaN,NaN), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF,+INF), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF,+INF), DEC::def)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF,+INF), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(1.0,2.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-1.0,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-3.0,-2.0), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(0.0,INF), DEC::def)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-0.0,INF), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)) );
}

//BOOST_AUTO_TEST_CASE(minimal_is_equal_test)
//{
//    BOOST_CHECK( F<double>::is_equal(REP<double>(1.0,2.0), REP<double>(1.0,2.0)) );
//    BOOST_CHECK( !F<double>::is_equal(REP<double>(1.0,2.1), REP<double>(1.0,2.0)) );
//    BOOST_CHECK( F<double>::is_equal(REP<double>(NaN,NaN), REP<double>(NaN,NaN)) );
//    BOOST_CHECK( !F<double>::is_equal(REP<double>(NaN,NaN), REP<double>(1.0,2.0)) );
//    BOOST_CHECK( F<double>::is_equal(REP<double>(-INF,+INF), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( !F<double>::is_equal(REP<double>(1.0,2.4), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( F<double>::is_equal(REP<double>(1.0,INF), REP<double>(1.0,INF)) );
//    BOOST_CHECK( !F<double>::is_equal(REP<double>(1.0,2.4), REP<double>(1.0,INF)) );
//    BOOST_CHECK( F<double>::is_equal(REP<double>(-INF,2.0), REP<double>(-INF,2.0)) );
//    BOOST_CHECK( !F<double>::is_equal(REP<double>(-INF,2.4), REP<double>(-INF,2.0)) );
//    BOOST_CHECK( F<double>::is_equal(REP<double>(-2.0,0.0), REP<double>(-2.0,0.0)) );
//    BOOST_CHECK( F<double>::is_equal(REP<double>(-0.0,2.0), REP<double>(0.0,2.0)) );
//    BOOST_CHECK( F<double>::is_equal(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) );
//    BOOST_CHECK( F<double>::is_equal(REP<double>(-0.0,0.0), REP<double>(0.0,0.0)) );
//    BOOST_CHECK( F<double>::is_equal(REP<double>(0.0,-0.0), REP<double>(0.0,0.0)) );
//}
//
//
//BOOST_AUTO_TEST_CASE(minimal_subset_test)
//{
//    BOOST_CHECK( F<double>::subset(REP<double>(NaN,NaN), REP<double>(NaN,NaN)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(NaN,NaN), REP<double>(0.0,4.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(NaN,NaN), REP<double>(-0.0,4.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(NaN,NaN), REP<double>(-0.1,1.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(NaN,NaN), REP<double>(-0.1,0.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(NaN,NaN), REP<double>(-0.1,-0.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(NaN,NaN), REP<double>(-INF,+INF)) );
//
//    BOOST_CHECK( !F<double>::subset(REP<double>(0.0,4.0), REP<double>(NaN,NaN)) );
//    BOOST_CHECK( !F<double>::subset(REP<double>(-0.0,4.0), REP<double>(NaN,NaN)) );
//    BOOST_CHECK( !F<double>::subset(REP<double>(-0.1,1.0), REP<double>(NaN,NaN)) );
//    BOOST_CHECK( !F<double>::subset(REP<double>(-INF,+INF), REP<double>(NaN,NaN)) );
//
//    BOOST_CHECK( F<double>::subset(REP<double>(0.0,4.0), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,4.0), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(-0.1,1.0), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(-INF,+INF), REP<double>(-INF,+INF)) );
//
//    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<double>(1.0,2.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<double>(0.0,4.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<double>(-0.0,4.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(0.1,0.2), REP<double>(0.0,4.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(0.1,0.2), REP<double>(-0.0,4.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(-0.1,-0.1), REP<double>(-4.0, 3.4)) );
//
//    BOOST_CHECK( F<double>::subset(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,0.0), REP<double>(0.0,0.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,0.0), REP<double>(0.0,-0.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(0.0,-0.0), REP<double>(0.0,0.0)) );
//    BOOST_CHECK( F<double>::subset(REP<double>(0.0,-0.0), REP<double>(-0.0,0.0)) );
//}
//
//
//BOOST_AUTO_TEST_CASE(minimal_less_test)
//{
//    BOOST_CHECK( F<double>::less(REP<double>(NaN,NaN), REP<double>(NaN,NaN)) );
//    BOOST_CHECK( !F<double>::less(REP<double>(1.0,2.0), REP<double>(NaN,NaN)) );
//    BOOST_CHECK( !F<double>::less(REP<double>(NaN,NaN), REP<double>(1.0,2.0)) );
//
//    BOOST_CHECK( F<double>::less(REP<double>(-INF,+INF), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( !F<double>::less(REP<double>(1.0,2.0), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( !F<double>::less(REP<double>(0.0,2.0), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( !F<double>::less(REP<double>(-0.0,2.0), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( !F<double>::less(REP<double>(-INF,+INF), REP<double>(1.0,2.0)) );
//    BOOST_CHECK( !F<double>::less(REP<double>(-INF,+INF), REP<double>(0.0,2.0)) );
//    BOOST_CHECK( !F<double>::less(REP<double>(-INF,+INF), REP<double>(-0.0,2.0)) );
//
//    BOOST_CHECK( F<double>::less(REP<double>(0.0,2.0), REP<double>(0.0,2.0)) );
//    BOOST_CHECK( F<double>::less(REP<double>(0.0,2.0), REP<double>(-0.0,2.0)) );
//    BOOST_CHECK( F<double>::less(REP<double>(0.0,2.0), REP<double>(1.0,2.0)) );
//    BOOST_CHECK( F<double>::less(REP<double>(-0.0,2.0), REP<double>(1.0,2.0)) );
//    BOOST_CHECK( F<double>::less(REP<double>(1.0,2.0), REP<double>(1.0,2.0)) );
//    BOOST_CHECK( F<double>::less(REP<double>(1.0,2.0), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( F<double>::less(REP<double>(1.0,3.5), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( F<double>::less(REP<double>(1.0,4.0), REP<double>(3.0,4.0)) );
//
//    BOOST_CHECK( F<double>::less(REP<double>(-2.0,-1.0), REP<double>(-2.0,-1.0)) );
//    BOOST_CHECK( F<double>::less(REP<double>(-3.0,-1.5), REP<double>(-2.0,-1.0)) );
//
//    BOOST_CHECK( F<double>::less(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );
//    BOOST_CHECK( F<double>::less(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) );
//    BOOST_CHECK( F<double>::less(REP<double>(-0.0,0.0), REP<double>(0.0,0.0)) );
//    BOOST_CHECK( F<double>::less(REP<double>(-0.0,0.0), REP<double>(0.0,-0.0)) );
//    BOOST_CHECK( F<double>::less(REP<double>(0.0,-0.0), REP<double>(0.0,0.0)) );
//    BOOST_CHECK( F<double>::less(REP<double>(0.0,-0.0), REP<double>(-0.0,0.0)) );
//}
//
//
//BOOST_AUTO_TEST_CASE(minimal_precedes_test)
//{
//    BOOST_CHECK( F<double>::precedes(REP<double>(NaN,NaN), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( F<double>::precedes(REP<double>(3.0,4.0), REP<double>(NaN,NaN)) );
//    BOOST_CHECK( F<double>::precedes(REP<double>(NaN,NaN), REP<double>(NaN,NaN)) );
//
//
//    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,2.0), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( !F<double>::precedes(REP<double>(0.0,2.0), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( !F<double>::precedes(REP<double>(-0.0,2.0), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( !F<double>::precedes(REP<double>(-INF,+INF), REP<double>(1.0,2.0)) );
//    BOOST_CHECK( !F<double>::precedes(REP<double>(-INF,+INF), REP<double>(-INF,+INF)) );
//
//    BOOST_CHECK( F<double>::precedes(REP<double>(1.0,2.0), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( F<double>::precedes(REP<double>(1.0,3.0), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( F<double>::precedes(REP<double>(-3.0, -1.0), REP<double>(-1.0,0.0)) );
//    BOOST_CHECK( F<double>::precedes(REP<double>(-3.0, -1.0), REP<double>(-1.0,-0.0)) );
//
//    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,3.5), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,4.0), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( !F<double>::precedes(REP<double>(-3.0, -0.1), REP<double>(-1.0,0.0)) );
//
//    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );
//    BOOST_CHECK( F<double>::precedes(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) );
//    BOOST_CHECK( F<double>::precedes(REP<double>(-0.0,0.0), REP<double>(0.0,0.0)) );
//    BOOST_CHECK( F<double>::precedes(REP<double>(-0.0,0.0), REP<double>(0.0,-0.0)) );
//    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,-0.0), REP<double>(0.0,0.0)) );
//    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,-0.0), REP<double>(-0.0,0.0)) );
//}
//
//
//BOOST_AUTO_TEST_CASE(minimal_is_interior_test)
//{
//    BOOST_CHECK( F<double>::is_interior(REP<double>(NaN,NaN), REP<double>(NaN,NaN)) );
//    BOOST_CHECK( F<double>::is_interior(REP<double>(NaN,NaN), REP<double>(0.0,4.0)) );
//    BOOST_CHECK( !F<double>::is_interior(REP<double>(0.0,4.0), REP<double>(NaN,NaN)) );
//
//    BOOST_CHECK( F<double>::is_interior(REP<double>(-INF,+INF), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( F<double>::is_interior(REP<double>(0.0,4.0), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( F<double>::is_interior(REP<double>(NaN,NaN), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( !F<double>::is_interior(REP<double>(-INF,+INF), REP<double>(0.0,4.0)) );
//
//    BOOST_CHECK( !F<double>::is_interior(REP<double>(0.0,4.0), REP<double>(0.0,4.0)) );
//    BOOST_CHECK( F<double>::is_interior(REP<double>(1.0,2.0), REP<double>(0.0,4.0)) );
//    BOOST_CHECK( !F<double>::is_interior(REP<double>(-2.0,2.0), REP<double>(-2.0,4.0)) );
//    BOOST_CHECK( F<double>::is_interior(REP<double>(-0.0,-0.0), REP<double>(-2.0,4.0)) );
//    BOOST_CHECK( F<double>::is_interior(REP<double>(0.0,0.0), REP<double>(-2.0,4.0)) );
//    BOOST_CHECK( !F<double>::is_interior(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );
//
//    BOOST_CHECK( !F<double>::is_interior(REP<double>(0.0,4.4), REP<double>(0.0,4.0)) );
//    BOOST_CHECK( !F<double>::is_interior(REP<double>(-1.0,-1.0), REP<double>(0.0,4.0)) );
//    BOOST_CHECK( !F<double>::is_interior(REP<double>(2.0,2.0), REP<double>(-2.0,-1.0)) );
//}
//
//
//BOOST_AUTO_TEST_CASE(minimal_strictly_less_test)
//{
//    BOOST_CHECK( F<double>::strictly_less(REP<double>(NaN,NaN), REP<double>(NaN,NaN)) );
//    BOOST_CHECK( !F<double>::strictly_less(REP<double>(1.0,2.0), REP<double>(NaN,NaN)) );
//    BOOST_CHECK( !F<double>::strictly_less(REP<double>(NaN,NaN), REP<double>(1.0,2.0)) );
//
//    BOOST_CHECK( F<double>::strictly_less(REP<double>(-INF,+INF), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( !F<double>::strictly_less(REP<double>(1.0,2.0), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( !F<double>::strictly_less(REP<double>(-INF,+INF), REP<double>(1.0,2.0)) );
//
//    BOOST_CHECK( !F<double>::strictly_less(REP<double>(1.0,2.0), REP<double>(1.0,2.0)) );
//    BOOST_CHECK( F<double>::strictly_less(REP<double>(1.0,2.0), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( F<double>::strictly_less(REP<double>(1.0,3.5), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( !F<double>::strictly_less(REP<double>(1.0,4.0), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( !F<double>::strictly_less(REP<double>(0.0,4.0), REP<double>(0.0,4.0)) );
//    BOOST_CHECK( !F<double>::strictly_less(REP<double>(-0.0,4.0), REP<double>(0.0,4.0)) );
//
//    BOOST_CHECK( !F<double>::strictly_less(REP<double>(-2.0,-1.0), REP<double>(-2.0,-1.0)) );
//    BOOST_CHECK( F<double>::strictly_less(REP<double>(-3.0,-1.5), REP<double>(-2.0,-1.0)) );
//}
//
//
//BOOST_AUTO_TEST_CASE(minimal_strictly_precedes_test)
//{
//    BOOST_CHECK( F<double>::strictly_precedes(REP<double>(NaN,NaN), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( F<double>::strictly_precedes(REP<double>(3.0,4.0), REP<double>(NaN,NaN)) );
//    BOOST_CHECK( F<double>::strictly_precedes(REP<double>(NaN,NaN), REP<double>(NaN,NaN)) );
//
//
//    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(1.0,2.0), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-INF,+INF), REP<double>(1.0,2.0)) );
//    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-INF,+INF), REP<double>(-INF,+INF)) );
//
//    BOOST_CHECK( F<double>::strictly_precedes(REP<double>(1.0,2.0), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(1.0,3.0), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-3.0, -1.0), REP<double>(-1.0,0.0)) );
//    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-3.0, -0.0), REP<double>(0.0,1.0)) );
//    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-3.0, 0.0), REP<double>(-0.0,1.0)) );
//
//    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(1.0,3.5), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(1.0,4.0), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-3.0, -0.1), REP<double>(-1.0,0.0)) );
//}
//
//
//BOOST_AUTO_TEST_CASE(minimal_are_disjoint_test)
//{
//    BOOST_CHECK( F<double>::are_disjoint(REP<double>(NaN,NaN), REP<double>(3.0,4.0)) );
//    BOOST_CHECK( F<double>::are_disjoint(REP<double>(3.0,4.0), REP<double>(NaN,NaN)) );
//    BOOST_CHECK( F<double>::are_disjoint(REP<double>(NaN,NaN), REP<double>(NaN,NaN)) );
//
//    BOOST_CHECK( F<double>::are_disjoint(REP<double>(3.0,4.0), REP<double>(1.0,2.0)) );
//
//    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );
//    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(0.0,-0.0), REP<double>(-0.0,0.0)) );
//    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(3.0,4.0), REP<double>(1.0,7.0)) );
//    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(3.0,4.0), REP<double>(-INF,+INF)) );
//    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(-INF,+INF), REP<double>(1.0,7.0)) );
//    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(-INF,+INF), REP<double>(-INF,+INF)) );
//}
