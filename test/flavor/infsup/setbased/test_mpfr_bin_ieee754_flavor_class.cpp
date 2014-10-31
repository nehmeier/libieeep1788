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

#define BOOST_TEST_MODULE "Flavor: Constructors, Methods, Interval constants [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"
#include "p1788/decoration/decoration.hpp"
#include "test/util/mpfr_bin_ieee754_flavor_io_test_util.hpp"

#include <cmath>
#include <limits>

template<typename T>
using F = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>;

template<typename T>
using REP = typename F<T>::representation;

template<typename T>
using REP_DEC = typename F<T>::representation_dec;

typedef p1788::decoration::decoration DEC;

const double INF_D = std::numeric_limits<double>::infinity();
const double MAX_D = std::numeric_limits<double>::max();
const double DNORM_MIN_D = std::numeric_limits<double>::denorm_min();

const float INF_F = std::numeric_limits<float>::infinity();
const float MAX_F = std::numeric_limits<float>::max();
const float DNORM_MIN_F = std::numeric_limits<float>::denorm_min();


BOOST_AUTO_TEST_CASE(minimal_empty_constructor_test)
{
    BOOST_CHECK( std::isnan( F<double>::constructor().first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor().second ) );
}

BOOST_AUTO_TEST_CASE(minimal_empty_constructor_dec_test)
{
    BOOST_CHECK( std::isnan( F<double>::constructor_dec().first.first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor_dec().first.second ) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec().second, DEC::trv );
}

BOOST_AUTO_TEST_CASE(minimal_infsup_constructor_test)
{
    BOOST_CHECK( std::isnan( F<double>::constructor(1.0,-1.0).first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor(1.0,-1.0).second ) );

    BOOST_CHECK( std::isnan( F<double>::constructor(-INF_D,-INF_D).first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor(-INF_D,-INF_D).second ) );
    BOOST_CHECK( std::isnan( F<double>::constructor(INF_D,INF_D).first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor(INF_D,INF_D).second ) );

    BOOST_CHECK_EQUAL( F<double>::constructor(-1.0,1.0), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::constructor(-INF_D,1.0), REP<double>(-INF_D,1.0) );
    BOOST_CHECK_EQUAL( F<double>::constructor(-1.0,INF_D), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::constructor(-INF_D,INF_D), REP<double>(-INF_D,INF_D) );
}

BOOST_AUTO_TEST_CASE(minimal_infsup_constructor_dec_test)
{
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(1.0,-1.0).first.first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(1.0,-1.0).first.second ) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(1.0,-1.0).second, DEC::ill );

    BOOST_CHECK( std::isnan( F<double>::constructor_dec(-INF_D,-INF_D).first.first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(-INF_D,-INF_D).first.second ) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-INF_D,-INF_D).second, DEC::ill );
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(INF_D,INF_D).first.first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(INF_D,INF_D).first.second ) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(INF_D,INF_D).second, DEC::ill );

    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-1.0,1.0), REP_DEC<double>(REP<double>(-1.0,1.0), DEC::com) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-INF_D,1.0), REP_DEC<double>(REP<double>(-INF_D,1.0), DEC::dac) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-1.0,INF_D), REP_DEC<double>(REP<double>(-1.0,INF_D), DEC::dac) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-INF_D,INF_D), REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
}


