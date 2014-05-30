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

#define BOOST_TEST_MODULE "Boolean functions on intervals [inf-sup-interval, mpfr_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include <limits>
#include "p1788/p1788.hpp"

template<typename T>
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes>;

template<typename T>
using I = p1788::infsup::interval<T, flavor>;


BOOST_AUTO_TEST_CASE(minimal_is_empty_test)
{
    BOOST_CHECK( is_empty(I<double>::empty()) );
    BOOST_CHECK( !is_empty(I<double>::entire()) );
    BOOST_CHECK( !is_empty(I<double>(1.0,2.0)) );
    BOOST_CHECK( !is_empty(I<double>(-1.0,2.0)) );
    BOOST_CHECK( !is_empty(I<double>(-3.0,-2.0)) );
    BOOST_CHECK( !is_empty(I<double>(-std::numeric_limits<double>::infinity(),2.0)) );
    BOOST_CHECK( !is_empty(I<double>(0.0,std::numeric_limits<double>::infinity())) );
}


BOOST_AUTO_TEST_CASE(minimal_is_entire_test)
{
    BOOST_CHECK( !is_entire(I<double>::empty()) );
    BOOST_CHECK( is_entire(I<double>::entire()) );
    BOOST_CHECK( !is_entire(I<double>(1.0,2.0)) );
    BOOST_CHECK( !is_entire(I<double>(-1.0,2.0)) );
    BOOST_CHECK( !is_entire(I<double>(-3.0,-2.0)) );
    BOOST_CHECK( !is_entire(I<double>(-std::numeric_limits<double>::infinity(),2.0)) );
    BOOST_CHECK( !is_entire(I<double>(0.0,std::numeric_limits<double>::infinity())) );
}

BOOST_AUTO_TEST_CASE(minimal_is_equal_test)
{
    BOOST_CHECK( is_equal(I<double>(1.0,2.0), I<double>(1.0,2.0)) );
    BOOST_CHECK( I<double>(1.0,2.0) == I<double>(1.0,2.0) );
    BOOST_CHECK( I<double>(1.0,2.4) != I<double>(1.0,2.0) );

    BOOST_CHECK( is_equal(I<double>::empty(), I<double>::empty()) );
    BOOST_CHECK( I<double>::empty() == I<double>::empty() );
    BOOST_CHECK( I<double>::empty() != I<double>(1.0,2.0) );

    BOOST_CHECK( is_equal(I<double>::entire(), I<double>::entire()) );
    BOOST_CHECK( I<double>::entire() == I<double>::entire() );
    BOOST_CHECK( I<double>(1.0,2.4) != I<double>::entire() );

    BOOST_CHECK( is_equal(I<double>(1.0,std::numeric_limits<double>::infinity()), I<double>(1.0,std::numeric_limits<double>::infinity())) );
    BOOST_CHECK( I<double>(1.0,std::numeric_limits<double>::infinity()) == I<double>(1.0,std::numeric_limits<double>::infinity()) );
    BOOST_CHECK( I<double>(1.0,2.4) != I<double>(1.0,std::numeric_limits<double>::infinity()) );

    BOOST_CHECK( is_equal(I<double>(-std::numeric_limits<double>::infinity(),2.0), I<double>(-std::numeric_limits<double>::infinity(),2.0)) );
    BOOST_CHECK( I<double>(-std::numeric_limits<double>::infinity(),2.0) == I<double>(-std::numeric_limits<double>::infinity(),2.0) );
    BOOST_CHECK( I<double>(-std::numeric_limits<double>::infinity(),2.4) != I<double>(-std::numeric_limits<double>::infinity(),2.0) );

    BOOST_CHECK( I<double>(-0.0,2.0) == I<double>(0.0,2.0) );
}


