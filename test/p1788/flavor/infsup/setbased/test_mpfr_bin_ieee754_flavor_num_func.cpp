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
//   UnF<double>::less required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#define BOOST_TEST_MODULE "Flavor: Numeric functions on intervals [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"
#include "test/util/mpfr_bin_ieee754_flavor_io_test_util.hpp"

#include <string>
#include <limits>
#include <cmath>

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
const double DNORM_MIN_D = std::numeric_limits<double>::denorm_min();

const float INF_F = std::numeric_limits<float>::infinity();
const float NaN_F = std::numeric_limits<float>::quiet_NaN();
const float MAX_F = std::numeric_limits<float>::max();
const float DNORM_MIN_F = std::numeric_limits<float>::denorm_min();

BOOST_AUTO_TEST_CASE(minimal_inf_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(NaN_D,NaN_D)), +INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(-INF_D,+INF_D)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(1.0,2.0)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(-3.0,-2.0)), -3.0 );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(-INF_D,2.0)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(-INF_D,0.0)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(-INF_D,-0.0)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(-2.0,INF_D)), -2.0 );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(0.0,INF_D)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP<double>(0.0,INF_D))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(-0.0,INF_D)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP<double>(-0.0,INF_D))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(-0.0,0.0)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP<double>(-0.0,0.0))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(0.0,-0.0)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP<double>(0.0,-0.0))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(0.0,0.0)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP<double>(0.0,0.0))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP<double>(-0.0,-0.0)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP<double>(-0.0,-0.0))));

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::inf(REP<double>(1.0,-2.0)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::inf(REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_inf_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(NaN_D,NaN_D)), +INF_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(-INF_D,+INF_D)), -INF_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(1.0,2.0)), 1.0f );
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(-3.0,-2.0)), -3.0f );
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(-INF_D,2.0)), -INF_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(-INF_D,0.0)), -INF_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(-INF_D,-0.0)), -INF_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(-2.0,INF_D)), -2.0f );
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(0.0,INF_D)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP<double>(0.0,INF_D))));
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(-0.0,INF_D)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP<double>(-0.0,INF_D))));
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(-0.0,0.0)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP<double>(-0.0,0.0))));
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(0.0,-0.0)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP<double>(0.0,-0.0))));
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(0.0,0.0)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP<double>(0.0,0.0))));
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(-0.0,-0.0)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP<double>(-0.0,-0.0))));

    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(-DNORM_MIN_D,DNORM_MIN_D)), -DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(-DNORM_MIN_D,-DNORM_MIN_D)), -DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(DNORM_MIN_D,DNORM_MIN_D)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP<double>(DNORM_MIN_D,DNORM_MIN_D))));
    BOOST_CHECK_EQUAL( F<float>::inf(REP<double>(-MAX_D,MAX_D)), -INF_F );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<float>::inf(REP<double>(1.0,-2.0)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::inf(REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);


    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(NaN_F,NaN_F)), +INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(-INF_F,+INF_F)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(1.0f,2.0f)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(-3.0f,-2.0f)), -3.0 );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(-INF_F,2.0f)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(-INF_F,0.0f)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(-INF_F,-0.0f)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(-2.0f,INF_F)), -2.0 );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(0.0f,INF_F)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP<float>(0.0f,INF_F))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(-0.0f,INF_F)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP<float>(-0.0f,INF_F))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(-0.0f,0.0f)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP<float>(-0.0f,0.0f))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(0.0f,-0.0f)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP<float>(0.0f,-0.0f))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(0.0f,0.0f)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP<float>(0.0f,0.0f))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(-0.0f,-0.0f)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP<float>(-0.0f,-0.0f))));

    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(-DNORM_MIN_F,DNORM_MIN_F)), -DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(-DNORM_MIN_F,-DNORM_MIN_F)), -DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(DNORM_MIN_F,DNORM_MIN_F)), DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<double>::inf(REP<float>(-MAX_F,MAX_F)), -MAX_F );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::inf(REP<float>(1.0f,-2.0f)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::inf(REP<float>(1.0f,-2.0f)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_inf_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan(F<double>::inf(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill))));

    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)), +INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::def)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(1.0,2.0), DEC::com)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(-3.0,-2.0), DEC::trv)), -3.0 );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(-INF_D,2.0), DEC::dac)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(-INF_D,0.0), DEC::def)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(-INF_D,-0.0), DEC::trv)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(-2.0,INF_D), DEC::trv)), -2.0 );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(0.0,INF_D), DEC::def)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP_DEC<double>(REP<double>(0.0,INF_D), DEC::def))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(-0.0,INF_D), DEC::trv)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP_DEC<double>(REP<double>(-0.0,INF_D), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::dac)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv))));

    BOOST_CHECK(!p1788::exception::invalid_operand());


    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::inf(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::com)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::inf(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_inf_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan(F<float>::inf(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill))));

    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)), +INF_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::def)), -INF_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(1.0,2.0), DEC::com)), 1.0f );
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(-3.0,-2.0), DEC::trv)), -3.0f );
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(-INF_D,2.0), DEC::dac)), -INF_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(-INF_D,0.0), DEC::def)), -INF_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(-INF_D,-0.0), DEC::trv)), -INF_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(-2.0,INF_D), DEC::trv)), -2.0f );
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(0.0,INF_D), DEC::def)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP_DEC<double>(REP<double>(0.0,INF_D), DEC::def))));
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(-0.0,INF_D), DEC::trv)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP_DEC<double>(REP<double>(-0.0,INF_D), DEC::trv))));
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::dac)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv))));

    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(-DNORM_MIN_D,DNORM_MIN_D), DEC::com)), -DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(-DNORM_MIN_D,-DNORM_MIN_D), DEC::trv)), -DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(DNORM_MIN_D,DNORM_MIN_D), DEC::def)), -0.0f );
    BOOST_CHECK( std::signbit(F<float>::inf(REP_DEC<double>(REP<double>(DNORM_MIN_D,DNORM_MIN_D), DEC::dac))));
    BOOST_CHECK_EQUAL( F<float>::inf(REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::trv)), -INF_F );


    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<float>::inf(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::com)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::inf(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);

    BOOST_CHECK( std::isnan(F<double>::inf(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill))));

    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv)), +INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::def)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::com)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(-3.0f,-2.0f), DEC::trv)), -3.0 );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(-INF_F,2.0f), DEC::dac)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(-INF_F,0.0f), DEC::def)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(-INF_F,-0.0f), DEC::trv)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(-2.0f,INF_F), DEC::trv)), -2.0 );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(0.0f,INF_F), DEC::def)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP_DEC<float>(REP<float>(0.0f,INF_F), DEC::def))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(-0.0f,INF_F), DEC::trv)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP_DEC<float>(REP<float>(-0.0f,INF_F), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::dac)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::trv)), -0.0 );
    BOOST_CHECK( std::signbit(F<double>::inf(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::trv))));

    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(-DNORM_MIN_F,DNORM_MIN_F), DEC::com)), -DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(-DNORM_MIN_F,-DNORM_MIN_F), DEC::trv)), -DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(DNORM_MIN_F,DNORM_MIN_F), DEC::def)), DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<double>::inf(REP_DEC<float>(REP<float>(-MAX_F,MAX_F), DEC::trv)), -MAX_F );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::inf(REP_DEC<float>(REP<float>(1.0f,-2.0f), DEC::com)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::inf(REP_DEC<float>(REP<float>(1.0f,-2.0f), DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}



BOOST_AUTO_TEST_CASE(minimal_sup_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(NaN_D,NaN_D)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(-INF_D,+INF_D)), +INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(1.0,2.0)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(-3.0,-2.0)), -2.0 );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(-INF_D,2.0)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(-INF_D,0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP<double>(-INF_D,0.0))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(-INF_D,-0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP<double>(-INF_D,-0.0))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(-2.0,INF_D)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(0.0,INF_D)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(-0.0,INF_D)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(-0.0,0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP<double>(-0.0,0.0))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(0.0,-0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP<double>(0.0,-0.0))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(0.0,0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP<double>(0.0,0.0))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP<double>(-0.0,-0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP<double>(-0.0,-0.0))));

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::sup(REP<double>(1.0,-2.0)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::sup(REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_sup_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(NaN_D,NaN_D)), -INF_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(-INF_D,+INF_D)), +INF_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(1.0,2.0)), 2.0f );
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(-3.0,-2.0)), -2.0f );
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(-INF_D,2.0)), 2.0f );
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(-INF_D,0.0)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP<double>(-INF_D,0.0))));
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(-INF_D,-0.0)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP<double>(-INF_D,-0.0))));
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(-2.0,INF_D)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(0.0,INF_D)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(-0.0,INF_D)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(-0.0,0.0)), +0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP<double>(-0.0,0.0))));
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(0.0,-0.0)), +0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP<double>(0.0,-0.0))));
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(0.0,0.0)), +0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP<double>(0.0,0.0))));
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(-0.0,-0.0)), +0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP<double>(-0.0,-0.0))));

    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(-DNORM_MIN_D,DNORM_MIN_D)), DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(-DNORM_MIN_D,-DNORM_MIN_D)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP<double>(-DNORM_MIN_D,-DNORM_MIN_D))));
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(DNORM_MIN_D,DNORM_MIN_D)), DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP<double>(-MAX_D,MAX_D)), INF_F );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<float>::sup(REP<double>(1.0,-2.0)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::sup(REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);

    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(NaN_F,NaN_F)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(-INF_F,+INF_F)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(1.0f,2.0f)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(-3.0f,-2.0f)), -2.0 );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(-INF_F,2.0f)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(-INF_F,0.0f)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP<float>(-INF_F,0.0f))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(-INF_F,-0.0f)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP<float>(-INF_F,-0.0f))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(-2.0f,INF_F)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(0.0f,INF_F)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(-0.0f,INF_F)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(-0.0f,0.0f)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP<float>(-0.0f,0.0f))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(0.0f,-0.0f)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP<float>(0.0f,-0.0f))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(0.0f,0.0f)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP<float>(0.0f,0.0f))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(-0.0f,-0.0f)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP<float>(-0.0f,-0.0f))));

    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(-DNORM_MIN_F,DNORM_MIN_F)), DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(-DNORM_MIN_F,-DNORM_MIN_F)), -DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(DNORM_MIN_F,DNORM_MIN_F)), DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<double>::sup(REP<float>(-MAX_F,MAX_F)), MAX_F );


    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::sup(REP<float>(1.0f,-2.0f)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::sup(REP<float>(1.0f,-2.0f)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_sup_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan(F<double>::sup(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill))));

    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::def)), +INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(1.0,2.0), DEC::com)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(-3.0,-2.0), DEC::trv)), -2.0 );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(-INF_D,2.0), DEC::dac)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(-INF_D,0.0), DEC::def)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP_DEC<double>(REP<double>(-INF_D,0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(-INF_D,-0.0), DEC::trv)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP_DEC<double>(REP<double>(-INF_D,0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(-2.0,INF_D), DEC::trv)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(0.0,INF_D), DEC::def)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(-0.0,INF_D), DEC::trv)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::dac)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv))));

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::sup(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::com)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::sup(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_sup_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan(F<float>::sup(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill))));

    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)), -INF_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::def)), +INF_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(1.0,2.0), DEC::com)), 2.0f );
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(-3.0,-2.0), DEC::trv)), -2.0f );
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(-INF_D,2.0), DEC::dac)), 2.0f );
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(-INF_D,0.0), DEC::def)), +0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP_DEC<double>(REP<double>(-INF_D,0.0), DEC::def))));
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(-INF_D,-0.0), DEC::trv)), +0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP_DEC<double>(REP<double>(-INF_D,-0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(-2.0,INF_D), DEC::trv)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(0.0,INF_D), DEC::def)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(-0.0,INF_D), DEC::trv)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::dac)), +0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)), +0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)), +0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)), +0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv))));

    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(-DNORM_MIN_D,DNORM_MIN_D), DEC::com)), DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(-DNORM_MIN_D,-DNORM_MIN_D), DEC::trv)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::sup(REP_DEC<double>(REP<double>(-DNORM_MIN_D,-DNORM_MIN_D), DEC::trv))));
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(DNORM_MIN_D,DNORM_MIN_D), DEC::def)), DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<float>::sup(REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::trv)), INF_F );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<float>::sup(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::com)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::sup(REP_DEC<double>(REP<double>(1.0,-2.0), DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);


    BOOST_CHECK( std::isnan(F<double>::sup(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill))) );

    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv)), -INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::def)), +INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::com)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(-3.0f,-2.0f), DEC::trv)), -2.0 );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(-INF_F,2.0f), DEC::dac)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(-INF_F,0.0f), DEC::def)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP_DEC<float>(REP<float>(-INF_F,0.0), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(-INF_F,-0.0f), DEC::trv)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP_DEC<float>(REP<float>(-INF_F,-0.0f), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(-2.0f,INF_F), DEC::trv)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(0.0f,INF_F), DEC::def)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(-0.0f,INF_F), DEC::trv)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::dac)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv))));
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::trv)), +0.0 );
    BOOST_CHECK( !std::signbit(F<double>::sup(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::trv))));

    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(-DNORM_MIN_F,DNORM_MIN_F), DEC::com)), DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(-DNORM_MIN_F,-DNORM_MIN_F), DEC::trv)), -DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(DNORM_MIN_F,DNORM_MIN_F), DEC::def)), DNORM_MIN_F );
    BOOST_CHECK_EQUAL( F<double>::sup(REP_DEC<float>(REP<float>(-MAX_F,MAX_F), DEC::trv)), MAX_F );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::sup(REP_DEC<float>(REP<float>(1.0f,-2.0f), DEC::com)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::sup(REP_DEC<float>(REP<float>(1.0f,-2.0f), DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}



BOOST_AUTO_TEST_CASE(minimal_mid_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan(F<double>::mid(REP<double>(NaN_D,NaN_D))) );
    BOOST_CHECK_EQUAL( F<double>::mid(REP<double>(-INF_D,+INF_D)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid(REP<double>(-INF_D,+INF_D))) );
    BOOST_CHECK_EQUAL( F<double>::mid(REP<double>(-MAX_D,+MAX_D)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid(REP<double>(-MAX_D,+MAX_D))) );
    BOOST_CHECK_EQUAL( F<double>::mid(REP<double>(0.0,2.0)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::mid(REP<double>(2.0,2.0)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::mid(REP<double>(-2.0,2.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid(REP<double>(-2.0,2.0))) );
    BOOST_CHECK_EQUAL( F<double>::mid(REP<double>(0.0,INF_D)), MAX_D );
    BOOST_CHECK_EQUAL( F<double>::mid(REP<double>(-INF_D, 1.2)), -MAX_D );
    BOOST_CHECK_EQUAL( F<double>::mid(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022"))), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022")))) );
    BOOST_CHECK_EQUAL( F<double>::mid(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022"))), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")))) );
    BOOST_CHECK_EQUAL( F<double>::mid(REP<double>(std::stod("0X1.FFFFFFFFFFFFFP+1022"),std::stod("0X1.FFFFFFFFFFFFFP+1023"))), std::stod("0X1.7FFFFFFFFFFFFP+1023") );
    BOOST_CHECK_EQUAL( F<double>::mid(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000003P-1022"))), std::stod("0X0.0000000000002P-1022") );
    BOOST_CHECK_EQUAL( F<double>::mid(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022"))), std::stod("0X0.0000000000002P-1022") );


    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::mid(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::mid(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_mid_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan(F<float>::mid(REP<double>(NaN_D,NaN_D))) );
    BOOST_CHECK_EQUAL( F<float>::mid(REP<double>(-INF_D,+INF_D)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid(REP<double>(-INF_D,+INF_D))) );
    BOOST_CHECK_EQUAL( F<float>::mid(REP<double>(-MAX_D,+MAX_D)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid(REP<double>(-MAX_D,+MAX_D))) );
    BOOST_CHECK_EQUAL( F<float>::mid(REP<double>(0.0,2.0)), 1.0f );
    BOOST_CHECK_EQUAL( F<float>::mid(REP<double>(2.0,2.0)), 2.0f );
    BOOST_CHECK_EQUAL( F<float>::mid(REP<double>(-2.0,2.0)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid(REP<double>(-2.0,2.0))) );
    BOOST_CHECK_EQUAL( F<float>::mid(REP<double>(0.0,INF_D)), MAX_F );
    BOOST_CHECK_EQUAL( F<float>::mid(REP<double>(-INF_D, 1.2)), -MAX_F );
    BOOST_CHECK_EQUAL( F<float>::mid(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022"))), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022")))) );
    BOOST_CHECK_EQUAL( F<float>::mid(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022"))), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")))) );
    BOOST_CHECK_EQUAL( F<float>::mid(REP<double>(std::stod("0X1.FFFFD90000000P+0"),std::stod("0X1.FFFFD90000001P+0"))), std::stof("0X1.FFFFDAP+0") );
    BOOST_CHECK_EQUAL( F<float>::mid(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000003P-1022"))), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000003P-1022")))) );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<float>::mid(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::mid(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_mid_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan(F<double>::mid(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<double>::mid(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill))) );
    BOOST_CHECK_EQUAL( F<double>::mid(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::def)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::def))) );
    BOOST_CHECK_EQUAL( F<double>::mid(REP_DEC<double>(REP<double>(-MAX_D,+MAX_D),DEC::trv)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid(REP_DEC<double>(REP<double>(-MAX_D,+MAX_D),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<double>::mid(REP_DEC<double>(REP<double>(0.0,2.0),DEC::com)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::mid(REP_DEC<double>(REP<double>(2.0,2.0),DEC::dac)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::mid(REP_DEC<double>(REP<double>(-2.0,2.0),DEC::trv)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid(REP_DEC<double>(REP<double>(-2.0,2.0),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<double>::mid(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv)), MAX_D );
    BOOST_CHECK_EQUAL( F<double>::mid(REP_DEC<double>(REP<double>(-INF_D, 1.2),DEC::trv)), -MAX_D );
    BOOST_CHECK_EQUAL( F<double>::mid(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022")),DEC::trv)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022")),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<double>::mid(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")),DEC::trv)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<double>::mid(REP_DEC<double>(REP<double>(std::stod("0X1.FFFFFFFFFFFFFP+1022"),std::stod("0X1.FFFFFFFFFFFFFP+1023")),DEC::trv)), std::stod("0X1.7FFFFFFFFFFFFP+1023") );
    BOOST_CHECK_EQUAL( F<double>::mid(REP_DEC<double>(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000003P-1022")),DEC::trv)), std::stod("0X0.0000000000002P-1022") );
    BOOST_CHECK_EQUAL( F<double>::mid(REP_DEC<double>(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")),DEC::trv)), std::stod("0X0.0000000000002P-1022") );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::mid(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::mid(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_mid_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan(F<float>::mid(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<float>::mid(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill))) );
    BOOST_CHECK_EQUAL( F<float>::mid(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::def)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<float>::mid(REP_DEC<double>(REP<double>(-MAX_D,+MAX_D),DEC::trv)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid(REP_DEC<double>(REP<double>(-MAX_D,+MAX_D),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<float>::mid(REP_DEC<double>(REP<double>(0.0,2.0),DEC::com)), 1.0f );
    BOOST_CHECK_EQUAL( F<float>::mid(REP_DEC<double>(REP<double>(2.0,2.0),DEC::trv)), 2.0f );
    BOOST_CHECK_EQUAL( F<float>::mid(REP_DEC<double>(REP<double>(-2.0,2.0),DEC::trv)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid(REP_DEC<double>(REP<double>(-2.0,2.0),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<float>::mid(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv)), MAX_F );
    BOOST_CHECK_EQUAL( F<float>::mid(REP_DEC<double>(REP<double>(-INF_D, 1.2),DEC::trv)), -MAX_F );
    BOOST_CHECK_EQUAL( F<float>::mid(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022")),DEC::trv)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022")),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<float>::mid(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")),DEC::trv)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<float>::mid(REP_DEC<double>(REP<double>(std::stod("0X1.FFFFD90000000P+0"),std::stod("0X1.FFFFD90000001P+0")),DEC::trv)), std::stof("0X1.FFFFDAP+0") );
    BOOST_CHECK_EQUAL( F<float>::mid(REP_DEC<double>(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000003P-1022")),DEC::trv)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid(REP_DEC<double>(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000003P-1022")),DEC::trv))) );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<float>::mid(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::mid(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}



BOOST_AUTO_TEST_CASE(minimal_rad_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::rad(REP<double>(0.0,2.0)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::rad(REP<double>(2.0,2.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::rad(REP<double>(2.0,2.0))) );
    BOOST_CHECK( std::isnan(F<double>::rad(REP<double>(NaN_D,NaN_D))) );
    BOOST_CHECK_EQUAL( F<double>::rad(REP<double>(-INF_D,+INF_D)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::rad(REP<double>(0.0,INF_D)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::rad(REP<double>(-INF_D, 1.2)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::rad(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022"))), std::stod("0X0.0000000000002P-1022") );
    BOOST_CHECK_EQUAL( F<double>::rad(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022"))), std::stod("0X0.0000000000001P-1022") );
    BOOST_CHECK_EQUAL( F<double>::rad(REP<double>(std::stod("0X1P+0"), std::stod("0X1.0000000000003P+0"))), std::stod("0X1P-51"));

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::rad(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::rad(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_rad_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<float>::rad(REP<double>(0.0,2.0)), 1.0f );
    BOOST_CHECK_EQUAL( F<float>::rad(REP<double>(2.0,2.0)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::rad(REP<double>(2.0,2.0))) );
    BOOST_CHECK( std::isnan(F<float>::rad(REP<double>(NaN_D,NaN_D))) );
    BOOST_CHECK_EQUAL( F<float>::rad(REP<double>(-INF_D,+INF_D)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::rad(REP<double>(0.0,INF_D)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::rad(REP<double>(-INF_D, 1.2)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::rad(REP<double>(std::stod("0X1.FFFFFCP+127"),std::stod("0X1.FFFFFFP+127"))), std::stof("0X1P+104") );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<float>::rad(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::rad(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_rad_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::rad(REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::rad(REP_DEC<double>(REP<double>(2.0,2.0),DEC::com)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::rad(REP_DEC<double>(REP<double>(2.0,2.0),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<double>::rad(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<double>::rad(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill))) );
    BOOST_CHECK_EQUAL( F<double>::rad(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::rad(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::def)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::rad(REP_DEC<double>(REP<double>(-INF_D, 1.2),DEC::trv)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::rad(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022")),DEC::trv)), std::stod("0X0.0000000000002P-1022") );
    BOOST_CHECK_EQUAL( F<double>::rad(REP_DEC<double>(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")),DEC::trv)), std::stod("0X0.0000000000001P-1022") );
    BOOST_CHECK_EQUAL( F<double>::rad(REP_DEC<double>(REP<double>(std::stod("0X1P+0"), std::stod("0X1.0000000000003P+0")),DEC::trv)), std::stod("0X1P-51"));

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::mid(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::mid(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_rad_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<float>::rad(REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)), 1.0f );
    BOOST_CHECK_EQUAL( F<float>::rad(REP_DEC<double>(REP<double>(2.0,2.0),DEC::com)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::rad(REP_DEC<double>(REP<double>(2.0,2.0),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<float>::rad(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<float>::rad(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill))) );
    BOOST_CHECK_EQUAL( F<float>::rad(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::def)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::rad(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::rad(REP_DEC<double>(REP<double>(-INF_D, 1.2),DEC::trv)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::rad(REP_DEC<double>(REP<double>(std::stod("0X1.FFFFFCP+127"),std::stod("0X1.FFFFFFP+127")),DEC::trv)), std::stof("0X1P+104") );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<float>::mid(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)) ) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW(F<float>::mid(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_mid_rad_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan(F<double>::mid_rad(REP<double>(NaN_D,NaN_D)).first) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(-INF_D,+INF_D)).first, 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid_rad(REP<double>(-INF_D,+INF_D)).first) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(-MAX_D,+MAX_D)).first, 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid_rad(REP<double>(-MAX_D,+MAX_D)).first) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(0.0,2.0)).first, 1.0 );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(2.0,2.0)).first, 2.0 );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(-2.0,2.0)).first, 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid_rad(REP<double>(-2.0,2.0)).first) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(0.0,INF_D)).first, MAX_D );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(-INF_D, 1.2)).first, -MAX_D );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022"))).first, 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid_rad(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022"))).first) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022"))).first, 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid_rad(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022"))).first) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(std::stod("0X1.FFFFFFFFFFFFFP+1022"),std::stod("0X1.FFFFFFFFFFFFFP+1023"))).first, std::stod("0X1.7FFFFFFFFFFFFP+1023") );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000003P-1022"))).first, std::stod("0X0.0000000000002P-1022") );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022"))).first, std::stod("0X0.0000000000002P-1022") );


    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<double>::mid_rad(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))).first) );
    BOOST_CHECK( std::isnan(F<double>::mid_rad(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))).second) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::mid_rad(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);

    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(0.0,2.0)).second, 1.0 );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(2.0,2.0)).second, 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid_rad(REP<double>(2.0,2.0)).second) );
    BOOST_CHECK( std::isnan(F<double>::mid_rad(REP<double>(NaN_D,NaN_D)).second) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(-INF_D,+INF_D)).second, INF_D );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(0.0,INF_D)).second, INF_D );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(-INF_D, 1.2)).second, INF_D );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022"))).second, std::stod("0X0.0000000000002P-1022") );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022"))).second, std::stod("0X0.0000000000001P-1022") );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP<double>(std::stod("0X1P+0"), std::stod("0X1.0000000000003P+0"))).second, std::stod("0X1P-51"));

    BOOST_CHECK(!p1788::exception::invalid_operand());

}

