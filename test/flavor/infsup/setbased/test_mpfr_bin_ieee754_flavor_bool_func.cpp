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


const double INF = std::numeric_limits<double>::infinity();

BOOST_AUTO_TEST_CASE(minimal_is_empty_test)
{
    BOOST_CHECK( F<double>::is_empty(F<double>::static_method_empty()) );
    BOOST_CHECK( !F<double>::is_empty(F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::is_empty(F<double>::representation(1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_empty(F<double>::representation(-1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_empty(F<double>::representation(-3.0,-2.0)) );
    BOOST_CHECK( !F<double>::is_empty(F<double>::representation(-INF,2.0)) );
    BOOST_CHECK( !F<double>::is_empty(F<double>::representation(-INF,0.0)) );
    BOOST_CHECK( !F<double>::is_empty(F<double>::representation(-INF,-0.0)) );
    BOOST_CHECK( !F<double>::is_empty(F<double>::representation(0.0,INF)) );
    BOOST_CHECK( !F<double>::is_empty(F<double>::representation(-0.0,INF)) );
    BOOST_CHECK( !F<double>::is_empty(F<double>::representation(-0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_empty(F<double>::representation(0.0,-0.0)) );
    BOOST_CHECK( !F<double>::is_empty(F<double>::representation(0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_empty(F<double>::representation(-0.0,-0.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_is_entire_test)
{
    BOOST_CHECK( !F<double>::is_entire(F<double>::static_method_empty()) );
    BOOST_CHECK( F<double>::is_entire(F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::is_entire(F<double>::representation(1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_entire(F<double>::representation(-1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_entire(F<double>::representation(-3.0,-2.0)) );
    BOOST_CHECK( !F<double>::is_entire(F<double>::representation(-INF,2.0)) );
    BOOST_CHECK( !F<double>::is_entire(F<double>::representation(-INF,0.0)) );
    BOOST_CHECK( !F<double>::is_entire(F<double>::representation(-INF,-0.0)) );
    BOOST_CHECK( !F<double>::is_entire(F<double>::representation(0.0,INF)) );
    BOOST_CHECK( !F<double>::is_entire(F<double>::representation(-0.0,INF)) );
    BOOST_CHECK( !F<double>::is_entire(F<double>::representation(-0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_entire(F<double>::representation(0.0,-0.0)) );
    BOOST_CHECK( !F<double>::is_entire(F<double>::representation(0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_entire(F<double>::representation(-0.0,-0.0)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_equal_test)
{
    BOOST_CHECK( F<double>::is_equal(F<double>::representation(1.0,2.0), F<double>::representation(1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_equal(F<double>::representation(1.0,2.1), F<double>::representation(1.0,2.0)) );
    BOOST_CHECK( F<double>::is_equal(F<double>::static_method_empty(), F<double>::static_method_empty()) );
    BOOST_CHECK( !F<double>::is_equal(F<double>::static_method_empty(), F<double>::representation(1.0,2.0)) );
    BOOST_CHECK( F<double>::is_equal(F<double>::static_method_entire(), F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::is_equal(F<double>::representation(1.0,2.4), F<double>::static_method_entire()) );
    BOOST_CHECK( F<double>::is_equal(F<double>::representation(1.0,INF), F<double>::representation(1.0,INF)) );
    BOOST_CHECK( !F<double>::is_equal(F<double>::representation(1.0,2.4), F<double>::representation(1.0,INF)) );
    BOOST_CHECK( F<double>::is_equal(F<double>::representation(-INF,2.0), F<double>::representation(-INF,2.0)) );
    BOOST_CHECK( !F<double>::is_equal(F<double>::representation(-INF,2.4), F<double>::representation(-INF,2.0)) );
    BOOST_CHECK( F<double>::is_equal(F<double>::representation(-2.0,0.0), F<double>::representation(-2.0,0.0)) );
    BOOST_CHECK( F<double>::is_equal(F<double>::representation(-0.0,2.0), F<double>::representation(0.0,2.0)) );
    BOOST_CHECK( F<double>::is_equal(F<double>::representation(-0.0,-0.0), F<double>::representation(0.0,0.0)) );
    BOOST_CHECK( F<double>::is_equal(F<double>::representation(-0.0,0.0), F<double>::representation(0.0,0.0)) );
    BOOST_CHECK( F<double>::is_equal(F<double>::representation(0.0,-0.0), F<double>::representation(0.0,0.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_subset_test)
{
    BOOST_CHECK( F<double>::subset(F<double>::static_method_empty(), F<double>::static_method_empty()) );
    BOOST_CHECK( F<double>::subset(F<double>::static_method_empty(), F<double>::representation(0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::static_method_empty(), F<double>::representation(-0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::static_method_empty(), F<double>::representation(-0.1,1.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::static_method_empty(), F<double>::representation(-0.1,0.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::static_method_empty(), F<double>::representation(-0.1,-0.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::static_method_empty(), F<double>::static_method_entire()) );

    BOOST_CHECK( !F<double>::subset(F<double>::representation(0.0,4.0), F<double>::static_method_empty()) );
    BOOST_CHECK( !F<double>::subset(F<double>::representation(-0.0,4.0), F<double>::static_method_empty()) );
    BOOST_CHECK( !F<double>::subset(F<double>::representation(-0.1,1.0), F<double>::static_method_empty()) );
    BOOST_CHECK( !F<double>::subset(F<double>::static_method_entire(), F<double>::static_method_empty()) );

    BOOST_CHECK( F<double>::subset(F<double>::representation(0.0,4.0), F<double>::static_method_entire()) );
    BOOST_CHECK( F<double>::subset(F<double>::representation(-0.0,4.0), F<double>::static_method_entire()) );
    BOOST_CHECK( F<double>::subset(F<double>::representation(-0.1,1.0), F<double>::static_method_entire()) );
    BOOST_CHECK( F<double>::subset(F<double>::static_method_entire(), F<double>::static_method_entire()) );

    BOOST_CHECK( F<double>::subset(F<double>::representation(1.0,2.0), F<double>::representation(1.0,2.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::representation(1.0,2.0), F<double>::representation(0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::representation(1.0,2.0), F<double>::representation(-0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::representation(0.1,0.2), F<double>::representation(0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::representation(0.1,0.2), F<double>::representation(-0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::representation(-0.1,-0.1), F<double>::representation(-4.0, 3.4)) );

    BOOST_CHECK( F<double>::subset(F<double>::representation(0.0,0.0), F<double>::representation(-0.0,-0.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::representation(-0.0,-0.0), F<double>::representation(0.0,0.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::representation(-0.0,0.0), F<double>::representation(0.0,0.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::representation(-0.0,0.0), F<double>::representation(0.0,-0.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::representation(0.0,-0.0), F<double>::representation(0.0,0.0)) );
    BOOST_CHECK( F<double>::subset(F<double>::representation(0.0,-0.0), F<double>::representation(-0.0,0.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_less_test)
{
    BOOST_CHECK( F<double>::less(F<double>::static_method_empty(), F<double>::static_method_empty()) );
    BOOST_CHECK( !F<double>::less(F<double>::representation(1.0,2.0), F<double>::static_method_empty()) );
    BOOST_CHECK( !F<double>::less(F<double>::static_method_empty(), F<double>::representation(1.0,2.0)) );

    BOOST_CHECK( F<double>::less(F<double>::static_method_entire(), F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::less(F<double>::representation(1.0,2.0), F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::less(F<double>::representation(0.0,2.0), F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::less(F<double>::representation(-0.0,2.0), F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::less(F<double>::static_method_entire(), F<double>::representation(1.0,2.0)) );
    BOOST_CHECK( !F<double>::less(F<double>::static_method_entire(), F<double>::representation(0.0,2.0)) );
    BOOST_CHECK( !F<double>::less(F<double>::static_method_entire(), F<double>::representation(-0.0,2.0)) );

    BOOST_CHECK( F<double>::less(F<double>::representation(0.0,2.0), F<double>::representation(0.0,2.0)) );
    BOOST_CHECK( F<double>::less(F<double>::representation(0.0,2.0), F<double>::representation(-0.0,2.0)) );
    BOOST_CHECK( F<double>::less(F<double>::representation(0.0,2.0), F<double>::representation(1.0,2.0)) );
    BOOST_CHECK( F<double>::less(F<double>::representation(-0.0,2.0), F<double>::representation(1.0,2.0)) );
    BOOST_CHECK( F<double>::less(F<double>::representation(1.0,2.0), F<double>::representation(1.0,2.0)) );
    BOOST_CHECK( F<double>::less(F<double>::representation(1.0,2.0), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( F<double>::less(F<double>::representation(1.0,3.5), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( F<double>::less(F<double>::representation(1.0,4.0), F<double>::representation(3.0,4.0)) );

    BOOST_CHECK( F<double>::less(F<double>::representation(-2.0,-1.0), F<double>::representation(-2.0,-1.0)) );
    BOOST_CHECK( F<double>::less(F<double>::representation(-3.0,-1.5), F<double>::representation(-2.0,-1.0)) );

    BOOST_CHECK( F<double>::less(F<double>::representation(0.0,0.0), F<double>::representation(-0.0,-0.0)) );
    BOOST_CHECK( F<double>::less(F<double>::representation(-0.0,-0.0), F<double>::representation(0.0,0.0)) );
    BOOST_CHECK( F<double>::less(F<double>::representation(-0.0,0.0), F<double>::representation(0.0,0.0)) );
    BOOST_CHECK( F<double>::less(F<double>::representation(-0.0,0.0), F<double>::representation(0.0,-0.0)) );
    BOOST_CHECK( F<double>::less(F<double>::representation(0.0,-0.0), F<double>::representation(0.0,0.0)) );
    BOOST_CHECK( F<double>::less(F<double>::representation(0.0,-0.0), F<double>::representation(-0.0,0.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_precedes_test)
{
    BOOST_CHECK( F<double>::precedes(F<double>::static_method_empty(), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( F<double>::precedes(F<double>::representation(3.0,4.0), F<double>::static_method_empty()) );
    BOOST_CHECK( F<double>::precedes(F<double>::static_method_empty(), F<double>::static_method_empty()) );


    BOOST_CHECK( !F<double>::precedes(F<double>::representation(1.0,2.0), F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::precedes(F<double>::representation(0.0,2.0), F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::precedes(F<double>::representation(-0.0,2.0), F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::precedes(F<double>::static_method_entire(), F<double>::representation(1.0,2.0)) );
    BOOST_CHECK( !F<double>::precedes(F<double>::static_method_entire(), F<double>::static_method_entire()) );

    BOOST_CHECK( F<double>::precedes(F<double>::representation(1.0,2.0), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( F<double>::precedes(F<double>::representation(1.0,3.0), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( F<double>::precedes(F<double>::representation(-3.0, -1.0), F<double>::representation(-1.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(F<double>::representation(-3.0, -1.0), F<double>::representation(-1.0,-0.0)) );

    BOOST_CHECK( !F<double>::precedes(F<double>::representation(1.0,3.5), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( !F<double>::precedes(F<double>::representation(1.0,4.0), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( !F<double>::precedes(F<double>::representation(-3.0, -0.1), F<double>::representation(-1.0,0.0)) );

    BOOST_CHECK( F<double>::precedes(F<double>::representation(0.0,0.0), F<double>::representation(-0.0,-0.0)) );
    BOOST_CHECK( F<double>::precedes(F<double>::representation(-0.0,-0.0), F<double>::representation(0.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(F<double>::representation(-0.0,0.0), F<double>::representation(0.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(F<double>::representation(-0.0,0.0), F<double>::representation(0.0,-0.0)) );
    BOOST_CHECK( F<double>::precedes(F<double>::representation(0.0,-0.0), F<double>::representation(0.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(F<double>::representation(0.0,-0.0), F<double>::representation(-0.0,0.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_is_interior_test)
{
    BOOST_CHECK( F<double>::is_interior(F<double>::static_method_empty(), F<double>::static_method_empty()) );
    BOOST_CHECK( F<double>::is_interior(F<double>::static_method_empty(), F<double>::representation(0.0,4.0)) );
    BOOST_CHECK( !F<double>::is_interior(F<double>::representation(0.0,4.0), F<double>::static_method_empty()) );

    BOOST_CHECK( F<double>::is_interior(F<double>::static_method_entire(), F<double>::static_method_entire()) );
    BOOST_CHECK( F<double>::is_interior(F<double>::representation(0.0,4.0), F<double>::static_method_entire()) );
    BOOST_CHECK( F<double>::is_interior(F<double>::static_method_empty(), F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::is_interior(F<double>::static_method_entire(), F<double>::representation(0.0,4.0)) );

    BOOST_CHECK( !F<double>::is_interior(F<double>::representation(0.0,4.0), F<double>::representation(0.0,4.0)) );
    BOOST_CHECK( F<double>::is_interior(F<double>::representation(1.0,2.0), F<double>::representation(0.0,4.0)) );
    BOOST_CHECK( !F<double>::is_interior(F<double>::representation(-2.0,2.0), F<double>::representation(-2.0,4.0)) );
    BOOST_CHECK( F<double>::is_interior(F<double>::representation(-0.0,-0.0), F<double>::representation(-2.0,4.0)) );
    BOOST_CHECK( F<double>::is_interior(F<double>::representation(0.0,0.0), F<double>::representation(-2.0,4.0)) );
    BOOST_CHECK( !F<double>::is_interior(F<double>::representation(0.0,0.0), F<double>::representation(-0.0,-0.0)) );

    BOOST_CHECK( !F<double>::is_interior(F<double>::representation(0.0,4.4), F<double>::representation(0.0,4.0)) );
    BOOST_CHECK( !F<double>::is_interior(F<double>::representation(-1.0,-1.0), F<double>::representation(0.0,4.0)) );
    BOOST_CHECK( !F<double>::is_interior(F<double>::representation(2.0,2.0), F<double>::representation(-2.0,-1.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_strictly_less_test)
{
    BOOST_CHECK( F<double>::strictly_less(F<double>::static_method_empty(), F<double>::static_method_empty()) );
    BOOST_CHECK( !F<double>::strictly_less(F<double>::representation(1.0,2.0), F<double>::static_method_empty()) );
    BOOST_CHECK( !F<double>::strictly_less(F<double>::static_method_empty(), F<double>::representation(1.0,2.0)) );

    BOOST_CHECK( F<double>::strictly_less(F<double>::static_method_entire(), F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::strictly_less(F<double>::representation(1.0,2.0), F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::strictly_less(F<double>::static_method_entire(), F<double>::representation(1.0,2.0)) );

    BOOST_CHECK( !F<double>::strictly_less(F<double>::representation(1.0,2.0), F<double>::representation(1.0,2.0)) );
    BOOST_CHECK( F<double>::strictly_less(F<double>::representation(1.0,2.0), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( F<double>::strictly_less(F<double>::representation(1.0,3.5), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_less(F<double>::representation(1.0,4.0), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_less(F<double>::representation(0.0,4.0), F<double>::representation(0.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_less(F<double>::representation(-0.0,4.0), F<double>::representation(0.0,4.0)) );

    BOOST_CHECK( !F<double>::strictly_less(F<double>::representation(-2.0,-1.0), F<double>::representation(-2.0,-1.0)) );
    BOOST_CHECK( F<double>::strictly_less(F<double>::representation(-3.0,-1.5), F<double>::representation(-2.0,-1.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_strictly_precedes_test)
{
    BOOST_CHECK( F<double>::strictly_precedes(F<double>::static_method_empty(), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( F<double>::strictly_precedes(F<double>::representation(3.0,4.0), F<double>::static_method_empty()) );
    BOOST_CHECK( F<double>::strictly_precedes(F<double>::static_method_empty(), F<double>::static_method_empty()) );


    BOOST_CHECK( !F<double>::strictly_precedes(F<double>::representation(1.0,2.0), F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::strictly_precedes(F<double>::static_method_entire(), F<double>::representation(1.0,2.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(F<double>::static_method_entire(), F<double>::static_method_entire()) );

    BOOST_CHECK( F<double>::strictly_precedes(F<double>::representation(1.0,2.0), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(F<double>::representation(1.0,3.0), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(F<double>::representation(-3.0, -1.0), F<double>::representation(-1.0,0.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(F<double>::representation(-3.0, -0.0), F<double>::representation(0.0,1.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(F<double>::representation(-3.0, 0.0), F<double>::representation(-0.0,1.0)) );

    BOOST_CHECK( !F<double>::strictly_precedes(F<double>::representation(1.0,3.5), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(F<double>::representation(1.0,4.0), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(F<double>::representation(-3.0, -0.1), F<double>::representation(-1.0,0.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_are_disjoint_test)
{
    BOOST_CHECK( F<double>::are_disjoint(F<double>::static_method_empty(), F<double>::representation(3.0,4.0)) );
    BOOST_CHECK( F<double>::are_disjoint(F<double>::representation(3.0,4.0), F<double>::static_method_empty()) );
    BOOST_CHECK( F<double>::are_disjoint(F<double>::static_method_empty(), F<double>::static_method_empty()) );

    BOOST_CHECK( F<double>::are_disjoint(F<double>::representation(3.0,4.0), F<double>::representation(1.0,2.0)) );

    BOOST_CHECK( !F<double>::are_disjoint(F<double>::representation(0.0,0.0), F<double>::representation(-0.0,-0.0)) );
    BOOST_CHECK( !F<double>::are_disjoint(F<double>::representation(0.0,-0.0), F<double>::representation(-0.0,0.0)) );
    BOOST_CHECK( !F<double>::are_disjoint(F<double>::representation(3.0,4.0), F<double>::representation(1.0,7.0)) );
    BOOST_CHECK( !F<double>::are_disjoint(F<double>::representation(3.0,4.0), F<double>::static_method_entire()) );
    BOOST_CHECK( !F<double>::are_disjoint(F<double>::static_method_entire(), F<double>::representation(1.0,7.0)) );
    BOOST_CHECK( !F<double>::are_disjoint(F<double>::static_method_entire(), F<double>::static_method_entire()) );
}
