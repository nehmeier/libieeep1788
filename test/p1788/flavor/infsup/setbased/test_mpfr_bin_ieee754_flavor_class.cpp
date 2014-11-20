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

const double NAN_D = std::numeric_limits<double>::quiet_NaN();
const double INF_D = std::numeric_limits<double>::infinity();
const double MAX_D = std::numeric_limits<double>::max();
const double DNORM_MIN_D = std::numeric_limits<double>::denorm_min();

const float NAN_F = std::numeric_limits<float>::quiet_NaN();
const float INF_F = std::numeric_limits<float>::infinity();
const float MAX_F = std::numeric_limits<float>::max();
const float DNORM_MIN_F = std::numeric_limits<float>::denorm_min();


BOOST_AUTO_TEST_CASE(minimal_empty_constructor_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan( F<double>::constructor().first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor().second ) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_empty_constructor_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan( F<double>::constructor_dec().first.first ) );
    BOOST_CHECK( std::isnan( F<double>::constructor_dec().first.second ) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec().second, DEC::trv );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_empty_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan( F<double>::empty().first ) );
    BOOST_CHECK( std::isnan( F<double>::empty().second ) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_empty_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan( F<double>::empty_dec().first.first ) );
    BOOST_CHECK( std::isnan( F<double>::empty_dec().first.second ) );
    BOOST_CHECK_EQUAL( F<double>::empty_dec().second, DEC::trv );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}



