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


#include "p1788/p1788.hpp"

template<typename T>
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes>;

template<typename T>
using I = p1788::infsup::interval<T, flavor>;


BOOST_AUTO_TEST_CASE(minimal_is_empty_test)
{
    BOOST_CHECK_EQUAL( is_empty(I<double>::empty()), true );
    BOOST_CHECK_EQUAL( is_empty(I<double>::entire()), false );
}


BOOST_AUTO_TEST_CASE(minimal_is_entire_test)
{
    BOOST_CHECK_EQUAL( is_entire(I<double>::empty()), false );
    BOOST_CHECK_EQUAL( is_entire(I<double>::entire()), true );
}


BOOST_AUTO_TEST_CASE(minimal_is_equal_test)
{
    BOOST_CHECK_EQUAL( is_equal(I<double>(1.0,2.0), I<double>(1.0,2.0)), true);
//    BOOST_CHECK_EQUAL( is_equal(I<double>(1.0,2.0), I<float>(1.0,2.0)), true);
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) == I<double>(1.0,2.0), true);
//    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) == I<float>(1.0,2.0), true);
    BOOST_CHECK_EQUAL( I<double>(1.0,2.4) != I<double>(1.0,2.0), true);
//    BOOST_CHECK_EQUAL( I<double>(1.0,2.4) != I<float>(1.0,2.0), true);
}


BOOST_AUTO_TEST_CASE(minimal_contained_in_test)
{
    BOOST_CHECK_EQUAL( contained_in(I<double>(1.0,2.0), I<double>(0.0,4.0)), true);
//    BOOST_CHECK_EQUAL( contained_in(I<double>(1.0,2.0), I<float>(0.0,4.0)), true);
}


BOOST_AUTO_TEST_CASE(minimal_contains_test)
{
    BOOST_CHECK_EQUAL( contains(I<double>(0.0,4.0), I<double>(1.0,2.0)), true);
//    BOOST_CHECK_EQUAL( contains(I<double>(0.0,4.0), I<float>(1.0,2.0)), true);
}


BOOST_AUTO_TEST_CASE(minimal_less_test)
{
    BOOST_CHECK_EQUAL( less(I<double>(1.0,2.0), I<double>(3.0,4.0)), true);
//    BOOST_CHECK_EQUAL( less(I<double>(1.0,2.0), I<float>(3.0,4.0)), true);
}


BOOST_AUTO_TEST_CASE(minimal_greater_test)
{
    BOOST_CHECK_EQUAL( greater(I<double>(3.0,4.0), I<double>(1.0,2.0)), true);
//    BOOST_CHECK_EQUAL( greater(I<float>(3.0,4.0), I<double>(1.0,2.0)), true);
}


BOOST_AUTO_TEST_CASE(minimal_precedes_test)
{
    BOOST_CHECK_EQUAL( precedes(I<double>(1.0,2.0), I<double>(3.0,4.0)), true);
//    BOOST_CHECK_EQUAL( precedes(I<double>(1.0,2.0), I<float>(3.0,4.0)), true);
}


BOOST_AUTO_TEST_CASE(minimal_succeeds_test)
{
    BOOST_CHECK_EQUAL( succeeds(I<double>(3.0,4.0), I<double>(1.0,2.0)), true);
//    BOOST_CHECK_EQUAL( succeeds(I<float>(3.0,4.0), I<double>(1.0,2.0)), true);
}


BOOST_AUTO_TEST_CASE(minimal_is_interior_test)
{
    BOOST_CHECK_EQUAL( is_interior(I<double>(1.0,2.0), I<double>(0.0,4.0)), true);
//    BOOST_CHECK_EQUAL( is_interior(I<double>(1.0,2.0), I<float>(0.0,4.0)), true);
}


BOOST_AUTO_TEST_CASE(minimal_contains_interior_test)
{
    BOOST_CHECK_EQUAL( contains_interior(I<double>(0.0,4.0), I<double>(1.0,2.0)), true);
//    BOOST_CHECK_EQUAL( contains_interior(I<float>(0.0,4.0), I<double>(1.0,2.0)), true);
}


BOOST_AUTO_TEST_CASE(minimal_strictly_less_test)
{
    BOOST_CHECK_EQUAL( strictly_less(I<double>(1.0,2.0), I<double>(3.0,4.0)), true);
//    BOOST_CHECK_EQUAL( strictly_less(I<double>(1.0,2.0), I<float>(3.0,4.0)), true);
}


BOOST_AUTO_TEST_CASE(minimal_strictly_greater_test)
{
    BOOST_CHECK_EQUAL( strictly_greater(I<double>(3.0,4.0), I<double>(1.0,2.0)), true);
//    BOOST_CHECK_EQUAL( strictly_greater(I<float>(3.0,4.0), I<double>(1.0,2.0)), true);
}


BOOST_AUTO_TEST_CASE(minimal_strictly_precedes_test)
{
    BOOST_CHECK_EQUAL( strictly_precedes(I<double>(1.0,2.0), I<double>(3.0,4.0)), true);
//    BOOST_CHECK_EQUAL( strictly_precedes(I<double>(1.0,2.0), I<float>(3.0,4.0)), true);
}


BOOST_AUTO_TEST_CASE(minimal_strictly_succeeds_test)
{
    BOOST_CHECK_EQUAL( strictly_succeeds(I<double>(3.0,4.0), I<double>(1.0,2.0)), true);
//    BOOST_CHECK_EQUAL( strictly_succeeds(I<float>(3.0,4.0), I<double>(1.0,2.0)), true);
}

BOOST_AUTO_TEST_CASE(minimal_are_disjoint_test)
{
    BOOST_CHECK_EQUAL( are_disjoint(I<double>(3.0,4.0), I<double>(1.0,2.0)), true);
//    BOOST_CHECK_EQUAL( are_disjoint(I<float>(3.0,4.0), I<double>(1.0,2.0)), true);
}