BOOST_AUTO_TEST_CASE(minimal_mid_rad_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan(F<float>::mid_rad(REP<double>(NaN_D,NaN_D)).first) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(-INF_D,+INF_D)).first, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP<double>(-INF_D,+INF_D)).first) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(-MAX_D,+MAX_D)).first, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP<double>(-MAX_D,+MAX_D)).first) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(0.0,2.0)).first, 1.0f );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(2.0,2.0)).first, 2.0f );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(-2.0,2.0)).first, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP<double>(-2.0,2.0)).first) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(0.0,INF_D)).first, MAX_F );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(-INF_D, 1.2)).first, -MAX_F );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022"))).first, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022"))).first) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022"))).first, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022"))).first) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(std::stod("0X1.FFFFD90000000P+0"),std::stod("0X1.FFFFD90000001P+0"))).first, std::stof("0X1.FFFFDAP+0") );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000003P-1022"))).first, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000003P-1022"))).first) );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<float>::mid_rad(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))).first) );
    BOOST_CHECK( std::isnan(F<float>::mid_rad(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))).second) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::mid_rad(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1"))), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);

    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(0.0,2.0)).second, 1.0f );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(2.0,2.0)).second, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP<double>(2.0,2.0)).second) );
    BOOST_CHECK( std::isnan(F<float>::mid_rad(REP<double>(NaN_D,NaN_D)).second) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(-INF_D,+INF_D)).second, INF_F );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(0.0,INF_D)).second, INF_F );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(-INF_D, 1.2)).second, INF_F );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP<double>(std::stod("0X1.FFFFFCP+127"),std::stod("0X1.FFFFFFP+127"))).second, std::stof("0X1P+104") );

    BOOST_CHECK(!p1788::exception::invalid_operand());

}

