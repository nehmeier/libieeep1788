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
//   UnF<double>::less required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#define BOOST_TEST_MODULE "Flavor: Recommended boolean functions of intervals [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include "p1788/exception/exception.hpp"
#include "p1788/decoration/decoration.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"
#include "test/util/mpfr_bin_ieee754_flavor_io_test_util.hpp"

#include <limits>

template<typename T>
using F = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>;

template<typename T>
using REP = typename F<T>::representation;

template<typename T>
using REP_DEC = typename F<T>::representation_dec;

typedef p1788::decoration::decoration DEC;

const double INF_D = std::numeric_limits<double>::infinity();
const double NaN_D = std::numeric_limits<double>::quiet_NaN();
const double MAX_D = std::numeric_limits<double>::max();
const double MIN_D = std::numeric_limits<double>::min();

const double INF_F = std::numeric_limits<float>::infinity();
const double NaN_F = std::numeric_limits<float>::quiet_NaN();
const double MAX_F = std::numeric_limits<float>::max();
const double MIN_F = std::numeric_limits<float>::min();

BOOST_AUTO_TEST_CASE(minimal_is_common_interval_test)
{
    p1788::exception::clear();

    BOOST_CHECK(F<double>::is_common_interval(REP<double>(-27.0,-27.0)));
    BOOST_CHECK(F<double>::is_common_interval(REP<double>(-27.0, 0.0)));
    BOOST_CHECK(F<double>::is_common_interval(REP<double>(0.0,0.0)));
    BOOST_CHECK(F<double>::is_common_interval(REP<double>(-0.0,-0.0)));
    BOOST_CHECK(F<double>::is_common_interval(REP<double>(-0.0,0.0)));
    BOOST_CHECK(F<double>::is_common_interval(REP<double>(0.0,-0.0)));
    BOOST_CHECK(F<double>::is_common_interval(REP<double>(5.0, 12.4)));
    BOOST_CHECK(F<double>::is_common_interval(REP<double>(-MAX_D, MAX_D)));

    BOOST_CHECK(!F<double>::is_common_interval(REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(!F<double>::is_common_interval(REP<double>(NaN_D, NaN_D)));
    BOOST_CHECK(!F<double>::is_common_interval(REP<double>(-INF_D, 0.0)));
    BOOST_CHECK(!F<double>::is_common_interval(REP<double>(0.0, INF_D)));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_common_interval(REP<double>(0.0, -INF_D)));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::is_common_interval(REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_is_common_interval_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(-27.0,-27.0), DEC::com)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(-27.0, 0.0), DEC::com)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(0.0,0.0), DEC::com)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::com)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(-0.0,0.0), DEC::com)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(0.0,-0.0), DEC::com)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(5.0, 12.4), DEC::com)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(-MAX_D, MAX_D), DEC::com)));

    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(-27.0,-27.0), DEC::trv)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(-27.0, 0.0), DEC::def)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(0.0,0.0), DEC::dac)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(-0.0,0.0), DEC::def)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(0.0,-0.0), DEC::dac)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(5.0, 12.4), DEC::def)));
    BOOST_CHECK(F<double>::is_common_interval( REP_DEC<double>(REP<double>(-MAX_D, MAX_D), DEC::trv)));

    BOOST_CHECK(!F<double>::is_common_interval( REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac)));
    BOOST_CHECK(!F<double>::is_common_interval( REP_DEC<double>(REP<double>(NaN_D, NaN_D), DEC::ill)));
    BOOST_CHECK(!F<double>::is_common_interval( REP_DEC<double>(REP<double>(NaN_D, NaN_D), DEC::trv)));
    BOOST_CHECK(!F<double>::is_common_interval( REP_DEC<double>(REP<double>(-INF_D, 0.0), DEC::trv)));
    BOOST_CHECK(!F<double>::is_common_interval( REP_DEC<double>(REP<double>(0.0, INF_D), DEC::def)));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_common_interval(REP_DEC<double>(REP<double>(27.0,-27.0), DEC::com)));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::is_common_interval(REP_DEC<double>(REP<double>(27.0,-27.0), DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_is_singleton_test)
{
    p1788::exception::clear();

    BOOST_CHECK(F<double>::is_singleton(REP<double>(-27.0,-27.0)));
    BOOST_CHECK(F<double>::is_singleton(REP<double>(-2.0, -2.0)));
    BOOST_CHECK(F<double>::is_singleton(REP<double>(12.0,12.0)));
    BOOST_CHECK(F<double>::is_singleton(REP<double>(17.1, 17.1)));
    BOOST_CHECK(F<double>::is_singleton(REP<double>(-0.0,-0.0)));
    BOOST_CHECK(F<double>::is_singleton(REP<double>(0.0,0.0)));
    BOOST_CHECK(F<double>::is_singleton(REP<double>(-0.0, 0.0)));
    BOOST_CHECK(F<double>::is_singleton(REP<double>(0.0, -0.0)));

    BOOST_CHECK(!F<double>::is_singleton(REP<double>(NaN_D,NaN_D)));
    BOOST_CHECK(!F<double>::is_singleton(REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(!F<double>::is_singleton(REP<double>(-1.0, 0.0)));
    BOOST_CHECK(!F<double>::is_singleton(REP<double>(-1.0, -0.5)));
    BOOST_CHECK(!F<double>::is_singleton(REP<double>(1.0, 2.0)));
    BOOST_CHECK(!F<double>::is_singleton(REP<double>(-INF_D,-MAX_D)));
    BOOST_CHECK(!F<double>::is_singleton(REP<double>(-1.0,INF_D)));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::is_singleton(REP<double>(1.0, 0.0)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::is_singleton(REP<double>(1.0, 0.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_is_singleton_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK(F<double>::is_singleton(REP_DEC<double>(REP<double>(-27.0,-27.0), DEC::def)));
    BOOST_CHECK(F<double>::is_singleton(REP_DEC<double>(REP<double>(-2.0, -2.0), DEC::trv)));
    BOOST_CHECK(F<double>::is_singleton(REP_DEC<double>(REP<double>(12.0,12.0), DEC::dac)));
    BOOST_CHECK(F<double>::is_singleton(REP_DEC<double>(REP<double>(17.1, 17.1), DEC::com)));
    BOOST_CHECK(F<double>::is_singleton(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::def)));
    BOOST_CHECK(F<double>::is_singleton(REP_DEC<double>(REP<double>(0.0,0.0), DEC::com)));
    BOOST_CHECK(F<double>::is_singleton(REP_DEC<double>(REP<double>(-0.0, 0.0), DEC::def)));
    BOOST_CHECK(F<double>::is_singleton(REP_DEC<double>(REP<double>(0.0, -0.0), DEC::dac)));

    BOOST_CHECK(!F<double>::is_singleton(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)));
    BOOST_CHECK(!F<double>::is_singleton(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)));
    BOOST_CHECK(!F<double>::is_singleton(REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def)));
    BOOST_CHECK(!F<double>::is_singleton(REP_DEC<double>(REP<double>(-1.0, 0.0), DEC::dac)));
    BOOST_CHECK(!F<double>::is_singleton(REP_DEC<double>(REP<double>(-1.0, -0.5), DEC::com)));
    BOOST_CHECK(!F<double>::is_singleton(REP_DEC<double>(REP<double>(1.0, 2.0), DEC::def)));
    BOOST_CHECK(!F<double>::is_singleton(REP_DEC<double>(REP<double>(-INF_D,-MAX_D), DEC::dac)));
    BOOST_CHECK(!F<double>::is_singleton(REP_DEC<double>(REP<double>(-1.0,INF_D), DEC::trv)));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::is_singleton(REP_DEC<double>(REP<double>(1.0, -0.5), DEC::com)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::is_singleton(REP_DEC<double>(REP<double>(-1.0, -0.5), DEC::ill)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_is_member_test)
{
    p1788::exception::clear();

    BOOST_CHECK(F<double>::is_member(-27.0, REP<double>(-27.0,-27.0)));
    BOOST_CHECK(F<double>::is_member(-27.0, REP<double>(-27.0, 0.0)));
    BOOST_CHECK(F<double>::is_member(-7.0, REP<double>(-27.0, 0.0)));
    BOOST_CHECK(F<double>::is_member(0.0, REP<double>(-27.0, 0.0)));
    BOOST_CHECK(F<double>::is_member(-0.0, REP<double>(0.0,0.0)));
    BOOST_CHECK(F<double>::is_member(0.0, REP<double>(0.0,0.0)));
    BOOST_CHECK(F<double>::is_member(0.0, REP<double>(-0.0,-0.0)));
    BOOST_CHECK(F<double>::is_member(0.0, REP<double>(-0.0,0.0)));
    BOOST_CHECK(F<double>::is_member(0.0, REP<double>(0.0,-0.0)));
    BOOST_CHECK(F<double>::is_member(5.0, REP<double>(5.0, 12.4)));
    BOOST_CHECK(F<double>::is_member(6.3, REP<double>(5.0, 12.4)));
    BOOST_CHECK(F<double>::is_member(12.4, REP<double>(5.0, 12.4)));
    BOOST_CHECK(F<double>::is_member(0.0, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(F<double>::is_member(5.0, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(F<double>::is_member(6.3, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(F<double>::is_member(12.4, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(F<double>::is_member(MAX_D, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(F<double>::is_member(-MAX_D, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(F<double>::is_member(MIN_D, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(F<double>::is_member(-MIN_D, REP<double>(-INF_D,INF_D)));

    BOOST_CHECK(!F<double>::is_member(-71.0, REP<double>(-27.0, 0.0)));
    BOOST_CHECK(!F<double>::is_member(0.1, REP<double>(-27.0, 0.0)));
    BOOST_CHECK(!F<double>::is_member(-0.01, REP<double>(0.0,0.0)));
    BOOST_CHECK(!F<double>::is_member(0.000001, REP<double>(0.0,0.0)));
    BOOST_CHECK(!F<double>::is_member(111110.0, REP<double>(-0.0,-0.0)));
    BOOST_CHECK(!F<double>::is_member(4.9, REP<double>(5.0, 12.4)));
    BOOST_CHECK(!F<double>::is_member(-6.3, REP<double>(5.0, 12.4)));
    BOOST_CHECK(!F<double>::is_member(0.0, REP<double>(NaN_D,NaN_D)));
    BOOST_CHECK(!F<double>::is_member(-4535.3, REP<double>(NaN_D,NaN_D)));
    BOOST_CHECK(!F<double>::is_member(-INF_D, REP<double>(NaN_D,NaN_D)));
    BOOST_CHECK(!F<double>::is_member(INF_D, REP<double>(NaN_D,NaN_D)));
    BOOST_CHECK(!F<double>::is_member(NaN_D, REP<double>(NaN_D,NaN_D)));
    BOOST_CHECK(!F<double>::is_member(-INF_D, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(!F<double>::is_member(INF_D, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(!F<double>::is_member(NaN_D, REP<double>(-INF_D,INF_D)));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::is_member(4.9, REP<double>(5.0, -12.4)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::is_member(4.9, REP<double>(NaN_D, 12.4)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_is_member_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK(F<double>::is_member(-27.0, REP_DEC<double>(REP<double>(-27.0,-27.0), DEC::trv)));
    BOOST_CHECK(F<double>::is_member(-27.0, REP_DEC<double>(REP<double>(-27.0, 0.0), DEC::def)));
    BOOST_CHECK(F<double>::is_member(-7.0, REP_DEC<double>(REP<double>(-27.0, 0.0), DEC::dac)));
    BOOST_CHECK(F<double>::is_member(0.0, REP_DEC<double>(REP<double>(-27.0, 0.0), DEC::com)));
    BOOST_CHECK(F<double>::is_member(-0.0, REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)));
    BOOST_CHECK(F<double>::is_member(0.0, REP_DEC<double>(REP<double>(0.0,0.0), DEC::def)));
    BOOST_CHECK(F<double>::is_member(0.0, REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::dac)));
    BOOST_CHECK(F<double>::is_member(0.0, REP_DEC<double>(REP<double>(-0.0,0.0), DEC::com)));
    BOOST_CHECK(F<double>::is_member(0.0, REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)));
    BOOST_CHECK(F<double>::is_member(5.0, REP_DEC<double>(REP<double>(5.0, 12.4), DEC::def)));
    BOOST_CHECK(F<double>::is_member(6.3, REP_DEC<double>(REP<double>(5.0, 12.4), DEC::dac)));
    BOOST_CHECK(F<double>::is_member(12.4, REP_DEC<double>(REP<double>(5.0, 12.4), DEC::com)));
    BOOST_CHECK(F<double>::is_member(0.0, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv)));
    BOOST_CHECK(F<double>::is_member(5.0, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def)));
    BOOST_CHECK(F<double>::is_member(6.3, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac)));
    BOOST_CHECK(F<double>::is_member(12.4, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv)));
    BOOST_CHECK(F<double>::is_member(MAX_D, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def)));
    BOOST_CHECK(F<double>::is_member(-MAX_D, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac)));
    BOOST_CHECK(F<double>::is_member(MIN_D, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv)));
    BOOST_CHECK(F<double>::is_member(-MIN_D, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def)));

    BOOST_CHECK(!F<double>::is_member(-71.0, REP_DEC<double>(REP<double>(-27.0, 0.0), DEC::trv)));
    BOOST_CHECK(!F<double>::is_member(0.1, REP_DEC<double>(REP<double>(-27.0, 0.0), DEC::def)));
    BOOST_CHECK(!F<double>::is_member(-0.01, REP_DEC<double>(REP<double>(0.0,0.0), DEC::dac)));
    BOOST_CHECK(!F<double>::is_member(0.000001, REP_DEC<double>(REP<double>(0.0,0.0), DEC::com)));
    BOOST_CHECK(!F<double>::is_member(111110.0, REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)));
    BOOST_CHECK(!F<double>::is_member(4.9, REP_DEC<double>(REP<double>(5.0, 12.4), DEC::def)));
    BOOST_CHECK(!F<double>::is_member(-6.3, REP_DEC<double>(REP<double>(5.0, 12.4), DEC::dac)));
    BOOST_CHECK(!F<double>::is_member(0.0, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)));
    BOOST_CHECK(!F<double>::is_member(0.0, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)));
    BOOST_CHECK(!F<double>::is_member(-4535.3, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)));
    BOOST_CHECK(!F<double>::is_member(-4535.3, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)));
    BOOST_CHECK(!F<double>::is_member(-INF_D, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)));
    BOOST_CHECK(!F<double>::is_member(-INF_D, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)));
    BOOST_CHECK(!F<double>::is_member(INF_D, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)));
    BOOST_CHECK(!F<double>::is_member(INF_D, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)));
    BOOST_CHECK(!F<double>::is_member(NaN_D, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)));
    BOOST_CHECK(!F<double>::is_member(NaN_D, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)));
    BOOST_CHECK(!F<double>::is_member(-INF_D, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv)));
    BOOST_CHECK(!F<double>::is_member(INF_D, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def)));
    BOOST_CHECK(!F<double>::is_member(NaN_D, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac)));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::is_member(-0.01, REP_DEC<double>(REP<double>(10.0,0.0), DEC::dac)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::is_member(-0.01, REP_DEC<double>(REP<double>(0.0,INF_D), DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_mixedtype_is_member_test)
{
    p1788::exception::clear();

    BOOST_CHECK(F<double>::is_member(-27.0f, REP<double>(-27.0,-27.0)));
    BOOST_CHECK(F<double>::is_member(-27.0, REP<double>(-27.0, 0.0)));
    BOOST_CHECK(F<double>::is_member(-7.0f, REP<double>(-27.0, 0.0)));
    BOOST_CHECK(F<double>::is_member(0.0f, REP<double>(-27.0, 0.0)));
    BOOST_CHECK(F<double>::is_member(-0.0f, REP<double>(0.0,0.0)));
    BOOST_CHECK(F<double>::is_member(0.0f, REP<double>(0.0,0.0)));
    BOOST_CHECK(F<double>::is_member(0.0f, REP<double>(-0.0,-0.0)));
    BOOST_CHECK(F<double>::is_member(0.0f, REP<double>(-0.0,0.0)));
    BOOST_CHECK(F<double>::is_member(0.0f, REP<double>(0.0,-0.0)));
    BOOST_CHECK(F<float>::is_member(5.0, REP<float>(5.0f, 12.4f)));
    BOOST_CHECK(F<float>::is_member(6.3, REP<float>(5.0f, 12.4f)));
    BOOST_CHECK(F<float>::is_member(0.0, REP<float>(-INF_F,INF_F)));
    BOOST_CHECK(F<float>::is_member(5.0, REP<float>(-INF_F,INF_F)));
    BOOST_CHECK(F<double>::is_member(6.3, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(F<double>::is_member(12.4, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(F<double>::is_member(MAX_D, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(F<float>::is_member(-MAX_D, REP<float>(-INF_F,INF_F)));
    BOOST_CHECK(F<double>::is_member(MIN_D, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(F<float>::is_member(-MIN_D, REP<float>(-INF_F,INF_F)));

    BOOST_CHECK(!F<float>::is_member(12.4, REP<float>(5.0f, 12.4f)));
    BOOST_CHECK(!F<double>::is_member(-71.0f, REP<double>(-27.0, 0.0)));
    BOOST_CHECK(!F<double>::is_member(0.1f, REP<double>(-27.0, 0.0)));
    BOOST_CHECK(!F<double>::is_member(-0.01f, REP<double>(0.0,0.0)));
    BOOST_CHECK(!F<double>::is_member(0.000001f, REP<double>(0.0,0.0)));
    BOOST_CHECK(!F<float>::is_member(111110.0, REP<float>(-0.0f,-0.0f)));
    BOOST_CHECK(!F<double>::is_member(4.9f, REP<double>(5.0, 12.4)));
    BOOST_CHECK(!F<double>::is_member(-6.3f, REP<double>(5.0, 12.4)));
    BOOST_CHECK(!F<double>::is_member(0.0f, REP<double>(NaN_D,NaN_D)));
    BOOST_CHECK(!F<double>::is_member(-4535.3f, REP<double>(NaN_D,NaN_D)));
    BOOST_CHECK(!F<float>::is_member(-INF_D, REP<float>(NaN_F,NaN_F)));
    BOOST_CHECK(!F<float>::is_member(INF_D, REP<float>(NaN_F,NaN_F)));
    BOOST_CHECK(!F<double>::is_member(NaN_F, REP<double>(NaN_D,NaN_D)));
    BOOST_CHECK(!F<double>::is_member(-INF_F, REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(!F<float>::is_member(INF_D, REP<float>(-INF_F,INF_F)));
    BOOST_CHECK(!F<float>::is_member(NaN_D, REP<float>(-INF_F,INF_F)));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::is_member(-71.0f, REP<double>(27.0, 0.0)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::is_member(-71.0f, REP<double>(27.0, -20.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_mixedtype_is_member_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK(F<double>::is_member(-27.0f, REP_DEC<double>(REP<double>(-27.0,-27.0), DEC::trv)));
    BOOST_CHECK(F<double>::is_member(-27.0, REP_DEC<double>(REP<double>(-27.0, 0.0), DEC::def)));
    BOOST_CHECK(F<double>::is_member(-7.0f, REP_DEC<double>(REP<double>(-27.0, 0.0), DEC::dac)));
    BOOST_CHECK(F<double>::is_member(0.0f, REP_DEC<double>(REP<double>(-27.0, 0.0), DEC::com)));
    BOOST_CHECK(F<double>::is_member(-0.0f, REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)));
    BOOST_CHECK(F<double>::is_member(0.0f, REP_DEC<double>(REP<double>(0.0,0.0), DEC::def)));
    BOOST_CHECK(F<double>::is_member(0.0f, REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::dac)));
    BOOST_CHECK(F<double>::is_member(0.0f, REP_DEC<double>(REP<double>(-0.0,0.0), DEC::com)));
    BOOST_CHECK(F<double>::is_member(0.0f, REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)));
    BOOST_CHECK(F<float>::is_member(5.0, REP_DEC<double>(REP<float>(5.0f, 12.4f), DEC::def)));
    BOOST_CHECK(F<float>::is_member(6.3, REP_DEC<double>(REP<float>(5.0f, 12.4f), DEC::dac)));
    BOOST_CHECK(F<float>::is_member(0.0, REP_DEC<double>(REP<float>(-INF_F,INF_F), DEC::trv)));
    BOOST_CHECK(F<float>::is_member(5.0, REP_DEC<double>(REP<float>(-INF_F,INF_F), DEC::def)));
    BOOST_CHECK(F<double>::is_member(6.3, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac)));
    BOOST_CHECK(F<double>::is_member(12.4, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv)));
    BOOST_CHECK(F<double>::is_member(MAX_D, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def)));
    BOOST_CHECK(F<float>::is_member(-MAX_D, REP_DEC<double>(REP<float>(-INF_F,INF_F), DEC::dac)));
    BOOST_CHECK(F<double>::is_member(MIN_D, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv)));
    BOOST_CHECK(F<float>::is_member(-MIN_D, REP_DEC<double>(REP<float>(-INF_F,INF_F), DEC::def)));

    BOOST_CHECK(!F<float>::is_member(12.4, REP_DEC<double>(REP<float>(5.0f, 12.4f), DEC::trv)));
    BOOST_CHECK(!F<double>::is_member(-71.0f, REP_DEC<double>(REP<double>(-27.0, 0.0), DEC::def)));
    BOOST_CHECK(!F<double>::is_member(0.1f, REP_DEC<double>(REP<double>(-27.0, 0.0), DEC::dac)));
    BOOST_CHECK(!F<double>::is_member(-0.01f, REP_DEC<double>(REP<double>(0.0,0.0), DEC::com)));
    BOOST_CHECK(!F<double>::is_member(0.000001f, REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)));
    BOOST_CHECK(!F<float>::is_member(111110.0, REP_DEC<double>(REP<float>(-0.0f,-0.0f), DEC::def)));
    BOOST_CHECK(!F<double>::is_member(4.9f, REP_DEC<double>(REP<double>(5.0, 12.4), DEC::dac)));
    BOOST_CHECK(!F<double>::is_member(-6.3f, REP_DEC<double>(REP<double>(5.0, 12.4), DEC::com)));
    BOOST_CHECK(!F<double>::is_member(0.0f, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)));
    BOOST_CHECK(!F<double>::is_member(0.0f, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)));
    BOOST_CHECK(!F<double>::is_member(-4535.3f, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)));
    BOOST_CHECK(!F<double>::is_member(-4535.3f, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)));
    BOOST_CHECK(!F<float>::is_member(-INF_D, REP_DEC<double>(REP<float>(NaN_F,NaN_F), DEC::trv)));
    BOOST_CHECK(!F<float>::is_member(-INF_D, REP_DEC<double>(REP<float>(NaN_F,NaN_F), DEC::ill)));
    BOOST_CHECK(!F<float>::is_member(INF_D, REP_DEC<double>(REP<float>(NaN_F,NaN_F), DEC::trv)));
    BOOST_CHECK(!F<float>::is_member(INF_D, REP_DEC<double>(REP<float>(NaN_F,NaN_F), DEC::ill)));
    BOOST_CHECK(!F<double>::is_member(NaN_F, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)));
    BOOST_CHECK(!F<double>::is_member(NaN_F, REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)));
    BOOST_CHECK(!F<double>::is_member(-INF_F, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv)));
    BOOST_CHECK(!F<float>::is_member(INF_D, REP_DEC<double>(REP<float>(-INF_F,INF_F), DEC::def)));
    BOOST_CHECK(!F<float>::is_member(NaN_D, REP_DEC<double>(REP<float>(-INF_F,INF_F), DEC::dac)));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( !F<double>::is_member(0.1f, REP_DEC<double>(REP<double>(-27.0, 0.0), DEC::ill)) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::is_member(0.1f, REP_DEC<double>(REP<double>(27.0, 0.0), DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

