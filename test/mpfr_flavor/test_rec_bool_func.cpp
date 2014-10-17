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

#define BOOST_TEST_MODULE "Recommended boolean functions on intervals [inf-sup-interval, mpfr_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include <limits>

#include "p1788/p1788.hpp"

template<typename T>
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes, p1788::flavor::infsup::auto_setup::yes>;

template<typename T>
using I = p1788::infsup::interval<T, flavor>;

const double INF = std::numeric_limits<double>::infinity();
const double MAX = std::numeric_limits<double>::max();
const double MIN = std::numeric_limits<double>::min();
const double NaN = std::numeric_limits<double>::quiet_NaN();

BOOST_AUTO_TEST_CASE(minimal_is_common_test)
{
    BOOST_CHECK(is_common(I<double>(-27.0)));
    BOOST_CHECK(is_common(I<double>(-27.0, 0.0)));
    BOOST_CHECK(is_common(I<double>(0.0)));
    BOOST_CHECK(is_common(I<double>(-0.0)));
    BOOST_CHECK(is_common(I<double>(-0.0,0.0)));
    BOOST_CHECK(is_common(I<double>(0.0,-0.0)));
    BOOST_CHECK(is_common(I<double>(5.0, 12.4)));
    BOOST_CHECK(is_common(I<double>(-MAX, MAX)));

    BOOST_CHECK(!is_common(I<double>::entire()));
    BOOST_CHECK(!is_common(I<double>::empty()));
    BOOST_CHECK(!is_common(I<double>(-INF, 0.0)));
    BOOST_CHECK(!is_common(I<double>(0.0, INF)));
}

BOOST_AUTO_TEST_CASE(minimal_is_singleton_test)
{
    BOOST_CHECK(is_singleton(I<double>(-27.0)));
    BOOST_CHECK(is_singleton(I<double>(-2.0, -2.0)));
    BOOST_CHECK(is_singleton(I<double>(12.0)));
    BOOST_CHECK(is_singleton(I<double>(17.1, 17.1)));
    BOOST_CHECK(is_singleton(I<double>(-0.0)));
    BOOST_CHECK(is_singleton(I<double>(0.0)));
    BOOST_CHECK(is_singleton(I<double>(-0.0, 0.0)));
    BOOST_CHECK(is_singleton(I<double>(0.0, -0.0)));

    BOOST_CHECK(!is_singleton(I<double>::entire()));
    BOOST_CHECK(!is_singleton(I<double>::empty()));
    BOOST_CHECK(!is_singleton(I<double>(-1.0, 0.0)));
    BOOST_CHECK(!is_singleton(I<double>(-1.0, -0.5)));
    BOOST_CHECK(!is_singleton(I<double>(1.0, 2.0)));
    BOOST_CHECK(!is_singleton(I<double>(-INF,-MAX)));
    BOOST_CHECK(!is_singleton(I<double>(-1.0,INF)));
}

BOOST_AUTO_TEST_CASE(minimal_is_member_test)
{
    BOOST_CHECK(is_member(-27.0, I<double>(-27.0)));
    BOOST_CHECK(is_member(-27.0, I<double>(-27.0, 0.0)));
    BOOST_CHECK(is_member(-7.0, I<double>(-27.0, 0.0)));
    BOOST_CHECK(is_member(0.0, I<double>(-27.0, 0.0)));
    BOOST_CHECK(is_member(-0.0, I<double>(0.0)));
    BOOST_CHECK(is_member(0.0, I<double>(0.0)));
    BOOST_CHECK(is_member(0.0, I<double>(-0.0)));
    BOOST_CHECK(is_member(0.0, I<double>(-0.0,0.0)));
    BOOST_CHECK(is_member(0.0, I<double>(0.0,-0.0)));
    BOOST_CHECK(is_member(5.0, I<double>(5.0, 12.4)));
    BOOST_CHECK(is_member(6.3, I<double>(5.0, 12.4)));
    BOOST_CHECK(is_member(12.4, I<double>(5.0, 12.4)));
    BOOST_CHECK(is_member(0.0, I<double>::entire()));
    BOOST_CHECK(is_member(5.0, I<double>::entire()));
    BOOST_CHECK(is_member(6.3, I<double>::entire()));
    BOOST_CHECK(is_member(12.4, I<double>::entire()));
    BOOST_CHECK(is_member(MAX, I<double>::entire()));
    BOOST_CHECK(is_member(-MAX, I<double>::entire()));
    BOOST_CHECK(is_member(MIN, I<double>::entire()));
    BOOST_CHECK(is_member(-MIN, I<double>::entire()));

    BOOST_CHECK(!is_member(-71.0, I<double>(-27.0, 0.0)));
    BOOST_CHECK(!is_member(0.1, I<double>(-27.0, 0.0)));
    BOOST_CHECK(!is_member(-0.01, I<double>(0.0)));
    BOOST_CHECK(!is_member(0.000001, I<double>(0.0)));
    BOOST_CHECK(!is_member(111110.0, I<double>(-0.0)));
    BOOST_CHECK(!is_member(4.9, I<double>(5.0, 12.4)));
    BOOST_CHECK(!is_member(-6.3, I<double>(5.0, 12.4)));
    BOOST_CHECK(!is_member(0.0, I<double>::empty()));
    BOOST_CHECK(!is_member(-4535.3, I<double>::empty()));
    BOOST_CHECK(!is_member(-INF, I<double>::empty()));
    BOOST_CHECK(!is_member(INF, I<double>::empty()));
    BOOST_CHECK(!is_member(NaN, I<double>::empty()));
    BOOST_CHECK(!is_member(-INF, I<double>::entire()));
    BOOST_CHECK(!is_member(INF, I<double>::entire()));
    BOOST_CHECK(!is_member(NaN, I<double>::entire()));
}