BOOST_AUTO_TEST_CASE(minimal_mid_rad_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan(F<double>::mid_rad(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)).first) );
    BOOST_CHECK( std::isnan(F<double>::mid_rad(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)).first) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::def)).first, 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid_rad(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::def)).first) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(-MAX_D,+MAX_D),DEC::trv)).first, 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid_rad(REP_DEC<double>(REP<double>(-MAX_D,+MAX_D),DEC::trv)).first) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(0.0,2.0),DEC::com)).first, 1.0 );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(2.0,2.0),DEC::dac)).first, 2.0 );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(-2.0,2.0),DEC::trv)).first, 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid_rad(REP_DEC<double>(REP<double>(-2.0,2.0),DEC::trv)).first) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv)).first, MAX_D );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(-INF_D, 1.2),DEC::trv)).first, -MAX_D );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022")),DEC::trv)).first, 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid_rad(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022")),DEC::trv)).first) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")),DEC::trv)).first, 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid_rad(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")),DEC::trv)).first) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X1.FFFFFFFFFFFFFP+1022"),std::stod("0X1.FFFFFFFFFFFFFP+1023")),DEC::trv)).first, std::stod("0X1.7FFFFFFFFFFFFP+1023") );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000003P-1022")),DEC::trv)).first, std::stod("0X0.0000000000002P-1022") );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")),DEC::trv)).first, std::stod("0X0.0000000000002P-1022") );


    BOOST_CHECK(!p1788::exception::invalid_operand());


    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<double>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)).first) );
    BOOST_CHECK( std::isnan(F<double>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)).second) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);

    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)).second, 1.0 );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(2.0,2.0),DEC::com)).second, 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mid_rad(REP_DEC<double>(REP<double>(2.0,2.0),DEC::trv)).second) );
    BOOST_CHECK( std::isnan(F<double>::mid_rad(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)).second) );
    BOOST_CHECK( std::isnan(F<double>::mid_rad(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)).second) );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)).second, INF_D );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::def)).second, INF_D );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(-INF_D, 1.2),DEC::trv)).second, INF_D );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022")),DEC::trv)).second, std::stod("0X0.0000000000002P-1022") );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")),DEC::trv)).second, std::stod("0X0.0000000000001P-1022") );
    BOOST_CHECK_EQUAL( F<double>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X1P+0"), std::stod("0X1.0000000000003P+0")),DEC::trv)).second, std::stod("0X1P-51"));

    BOOST_CHECK(!p1788::exception::invalid_operand());

}