BOOST_AUTO_TEST_CASE(minimal_subset_test)
{
    BOOST_CHECK( subset(I<double>::empty(), I<double>::empty()) );
    BOOST_CHECK( subset(I<double>::empty(), I<double>(0.0,4.0)) );
    BOOST_CHECK( subset(I<double>::empty(), I<double>(-0.1,1.0)) );
    BOOST_CHECK( subset(I<double>::empty(), I<double>::entire()) );

    BOOST_CHECK( !subset(I<double>(0.0,4.0), I<double>::empty()) );
    BOOST_CHECK( !subset(I<double>(-0.1,1.0), I<double>::empty()) );
    BOOST_CHECK( !subset(I<double>::entire(), I<double>::empty()) );

    BOOST_CHECK( subset(I<double>(0.0,4.0), I<double>::entire()) );
    BOOST_CHECK( subset(I<double>(-0.1,1.0), I<double>::entire()) );
    BOOST_CHECK( subset(I<double>::entire(), I<double>::entire()) );

    BOOST_CHECK( subset(I<double>(1.0,2.0), I<double>(0.0,4.0)) );
    BOOST_CHECK( subset(I<double>(0.1,0.2), I<double>(0.0,4.0)) );
    BOOST_CHECK( subset(I<double>(-0.1), I<double>(-4.0, 3.4)) );
}


BOOST_AUTO_TEST_CASE(minimal_superset_test)
{
    BOOST_CHECK( superset(I<double>::empty(), I<double>::empty()) );
    BOOST_CHECK( superset(I<double>(0.0,4.0), I<double>::empty()) );
    BOOST_CHECK( superset(I<double>(-0.1,1.0), I<double>::empty()) );
    BOOST_CHECK( superset(I<double>::entire(), I<double>::empty()) );

    BOOST_CHECK( !superset(I<double>::empty(), I<double>(0.0,4.0)) );
    BOOST_CHECK( !superset(I<double>::empty(), I<double>(-0.1,1.0)) );
    BOOST_CHECK( !superset(I<double>::empty(), I<double>::entire()) );

    BOOST_CHECK( superset(I<double>::entire(), I<double>(0.0,4.0)) );
    BOOST_CHECK( superset(I<double>::entire(), I<double>(-0.1,1.0)) );
    BOOST_CHECK( superset(I<double>::entire(), I<double>::entire()) );

    BOOST_CHECK( superset(I<double>(0.0,4.0), I<double>(1.0,2.0)) );
    BOOST_CHECK( superset(I<double>(0.0,4.0), I<double>(0.1,0.2)) );
    BOOST_CHECK( superset(I<double>(-4.0, 3.4), I<double>(-0.1)) );
}