BOOST_AUTO_TEST_CASE(minimal_infsup_constructor_mixedtype_test)
{
    BOOST_CHECK( std::isnan( F<float>::constructor(1.0,-1.0).first ) );
    BOOST_CHECK( std::isnan( F<float>::constructor(1.0,-1.0).second ) );

    BOOST_CHECK( std::isnan( F<float>::constructor(-INF_D,-INF_D).first ) );
    BOOST_CHECK( std::isnan( F<float>::constructor(-INF_D,-INF_D).second ) );
    BOOST_CHECK( std::isnan( F<float>::constructor(INF_D,INF_D).first ) );
    BOOST_CHECK( std::isnan( F<float>::constructor(INF_D,INF_D).second ) );

    BOOST_CHECK_EQUAL( F<float>::constructor(-1.0,1.0), REP<float>(-1.0f,1.0f) );
    BOOST_CHECK_EQUAL( F<float>::constructor(-INF_D,1.0), REP<float>(-INF_F,1.f) );
    BOOST_CHECK_EQUAL( F<float>::constructor(-1.0,INF_D), REP<float>(-1.f,INF_F) );
    BOOST_CHECK_EQUAL( F<float>::constructor(-INF_D,INF_D), REP<float>(-INF_F,INF_F) );
    BOOST_CHECK_EQUAL( F<float>::constructor(-MAX_D,MAX_D), REP<float>(-INF_F,INF_F) );
    BOOST_CHECK_EQUAL( F<float>::constructor(DNORM_MIN_D,DNORM_MIN_D), REP<float>(0.0f,DNORM_MIN_F) );
    BOOST_CHECK_EQUAL( F<float>::constructor(-DNORM_MIN_D,-DNORM_MIN_D), REP<float>(-DNORM_MIN_F,0.0f) );
    BOOST_CHECK_EQUAL( F<float>::constructor(-DNORM_MIN_D,DNORM_MIN_D), REP<float>(-DNORM_MIN_F,DNORM_MIN_F) );
    BOOST_CHECK_EQUAL( F<float>::constructor(std::stod("-0x1.99999A842549Ap+4"),std::stod("0X1.9999999999999P-4")), REP<float>(std::stof("-0X1.99999CP+4"),std::stof("0X1.99999AP-4")) );

    BOOST_CHECK( std::isnan( F<double>::constructor(1.0f,-1.0f).first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor(1.0f,-1.0f).second ) );

    BOOST_CHECK( std::isnan( F<double>::constructor(-INF_F,-INF_F).first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor(-INF_F,-INF_F).second ) );
    BOOST_CHECK( std::isnan( F<double>::constructor(INF_F,INF_F).first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor(INF_F,INF_F).second ) );
    BOOST_CHECK_EQUAL( F<double>::constructor(std::stof("-0X1.99999CP+4"),std::stof("0X1.99999AP-4")), REP<double>(std::stod("-0X1.99999CP+4"),std::stod("0X1.99999AP-4")) );

    BOOST_CHECK_EQUAL( F<double>::constructor(-1.0f,1.0f), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::constructor(-INF_F,1.0f), REP<double>(-INF_D,1.0) );
    BOOST_CHECK_EQUAL( F<double>::constructor(-1.0f,INF_F), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::constructor(-INF_F,INF_F), REP<double>(-INF_D,INF_D) );
}

BOOST_AUTO_TEST_CASE(minimal_infsup_constructor_dec_mixedtype_test)
{
    BOOST_CHECK( std::isnan( F<float>::constructor_dec(1.0,-1.0).first.first ) );
    BOOST_CHECK( std::isnan( F<float>::constructor_dec(1.0,-1.0).first.second ) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(1.0,-1.0).second, DEC::ill );

    BOOST_CHECK( std::isnan( F<float>::constructor_dec(-INF_D,-INF_D).first.first ) );
    BOOST_CHECK( std::isnan( F<float>::constructor_dec(-INF_D,-INF_D).first.second ) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-INF_D,-INF_D).second, DEC::ill );
    BOOST_CHECK( std::isnan( F<float>::constructor_dec(INF_D,INF_D).first.first ) );
    BOOST_CHECK( std::isnan( F<float>::constructor_dec(INF_D,INF_D).first.second ) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(INF_D,INF_D).second, DEC::ill );

    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-1.0,1.0), REP_DEC<float>(REP<float>(-1.0f,1.0f), DEC::com) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-INF_D,1.0), REP_DEC<float>(REP<float>(-INF_F,1.0f), DEC::dac) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-1.0,INF_D), REP_DEC<float>(REP<float>(-1.0f,INF_F), DEC::dac) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-INF_D,INF_D), REP_DEC<float>(REP<float>(-INF_F,INF_F), DEC::dac) );

    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-MAX_D,MAX_D), REP_DEC<float>(REP<float>(-INF_F,INF_F), DEC::dac) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(DNORM_MIN_D,DNORM_MIN_D), REP_DEC<float>(REP<float>(0.0f,DNORM_MIN_F), DEC::com) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-DNORM_MIN_D,-DNORM_MIN_D), REP_DEC<float>(REP<float>(-DNORM_MIN_F,0.0f), DEC::com) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-DNORM_MIN_D,DNORM_MIN_D), REP_DEC<float>(REP<float>(-DNORM_MIN_F,DNORM_MIN_F), DEC::com) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(std::stod("-0x1.99999A842549Ap+4"),std::stod("0X1.9999999999999P-4")), REP_DEC<float>(REP<float>(std::stof("-0X1.99999CP+4"),std::stof("0X1.99999AP-4")), DEC::com) );


    BOOST_CHECK( std::isnan( F<double>::constructor_dec(1.0f,-1.0f).first.first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(1.0f,-1.0f).first.second ) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(1.0f,-1.0f).second, DEC::ill );

    BOOST_CHECK( std::isnan( F<double>::constructor_dec(-INF_F,-INF_F).first.first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(-INF_F,-INF_F).first.second ) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-INF_F,-INF_F).second, DEC::ill );
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(INF_F,INF_F).first.first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(INF_F,INF_F).first.second ) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(INF_F,INF_F).second, DEC::ill );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(std::stof("-0X1.99999CP+4"),std::stof("0X1.99999AP-4")), REP_DEC<double>(REP<double>(std::stod("-0X1.99999CP+4"),std::stod("0X1.99999AP-4")), DEC::com) );

    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-1.0f,1.0f), REP_DEC<double>(REP<double>(-1.0,1.0), DEC::com) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-INF_F,1.0f), REP_DEC<double>(REP<double>(-INF_D,1.0), DEC::dac) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-1.0f,INF_F), REP_DEC<double>(REP<double>(-1.0,INF_D), DEC::dac) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-INF_F,INF_F), REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
}