BOOST_AUTO_TEST_CASE(minimal_mid_rad_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan(F<float>::mid_rad(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)).first) );
    BOOST_CHECK( std::isnan(F<float>::mid_rad(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)).first) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::def)).first, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)).first) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(-MAX_D,+MAX_D),DEC::trv)).first, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP_DEC<double>(REP<double>(-MAX_D,+MAX_D),DEC::trv)).first) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(0.0,2.0),DEC::com)).first, 1.0f );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(2.0,2.0),DEC::trv)).first, 2.0f );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(-2.0,2.0),DEC::trv)).first, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP_DEC<double>(REP<double>(-2.0,2.0),DEC::trv)).first) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv)).first, MAX_F );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(-INF_D, 1.2),DEC::trv)).first, -MAX_F );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022")),DEC::trv)).first, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000002P-1022"),std::stod("0X0.0000000000001P-1022")),DEC::trv)).first) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")),DEC::trv)).first, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("0X0.0000000000002P-1022")),DEC::trv)).first) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X1.FFFFD90000000P+0"),std::stod("0X1.FFFFD90000001P+0")),DEC::trv)).first, std::stof("0X1.FFFFDAP+0") );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000003P-1022")),DEC::trv)).first, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X0.0000000000001P-1022"),std::stod("0X0.0000000000003P-1022")),DEC::trv)).first) );

    BOOST_CHECK(!p1788::exception::invalid_operand());


    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<float>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)).first) );
    BOOST_CHECK( std::isnan(F<float>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)).second) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X1.8P+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);

    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)).second, 1.0f );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(2.0,2.0),DEC::com)).second, 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mid_rad(REP_DEC<double>(REP<double>(2.0,2.0),DEC::trv)).second) );
    BOOST_CHECK( std::isnan(F<float>::mid_rad(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)).second) );
    BOOST_CHECK( std::isnan(F<float>::mid_rad(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)).second) );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::def)).second, INF_F );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv)).second, INF_F );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(-INF_D, 1.2),DEC::trv)).second, INF_F );
    BOOST_CHECK_EQUAL( F<float>::mid_rad(REP_DEC<double>(REP<double>(std::stod("0X1.FFFFFCP+127"),std::stod("0X1.FFFFFFP+127")),DEC::trv)).second, std::stof("0X1P+104") );

    BOOST_CHECK(!p1788::exception::invalid_operand());

}


