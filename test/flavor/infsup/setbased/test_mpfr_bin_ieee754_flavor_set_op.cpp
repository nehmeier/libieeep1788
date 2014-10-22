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

#define BOOST_TEST_MODULE "Flavor: Set operations [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"
#include "test/util/mpfr_bin_ieee754_flavor_io_test_util.hpp"

template<typename T>
using F = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>;



BOOST_AUTO_TEST_CASE(minimal_intersect_test)
{
    BOOST_CHECK_EQUAL( F<double>::intersect(F<double>::representation(1.0,3.0), F<double>::representation(2.1,4.0)), F<double>::representation(2.1,3.0) );
    BOOST_CHECK_EQUAL( F<double>::intersect(F<double>::representation(1.0,3.0), F<double>::representation(3.0,4.0)), F<double>::representation(3.0,3.0) );
    BOOST_CHECK( F<double>::is_empty( F<double>::intersect(F<double>::representation(1.0,3.0), F<double>::static_method_empty()) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::intersect(F<double>::static_method_entire(), F<double>::static_method_empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::intersect(F<double>::representation(1.0,3.0), F<double>::static_method_entire()), F<double>::representation(1.0,3.0) );
}

BOOST_AUTO_TEST_CASE(minimal_hull_test)
{
    BOOST_CHECK_EQUAL( F<double>::hull(F<double>::representation(1.0,3.0), F<double>::representation(2.1,4.0)), F<double>::representation(1.0,4.0) );
    BOOST_CHECK_EQUAL( F<double>::hull(F<double>::representation(1.0,1.0), F<double>::representation(2.1,4.0)), F<double>::representation(1.0,4.0) );
    BOOST_CHECK_EQUAL( F<double>::hull(F<double>::representation(1.0,3.0), F<double>::static_method_empty()), F<double>::representation(1.0,3.0) );
    BOOST_CHECK( F<double>::is_empty( F<double>::hull(F<double>::static_method_empty(), F<double>::static_method_empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::hull(F<double>::representation(1.0,3.0), F<double>::static_method_entire()), F<double>::static_method_entire() );
}
