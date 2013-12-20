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
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes>;

template<typename T>
using I = p1788::infsup::interval<T, flavor>;

template<typename T>
using DI = p1788::infsup::decorated_interval<T, flavor>;



BOOST_AUTO_TEST_CASE(minimal_is_common_test)
{
    //TODO ist das in D8.1 7.2 so gemeint?
    BOOST_CHECK_EQUAL(is_common(I<double>(-27.0)), true);
    BOOST_CHECK_EQUAL(is_common(I<double>(-27.0, 0.0)), true);
    BOOST_CHECK_EQUAL(is_common(I<double>(0.0)), true);
    BOOST_CHECK_EQUAL(is_common(I<double>(-0.0)), true);
    BOOST_CHECK_EQUAL(is_common(I<double>(5.0, 12.4)), true);

    BOOST_CHECK_EQUAL(is_common(I<double>::entire()), false);
    BOOST_CHECK_EQUAL(is_common(I<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_common(I<double>(-std::numeric_limits<double>::infinity(), 0.0)), false);
    BOOST_CHECK_EQUAL(is_common(I<double>(0.0, std::numeric_limits<double>::infinity())), false);
}

BOOST_AUTO_TEST_CASE(minimal_is_common_test_dec)
{
    //TODO ist das in D8.1 7.2 so gemeint? oder hier die decoration verwenden?
    BOOST_CHECK_EQUAL(is_common(DI<double>(-27.0)), true);
    BOOST_CHECK_EQUAL(is_common(DI<double>(-27.0, 0.0)), true);
    BOOST_CHECK_EQUAL(is_common(DI<double>(0.0)), true);
    BOOST_CHECK_EQUAL(is_common(DI<double>(-0.0)), true);
    BOOST_CHECK_EQUAL(is_common(DI<double>(5.0, 12.4)), true);

    BOOST_CHECK_EQUAL(is_common(DI<double>::entire()), false);
    BOOST_CHECK_EQUAL(is_common(DI<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_common(DI<double>(-std::numeric_limits<double>::infinity(), 0.0)), false);
    BOOST_CHECK_EQUAL(is_common(DI<double>(0.0, std::numeric_limits<double>::infinity())), false);
}



BOOST_AUTO_TEST_CASE(minimal_is_singleton_test)
{
    BOOST_CHECK_EQUAL(is_singleton(I<double>(-27.0)), true);
    BOOST_CHECK_EQUAL(is_singleton(I<double>(-2.0, -2.0)), true);
    BOOST_CHECK_EQUAL(is_singleton(I<double>(12.0)), true);
    BOOST_CHECK_EQUAL(is_singleton(I<double>(17.1, 17.1)), true);
    BOOST_CHECK_EQUAL(is_singleton(I<double>(-0.0)), true);
    BOOST_CHECK_EQUAL(is_singleton(I<double>(0.0)), true);
    BOOST_CHECK_EQUAL(is_singleton(I<double>(-0.0, 0.0)), true);

    BOOST_CHECK_EQUAL(is_singleton(I<double>::entire()), false);
    BOOST_CHECK_EQUAL(is_singleton(I<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_singleton(I<double>(-1.0, 0.0)), false);
    BOOST_CHECK_EQUAL(is_singleton(I<double>(-1.0, -0.5)), false);
    BOOST_CHECK_EQUAL(is_singleton(I<double>(1.0, 2.0)), false);
    BOOST_CHECK_EQUAL(is_singleton(I<double>(-std::numeric_limits<double>::infinity())), false);
    BOOST_CHECK_EQUAL(is_singleton(I<double>(-1.0,std::numeric_limits<double>::infinity())), false);
}

BOOST_AUTO_TEST_CASE(minimal_is_singleton_test_dec)
{
    BOOST_CHECK_EQUAL(is_singleton(DI<double>(-27.0)), true);
    BOOST_CHECK_EQUAL(is_singleton(DI<double>(-2.0, -2.0)), true);
    BOOST_CHECK_EQUAL(is_singleton(DI<double>(12.0)), true);
    BOOST_CHECK_EQUAL(is_singleton(DI<double>(17.1, 17.1)), true);
    BOOST_CHECK_EQUAL(is_singleton(DI<double>(-0.0)), true);
    BOOST_CHECK_EQUAL(is_singleton(DI<double>(0.0)), true);
    BOOST_CHECK_EQUAL(is_singleton(DI<double>(-0.0, 0.0)), true);

    BOOST_CHECK_EQUAL(is_singleton(DI<double>::entire()), false);
    BOOST_CHECK_EQUAL(is_singleton(DI<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_singleton(DI<double>(-1.0, 0.0)), false);
    BOOST_CHECK_EQUAL(is_singleton(DI<double>(-1.0, -0.5)), false);
    BOOST_CHECK_EQUAL(is_singleton(DI<double>(1.0, 2.0)), false);
    BOOST_CHECK_EQUAL(is_singleton(DI<double>(-std::numeric_limits<double>::infinity())), false);
    BOOST_CHECK_EQUAL(is_singleton(DI<double>(-1.0,std::numeric_limits<double>::infinity())), false);
}



BOOST_AUTO_TEST_CASE(minimal_is_member_test)
{
    BOOST_CHECK_EQUAL(is_member(-27.0, I<double>(-27.0)), true);
    BOOST_CHECK_EQUAL(is_member(-27.0, I<double>(-27.0, 0.0)), true);
    BOOST_CHECK_EQUAL(is_member(-7.0, I<double>(-27.0, 0.0)), true);
    BOOST_CHECK_EQUAL(is_member(0.0, I<double>(-27.0, 0.0)), true);
    BOOST_CHECK_EQUAL(is_member(-0.0, I<double>(0.0)), true);
    BOOST_CHECK_EQUAL(is_member(0.0, I<double>(0.0)), true);
    BOOST_CHECK_EQUAL(is_member(0.0, I<double>(-0.0)), true);
    BOOST_CHECK_EQUAL(is_member(5.0, I<double>(5.0, 12.4)), true);
    BOOST_CHECK_EQUAL(is_member(6.3, I<double>(5.0, 12.4)), true);
    BOOST_CHECK_EQUAL(is_member(12.4, I<double>(5.0, 12.4)), true);
    BOOST_CHECK_EQUAL(is_member(0.0, I<double>::entire()), true);
    BOOST_CHECK_EQUAL(is_member(5.0, I<double>::entire()), true);
    BOOST_CHECK_EQUAL(is_member(6.3, I<double>::entire()), true);
    BOOST_CHECK_EQUAL(is_member(12.4, I<double>::entire()), true);

    BOOST_CHECK_EQUAL(is_member(-71.0, I<double>(-27.0, 0.0)), false);
    BOOST_CHECK_EQUAL(is_member(0.1, I<double>(-27.0, 0.0)), false);
    BOOST_CHECK_EQUAL(is_member(-0.01, I<double>(0.0)), false);
    BOOST_CHECK_EQUAL(is_member(0.000001, I<double>(0.0)), false);
    BOOST_CHECK_EQUAL(is_member(111110.0, I<double>(-0.0)), false);
    BOOST_CHECK_EQUAL(is_member(4.9, I<double>(5.0, 12.4)), false);
    BOOST_CHECK_EQUAL(is_member(-6.3, I<double>(5.0, 12.4)), false);
    BOOST_CHECK_EQUAL(is_member(0.0, I<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_member(-4535.3, I<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_member(-std::numeric_limits<double>::infinity(), I<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_member(std::numeric_limits<double>::infinity(), I<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_member(std::numeric_limits<double>::quiet_NaN(), I<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_member(-std::numeric_limits<double>::infinity(), I<double>::entire()), false);
    BOOST_CHECK_EQUAL(is_member(std::numeric_limits<double>::infinity(), I<double>::entire()), false);
    BOOST_CHECK_EQUAL(is_member(std::numeric_limits<double>::quiet_NaN(), I<double>::entire()), false);
}

BOOST_AUTO_TEST_CASE(minimal_is_member_test_dec)
{
    BOOST_CHECK_EQUAL(is_member(-27.0, DI<double>(-27.0)), true);
    BOOST_CHECK_EQUAL(is_member(-27.0, DI<double>(-27.0, 0.0)), true);
    BOOST_CHECK_EQUAL(is_member(-7.0, DI<double>(-27.0, 0.0)), true);
    BOOST_CHECK_EQUAL(is_member(0.0, DI<double>(-27.0, 0.0)), true);
    BOOST_CHECK_EQUAL(is_member(-0.0, DI<double>(0.0)), true);
    BOOST_CHECK_EQUAL(is_member(0.0, DI<double>(0.0)), true);
    BOOST_CHECK_EQUAL(is_member(0.0, DI<double>(-0.0)), true);
    BOOST_CHECK_EQUAL(is_member(5.0, DI<double>(5.0, 12.4)), true);
    BOOST_CHECK_EQUAL(is_member(6.3, DI<double>(5.0, 12.4)), true);
    BOOST_CHECK_EQUAL(is_member(12.4, DI<double>(5.0, 12.4)), true);
    BOOST_CHECK_EQUAL(is_member(0.0, DI<double>::entire()), true);
    BOOST_CHECK_EQUAL(is_member(5.0, DI<double>::entire()), true);
    BOOST_CHECK_EQUAL(is_member(6.3, DI<double>::entire()), true);
    BOOST_CHECK_EQUAL(is_member(12.4, DI<double>::entire()), true);

    BOOST_CHECK_EQUAL(is_member(-71.0, DI<double>(-27.0, 0.0)), false);
    BOOST_CHECK_EQUAL(is_member(0.1, DI<double>(-27.0, 0.0)), false);
    BOOST_CHECK_EQUAL(is_member(-0.01, DI<double>(0.0)), false);
    BOOST_CHECK_EQUAL(is_member(0.000001, DI<double>(0.0)), false);
    BOOST_CHECK_EQUAL(is_member(111110.0, DI<double>(-0.0)), false);
    BOOST_CHECK_EQUAL(is_member(4.9, DI<double>(5.0, 12.4)), false);
    BOOST_CHECK_EQUAL(is_member(-6.3, DI<double>(5.0, 12.4)), false);
    BOOST_CHECK_EQUAL(is_member(0.0, DI<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_member(-4535.3, DI<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_member(-std::numeric_limits<double>::infinity(), DI<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_member(std::numeric_limits<double>::infinity(), DI<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_member(std::numeric_limits<double>::quiet_NaN(), DI<double>::empty()), false);
    BOOST_CHECK_EQUAL(is_member(-std::numeric_limits<double>::infinity(), DI<double>::entire()), false);
    BOOST_CHECK_EQUAL(is_member(std::numeric_limits<double>::infinity(), DI<double>::entire()), false);
    BOOST_CHECK_EQUAL(is_member(std::numeric_limits<double>::quiet_NaN(), DI<double>::entire()), false);
}