BOOST_AUTO_TEST_CASE(minimal_wid_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::wid(REP<double>(2.0,2.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::wid(REP<double>(2.0,2.0))) );
    BOOST_CHECK_EQUAL( F<double>::wid(REP<double>(1.0,2.0)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::wid(REP<double>(1.0,INF_D)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::wid(REP<double>(-INF_D,2.0)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::wid(REP<double>(-INF_D,+INF_D)), INF_D );
    BOOST_CHECK( std::isnan(F<double>::wid(REP<double>(NaN_D,NaN_D))) );
    BOOST_CHECK_EQUAL( F<double>::wid(REP<double>(std::stod("0X1P+0"),std::stod("0X1.0000000000001P+0"))), std::stod("0X1P-52") );
    BOOST_CHECK_EQUAL( F<double>::wid(REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000001P-1022"))), std::stod("0X0.0000000000001P-1022") );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<double>::wid(REP<double>(1.0,-2.0))) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::wid(REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_wid_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<float>::wid(REP<double>(2.0,2.0)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::wid(REP<double>(2.0,2.0))) );
    BOOST_CHECK_EQUAL( F<float>::wid(REP<double>(1.0,2.0)), 1.0f );
    BOOST_CHECK_EQUAL( F<float>::wid(REP<double>(1.0,INF_D)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::wid(REP<double>(-INF_D,2.0)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::wid(REP<double>(-INF_D,+INF_D)), INF_F );
    BOOST_CHECK( std::isnan(F<float>::wid(REP<double>(NaN_D,NaN_D))) );
    BOOST_CHECK_EQUAL( F<float>::wid(REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000001P-1022"))), std::stof("0X1P-149") );

    BOOST_CHECK(!p1788::exception::invalid_operand());


    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<float>::wid(REP<double>(1.0,-2.0))) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::wid(REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_wid_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::wid(REP_DEC<double>(REP<double>(2.0,2.0),DEC::com)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::wid(REP_DEC<double>(REP<double>(2.0,2.0),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<double>::wid(REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::wid(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::wid(REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::def)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::wid(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)), INF_D );
    BOOST_CHECK( std::isnan(F<double>::wid(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<double>::wid(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill))) );
    BOOST_CHECK_EQUAL( F<double>::wid(REP_DEC<double>(REP<double>(std::stod("0X1P+0"),std::stod("0X1.0000000000001P+0")),DEC::trv)), std::stod("0X1P-52") );
    BOOST_CHECK_EQUAL( F<double>::wid(REP_DEC<double>(REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000001P-1022")),DEC::trv)), std::stod("0X0.0000000000001P-1022") );

    BOOST_CHECK(!p1788::exception::invalid_operand());


    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<double>::wid(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::trv))) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::wid(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_wid_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<float>::wid(REP_DEC<double>(REP<double>(2.0,2.0),DEC::com)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::wid(REP_DEC<double>(REP<double>(2.0,2.0),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<float>::wid(REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)), 1.0f );
    BOOST_CHECK_EQUAL( F<float>::wid(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::wid(REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::def)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::wid(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)), INF_F );
    BOOST_CHECK( std::isnan(F<float>::wid(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<float>::wid(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill))) );
    BOOST_CHECK_EQUAL( F<float>::wid(REP_DEC<double>(REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000001P-1022")),DEC::trv)), std::stof("0X1P-149") );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<float>::wid(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::trv))) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::wid(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_mag_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::mag(REP<double>(1.0,2.0)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::mag(REP<double>(-4.0,2.0)), 4.0 );
    BOOST_CHECK_EQUAL( F<double>::mag(REP<double>(-INF_D,2.0)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::mag(REP<double>(1.0,INF_D)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::mag(REP<double>(-INF_D,+INF_D)), INF_D );
    BOOST_CHECK( std::isnan(F<double>::mag(REP<double>(NaN_D,NaN_D))) );
    BOOST_CHECK_EQUAL( F<double>::mag(REP<double>(-0.0,0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mag(REP<double>(-0.0,0.0))) );
    BOOST_CHECK_EQUAL( F<double>::mag(REP<double>(-0.0,-0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mag(REP<double>(-0.0,-0.0))) );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<double>::mag(REP<double>(1.0,-2.0))) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::mag(REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_mag_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<float>::mag(REP<double>(1.0,2.0)), 2.0f );
    BOOST_CHECK_EQUAL( F<float>::mag(REP<double>(-4.0,2.0)), 4.0f );
    BOOST_CHECK_EQUAL( F<float>::mag(REP<double>(-INF_D,2.0)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::mag(REP<double>(1.0,INF_D)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::mag(REP<double>(-INF_D,+INF_D)), INF_F );
    BOOST_CHECK( std::isnan(F<float>::mag(REP<double>(NaN_D,NaN_D))) );
    BOOST_CHECK_EQUAL( F<float>::mag(REP<double>(-0.0,0.0)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mag(REP<double>(-0.0,0.0))) );
    BOOST_CHECK_EQUAL( F<float>::mag(REP<double>(-0.0,-0.0)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mag(REP<double>(-0.0,-0.0))) );
    BOOST_CHECK_EQUAL( F<float>::mag(REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000001P-1022"))), std::stof("0X1P-149") );
    BOOST_CHECK_EQUAL( F<float>::mag(REP<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.6666666666666P-1"))), std::stof("0X1.19999AP+0") );

    BOOST_CHECK(!p1788::exception::invalid_operand());


    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<float>::mag(REP<double>(1.0,-2.0))) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::mag(REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_mag_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::mag(REP_DEC<double>(REP<double>(1.0,2.0),DEC::com)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::mag(REP_DEC<double>(REP<double>(-4.0,2.0),DEC::trv)), 4.0 );
    BOOST_CHECK_EQUAL( F<double>::mag(REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::mag(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::def)), INF_D );
    BOOST_CHECK_EQUAL( F<double>::mag(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)), INF_D );
    BOOST_CHECK( std::isnan(F<double>::mag(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<double>::mag(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill))) );
    BOOST_CHECK_EQUAL( F<double>::mag(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mag(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<double>::mag(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mag(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv))) );


    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<double>::mag(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::trv))) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::mag(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_mag_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<float>::mag(REP_DEC<double>(REP<double>(1.0,2.0),DEC::com)), 2.0f );
    BOOST_CHECK_EQUAL( F<float>::mag(REP_DEC<double>(REP<double>(-4.0,2.0),DEC::trv)), 4.0f );
    BOOST_CHECK_EQUAL( F<float>::mag(REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::mag(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::def)), INF_F );
    BOOST_CHECK_EQUAL( F<float>::mag(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)), INF_F );
    BOOST_CHECK( std::isnan(F<float>::mag(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<float>::mag(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill))) );
    BOOST_CHECK_EQUAL( F<float>::mag(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mag(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<float>::mag(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mag(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<float>::mag(REP_DEC<double>(REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000001P-1022")),DEC::trv)), std::stof("0X1P-149") );
    BOOST_CHECK_EQUAL( F<float>::mag(REP_DEC<double>(REP<double>(std::stod("-0X1.199999999999AP+0"),std::stod("0X1.6666666666666P-1")),DEC::trv)), std::stof("0X1.19999AP+0") );


    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<float>::mag(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::trv))) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::mag(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_mig_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::mig(REP<double>(1.0,2.0)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::mig(REP<double>(-4.0,2.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mig(REP<double>(-4.0,2.0))) );
    BOOST_CHECK_EQUAL( F<double>::mig(REP<double>(-4.0,-2.0)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::mig(REP<double>(-INF_D,2.0)), 0.0 );
    BOOST_CHECK_EQUAL( F<double>::mig(REP<double>(-INF_D,-2.0)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::mig(REP<double>(-1.0,INF_D)), 0.0 );
    BOOST_CHECK_EQUAL( F<double>::mig(REP<double>(1.0,INF_D)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::mig(REP<double>(-INF_D,+INF_D)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mig(REP<double>(-INF_D,+INF_D))) );
    BOOST_CHECK( std::isnan(F<double>::mig(REP<double>(NaN_D,NaN_D))) );
    BOOST_CHECK_EQUAL( F<double>::mig(REP<double>(-0.0,0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mig(REP<double>(-0.0,0.0))) );
    BOOST_CHECK_EQUAL( F<double>::mig(REP<double>(-0.0,-0.0)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mig(REP<double>(-0.0,-0.0))) );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<double>::mig(REP<double>(1.0,-2.0))) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::mig(REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_mig_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<float>::mig(REP<double>(1.0,2.0)), 1.0f );
    BOOST_CHECK_EQUAL( F<float>::mig(REP<double>(-4.0,2.0)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mig(REP<double>(-4.0,2.0))) );
    BOOST_CHECK_EQUAL( F<float>::mig(REP<double>(-4.0,-2.0)), 2.0f );
    BOOST_CHECK_EQUAL( F<float>::mig(REP<double>(-INF_D,2.0)), 0.0f );
    BOOST_CHECK_EQUAL( F<float>::mig(REP<double>(-INF_D,-2.0)), 2.0f );
    BOOST_CHECK_EQUAL( F<float>::mig(REP<double>(-1.0,INF_D)), 0.0f );
    BOOST_CHECK_EQUAL( F<float>::mig(REP<double>(1.0,INF_D)), 1.0f );
    BOOST_CHECK_EQUAL( F<float>::mig(REP<double>(-INF_D,+INF_D)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mig(REP<double>(-INF_D,+INF_F))) );
    BOOST_CHECK( std::isnan(F<float>::mig(REP<double>(NaN_D,NaN_D))) );
    BOOST_CHECK_EQUAL( F<float>::mig(REP<double>(-0.0,0.0)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mig(REP<double>(-0.0,0.0))) );
    BOOST_CHECK_EQUAL( F<float>::mig(REP<double>(-0.0,-0.0)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mig(REP<double>(-0.0,-0.0))) );
    BOOST_CHECK_EQUAL( F<float>::mig(REP<double>(std::stod("0X1.199999999999AP+0"),std::stod("0X1.6666666666666P+1"))), std::stof("0X1.199998P+0") );

    BOOST_CHECK(!p1788::exception::invalid_operand());


    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<float>::mig(REP<double>(1.0,-2.0))) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::mig(REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_mig_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::mig(REP_DEC<double>(REP<double>(1.0,2.0),DEC::com)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::mig(REP_DEC<double>(REP<double>(-4.0,2.0),DEC::trv)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mig(REP_DEC<double>(REP<double>(-4.0,2.0),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<double>::mig(REP_DEC<double>(REP<double>(-4.0,-2.0),DEC::trv)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::mig(REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::def)), 0.0 );
    BOOST_CHECK_EQUAL( F<double>::mig(REP_DEC<double>(REP<double>(-INF_D,-2.0),DEC::trv)), 2.0 );
    BOOST_CHECK_EQUAL( F<double>::mig(REP_DEC<double>(REP<double>(-1.0,INF_D),DEC::trv)), 0.0 );
    BOOST_CHECK_EQUAL( F<double>::mig(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)), 1.0 );
    BOOST_CHECK_EQUAL( F<double>::mig(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mig(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<double>::mig(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<double>::mig(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill))) );
    BOOST_CHECK_EQUAL( F<double>::mig(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mig(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<double>::mig(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)), 0.0 );
    BOOST_CHECK( !std::signbit(F<double>::mig(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv))) );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<double>::mig(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::trv))) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::mig(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_mig_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<float>::mig(REP_DEC<double>(REP<double>(1.0,2.0),DEC::com)), 1.0f );
    BOOST_CHECK_EQUAL( F<float>::mig(REP_DEC<double>(REP<double>(-4.0,2.0),DEC::trv)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mig(REP_DEC<double>(REP<double>(-4.0,2.0),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<float>::mig(REP_DEC<double>(REP<double>(-4.0,-2.0),DEC::trv)), 2.0f );
    BOOST_CHECK_EQUAL( F<float>::mig(REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv)), 0.0f );
    BOOST_CHECK_EQUAL( F<float>::mig(REP_DEC<double>(REP<double>(-INF_D,-2.0),DEC::def)), 2.0f );
    BOOST_CHECK_EQUAL( F<float>::mig(REP_DEC<double>(REP<double>(-1.0,INF_D),DEC::trv)), 0.0f );
    BOOST_CHECK_EQUAL( F<float>::mig(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)), 1.0f );
    BOOST_CHECK_EQUAL( F<float>::mig(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mig(REP_DEC<double>(REP<double>(-INF_D,+INF_F),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<float>::mig(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv))) );
    BOOST_CHECK( std::isnan(F<float>::mig(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill))) );
    BOOST_CHECK_EQUAL( F<float>::mig(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mig(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<float>::mig(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)), 0.0f );
    BOOST_CHECK( !std::signbit(F<float>::mig(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv))) );
    BOOST_CHECK_EQUAL( F<float>::mig(REP_DEC<double>(REP<double>(std::stod("0X1.199999999999AP+0"),std::stod("0X1.6666666666666P+1")),DEC::trv)), std::stof("0X1.199998P+0") );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    p1788::exception::clear();
    BOOST_CHECK( std::isnan(F<float>::mig(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::trv))) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::mig(REP_DEC<double>(REP<double>(1.0,-2.0),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}