BOOST_AUTO_TEST_CASE(minimal_less_test)
{
    BOOST_CHECK( less(I<double>::empty(), I<double>::empty()) );
    BOOST_CHECK( !less(I<double>(1.0,2.0), I<double>::empty()) );
    BOOST_CHECK( !less(I<double>::empty(), I<double>(1.0,2.0)) );

    BOOST_CHECK( less(I<double>::entire(), I<double>::entire()) );
    BOOST_CHECK( !less(I<double>(1.0,2.0), I<double>::entire()) );
    BOOST_CHECK( !less(I<double>::entire(), I<double>(1.0,2.0)) );

    BOOST_CHECK( less(I<double>(1.0,2.0), I<double>(1.0,2.0)) );
    BOOST_CHECK( less(I<double>(1.0,2.0), I<double>(3.0,4.0)) );
    BOOST_CHECK( less(I<double>(1.0,3.5), I<double>(3.0,4.0)) );
    BOOST_CHECK( less(I<double>(1.0,4.0), I<double>(3.0,4.0)) );

    BOOST_CHECK( less(I<double>(-2.0,-1.0), I<double>(-2.0,-1.0)) );
    BOOST_CHECK( less(I<double>(-3.0,-1.5), I<double>(-2.0,-1.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_greater_test)
{
    BOOST_CHECK( greater(I<double>::empty(), I<double>::empty()) );
    BOOST_CHECK( !greater(I<double>(1.0,2.0), I<double>::empty()) );
    BOOST_CHECK( !greater(I<double>::empty(), I<double>(1.0,2.0)) );

    BOOST_CHECK( greater(I<double>::entire(), I<double>::entire()) );
    BOOST_CHECK( !greater(I<double>(1.0,2.0), I<double>::entire()) );
    BOOST_CHECK( !greater(I<double>::entire(), I<double>(1.0,2.0)) );

    BOOST_CHECK( greater(I<double>(1.0,2.0), I<double>(1.0,2.0)) );
    BOOST_CHECK( greater(I<double>(3.0,4.0), I<double>(1.0,2.0)) );
    BOOST_CHECK( greater(I<double>(3.0,4.0), I<double>(1.0,3.5)) );
    BOOST_CHECK( greater(I<double>(3.0,4.0), I<double>(1.0,4.0)) );

    BOOST_CHECK( greater(I<double>(-2.0,-1.0), I<double>(-2.0,-1.0)) );
    BOOST_CHECK( greater( I<double>(-2.0,-1.0), I<double>(-3.0,-1.5)) );
}


BOOST_AUTO_TEST_CASE(minimal_precedes_test)
{
    BOOST_CHECK( precedes(I<double>::empty(), I<double>(3.0,4.0)) );
    BOOST_CHECK( precedes(I<double>(3.0,4.0), I<double>::empty()) );
    BOOST_CHECK( precedes(I<double>::empty(), I<double>::empty()) );


    BOOST_CHECK( !precedes(I<double>(1.0,2.0), I<double>::entire()) );
    BOOST_CHECK( !precedes(I<double>::entire(), I<double>(1.0,2.0)) );
    BOOST_CHECK( !precedes(I<double>::entire(), I<double>::entire()) );

    BOOST_CHECK( precedes(I<double>(1.0,2.0), I<double>(3.0,4.0)) );
    BOOST_CHECK( precedes(I<double>(1.0,3.0), I<double>(3.0,4.0)) );
    BOOST_CHECK( precedes(I<double>(-3.0, -1.0), I<double>(-1.0,0.0)) );

    BOOST_CHECK( !precedes(I<double>(1.0,3.5), I<double>(3.0,4.0)) );
    BOOST_CHECK( !precedes(I<double>(1.0,4.0), I<double>(3.0,4.0)) );
    BOOST_CHECK( !precedes(I<double>(-3.0, -0.1), I<double>(-1.0,0.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_succeeds_test)
{
    BOOST_CHECK( succeeds(I<double>::empty(), I<double>(3.0,4.0)) );
    BOOST_CHECK( succeeds(I<double>(3.0,4.0), I<double>::empty()) );
    BOOST_CHECK( succeeds(I<double>::empty(), I<double>::empty()) );


    BOOST_CHECK( !succeeds(I<double>(1.0,2.0), I<double>::entire()) );
    BOOST_CHECK( !succeeds(I<double>::entire(), I<double>(1.0,2.0)) );
    BOOST_CHECK( !succeeds(I<double>::entire(), I<double>::entire()) );

    BOOST_CHECK( succeeds(I<double>(3.0,4.0), I<double>(1.0,2.0)) );
    BOOST_CHECK( succeeds(I<double>(3.0,4.0), I<double>(1.0,3.0)) );
    BOOST_CHECK( succeeds(I<double>(-1.0,0.0), I<double>(-3.0, -1.0)) );

    BOOST_CHECK( !succeeds(I<double>(3.0,4.0), I<double>(1.0,3.5)) );
    BOOST_CHECK( !succeeds(I<double>(3.0,4.0), I<double>(1.0,4.0)) );
    BOOST_CHECK( !succeeds(I<double>(-1.0,0.0), I<double>(-3.0, -0.1)) );
}


BOOST_AUTO_TEST_CASE(minimal_is_interior_test)
{
    BOOST_CHECK( is_interior(I<double>::empty(), I<double>::empty()) );
    BOOST_CHECK( is_interior(I<double>::empty(), I<double>(0.0,4.0)) );
    BOOST_CHECK( !is_interior(I<double>(0.0,4.0), I<double>::empty()) );

    BOOST_CHECK( is_interior(I<double>::entire(), I<double>::entire()) );
    BOOST_CHECK( is_interior(I<double>(0.0,4.0), I<double>::entire()) );
    BOOST_CHECK( is_interior(I<double>::empty(), I<double>::entire()) );
    BOOST_CHECK( !is_interior(I<double>::entire(), I<double>(0.0,4.0)) );

    BOOST_CHECK( !is_interior(I<double>(0.0,4.0), I<double>(0.0,4.0)) );
    BOOST_CHECK( is_interior(I<double>(1.0,2.0), I<double>(0.0,4.0)) );
    BOOST_CHECK( !is_interior(I<double>(-2.0,2.0), I<double>(-2.0,4.0)) );

    BOOST_CHECK( !is_interior(I<double>(0.0,4.4), I<double>(0.0,4.0)) );
    BOOST_CHECK( !is_interior(I<double>(-1.0), I<double>(0.0,4.0)) );
    BOOST_CHECK( !is_interior(I<double>(2.0,2.0), I<double>(-2.0,-1.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_contains_interior_test)
{
    BOOST_CHECK( contains_interior(I<double>::empty(), I<double>::empty()) );
    BOOST_CHECK( contains_interior(I<double>(0.0,4.0), I<double>::empty()) );
    BOOST_CHECK( !contains_interior(I<double>::empty(), I<double>(0.0,4.0)) );

    BOOST_CHECK( contains_interior(I<double>::entire(), I<double>::entire()) );
    BOOST_CHECK( contains_interior(I<double>::entire(), I<double>(0.0,4.0)) );
    BOOST_CHECK( contains_interior(I<double>::entire(), I<double>::empty()) );
    BOOST_CHECK( !contains_interior(I<double>(0.0,4.0), I<double>::entire()) );

    BOOST_CHECK( !contains_interior(I<double>(0.0,4.0), I<double>(0.0,4.0)) );
    BOOST_CHECK( contains_interior(I<double>(0.0,4.0), I<double>(1.0,2.0)) );
    BOOST_CHECK( !contains_interior(I<double>(-2.0,4.0), I<double>(-2.0,2.0)) );

    BOOST_CHECK( !contains_interior(I<double>(0.0,4.0), I<double>(0.0,4.4)) );
    BOOST_CHECK( !contains_interior(I<double>(0.0,4.0), I<double>(-1.0)) );
    BOOST_CHECK( !contains_interior(I<double>(-2.0,-1.0), I<double>(2.0,2.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_strictly_less_test)
{
    BOOST_CHECK( strictly_less(I<double>::empty(), I<double>::empty()) );
    BOOST_CHECK( !strictly_less(I<double>(1.0,2.0), I<double>::empty()) );
    BOOST_CHECK( !strictly_less(I<double>::empty(), I<double>(1.0,2.0)) );

    BOOST_CHECK( strictly_less(I<double>::entire(), I<double>::entire()) );
    BOOST_CHECK( !strictly_less(I<double>(1.0,2.0), I<double>::entire()) );
    BOOST_CHECK( !strictly_less(I<double>::entire(), I<double>(1.0,2.0)) );

    BOOST_CHECK( !strictly_less(I<double>(1.0,2.0), I<double>(1.0,2.0)) );
    BOOST_CHECK( strictly_less(I<double>(1.0,2.0), I<double>(3.0,4.0)) );
    BOOST_CHECK( strictly_less(I<double>(1.0,3.5), I<double>(3.0,4.0)) );
    BOOST_CHECK( !strictly_less(I<double>(1.0,4.0), I<double>(3.0,4.0)) );

    BOOST_CHECK( !strictly_less(I<double>(-2.0,-1.0), I<double>(-2.0,-1.0)) );
    BOOST_CHECK( strictly_less(I<double>(-3.0,-1.5), I<double>(-2.0,-1.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_strictly_greater_test)
{
    BOOST_CHECK( strictly_greater(I<double>::empty(), I<double>::empty()) );
    BOOST_CHECK( !strictly_greater(I<double>(1.0,2.0), I<double>::empty()) );
    BOOST_CHECK( !strictly_greater(I<double>::empty(), I<double>(1.0,2.0)) );

    BOOST_CHECK( strictly_greater(I<double>::entire(), I<double>::entire()) );
    BOOST_CHECK( !strictly_greater(I<double>(1.0,2.0), I<double>::entire()) );
    BOOST_CHECK( !strictly_greater(I<double>::entire(), I<double>(1.0,2.0)) );

    BOOST_CHECK( !strictly_greater(I<double>(1.0,2.0), I<double>(1.0,2.0)) );
    BOOST_CHECK( strictly_greater(I<double>(3.0,4.0), I<double>(1.0,2.0)) );
    BOOST_CHECK( strictly_greater(I<double>(3.0,4.0), I<double>(1.0,3.5)) );
    BOOST_CHECK( !strictly_greater(I<double>(3.0,4.0), I<double>(1.0,4.0)) );

    BOOST_CHECK( !strictly_greater(I<double>(-2.0,-1.0), I<double>(-2.0,-1.0)) );
    BOOST_CHECK( strictly_greater( I<double>(-2.0,-1.0), I<double>(-3.0,-1.5)) );
}


BOOST_AUTO_TEST_CASE(minimal_strictly_precedes_test)
{
    BOOST_CHECK( strictly_precedes(I<double>::empty(), I<double>(3.0,4.0)) );
    BOOST_CHECK( strictly_precedes(I<double>(3.0,4.0), I<double>::empty()) );
    BOOST_CHECK( strictly_precedes(I<double>::empty(), I<double>::empty()) );


    BOOST_CHECK( !strictly_precedes(I<double>(1.0,2.0), I<double>::entire()) );
    BOOST_CHECK( !strictly_precedes(I<double>::entire(), I<double>(1.0,2.0)) );
    BOOST_CHECK( !strictly_precedes(I<double>::entire(), I<double>::entire()) );

    BOOST_CHECK( strictly_precedes(I<double>(1.0,2.0), I<double>(3.0,4.0)) );
    BOOST_CHECK( !strictly_precedes(I<double>(1.0,3.0), I<double>(3.0,4.0)) );
    BOOST_CHECK( !strictly_precedes(I<double>(-3.0, -1.0), I<double>(-1.0,0.0)) );

    BOOST_CHECK( !strictly_precedes(I<double>(1.0,3.5), I<double>(3.0,4.0)) );
    BOOST_CHECK( !strictly_precedes(I<double>(1.0,4.0), I<double>(3.0,4.0)) );
    BOOST_CHECK( !strictly_precedes(I<double>(-3.0, -0.1), I<double>(-1.0,0.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_strictly_succeeds_test)
{
    BOOST_CHECK( strictly_succeeds(I<double>::empty(), I<double>(3.0,4.0)) );
    BOOST_CHECK( strictly_succeeds(I<double>(3.0,4.0), I<double>::empty()) );
    BOOST_CHECK( strictly_succeeds(I<double>::empty(), I<double>::empty()) );


    BOOST_CHECK( !strictly_succeeds(I<double>(1.0,2.0), I<double>::entire()) );
    BOOST_CHECK( !strictly_succeeds(I<double>::entire(), I<double>(1.0,2.0)) );
    BOOST_CHECK( !strictly_succeeds(I<double>::entire(), I<double>::entire()) );

    BOOST_CHECK( strictly_succeeds(I<double>(3.0,4.0), I<double>(1.0,2.0)) );
    BOOST_CHECK( !strictly_succeeds(I<double>(3.0,4.0), I<double>(1.0,3.0)) );
    BOOST_CHECK( !strictly_succeeds(I<double>(-1.0,0.0), I<double>(-3.0, -1.0)) );

    BOOST_CHECK( !strictly_succeeds(I<double>(3.0,4.0), I<double>(1.0,3.5)) );
    BOOST_CHECK( !strictly_succeeds(I<double>(3.0,4.0), I<double>(1.0,4.0)) );
    BOOST_CHECK( !strictly_succeeds(I<double>(-1.0,0.0), I<double>(-3.0, -0.1)) );
}

BOOST_AUTO_TEST_CASE(minimal_are_disjoint_test)
{
    BOOST_CHECK( are_disjoint(I<double>::empty(), I<double>(3.0,4.0)) );
    BOOST_CHECK( are_disjoint(I<double>(3.0,4.0), I<double>::empty()) );
    BOOST_CHECK( are_disjoint(I<double>::empty(), I<double>::empty()) );

    BOOST_CHECK( are_disjoint(I<double>(3.0,4.0), I<double>(1.0,2.0)) );

    BOOST_CHECK( !are_disjoint(I<double>(3.0,4.0), I<double>(1.0,7.0)) );
    BOOST_CHECK( !are_disjoint(I<double>(3.0,4.0), I<double>::entire()) );
    BOOST_CHECK( !are_disjoint(I<double>::entire(), I<double>(1.0,7.0)) );
    BOOST_CHECK( !are_disjoint(I<double>::entire(), I<double>::entire()) );
}
