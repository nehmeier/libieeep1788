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

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_mpfr_bool_func
#include <boost/test/unit_test.hpp>

#include <limits>

#include "p1788/infsup/interval.hpp"
#include "p1788/flavor/infsup/flavor_mpfr.hpp"

template<typename T>
using interval = p1788::infsup::interval<T, p1788::flavor::infsup::mpfr_flavor>;

BOOST_AUTO_TEST_CASE(test_is_empty)
{
    BOOST_CHECK( is_empty(interval<float>()) );
    BOOST_CHECK( is_empty(interval<float>::empty()) );
    BOOST_CHECK( !is_empty(interval<float>(1,2)) );
    BOOST_CHECK( !is_empty(interval<float>::entire()) );

    BOOST_CHECK( is_empty(interval<double>()) );
    BOOST_CHECK( is_empty(interval<double>::empty()) );
    BOOST_CHECK( !is_empty(interval<double>(1,2)) );
    BOOST_CHECK( !is_empty(interval<double>::entire()) );

    BOOST_CHECK( is_empty(interval<long double>()) );
    BOOST_CHECK( is_empty(interval<long double>::empty()) );
    BOOST_CHECK( !is_empty(interval<long double>(1,2)) );
    BOOST_CHECK( !is_empty(interval<long double>::entire()) );
}


BOOST_AUTO_TEST_CASE(test_is_entire)
{
    BOOST_CHECK( !is_entire(interval<float>()) );
    BOOST_CHECK( !is_entire(interval<float>::empty()) );
    BOOST_CHECK( !is_entire(interval<float>(1,2)) );
    BOOST_CHECK( is_entire(interval<float>::entire()) );
    BOOST_CHECK( is_entire(interval<float>(-std::numeric_limits<float>::infinity(),
                                           std::numeric_limits<float>::infinity())) );

    BOOST_CHECK( !is_entire(interval<double>()) );
    BOOST_CHECK( !is_entire(interval<double>::empty()) );
    BOOST_CHECK( !is_entire(interval<double>(1,2)) );
    BOOST_CHECK( is_entire(interval<double>::entire()) );
    BOOST_CHECK( is_entire(interval<double>(-std::numeric_limits<double>::infinity(),
                                           std::numeric_limits<double>::infinity())) );

    BOOST_CHECK( !is_entire(interval<long double>()) );
    BOOST_CHECK( !is_entire(interval<long double>::empty()) );
    BOOST_CHECK( !is_entire(interval<long double>(1,2)) );
    BOOST_CHECK( is_entire(interval<long double>::entire()) );
    BOOST_CHECK( is_entire(interval<long double>(-std::numeric_limits<long double>::infinity(),
                                           std::numeric_limits<long double>::infinity())) );
}


BOOST_AUTO_TEST_CASE(test_is_equal)
{
    BOOST_CHECK( is_equal(interval<float>(), interval<float>()) );
    BOOST_CHECK( is_equal(interval<float>::empty(), interval<float>()) );
    BOOST_CHECK( is_equal(interval<float>(), interval<float>::empty()) );
    BOOST_CHECK( is_equal(interval<float>::empty(), interval<float>::empty()) );
}
