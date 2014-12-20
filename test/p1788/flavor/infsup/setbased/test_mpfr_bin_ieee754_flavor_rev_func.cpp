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

#define BOOST_TEST_MODULE "Flavor: Reverse functions [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
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
const double DNORM_MIN_D = std::numeric_limits<double>::denorm_min();

const double INF_F = std::numeric_limits<float>::infinity();
const double NaN_F = std::numeric_limits<float>::quiet_NaN();
const double MAX_F = std::numeric_limits<float>::max();
const double MIN_F = std::numeric_limits<float>::min();
const double DNORM_MIN_F = std::numeric_limits<float>::denorm_min();


BOOST_AUTO_TEST_CASE(minimal_sqr_rev_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(F<double>::empty()) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(REP<double>(-10.0,-1.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(0.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(0.0,1.0)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(-0.5,1.0)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(-1000.0,1.0)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(0.0,25.0)), REP<double>(-5.0,5.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(-1.0,25.0)), REP<double>(-5.0,5.0) );


    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7"))), REP<double>(std::stod("-0X1.999999999999BP-4"),std::stod("0X1.999999999999BP-4")) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(0.0,std::stod("0X1.FFFFFFFFFFFE1P+1"))), REP<double>(std::stod("-0x1.ffffffffffff1p+0"),std::stod("0x1.ffffffffffff1p+0")) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(REP<double>(1.0,-MAX_D)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::sqr_rev(REP<double>(3.0,-4.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_sqr_rev_bin_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(F<double>::empty(), REP<double>(-5.0,1.0)) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(REP<double>(-10.0,-1.0), REP<double>(-5.0,1.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(0.0,INF_D), REP<double>(-5.0,1.0)), REP<double>(-5.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(0.0,1.0), REP<double>(-0.1,1.0)), REP<double>(-0.1,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(-0.5,1.0), REP<double>(-0.1,1.0)), REP<double>(-0.1,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(-1000.0,1.0), REP<double>(-0.1,1.0)), REP<double>(-0.1,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(0.0,25.0), REP<double>(-4.1,6.0)), REP<double>(-4.1,5.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(-1.0,25.0), REP<double>(-4.1,7.0)), REP<double>(-4.1,5.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(1.0,25.0), REP<double>(0.0,7.0)), REP<double>(1.0,5.0) );


    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7")), REP<double>(-0.1,INF_D)), REP<double>(-0.1,std::stod("0X1.999999999999BP-4")) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<double>(0.0,std::stod("0X1.FFFFFFFFFFFE1P+1")), REP<double>(-0.1,INF_D)), REP<double>(-0.1,std::stod("0x1.ffffffffffff1p+0")) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(REP<double>(1.0,-MAX_D), REP<double>(1.0,-MAX_D)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::sqr_rev(REP<double>(3.0,-4.0), REP<double>(3.0,-4.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_sqr_rev_mixedtype_test)
{
    BOOST_CHECK( F<float>::is_empty( F<float>::sqr_rev(F<double>::empty()) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(REP<float>(-10.0f,-1.0f)) ) );
    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP<double>(0.0,INF_D)), F<float>::entire() );
    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP<double>(0.0,1.0)), REP<float>(-1.0f,1.0f) );
    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP<double>(-0.5,1.0)), REP<float>(-1.0f,1.0f) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<float>(-1000.0f,1.0f)), REP<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<float>(0.0f,25.0f)), REP<double>(-5.0,5.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<float>(-1.0f,25.0f)), REP<double>(-5.0,5.0) );


    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7"))), REP<float>(std::stof("-0X1.99999AP-4"),std::stof("0X1.99999AP-4")) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<float>(0.0f,std::stof("0X1.FFFFFEP+1"))), REP<double>(std::stod("-0x1.fffffeffffffcp+0"),std::stod("0x1.fffffeffffffcp+0")) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty( F<float>::sqr_rev(REP<double>(1.0,-MAX_D)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::sqr_rev(REP<float>(3.0f,-4.0f)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_sqr_rev_bin_mixedtype_test)
{
    BOOST_CHECK( F<float>::is_empty( F<float>::sqr_rev(F<double>::empty(), REP<double>(-5.0,1.0)) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(REP<float>(-10.0f,-1.0f), REP<double>(-5.0,1.0)) ) );
    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP<double>(0.0,INF_D), REP<float>(-5.0f,1.0f)), REP<float>(-5.0f,1.0f) );
    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP<double>(0.0,1.0), REP<float>(-0.1f,1.0f)), REP<float>(-0.1f,1.0f) );
    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP<double>(-0.5,1.0), REP<float>(-0.1f,1.0f)), REP<float>(-0.1f,1.0f) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<float>(-1000.0f,1.0f), REP<double>(-0.1,1.0)), REP<double>(-0.1,1.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<float>(0.0f,25.0f), REP<double>(-4.1,6.0)), REP<double>(-4.1,5.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<float>(-1.0f,25.0f), REP<double>(-4.1,7.0)), REP<double>(-4.1,5.0) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<float>(1.0f,25.0f), REP<double>(0.0,7.0)), REP<double>(1.0,5.0) );


    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7")), REP<float>(-0.1f,INF_F)), REP<float>(-0.1f,std::stof("0X1.99999AP-4")) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP<float>(0.0f,std::stof("0X1.FFFFFEP+1")), REP<double>(-0.1,INF_D)), REP<double>(-0.1,std::stod("0x1.fffffeffffffcp+0")) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty( F<float>::sqr_rev(REP<double>(1.0,-MAX_D), REP<double>(1.0,-MAX_D)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::sqr_rev(REP<float>(3.0f,-4.0f), REP<double>(3.0,-4.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_sqr_rev_dec_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(F<double>::empty_dec()) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(REP_DEC<double>(REP<double>(-10.0,-1.0),DEC::com)) ) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac)), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(0.0,1.0),DEC::def)), REP_DEC<double>(REP<double>(-1.0,1.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(-0.5,1.0),DEC::dac)), REP_DEC<double>(REP<double>(-1.0,1.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(-1000.0,1.0),DEC::com)), REP_DEC<double>(REP<double>(-1.0,1.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(0.0,25.0),DEC::def)), REP_DEC<double>(REP<double>(-5.0,5.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(-1.0,25.0),DEC::dac)), REP_DEC<double>(REP<double>(-5.0,5.0),DEC::trv) );


    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7")),DEC::com)), REP_DEC<double>(REP<double>(std::stod("-0X1.999999999999BP-4"),std::stod("0X1.999999999999BP-4")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(0.0,std::stod("0X1.FFFFFFFFFFFE1P+1")),DEC::def)), REP_DEC<double>(REP<double>(std::stod("-0x1.ffffffffffff1p+0"),std::stod("0x1.ffffffffffff1p+0")),DEC::trv) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai( F<double>::sqr_rev(REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::ill)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::sqr_rev(REP_DEC<double>(REP<double>(3.0,-4.0),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_sqr_rev_dec_bin_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-5.0,1.0),DEC::def)) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(REP_DEC<double>(REP<double>(-10.0,-1.0),DEC::com), REP_DEC<double>(REP<double>(-5.0,1.0),DEC::dac)) ) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::def), REP_DEC<double>(REP<double>(-5.0,1.0),DEC::dac)), REP_DEC<double>(REP<double>(-5.0,1.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(0.0,1.0),DEC::dac), REP_DEC<double>(REP<double>(-0.1,1.0),DEC::def)), REP_DEC<double>(REP<double>(-0.1,1.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(-0.5,1.0),DEC::def), REP_DEC<double>(REP<double>(-0.1,1.0),DEC::dac)), REP_DEC<double>(REP<double>(-0.1,1.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(-1000.0,1.0),DEC::com), REP_DEC<double>(REP<double>(-0.1,1.0),DEC::def)), REP_DEC<double>(REP<double>(-0.1,1.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(0.0,25.0),DEC::def), REP_DEC<double>(REP<double>(-4.1,6.0),DEC::com)), REP_DEC<double>(REP<double>(-4.1,5.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(-1.0,25.0),DEC::dac), REP_DEC<double>(REP<double>(-4.1,7.0),DEC::def)), REP_DEC<double>(REP<double>(-4.1,5.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(1.0,25.0),DEC::dac), REP_DEC<double>(REP<double>(0.0,7.0),DEC::def)), REP_DEC<double>(REP<double>(1.0,5.0),DEC::trv) );


    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7")),DEC::def), REP_DEC<double>(REP<double>(-0.1,INF_D),DEC::dac)), REP_DEC<double>(REP<double>(-0.1,std::stod("0X1.999999999999BP-4")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<double>(REP<double>(0.0,std::stod("0X1.FFFFFFFFFFFE1P+1")),DEC::dac), REP_DEC<double>(REP<double>(-0.1,INF_D),DEC::dac)), REP_DEC<double>(REP<double>(-0.1,std::stod("0x1.ffffffffffff1p+0")),DEC::trv) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai( F<double>::sqr_rev(REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::ill), REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::trv)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::sqr_rev(REP_DEC<double>(REP<double>(3.0,-4.0),DEC::def), REP_DEC<double>(REP<double>(3.0,-4.0),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_sqr_rev_dec_mixedtype_test)
{
    BOOST_CHECK( F<float>::is_empty( F<float>::sqr_rev(F<double>::empty_dec()) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(REP_DEC<float>(REP<float>(-10.0f,-1.0f),DEC::def)) ) );
    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac)), REP_DEC<float>(REP<float>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP_DEC<double>(REP<double>(0.0,1.0),DEC::def)), REP_DEC<float>(REP<float>(-1.0f,1.0f),DEC::trv) );
    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP_DEC<double>(REP<double>(-0.5,1.0),DEC::com)), REP_DEC<float>(REP<float>(-1.0f,1.0f),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<float>(REP<float>(-1000.0f,1.0f),DEC::def)), REP_DEC<double>(REP<double>(-1.0,1.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<float>(REP<float>(0.0f,25.0f),DEC::dac)), REP_DEC<double>(REP<double>(-5.0,5.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<float>(REP<float>(-1.0f,25.0f),DEC::def)), REP_DEC<double>(REP<double>(-5.0,5.0),DEC::trv) );


    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP_DEC<double>(REP<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7")),DEC::def)), REP_DEC<float>(REP<float>(std::stof("-0X1.99999AP-4"),std::stof("0X1.99999AP-4")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<float>(REP<float>(0.0f,std::stof("0X1.FFFFFEP+1")),DEC::com)), REP_DEC<double>(REP<double>(std::stod("-0x1.fffffeffffffcp+0"),std::stod("0x1.fffffeffffffcp+0")),DEC::trv) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai( F<float>::sqr_rev(REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::def)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::sqr_rev(REP_DEC<float>(REP<float>(3.0f,-4.0f),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_sqr_rev_dec_bin_mixedtype_test)
{
    BOOST_CHECK( F<float>::is_empty( F<float>::sqr_rev(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-5.0,1.0),DEC::def)) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::sqr_rev(REP_DEC<float>(REP<float>(-10.0f,-1.0f),DEC::dac), REP_DEC<double>(REP<double>(-5.0,1.0),DEC::def)) ) );
    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac), REP_DEC<float>(REP<float>(-5.0f,1.0f),DEC::dac)), REP_DEC<float>(REP<float>(-5.0f,1.0f),DEC::trv) );
    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP_DEC<double>(REP<double>(0.0,1.0),DEC::com), REP_DEC<float>(REP<float>(-0.1f,1.0f),DEC::dac)), REP_DEC<float>(REP<float>(-0.1f,1.0f),DEC::trv) );
    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP_DEC<double>(REP<double>(-0.5,1.0),DEC::def), REP_DEC<float>(REP<float>(-0.1f,1.0f),DEC::def)), REP_DEC<float>(REP<float>(-0.1f,1.0f),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<float>(REP<float>(-1000.0f,1.0f),DEC::def), REP_DEC<double>(REP<double>(-0.1,1.0),DEC::com)), REP_DEC<double>(REP<double>(-0.1,1.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<float>(REP<float>(0.0f,25.0f),DEC::dac), REP_DEC<double>(REP<double>(-4.1,6.0),DEC::com)), REP_DEC<double>(REP<double>(-4.1,5.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<float>(REP<float>(-1.0f,25.0f),DEC::dac), REP_DEC<double>(REP<double>(-4.1,7.0),DEC::def)), REP_DEC<double>(REP<double>(-4.1,5.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<float>(REP<float>(1.0f,25.0f),DEC::dac), REP_DEC<double>(REP<double>(0.0,7.0),DEC::def)), REP_DEC<double>(REP<double>(1.0,5.0),DEC::trv) );


    BOOST_CHECK_EQUAL( F<float>::sqr_rev(REP_DEC<double>(REP<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7")),DEC::dac), REP_DEC<float>(REP<float>(-0.1f,INF_F),DEC::dac)), REP_DEC<float>(REP<float>(-0.1f,std::stof("0X1.99999AP-4")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::sqr_rev(REP_DEC<float>(REP<float>(0.0f,std::stof("0X1.FFFFFEP+1")),DEC::dac), REP_DEC<double>(REP<double>(-0.1,INF_D),DEC::def)), REP_DEC<double>(REP<double>(-0.1,std::stod("0x1.fffffeffffffcp+0")),DEC::trv) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai( F<float>::sqr_rev(REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::def), REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::trv)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::sqr_rev(REP_DEC<float>(REP<float>(3.0f,-4.0f),DEC::trv), REP_DEC<double>(REP<double>(3.0,-4.0),DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_abs_rev_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(F<double>::empty()) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(REP<double>(-1.1,-0.4)) ) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<double>(0.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<double>(1.1,2.1)), REP<double>(-2.1,2.1) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<double>(-1.1,2.0)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<double>(-1.1,0.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<double>(-1.9,0.2)), REP<double>(-0.2,0.2) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<double>(0.0,0.2)), REP<double>(-0.2,0.2) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<double>(-1.5,INF_D)), REP<double>(-INF_D,INF_D) );

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(REP<double>(1.0,-MAX_D)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::abs_rev(REP<double>(1.0,-3.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_abs_rev_bin_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(F<double>::empty(), REP<double>(-1.1,5.0)) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(REP<double>(-1.1,-0.4), REP<double>(-1.1,5.0)) ) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<double>(0.0,INF_D), REP<double>(-1.1,5.0)), REP<double>(-1.1,5.0) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<double>(1.1,2.1), REP<double>(-1.0,5.0)), REP<double>(1.1,2.1) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<double>(-1.1,2.0), REP<double>(-1.1,5.0)), REP<double>(-1.1,2.0) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<double>(-1.1,0.0), REP<double>(-1.1,5.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<double>(-1.9,0.2), REP<double>(-1.1,5.0)), REP<double>(-0.2,0.2) );

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(REP<double>(1.0,-MAX_D), REP<double>(-1.1,5.0)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::abs_rev(REP<double>(1.0,-3.0), REP<double>(-1.1,5.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_abs_rev_mixedtype_test)
{
    BOOST_CHECK( F<float>::is_empty( F<float>::abs_rev(F<double>::empty()) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(REP<float>(-1.1f,-0.4f)) ) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<float>(0.0,INF_F)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<float>(1.1f,2.1f)), REP<double>(-2.1f,2.1f) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<float>(-1.1f,2.0f)), REP<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( F<float>::abs_rev(REP<double>(-1.1,0.0)), REP<float>(0.0f,0.0f) );
    BOOST_CHECK_EQUAL( F<float>::abs_rev(REP<double>(-1.9,0.2)), REP<float>(-0.2f,0.2f) );
    BOOST_CHECK_EQUAL( F<float>::abs_rev(REP<double>(0.0,0.2)), REP<float>(-0.2f,0.2f) );
    BOOST_CHECK_EQUAL( F<float>::abs_rev(REP<double>(-1.5,INF_D)), REP<float>(-INF_F,INF_F) );

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty( F<float>::abs_rev(REP<double>(1.0,-MAX_D)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::abs_rev(REP<float>(1.0f,-3.0f)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_abs_rev_bin_mixedtype_test)
{
    BOOST_CHECK( F<float>::is_empty( F<float>::abs_rev(F<double>::empty(), REP<double>(-1.1,5.0)) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(REP<float>(-1.1f,-0.4f), REP<float>(-1.f,5.0f)) ) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<float>(0.0f,INF_F), REP<double>(-1.1,5.0)), REP<double>(-1.1,5.0) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<float>(1.1f,2.1f), REP<double>(-1.1,5.0)), REP<double>(1.1f,2.1f) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP<float>(-1.1f,2.0f), REP<double>(-1.1,5.0)), REP<double>(-1.1,2.0) );
    BOOST_CHECK_EQUAL( F<float>::abs_rev(REP<double>(-1.1,0.0), REP<double>(-1.1,5.0)), REP<float>(0.0f,0.0f) );
    BOOST_CHECK_EQUAL( F<float>::abs_rev(REP<double>(-1.9,0.2), REP<double>(-1.1,5.0)), REP<float>(-0.2f,0.2f) );

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty( F<float>::abs_rev(REP<double>(1.0,-MAX_D), REP<double>(-1.1,5.0)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::abs_rev(REP<float>(1.0f,-3.0f), REP<double>(-1.1,5.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}



BOOST_AUTO_TEST_CASE(minimal_abs_rev_dec_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(F<double>::empty_dec()) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(REP_DEC<double>(REP<double>(-1.1,-0.4),DEC::dac)) ) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac)), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<double>(REP<double>(1.1,2.1),DEC::com)), REP_DEC<double>(REP<double>(-2.1,2.1),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<double>(REP<double>(-1.1,2.0),DEC::def)), REP_DEC<double>(REP<double>(-2.0,2.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<double>(REP<double>(-1.1,0.0),DEC::dac)), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<double>(REP<double>(-1.9,0.2),DEC::com)), REP_DEC<double>(REP<double>(-0.2,0.2),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<double>(REP<double>(0.0,0.2),DEC::def)), REP_DEC<double>(REP<double>(-0.2,0.2),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<double>(REP<double>(-1.5,INF_D),DEC::def)), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai( F<double>::abs_rev(REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::trv)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::abs_rev(REP_DEC<double>(REP<double>(1.0,-3.0),DEC::dac)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_abs_rev_dec_bin_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::com)) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(REP_DEC<double>(REP<double>(-1.1,-0.4),DEC::dac), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::dac)) ) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::def), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::def)), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<double>(REP<double>(1.1,2.1),DEC::dac), REP_DEC<double>(REP<double>(-1.0,5.0),DEC::def)), REP_DEC<double>(REP<double>(1.1,2.1),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<double>(REP<double>(-1.1,2.0),DEC::com), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::def)), REP_DEC<double>(REP<double>(-1.1,2.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<double>(REP<double>(-1.1,0.0),DEC::def), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::def)), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<double>(REP<double>(-1.9,0.2),DEC::dac), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::def)), REP_DEC<double>(REP<double>(-0.2,0.2),DEC::trv) );

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai( F<double>::abs_rev(REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::dac), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::def)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::abs_rev(REP_DEC<double>(REP<double>(1.0,-3.0),DEC::trv), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_abs_rev_dec_mixedtype_test)
{
    BOOST_CHECK( F<float>::is_empty( F<float>::abs_rev(F<double>::empty_dec()) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(REP_DEC<float>(REP<float>(-1.1f,-0.4f),DEC::def)) ) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<float>(REP<float>(0.0,INF_F),DEC::dac)), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<float>(REP<float>(1.1f,2.1f),DEC::def)), REP_DEC<double>(REP<double>(-2.1f,2.1f),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<float>(REP<float>(-1.1f,2.0f),DEC::com)), REP_DEC<double>(REP<double>(-2.0,2.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<float>::abs_rev(REP_DEC<double>(REP<double>(-1.1,0.0),DEC::dac)), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv) );
    BOOST_CHECK_EQUAL( F<float>::abs_rev(REP_DEC<double>(REP<double>(-1.9,0.2),DEC::def)), REP_DEC<float>(REP<float>(-0.2f,0.2f),DEC::trv) );
    BOOST_CHECK_EQUAL( F<float>::abs_rev(REP_DEC<double>(REP<double>(0.0,0.2),DEC::com)), REP_DEC<float>(REP<float>(-0.2f,0.2f),DEC::trv) );
    BOOST_CHECK_EQUAL( F<float>::abs_rev(REP_DEC<double>(REP<double>(-1.5,INF_D),DEC::dac)), REP_DEC<float>(REP<float>(-INF_F,INF_F),DEC::trv) );

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai( F<float>::abs_rev(REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::def)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::abs_rev(REP_DEC<float>(REP<float>(1.0f,-3.0f),DEC::dac)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_abs_rev_dec_bin_mixedtype_test)
{
    BOOST_CHECK( F<float>::is_empty( F<float>::abs_rev(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::trv)) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::abs_rev(REP_DEC<float>(REP<float>(-1.1f,-0.4f),DEC::def), REP_DEC<float>(REP<float>(-1.f,5.0f),DEC::dac)) ) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<float>(REP<float>(0.0f,INF_F),DEC::dac), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::def)), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<float>(REP<float>(1.1f,2.1f),DEC::def), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::def)), REP_DEC<double>(REP<double>(1.1f,2.1f),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::abs_rev(REP_DEC<float>(REP<float>(-1.1f,2.0f),DEC::def), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::dac)), REP_DEC<double>(REP<double>(-1.1,2.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<float>::abs_rev(REP_DEC<double>(REP<double>(-1.1,0.0),DEC::com), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::dac)), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv) );
    BOOST_CHECK_EQUAL( F<float>::abs_rev(REP_DEC<double>(REP<double>(-1.9,0.2),DEC::com), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::com)), REP_DEC<float>(REP<float>(-0.2f,0.2f),DEC::trv) );

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai( F<float>::abs_rev(REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::def), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::trv)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::abs_rev(REP_DEC<float>(REP<float>(1.0f,-3.0f),DEC::trv), REP_DEC<double>(REP<double>(-1.1,5.0),DEC::dac)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_pown_rev_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), 0) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(1.0,1.0), 0), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-1.0,5.0), 0), F<double>::entire() );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(-1.0,0.0), 0) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(-1.0,-0.0), 0) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(1.1,10.0), 0) ) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), 1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire(), 1), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,0.0), 1), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,-0.0), 1), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(13.1,13.1), 1), REP<double>(13.1,13.1) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-7451.145,-7451.145), 1), REP<double>(-7451.145,-7451.145) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(MAX_D,MAX_D), 1), REP<double>(MAX_D,MAX_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-MAX_D,-MAX_D), 1), REP<double>(-MAX_D,-MAX_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,INF_D), 1), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,INF_D), 1), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,0.0), 1), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,-0.0), 1), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-324.3,2.5), 1), REP<double>(-324.3,2.5) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.01,2.33), 1), REP<double>(0.01,2.33) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-1.9,-0.33), 1), REP<double>(-1.9,-0.33) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), 2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,INF_D), 2), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,INF_D), 2), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,0.0), 2), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,-0.0), 2), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.573851EB851EBP+7"),std::stod("0X1.573851EB851ECP+7")), 2), REP<double>(std::stod("-0x1.a333333333334p+3"),std::stod("0x1.a333333333334p+3")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.A794A4E7CFAADP+25"),std::stod("0X1.A794A4E7CFAAEP+25")), 2), REP<double>(std::stod("-0x1.d1b251eb851edp+12"),std::stod("0x1.d1b251eb851edp+12")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(MAX_D,MAX_D), 2), REP<double>(std::stod("-0x1p+512"),std::stod("0x1p+512")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,std::stod("0X1.9AD27D70A3D72P+16")), 2), REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.444cccccccccep+8")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,std::stod("0X1.9AD27D70A3D72P+16")), 2), REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.444cccccccccep+8")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.A36E2EB1C432CP-14"),std::stod("0X1.5B7318FC50482P+2")), 2), REP<double>(std::stod("-0x1.2a3d70a3d70a5p+1"),std::stod("0x1.2a3d70a3d70a5p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.BE0DED288CE7P-4"),std::stod("0X1.CE147AE147AE1P+1")), 2), REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("0x1.e666666666667p+0")) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), 8) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire(), 8), REP<double>(-INF_D,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,INF_D), 8), REP<double>(-INF_D,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,INF_D), 8), REP<double>(-INF_D,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,0.0), 8), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,-0.0), 8), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.9D8FD495853F5P+29"),std::stod("0X1.9D8FD495853F6P+29")), 8), REP<double>(std::stod("-0x1.a333333333334p+3"),std::stod("0x1.a333333333334p+3")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.DFB1BB622E70DP+102"),std::stod("0X1.DFB1BB622E70EP+102")), 8), REP<double>(std::stod("-0x1.d1b251eb851edp+12"),std::stod("0x1.d1b251eb851edp+12")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(MAX_D,MAX_D), 8), REP<double>(std::stod("-0x1p+128"),std::stod("0x1p+128")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,std::stod("0X1.A87587109655P+66")), 8), REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.444cccccccccep+8")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,std::stod("0X1.A87587109655P+66")), 8), REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.444cccccccccep+8")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.CD2B297D889BDP-54"),std::stod("0X1.B253D9F33CE4DP+9")), 8), REP<double>(std::stod("-0x1.2a3d70a3d70a5p+1"),std::stod("0x1.2a3d70a3d70a5p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.26F1FCDD502A3P-13"),std::stod("0X1.53ABD7BFC4FC6P+7")), 8), REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("0x1.e666666666667p+0")) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), 3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire(), 3), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,0.0), 3), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,-0.0), 3), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev( REP<double>(std::stod("0X1.1902E978D4FDEP+11"),std::stod("0X1.1902E978D4FDFP+11")), 3), REP<double>(std::stod("0x1.a333333333332p+3"),std::stod("0x1.a333333333334p+3")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X1.81460637B9A3DP+38"),std::stod("-0X1.81460637B9A3CP+38")), 3), REP<double>(std::stod("-0x1.d1b251eb851edp+12"),std::stod("-0x1.d1b251eb851ebp+12")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(MAX_D,MAX_D), 3), REP<double>(std::stod("0x1.428a2f98d728ap+341"),std::stod("0x1.428a2f98d728bp+341")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-MAX_D,-MAX_D), 3), REP<double>(std::stod("-0x1.428a2f98d728bp+341"), std::stod("-0x1.428a2f98d728ap+341")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,INF_D), 3), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,INF_D), 3), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,0.0), 3), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,-0.0), 3), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X1.0436D2F418938P+25"),std::stod("0X1.F4P+3")), 3), REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.4p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.0C6F7A0B5ED8DP-20"),std::stod("0X1.94C75E6362A6P+3")), 3), REP<double>(std::stod("0x1.47ae147ae147ap-7"),std::stod("0x1.2a3d70a3d70a5p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X1.B6F9DB22D0E55P+2"),std::stod("-0X1.266559F6EC5B1P-5")), 3), REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("-0x1.51eb851eb851ep-2")) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), 7) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire(), 7), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,0.0), 7), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,-0.0), 7), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.F91D1B185493BP+25"),std::stod("0X1.F91D1B185493CP+25")), 7), REP<double>(std::stod("0x1.a333333333332p+3"),std::stod("0x1.a333333333334p+3")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X1.07B1DA32F9B59P+90"),std::stod("-0X1.07B1DA32F9B58P+90")), 7), REP<double>(std::stod("-0x1.d1b251eb851edp+12"),std::stod("-0x1.d1b251eb851ebp+12")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(MAX_D,MAX_D), 7), REP<double>(std::stod("0x1.381147622f886p+146"),std::stod("0x1.381147622f887p+146")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-MAX_D,-MAX_D), 7), REP<double>(std::stod("-0x1.381147622f887p+146"),std::stod("-0x1.381147622f886p+146")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,INF_D), 7), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,INF_D), 7), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,0.0), 7), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,-0.0), 7), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X1.4F109959E6D7FP+58"),std::stod("0X1.312DP+9")), 7), REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.4p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.6849B86A12B9BP-47"),std::stod("0X1.74D0373C76313P+8")), 7), REP<double>(std::stod("0x1.47ae147ae147ap-7"),std::stod("0x1.2a3d70a3d70a5p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X1.658C775099757P+6"),std::stod("-0X1.BEE30301BF47AP-12")), 7), REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("-0x1.51eb851eb851ep-2")) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), -2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,INF_D), -2), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,INF_D), -2), F<double>::entire() );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(0.0,0.0), -2) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(-0.0,-0.0), -2) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(-10.0,0.0), -2) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(-10.0,-0.0), -2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.7DE3A077D1568P-8"),std::stod("0X1.7DE3A077D1569P-8")), -2), REP<double>(std::stod("-0x1.a333333333335p+3"),std::stod("0x1.a333333333335p+3")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.3570290CD6E14P-26"),std::stod("0X1.3570290CD6E15P-26")), -2), REP<double>(std::stod("-0x1.d1b251eb851eep+12"),std::stod("0x1.d1b251eb851eep+12")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")), -2), REP<double>(-INF_D,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.3F0C482C977C9P-17"),INF_D), -2), REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.444cccccccccep+8")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.793D85EF38E47P-3"),std::stod("0X1.388P+13")), -2), REP<double>(std::stod("-0x1.2a3d70a3d70a5p+1"),std::stod("0x1.2a3d70a3d70a5p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.1BA81104F6C8P-2"),std::stod("0X1.25D8FA1F801E1P+3")), -2), REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("0x1.e666666666667p+0")) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), -8) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,INF_D), -8), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,INF_D), -8), F<double>::entire() );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(0.0,0.0), -8) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(-0.0,-0.0), -8) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.3CEF39247CA6DP-30"),std::stod("0X1.3CEF39247CA6EP-30")), -8), REP<double>(std::stod("-0x1.a333333333335p+3"),std::stod("0x1.a333333333335p+3")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.113D9EF0A99ACP-103"),std::stod("0X1.113D9EF0A99ADP-103")), -8), REP<double>(std::stod("-0x1.d1b251eb851eep+12"),std::stod("0x1.d1b251eb851eep+12")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")), -8), REP<double>(-INF_D,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.34CC3764D1E0CP-67"),INF_D), -8), REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.444cccccccccep+8")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.2DC80DB11AB7CP-10"),std::stod("0X1.1C37937E08P+53")), -8), REP<double>(std::stod("-0x1.2a3d70a3d70a5p+1"),std::stod("0x1.2a3d70a3d70a5p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.81E104E61630DP-8"),std::stod("0X1.BC64F21560E34P+12")), -8), REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("0x1.e666666666667p+0")) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), -1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire(), -1), F<double>::entire() );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(0.0,0.0), -1) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(-0.0,-0.0), -1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.38ABF82EE6986P-4"),std::stod("0X1.38ABF82EE6987P-4")), -1), REP<double>(std::stod("0x1.a333333333332p+3"),std::stod("0x1.a333333333335p+3")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X1.197422C9048BFP-13"),std::stod("-0X1.197422C9048BEP-13")), -1), REP<double>(std::stod("-0x1.d1b251eb851eep+12"),std::stod("-0x1.d1b251eb851ebp+12")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X0.4P-1022"),std::stod("0X0.4000000000001P-1022")), -1), REP<double>(std::stod("0x1.ffffffffffff8p+1023"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X0.4000000000001P-1022"),std::stod("-0X0.4P-1022")), -1), REP<double>(-INF_D,std::stod("-0x1.ffffffffffff8p+1023")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,INF_D), -1), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,INF_D), -1), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,0.0), -1), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,-0.0), -1), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.B77C278DBBE13P-2"),std::stod("0X1.9P+6")), -1), REP<double>(std::stod("0x1.47ae147ae147ap-7"),std::stod("0x1.2a3d70a3d70a5p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X1.83E0F83E0F83EP+1"),std::stod("-0X1.0D79435E50D79P-1")), -1), REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("-0x1.51eb851eb851ep-2")) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), -3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire(), -3), F<double>::entire() );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(0.0,0.0), -3) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(-0.0,-0.0), -3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.D26DF4D8B1831P-12"),std::stod("0X1.D26DF4D8B1832P-12")), -3), REP<double>(std::stod("0x1.a333333333331p+3"),std::stod("0x1.a333333333335p+3")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X1.54347DED91B19P-39"),std::stod("-0X1.54347DED91B18P-39")), -3), REP<double>(std::stod("-0x1.d1b251eb851eep+12"),std::stod("-0x1.d1b251eb851eap+12")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")), -3), REP<double>(std::stod("0x1p+358"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("-0X0P+0")), -3), REP<double>(-INF_D,std::stod("-0x1p+358")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,INF_D), -3), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,INF_D), -3), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,0.0), -3), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,-0.0), -3), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.43CFBA61AACABP-4"),std::stod("0X1.E848P+19")), -3), REP<double>(std::stod("0x1.47ae147ae147ap-7"),std::stod("0x1.2a3d70a3d70a5p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X1.BD393CE9E8E7CP+4"),std::stod("-0X1.2A95F6F7C066CP-3")), -3), REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("-0x1.51eb851eb851ep-2")) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), -7) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire(), -7), F<double>::entire() );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(0.0,0.0), -7) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(-0.0,-0.0), -7) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.037D76C912DBCP-26"),std::stod("0X1.037D76C912DBDP-26")), -7), REP<double>(std::stod("0x1.a333333333332p+3"),std::stod("0x1.a333333333335p+3")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X1.F10F41FB8858FP-91"),std::stod("-0X1.F10F41FB8858EP-91")), -7), REP<double>(std::stod("-0x1.d1b251eb851eep+12"),std::stod("-0x1.d1b251eb851ebp+12")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")), -7), REP<double>(std::stod("0x1.588cea3f093bcp+153"),INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("-0X0P+0")), -7), REP<double>(-INF_D,std::stod("-0x1.588cea3f093bcp+153")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,INF_D), -7), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-0.0,INF_D), -7), REP<double>(0.0,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,0.0), -7), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,-0.0), -7), REP<double>(-INF_D,0.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.5F934D64162A9P-9"),std::stod("0X1.6BCC41E9P+46")), -7), REP<double>(std::stod("0x1.47ae147ae147ap-7"),std::stod("0x1.2a3d70a3d70a5p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X1.254CDD3711DDBP+11"),std::stod("-0X1.6E95C4A761E19P-7")), -7), REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("-0x1.51eb851eb851ep-2")) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(1.0,-MAX_D), 5) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::pown_rev(REP<double>(3.0,-4.0), 1), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_pown_rev_bin_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), REP<double>(1.0,1.0), 0) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(1.0,1.0), REP<double>(1.0,1.0), 0), REP<double>(1.0,1.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-1.0,5.0), REP<double>(-51.0,12.0), 0), REP<double>(-51.0,12.0) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(-1.0,0.0), REP<double>(5.0,10.0), 0) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(-1.0,-0.0), REP<double>(-1.0,1.0), 0) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(1.1,10.0),REP<double>(1.0,41.0), 0) ) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), REP<double>(0.0,100.1), 1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire(), REP<double>(-5.1,10.0), 1), REP<double>(-5.1,10.0) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,0.0), REP<double>(-10.0,5.1), 1), REP<double>(0.0,0.0) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(-0.0,-0.0), REP<double>(1.0,5.0), 1) ) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), REP<double>(5.0,17.1), 2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,INF_D), REP<double>(5.6,27.544), 2), REP<double>(5.6,27.544) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(0.0,0.0), REP<double>(1.0,2.0), 2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.A36E2EB1C432CP-14"),std::stod("0X1.5B7318FC50482P+2")), REP<double>(1.0,INF_D), 2), REP<double>(1.0,std::stod("0x1.2a3d70a3d70a5p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.BE0DED288CE7P-4"),std::stod("0X1.CE147AE147AE1P+1")), REP<double>(-INF_D,-1.0), 2), REP<double>(std::stod("-0x1.e666666666667p+0"),-1.0) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), REP<double>(-23.0,-1.0), 3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire(), REP<double>(-23.0,-1.0), 3), REP<double>(-23.0,-1.0) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(0.0,0.0), REP<double>(1.0,2.0), 3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.0C6F7A0B5ED8DP-20"),std::stod("0X1.94C75E6362A6P+3")), REP<double>(1.0,INF_D), 3), REP<double>(1.0,std::stod("0x1.2a3d70a3d70a5p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("-0X1.B6F9DB22D0E55P+2"),std::stod("-0X1.266559F6EC5B1P-5")), REP<double>(-INF_D,-1.0), 3), REP<double>(std::stod("-0x1.e666666666667p+0"),-1.0) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), REP<double>(-3.0,17.3), -2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(0.0,INF_D), REP<double>(-5.1,-0.1), -2), REP<double>(-5.1,-0.1) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(0.0,0.0), REP<double>(27.2,55.1), -2) ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::pown_rev(REP<double>(std::stod("0X1.3F0C482C977C9P-17"),INF_D), REP<double>(-INF_D,-MAX_D), -2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.793D85EF38E47P-3"),std::stod("0X1.388P+13")), REP<double>(1.0,INF_D), -2), REP<double>(1.0,std::stod("0x1.2a3d70a3d70a5p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(std::stod("0X1.1BA81104F6C8P-2"),std::stod("0X1.25D8FA1F801E1P+3")), REP<double>(-INF_D,-1.0), -2), REP<double>(std::stod("-0x1.e666666666667p+0"),-1.0) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), REP<double>(-5.1,55.5), -1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire(), REP<double>(-5.1,55.5), -1), REP<double>(-5.1,55.5) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(0.0,0.0), REP<double>(-5.1,55.5), -1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,-0.0), REP<double>(-1.0,1.0), -1), REP<double>(-1.0,0.0) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(std::stod("0X1.B77C278DBBE13P-2"),std::stod("0X1.9P+6")), REP<double>(-1.0,0.0), -1) ) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty(), REP<double>(-5.1,55.5), -3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire(), REP<double>(-5.1,55.5), -3), REP<double>(-5.1,55.5) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(0.0,0.0), REP<double>(-5.1,55.5), -3) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(-INF_D,0.0), REP<double>(5.1,55.5), -3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<double>(-INF_D,-0.0), REP<double>(-32.0,1.1), -3), REP<double>(-32.0,0.0) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<double>(1.0,-MAX_D), REP<double>(-1.0,5.0), 5) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::pown_rev(REP<double>(3.0,4.0), REP<double>(5.0,-7.1), 1), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_pown_rev_mixedtype_test)
{
    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP<double>(0.01,2.33), 1), REP<float>(std::stod("0x1.47ae14p-7"),std::stod("0x1.2a3d72p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<float>(-1.9f,-0.33f), 1), REP<double>(std::stod("-0x1.e66666p+0"),std::stod("-0x1.51eb86p-2")) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP<double>(std::stod("0X1.A36E2EB1C432CP-14"),std::stod("0X1.5B7318FC50482P+2")), 2), REP<float>(std::stof("-0x1.2a3d72p+1"),std::stof("0x1.2a3d72p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<float>(std::stof("0X1.BE0DECP-4"),std::stof("0X1.CE147CP+1")), 2), REP<double>(std::stod("-0x1.e66666fd4e25bp+0"),std::stod("0x1.e66666fd4e25bp+0")) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP<double>(std::stod("0X1.0C6F7A0B5ED8DP-20"),std::stod("0X1.94C75E6362A6P+3")), 3), REP<float>(std::stof("0x1.47ae14p-7"),std::stof("0x1.2a3d72p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<float>(std::stof("-0X1.B6F9DCP+2"),std::stof("-0X1.266558P-5")), 3), REP<double>(std::stod("-0x1.e66666b817d3cp+0"),std::stod("-0x1.51eb845e4b647p-2")) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP<double>(std::stod("0X1.2DC80DB11AB7CP-10"),std::stod("0X1.1C37937E08P+53")), -8), REP<float>(std::stof("-0x1.2a3d72p+1"),std::stof("0x1.2a3d72p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<float>(std::stof("0X1.81E104P-8"),std::stof("0X1.BC64F4P+12")), -8), REP<double>(std::stod("-0x1.e666668aa72b1p+0"),std::stod("0x1.e666668aa72b1p+0")) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP<double>(std::stod("0X1.B77C278DBBE13P-2"),std::stod("0X1.9P+6")), -1), REP<float>(std::stof("0x1.47ae14p-7"),std::stof("0x1.2a3d72p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<float>(std::stof("-0X1.83E0FAP+1"),std::stof("-0X1.0D7942P-1")), -1), REP<double>(std::stod("-0x1.e66668deb8553p+0"),std::stod("-0x1.51eb8396bb9a8p-2")) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP<double>(std::stod("0X1.5F934D64162A9P-9"),std::stod("0X1.6BCC41E9P+46")), -7), REP<float>(std::stof("0x1.47ae14p-7"),std::stof("0x1.2a3d72p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<float>(std::stof("-0X1.254CDEP+11"),std::stof("-0X1.6E95C4P-7")), -7), REP<double>(std::stod("-0x1.e6666686208a1p+0"),std::stod("-0x1.51eb84fda61e4p-2")) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty( F<float>::pown_rev(REP<double>(1.0,-MAX_D), 5) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::pown_rev(REP<float>(3.0f,-4.0f), 1), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_pown_rev_bin_mixedtype_test)
{
    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP<double>(std::stod("0X1.A36E2EB1C432CP-14"),std::stod("0X1.5B7318FC50482P+2")), REP<double>(1.0,INF_D), 2), REP<float>(1.0f,std::stof("0x1.2a3d72p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<float>(std::stof("0X1.BE0DECP-4"),std::stof("0X1.CE147CP+1")), REP<float>(-INF_F,-1.0f), 2), REP<double>(std::stod("-0x1.e66666fd4e25bp+0"),-1.0) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP<double>(std::stod("0X1.0C6F7A0B5ED8DP-20"),std::stod("0X1.94C75E6362A6P+3")), REP<double>(1.0,INF_D), 3), REP<float>(1.0,std::stof("0x1.2a3d72p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<float>(std::stof("-0X1.B6F9DCP+2"),std::stod("-0X1.266558P-5")), REP<float>(-INF_F,-1.0f), 3), REP<double>(std::stod("-0x1.e66666b817d3cp+0"),-1.0) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP<double>(std::stod("0X1.793D85EF38E47P-3"),std::stod("0X1.388P+13")), REP<double>(1.0,INF_D), -2), REP<float>(1.0,std::stof("0x1.2a3d72p+1")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<float>(std::stof("0X1.1BA810P-2"),std::stof("0X1.25D8FCP+3")), REP<float>(-INF_F,-1.0f), -2), REP<double>(std::stod("-0x1.e666674624dddp+0"),-1.0) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(F<double>::entire(), REP<double>(-5.1,55.5), -1), REP<float>(std::stod("-0x1.466668p+2"),std::stod("0x1.bcp+5")) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP<float>(std::stof("0X1.B77C26P-2"),std::stof("0X1.9P+6")), REP<float>(-1.0f,0.0f), -1) ) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(F<double>::entire(), REP<double>(-5.1,55.5), -3), REP<float>(std::stod("-0x1.466668p+2"),std::stod("0x1.bcp+5")) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP<float>(-INF_F,-0.0f), REP<float>(-32.0f,1.1f), -3), REP<double>(-32.0,0.0) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty( F<float>::pown_rev(REP<double>(1.0,-MAX_D), REP<double>(-1.0,5.0), 5) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::pown_rev(REP<float>(3.0f,4.0f), REP<double>(5.0,-7.1), 1), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_pown_rev_dec_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), 0) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(1.0,1.0),DEC::com), 0), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-1.0,5.0),DEC::dac), 0), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(-1.0,0.0),DEC::def), 0) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(-1.0,-0.0),DEC::dac), 0) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(1.1,10.0),DEC::com), 0) ) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), 1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire_dec(), 1), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::com), 1), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::dac), 1), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(13.1,13.1),DEC::def), 1), REP_DEC<double>(REP<double>(13.1,13.1),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-7451.145,-7451.145),DEC::dac), 1), REP_DEC<double>(REP<double>(-7451.145,-7451.145),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(MAX_D,MAX_D),DEC::com), 1), REP_DEC<double>(REP<double>(MAX_D,MAX_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-MAX_D,-MAX_D),DEC::com), 1), REP_DEC<double>(REP<double>(-MAX_D,-MAX_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac), 1), REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,INF_D),DEC::dac), 1), REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::def), 1), REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,-0.0),DEC::def), 1), REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-324.3,2.5),DEC::dac), 1), REP_DEC<double>(REP<double>(-324.3,2.5),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.01,2.33),DEC::com), 1), REP_DEC<double>(REP<double>(0.01,2.33),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-1.9,-0.33),DEC::def), 1), REP_DEC<double>(REP<double>(-1.9,-0.33),DEC::trv) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), 2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac), 2), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,INF_D),DEC::def), 2), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::com), 2), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::dac), 2), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.573851EB851EBP+7"),std::stod("0X1.573851EB851ECP+7")),DEC::def), 2), REP_DEC<double>(REP<double>(std::stod("-0x1.a333333333334p+3"),std::stod("0x1.a333333333334p+3")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.A794A4E7CFAADP+25"),std::stod("0X1.A794A4E7CFAAEP+25")),DEC::def), 2), REP_DEC<double>(REP<double>(std::stod("-0x1.d1b251eb851edp+12"),std::stod("0x1.d1b251eb851edp+12")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(MAX_D,MAX_D),DEC::dac), 2), REP_DEC<double>(REP<double>(std::stod("-0x1p+512"),std::stod("0x1p+512")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,std::stod("0X1.9AD27D70A3D72P+16")),DEC::dac), 2), REP_DEC<double>(REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.444cccccccccep+8")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,std::stod("0X1.9AD27D70A3D72P+16")),DEC::def), 2), REP_DEC<double>(REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.444cccccccccep+8")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.A36E2EB1C432CP-14"),std::stod("0X1.5B7318FC50482P+2")),DEC::com), 2), REP_DEC<double>(REP<double>(std::stod("-0x1.2a3d70a3d70a5p+1"),std::stod("0x1.2a3d70a3d70a5p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.BE0DED288CE7P-4"),std::stod("0X1.CE147AE147AE1P+1")),DEC::def), 2), REP_DEC<double>(REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("0x1.e666666666667p+0")),DEC::trv) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), 8) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire_dec(), 8), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac), 8), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,INF_D),DEC::dac), 8), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::def), 8), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::dac), 8), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.9D8FD495853F5P+29"),std::stod("0X1.9D8FD495853F6P+29")),DEC::com), 8), REP_DEC<double>(REP<double>(std::stod("-0x1.a333333333334p+3"),std::stod("0x1.a333333333334p+3")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.DFB1BB622E70DP+102"),std::stod("0X1.DFB1BB622E70EP+102")),DEC::dac), 8), REP_DEC<double>(REP<double>(std::stod("-0x1.d1b251eb851edp+12"),std::stod("0x1.d1b251eb851edp+12")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(MAX_D,MAX_D),DEC::def), 8), REP_DEC<double>(REP<double>(std::stod("-0x1p+128"),std::stod("0x1p+128")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,std::stod("0X1.A87587109655P+66")),DEC::dac), 8), REP_DEC<double>(REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.444cccccccccep+8")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,std::stod("0X1.A87587109655P+66")),DEC::def), 8), REP_DEC<double>(REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.444cccccccccep+8")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.CD2B297D889BDP-54"),std::stod("0X1.B253D9F33CE4DP+9")),DEC::com), 8), REP_DEC<double>(REP<double>(std::stod("-0x1.2a3d70a3d70a5p+1"),std::stod("0x1.2a3d70a3d70a5p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.26F1FCDD502A3P-13"),std::stod("0X1.53ABD7BFC4FC6P+7")),DEC::dac), 8), REP_DEC<double>(REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("0x1.e666666666667p+0")),DEC::trv) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), 3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire_dec(), 3), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::dac), 3), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::def), 3), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev( REP_DEC<double>(REP<double>(std::stod("0X1.1902E978D4FDEP+11"),std::stod("0X1.1902E978D4FDFP+11")),DEC::com), 3), REP_DEC<double>(REP<double>(std::stod("0x1.a333333333332p+3"),std::stod("0x1.a333333333334p+3")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X1.81460637B9A3DP+38"),std::stod("-0X1.81460637B9A3CP+38")),DEC::def), 3), REP_DEC<double>(REP<double>(std::stod("-0x1.d1b251eb851edp+12"),std::stod("-0x1.d1b251eb851ebp+12")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(MAX_D,MAX_D),DEC::dac), 3), REP_DEC<double>(REP<double>(std::stod("0x1.428a2f98d728ap+341"),std::stod("0x1.428a2f98d728bp+341")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-MAX_D,-MAX_D),DEC::com), 3), REP_DEC<double>(REP<double>(std::stod("-0x1.428a2f98d728bp+341"), std::stod("-0x1.428a2f98d728ap+341")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::def), 3), REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,INF_D),DEC::def), 3), REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::dac), 3), REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,-0.0),DEC::def), 3), REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X1.0436D2F418938P+25"),std::stod("0X1.F4P+3")),DEC::com), 3), REP_DEC<double>(REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.4p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.0C6F7A0B5ED8DP-20"),std::stod("0X1.94C75E6362A6P+3")),DEC::dac), 3), REP_DEC<double>(REP<double>(std::stod("0x1.47ae147ae147ap-7"),std::stod("0x1.2a3d70a3d70a5p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X1.B6F9DB22D0E55P+2"),std::stod("-0X1.266559F6EC5B1P-5")),DEC::def), 3), REP_DEC<double>(REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("-0x1.51eb851eb851ep-2")),DEC::trv) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), 7) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire_dec(), 7), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::com), 7), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::dac), 7), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.F91D1B185493BP+25"),std::stod("0X1.F91D1B185493CP+25")),DEC::def), 7), REP_DEC<double>(REP<double>(std::stod("0x1.a333333333332p+3"),std::stod("0x1.a333333333334p+3")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X1.07B1DA32F9B59P+90"),std::stod("-0X1.07B1DA32F9B58P+90")),DEC::dac), 7), REP_DEC<double>(REP<double>(std::stod("-0x1.d1b251eb851edp+12"),std::stod("-0x1.d1b251eb851ebp+12")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(MAX_D,MAX_D),DEC::com), 7), REP_DEC<double>(REP<double>(std::stod("0x1.381147622f886p+146"),std::stod("0x1.381147622f887p+146")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-MAX_D,-MAX_D),DEC::def), 7), REP_DEC<double>(REP<double>(std::stod("-0x1.381147622f887p+146"),std::stod("-0x1.381147622f886p+146")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac), 7), REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,INF_D),DEC::dac), 7), REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::def), 7), REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,-0.0),DEC::def), 7), REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X1.4F109959E6D7FP+58"),std::stod("0X1.312DP+9")),DEC::dac), 7), REP_DEC<double>(REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.4p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.6849B86A12B9BP-47"),std::stod("0X1.74D0373C76313P+8")),DEC::com), 7), REP_DEC<double>(REP<double>(std::stod("0x1.47ae147ae147ap-7"),std::stod("0x1.2a3d70a3d70a5p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X1.658C775099757P+6"),std::stod("-0X1.BEE30301BF47AP-12")),DEC::def), 7), REP_DEC<double>(REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("-0x1.51eb851eb851ep-2")),DEC::trv) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), -2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac), -2), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,INF_D),DEC::dac), -2), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::def), -2) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::com), -2) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(-10.0,0.0),DEC::dac), -2) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(-10.0,-0.0),DEC::def), -2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.7DE3A077D1568P-8"),std::stod("0X1.7DE3A077D1569P-8")),DEC::dac), -2), REP_DEC<double>(REP<double>(std::stod("-0x1.a333333333335p+3"),std::stod("0x1.a333333333335p+3")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.3570290CD6E14P-26"),std::stod("0X1.3570290CD6E15P-26")),DEC::def), -2), REP_DEC<double>(REP<double>(std::stod("-0x1.d1b251eb851eep+12"),std::stod("0x1.d1b251eb851eep+12")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")),DEC::com), -2), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.3F0C482C977C9P-17"),INF_D),DEC::dac), -2), REP_DEC<double>(REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.444cccccccccep+8")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.793D85EF38E47P-3"),std::stod("0X1.388P+13")),DEC::def), -2), REP_DEC<double>(REP<double>(std::stod("-0x1.2a3d70a3d70a5p+1"),std::stod("0x1.2a3d70a3d70a5p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.1BA81104F6C8P-2"),std::stod("0X1.25D8FA1F801E1P+3")),DEC::com), -2), REP_DEC<double>(REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("0x1.e666666666667p+0")),DEC::trv) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), -8) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::def), -8), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,INF_D),DEC::dac), -8), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::def), -8) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::dac), -8) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.3CEF39247CA6DP-30"),std::stod("0X1.3CEF39247CA6EP-30")),DEC::com), -8), REP_DEC<double>(REP<double>(std::stod("-0x1.a333333333335p+3"),std::stod("0x1.a333333333335p+3")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.113D9EF0A99ACP-103"),std::stod("0X1.113D9EF0A99ADP-103")),DEC::def), -8), REP_DEC<double>(REP<double>(std::stod("-0x1.d1b251eb851eep+12"),std::stod("0x1.d1b251eb851eep+12")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")),DEC::dac), -8), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.34CC3764D1E0CP-67"),INF_D),DEC::def), -8), REP_DEC<double>(REP<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.444cccccccccep+8")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.2DC80DB11AB7CP-10"),std::stod("0X1.1C37937E08P+53")),DEC::com), -8), REP_DEC<double>(REP<double>(std::stod("-0x1.2a3d70a3d70a5p+1"),std::stod("0x1.2a3d70a3d70a5p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.81E104E61630DP-8"),std::stod("0X1.BC64F21560E34P+12")),DEC::def), -8), REP_DEC<double>(REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("0x1.e666666666667p+0")),DEC::trv) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), -1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire_dec(), -1), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::dac), -1) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::dac), -1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.38ABF82EE6986P-4"),std::stod("0X1.38ABF82EE6987P-4")),DEC::def), -1), REP_DEC<double>(REP<double>(std::stod("0x1.a333333333332p+3"),std::stod("0x1.a333333333335p+3")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X1.197422C9048BFP-13"),std::stod("-0X1.197422C9048BEP-13")),DEC::dac), -1), REP_DEC<double>(REP<double>(std::stod("-0x1.d1b251eb851eep+12"),std::stod("-0x1.d1b251eb851ebp+12")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X0.4P-1022"),std::stod("0X0.4000000000001P-1022")),DEC::dac), -1), REP_DEC<double>(REP<double>(std::stod("0x1.ffffffffffff8p+1023"),INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X0.4000000000001P-1022"),std::stod("-0X0.4P-1022")),DEC::def), -1), REP_DEC<double>(REP<double>(-INF_D,std::stod("-0x1.ffffffffffff8p+1023")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac), -1), REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,INF_D),DEC::dac), -1), REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::dac), -1), REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,-0.0),DEC::def), -1), REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.B77C278DBBE13P-2"),std::stod("0X1.9P+6")),DEC::com), -1), REP_DEC<double>(REP<double>(std::stod("0x1.47ae147ae147ap-7"),std::stod("0x1.2a3d70a3d70a5p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X1.83E0F83E0F83EP+1"),std::stod("-0X1.0D79435E50D79P-1")),DEC::com), -1), REP_DEC<double>(REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("-0x1.51eb851eb851ep-2")),DEC::trv) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), -3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire_dec(), -3), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::def), -3) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::dac), -3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.D26DF4D8B1831P-12"),std::stod("0X1.D26DF4D8B1832P-12")),DEC::com), -3), REP_DEC<double>(REP<double>(std::stod("0x1.a333333333331p+3"),std::stod("0x1.a333333333335p+3")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X1.54347DED91B19P-39"),std::stod("-0X1.54347DED91B18P-39")),DEC::def), -3), REP_DEC<double>(REP<double>(std::stod("-0x1.d1b251eb851eep+12"),std::stod("-0x1.d1b251eb851eap+12")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")),DEC::dac), -3), REP_DEC<double>(REP<double>(std::stod("0x1p+358"),INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("-0X0P+0")),DEC::def), -3), REP_DEC<double>(REP<double>(-INF_D,std::stod("-0x1p+358")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac), -3), REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,INF_D),DEC::dac), -3), REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::def), -3), REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,-0.0),DEC::def), -3), REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.43CFBA61AACABP-4"),std::stod("0X1.E848P+19")),DEC::com), -3), REP_DEC<double>(REP<double>(std::stod("0x1.47ae147ae147ap-7"),std::stod("0x1.2a3d70a3d70a5p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X1.BD393CE9E8E7CP+4"),std::stod("-0X1.2A95F6F7C066CP-3")),DEC::def), -3), REP_DEC<double>(REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("-0x1.51eb851eb851ep-2")),DEC::trv) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), -7) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire_dec(), -7), REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::com), -7) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::def), -7) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.037D76C912DBCP-26"),std::stod("0X1.037D76C912DBDP-26")),DEC::dac), -7), REP_DEC<double>(REP<double>(std::stod("0x1.a333333333332p+3"),std::stod("0x1.a333333333335p+3")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X1.F10F41FB8858FP-91"),std::stod("-0X1.F10F41FB8858EP-91")),DEC::dac), -7), REP_DEC<double>(REP<double>(std::stod("-0x1.d1b251eb851eep+12"),std::stod("-0x1.d1b251eb851ebp+12")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")),DEC::def), -7), REP_DEC<double>(REP<double>(std::stod("0x1.588cea3f093bcp+153"),INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X0.0000000000001P-1022"),std::stod("-0X0P+0")),DEC::def), -7), REP_DEC<double>(REP<double>(-INF_D,std::stod("-0x1.588cea3f093bcp+153")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac), -7), REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,INF_D),DEC::def), -7), REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::dac), -7), REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,-0.0),DEC::def), -7), REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.5F934D64162A9P-9"),std::stod("0X1.6BCC41E9P+46")),DEC::com), -7), REP_DEC<double>(REP<double>(std::stod("0x1.47ae147ae147ap-7"),std::stod("0x1.2a3d70a3d70a5p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X1.254CDD3711DDBP+11"),std::stod("-0X1.6E95C4A761E19P-7")),DEC::com), -7), REP_DEC<double>(REP<double>(std::stod("-0x1.e666666666667p+0"),std::stod("-0x1.51eb851eb851ep-2")),DEC::trv) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai( F<double>::pown_rev(REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::def), 5) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::pown_rev(REP_DEC<double>(REP<double>(3.0,-4.0),DEC::dac), 1), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_pown_rev_dec_bin_test)
{
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), REP_DEC<double>(REP<double>(1.0,1.0),DEC::def), 0) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(1.0,1.0),DEC::dac), REP_DEC<double>(REP<double>(1.0,1.0),DEC::dac), 0), REP_DEC<double>(REP<double>(1.0,1.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-1.0,5.0),DEC::def), REP_DEC<double>(REP<double>(-51.0,12.0),DEC::dac), 0), REP_DEC<double>(REP<double>(-51.0,12.0),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(-1.0,0.0),DEC::com), REP_DEC<double>(REP<double>(5.0,10.0),DEC::dac), 0) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(-1.0,-0.0),DEC::dac), REP_DEC<double>(REP<double>(-1.0,1.0),DEC::def), 0) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(1.1,10.0),DEC::def),REP_DEC<double>(REP<double>(1.0,41.0),DEC::dac), 0) ) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), REP_DEC<double>(REP<double>(0.0,100.1),DEC::dac), 1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire_dec(), REP_DEC<double>(REP<double>(-5.1,10.0),DEC::def), 1), REP_DEC<double>(REP<double>(-5.1,10.0),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::com), REP_DEC<double>(REP<double>(-10.0,5.1),DEC::dac), 1), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::def), REP_DEC<double>(REP<double>(1.0,5.0),DEC::dac), 1) ) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), REP_DEC<double>(REP<double>(5.0,17.1),DEC::def), 2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac), REP_DEC<double>(REP<double>(5.6,27.544),DEC::dac), 2), REP_DEC<double>(REP<double>(5.6,27.544),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::def), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def), 2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.A36E2EB1C432CP-14"),std::stod("0X1.5B7318FC50482P+2")),DEC::com), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::def), 2), REP_DEC<double>(REP<double>(1.0,std::stod("0x1.2a3d70a3d70a5p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.BE0DED288CE7P-4"),std::stod("0X1.CE147AE147AE1P+1")),DEC::dac), REP_DEC<double>(REP<double>(-INF_D,-1.0),DEC::def), 2), REP_DEC<double>(REP<double>(std::stod("-0x1.e666666666667p+0"),-1.0),DEC::trv) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-23.0,-1.0),DEC::dac), 3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire_dec(), REP_DEC<double>(REP<double>(-23.0,-1.0),DEC::com), 3), REP_DEC<double>(REP<double>(-23.0,-1.0),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::def), REP_DEC<double>(REP<double>(1.0,2.0),DEC::dac), 3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.0C6F7A0B5ED8DP-20"),std::stod("0X1.94C75E6362A6P+3")),DEC::com), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::dac), 3), REP_DEC<double>(REP<double>(1.0,std::stod("0x1.2a3d70a3d70a5p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("-0X1.B6F9DB22D0E55P+2"),std::stod("-0X1.266559F6EC5B1P-5")),DEC::com), REP_DEC<double>(REP<double>(-INF_D,-1.0),DEC::dac), 3), REP_DEC<double>(REP<double>(std::stod("-0x1.e666666666667p+0"),-1.0),DEC::trv) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-3.0,17.3),DEC::def), -2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac), REP_DEC<double>(REP<double>(-5.1,-0.1),DEC::dac), -2), REP_DEC<double>(REP<double>(-5.1,-0.1),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::def), REP_DEC<double>(REP<double>(27.2,55.1),DEC::dac), -2) ) );
    BOOST_CHECK( F<double>::is_empty(F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.3F0C482C977C9P-17"),INF_D),DEC::def), REP_DEC<double>(REP<double>(-INF_D,-MAX_D),DEC::dac), -2) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.793D85EF38E47P-3"),std::stod("0X1.388P+13")),DEC::com), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::dac), -2), REP_DEC<double>(REP<double>(1.0,std::stod("0x1.2a3d70a3d70a5p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.1BA81104F6C8P-2"),std::stod("0X1.25D8FA1F801E1P+3")),DEC::com), REP_DEC<double>(REP<double>(-INF_D,-1.0),DEC::dac), -2), REP_DEC<double>(REP<double>(std::stod("-0x1.e666666666667p+0"),-1.0),DEC::trv) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-5.1,55.5),DEC::def), -1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire_dec(), REP_DEC<double>(REP<double>(-5.1,55.5),DEC::dac), -1), REP_DEC<double>(REP<double>(-5.1,55.5),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::dac), REP_DEC<double>(REP<double>(-5.1,55.5),DEC::def), -1) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,-0.0),DEC::dac), REP_DEC<double>(REP<double>(-1.0,1.0),DEC::com), -1), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.B77C278DBBE13P-2"),std::stod("0X1.9P+6")),DEC::def), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::dac), -1) ) );

    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-5.1,55.5),DEC::dac), -3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(F<double>::entire_dec(), REP_DEC<double>(REP<double>(-5.1,55.5),DEC::def), -3), REP_DEC<double>(REP<double>(-5.1,55.5),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(0.0,0.0),DEC::def), REP_DEC<double>(REP<double>(-5.1,55.5),DEC::def), -3) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::dac), REP_DEC<double>(REP<double>(5.1,55.5),DEC::com), -3) ) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<double>(REP<double>(-INF_D,-0.0),DEC::dac), REP_DEC<double>(REP<double>(-32.0,1.1),DEC::def), -3), REP_DEC<double>(REP<double>(-32.0,0.0),DEC::trv) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai( F<double>::pown_rev(REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::com), REP_DEC<double>(REP<double>(-1.0,5.0),DEC::dac), 5) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::pown_rev(REP_DEC<double>(REP<double>(3.0,4.0),DEC::def), REP_DEC<double>(REP<double>(5.0,-7.1),DEC::def), 1), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_pown_rev_dec_mixedtype_test)
{
    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP_DEC<double>(REP<double>(0.01,2.33),DEC::com), 1), REP_DEC<float>(REP<float>(std::stod("0x1.47ae14p-7"),std::stod("0x1.2a3d72p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<float>(REP<float>(-1.9f,-0.33f),DEC::com), 1), REP_DEC<double>(REP<double>(std::stod("-0x1.e66666p+0"),std::stod("-0x1.51eb86p-2")),DEC::trv) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.A36E2EB1C432CP-14"),std::stod("0X1.5B7318FC50482P+2")),DEC::def), 2), REP_DEC<float>(REP<float>(std::stof("-0x1.2a3d72p+1"),std::stof("0x1.2a3d72p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<float>(REP<float>(std::stof("0X1.BE0DECP-4"),std::stof("0X1.CE147CP+1")),DEC::dac), 2), REP_DEC<double>(REP<double>(std::stod("-0x1.e66666fd4e25bp+0"),std::stod("0x1.e66666fd4e25bp+0")),DEC::trv) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.0C6F7A0B5ED8DP-20"),std::stod("0X1.94C75E6362A6P+3")),DEC::dac), 3), REP_DEC<float>(REP<float>(std::stof("0x1.47ae14p-7"),std::stof("0x1.2a3d72p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<float>(REP<float>(std::stof("-0X1.B6F9DCP+2"),std::stof("-0X1.266558P-5")),DEC::com), 3), REP_DEC<double>(REP<double>(std::stod("-0x1.e66666b817d3cp+0"),std::stod("-0x1.51eb845e4b647p-2")),DEC::trv) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.2DC80DB11AB7CP-10"),std::stod("0X1.1C37937E08P+53")),DEC::def), -8), REP_DEC<float>(REP<float>(std::stof("-0x1.2a3d72p+1"),std::stof("0x1.2a3d72p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<float>(REP<float>(std::stof("0X1.81E104P-8"),std::stof("0X1.BC64F4P+12")),DEC::dac), -8), REP_DEC<double>(REP<double>(std::stod("-0x1.e666668aa72b1p+0"),std::stod("0x1.e666668aa72b1p+0")),DEC::trv) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.B77C278DBBE13P-2"),std::stod("0X1.9P+6")),DEC::def), -1), REP_DEC<float>(REP<float>(std::stof("0x1.47ae14p-7"),std::stof("0x1.2a3d72p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<float>(REP<float>(std::stof("-0X1.83E0FAP+1"),std::stof("-0X1.0D7942P-1")),DEC::com), -1), REP_DEC<double>(REP<double>(std::stod("-0x1.e66668deb8553p+0"),std::stod("-0x1.51eb8396bb9a8p-2")),DEC::trv) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.5F934D64162A9P-9"),std::stod("0X1.6BCC41E9P+46")),DEC::com), -7), REP_DEC<float>(REP<float>(std::stof("0x1.47ae14p-7"),std::stof("0x1.2a3d72p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<float>(REP<float>(std::stof("-0X1.254CDEP+11"),std::stof("-0X1.6E95C4P-7")),DEC::dac), -7), REP_DEC<double>(REP<double>(std::stod("-0x1.e6666686208a1p+0"),std::stod("-0x1.51eb84fda61e4p-2")),DEC::trv) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai( F<float>::pown_rev(REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::def), 5) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::pown_rev(REP_DEC<float>(REP<float>(3.0f,-4.0f),DEC::dac), 1), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_pown_rev_dec_bin_mixedtype_test)
{
    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.A36E2EB1C432CP-14"),std::stod("0X1.5B7318FC50482P+2")),DEC::com), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::dac), 2), REP_DEC<float>(REP<float>(1.0f,std::stof("0x1.2a3d72p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<float>(REP<float>(std::stof("0X1.BE0DECP-4"),std::stof("0X1.CE147CP+1")),DEC::dac), REP_DEC<float>(REP<float>(-INF_F,-1.0f),DEC::def), 2), REP_DEC<double>(REP<double>(std::stod("-0x1.e66666fd4e25bp+0"),-1.0),DEC::trv) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.0C6F7A0B5ED8DP-20"),std::stod("0X1.94C75E6362A6P+3")),DEC::com), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::dac), 3), REP_DEC<float>(REP<float>(1.0,std::stof("0x1.2a3d72p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<float>(REP<float>(std::stof("-0X1.B6F9DCP+2"),std::stod("-0X1.266558P-5")),DEC::def), REP_DEC<float>(REP<float>(-INF_F,-1.0f),DEC::def), 3), REP_DEC<double>(REP<double>(std::stod("-0x1.e66666b817d3cp+0"),-1.0),DEC::trv) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(REP_DEC<double>(REP<double>(std::stod("0X1.793D85EF38E47P-3"),std::stod("0X1.388P+13")),DEC::def), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::dac), -2), REP_DEC<float>(REP<float>(1.0,std::stof("0x1.2a3d72p+1")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<float>(REP<float>(std::stof("0X1.1BA810P-2"),std::stof("0X1.25D8FCP+3")),DEC::dac), REP_DEC<float>(REP<float>(-INF_F,-1.0f),DEC::dac), -2), REP_DEC<double>(REP<double>(std::stod("-0x1.e666674624dddp+0"),-1.0),DEC::trv) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(F<double>::entire_dec(), REP_DEC<double>(REP<double>(-5.1,55.5),DEC::dac), -1), REP_DEC<float>(REP<float>(std::stod("-0x1.466668p+2"),std::stod("0x1.bcp+5")),DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::pown_rev(REP_DEC<float>(REP<float>(std::stof("0X1.B77C26P-2"),std::stof("0X1.9P+6")),DEC::def), REP_DEC<float>(REP<float>(-1.0f,0.0f),DEC::dac), -1) ) );

    BOOST_CHECK_EQUAL( F<float>::pown_rev(F<double>::entire_dec(), REP_DEC<double>(REP<double>(-5.1,55.5),DEC::def), -3), REP_DEC<float>(REP<float>(std::stod("-0x1.466668p+2"),std::stod("0x1.bcp+5")),DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::pown_rev(REP_DEC<float>(REP<float>(-INF_F,-0.0f),DEC::dac), REP_DEC<float>(REP<float>(-32.0f,1.1f),DEC::dac), -3), REP_DEC<double>(REP<double>(-32.0,0.0),DEC::trv) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai( F<float>::pown_rev(REP_DEC<double>(REP<double>(1.0,-MAX_D),DEC::com), REP_DEC<double>(REP<double>(-1.0,5.0),DEC::dac), 5) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::pown_rev(REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::def), REP_DEC<double>(REP<double>(5.0,-7.1),DEC::dac), 1), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}









BOOST_AUTO_TEST_CASE(minimal_sin_rev_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_cos_rev_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_tan_rev_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_cosh_rev_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_mul_rev_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_div_rev1_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_div_rev2_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_pow_rev1_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_pow_rev2_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_atan2_rev1_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_atan2_rev2_test)
{
    BOOST_CHECK(false);
}
