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

#define BOOST_TEST_MODULE "Flavor: Validation functions [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include <limits>
#include "p1788/decoration/decoration.hpp"
#include "p1788/exception/exception.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"
#include "test/util/mpfr_bin_ieee754_flavor_io_test_util.hpp"

template<typename T>
using F = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>;

template<typename T>
using REP = typename F<T>::representation;

template<typename T>
using REP_DEC = typename F<T>::representation_dec;

typedef p1788::decoration::decoration DEC;

const double INF_D = std::numeric_limits<double>::infinity();
const float INF_F = std::numeric_limits<float>::infinity();
const double MAX_D = std::numeric_limits<double>::max();
const float MAX_F = std::numeric_limits<float>::max();
const double DNORM_MIN_D = std::numeric_limits<double>::denorm_min();
const float DNORM_MIN_F = std::numeric_limits<float>::denorm_min();

const double NAN_D = std::numeric_limits<double>::quiet_NaN();
const float NAN_F = std::numeric_limits<float>::quiet_NaN();


BOOST_AUTO_TEST_CASE(minimal_is_valid_test)
{
    p1788::exception::clear();

    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(F<double>::is_valid(REP<double>(NAN_D,NAN_D)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-INF_D,-MAX_D)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-INF_D,-1.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-INF_D,0.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-INF_D,1.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-INF_D,MAX_D)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-INF_D,INF_D)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-MAX_D,-1.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-MAX_D,0.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-MAX_D,1.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-MAX_D,MAX_D)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-MAX_D,INF_D)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-1.0,-1.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-1.0,0.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-1.0,1.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-1.0,MAX_D)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-1.0,INF_D)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(0.0,0.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-0.0,-0.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(0.0,-0.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(-0.0,0.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(0.0,1.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(0.0,MAX_D)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(0.0,INF_D)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(1.0,1.0)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(1.0,MAX_D)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(1.0,INF_D)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(MAX_D,MAX_D)));
    BOOST_CHECK(F<double>::is_valid(REP<double>(MAX_D,INF_D)));
    BOOST_CHECK(!p1788::exception::invalid_operand());


    BOOST_CHECK(!F<double>::is_valid(REP<double>(-INF_D,-INF_D)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(-1.0,-3.0)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(0.0,-3.0)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(1.0,-3.0)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(INF_D,INF_D)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(-NAN_D,-INF_D)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(NAN_D,-3.0)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(NAN_D,-3.0)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(NAN_D,-3.0)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(NAN_D,INF_D)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(-INF_D,NAN_D)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(-1.0,NAN_D)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(0.0,NAN_D)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(1.0,NAN_D)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP<double>(INF_D,NAN_D)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW(F<double>::is_valid(REP<double>(-INF_D,-INF_D)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_is_valid_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(NAN_D,NAN_D),DEC::ill)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(NAN_D,NAN_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,-MAX_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,-MAX_D),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,-MAX_D),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,-1.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,-1.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,-1.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,1.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,1.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,1.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,MAX_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,MAX_D),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,MAX_D),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,-1.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,-1.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,-1.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,-1.0),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,0.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,0.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,0.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,0.0),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,1.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,1.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,1.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,1.0),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,MAX_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,MAX_D),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,MAX_D),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,MAX_D),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,INF_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,INF_D),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,INF_D),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,-1.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,-1.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,-1.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,-1.0),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,0.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,0.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,0.0),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,1.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,1.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,1.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,1.0),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,MAX_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,MAX_D),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,MAX_D),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,MAX_D),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,INF_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,INF_D),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,0.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,0.0),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,-0.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,-0.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,-0.0),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,1.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,1.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,1.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,1.0),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,MAX_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,MAX_D),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,MAX_D),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,MAX_D),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,1.0),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,1.0),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,1.0),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,1.0),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,MAX_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,MAX_D),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,MAX_D),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,MAX_D),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(MAX_D,MAX_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(MAX_D,MAX_D),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(MAX_D,MAX_D),DEC::dac)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(MAX_D,MAX_D),DEC::com)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(MAX_D,INF_D),DEC::trv)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(MAX_D,INF_D),DEC::def)));
    BOOST_CHECK(F<double>::is_valid(REP_DEC<double>(REP<double>(MAX_D,INF_D),DEC::dac)));
    BOOST_CHECK(!p1788::exception::invalid_operand());


    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(NAN_D,NAN_D),DEC::def)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(NAN_D,NAN_D),DEC::dac)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(NAN_D,NAN_D),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,-MAX_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,-MAX_D),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,-1.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,-1.0),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,1.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,1.0),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,MAX_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,MAX_D),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,-1.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,0.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,1.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,MAX_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,INF_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-MAX_D,INF_D),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,-1.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,0.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,1.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,MAX_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,INF_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,INF_D),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,0.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,-0.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,1.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,MAX_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,INF_D),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,1.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,MAX_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(MAX_D,MAX_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(MAX_D,INF_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(MAX_D,INF_D),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,-INF_D),DEC::trv)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,-3.0),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,-3.0),DEC::def)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,-3.0),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(INF_D,INF_D),DEC::dac)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-NAN_D,-INF_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(NAN_D,-3.0),DEC::trv)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(NAN_D,-3.0),DEC::def)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(NAN_D,-3.0),DEC::dac)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(NAN_D,INF_D),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-INF_D,NAN_D),DEC::ill)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(-1.0,NAN_D),DEC::def)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(0.0,NAN_D),DEC::trv)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(1.0,NAN_D),DEC::dac)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    BOOST_CHECK(!p1788::exception::invalid_operand());
    BOOST_CHECK(!F<double>::is_valid(REP_DEC<double>(REP<double>(INF_D,NAN_D),DEC::com)));
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW(F<double>::is_valid(REP_DEC<double>(REP<double>(INF_D,NAN_D),DEC::com)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

