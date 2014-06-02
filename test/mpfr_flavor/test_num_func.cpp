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

#define BOOST_TEST_MODULE "Numeric functions on intervals [inf-sup-interval, mpfr_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include <cmath>
#include <limits>
#include "p1788/p1788.hpp"

template<typename T>
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes>;

template<typename T>
using I = p1788::infsup::interval<T, flavor>;

const double INF = std::numeric_limits<double>::infinity();
const double MAX = std::numeric_limits<double>::max();

BOOST_AUTO_TEST_CASE(minimal_inf_test)
{
    BOOST_CHECK_EQUAL( inf(I<double>(1.0,2.0)), 1.0 );
    BOOST_CHECK_EQUAL( inf(I<double>::entire()), -INF );
    BOOST_CHECK_EQUAL( inf(I<double>::empty()), INF );

    BOOST_CHECK_EQUAL( inf(I<double>(-0.0,2.0)), 0.0 );
    BOOST_CHECK( std::signbit(inf(I<double>(-0.0,2.0))) );
    BOOST_CHECK_EQUAL( inf(I<double>(0.0,2.0)), 0.0 );
    BOOST_CHECK( std::signbit(inf(I<double>(0.0,2.0))) );
}

BOOST_AUTO_TEST_CASE(minimal_sup_test)
{
    BOOST_CHECK_EQUAL( sup(I<double>(1.0,2.0)), 2.0 );
    BOOST_CHECK_EQUAL( sup(I<double>::entire()), INF );
    BOOST_CHECK_EQUAL( sup(I<double>::empty()), -INF );

    BOOST_CHECK_EQUAL( sup(I<double>(-3.0,0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(sup(I<double>(-3.0,0.0))) );
    BOOST_CHECK_EQUAL( sup(I<double>(-3.0,-0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(sup(I<double>(-3.0,-0.0))) );
}

BOOST_AUTO_TEST_CASE(minimal_mid_test)
{
    BOOST_CHECK_EQUAL( mid(I<double>(0.0,2.0)), 1.0 );
    BOOST_CHECK_EQUAL( mid(I<double>(2.0)), 2.0 );
    BOOST_CHECK( std::isnan(mid(I<double>::empty())) );
    BOOST_CHECK_EQUAL( mid(I<double>::entire()), 0.0 );
    BOOST_CHECK( !std::signbit(mid(I<double>::entire())) );
    BOOST_CHECK_EQUAL( mid(I<double>(-2.0,2.0)), 0.0 );
    BOOST_CHECK( !std::signbit(mid(I<double>(-2.0,2.0))) );
    BOOST_CHECK_EQUAL( mid(I<double>(0.0,INF)), MAX );
    BOOST_CHECK_EQUAL( mid(I<double>(-INF, 1.2)), -MAX );
}

BOOST_AUTO_TEST_CASE(minimal_rad_test)
{
    BOOST_CHECK_EQUAL( rad(I<double>(0.0,2.0)), 1.0 );
    BOOST_CHECK_EQUAL( rad(I<double>(2.0,2.0)), 0.0 );
    BOOST_CHECK( !std::signbit(rad(I<double>(2.0,2.0))) );
    BOOST_CHECK( std::isnan(rad(I<double>::empty())) );
    BOOST_CHECK_EQUAL( rad(I<double>::entire()), INF );
    BOOST_CHECK_EQUAL( rad(I<double>(0.0,INF)), INF );
    BOOST_CHECK_EQUAL( rad(I<double>(-INF, 1.2)), INF );
}

BOOST_AUTO_TEST_CASE(minimal_mid_rad_test)
{
    BOOST_CHECK_EQUAL( mid_rad(I<double>(0.0,2.0)).first, 1.0 );
    BOOST_CHECK_EQUAL( mid_rad(I<double>(2.0)).first, 2.0 );
    BOOST_CHECK( std::isnan(mid_rad(I<double>::empty()).first) );
    BOOST_CHECK_EQUAL( mid_rad(I<double>::entire()).first, 0.0 );
    BOOST_CHECK( !std::signbit(mid_rad(I<double>::entire()).first) );
    BOOST_CHECK_EQUAL( mid_rad(I<double>(-2.0,2.0)).first, 0.0 );
    BOOST_CHECK( !std::signbit(mid_rad(I<double>(-2.0,2.0)).first) );
    BOOST_CHECK_EQUAL( mid_rad(I<double>(0.0,INF)).first, MAX );
    BOOST_CHECK_EQUAL( mid_rad(I<double>(-INF, 1.2)).first, -MAX );

    BOOST_CHECK_EQUAL( mid_rad(I<double>(0.0,2.0)).second, 1.0 );
    BOOST_CHECK_EQUAL( mid_rad(I<double>(2.0,2.0)).second, 0.0 );
    BOOST_CHECK( !std::signbit(mid_rad(I<double>(2.0,2.0)).second) );
    BOOST_CHECK( std::isnan(mid_rad(I<double>::empty()).second) );
    BOOST_CHECK_EQUAL( mid_rad(I<double>::entire()).second, INF );
    BOOST_CHECK_EQUAL( mid_rad(I<double>(0.0,INF)).second, INF );
    BOOST_CHECK_EQUAL( mid_rad(I<double>(-INF, 1.2)).second, INF );
}

BOOST_AUTO_TEST_CASE(minimal_wid_test)
{
    BOOST_CHECK_EQUAL( wid(I<double>(2.0,2.0)), 0.0 );
    BOOST_CHECK( !std::signbit(wid(I<double>(2.0,2.0))) );
    BOOST_CHECK_EQUAL( wid(I<double>(1.0,2.0)), 1.0 );
    BOOST_CHECK_EQUAL( wid(I<double>(1.0,INF)), INF );
    BOOST_CHECK_EQUAL( wid(I<double>(-INF,2.0)), INF );
    BOOST_CHECK_EQUAL( wid(I<double>::entire()), INF );
    BOOST_CHECK( std::isnan(wid(I<double>::empty())) );
}

BOOST_AUTO_TEST_CASE(minimal_mag_test)
{
    BOOST_CHECK_EQUAL( mag(I<double>(1.0,2.0)), 2.0 );
    BOOST_CHECK_EQUAL( mag(I<double>(-4.0,2.0)), 4.0 );
    BOOST_CHECK_EQUAL( mag(I<double>(-INF,2.0)), INF );
    BOOST_CHECK_EQUAL( mag(I<double>(1.0,INF)), INF );
    BOOST_CHECK_EQUAL( mag(I<double>::entire()), INF );
    BOOST_CHECK( std::isnan(mag(I<double>::empty())) );
    BOOST_CHECK_EQUAL( mag(I<double>(-0.0,0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(mag(I<double>(-0.0,0.0))) );
    BOOST_CHECK_EQUAL( mag(I<double>(-0.0,-0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(mag(I<double>(-0.0,-0.0))) );
}

BOOST_AUTO_TEST_CASE(minimal_mig_test)
{
    BOOST_CHECK_EQUAL( mig(I<double>(1.0,2.0)), 1.0 );
    BOOST_CHECK_EQUAL( mig(I<double>(-4.0,2.0)), 0.0 );
    BOOST_CHECK( !std::signbit(mig(I<double>(-4.0,2.0))) );
    BOOST_CHECK_EQUAL( mig(I<double>(-4.0,-2.0)), 2.0 );
    BOOST_CHECK_EQUAL( mig(I<double>(-INF,2.0)), 0.0 );
    BOOST_CHECK_EQUAL( mig(I<double>(-INF,-2.0)), 2.0 );
    BOOST_CHECK_EQUAL( mig(I<double>(-1.0,INF)), 0.0 );
    BOOST_CHECK_EQUAL( mig(I<double>(1.0,INF)), 1.0 );
    BOOST_CHECK_EQUAL( mig(I<double>::entire()), 0.0 );
    BOOST_CHECK( !std::signbit(mig(I<double>::entire())) );
    BOOST_CHECK( std::isnan(mig(I<double>::empty())) );
    BOOST_CHECK_EQUAL( mig(I<double>(-0.0,0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(mig(I<double>(-0.0,0.0))) );
    BOOST_CHECK_EQUAL( mig(I<double>(-0.0,-0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(mig(I<double>(-0.0,-0.0))) );
}