BOOST_AUTO_TEST_CASE(minimal_string_constructor_test)
{
    BOOST_CHECK( false );
}

BOOST_AUTO_TEST_CASE(minimal_string_constructor_dec_test)
{
    BOOST_CHECK( false );
}

BOOST_AUTO_TEST_CASE(minimal_copy_constructor_test)
{
    BOOST_CHECK( false );
}

BOOST_AUTO_TEST_CASE(minimal_copy_constructor_dec_test)
{
    BOOST_CHECK( false );
}

BOOST_AUTO_TEST_CASE(minimal_copy_constructor_mixedtype_test)
{
    BOOST_CHECK( false );
}


BOOST_AUTO_TEST_CASE(minimal_copy_constructor_dec_mixedtype_test)
{
    BOOST_CHECK( false );
}

BOOST_AUTO_TEST_CASE(minimal_convert_constructor_test)
{
    BOOST_CHECK( false );
}

BOOST_AUTO_TEST_CASE(minimal_convert_constructor_dec_test)
{
    BOOST_CHECK( false );
}

BOOST_AUTO_TEST_CASE(minimal_convert_constructor_mixedtype_test)
{
    BOOST_CHECK( false );
}

BOOST_AUTO_TEST_CASE(minimal_convert_constructor_dec_mixedtype_test)
{
    BOOST_CHECK( false );
}

BOOST_AUTO_TEST_CASE(minimal_set_dec_constructor_test)
{
    BOOST_CHECK( false );
}

BOOST_AUTO_TEST_CASE(minimal_set_dec_constructor_mixedtype_test)
{
    BOOST_CHECK( false );
}


BOOST_AUTO_TEST_CASE(minimal_empty_test)
{
    BOOST_CHECK( std::isnan( F<double>::empty().first ) );
    BOOST_CHECK( std::isnan( F<double>::empty().second ) );
}

BOOST_AUTO_TEST_CASE(minimal_empty_dec_test)
{
    BOOST_CHECK( std::isnan( F<double>::empty_dec().first.first ) );
    BOOST_CHECK( std::isnan( F<double>::empty_dec().first.second ) );
    BOOST_CHECK_EQUAL( F<double>::empty_dec().second, DEC::trv );
}

BOOST_AUTO_TEST_CASE(minimal_entire_test)
{
    BOOST_CHECK_EQUAL( F<double>::entire().first, -INF_D );
    BOOST_CHECK_EQUAL( F<double>::entire().second, INF_D );
}

BOOST_AUTO_TEST_CASE(minimal_entire_dec_test)
{
    BOOST_CHECK_EQUAL( F<double>::entire_dec().first.first, -INF_D );
    BOOST_CHECK_EQUAL( F<double>::entire_dec().first.second, INF_D );
    BOOST_CHECK_EQUAL( F<double>::entire_dec().second, DEC::dac );
}

BOOST_AUTO_TEST_CASE(minimal_nai_test)
{
    BOOST_CHECK( std::isnan( F<double>::nai().first.first ) );
    BOOST_CHECK( std::isnan( F<double>::nai().first.second ) );
    BOOST_CHECK_EQUAL( F<double>::nai().second, DEC::ill );
}

BOOST_AUTO_TEST_CASE(minimal_decoration_test)
{
    BOOST_CHECK( false );
}
