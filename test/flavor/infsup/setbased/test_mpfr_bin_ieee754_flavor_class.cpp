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

#define BOOST_TEST_MODULE "Flavor: Constructors, Methods, Interval constants [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"
#include "p1788/decoration/decoration.hpp"
#include "test/util/mpfr_bin_ieee754_flavor_io_test_util.hpp"

#include <cmath>
#include <limits>

template<typename T>
using F = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>;


const double INF = std::numeric_limits<double>::infinity();



BOOST_AUTO_TEST_CASE(minimal_empty_test)
{
    BOOST_CHECK( std::isnan( F<double>::empty().first ) );
    BOOST_CHECK( std::isnan( F<double>::empty().second ) );
}

BOOST_AUTO_TEST_CASE(minimal_empty_dec_test)
{
    BOOST_CHECK( std::isnan( F<double>::empty_dec().first.first ) );
    BOOST_CHECK( std::isnan( F<double>::empty_dec().first.second ) );
    BOOST_CHECK_EQUAL( F<double>::empty_dec().second, p1788::decoration::decoration::trv );
}

BOOST_AUTO_TEST_CASE(minimal_entire_test)
{
    BOOST_CHECK_EQUAL( F<double>::entire().first, -INF );
    BOOST_CHECK_EQUAL( F<double>::entire().second, INF );
}

BOOST_AUTO_TEST_CASE(minimal_entire_dec_test)
{
    BOOST_CHECK_EQUAL( F<double>::entire_dec().first.first, -INF );
    BOOST_CHECK_EQUAL( F<double>::entire_dec().first.second, INF );
    BOOST_CHECK_EQUAL( F<double>::entire_dec().second, p1788::decoration::decoration::dac );
}

BOOST_AUTO_TEST_CASE(minimal_nai_test)
{
    BOOST_CHECK( std::isnan( F<double>::nai().first.first ) );
    BOOST_CHECK( std::isnan( F<double>::nai().first.second ) );
    BOOST_CHECK_EQUAL( F<double>::nai().second, p1788::decoration::decoration::ill );
}