BOOST_AUTO_TEST_CASE(minimal_infsup_constructor_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::constructor(-1.0,1.0), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::constructor(-INF_D,1.0), REP<double>(-INF_D,1.0) );
    BOOST_CHECK_EQUAL( F<double>::constructor(-1.0,INF_D), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::constructor(-INF_D,INF_D), REP<double>(-INF_D,INF_D) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( std::isnan( F<double>::constructor(NAN_D,NAN_D).first ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor(NAN_D,NAN_D).second ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor(1.0,-1.0).first ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor(1.0,-1.0).second ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor(-INF_D,-INF_D).first ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor(-INF_D,-INF_D).second ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor(INF_D,INF_D).first ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor(INF_D,INF_D).second ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::undefined_operation_bit);
    BOOST_CHECK_THROW( F<double>::constructor(INF_D,INF_D), p1788::exception::undefined_operation_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_infsup_constructor_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-1.0,1.0), REP_DEC<double>(REP<double>(-1.0,1.0), DEC::com) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-INF_D,1.0), REP_DEC<double>(REP<double>(-INF_D,1.0), DEC::dac) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-1.0,INF_D), REP_DEC<double>(REP<double>(-1.0,INF_D), DEC::dac) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-INF_D,INF_D), REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( std::isnan( F<double>::constructor_dec(NAN_D,NAN_D).first.first ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(NAN_D,NAN_D).first.second ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(NAN_D,NAN_D).second, DEC::ill );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(1.0,-1.0).first.first ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(1.0,-1.0).first.second ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(1.0,-1.0).second, DEC::ill );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(-INF_D,-INF_D).first.first ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(-INF_D,-INF_D).first.second ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-INF_D,-INF_D).second, DEC::ill );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(INF_D,INF_D).first.first ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( std::isnan( F<double>::constructor_dec(INF_D,INF_D).first.second ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(INF_D,INF_D).second, DEC::ill );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::undefined_operation_bit);
    BOOST_CHECK_THROW( F<double>::constructor_dec(INF_D,INF_D), p1788::exception::undefined_operation_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_infsup_constructor_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<float>::constructor(-1.0,1.0), REP<float>(-1.0f,1.0f) );
    BOOST_CHECK_EQUAL( F<float>::constructor(-INF_D,1.0), REP<float>(-INF_F,1.f) );
    BOOST_CHECK_EQUAL( F<float>::constructor(-1.0,INF_D), REP<float>(-1.f,INF_F) );
    BOOST_CHECK_EQUAL( F<float>::constructor(-INF_D,INF_D), REP<float>(-INF_F,INF_F) );
    BOOST_CHECK_EQUAL( F<float>::constructor(-MAX_D,MAX_D), REP<float>(-INF_F,INF_F) );
    BOOST_CHECK_EQUAL( F<float>::constructor(DNORM_MIN_D,DNORM_MIN_D), REP<float>(0.0f,DNORM_MIN_F) );
    BOOST_CHECK_EQUAL( F<float>::constructor(-DNORM_MIN_D,-DNORM_MIN_D), REP<float>(-DNORM_MIN_F,0.0f) );
    BOOST_CHECK_EQUAL( F<float>::constructor(-DNORM_MIN_D,DNORM_MIN_D), REP<float>(-DNORM_MIN_F,DNORM_MIN_F) );
    BOOST_CHECK_EQUAL( F<float>::constructor(std::stod("-0x1.99999A842549Ap+4"),std::stod("0X1.9999999999999P-4")), REP<float>(std::stof("-0X1.99999CP+4"),std::stof("0X1.99999AP-4")) );
    BOOST_CHECK_EQUAL( F<double>::constructor(std::stof("-0X1.99999CP+4"),std::stof("0X1.99999AP-4")), REP<double>(std::stod("-0X1.99999CP+4"),std::stod("0X1.99999AP-4")) );
    BOOST_CHECK_EQUAL( F<double>::constructor(-1.0f,1.0f), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::constructor(-INF_F,1.0f), REP<double>(-INF_D,1.0) );
    BOOST_CHECK_EQUAL( F<double>::constructor(-1.0f,INF_F), REP<double>(-1.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::constructor(-INF_F,INF_F), REP<double>(-INF_D,INF_D) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( F<float>::is_empty( F<float>::constructor(-DNORM_MIN_D,-DNORM_MIN_F) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty( F<float>::constructor(1.0,-1.0) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty( F<float>::constructor(-INF_D,-INF_D) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty( F<float>::constructor(INF_D,INF_D) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::constructor(1.0f,-1.0f) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::constructor(-INF_F,-INF_F) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::constructor(INF_F,INF_F) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::undefined_operation_bit);
    BOOST_CHECK_THROW( F<float>::constructor(1.0,-1.0), p1788::exception::undefined_operation_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_THROW( F<double>::constructor(INF_F,INF_F), p1788::exception::undefined_operation_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_infsup_constructor_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-1.0,1.0), REP_DEC<float>(REP<float>(-1.0f,1.0f), DEC::com) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-INF_D,1.0), REP_DEC<float>(REP<float>(-INF_F,1.0f), DEC::dac) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-1.0,INF_D), REP_DEC<float>(REP<float>(-1.0f,INF_F), DEC::dac) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-INF_D,INF_D), REP_DEC<float>(REP<float>(-INF_F,INF_F), DEC::dac) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-MAX_D,MAX_D), REP_DEC<float>(REP<float>(-INF_F,INF_F), DEC::dac) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(DNORM_MIN_D,DNORM_MIN_D), REP_DEC<float>(REP<float>(0.0f,DNORM_MIN_F), DEC::com) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-DNORM_MIN_D,-DNORM_MIN_D), REP_DEC<float>(REP<float>(-DNORM_MIN_F,0.0f), DEC::com) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(-DNORM_MIN_D,DNORM_MIN_D), REP_DEC<float>(REP<float>(-DNORM_MIN_F,DNORM_MIN_F), DEC::com) );
    BOOST_CHECK_EQUAL( F<float>::constructor_dec(std::stod("-0x1.99999A842549Ap+4"),std::stod("0X1.9999999999999P-4")), REP_DEC<float>(REP<float>(std::stof("-0X1.99999CP+4"),std::stof("0X1.99999AP-4")), DEC::com) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(std::stof("-0X1.99999CP+4"),std::stof("0X1.99999AP-4")), REP_DEC<double>(REP<double>(std::stod("-0X1.99999CP+4"),std::stod("0X1.99999AP-4")), DEC::com) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-1.0f,1.0f), REP_DEC<double>(REP<double>(-1.0,1.0), DEC::com) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-INF_F,1.0f), REP_DEC<double>(REP<double>(-INF_D,1.0), DEC::dac) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-1.0f,INF_F), REP_DEC<double>(REP<double>(-1.0,INF_D), DEC::dac) );
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(-INF_F,INF_F), REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( F<float>::is_nai( F<float>::constructor_dec(-DNORM_MIN_D,-DNORM_MIN_F) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai( F<float>::constructor_dec(1.0,-1.0) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai( F<float>::constructor_dec(-INF_D,-INF_D) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai( F<float>::constructor_dec(INF_D,INF_D) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai( F<double>::constructor_dec(1.0f,-1.0f) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai( F<double>::constructor_dec(-INF_F,-INF_F) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai( F<double>::constructor_dec(INF_F,INF_F) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();


    p1788::exception::set_throw_exception_cwd(p1788::exception::undefined_operation_bit);
    BOOST_CHECK_THROW( F<float>::constructor_dec(-INF_D,-INF_D), p1788::exception::undefined_operation_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_THROW( F<double>::constructor_dec(INF_F,INF_F), p1788::exception::undefined_operation_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_string_constructor_test)
{
    p1788::exception::clear();

    BOOST_CHECK( false );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

}

BOOST_AUTO_TEST_CASE(minimal_string_constructor_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( false );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

}

BOOST_AUTO_TEST_CASE(minimal_copy_constructor_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL(F<double>::constructor( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")) ), REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")) ), REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")) ), REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")) ), REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D) ), REP<double>(-DNORM_MIN_D, -DNORM_MIN_D));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<double>(-DNORM_MIN_D, DNORM_MIN_D) ), REP<double>(-DNORM_MIN_D, DNORM_MIN_D));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<double>(DNORM_MIN_D, DNORM_MIN_D) ), REP<double>(DNORM_MIN_D, DNORM_MIN_D));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<double>(-MAX_D, -MAX_D) ), REP<double>(-MAX_D, -MAX_D));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<double>(-MAX_D, MAX_D) ), REP<double>(-MAX_D, MAX_D));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<double>(MAX_D, MAX_D) ), REP<double>(MAX_D, MAX_D));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<double>(-INF_D, INF_D) ), REP<double>(-INF_D, INF_D));
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP<double>(NAN_D, NAN_D) )));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP<double>(7.0, NAN_D) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP<double>(7.0, -3.0) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP<double>(-INF_D, -INF_D) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP<double>(+INF_D, +INF_D) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::constructor( REP<double>(7.0, -3.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_copy_constructor_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")), DEC::trv) ), REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")), DEC::trv));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com) ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")), DEC::dac) ), REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")), DEC::dac));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC::def) ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC::def));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<double>( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC::trv) ), REP_DEC<double>( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC::trv));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<double>( REP<double>(-DNORM_MIN_D, DNORM_MIN_D), DEC::trv) ), REP_DEC<double>( REP<double>(-DNORM_MIN_D, DNORM_MIN_D), DEC::trv));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<double>( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC::trv) ), REP_DEC<double>( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC::trv));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<double>( REP<double>(-MAX_D, -MAX_D), DEC::trv) ), REP_DEC<double>( REP<double>(-MAX_D, -MAX_D), DEC::trv));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<double>( REP<double>(-MAX_D, MAX_D), DEC::trv) ), REP_DEC<double>( REP<double>(-MAX_D, MAX_D), DEC::trv));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<double>( REP<double>(MAX_D, MAX_D), DEC::trv) ), REP_DEC<double>( REP<double>(MAX_D, MAX_D), DEC::trv));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::trv) ), REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::trv));
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor_dec( REP_DEC<double>(REP<double>(NAN_D, NAN_D), DEC::trv) )));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com) ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP_DEC<double>(REP<double>(7.0, NAN_D), DEC::trv) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP_DEC<double>(REP<double>(7.0, -3.0), DEC::def) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP_DEC<double>(REP<double>(-INF_D, -INF_D), DEC::com) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP_DEC<double>(REP<double>(+INF_D, +INF_D), DEC::dac) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::constructor_dec( REP_DEC<double>(REP<double>(-7.0, -3.0), DEC::ill)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_copy_constructor_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL(F<float>::constructor( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")) ), REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")) ), REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")) ), REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")) ), REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<float>(std::stof("-0X1.99999Cp+4"), std::stof("0x1.99999Ap-4")) ), REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D) ), REP<float>(-DNORM_MIN_F,+0.0));
    BOOST_CHECK( !std::signbit( F<float>::constructor( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D) ).second ));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP<double>(-DNORM_MIN_D, DNORM_MIN_D) ), REP<float>(-DNORM_MIN_F, DNORM_MIN_F));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP<double>(DNORM_MIN_D, DNORM_MIN_D) ), REP<float>(-0.0, DNORM_MIN_F));
    BOOST_CHECK( std::signbit( F<float>::constructor( REP<double>(DNORM_MIN_D, DNORM_MIN_D) ).first ));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<float>(DNORM_MIN_F, DNORM_MIN_F) ), REP<double>(DNORM_MIN_F, DNORM_MIN_F));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP<double>(-MAX_D, -MAX_D) ), REP<float>(-INF_F, -MAX_F));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP<double>(-MAX_D, MAX_D) ), REP<float>(-INF_F, INF_F));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP<double>(MAX_D, MAX_D) ), REP<float>(MAX_F, INF_F));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<float>(MAX_F, MAX_F) ), REP<double>(MAX_F, MAX_F));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP<double>(-INF_D, INF_D) ), REP<float>(-INF_F, INF_F));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP<float>(-INF_F, INF_F) ), REP<double>(-INF_D, INF_D));
    BOOST_CHECK( F<float>::is_empty(F<float>::constructor( REP<double>(NAN_D, NAN_D) )));
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP<float>(NAN_D, NAN_D) )));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( F<float>::is_empty( F<float>::constructor(REP<double>(-DNORM_MIN_D,-DNORM_MIN_F)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty(F<float>::constructor( REP<double>(7.0, NAN_D) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty(F<float>::constructor( REP<double>(7.0, -3.0) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP<float>(-INF_F, -INF_F) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP<float>(+INF_F, +INF_F) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::constructor( REP<double>(7.0, -3.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_copy_constructor_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")), DEC::trv) ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC::trv));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com) ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC::com));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")), DEC::dac) ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC::dac));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC::def) ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC::def));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<float>( REP<float>(std::stof("-0X1.99999Cp+4"), std::stof("0x1.99999Ap-4")), DEC::trv) ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC::trv));

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC::trv) ), REP_DEC<float>( REP<float>(-DNORM_MIN_F,+0.0), DEC::trv));
    BOOST_CHECK( !std::signbit( F<float>::constructor_dec( REP_DEC<double>( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC::trv) ).first.second ));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(-DNORM_MIN_D, DNORM_MIN_D), DEC::trv) ), REP_DEC<float>( REP<float>(-DNORM_MIN_F, DNORM_MIN_F), DEC::trv));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC::trv) ), REP_DEC<float>( REP<float>(-0.0, DNORM_MIN_F), DEC::trv));
    BOOST_CHECK( std::signbit( F<float>::constructor_dec( REP_DEC<double>( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC::trv) ).first.first ));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<float>( REP<float>(DNORM_MIN_F, DNORM_MIN_F), DEC::trv) ), REP_DEC<double>( REP<double>(DNORM_MIN_F, DNORM_MIN_F), DEC::trv));

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(-MAX_D, -MAX_D), DEC::def) ), REP_DEC<float>( REP<float>(-INF_F, -MAX_F), DEC::def));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(-MAX_D, MAX_D), DEC::trv) ), REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC::trv));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(MAX_D, MAX_D), DEC::dac) ), REP_DEC<float>( REP<float>(MAX_F, INF_F), DEC::dac));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<float>( REP<float>(MAX_F, MAX_F), DEC::trv) ), REP_DEC<double>( REP<double>(MAX_F, MAX_F), DEC::trv));

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(-MAX_D, -MAX_D), DEC::com) ), REP_DEC<float>( REP<float>(-INF_F, -MAX_F), DEC::dac));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(-MAX_D, MAX_D), DEC::com) ), REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC::dac));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(MAX_D, MAX_D), DEC::com) ), REP_DEC<float>( REP<float>(MAX_F, INF_F), DEC::dac));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC::trv) ), REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::trv));

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::trv) ), REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC::trv));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC::trv) ), REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::trv));

    BOOST_CHECK( F<float>::is_empty(F<float>::constructor_dec( REP_DEC<double>(REP<double>(NAN_D, NAN_D), DEC::trv) )));
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor_dec( REP_DEC<float>(REP<float>(NAN_D, NAN_D), DEC::trv) )));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( F<float>::is_nai( F<float>::constructor_dec(REP_DEC<double>(REP<double>(-DNORM_MIN_D,-DNORM_MIN_F), DEC::trv)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai(F<float>::constructor_dec( REP_DEC<double>(REP<double>(7.0, NAN_D), DEC::trv) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai(F<float>::constructor_dec( REP_DEC<double>(REP<double>(7.0, -3.0), DEC::def) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP_DEC<float>(REP<float>(-INF_F, -INF_F), DEC::com) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP_DEC<float>(REP<float>(+INF_F, +INF_F), DEC::dac) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::constructor_dec( REP_DEC<double>(REP<double>(-7.0, -3.0), DEC::ill)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_convert_constructor_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")), DEC::trv) ), REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")) );
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com) ), REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")) );
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")), DEC::dac) ), REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")) );
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC::def) ), REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")) );
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<double>( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC::trv) ), REP<double>(-DNORM_MIN_D, -DNORM_MIN_D) );
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<double>( REP<double>(-DNORM_MIN_D, DNORM_MIN_D), DEC::trv) ), REP<double>(-DNORM_MIN_D, DNORM_MIN_D) );
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<double>( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC::trv) ), REP<double>(DNORM_MIN_D, DNORM_MIN_D) );
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<double>( REP<double>(-MAX_D, -MAX_D), DEC::trv) ), REP<double>(-MAX_D, -MAX_D) );
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<double>( REP<double>(-MAX_D, MAX_D), DEC::trv) ), REP<double>(-MAX_D, MAX_D) );
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<double>( REP<double>(MAX_D, MAX_D), DEC::trv) ), REP<double>(MAX_D, MAX_D) );
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::trv) ), REP<double>(-INF_D, INF_D) );
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP_DEC<double>(REP<double>(NAN_D, NAN_D), DEC::trv) )));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com) ), REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP_DEC<double>(REP<double>(NAN_D, NAN_D), DEC::ill) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::interval_part_of_nai_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::interval_part_of_nai_bit);
    BOOST_CHECK_THROW( F<double>::constructor(REP_DEC<double>(REP<double>(NAN_D, NAN_D), DEC::ill) ), p1788::exception::interval_part_of_nai_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::interval_part_of_nai_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);

    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP_DEC<double>(REP<double>(7.0, NAN_D), DEC::trv) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP_DEC<double>(REP<double>(7.0, -3.0), DEC::def) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP_DEC<double>(REP<double>(-INF_D, -INF_D), DEC::com) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP_DEC<double>(REP<double>(+INF_D, +INF_D), DEC::dac) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::constructor( REP_DEC<double>(REP<double>(-7.0, -3.0), DEC::ill)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

}

