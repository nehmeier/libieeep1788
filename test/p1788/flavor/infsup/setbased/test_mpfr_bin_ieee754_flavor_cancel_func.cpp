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

#define BOOST_TEST_MODULE "Flavor: Cancellative addition and subtraction [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
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
const double MAX_D = std::numeric_limits<double>::max();
const double MIN_D = std::numeric_limits<double>::min();

const float INF_F = std::numeric_limits<float>::infinity();
const float MAX_F = std::numeric_limits<float>::max();


BOOST_AUTO_TEST_CASE(minimal_cancel_plus_test)
{
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-INF_D, -1.0), F<double>::empty()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-1.0, INF_D), F<double>::empty()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::entire(), F<double>::empty()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-INF_D, -1.0), REP<double>(-5.0,1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-1.0, INF_D), REP<double>(-5.0,1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::entire(), REP<double>(-5.0,1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-INF_D, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-1.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::empty(), REP<double>(1.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::empty(), REP<double>(-INF_D,1.0)),F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::empty(), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-1.0,5.0), REP<double>(1.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-1.0,5.0), REP<double>(-INF_D,1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-1.0,5.0), F<double>::entire() ), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::entire(), REP<double>(1.0,INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::entire(), REP<double>(-INF_D,1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::entire(), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-5.0, -1.0), REP<double>(1.0,5.1)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-5.0, -1.0), REP<double>(0.9,5.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-5.0, -1.0), REP<double>(0.9,5.1)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-10.0, 5.0), REP<double>(-5.0,10.1)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-10.0, 5.0), REP<double>(-5.1,10.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-10.0, 5.0), REP<double>(-5.1,10.1)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(1.0, 5.0), REP<double>(-5.0,-0.9)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(1.0, 5.0), REP<double>(-5.1,-1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(1.0, 5.0), REP<double>(-5.1,-0.9)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-10.0, -1.0), F<double>::empty()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-10.0, 5.0), F<double>::empty()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(1.0, 5.0), F<double>::empty()), F<double>::entire() );


    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_plus(F<double>::empty(), F<double>::empty() ) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_plus(F<double>::empty(), REP<double>(1.0,10.0) ) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_plus(F<double>::empty(), REP<double>(-5.0,10.0) ) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_plus(F<double>::empty(), REP<double>(-5.0,-1.0) ) ) );

    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-5.1,-0.0), REP<double>(0.0,5.0)), REP<double>(std::stod("-0X1.999999999998P-4"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-5.1,-1.0), REP<double>(1.0,5.0)), REP<double>(std::stod("-0X1.999999999998P-4"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-5.0,-0.9), REP<double>(1.0,5.0)), REP<double>(0.0, std::stod("0X1.9999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-5.1,-0.9), REP<double>(1.0,5.0)), REP<double>(std::stod("-0X1.999999999998P-4"),std::stod("0X1.9999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-5.0,-1.0), REP<double>(1.0,5.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-10.1, 5.0), REP<double>(-5.0,10.0)), REP<double>(std::stod("-0X1.999999999998P-4"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-10.0, 5.1), REP<double>(-5.0,10.0)), REP<double>(0.0,std::stod("0X1.999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-10.1, 5.1), REP<double>(-5.0,10.0)), REP<double>(std::stod("-0X1.999999999998P-4"),std::stod("0X1.999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-10.0, 5.0), REP<double>(-5.0,10.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(0.9, 5.0), REP<double>(-5.0,-1.0)), REP<double>(std::stod("-0X1.9999999999998P-4"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(1.0, 5.1), REP<double>(-5.0,-1.0)), REP<double>(0.0,std::stod("0X1.999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(0.0, 5.1), REP<double>(-5.0,-0.0)), REP<double>(0.0,std::stod("0X1.999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(0.9, 5.1), REP<double>(-5.0,-1.0)), REP<double>(std::stod("-0X1.9999999999998P-4"),std::stod("0X1.999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(1.0, 5.0), REP<double>(-5.0,-1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(0.0, 5.0), REP<double>(-5.0,-0.0)), REP<double>(0.0,0.0) );

    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(std::stod("0X1.FFFFFFFFFFFFP+0"),std::stod("0X1.FFFFFFFFFFFFP+0")), REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("-0X1.999999999999AP-4"))), REP<double>(std::stod("0X1.E666666666656P+0"),std::stod("0X1.E666666666657P+0")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("0X1.FFFFFFFFFFFFP+0")), REP<double>(std::stod("-0X1.999999999999AP-4"),0.01)), REP<double>(std::stod("-0X1.70A3D70A3D70BP-4"),std::stod("0X1.E666666666657P+0")) );

    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(MAX_D,MAX_D), REP<double>(MAX_D,MAX_D)), REP<double>(MAX_D,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-MAX_D,MAX_D), REP<double>(-MAX_D,MAX_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-MAX_D,MAX_D), REP<double>(std::stod("-0X1.FFFFFFFFFFFFEP+1023"),MAX_D)), REP<double>(0.0,std::stod("0X1P+971")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-MAX_D,MAX_D), REP<double>(-MAX_D,std::stod("0X1.FFFFFFFFFFFFEP+1023"))), REP<double>(std::stod("-0X1P+971"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(-MAX_D,std::stod("0X1.FFFFFFFFFFFFEP+1023")), REP<double>(-MAX_D,MAX_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(std::stod("-0X1.FFFFFFFFFFFFEP+1023"),MAX_D), REP<double>(-MAX_D,MAX_D)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFFP-53")), REP<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFEP-53"))), REP<double>(std::stod("-0X1.FFFFFFFFFFFFFP-1"),std::stod("-0X1.FFFFFFFFFFFFEP-1")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFEP-53")), REP<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFFP-53"))), F<double>::entire() );


    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_plus(REP<double>(1.0,-MAX_D), REP<double>(3.0,4.0)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::cancel_plus(REP<double>(1.0,MAX_D), REP<double>(3.0,-4.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_cancel_plus_mixedtype_test)
{
    BOOST_CHECK_EQUAL( F<float>::cancel_plus(REP<double>(-5.0,-0.9), REP<double>(1.0,5.0)), REP<float>(0.0f, std::stof("0X1.99999AP-4")) );
    BOOST_CHECK_EQUAL( F<float>::cancel_plus(REP<double>(-5.1,-0.9), REP<double>(1.0,5.0)), REP<float>(std::stof("-0X1.99999AP-4"),std::stof("0X1.99999AP-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<float>(-10.1f, 5.1f), REP<float>(-5.0f,10.0f)), REP<double>(std::stod("-0x1.999ap-4"),std::stod("0x1.99998p-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<float>(std::stof("-0X1.99999AP-4"),std::stof("0X1.FFFFFFP+0")), REP<float>(std::stof("-0X1.99999AP-4"),0.01f)), REP<double>(std::stod("-0x1.70a3d78p-4"),std::stod("0x1.e666666p+0")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP<float>(std::stof("-0X1P+0"),std::stof("0X1.FFFFFCP-53")), REP<float>(std::stof("-0X1P+0"),std::stod("0X1.FFFFFEP-53"))), F<double>::entire() );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty( F<float>::cancel_plus(REP<double>(1.0,-MAX_D), REP<double>(3.0,4.0)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::cancel_plus(REP<double>(1.0,MAX_D), REP<float>(3.0f,-4.0f)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_cancel_plus_dec_test)
{
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-INF_D, -1.0), DEC::dac), F<double>::empty_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-1.0, INF_D), DEC::def), F<double>::empty_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::entire_dec(), F<double>::empty_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-INF_D, -1.0), DEC::dac), REP_DEC<double>(REP<double>(-5.0,1.0), DEC::com)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-1.0, INF_D), DEC::trv), REP_DEC<double>(REP<double>(-5.0,1.0), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::entire_dec(), REP_DEC<double>(REP<double>(-5.0,1.0), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-INF_D, -1.0), DEC::dac), F<double>::entire_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-1.0, INF_D), DEC::def), F<double>::entire_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::empty_dec(), REP_DEC<double>(REP<double>(1.0, INF_D), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-INF_D,1.0), DEC::trv)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::empty_dec(), F<double>::entire_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-1.0,5.0), DEC::dac), REP_DEC<double>(REP<double>(1.0,INF_D), DEC::dac)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-1.0,5.0), DEC::def), REP_DEC<double>(REP<double>(-INF_D,1.0), DEC::dac)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-1.0,5.0), DEC::com), F<double>::entire_dec() ), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::entire_dec(), REP_DEC<double>(REP<double>(1.0,INF_D), DEC::dac)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::entire_dec(), REP_DEC<double>(REP<double>(-INF_D,1.0), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(F<double>::entire_dec(), F<double>::entire_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );

    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-5.0, -1.0), DEC::com), REP_DEC<double>(REP<double>(1.0,5.1), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-5.0, -1.0), DEC::dac), REP_DEC<double>(REP<double>(0.9,5.0), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-5.0, -1.0), DEC::def), REP_DEC<double>(REP<double>(0.9,5.1), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::trv), REP_DEC<double>(REP<double>(-5.0,10.1), DEC::dac)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::com), REP_DEC<double>(REP<double>(-5.1,10.0), DEC::dac)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::dac), REP_DEC<double>(REP<double>(-5.1,10.1), DEC::dac)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(1.0, 5.0), DEC::def), REP_DEC<double>(REP<double>(-5.0,-0.9), DEC::com)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(1.0, 5.0), DEC::trv), REP_DEC<double>(REP<double>(-5.1,-1.0), DEC::com)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(1.0, 5.0), DEC::dac), REP_DEC<double>(REP<double>(-5.1,-0.9), DEC::com)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );

    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-10.0, -1.0), DEC::trv), F<double>::empty_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::def), F<double>::empty_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(1.0, 5.0), DEC::com), F<double>::empty_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );


    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_plus(F<double>::empty_dec(), F<double>::empty_dec() ) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_plus(F<double>::empty_dec(), REP_DEC<double>(REP<double>(1.0,10.0), DEC::dac) ) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_plus(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-5.0,10.0), DEC::def) ) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_plus(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-5.0,-1.0), DEC::com) ) ) );

    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-5.1,-0.0), DEC::com), REP_DEC<double>(REP<double>(0.0,5.0), DEC::com)), REP_DEC<double>(REP<double>(std::stod("-0X1.999999999998P-4"),0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-5.1,-1.0), DEC::com), REP_DEC<double>(REP<double>(1.0,5.0), DEC::dac)), REP_DEC<double>(REP<double>(std::stod("-0X1.999999999998P-4"),0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-5.0,-0.9), DEC::com), REP_DEC<double>(REP<double>(1.0,5.0), DEC::def)), REP_DEC<double>(REP<double>(0.0, std::stod("0X1.9999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-5.1,-0.9), DEC::dac), REP_DEC<double>(REP<double>(1.0,5.0), DEC::trv)), REP_DEC<double>(REP<double>(std::stod("-0X1.999999999998P-4"),std::stod("0X1.9999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-5.0,-1.0), DEC::dac), REP_DEC<double>(REP<double>(1.0,5.0), DEC::com)), REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-10.1, 5.0), DEC::dac), REP_DEC<double>(REP<double>(-5.0,10.0), DEC::dac)), REP_DEC<double>(REP<double>(std::stod("-0X1.999999999998P-4"),0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-10.0, 5.1), DEC::def), REP_DEC<double>(REP<double>(-5.0,10.0), DEC::def)), REP_DEC<double>(REP<double>(0.0,std::stod("0X1.999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-10.1, 5.1), DEC::def), REP_DEC<double>(REP<double>(-5.0,10.0), DEC::trv)), REP_DEC<double>(REP<double>(std::stod("-0X1.999999999998P-4"),std::stod("0X1.999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::def), REP_DEC<double>(REP<double>(-5.0,10.0), DEC::com)), REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(0.9, 5.0), DEC::trv), REP_DEC<double>(REP<double>(-5.0,-1.0), DEC::dac)), REP_DEC<double>(REP<double>(std::stod("-0X1.9999999999998P-4"),0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(1.0, 5.1), DEC::trv), REP_DEC<double>(REP<double>(-5.0,-1.0), DEC::def)), REP_DEC<double>(REP<double>(0.0,std::stod("0X1.999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(0.0, 5.1), DEC::trv), REP_DEC<double>(REP<double>(-5.0,-0.0), DEC::trv)), REP_DEC<double>(REP<double>(0.0,std::stod("0X1.999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(0.9, 5.1), DEC::com), REP_DEC<double>(REP<double>(-5.0,-1.0), DEC::com)), REP_DEC<double>(REP<double>(std::stod("-0X1.9999999999998P-4"),std::stod("0X1.999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(1.0, 5.0), DEC::dac), REP_DEC<double>(REP<double>(-5.0,-1.0), DEC::dac)), REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(0.0, 5.0), DEC::def), REP_DEC<double>(REP<double>(-5.0,-0.0), DEC::trv)), REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv) );

    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(std::stod("0X1.FFFFFFFFFFFFP+0"),std::stod("0X1.FFFFFFFFFFFFP+0")), DEC::com), REP_DEC<double>(REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("-0X1.999999999999AP-4")), DEC::com)), REP_DEC<double>(REP<double>(std::stod("0X1.E666666666656P+0"),std::stod("0X1.E666666666657P+0")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("0X1.FFFFFFFFFFFFP+0")), DEC::dac), REP_DEC<double>(REP<double>(std::stod("-0X1.999999999999AP-4"),0.01), DEC::com)), REP_DEC<double>(REP<double>(std::stod("-0X1.70A3D70A3D70BP-4"),std::stod("0X1.E666666666657P+0")), DEC::trv) );

    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(MAX_D,MAX_D), DEC::com), REP_DEC<double>(REP<double>(MAX_D,MAX_D), DEC::com)), REP_DEC<double>(REP<double>(MAX_D,INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::com), REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::com)), REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::dac), REP_DEC<double>(REP<double>(std::stod("-0X1.FFFFFFFFFFFFEP+1023"),MAX_D), DEC::com)), REP_DEC<double>(REP<double>(0.0,std::stod("0X1P+971")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::dac), REP_DEC<double>(REP<double>(-MAX_D,std::stod("0X1.FFFFFFFFFFFFEP+1023")), DEC::com)), REP_DEC<double>(REP<double>(std::stod("-0X1P+971"),0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(-MAX_D,std::stod("0X1.FFFFFFFFFFFFEP+1023")), DEC::com), REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::com)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(std::stod("-0X1.FFFFFFFFFFFFEP+1023"),MAX_D), DEC::com), REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::com)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );

    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFFP-53")), DEC::dac), REP_DEC<double>(REP<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFEP-53")), DEC::com)), REP_DEC<double>(REP<double>(std::stod("-0X1.FFFFFFFFFFFFFP-1"),std::stod("-0X1.FFFFFFFFFFFFEP-1")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<double>(REP<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFEP-53")), DEC::def), REP_DEC<double>(REP<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFFP-53")), DEC::com)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );



    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai( F<double>::cancel_plus(REP_DEC<double>(REP<double>(1.0,-MAX_D), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::cancel_plus(REP_DEC<double>(REP<double>(1.0,MAX_D), DEC::trv), REP_DEC<double>(REP<double>(3.0,-4.0), DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_cancel_plus_dec_mixedtype_test)
{
    BOOST_CHECK_EQUAL( F<float>::cancel_plus(REP_DEC<double>(REP<double>(-5.0,-0.9), DEC::com), REP_DEC<double>(REP<double>(1.0,5.0), DEC::com)), REP_DEC<float>(REP<float>(0.0f, std::stof("0X1.99999AP-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<float>::cancel_plus(REP_DEC<double>(REP<double>(-5.1,-0.9), DEC::dac), REP_DEC<double>(REP<double>(1.0,5.0), DEC::def)), REP_DEC<float>(REP<float>(std::stof("-0X1.99999AP-4"),std::stof("0X1.99999AP-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<float>(REP<float>(-10.1f, 5.1f), DEC::def), REP_DEC<float>(REP<float>(-5.0f,10.0f), DEC::trv)), REP_DEC<double>(REP<double>(std::stod("-0x1.999ap-4"),std::stod("0x1.99998p-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<float>(REP<float>(std::stof("-0X1.99999AP-4"),std::stof("0X1.FFFFFFP+0")), DEC::trv), REP_DEC<float>(REP<float>(std::stof("-0X1.99999AP-4"),0.01f), DEC::dac)), REP_DEC<double>(REP<double>(std::stod("-0x1.70a3d78p-4"),std::stod("0x1.e666666p+0")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_plus(REP_DEC<float>(REP<float>(std::stof("-0X1P+0"),std::stof("0X1.FFFFFCP-53")), DEC::com), REP_DEC<float>(REP<float>(std::stof("-0X1P+0"),std::stod("0X1.FFFFFEP-53")), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );


    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai( F<float>::cancel_plus(REP_DEC<double>(REP<double>(1.0,-MAX_D), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::cancel_plus(REP_DEC<double>(REP<double>(1.0,MAX_D), DEC::trv), REP_DEC<float>(REP<float>(3.0f,-4.0f), DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_cancel_minus_test)
{
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-INF_D, -1.0), F<double>::empty()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-1.0, INF_D), F<double>::empty()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::entire(), F<double>::empty()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-INF_D, -1.0), REP<double>(-1.0,5.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-1.0, INF_D), REP<double>(-1.0,5.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::entire(), REP<double>(-1.0,5.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-INF_D, -1.0), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-1.0, INF_D), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::empty(), REP<double>(-INF_D, -1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::empty(), REP<double>(-1.0, INF_D)),F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::empty(), F<double>::entire()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-1.0,5.0), REP<double>(-INF_D, -1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-1.0,5.0), REP<double>(-1.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-1.0,5.0), F<double>::entire() ), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::entire(), REP<double>(-INF_D, -1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::entire(), REP<double>(-1.0, INF_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::entire(), F<double>::entire()), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-5.0, -1.0), REP<double>(-5.1,-1.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-5.0, -1.0), REP<double>(-5.0,-0.9)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-5.0, -1.0), REP<double>(-5.1,-0.9)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-10.0, 5.0), REP<double>(-10.1, 5.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-10.0, 5.0), REP<double>(-10.0, 5.1)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-10.0, 5.0), REP<double>(-10.1, 5.1)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(1.0, 5.0), REP<double>(0.9, 5.0)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(1.0, 5.0), REP<double>(1.0, 5.1)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(1.0, 5.0), REP<double>(0.9, 5.1)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-10.0, -1.0), F<double>::empty()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-10.0, 5.0), F<double>::empty()), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(1.0, 5.0), F<double>::empty()), F<double>::entire() );


    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_minus(F<double>::empty(), F<double>::empty()) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_minus(F<double>::empty(), REP<double>(-10.0, -1.0)) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_minus(F<double>::empty(), REP<double>(-10.0, 5.0)) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_minus(F<double>::empty(), REP<double>(1.0, 5.0)) ) );

    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-5.1,-0.0), REP<double>(-5.0, 0.0)), REP<double>(std::stod("-0X1.999999999998P-4"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-5.1,-1.0), REP<double>(-5.0, -1.0)), REP<double>(std::stod("-0X1.999999999998P-4"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-5.0,-0.9), REP<double>(-5.0, -1.0)), REP<double>(0.0, std::stod("0X1.9999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-5.1,-0.9), REP<double>(-5.0, -1.0)), REP<double>(std::stod("-0X1.999999999998P-4"),std::stod("0X1.9999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-5.0,-1.0), REP<double>(-5.0, -1.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-10.1, 5.0), REP<double>(-10.0, 5.0)), REP<double>(std::stod("-0X1.999999999998P-4"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-10.0, 5.1), REP<double>(-10.0, 5.0)), REP<double>(0.0,std::stod("0X1.999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-10.1, 5.1), REP<double>(-10.0, 5.0)), REP<double>(std::stod("-0X1.999999999998P-4"),std::stod("0X1.999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-10.0, 5.0), REP<double>(-10.0, 5.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(0.9, 5.0), REP<double>(1.0, 5.0)), REP<double>(std::stod("-0X1.9999999999998P-4"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-0.0, 5.1), REP<double>(0.0, 5.0)), REP<double>(0.0,std::stod("0X1.999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(1.0, 5.1), REP<double>(1.0, 5.0)), REP<double>(0.0,std::stod("0X1.999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(0.9, 5.1), REP<double>(1.0, 5.0)), REP<double>(std::stod("-0X1.9999999999998P-4"),std::stod("0X1.999999999998P-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(1.0, 5.0), REP<double>(1.0, 5.0)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-5.0, 1.0), REP<double>(-1.0, 5.0)), REP<double>(-4.0,-4.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-5.0, 0.0), REP<double>(-0.0, 5.0)), REP<double>(-5.0,-5.0) );

    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(std::stod("0X1.FFFFFFFFFFFFP+0"),std::stod("0X1.FFFFFFFFFFFFP+0")), REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("0X1.E666666666656P+0"),std::stod("0X1.E666666666657P+0")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("0X1.FFFFFFFFFFFFP+0")), REP<double>(-0.01,std::stod("0X1.999999999999AP-4"))), REP<double>(std::stod("-0X1.70A3D70A3D70BP-4"),std::stod("0X1.E666666666657P+0")) );

    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(MAX_D,MAX_D), REP<double>(-MAX_D,-MAX_D)), REP<double>(MAX_D,INF_D) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-MAX_D,MAX_D), REP<double>(-MAX_D,MAX_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-MAX_D,MAX_D), REP<double>(-MAX_D,std::stod("0X1.FFFFFFFFFFFFEP+1023"))), REP<double>(0.0,std::stod("0X1P+971")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-MAX_D,MAX_D), REP<double>(std::stod("-0X1.FFFFFFFFFFFFEP+1023"),MAX_D)), REP<double>(-std::stod("0X1P+971"),0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(-MAX_D,std::stod("0X1.FFFFFFFFFFFFEP+1023")), REP<double>(-MAX_D,MAX_D)), F<double>::entire() );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(std::stod("-0X1.FFFFFFFFFFFFEP+1023"),MAX_D), REP<double>(-MAX_D,MAX_D)), F<double>::entire() );

    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(MIN_D,MIN_D), REP<double>(MIN_D,MIN_D)), REP<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(MIN_D,MIN_D), REP<double>(-MIN_D,-MIN_D)), REP<double>(std::stod("0X1P-1021"),std::stod("0X1P-1021")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000002P-1022")), REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000001P-1022"))), REP<double>(0.0,std::stod("0X0.0000000000001P-1022")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000001P-1022")), REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000002P-1022"))), F<double>::entire() );


    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFFP-53")), REP<double>(std::stod("-0X1.FFFFFFFFFFFFEP-53"),std::stod("0X1P+0"))), REP<double>(std::stod("-0X1.FFFFFFFFFFFFFP-1"),std::stod("-0X1.FFFFFFFFFFFFEP-1")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFEP-53")), REP<double>(std::stod("-0X1.FFFFFFFFFFFFFP-53"),std::stod("0X1P+0"))), F<double>::entire() );


    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_minus(REP<double>(1.0,-MAX_D), REP<double>(3.0,4.0)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::cancel_minus(REP<double>(1.0,MAX_D), REP<double>(3.0,-4.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_cancel_minus_mixedtype_test)
{
    BOOST_CHECK_EQUAL( F<float>::cancel_minus(REP<double>(-5.0,-0.9), REP<double>(-5.0,-1.0)), REP<float>(0.0f, std::stof("0X1.99999AP-4")) );
    BOOST_CHECK_EQUAL( F<float>::cancel_minus(REP<double>(-5.1,-0.9), REP<double>(-5.0,-1.0)), REP<float>(std::stof("-0X1.99999AP-4"),std::stof("0X1.99999AP-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<float>(-10.1f, 5.1f), REP<float>(-10.0f,5.0f)), REP<double>(std::stod("-0x1.999ap-4"),std::stod("0x1.99998p-4")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<float>(std::stof("-0X1.99999AP-4"),std::stof("0X1.FFFFFFP+0")), REP<float>(-0.01f,std::stof("0X1.99999AP-4"))), REP<double>(std::stod("-0x1.70a3d78p-4"),std::stod("0x1.e666666p+0")) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP<float>(std::stof("-0X1P+0"),std::stof("0X1.FFFFFCP-53")), REP<float>(std::stod("-0X1.FFFFFEP-53"),std::stof("0X1P+0"))), F<double>::entire() );


    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_empty( F<float>::cancel_minus(REP<double>(1.0,-MAX_D), REP<double>(3.0,4.0)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::cancel_minus(REP<double>(1.0,MAX_D), REP<float>(3.0f,-4.0f)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_cancel_minus_dec_test)
{
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-INF_D, -1.0), DEC::dac), F<double>::empty_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-1.0, INF_D), DEC::def), F<double>::empty_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::entire_dec(), F<double>::empty_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-INF_D, -1.0), DEC::trv), REP_DEC<double>(REP<double>(-1.0,5.0), DEC::dac)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-1.0, INF_D), DEC::dac), REP_DEC<double>(REP<double>(-1.0,5.0), DEC::com)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::entire_dec(), REP_DEC<double>(REP<double>(-1.0,5.0), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-INF_D, -1.0), DEC::def), F<double>::entire_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-1.0, INF_D), DEC::trv), F<double>::entire_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-INF_D, -1.0), DEC::dac)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-1.0, INF_D), DEC::dac)),REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::empty_dec(), F<double>::entire_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-1.0,5.0), DEC::dac), REP_DEC<double>(REP<double>(-INF_D, -1.0), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-1.0,5.0), DEC::def), REP_DEC<double>(REP<double>(-1.0, INF_D), DEC::trv)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-1.0,5.0), DEC::com), F<double>::entire_dec() ), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::entire_dec(), REP_DEC<double>(REP<double>(-INF_D, -1.0), DEC::dac)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::entire_dec(), REP_DEC<double>(REP<double>(-1.0, INF_D), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(F<double>::entire_dec(), F<double>::entire_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );

    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-5.0, -1.0), DEC::com), REP_DEC<double>(REP<double>(-5.1,-1.0), DEC::trv)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-5.0, -1.0), DEC::dac), REP_DEC<double>(REP<double>(-5.0,-0.9), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-5.0, -1.0), DEC::def), REP_DEC<double>(REP<double>(-5.1,-0.9), DEC::dac)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::trv), REP_DEC<double>(REP<double>(-10.1, 5.0), DEC::com)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::com), REP_DEC<double>(REP<double>(-10.0, 5.1), DEC::com)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::dac), REP_DEC<double>(REP<double>(-10.1, 5.1), DEC::trv)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(1.0, 5.0), DEC::def), REP_DEC<double>(REP<double>(0.9, 5.0), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(1.0, 5.0), DEC::trv), REP_DEC<double>(REP<double>(1.0, 5.1), DEC::dac)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(1.0, 5.0), DEC::com), REP_DEC<double>(REP<double>(0.9, 5.1), DEC::dac)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );

    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-10.0, -1.0), DEC::com), F<double>::empty_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::dac), F<double>::empty_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(1.0, 5.0), DEC::def), F<double>::empty_dec()), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );


    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_minus(F<double>::empty_dec(), F<double>::empty_dec()) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_minus(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-10.0, -1.0), DEC::com)) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_minus(F<double>::empty_dec(), REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::dac)) ) );
    BOOST_CHECK( F<double>::is_empty( F<double>::cancel_minus(F<double>::empty_dec(), REP_DEC<double>(REP<double>(1.0, 5.0), DEC::def)) ) );

    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-5.1,-0.0), DEC::com), REP_DEC<double>(REP<double>(-5.0, 0.0), DEC::com)), REP_DEC<double>(REP<double>(std::stod("-0X1.999999999998P-4"),0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-5.1,-1.0), DEC::dac), REP_DEC<double>(REP<double>(-5.0, -1.0), DEC::com)), REP_DEC<double>(REP<double>(std::stod("-0X1.999999999998P-4"),0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-5.0,-0.9), DEC::def), REP_DEC<double>(REP<double>(-5.0, -1.0), DEC::com)), REP_DEC<double>(REP<double>(0.0, std::stod("0X1.9999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-5.1,-0.9), DEC::trv), REP_DEC<double>(REP<double>(-5.0, -1.0), DEC::com)), REP_DEC<double>(REP<double>(std::stod("-0X1.999999999998P-4"),std::stod("0X1.9999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-5.0,-1.0), DEC::com), REP_DEC<double>(REP<double>(-5.0, -1.0), DEC::dac)), REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-10.1, 5.0), DEC::dac), REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::dac)), REP_DEC<double>(REP<double>(std::stod("-0X1.999999999998P-4"),0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-10.0, 5.1), DEC::def), REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::dac)), REP_DEC<double>(REP<double>(0.0,std::stod("0X1.999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-10.1, 5.1), DEC::trv), REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::def)), REP_DEC<double>(REP<double>(std::stod("-0X1.999999999998P-4"),std::stod("0X1.999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::com), REP_DEC<double>(REP<double>(-10.0, 5.0), DEC::def)), REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(0.9, 5.0), DEC::dac), REP_DEC<double>(REP<double>(1.0, 5.0), DEC::def)), REP_DEC<double>(REP<double>(std::stod("-0X1.9999999999998P-4"),0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-0.0, 5.1), DEC::def), REP_DEC<double>(REP<double>(0.0, 5.0), DEC::def)), REP_DEC<double>(REP<double>(0.0,std::stod("0X1.999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(1.0, 5.1), DEC::trv), REP_DEC<double>(REP<double>(1.0, 5.0), DEC::trv)), REP_DEC<double>(REP<double>(0.0,std::stod("0X1.999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(0.9, 5.1), DEC::com), REP_DEC<double>(REP<double>(1.0, 5.0), DEC::trv)), REP_DEC<double>(REP<double>(std::stod("-0X1.9999999999998P-4"),std::stod("0X1.999999999998P-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(1.0, 5.0), DEC::dac), REP_DEC<double>(REP<double>(1.0, 5.0), DEC::com)), REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-5.0, 1.0), DEC::def), REP_DEC<double>(REP<double>(-1.0, 5.0), DEC::def)), REP_DEC<double>(REP<double>(-4.0,-4.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-5.0, 0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0, 5.0), DEC::trv)), REP_DEC<double>(REP<double>(-5.0,-5.0), DEC::trv) );

    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(std::stod("0X1.FFFFFFFFFFFFP+0"),std::stod("0X1.FFFFFFFFFFFFP+0")), DEC::com), REP_DEC<double>(REP<double>(std::stod("0X1.999999999999AP-4"),std::stod("0X1.999999999999AP-4")), DEC::com)), REP_DEC<double>(REP<double>(std::stod("0X1.E666666666656P+0"),std::stod("0X1.E666666666657P+0")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(std::stod("-0X1.999999999999AP-4"),std::stod("0X1.FFFFFFFFFFFFP+0")), DEC::def), REP_DEC<double>(REP<double>(-0.01,std::stod("0X1.999999999999AP-4")), DEC::dac)), REP_DEC<double>(REP<double>(std::stod("-0X1.70A3D70A3D70BP-4"),std::stod("0X1.E666666666657P+0")), DEC::trv) );

    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(MAX_D,MAX_D), DEC::com), REP_DEC<double>(REP<double>(-MAX_D,-MAX_D), DEC::com)), REP_DEC<double>(REP<double>(MAX_D,INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::com), REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::com)), REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::com), REP_DEC<double>(REP<double>(-MAX_D,std::stod("0X1.FFFFFFFFFFFFEP+1023")), DEC::com)), REP_DEC<double>(REP<double>(0.0,std::stod("0X1P+971")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::com), REP_DEC<double>(REP<double>(std::stod("-0X1.FFFFFFFFFFFFEP+1023"),MAX_D), DEC::com)), REP_DEC<double>(REP<double>(-std::stod("0X1P+971"),0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(-MAX_D,std::stod("0X1.FFFFFFFFFFFFEP+1023")), DEC::com), REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::com)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(std::stod("-0X1.FFFFFFFFFFFFEP+1023"),MAX_D), DEC::com), REP_DEC<double>(REP<double>(-MAX_D,MAX_D), DEC::com)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );

    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(MIN_D,MIN_D), DEC::com), REP_DEC<double>(REP<double>(MIN_D,MIN_D), DEC::com)), REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(MIN_D,MIN_D), DEC::com), REP_DEC<double>(REP<double>(-MIN_D,-MIN_D), DEC::dac)), REP_DEC<double>(REP<double>(std::stod("0X1P-1021"),std::stod("0X1P-1021")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000002P-1022")), DEC::dac), REP_DEC<double>(REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000001P-1022")), DEC::dac)), REP_DEC<double>(REP<double>(0.0,std::stod("0X0.0000000000001P-1022")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000001P-1022")), DEC::def), REP_DEC<double>(REP<double>(std::stod("0X1P-1022"),std::stod("0X1.0000000000002P-1022")), DEC::com)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );


    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFFP-53")), DEC::com), REP_DEC<double>(REP<double>(std::stod("-0X1.FFFFFFFFFFFFEP-53"),std::stod("0X1P+0")), DEC::dac)), REP_DEC<double>(REP<double>(std::stod("-0X1.FFFFFFFFFFFFFP-1"),std::stod("-0X1.FFFFFFFFFFFFEP-1")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<double>(REP<double>(std::stod("-0X1P+0"),std::stod("0X1.FFFFFFFFFFFFEP-53")), DEC::def), REP_DEC<double>(REP<double>(std::stod("-0X1.FFFFFFFFFFFFFP-53"),std::stod("0X1P+0")), DEC::dac)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );



    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<double>::is_nai( F<double>::cancel_minus(REP_DEC<double>(REP<double>(1.0,-MAX_D), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::cancel_minus(REP_DEC<double>(REP<double>(1.0,MAX_D), DEC::trv), REP_DEC<double>(REP<double>(3.0,-4.0), DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_cancel_minus_dec_mixedtype_test)
{
    BOOST_CHECK_EQUAL( F<float>::cancel_minus(REP_DEC<double>(REP<double>(-5.0,-0.9), DEC::com), REP_DEC<double>(REP<double>(-5.0,-1.0), DEC::dac)), REP_DEC<float>(REP<float>(0.0f, std::stof("0X1.99999AP-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<float>::cancel_minus(REP_DEC<double>(REP<double>(-5.1,-0.9), DEC::dac), REP_DEC<double>(REP<double>(-5.0,-1.0), DEC::def)), REP_DEC<float>(REP<float>(std::stof("-0X1.99999AP-4"),std::stof("0X1.99999AP-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<float>(REP<float>(-10.1f, 5.1f), DEC::def), REP_DEC<float>(REP<float>(-10.0f,5.0f), DEC::dac)), REP_DEC<double>(REP<double>(std::stod("-0x1.999ap-4"),std::stod("0x1.99998p-4")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<float>(REP<float>(std::stof("-0X1.99999AP-4"),std::stof("0X1.FFFFFFP+0")), DEC::trv), REP_DEC<float>(REP<float>(-0.01f,std::stof("0X1.99999AP-4")), DEC::com)), REP_DEC<double>(REP<double>(std::stod("-0x1.70a3d78p-4"),std::stod("0x1.e666666p+0")), DEC::trv) );
    BOOST_CHECK_EQUAL( F<double>::cancel_minus(REP_DEC<float>(REP<float>(std::stof("-0X1P+0"),std::stof("0X1.FFFFFCP-53")), DEC::dac), REP_DEC<float>(REP<float>(std::stod("-0X1.FFFFFEP-53"),std::stof("0X1P+0")), DEC::def)), REP_DEC<double>(REP<double>(-INF_D, INF_D), DEC::trv) );



    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK( F<float>::is_nai( F<float>::cancel_minus(REP_DEC<double>(REP<double>(1.0,-MAX_D), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv)) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::cancel_minus(REP_DEC<double>(REP<double>(1.0,MAX_D), DEC::trv), REP_DEC<float>(REP<float>(3.0f,-4.0f), DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}
