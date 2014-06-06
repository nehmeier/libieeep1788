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

#define BOOST_TEST_MODULE "Forward elementary functions [inf-sup-interval, mpfr_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include <limits>
#include "p1788/p1788.hpp"


template<typename T>
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes>;

template<typename T>
using I = p1788::infsup::interval<T, flavor>;

const double INF = std::numeric_limits<double>::infinity();
const double MAX = std::numeric_limits<double>::max();
const double MIN = std::numeric_limits<double>::min();


BOOST_AUTO_TEST_CASE(minimal_pos_test)
{
    BOOST_CHECK_EQUAL( pos(I<double>(1.0,2.0)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( +I<double>(1.0,2.0), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( pos(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( +I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( pos(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( +I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( pos(I<double>(1.0,INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( +I<double>(1.0,INF), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( pos(I<double>(-INF,-1.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( +I<double>(-INF,-1.0), I<double>(-INF,-1.0) );
}

BOOST_AUTO_TEST_CASE(minimal_neg_test)
{
    BOOST_CHECK_EQUAL( neg(I<double>(1.0,2.0)), I<double>(-2.0,-1.0) );
    BOOST_CHECK_EQUAL( -I<double>(1.0,2.0), I<double>(-2.0,-1.0) );
    BOOST_CHECK_EQUAL( neg(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( -I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( neg(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( -I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( neg(I<double>(1.0,INF)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( -I<double>(1.0,INF), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( neg(I<double>(-INF,1.0)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( -I<double>(-INF,1.0), I<double>(-1.0,INF) );
}

BOOST_AUTO_TEST_CASE(minimal_add_test)
{
    BOOST_CHECK_EQUAL( add(I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() + I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( add(I<double>(-1.0,1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,1.0) + I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( add(I<double>::empty(), I<double>(-1.0,1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() + I<double>(-1.0,1.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( add(I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() + I<double>::entire(), I<double>::empty() );
    BOOST_CHECK_EQUAL( add(I<double>::entire(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::entire() + I<double>::empty(), I<double>::empty() );

    BOOST_CHECK_EQUAL( add(I<double>::entire(), I<double>(-INF,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() + I<double>(-INF,1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>::entire(), I<double>(-1.0,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() + I<double>(-1.0,1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>::entire(), I<double>(-1.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() + I<double>(-1.0,INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>::entire(), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() + I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>(-INF,1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,1.0) + I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>(-1.0,1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,1.0) + I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>(-1.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) + I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( add(I<double>(-INF,2.0), I<double>(-INF,4.0)), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,2.0) + I<double>(-INF,4.0), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( add(I<double>(-INF,2.0), I<double>(3.0,4.0)), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,2.0) + I<double>(3.0,4.0), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( add(I<double>(-INF,2.0), I<double>(3.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,2.0) + I<double>(3.0,INF), I<double>::entire() );

    BOOST_CHECK_EQUAL( add(I<double>(1.0,2.0), I<double>(-INF,4.0)), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) + I<double>(-INF,4.0), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( add(I<double>(1.0,2.0), I<double>(3.0,4.0)), I<double>(4.0,6.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) + I<double>(3.0,4.0), I<double>(4.0,6.0) );
    BOOST_CHECK_EQUAL( add(I<double>(1.0,2.0), I<double>(3.0,INF)), I<double>(4.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) + I<double>(3.0,INF), I<double>(4.0,INF) );

    BOOST_CHECK_EQUAL( add(I<double>(1.0,INF), I<double>(-INF,4.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) + I<double>(-INF,4.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( add(I<double>(1.0,INF), I<double>(3.0,4.0)), I<double>(4.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) + I<double>(3.0,4.0), I<double>(4.0,INF) );
    BOOST_CHECK_EQUAL( add(I<double>(1.0,INF), I<double>(3.0,INF)), I<double>(4.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) + I<double>(3.0,INF), I<double>(4.0,INF) );

    BOOST_CHECK_EQUAL( add(I<double>(1.0,MAX), I<double>(3.0,4.0)), I<double>(4.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,MAX) + I<double>(3.0,4.0), I<double>(4.0,INF) );
    BOOST_CHECK_EQUAL( add(I<double>(-MAX,2.0), I<double>(-3.0,4.0)), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( I<double>(-MAX,2.0) + I<double>(-3.0,4.0), I<double>(-INF,6.0) );
    BOOST_CHECK_EQUAL( add(I<double>(-MAX,2.0), I<double>(-3.0,MAX)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-MAX,2.0) + I<double>(-3.0,MAX), I<double>::entire() );

    BOOST_CHECK_EQUAL( add(I<double>(0X1.FFFFFFFFFFFFP+0), I<double>(0X1.999999999999AP-4)), I<double>(0X1.0CCCCCCCCCCC4P+1,0X1.0CCCCCCCCCCC5P+1) );
    BOOST_CHECK_EQUAL( I<double>(0X1.FFFFFFFFFFFFP+0) + I<double>(0X1.999999999999AP-4), I<double>(0X1.0CCCCCCCCCCC4P+1,0X1.0CCCCCCCCCCC5P+1) );
    BOOST_CHECK_EQUAL( add(I<double>(0X1.FFFFFFFFFFFFP+0), I<double>(-0X1.999999999999AP-4)), I<double>(0X1.E666666666656P+0,0X1.E666666666657P+0) );
    BOOST_CHECK_EQUAL( I<double>(0X1.FFFFFFFFFFFFP+0) + I<double>(-0X1.999999999999AP-4), I<double>(0X1.E666666666656P+0,0X1.E666666666657P+0) );
    BOOST_CHECK_EQUAL( add(I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.FFFFFFFFFFFFP+0), I<double>(0X1.999999999999AP-4)), I<double>(-0X1.E666666666657P+0,0X1.0CCCCCCCCCCC5P+1) );
    BOOST_CHECK_EQUAL( I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.FFFFFFFFFFFFP+0) + I<double>(0X1.999999999999AP-4), I<double>(-0X1.E666666666657P+0,0X1.0CCCCCCCCCCC5P+1) );
}

BOOST_AUTO_TEST_CASE(minimal_sub_test)
{
    BOOST_CHECK_EQUAL( sub(I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() - I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( sub(I<double>(-1.0,1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,1.0) - I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( sub(I<double>::empty(), I<double>(-1.0,1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() - I<double>(-1.0,1.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( sub(I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() - I<double>::entire(), I<double>::empty() );
    BOOST_CHECK_EQUAL( sub(I<double>::entire(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::entire() - I<double>::empty(), I<double>::empty() );

    BOOST_CHECK_EQUAL( sub(I<double>::entire(), I<double>(-INF,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() - I<double>(-INF,1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>::entire(), I<double>(-1.0,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() - I<double>(-1.0,1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>::entire(), I<double>(-1.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() - I<double>(-1.0,INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>::entire(), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() - I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>(-INF,1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,1.0) - I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>(-1.0,1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,1.0) - I<double>::entire(), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>(-1.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) - I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( sub(I<double>(-INF,2.0), I<double>(-INF,4.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,2.0) - I<double>(-INF,4.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( sub(I<double>(-INF,2.0), I<double>(3.0,4.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,2.0) - I<double>(3.0,4.0), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( sub(I<double>(-INF,2.0), I<double>(3.0,INF)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,2.0) - I<double>(3.0,INF), I<double>(-INF,-1.0) );

    BOOST_CHECK_EQUAL( sub(I<double>(1.0,2.0), I<double>(-INF,4.0)), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) - I<double>(-INF,4.0), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( sub(I<double>(1.0,2.0), I<double>(3.0,4.0)), I<double>(-3.0,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) - I<double>(3.0,4.0), I<double>(-3.0,-1.0) );
    BOOST_CHECK_EQUAL( sub(I<double>(1.0,2.0), I<double>(3.0,INF)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) - I<double>(3.0,INF), I<double>(-INF,-1.0) );

    BOOST_CHECK_EQUAL( sub(I<double>(1.0,INF), I<double>(-INF,4.0)), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) - I<double>(-INF,4.0), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( sub(I<double>(1.0,INF), I<double>(3.0,4.0)), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) - I<double>(3.0,4.0), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( sub(I<double>(1.0,INF), I<double>(3.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) - I<double>(3.0,INF), I<double>::entire() );

    BOOST_CHECK_EQUAL( sub(I<double>(1.0,MAX), I<double>(-3.0,4.0)), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,MAX) - I<double>(-3.0,4.0), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( sub(I<double>(-MAX,2.0), I<double>(3.0,4.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(-MAX,2.0) - I<double>(3.0,4.0), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( sub(I<double>(-MAX,2.0), I<double>(-MAX,4.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-MAX,2.0) - I<double>(-MAX,4.0), I<double>::entire() );

    BOOST_CHECK_EQUAL( sub(I<double>(0X1.FFFFFFFFFFFFP+0), I<double>(0X1.999999999999AP-4)), I<double>(0X1.E666666666656P+0,0X1.E666666666657P+0) );
    BOOST_CHECK_EQUAL( I<double>(0X1.FFFFFFFFFFFFP+0) - I<double>(0X1.999999999999AP-4), I<double>(0X1.E666666666656P+0,0X1.E666666666657P+0) );
    BOOST_CHECK_EQUAL( sub(I<double>(0X1.FFFFFFFFFFFFP+0), I<double>(-0X1.999999999999AP-4)), I<double>(0X1.0CCCCCCCCCCC4P+1,0X1.0CCCCCCCCCCC5P+1) );
    BOOST_CHECK_EQUAL( I<double>(0X1.FFFFFFFFFFFFP+0) - I<double>(-0X1.999999999999AP-4), I<double>(0X1.0CCCCCCCCCCC4P+1,0X1.0CCCCCCCCCCC5P+1) );
    BOOST_CHECK_EQUAL( sub(I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.FFFFFFFFFFFFP+0), I<double>(0X1.999999999999AP-4)), I<double>(-0X1.0CCCCCCCCCCC5P+1,0X1.E666666666657P+0) );
    BOOST_CHECK_EQUAL( I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.FFFFFFFFFFFFP+0) - I<double>(0X1.999999999999AP-4), I<double>(-0X1.0CCCCCCCCCCC5P+1,0X1.E666666666657P+0) );
}

BOOST_AUTO_TEST_CASE(minimal_mul_test)
{
    BOOST_CHECK_EQUAL( mul(I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() * I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,1.0) * I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( mul(I<double>::empty(), I<double>(-1.0,1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() * I<double>(-1.0,1.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( mul(I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() * I<double>::entire(), I<double>::empty() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( mul(I<double>::empty(), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() * I<double>(0.0), I<double>::empty() );

    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(-5.0, -1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(-5.0, -1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(-5.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(-5.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(1.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(1.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(-INF, -1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(-INF, -1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(-5.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(-5.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>(1.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>(1.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>::entire(), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(-5.0, -1.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(-5.0, -1.0), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(-5.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(-5.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(1.0, 3.0)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(1.0, 3.0), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(-INF, -1.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(-INF, -1.0), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(-5.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(-5.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>(1.0, INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>(1.0, INF), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,INF) * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(-5.0, -1.0)), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(-5.0, -1.0), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(-5.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(-5.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(1.0, 3.0)), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(1.0, 3.0), I<double>(-3.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(-INF, -1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(-INF, -1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(-5.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(-5.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>(1.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>(1.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,INF) * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(-5.0, -1.0)), I<double>(-15.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(-5.0, -1.0), I<double>(-15.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(-5.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(-5.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(1.0, 3.0)), I<double>(-INF,9.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(1.0, 3.0), I<double>(-INF,9.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(-INF, -1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(-INF, -1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(-5.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(-5.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>(1.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>(1.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,3.0) * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(-5.0, -1.0)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(-5.0, -1.0), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(-5.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(-5.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(1.0, 3.0)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(1.0, 3.0), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(-INF, -1.0)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(-INF, -1.0), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(-5.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(-5.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>(1.0, INF)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>(1.0, INF), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-INF,-3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-3.0) * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(-5.0, -1.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(-5.0, -1.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(-5.0, 3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(-5.0, 3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(1.0, 3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(1.0, 3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(-INF, -1.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(-INF, -1.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(-INF, 3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(-INF, 3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(-5.0, INF)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(-5.0, INF), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>(1.0, INF)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>(1.0, INF), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(0.0), I<double>::entire()), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) * I<double>::entire(), I<double>(0.0) );

    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(-5.0, -1.0)), I<double>(-25.0,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(-5.0, -1.0), I<double>(-25.0,-1.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(-5.0, 3.0)), I<double>(-25.0,15.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(-5.0, 3.0), I<double>(-25.0,15.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(1.0, 3.0)), I<double>(1.0,15.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(1.0, 3.0), I<double>(1.0,15.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(-INF, -1.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(-INF, -1.0), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(-INF, 3.0)), I<double>(-INF,15.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(-INF, 3.0), I<double>(-INF,15.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(-5.0, INF)), I<double>(-25.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(-5.0, INF), I<double>(-25.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>(1.0, INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>(1.0, INF), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(1.0,5.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(1.0,5.0) * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(-5.0, -1.0)), I<double>(-25.0,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(-5.0, -1.0), I<double>(-25.0,5.0) );
    //min max
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(-5.0, 3.0)), I<double>(-25.0,15.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(-5.0, 3.0), I<double>(-25.0,15.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,2.0), I<double>(-5.0, 3.0)), I<double>(-30.0,50.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,2.0) * I<double>(-5.0, 3.0), I<double>(-30.0,50.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(-1.0, 10.0)), I<double>(-10.0,50.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(-1.0, 10.0), I<double>(-10.0,50.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-2.0,2.0), I<double>(-5.0, 3.0)), I<double>(-10.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-2.0,2.0) * I<double>(-5.0, 3.0), I<double>(-10.0,10.0) );
    //end min max
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(1.0, 3.0)), I<double>(-3.0,15.0) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(1.0, 3.0), I<double>(-3.0,15.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(-INF, -1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(-INF, -1.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(-5.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(-5.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>(1.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>(1.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( mul(I<double>(-1.0,5.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,5.0) * I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(-5.0, -1.0)), I<double>(5.0,50.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(-5.0, -1.0), I<double>(5.0,50.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(-5.0, 3.0)), I<double>(-30.0,50.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(-5.0, 3.0), I<double>(-30.0,50.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(1.0, 3.0)), I<double>(-30.0,-5.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(1.0, 3.0), I<double>(-30.0,-5.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(-INF, -1.0)), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(-INF, -1.0), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(-INF, 3.0)), I<double>(-30.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(-INF, 3.0), I<double>(-30.0,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(-5.0, INF)), I<double>(-INF,50.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(-5.0, INF), I<double>(-INF,50.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>(1.0, INF)), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>(1.0, INF), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( mul(I<double>(-10.0,-5.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-10.0,-5.0) * I<double>::entire(), I<double>::entire() );


    BOOST_CHECK_EQUAL( mul(I<double>(0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0), I<double>(-0X1.FFFFFFFFFFFFP+0, INF)), I<double>(-0X1.FFFFFFFFFFFE1P+1,INF) );
    BOOST_CHECK_EQUAL( I<double>(0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0) * I<double>(-0X1.FFFFFFFFFFFFP+0, INF), I<double>(-0X1.FFFFFFFFFFFE1P+1,INF) );
    BOOST_CHECK_EQUAL( mul(I<double>(-0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0), I<double>(-0X1.FFFFFFFFFFFFP+0,-0X1.999999999999AP-4)), I<double>(-0X1.FFFFFFFFFFFE1P+1,0X1.999999999998EP-3) );
    BOOST_CHECK_EQUAL( I<double>(-0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0) * I<double>(-0X1.FFFFFFFFFFFFP+0,-0X1.999999999999AP-4), I<double>(-0X1.FFFFFFFFFFFE1P+1,0X1.999999999998EP-3) );
    BOOST_CHECK_EQUAL( mul(I<double>(-0X1.999999999999AP-4,0X1.999999999999AP-4), I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.999999999999AP-4)), I<double>(-0X1.999999999998EP-3,0X1.999999999998EP-3) );
    BOOST_CHECK_EQUAL( I<double>(-0X1.999999999999AP-4,0X1.999999999999AP-4) * I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.999999999999AP-4), I<double>(-0X1.999999999998EP-3,0X1.999999999998EP-3) );
    BOOST_CHECK_EQUAL( mul(I<double>(-0X1.FFFFFFFFFFFFP+0,-0X1.999999999999AP-4), I<double>(0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0)), I<double>(-0X1.FFFFFFFFFFFE1P+1,-0X1.47AE147AE147BP-7) );
    BOOST_CHECK_EQUAL( I<double>(-0X1.FFFFFFFFFFFFP+0,-0X1.999999999999AP-4) * I<double>(0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0), I<double>(-0X1.FFFFFFFFFFFE1P+1,-0X1.47AE147AE147BP-7) );
}


BOOST_AUTO_TEST_CASE(minimal_div_test)
{
    BOOST_CHECK_EQUAL( div(I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() / I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-1.0,1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-1.0,1.0) / I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::empty(), I<double>(-1.0,1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() / I<double>(-1.0,1.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::empty(), I<double>(0.1,1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() / I<double>(0.1,1.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::empty(), I<double>(-1.0,-0.1)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() / I<double>(-1.0,-0.1), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() / I<double>::entire(), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>::empty(), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::empty(), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::empty() / I<double>(0.0), I<double>::empty() );

    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-5.0, -3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-5.0, -3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(3.0, 5.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(3.0, 5.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-INF, -3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-INF, -3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(3.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(3.0,INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-3.0, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-3.0, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(0.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(0.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-INF, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-INF, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>(0.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>(0.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>::entire(), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>::entire() / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-5.0, -3.0)), I<double>(3.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-5.0, -3.0), I<double>(3.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(3.0, 5.0)), I<double>(-10.0,-3.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(3.0, 5.0), I<double>(-10.0,-3.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-INF, -3.0)), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-INF, -3.0), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(3.0,INF)), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(3.0,INF), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-3.0, 0.0)), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-3.0, 0.0), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(0.0, 3.0)), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(0.0, 3.0), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-INF, 0.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-INF, 0.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>(0.0, INF)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>(0.0, INF), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,-15.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,-15.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-5.0, -3.0)), I<double>(-5.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-5.0, -3.0), I<double>(-5.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(3.0, 5.0)), I<double>(-10.0,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(3.0, 5.0), I<double>(-10.0,5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-INF, -3.0)), I<double>(-5.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-INF, -3.0), I<double>(-5.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(3.0,INF)), I<double>(-10.0,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(3.0,INF), I<double>(-10.0,5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-3.0, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-3.0, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(0.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(0.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-INF, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-INF, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>(0.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>(0.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,15.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,15.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-5.0, -3.0)), I<double>(-10.0,-3.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-5.0, -3.0), I<double>(-10.0,-3.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(3.0, 5.0)), I<double>(3.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(3.0, 5.0), I<double>(3.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-INF, -3.0)), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-INF, -3.0), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(3.0,INF)), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(3.0,INF), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-3.0, 0.0)), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-3.0, 0.0), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(0.0, 3.0)), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(0.0, 3.0), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-INF, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-INF, 0.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>(0.0, INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>(0.0, INF), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,30.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,30.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-5.0, -3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-5.0, -3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(3.0, 5.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(3.0, 5.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-INF, -3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-INF, -3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(3.0,INF)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(3.0,INF), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-3.0, 0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-3.0, 0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-3.0, 3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-3.0, 3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(0.0, 3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(0.0, 3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-INF, 0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-INF, 0.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-INF, 3.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-INF, 3.0), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(-3.0, INF)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(-3.0, INF), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>(0.0, INF)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>(0.0, INF), I<double>(0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0), I<double>::entire()), I<double>(0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0) / I<double>::entire(), I<double>(0.0) );

    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-5.0, -3.0)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-5.0, -3.0), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(3.0, 5.0)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(3.0, 5.0), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-INF, -3.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-INF, -3.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(3.0,INF)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(3.0,INF), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-3.0, 0.0)), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-3.0, 0.0), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(0.0, 3.0)), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(0.0, 3.0), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-INF, 0.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-INF, 0.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>(0.0, INF)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>(0.0, INF), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-15.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,-15.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-5.0, -3.0)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-5.0, -3.0), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(3.0, 5.0)), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(3.0, 5.0), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-INF, -3.0)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-INF, -3.0), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(3.0,INF)), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(3.0,INF), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-3.0, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-3.0, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(0.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(0.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-INF, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-INF, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>(0.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>(0.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,15.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,15.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-5.0, -3.0)), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-5.0, -3.0), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(3.0, 5.0)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(3.0, 5.0), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-INF, -3.0)), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-INF, -3.0), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(3.0,INF)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(3.0,INF), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-3.0, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-3.0, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(0.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(0.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-INF, 0.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-INF, 0.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>(0.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>(0.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-15.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-15.0,INF) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-5.0, -3.0)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-5.0, -3.0), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(3.0, 5.0)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(3.0, 5.0), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-INF, -3.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-INF, -3.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(3.0,INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(3.0,INF), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-3.0, 0.0)), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-3.0, 0.0), I<double>(-INF,-5.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(0.0, 3.0)), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(0.0, 3.0), I<double>(5.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-INF, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-INF, 0.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>(0.0, INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>(0.0, INF), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(15.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(15.0,INF) / I<double>::entire(), I<double>::entire() );


    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-5.0, -3.0)), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-5.0, -3.0), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(3.0, 5.0)), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(3.0, 5.0), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-INF, -3.0)), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-INF, -3.0), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(3.0,INF)), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(3.0,INF), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-3.0, 0.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-3.0, 0.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(0.0, 3.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(0.0, 3.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-INF, 0.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-INF, 0.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>(0.0, INF)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>(0.0, INF), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-30.0,0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-30.0,0.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-5.0, -3.0)), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-5.0, -3.0), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(3.0, 5.0)), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(3.0, 5.0), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-INF, -3.0)), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-INF, -3.0), I<double>(-10.0,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(3.0,INF)), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(3.0,INF), I<double>(0.0,10.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-3.0, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-3.0, 0.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(0.0, 3.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(0.0, 3.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-INF, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-INF, 0.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>(0.0, INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>(0.0, INF), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,30.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,30.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-5.0, -3.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-5.0, -3.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(3.0, 5.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(3.0, 5.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-INF, -3.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-INF, -3.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(3.0,INF)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(3.0,INF), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-3.0, 0.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-3.0, 0.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-3.0, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-3.0, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(0.0, 3.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(0.0, 3.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-INF, 0.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-INF, 0.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>(0.0, INF)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>(0.0, INF), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(-INF,0.0) / I<double>::entire(), I<double>::entire() );

    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-5.0, -3.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-5.0, -3.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(3.0, 5.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(3.0, 5.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-INF, -3.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-INF, -3.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(3.0,INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(3.0,INF), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(0.0), I<double>::empty() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-3.0, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-3.0, 0.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-3.0, 3.0)), I<double>::entire()  );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-3.0, 3.0), I<double>::entire()  );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(0.0, 3.0)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(0.0, 3.0), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-INF, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-INF, 0.0), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-INF, 3.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-INF, 3.0), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(-3.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(-3.0, INF), I<double>::entire() );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>(0.0, INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>(0.0, INF), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( div(I<double>(0.0,INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( I<double>(0.0,INF) / I<double>::entire(), I<double>::entire() );



    BOOST_CHECK_EQUAL( div(I<double>(-2.0,-1.0), I<double>(-10.0, -3.0)), I<double>(0X1.9999999999999P-4,0X1.5555555555556P-1) );
    BOOST_CHECK_EQUAL( I<double>(-2.0,-1.0) / I<double>(-10.0, -3.0), I<double>(0X1.9999999999999P-4,0X1.5555555555556P-1) );
    BOOST_CHECK_EQUAL( div(I<double>(-2.0,-1.0), I<double>(0.0, 10.0)), I<double>(-INF,-0X1.9999999999999P-4) );
    BOOST_CHECK_EQUAL( I<double>(-2.0,-1.0) / I<double>(0.0, 10.0), I<double>(-INF,-0X1.9999999999999P-4) );
    BOOST_CHECK_EQUAL( div(I<double>(-1.0,2.0), I<double>(10.0,INF)), I<double>(-0X1.999999999999AP-4,0X1.999999999999AP-3) );
    BOOST_CHECK_EQUAL( I<double>(-1.0,2.0) / I<double>(10.0,INF), I<double>(-0X1.999999999999AP-4,0X1.999999999999AP-3) );
    BOOST_CHECK_EQUAL( div(I<double>(1.0,3.0), I<double>(-INF, -10.0)), I<double>(-0X1.3333333333334P-2,0.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,3.0) / I<double>(-INF, -10.0), I<double>(-0X1.3333333333334P-2,0.0) );
    BOOST_CHECK_EQUAL( div(I<double>(-INF,-1.0), I<double>(1.0, 3.0)), I<double>(-INF,-0X1.5555555555555P-2) );
    BOOST_CHECK_EQUAL( I<double>(-INF,-1.0) / I<double>(1.0, 3.0), I<double>(-INF,-0X1.5555555555555P-2) );
}

BOOST_AUTO_TEST_CASE(minimal_recip_test)
{
    BOOST_CHECK_EQUAL( recip(I<double>(-50.0, -10.0)), I<double>(-0X1.999999999999AP-4,-0X1.47AE147AE147AP-6) );
    BOOST_CHECK_EQUAL( recip(I<double>(10.0, 50.0)), I<double>(0X1.47AE147AE147AP-6,0X1.999999999999AP-4) );
    BOOST_CHECK_EQUAL( recip(I<double>(-INF, -10.0)), I<double>(-0X1.999999999999AP-4,0.0) );
    BOOST_CHECK_EQUAL( recip(I<double>(10.0,INF)), I<double>(0.0,0X1.999999999999AP-4) );
    BOOST_CHECK_EQUAL( recip(I<double>(0.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( recip(I<double>(-10.0, 0.0)), I<double>(-INF,-0X1.9999999999999P-4) );
    BOOST_CHECK_EQUAL( recip(I<double>(-10.0, 10.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( recip(I<double>(0.0, 10.0)), I<double>(0X1.9999999999999P-4,INF) );
    BOOST_CHECK_EQUAL( recip(I<double>(-INF, 0.0)), I<double>(-INF,0.0) );
    BOOST_CHECK_EQUAL( recip(I<double>(-INF, 10.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( recip(I<double>(-10.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( recip(I<double>(0.0, INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( recip(I<double>::entire()), I<double>::entire() );
}

BOOST_AUTO_TEST_CASE(minimal_sqr_test)
{
    BOOST_CHECK_EQUAL( sqr(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( sqr(I<double>::entire()), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( sqr(I<double>(-INF,-MIN)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( sqr(I<double>(-1.0,1.0)), I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( sqr(I<double>(-5.0,3.0)), I<double>(0.0,25.0) );
    BOOST_CHECK_EQUAL( sqr(I<double>(0X1.999999999999AP-4)), I<double>(0X1.47AE147AE147BP-7,0X1.47AE147AE147CP-7) );
    BOOST_CHECK_EQUAL( sqr(I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.999999999999AP-4)), I<double>(0.0,0X1.FFFFFFFFFFFE1P+1) );
    BOOST_CHECK_EQUAL( sqr(I<double>(-0X1.FFFFFFFFFFFFP+0)), I<double>(0X1.FFFFFFFFFFFEP+1,0X1.FFFFFFFFFFFE1P+1) );
}

BOOST_AUTO_TEST_CASE(minimal_sqrt_test)
{
    BOOST_CHECK_EQUAL( sqrt(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( sqrt(I<double>::entire()), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( sqrt(I<double>(-INF,-MIN)), I<double>::empty() );
    BOOST_CHECK_EQUAL( sqrt(I<double>(-1.0,1.0)), I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( sqrt(I<double>(-5.0,25.0)), I<double>(0.0,5.0) );
    BOOST_CHECK_EQUAL( sqrt(I<double>(-5.0,INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( sqrt(I<double>(0X1.999999999999AP-4)), I<double>(0X1.43D136248490FP-2,0X1.43D136248491P-2) );
    BOOST_CHECK_EQUAL( sqrt(I<double>(-0X1.FFFFFFFFFFFFP+0,0X1.999999999999AP-4)), I<double>(0.0,0X1.43D136248491P-2) );
    BOOST_CHECK_EQUAL( sqrt(I<double>(0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0)), I<double>(0X1.43D136248490FP-2,0X1.6A09E667F3BC7P+0) );
}

BOOST_AUTO_TEST_CASE(minimal_fma_test)
{
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,1.0), I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(-1.0,1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::entire(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(0.0), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    //min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,2.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-1.0, 10.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-2.0,2.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    //end min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>::entire(), I<double>::empty()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(0.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, -1.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, 3.0), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, INF), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>::entire(), I<double>::empty()), I<double>::empty() );



    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::empty(), I<double>(-INF,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,1.0), I<double>::empty(), I<double>(-INF,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(-1.0,1.0), I<double>(-INF,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::entire(), I<double>(-INF,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::empty(), I<double>(-INF,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::empty(), I<double>(-INF,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(0.0), I<double>(-INF,2.0)), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>(-INF,7.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,11.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::entire(), I<double>(-INF,2.0)), I<double>(-INF,2.0) );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>(-INF,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>(-INF,7.0) );
    //min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,2.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-1.0, 10.0), I<double>(-INF,2.0)), I<double>(-INF,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-2.0,2.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,12.0) );
    //end min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(0.0), I<double>(-INF,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, -1.0), I<double>(-INF,2.0)), I<double>(-INF,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, 3.0), I<double>(-INF,2.0)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, -1.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, 3.0), I<double>(-INF,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, INF), I<double>(-INF,2.0)), I<double>(-INF,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, INF), I<double>(-INF,2.0)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>::entire(), I<double>(-INF,2.0)), I<double>::entire() );



    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::empty(), I<double>(-2.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,1.0), I<double>::empty(), I<double>(-2.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(-1.0,1.0), I<double>(-2.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::empty(), I<double>(-2.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::empty(), I<double>(-2.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(0.0), I<double>(-2.0,2.0)), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(-INF,7.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(-17.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-INF,11.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>(-INF,-1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::entire(), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(-27.0,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>(-27.0,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-1.0,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>(-INF,1.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>(-INF,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>(-27.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(-27.0,7.0) );
    //min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>(-27.0,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,2.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>(-32.0,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-1.0, 10.0), I<double>(-2.0,2.0)), I<double>(-12.0,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-2.0,2.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>(-12.0,12.0) );
    //end min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-5.0,17.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(0.0), I<double>(-2.0,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, -1.0), I<double>(-2.0,2.0)), I<double>(3.0,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, 3.0), I<double>(-2.0,2.0)), I<double>(-32.0,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, 3.0), I<double>(-2.0,2.0)), I<double>(-32.0,-3.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, -1.0), I<double>(-2.0,2.0)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, 3.0), I<double>(-2.0,2.0)), I<double>(-32.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, INF), I<double>(-2.0,2.0)), I<double>(-INF,52.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, INF), I<double>(-2.0,2.0)), I<double>(-INF,-3.0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>::entire(), I<double>(-2.0,2.0)), I<double>::entire() );



    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::empty(), I<double>(-2.0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,1.0), I<double>::empty(), I<double>(-2.0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(-1.0,1.0), I<double>(-2.0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::entire(), I<double>(-2.0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::empty(), I<double>(-2.0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::empty(), I<double>(-2.0,INF)), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(0.0), I<double>(-2.0,INF)), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>(-17.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::entire(), I<double>(-2.0,INF)), I<double>(-2.0,INF) );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>(-27.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>(-27.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>(-27.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>(-27.0,INF) );
    //min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>(-27.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,2.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>(-32.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-1.0, 10.0), I<double>(-2.0,INF)), I<double>(-12.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-2.0,2.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>(-12.0,INF) );
    //end min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>(-5.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(0.0), I<double>(-2.0,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, -1.0), I<double>(-2.0,INF)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, 3.0), I<double>(-2.0,INF)), I<double>(-32.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, 3.0), I<double>(-2.0,INF)), I<double>(-32.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, -1.0), I<double>(-2.0,INF)), I<double>(3.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, 3.0), I<double>(-2.0,INF)), I<double>(-32.0,INF) );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, INF), I<double>(-2.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>::entire(), I<double>(-2.0,INF)), I<double>::entire() );



    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,1.0), I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(-1.0,1.0), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>::entire(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::empty(), I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( fma(I<double>::empty(), I<double>(0.0), I<double>::entire()), I<double>::empty() );

    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>::entire(), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,INF), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,INF), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,3.0), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-INF,-3.0), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(0.0), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(1.0,5.0), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    //min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,2.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-1.0, 10.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-2.0,2.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    //end min max
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-1.0,5.0), I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(0.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-INF, 3.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(-5.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>(1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( fma(I<double>(-10.0,-5.0), I<double>::entire(), I<double>::entire()), I<double>::entire() );


    BOOST_CHECK_EQUAL( fma(I<double>(0.1,0.5), I<double>(-5.0, 3.0), I<double>(-0.1,0.1)), I<double>(-0X1.4CCCCCCCCCCCDP+1,0X1.999999999999AP+0) );
    BOOST_CHECK_EQUAL( fma(I<double>(-0.5,0.2), I<double>(-5.0, 3.0), I<double>(-0.1,0.1)), I<double>(-0X1.999999999999AP+0,0X1.4CCCCCCCCCCCDP+1) );
    BOOST_CHECK_EQUAL( fma(I<double>(-0.5,-0.1), I<double>(2.0, 3.0), I<double>(-0.1,0.1)), I<double>(-0X1.999999999999AP+0,-0X1.999999999999AP-4) );
    BOOST_CHECK_EQUAL( fma(I<double>(-0.5,-0.1), I<double>(-INF, 3.0), I<double>(-0.1,0.1)), I<double>(-0X1.999999999999AP+0,INF) );
}

//BOOST_AUTO_TEST_CASE(minimal_interval_case_test)
//{
//TODO noch notwendig?
//    BOOST_CHECK(false);
//}


BOOST_AUTO_TEST_CASE(minimal_pown_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_pow_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_exp_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_exp2_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_exp10_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_log_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_log2_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_log10_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_sin_test)
{
    BOOST_CHECK_EQUAL( sin(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( sin(I<double>::entire()), I<double>(-1.0,1.0) );

    BOOST_CHECK_EQUAL( sin(I<double>(0.0, 3.14)), I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( sin(I<double>(-3.14, 0.0)), I<double>(-1.0,0.0) );

    BOOST_CHECK_EQUAL( sin(I<double>(0.0, 6.29)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( sin(I<double>(-6.29, 0.0)), I<double>(-1.0,1.0) );

    BOOST_CHECK_EQUAL( sin(I<double>(0.0, 6.28)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( sin(I<double>(-6.28, 0.0)), I<double>(-1.0,1.0) );

    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_cos_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_tan_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_asin_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_acos_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_atan_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_atan2_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_sinh_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_cosh_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_tanh_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_asinh_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_acosh_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_atanh_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_sign_test)
{
    BOOST_CHECK_EQUAL( sign(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( sign(I<double>(1.0,2.0)), I<double>(1.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(-1.0,2.0)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(-1.0,0.0)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(0.0,2.0)), I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(-5.0,-2.0)), I<double>(-1.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(-0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( sign(I<double>(-0.0,0.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( sign(I<double>::entire()), I<double>(-1.0,1.0) );
}

BOOST_AUTO_TEST_CASE(minimal_ceil_test)
{
    BOOST_CHECK_EQUAL( ceil(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( ceil(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( ceil(I<double>(1.1,2.0)), I<double>(2.0) );
    BOOST_CHECK_EQUAL( ceil(I<double>(-1.1,2.0)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( ceil(I<double>(-1.1,-0.4)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( ceil(I<double>(-1.9,2.2)), I<double>(-1.0,3.0) );
    BOOST_CHECK_EQUAL( ceil(I<double>(-1.0,2.2)), I<double>(-1.0,3.0) );
    BOOST_CHECK_EQUAL( ceil(I<double>(-1.5,INF)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( ceil(I<double>(-INF,2.2)), I<double>(-INF,3.0) );
}

BOOST_AUTO_TEST_CASE(minimal_floor_test)
{
    BOOST_CHECK_EQUAL( floor(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( floor(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( floor(I<double>(1.1,2.0)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( floor(I<double>(-1.1,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( floor(I<double>(-1.1,-0.4)), I<double>(-2.0,-1.0) );
    BOOST_CHECK_EQUAL( floor(I<double>(-1.9,2.2)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( floor(I<double>(-1.0,2.2)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( floor(I<double>(-1.5,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( floor(I<double>(-INF,2.2)), I<double>(-INF,2.0) );
}

BOOST_AUTO_TEST_CASE(minimal_trunc_test)
{
    BOOST_CHECK_EQUAL( trunc(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( trunc(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( trunc(I<double>(1.1,2.1)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( trunc(I<double>(-1.1,2.0)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( trunc(I<double>(-1.1,-0.4)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( trunc(I<double>(-1.9,2.2)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( trunc(I<double>(-1.0,2.2)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( trunc(I<double>(-1.5,INF)), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( trunc(I<double>(-INF,2.2)), I<double>(-INF,2.0) );
}

BOOST_AUTO_TEST_CASE(minimal_round_ties_to_even_test)
{
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(1.1,2.1)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.1,2.0)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.1,-0.4)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.9,2.2)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.0,2.2)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(1.5,2.1)), I<double>(2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.5,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.1,-0.5)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.9,2.5)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.5,2.5)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-1.5,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( round_ties_to_even(I<double>(-INF,2.2)), I<double>(-INF,2.0) );
}

BOOST_AUTO_TEST_CASE(minimal_round_ties_to_away_test)
{
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(1.1,2.1)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.1,2.0)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.1,-0.4)), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.9,2.2)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.0,2.2)), I<double>(-1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(0.5,2.1)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-2.5,2.0)), I<double>(-3.0,2.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.1,-0.5)), I<double>(-1.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.9,2.5)), I<double>(-2.0,3.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.5,2.5)), I<double>(-2.0,3.0) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-1.5,INF)), I<double>(-2.0,INF) );
    BOOST_CHECK_EQUAL( round_ties_to_away(I<double>(-INF,2.2)), I<double>(-INF,2.0) );
}

BOOST_AUTO_TEST_CASE(minimal_abs_test)
{
    BOOST_CHECK_EQUAL( abs(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( abs(I<double>::entire()), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( abs(I<double>(1.1,2.1)), I<double>(1.1,2.1) );
    BOOST_CHECK_EQUAL( abs(I<double>(-1.1,2.0)), I<double>(0.0,2.0) );
    BOOST_CHECK_EQUAL( abs(I<double>(-1.1,-0.4)), I<double>(0.4,1.1) );
    BOOST_CHECK_EQUAL( abs(I<double>(-1.9,0.2)), I<double>(0.0,1.9) );
    BOOST_CHECK_EQUAL( abs(I<double>(-1.5,INF)), I<double>(0.0,INF) );
    BOOST_CHECK_EQUAL( abs(I<double>(-INF,-2.2)), I<double>(2.2,INF) );
}

BOOST_AUTO_TEST_CASE(minimal_min_test)
{
//TODO ist das so gedacht?
    BOOST_CHECK_EQUAL( min(I<double>::empty(),I<double>(1.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( min(I<double>(1.0,2.0),I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( min(I<double>::empty(),I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( min(I<double>::entire(),I<double>(1.0,2.0)), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( min(I<double>(1.0,2.0),I<double>::entire()), I<double>(-INF,2.0) );
    BOOST_CHECK_EQUAL( min(I<double>::entire(),I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( min(I<double>::empty(),I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( min(I<double>(1.0,5.0),I<double>(2.0,4.0)), I<double>(1.0,4.0) );
    BOOST_CHECK_EQUAL( min(I<double>(1.0,5.0),I<double>(2.0,8.0)), I<double>(1.0,5.0) );
    BOOST_CHECK_EQUAL( min(I<double>(1.0,5.0),I<double>::entire()), I<double>(-INF,5.0) );
    BOOST_CHECK_EQUAL( min(I<double>(-7.0,-5.0),I<double>(2.0,4.0)), I<double>(-7.0,-5.0) );
}

BOOST_AUTO_TEST_CASE(minimal_max_test)
{
//TODO ist das so gedacht?
    BOOST_CHECK_EQUAL( max(I<double>::empty(),I<double>(1.0,2.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( max(I<double>(1.0,2.0),I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( max(I<double>::empty(),I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( max(I<double>::entire(),I<double>(1.0,2.0)), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( max(I<double>(1.0,2.0),I<double>::entire()), I<double>(1.0,INF) );
    BOOST_CHECK_EQUAL( max(I<double>::entire(),I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( max(I<double>::empty(),I<double>::entire()), I<double>::empty() );
    BOOST_CHECK_EQUAL( max(I<double>(1.0,5.0),I<double>(2.0,4.0)), I<double>(2.0,5.0) );
    BOOST_CHECK_EQUAL( max(I<double>(1.0,5.0),I<double>(2.0,8.0)), I<double>(2.0,8.0) );
    BOOST_CHECK_EQUAL( max(I<double>(-1.0,5.0),I<double>::entire()), I<double>(-1.0,INF) );
    BOOST_CHECK_EQUAL( max(I<double>(-7.0,-5.0),I<double>(2.0,4.0)), I<double>(2.0,4.0) );
}