BOOST_AUTO_TEST_CASE(minimal_convert_constructor_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")), DEC::trv) ), REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com) ), REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")), DEC::dac) ), REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC::def) ), REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<float>( REP<float>(std::stof("-0X1.99999Cp+4"), std::stof("0x1.99999Ap-4")), DEC::trv) ), REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")));

    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC::trv) ), REP<float>(-DNORM_MIN_F,+0.0));
    BOOST_CHECK( !std::signbit( F<float>::constructor( REP_DEC<double>( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC::trv) ).second ));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(-DNORM_MIN_D, DNORM_MIN_D), DEC::trv) ), REP<float>(-DNORM_MIN_F, DNORM_MIN_F));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC::trv) ), REP<float>(-0.0, DNORM_MIN_F));
    BOOST_CHECK( std::signbit( F<float>::constructor( REP_DEC<double>( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC::trv) ).first ));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<float>( REP<float>(DNORM_MIN_F, DNORM_MIN_F), DEC::trv) ), REP<double>(DNORM_MIN_F, DNORM_MIN_F));

    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(-MAX_D, -MAX_D), DEC::def) ), REP<float>(-INF_F, -MAX_F));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(-MAX_D, MAX_D), DEC::trv) ), REP<float>(-INF_F, INF_F));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(MAX_D, MAX_D), DEC::dac) ), REP<float>(MAX_F, INF_F));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<float>( REP<float>(MAX_F, MAX_F), DEC::trv) ), REP<double>(MAX_F, MAX_F));

    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(-MAX_D, -MAX_D), DEC::com) ), REP<float>(-INF_F, -MAX_F));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(-MAX_D, MAX_D), DEC::com) ), REP<float>(-INF_F, INF_F));
    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(MAX_D, MAX_D), DEC::com) ), REP<float>(MAX_F, INF_F));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC::trv) ), REP<double>(-INF_D, INF_D));

    BOOST_CHECK_EQUAL(F<float>::constructor( REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::trv) ), REP<float>(-INF_F, INF_F));
    BOOST_CHECK_EQUAL(F<double>::constructor( REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC::trv) ), REP<double>(-INF_D, INF_D));

    BOOST_CHECK( F<float>::is_empty(F<float>::constructor( REP_DEC<double>(REP<double>(NAN_D, NAN_D), DEC::trv) )));
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP_DEC<float>(REP<float>(NAN_D, NAN_D), DEC::trv) )));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( F<float>::is_empty( F<float>::constructor(REP_DEC<double>(REP<double>(NAN_D, NAN_D), DEC::ill)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::interval_part_of_nai_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::constructor(REP_DEC<float>(REP<float>(NAN_F, NAN_F), DEC::ill)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::interval_part_of_nai_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::interval_part_of_nai_bit);
    BOOST_CHECK_THROW( F<double>::constructor(REP_DEC<float>(REP<float>(NAN_F, NAN_F), DEC::ill)), p1788::exception::interval_part_of_nai_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::interval_part_of_nai_bit);
    p1788::exception::clear();
    BOOST_CHECK_THROW( F<float>::constructor(REP_DEC<double>(REP<double>(NAN_D, NAN_D), DEC::ill)), p1788::exception::interval_part_of_nai_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::interval_part_of_nai_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);

    BOOST_CHECK( F<float>::is_empty( F<float>::constructor(REP_DEC<double>(REP<double>(-DNORM_MIN_D,-DNORM_MIN_F), DEC::trv)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty(F<float>::constructor( REP_DEC<double>(REP<double>(7.0, NAN_D), DEC::trv) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty(F<float>::constructor( REP_DEC<double>(REP<double>(7.0, -3.0), DEC::def) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP_DEC<float>(REP<float>(-INF_F, -INF_F), DEC::com) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor( REP_DEC<float>(REP<float>(+INF_F, +INF_F), DEC::dac) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::constructor( REP_DEC<double>(REP<double>(-7.0, -3.0), DEC::ill)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_convert_constructor_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")) ), REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")) ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")) ), REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")) ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D) ), REP_DEC<double>( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(-DNORM_MIN_D, DNORM_MIN_D) ), REP_DEC<double>( REP<double>(-DNORM_MIN_D, DNORM_MIN_D), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(DNORM_MIN_D, DNORM_MIN_D) ), REP_DEC<double>( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(-MAX_D, -MAX_D) ), REP_DEC<double>( REP<double>(-MAX_D, -MAX_D), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(-MAX_D, MAX_D) ), REP_DEC<double>( REP<double>(-MAX_D, MAX_D), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(MAX_D, MAX_D) ), REP_DEC<double>( REP<double>(MAX_D, MAX_D), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(-INF_D, INF_D) ), REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::dac));
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor_dec( REP<double>(NAN_D, NAN_D) )));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")) ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP<double>(7.0, NAN_D) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP<double>(7.0, -3.0) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP<double>(-INF_D, -INF_D) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP<double>(+INF_D, +INF_D) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::constructor_dec( REP<double>(7.0, -3.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_convert_constructor_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")) ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC::com));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")) ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC::com));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")) ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC::com));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")) ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<float>(std::stof("-0X1.99999Cp+4"), std::stof("0x1.99999Ap-4")) ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC::com));

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D) ), REP_DEC<float>( REP<float>(-DNORM_MIN_F,+0.0), DEC::com));
    BOOST_CHECK( !std::signbit( F<float>::constructor_dec( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D) ).first.second ));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(-DNORM_MIN_D, DNORM_MIN_D) ), REP_DEC<float>( REP<float>(-DNORM_MIN_F, DNORM_MIN_F), DEC::com));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(DNORM_MIN_D, DNORM_MIN_D) ), REP_DEC<float>( REP<float>(-0.0, DNORM_MIN_F), DEC::com));
    BOOST_CHECK( std::signbit( F<float>::constructor_dec( REP<double>(DNORM_MIN_D, DNORM_MIN_D) ).first.first ));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<float>(DNORM_MIN_F, DNORM_MIN_F) ), REP_DEC<double>( REP<double>(DNORM_MIN_F, DNORM_MIN_F), DEC::com));

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(-MAX_D, -MAX_D) ), REP_DEC<float>( REP<float>(-INF_F, -MAX_F), DEC::dac));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(-MAX_D, MAX_D) ), REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC::dac));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(MAX_D, MAX_D) ), REP_DEC<float>( REP<float>(MAX_F, INF_F), DEC::dac));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<float>(MAX_F, MAX_F) ), REP_DEC<double>( REP<double>(MAX_F, MAX_F), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<float>(-INF_F, INF_F) ), REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::dac));

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(-INF_D, INF_D) ), REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC::dac));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<float>(-INF_F, INF_F) ), REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::dac));

    BOOST_CHECK( F<float>::is_empty(F<float>::constructor_dec( REP<double>(NAN_D, NAN_D) )));
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor_dec( REP<float>(NAN_D, NAN_D) )));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( F<float>::is_nai( F<float>::constructor_dec( REP<double>(-DNORM_MIN_D,-DNORM_MIN_F) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai(F<float>::constructor_dec( REP<double>(7.0, NAN_D) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai(F<float>::constructor_dec( REP<double>(7.0, -3.0) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP<float>(-INF_F, -INF_F) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP<float>(+INF_F, +INF_F) )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::constructor_dec( REP<double>(7.0, -3.0) ), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_set_dec_constructor_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")), DEC::trv ), REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")), DEC::trv));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")), DEC::dac ), REP_DEC<double>( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")), DEC::dac));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC::def ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC::def));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC::trv ), REP_DEC<double>( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC::trv));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(-DNORM_MIN_D, DNORM_MIN_D), DEC::def ), REP_DEC<double>( REP<double>(-DNORM_MIN_D, DNORM_MIN_D), DEC::def));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC::dac ), REP_DEC<double>( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC::dac));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(-MAX_D, -MAX_D), DEC::com ), REP_DEC<double>( REP<double>(-MAX_D, -MAX_D), DEC::com));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(-MAX_D, MAX_D), DEC::def ), REP_DEC<double>( REP<double>(-MAX_D, MAX_D), DEC::def));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(MAX_D, MAX_D), DEC::trv ), REP_DEC<double>( REP<double>(MAX_D, MAX_D), DEC::trv));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(-INF_D, INF_D), DEC::dac ), REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::dac));
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor_dec(REP<double>(NAN_D, NAN_D), DEC::trv )));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( F<double>::is_empty(F<double>::constructor_dec(REP<double>(NAN_D, NAN_D), DEC::def )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor_dec(REP<double>(NAN_D, NAN_D), DEC::dac )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor_dec(REP<double>(NAN_D, NAN_D), DEC::com )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::constructor_dec(REP<double>(1.0, INF_D), DEC::com ), REP_DEC<double>( REP<double>(1.0, INF_D), DEC::dac) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(REP<double>(-INF_D,3.0), DEC::com ), REP_DEC<double>( REP<double>(-INF_D,3.0), DEC::dac) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(REP<double>(-INF_D, INF_D), DEC::com ), REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::dac) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();

    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec(REP<double>(NAN_D, NAN_D), DEC::ill )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec(REP<double>(-INF_D,3.0), DEC::ill )) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec(REP<double>(-1.0,3.0), DEC::ill )) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::undefined_operation_bit);
    BOOST_CHECK_THROW( F<double>::constructor_dec( REP<double>(NAN_D, NAN_D), DEC::dac), p1788::exception::undefined_operation_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_THROW( F<double>::constructor_dec( REP<double>(-INF_D,3.0), DEC::com), p1788::exception::undefined_operation_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_THROW( F<double>::constructor_dec( REP<double>(-1.0,3.0), DEC::ill), p1788::exception::undefined_operation_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);

    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP<double>(7.0, NAN_D), DEC::trv )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP<double>(7.0, -3.0), DEC::def )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP<double>(-INF_D, -INF_D), DEC::com )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP<double>(+INF_D, +INF_D), DEC::dac )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::constructor_dec( REP<double>(7.0, -3.0), DEC::ill), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_set_dec_constructor_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0X1.9999999999999P-4")), DEC::trv ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC::trv));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0X1.9999999999999P-4")), DEC::com ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC::com));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(std::stod("-0x1.99999A842549Ap+4"), std::stod("0x1.99999A0000000p-4")), DEC::dac ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC::dac));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC::def ), REP_DEC<float>( REP<float>(std::stof("-0X1.99999CP+4"), std::stof("0X1.99999AP-4")), DEC::def));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<float>(std::stof("-0X1.99999Cp+4"), std::stof("0x1.99999Ap-4")), DEC::trv ), REP_DEC<double>( REP<double>(std::stod("-0X1.99999C0000000p+4"), std::stod("0x1.99999A0000000p-4")), DEC::trv));

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC::trv ), REP_DEC<float>( REP<float>(-DNORM_MIN_F,+0.0), DEC::trv));
    BOOST_CHECK( !std::signbit( F<float>::constructor_dec( REP<double>(-DNORM_MIN_D, -DNORM_MIN_D), DEC::trv ).first.second ));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(-DNORM_MIN_D, DNORM_MIN_D), DEC::trv ), REP_DEC<float>( REP<float>(-DNORM_MIN_F, DNORM_MIN_F), DEC::trv));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC::trv ), REP_DEC<float>( REP<float>(-0.0, DNORM_MIN_F), DEC::trv));
    BOOST_CHECK( std::signbit( F<float>::constructor_dec( REP<double>(DNORM_MIN_D, DNORM_MIN_D), DEC::trv ).first.first ));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<float>(DNORM_MIN_F, DNORM_MIN_F), DEC::trv ), REP_DEC<double>( REP<double>(DNORM_MIN_F, DNORM_MIN_F), DEC::trv));

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(-MAX_D, -MAX_D), DEC::def ), REP_DEC<float>( REP<float>(-INF_F, -MAX_F), DEC::def));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(-MAX_D, MAX_D), DEC::trv ), REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC::trv));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(MAX_D, MAX_D), DEC::dac ), REP_DEC<float>( REP<float>(MAX_F, INF_F), DEC::dac));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<float>(MAX_F, MAX_F), DEC::trv ), REP_DEC<double>( REP<double>(MAX_F, MAX_F), DEC::trv));

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(-MAX_D, -MAX_D), DEC::com ), REP_DEC<float>( REP<float>(-INF_F, -MAX_F), DEC::dac));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(-MAX_D, MAX_D), DEC::com ), REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC::dac));
    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(MAX_D, MAX_D), DEC::com ), REP_DEC<float>( REP<float>(MAX_F, INF_F), DEC::dac));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<float>(-INF_F, INF_F), DEC::trv ), REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::trv));

    BOOST_CHECK_EQUAL(F<float>::constructor_dec( REP<double>(-INF_D, INF_D), DEC::trv ), REP_DEC<float>( REP<float>(-INF_F, INF_F), DEC::trv));
    BOOST_CHECK_EQUAL(F<double>::constructor_dec( REP<float>(-INF_F, INF_F), DEC::trv ), REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::trv));

    BOOST_CHECK( F<float>::is_empty(F<float>::constructor_dec( REP<double>(NAN_D, NAN_D), DEC::trv )));
    BOOST_CHECK( F<double>::is_empty(F<double>::constructor_dec( REP<float>(NAN_D, NAN_D), DEC::trv )));

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( F<float>::is_empty(F<float>::constructor_dec(REP<double>(NAN_D, NAN_D), DEC::def )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty(F<float>::constructor_dec(REP<double>(NAN_D, NAN_D), DEC::dac )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty(F<float>::constructor_dec(REP<double>(NAN_D, NAN_D), DEC::com )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::constructor_dec(REP<float>(1.0f, INF_F), DEC::com ), REP_DEC<double>( REP<double>(1.0, INF_D), DEC::dac) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(REP<float>(-INF_F,3.0f), DEC::com ), REP_DEC<double>( REP<double>(-INF_D,3.0), DEC::dac) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_EQUAL( F<double>::constructor_dec(REP<float>(-INF_F, INF_F), DEC::com ), REP_DEC<double>( REP<double>(-INF_D, INF_D), DEC::dac) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();

    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec(REP<float>(NAN_F, NAN_F), DEC::ill )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec(REP<float>(-INF_F,3.0f), DEC::ill )) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec(REP<float>(-1.0f,3.0f), DEC::ill )) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::undefined_operation_bit);
    BOOST_CHECK_THROW( F<float>::constructor_dec( REP<double>(NAN_D, NAN_D), DEC::dac), p1788::exception::undefined_operation_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_THROW( F<float>::constructor_dec( REP<double>(-INF_D,3.0), DEC::com), p1788::exception::undefined_operation_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    BOOST_CHECK_THROW( F<float>::constructor_dec( REP<double>(-1.0,3.0), DEC::ill), p1788::exception::undefined_operation_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);

    BOOST_CHECK( F<float>::is_nai(F<float>::constructor_dec( REP<double>(7.0, NAN_D), DEC::trv )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai(F<float>::constructor_dec( REP<double>(7.0, -3.0), DEC::def )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP<float>(-INF_F, -INF_F), DEC::com )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai(F<double>::constructor_dec( REP<float>(+INF_F, +INF_F), DEC::dac )));
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::constructor_dec( REP<double>(7.0, -3.0), DEC::ill), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}




BOOST_AUTO_TEST_CASE(minimal_entire_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::entire().first, -INF_D );
    BOOST_CHECK_EQUAL( F<double>::entire().second, INF_D );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

}

BOOST_AUTO_TEST_CASE(minimal_entire_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::entire_dec().first.first, -INF_D );
    BOOST_CHECK_EQUAL( F<double>::entire_dec().first.second, INF_D );
    BOOST_CHECK_EQUAL( F<double>::entire_dec().second, DEC::dac );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

}

BOOST_AUTO_TEST_CASE(minimal_nai_test)
{
    p1788::exception::clear();

    BOOST_CHECK( std::isnan( F<double>::nai().first.first ) );
    BOOST_CHECK( std::isnan( F<double>::nai().first.second ) );
    BOOST_CHECK_EQUAL( F<double>::nai().second, DEC::ill );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

}

BOOST_AUTO_TEST_CASE(minimal_decoration_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL(F<double>::decoration(REP_DEC<double>(REP<double>(NAN_D,NAN_D),DEC::ill)), DEC::ill);
    BOOST_CHECK_EQUAL(F<double>::decoration(REP_DEC<double>(REP<double>(NAN_D,NAN_D),DEC::trv)), DEC::trv);
    BOOST_CHECK_EQUAL(F<double>::decoration(REP_DEC<double>(REP<double>(-1.0,3.0),DEC::trv)), DEC::trv);
    BOOST_CHECK_EQUAL(F<double>::decoration(REP_DEC<double>(REP<double>(-1.0,3.0),DEC::def)), DEC::def);
    BOOST_CHECK_EQUAL(F<double>::decoration(REP_DEC<double>(REP<double>(-1.0,3.0),DEC::dac)), DEC::dac);
    BOOST_CHECK_EQUAL(F<double>::decoration(REP_DEC<double>(REP<double>(-1.0,3.0),DEC::com)), DEC::com);

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);


    BOOST_CHECK_EQUAL(F<double>::decoration(REP_DEC<double>(REP<double>(1.0,17),DEC::ill)), DEC::ill);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK_EQUAL(F<double>::decoration(REP_DEC<double>(REP<double>(NAN_D,NAN_D),DEC::dac)), DEC::ill);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK_EQUAL(F<double>::decoration(REP_DEC<double>(REP<double>(-INF_D,3.0),DEC::com)), DEC::ill);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    BOOST_CHECK_EQUAL(F<double>::decoration(REP_DEC<double>(REP<double>(-15.0,INF_D),DEC::com)), DEC::ill);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::decoration(REP_DEC<double>(REP<double>(-15.0,INF_D),DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}
