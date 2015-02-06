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
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#define BOOST_TEST_MODULE "Integration: Recommended boolean functions of intervals  [infsup/interval, infsup/decorated_interval, p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include <limits>

#include "p1788/p1788.hpp"

template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;
template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

typedef p1788::decoration::decoration DEC;

BOOST_AUTO_TEST_CASE(integration_is_common_test)
{
    BOOST_CHECK(!is_common(I<double>::empty()));
    BOOST_CHECK(is_common(I<double>(1.0,2.0)));
    BOOST_CHECK(!is_common(I<double>::entire()));
    BOOST_CHECK(!I<double>::is_common(I<double>::empty()));
    BOOST_CHECK(I<double>::is_common(I<double>(1.0,2.0)));
    BOOST_CHECK(!I<double>::is_common(I<double>::entire()));

    BOOST_CHECK(!is_common(DI<double>::empty()));
    BOOST_CHECK(!is_common(DI<double>::nai()));
    BOOST_CHECK(is_common(DI<double>(-5.7,8.3)));
    BOOST_CHECK(is_common(DI<double>(-5.7,8.3, DEC::com)));
    BOOST_CHECK(is_common(DI<double>(-5.7,8.3, DEC::dac)));
    BOOST_CHECK(!is_common(DI<double>::entire()));
    BOOST_CHECK(!DI<double>::is_common(DI<double>::empty()));
    BOOST_CHECK(!DI<double>::is_common(DI<double>::nai()));
    BOOST_CHECK(DI<double>::is_common(DI<double>(-5.7,8.3)));
    BOOST_CHECK(DI<double>::is_common(DI<double>(-5.7,8.3, DEC::com)));
    BOOST_CHECK(DI<double>::is_common(DI<double>(-5.7,8.3, DEC::dac)));
    BOOST_CHECK(!DI<double>::is_common(DI<double>::entire()));
}

BOOST_AUTO_TEST_CASE(integration_is_singleton_test)
{
    BOOST_CHECK(is_singleton(I<double>(1.0,1.0)));
    BOOST_CHECK(is_singleton(I<double>(0.0,0.0)));
    BOOST_CHECK(is_singleton(I<double>(-7.0,-7.0)));
    BOOST_CHECK(!is_singleton(I<double>(-7.0,7.0)));
    BOOST_CHECK(!is_singleton(I<double>::empty()));
    BOOST_CHECK(!is_singleton(I<double>::entire()));
    BOOST_CHECK(I<double>::is_singleton(I<double>(1.0,1.0)));
    BOOST_CHECK(I<double>::is_singleton(I<double>(0.0,0.0)));
    BOOST_CHECK(I<double>::is_singleton(I<double>(-7.0,-7.0)));
    BOOST_CHECK(!I<double>::is_singleton(I<double>(-7.0,7.0)));
    BOOST_CHECK(!I<double>::is_singleton(I<double>::empty()));
    BOOST_CHECK(!I<double>::is_singleton(I<double>::entire()));

    BOOST_CHECK(is_singleton(DI<double>(1.0,1.0)));
    BOOST_CHECK(is_singleton(DI<double>(0.0,0.0)));
    BOOST_CHECK(is_singleton(DI<double>(-7.0,-7.0)));
    BOOST_CHECK(!is_singleton(DI<double>(-7.0,7.0)));
    BOOST_CHECK(!is_singleton(DI<double>::empty()));
    BOOST_CHECK(!is_singleton(DI<double>::nai()));
    BOOST_CHECK(!is_singleton(DI<double>::entire()));
    BOOST_CHECK(DI<double>::is_singleton(DI<double>(1.0,1.0)));
    BOOST_CHECK(DI<double>::is_singleton(DI<double>(0.0,0.0)));
    BOOST_CHECK(DI<double>::is_singleton(DI<double>(-7.0,-7.0)));
    BOOST_CHECK(!DI<double>::is_singleton(DI<double>(-7.0,7.0)));
    BOOST_CHECK(!DI<double>::is_singleton(DI<double>::empty()));
    BOOST_CHECK(!DI<double>::is_singleton(DI<double>::nai()));
    BOOST_CHECK(!DI<double>::is_singleton(DI<double>::entire()));
}

BOOST_AUTO_TEST_CASE(integration_is_member_test)
{
    BOOST_CHECK(!is_member(7.0, I<double>::empty()));
    BOOST_CHECK(!is_member(7.0f, I<double>::empty()));
    BOOST_CHECK(is_member(5.0, I<double>::entire()));
    BOOST_CHECK(is_member(5.0f, I<double>::entire()));
    BOOST_CHECK(is_member(5.0, I<double>(-8.0,10.1)));
    BOOST_CHECK(is_member(5.0f, I<double>(-8.0,10.1)));
    BOOST_CHECK(!I<double>::is_member(7.0, I<double>::empty()));
    BOOST_CHECK(!I<double>::is_member(7.0f, I<double>::empty()));
    BOOST_CHECK(I<double>::is_member(5.0, I<double>::entire()));
    BOOST_CHECK(I<double>::is_member(5.0f, I<double>::entire()));
    BOOST_CHECK(I<double>::is_member(5.0, I<double>(-8.0,10.1)));
    BOOST_CHECK(I<double>::is_member(5.0f, I<double>(-8.0,10.1)));

    BOOST_CHECK(!is_member(7.0, DI<double>::empty()));
    BOOST_CHECK(!is_member(7.0f, DI<double>::empty()));
    BOOST_CHECK(!is_member(7.0, DI<double>::nai()));
    BOOST_CHECK(!is_member(7.0f, DI<double>::nai()));
    BOOST_CHECK(is_member(5.0, DI<double>::entire()));
    BOOST_CHECK(is_member(5.0f, DI<double>::entire()));
    BOOST_CHECK(is_member(5.0, DI<double>(-8.0,10.1)));
    BOOST_CHECK(is_member(5.0f, DI<double>(-8.0,10.1)));
    BOOST_CHECK(!DI<double>::is_member(7.0, DI<double>::empty()));
    BOOST_CHECK(!DI<double>::is_member(7.0f, DI<double>::empty()));
    BOOST_CHECK(!DI<double>::is_member(7.0, DI<double>::nai()));
    BOOST_CHECK(!DI<double>::is_member(7.0f, DI<double>::nai()));
    BOOST_CHECK(DI<double>::is_member(5.0, DI<double>::entire()));
    BOOST_CHECK(DI<double>::is_member(5.0f, DI<double>::entire()));
    BOOST_CHECK(DI<double>::is_member(5.0, DI<double>(-8.0,10.1)));
    BOOST_CHECK(DI<double>::is_member(5.0f, DI<double>(-8.0,10.1)));
}
