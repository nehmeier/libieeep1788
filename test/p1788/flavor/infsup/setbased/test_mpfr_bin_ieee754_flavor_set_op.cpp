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

#define BOOST_TEST_MODULE "Flavor: Set operations [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"
#include "test/util/mpfr_bin_ieee754_flavor_io_test_util.hpp"

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

BOOST_AUTO_TEST_CASE(minimal_intersect_test)
{
    BOOST_CHECK_EQUAL( F<double>::intersect(REP<double>(1.0,3.0), REP<double>(2.1,4.0)), REP<double>(2.1,3.0) );
    BOOST_CHECK_EQUAL( F<double>::intersect(REP<double>(1.0,3.0), REP<double>(3.0,4.0)), REP<double>(3.0,3.0) );
    BOOST_CHECK( F<double>::is_empty( F<double>::intersect(REP<double>(1.0,3.0), F<double>::empty()) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::intersect(F<double>::entire(), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::intersect(REP<double>(1.0,3.0), F<double>::entire()), REP<double>(1.0,3.0) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::intersect(REP<double>(1.0,-3.0), F<double>::entire())) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::intersect(REP<double>(1.0,3.0), REP<double>(1.0, NAN_D) ), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_intersect_mixedtype_test)
{
    BOOST_CHECK_EQUAL( F<float>::intersect(REP<float>(-1.0f,3.0f), REP<double>(DNORM_MIN_D,4.0)), REP<float>(0.0f,3.0f) );
    BOOST_CHECK_EQUAL( F<double>::intersect(REP<float>(1.0f,3.0f), REP<double>(3.0,4.0)), REP<double>(3.0,3.0) );
    BOOST_CHECK( F<double>::is_empty( F<double>::intersect(REP<float>(1.0,3.0), F<double>::empty()) ) );
    BOOST_CHECK( F<float>::is_empty( F<float>::intersect(F<double>::entire(), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::intersect(REP<double>(1.0,3.0), F<float>::entire()), REP<double>(1.0,3.0) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty( F<float>::intersect(REP<double>(1.0,-3.0), F<float>::entire())) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<float>::intersect(REP<float>(1.0f,3.0f), REP<double>(1.0, NAN_D) ), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_intersect_dec_test)
{
    BOOST_CHECK_EQUAL( F<double>::intersect(REP_DEC<double>(REP<double>(1.0,3.0), DEC::com), REP_DEC<double>(REP<double>(2.1,4.0), DEC::com)), REP_DEC<double>(REP<double>(2.1,3.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::intersect(REP_DEC<double>(REP<double>(1.0,3.0), DEC::dac), REP_DEC<double>(REP<double>(3.0,4.0), DEC::def)), REP_DEC<double>(REP<double>(3.0,3.0), DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::intersect(REP_DEC<double>(REP<double>(1.0,3.0), DEC::def), F<double>::empty_dec()) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::intersect(F<double>::entire_dec(), F<double>::empty_dec()) ) );
    BOOST_CHECK_EQUAL( F<double>::intersect(REP_DEC<double>(REP<double>(1.0,3.0), DEC::dac), F<double>::entire_dec()), REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai( F<double>::intersect(REP_DEC<double>(REP<double>(1.0,-3.0), DEC::com), REP_DEC<double>(REP<double>(2.1,4.0), DEC::com))) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::intersect(REP_DEC<double>(REP<double>(1.0,3.0), DEC::com), REP_DEC<double>(REP<double>(2.1,INF_D), DEC::com) ), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_intersect_dec_mixedtype_test)
{
    BOOST_CHECK_EQUAL( F<float>::intersect(REP_DEC<float>(REP<float>(-1.0f,3.0f), DEC::com), REP_DEC<double>(REP<double>(DNORM_MIN_D,4.0), DEC::com)), REP_DEC<float>(REP<float>(0.0f,3.0f), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::intersect(REP_DEC<float>(REP<float>(1.0f,3.0f), DEC::dac), REP_DEC<double>(REP<double>(3.0,4.0), DEC::def)), REP_DEC<double>(REP<double>(3.0,3.0), DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::intersect(REP_DEC<float>(REP<float>(1.0,3.0), DEC::def), F<double>::empty_dec()) ) );
    BOOST_CHECK( F<float>::is_empty( F<float>::intersect(F<double>::entire_dec(), F<double>::empty_dec()) ) );
    BOOST_CHECK_EQUAL( F<double>::intersect(REP_DEC<double>(REP<double>(1.0,3.0), DEC::dac), F<float>::entire_dec()), REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv) );


    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai( F<float>::intersect(REP_DEC<double>(REP<double>(1.0,-3.0), DEC::com), REP_DEC<double>(REP<double>(2.1,4.0), DEC::com))) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::intersect(REP_DEC<float>(REP<float>(1.0f,3.0f), DEC::com), REP_DEC<double>(REP<double>(2.1,INF_D), DEC::com) ), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_hull_test)
{
    BOOST_CHECK_EQUAL( F<double>::hull(REP<double>(1.0,3.0), REP<double>(2.1,4.0)), REP<double>(1.0,4.0) );
    BOOST_CHECK_EQUAL( F<double>::hull(REP<double>(1.0,1.0), REP<double>(2.1,4.0)), REP<double>(1.0,4.0) );
    BOOST_CHECK_EQUAL( F<double>::hull(REP<double>(1.0,3.0), F<double>::empty()), REP<double>(1.0,3.0) );
    BOOST_CHECK( F<double>::is_empty( F<double>::hull(F<double>::empty(), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::hull(REP<double>(1.0,3.0), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::hull(REP<double>(1.0,-3.0), F<double>::entire())) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::hull(REP<double>(1.0,3.0), REP<double>(1.0, NAN_D) ), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_hull_mixedtype_test)
{
    BOOST_CHECK_EQUAL( F<float>::hull(REP<double>(DNORM_MIN_D,3.0), REP<double>(3.8,4.0)), REP<float>(0.0f,4.0f) );
    BOOST_CHECK_EQUAL( F<double>::hull(REP<float>(1.0f,1.0f), REP<double>(2.1,4.0)), REP<double>(1.0,4.0) );
    BOOST_CHECK_EQUAL( F<double>::hull(REP<float>(1.0f,3.0f), F<double>::empty()), REP<double>(1.0f,3.0f) );
    BOOST_CHECK( F<double>::is_empty( F<double>::hull(F<float>::empty(), F<double>::empty()) ) );
    BOOST_CHECK_EQUAL( F<double>::hull(REP<double>(1.0,3.0), F<float>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty( F<float>::hull(REP<double>(1.0,-3.0), F<double>::entire())) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::hull(REP<float>(1.0f,3.0f), REP<double>(1.0, NAN_D) ), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_hull_dec_test)
{
    BOOST_CHECK_EQUAL( F<double>::hull(REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv), REP_DEC<double>(REP<double>(2.1,4.0), DEC::trv)), REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::hull(REP_DEC<double>(REP<double>(1.0,1.0), DEC::trv), REP_DEC<double>(REP<double>(2.1,4.0), DEC::trv)), REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::hull(REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv), F<double>::empty_dec()), REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::hull(F<double>::empty_dec(), F<double>::empty_dec()) ) );
    BOOST_CHECK_EQUAL( F<double>::hull(REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv), F<double>::entire_dec()), REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai( F<double>::hull(REP_DEC<double>(REP<double>(1.0,-3.0), DEC::trv), F<double>::entire_dec())) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::hull(REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv), REP_DEC<double>(REP<double>(1.0, NAN_D), DEC::trv) ), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_hull_dec_mixedtype_test)
{
    BOOST_CHECK_EQUAL( F<float>::hull(REP_DEC<double>(REP<double>(DNORM_MIN_D,3.0), DEC::trv), REP_DEC<double>(REP<double>(3.8,4.0), DEC::trv)), REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::hull(REP_DEC<float>(REP<float>(1.0f,1.0f), DEC::trv), REP_DEC<double>(REP<double>(2.1,4.0), DEC::trv)), REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::hull(REP_DEC<float>(REP<float>(1.0f,3.0f), DEC::trv), F<double>::empty_dec()), REP_DEC<double>(REP<double>(1.0f,3.0f), DEC::trv) );
    BOOST_CHECK( F<double>::is_empty( F<double>::hull(F<float>::empty_dec(), F<double>::empty_dec()) ) );
    BOOST_CHECK_EQUAL( F<double>::hull(REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv), F<float>::entire_dec()), REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai( F<float>::hull(REP_DEC<double>(REP<double>(1.0,-3.0), DEC::trv), F<double>::entire_dec())) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::hull(REP_DEC<float>(REP<float>(1.0f,3.0f), DEC::trv), REP_DEC<double>(REP<double>(1.0, NAN_D), DEC::trv) ), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}
