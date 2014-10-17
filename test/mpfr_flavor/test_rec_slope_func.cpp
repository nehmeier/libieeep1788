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

#define BOOST_TEST_MODULE "Recommended slope functions [inf-sup-interval, mpfr_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include "p1788/p1788.hpp"

template<typename T>
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes, p1788::flavor::infsup::auto_setup::yes>;

template<typename T>
using interval = p1788::infsup::interval<T, flavor>;


BOOST_AUTO_TEST_CASE(minimal_exp_slope1_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_exp_slope2_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_log_slope1_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_log_slope2_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_cos_slope2_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_sin_slope3_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_asin_slope3_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_atan_slope3_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_cosh_slope2_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_sinh_slope3_test)
{
    BOOST_CHECK(false);
}

