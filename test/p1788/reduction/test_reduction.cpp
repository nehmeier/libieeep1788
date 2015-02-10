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
//   UnF<double>::less required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#define BOOST_TEST_MODULE "Reduction operations [p1788/reduction/reduction]"
#include "test/util/boost_test_wrapper.hpp"


#include "p1788/reduction/reduction.hpp"


#include <iostream>
#include <limits>
#include <cmath>

const double INF_D = std::numeric_limits<double>::infinity();
const double NaN_D = std::numeric_limits<double>::quiet_NaN();
const double MAX_D = std::numeric_limits<double>::max();
const double MIN_D = std::numeric_limits<double>::min();
const double DNORM_MIN_D = std::numeric_limits<double>::denorm_min();


BOOST_AUTO_TEST_CASE(minimal_sum_test)
{
    double a[] = {1.0,2.0,3.0};

    BOOST_CHECK_EQUAL( p1788::reduction::sum(std::begin(a), std::end(a), p1788::reduction::rnd_mode::to_nearest), 6.0);
    BOOST_CHECK_EQUAL( p1788::reduction::sum(a, a + 3, p1788::reduction::rnd_mode::to_nearest), 6.0 );
    BOOST_CHECK_EQUAL( p1788::reduction::sum({1.0,2.0,3.0}, p1788::reduction::rnd_mode::to_nearest), 6.0 );

    BOOST_CHECK( std::isnan( p1788::reduction::sum({1.0,2.0,NaN_D,3.0}, p1788::reduction::rnd_mode::to_nearest) ) );

    BOOST_CHECK( std::isnan( p1788::reduction::sum({1.0,-INF_D,2.0,INF_D,3.0}, p1788::reduction::rnd_mode::to_nearest) ) );
}


BOOST_AUTO_TEST_CASE(minimal_sum_abs_test)
{
    double a[] = {1.0,-2.0,3.0};

    BOOST_CHECK_EQUAL( p1788::reduction::sum_abs(std::begin(a), std::end(a), p1788::reduction::rnd_mode::to_nearest), 6.0 );
    BOOST_CHECK_EQUAL( p1788::reduction::sum_abs(a, a + 3, p1788::reduction::rnd_mode::to_nearest), 6.0 );
    BOOST_CHECK_EQUAL( p1788::reduction::sum_abs({1.0,-2.0,3.0}, p1788::reduction::rnd_mode::to_nearest), 6.0 );

    BOOST_CHECK( std::isnan( p1788::reduction::sum_abs({1.0,-2.0,NaN_D,3.0}, p1788::reduction::rnd_mode::to_nearest) ) );

    BOOST_CHECK_EQUAL( p1788::reduction::sum_abs({1.0,-INF_D,2.0,INF_D,3.0}, p1788::reduction::rnd_mode::to_nearest), INF_D );
}


BOOST_AUTO_TEST_CASE(minimal_sum_sqr_test)
{
    double a[] = {1.0,2.0,3.0};

    BOOST_CHECK_EQUAL( p1788::reduction::sum_sqr(std::begin(a), std::end(a), p1788::reduction::rnd_mode::to_nearest), 14.0 );
    BOOST_CHECK_EQUAL( p1788::reduction::sum_sqr(a, a + 3, p1788::reduction::rnd_mode::to_nearest), 14.0 );
    BOOST_CHECK_EQUAL( p1788::reduction::sum_sqr({1.0,2.0,3.0}, p1788::reduction::rnd_mode::to_nearest), 14.0 );

    BOOST_CHECK( std::isnan( p1788::reduction::sum_sqr({1.0,2.0,NaN_D,3.0}, p1788::reduction::rnd_mode::to_nearest) ) );

    BOOST_CHECK_EQUAL( p1788::reduction::sum_sqr({1.0,-INF_D,2.0,INF_D,3.0}, p1788::reduction::rnd_mode::to_nearest), INF_D );
}

BOOST_AUTO_TEST_CASE(minimal_dot_test)
{

    double a[] = {1.0, 2.0, 3.0};
    double b[] = {1.0, 2.0, 3.0};

    BOOST_CHECK_EQUAL( p1788::reduction::dot(std::begin(a), std::end(a), std::begin(b), p1788::reduction::rnd_mode::to_nearest), 14.0 );
    BOOST_CHECK_EQUAL( p1788::reduction::dot(a, a + 3, b, p1788::reduction::rnd_mode::to_nearest), 14.0 );
    BOOST_CHECK_EQUAL( p1788::reduction::dot({1.0,2.0,3.0}, {1.0,2.0,3.0}, p1788::reduction::rnd_mode::to_nearest), 14.0 );

    BOOST_CHECK_EQUAL( p1788::reduction::dot({std::stod("0x10000000000001p0"), std::stod("0x1p104")}, {std::stod("0x0fffffffffffffp0"), -1.0}, p1788::reduction::rnd_mode::to_nearest), -1.0 );

    BOOST_CHECK( std::isnan( p1788::reduction::dot({1.0,2.0,NaN_D,3.0}, {1.0,2.0,3.0,4.0}, p1788::reduction::rnd_mode::to_nearest) ) );
    BOOST_CHECK( std::isnan( p1788::reduction::dot({1.0,2.0,3.0,4.0}, {1.0,2.0,NaN_D,3.0}, p1788::reduction::rnd_mode::to_nearest) ) );

    BOOST_CHECK( std::isnan( p1788::reduction::dot({1.0,2.0,0.0,4.0}, {1.0,2.0,INF_D,3.0}, p1788::reduction::rnd_mode::to_nearest) ) );
    BOOST_CHECK( std::isnan( p1788::reduction::dot({1.0,2.0,-INF_D,4.0}, {1.0,2.0,0.0,3.0}, p1788::reduction::rnd_mode::to_nearest) ) );
}
