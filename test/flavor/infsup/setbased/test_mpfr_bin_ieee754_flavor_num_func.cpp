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
}

BOOST_AUTO_TEST_CASE(minimal_inf_mixedtype_test)
{
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
}

BOOST_AUTO_TEST_CASE(minimal_inf_dec_test)
{
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
}

BOOST_AUTO_TEST_CASE(minimal_inf_dec_mixedtype_test)
{
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
}


///
BOOST_AUTO_TEST_CASE(minimal_sup_test)
{
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
}

BOOST_AUTO_TEST_CASE(minimal_sup_mixedtype_test)
{
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
}

BOOST_AUTO_TEST_CASE(minimal_sup_dec_test)
{
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
}

BOOST_AUTO_TEST_CASE(minimal_sup_dec_mixedtype_test)
{
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


    BOOST_CHECK( std::isnan(F<double>::sup(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill))));

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
}
