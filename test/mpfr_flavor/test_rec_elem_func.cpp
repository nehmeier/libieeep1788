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

#define BOOST_TEST_MODULE "Recommended forward elementary functions on intervals [inf-sup-interval, mpfr_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include "p1788/p1788.hpp"

template<typename T>
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes>;

template<typename T>
using interval = p1788::infsup::interval<T, flavor>;


BOOST_AUTO_TEST_CASE(minimal_rootn_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_expm1_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_exp2m1_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_exp10m1_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_logp1_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_log2p1_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_log10p1_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_compoundm1_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_hypot_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_r_sqrt_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_sin_pi_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_cos_pi_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_tan_pi_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_asin_pi_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_acos_pi_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_atan_pi_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_atan2_pi_test)
{
    BOOST_CHECK(false);
}
