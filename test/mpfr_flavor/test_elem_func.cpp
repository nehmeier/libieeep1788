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

#define BOOST_TEST_MODULE "Forward elementary functions [inf-sup-interval, mpfr_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include "p1788/p1788.hpp"


template<typename T>
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes>;

template<typename T>
using I = p1788::infsup::interval<T, flavor>;


BOOST_AUTO_TEST_CASE(minimal_pos_test)
{
    BOOST_CHECK_EQUAL( pos(I<double>(1.0,2.0)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( +I<double>(1.0,2.0), I<double>(1.0,2.0) );
}

BOOST_AUTO_TEST_CASE(minimal_neg_test)
{
    BOOST_CHECK_EQUAL( neg(I<double>(1.0,2.0)), I<double>(-2.0,-1.0) );
    BOOST_CHECK_EQUAL( -I<double>(1.0,2.0), I<double>(-2.0,-1.0) );
}

BOOST_AUTO_TEST_CASE(minimal_add_test)
{
    BOOST_CHECK_EQUAL( add(I<double>(1.0,2.0), I<double>(3.0,4.0)), I<double>(4.0,6.0) );
//    BOOST_CHECK_EQUAL( p1788::infsup::add<I<float>>(I<double>(1.0,2.0), I<float>(3.0,4.0)), I<float>(4.0,6.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) + I<double>(3.0,4.0), I<double>(4.0,6.0) );
}

BOOST_AUTO_TEST_CASE(minimal_sub_test)
{
    BOOST_CHECK_EQUAL( sub(I<double>(1.0,2.0), I<double>(3.0,4.0)), I<double>(-3.0,-1.0) );
//    BOOST_CHECK_EQUAL( p1788::infsup::sub<I<float>>(I<double>(1.0,2.0), I<float>(3.0,4.0)), I<float>(-3.0,-1.0) );
    BOOST_CHECK_EQUAL( I<double>(1.0,2.0) - I<double>(3.0,4.0), I<double>(-3.0,-1.0) );
}

BOOST_AUTO_TEST_CASE(minimal_mul_test)
{
    BOOST_CHECK(true);
}


BOOST_AUTO_TEST_CASE(minimal_div_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_recip_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_sqr_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_sqrt_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_fma_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_interval_case_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_pown_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_pow_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_exp_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_exp2_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_exp10_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_log_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_log2_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_log10_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_sin_test)
{
    BOOST_CHECK_EQUAL( sin(I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( sin(I<double>::entire()), I<double>(-1.0,1.0) );

    BOOST_CHECK_EQUAL( sin(I<double>(0.0, 3.14)), I<double>(0.0,1.0) );
    BOOST_CHECK_EQUAL( sin(I<double>(-3.14, 0.0)), I<double>(-1.0,0.0) );

    BOOST_CHECK_EQUAL( sin(I<double>(0.0, 6.29)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( sin(I<double>(-6.29, 0.0)), I<double>(-1.0,1.0) );

    BOOST_CHECK_EQUAL( sin(I<double>(0.0, 6.28)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( sin(I<double>(-6.28, 0.0)), I<double>(-1.0,1.0) );
}

BOOST_AUTO_TEST_CASE(minimal_cos_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_tan_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_asin_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_acos_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_atan_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_atan2_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_sinh_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_cosh_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_tanh_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_asinh_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_acosh_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_atanh_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_sign_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_ceil_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_floor_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_trunc_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_round_ties_to_even_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_round_ties_to_away_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_abs_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_min_test)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(minimal_max_test)
{
    BOOST_CHECK(true);
}
