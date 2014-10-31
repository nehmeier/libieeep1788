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

#define BOOST_TEST_MODULE "Flavor: Boolean functions of intervals [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

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
const float INF_F = std::numeric_limits<float>::infinity();
const float NaN_F = std::numeric_limits<float>::quiet_NaN();

BOOST_AUTO_TEST_CASE(minimal_is_empty_test)
{
    BOOST_CHECK( F<double>::is_empty(REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-3.0,-2.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-INF_D,2.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-INF_D,0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-INF_D,-0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(0.0,INF_D)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-0.0,INF_D)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(0.0,-0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_empty(REP<double>(-0.0,-0.0)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_empty_dec_test)
{
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)) );
    BOOST_CHECK( F<double>::is_empty(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::def)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(1.0,2.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-1.0,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-3.0,-2.0), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-INF_D,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-INF_D,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-INF_D,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(0.0,INF_D), DEC::def)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-0.0,INF_D), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_empty(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_entire_test)
{
    BOOST_CHECK( !F<double>::is_entire(REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::is_entire(REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-3.0,-2.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-INF_D,2.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-INF_D,0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-INF_D,-0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(0.0,INF_D)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-0.0,INF_D)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(0.0,-0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(0.0,0.0)) );
    BOOST_CHECK( !F<double>::is_entire(REP<double>(-0.0,-0.0)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_entire_dec_test)
{
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)) );
    BOOST_CHECK( F<double>::is_entire(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv)) );
    BOOST_CHECK( F<double>::is_entire(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::def)) );
    BOOST_CHECK( F<double>::is_entire(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(1.0,2.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-1.0,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-3.0,-2.0), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-INF_D,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-INF_D,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-INF_D,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(0.0,INF_D), DEC::def)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-0.0,INF_D), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_entire(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_nai_dec_test)
{
    BOOST_CHECK( F<double>::is_nai(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::def)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(1.0,2.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-1.0,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-3.0,-2.0), DEC::dac)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF_D,2.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF_D,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-INF_D,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(0.0,INF_D), DEC::def)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-0.0,INF_D), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::com)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv)) );
    BOOST_CHECK( !F<double>::is_nai(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_equal_test)
{
    BOOST_CHECK( F<double>::is_equal(REP<double>(1.0,2.0), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_equal(REP<double>(1.0,2.1), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::is_equal(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::is_equal(REP<double>(NaN_D,NaN_D), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::is_equal(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::is_equal(REP<double>(1.0,2.4), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::is_equal(REP<double>(1.0,INF_D), REP<double>(1.0,INF_D)) );
    BOOST_CHECK( !F<double>::is_equal(REP<double>(1.0,2.4), REP<double>(1.0,INF_D)) );
    BOOST_CHECK( F<double>::is_equal(REP<double>(-INF_D,2.0), REP<double>(-INF_D,2.0)) );
    BOOST_CHECK( !F<double>::is_equal(REP<double>(-INF_D,2.4), REP<double>(-INF_D,2.0)) );
    BOOST_CHECK( F<double>::is_equal(REP<double>(-2.0,0.0), REP<double>(-2.0,0.0)) );
    BOOST_CHECK( F<double>::is_equal(REP<double>(-0.0,2.0), REP<double>(0.0,2.0)) );
    BOOST_CHECK( F<double>::is_equal(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::is_equal(REP<double>(-0.0,0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::is_equal(REP<double>(0.0,-0.0), REP<double>(0.0,0.0)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_equal_mixedtype_test)
{
    BOOST_CHECK( F<double>::is_equal(REP<float>(1.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::is_equal(REP<double>(1.0,2.1), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<double>::is_equal(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::is_equal(REP<double>(NaN_D,NaN_D), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<double>::is_equal(REP<float>(-INF_F,+INF_F), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::is_equal(REP<double>(1.0,2.4), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( F<double>::is_equal(REP<float>(1.0f,INF_F), REP<double>(1.0,INF_D)) );
    BOOST_CHECK( !F<double>::is_equal(REP<float>(1.0f,2.4f), REP<double>(1.0,INF_D)) );
    BOOST_CHECK( F<double>::is_equal(REP<double>(-INF_D,2.0), REP<float>(-INF_F,2.0f)) );
    BOOST_CHECK( !F<double>::is_equal(REP<float>(-INF_F,2.4f), REP<double>(-INF_D,2.0)) );
    BOOST_CHECK( F<double>::is_equal(REP<double>(-2.0,0.0), REP<float>(-2.0f,0.0f)) );
    BOOST_CHECK( F<double>::is_equal(REP<float>(-0.0f,2.0f), REP<double>(0.0,2.0)) );
    BOOST_CHECK( F<double>::is_equal(REP<double>(-0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::is_equal(REP<float>(-0.0f,0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::is_equal(REP<double>(0.0,-0.0), REP<float>(0.0f,0.0f)) );

    BOOST_CHECK( F<float>::is_equal(REP<float>(1.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<float>::is_equal(REP<double>(1.0,2.1), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<float>::is_equal(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<float>::is_equal(REP<double>(NaN_D,NaN_D), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<float>::is_equal(REP<float>(-INF_F,+INF_F), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::is_equal(REP<double>(1.0,2.4), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( F<float>::is_equal(REP<float>(1.0f,INF_F), REP<double>(1.0,INF_D)) );
    BOOST_CHECK( !F<float>::is_equal(REP<float>(1.0f,2.4f), REP<double>(1.0,INF_D)) );
    BOOST_CHECK( F<float>::is_equal(REP<double>(-INF_D,2.0), REP<float>(-INF_F,2.0f)) );
    BOOST_CHECK( !F<float>::is_equal(REP<float>(-INF_F,2.4f), REP<double>(-INF_D,2.0)) );
    BOOST_CHECK( F<float>::is_equal(REP<double>(-2.0,0.0), REP<float>(-2.0f,0.0f)) );
    BOOST_CHECK( F<float>::is_equal(REP<float>(-0.0f,2.0f), REP<double>(0.0,2.0)) );
    BOOST_CHECK( F<float>::is_equal(REP<double>(-0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<float>::is_equal(REP<float>(-0.0f,0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::is_equal(REP<double>(0.0,-0.0), REP<float>(0.0f,0.0f)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_equal_dec_test)
{
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(1.0,2.0),DEC::def), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<double>(REP<double>(1.0,2.1),DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::def), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<double>(REP<double>(1.0,2.4),DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<double>(REP<double>(1.0,2.4),DEC::def), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv), REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<double>(REP<double>(-INF_D,2.4),DEC::def), REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(-2.0,0.0),DEC::trv), REP_DEC<double>(REP<double>(-2.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(-0.0,2.0),DEC::def), REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(-0.0,0.0),DEC::def), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_equal_dec_mixedtype_test)
{
    BOOST_CHECK( F<double>::is_equal(REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::com), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<double>(REP<double>(1.0,2.1),DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::def)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<double>(REP<double>(1.0,2.4),DEC::def), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<float>(REP<float>(1.0f,INF_F),DEC::trv), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<float>(REP<float>(1.0f,2.4f),DEC::trv), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv), REP_DEC<float>(REP<float>(-INF_F,2.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_equal(REP_DEC<float>(REP<float>(-INF_F,2.4f),DEC::trv), REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(-2.0,0.0),DEC::trv), REP_DEC<float>(REP<float>(-2.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<float>(REP<float>(-0.0f,2.0f),DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::def), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<float>(REP<float>(-0.0f,0.0f),DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::dac)) );
    BOOST_CHECK( F<double>::is_equal(REP_DEC<double>(REP<double>(0.0,-0.0),DEC::com), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::def)) );

    BOOST_CHECK( F<float>::is_equal(REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::com), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::is_equal(REP_DEC<double>(REP<double>(1.0,2.1),DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::is_equal(REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::is_equal(REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::is_equal(REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::is_equal(REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::is_equal(REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::is_equal(REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::def)) );
    BOOST_CHECK( !F<float>::is_equal(REP_DEC<double>(REP<double>(1.0,2.4),DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( F<float>::is_equal(REP_DEC<float>(REP<float>(1.0f,INF_F),DEC::dac), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::is_equal(REP_DEC<float>(REP<float>(1.0f,2.4f),DEC::trv), REP_DEC<double>(REP<double>(1.0,INF_D),DEC::trv)) );
    BOOST_CHECK( F<float>::is_equal(REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv), REP_DEC<float>(REP<float>(-INF_F,2.0f),DEC::trv)) );
    BOOST_CHECK( !F<float>::is_equal(REP_DEC<float>(REP<float>(-INF_F,2.4f),DEC::def), REP_DEC<double>(REP<double>(-INF_D,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::is_equal(REP_DEC<double>(REP<double>(-2.0,0.0),DEC::trv), REP_DEC<float>(REP<float>(-2.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::is_equal(REP_DEC<float>(REP<float>(-0.0f,2.0f),DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::is_equal(REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::is_equal(REP_DEC<float>(REP<float>(-0.0f,0.0f),DEC::com), REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)) );
    BOOST_CHECK( F<float>::is_equal(REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
}


BOOST_AUTO_TEST_CASE(minimal_subset_test)
{
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(-0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(-0.1,1.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(-0.1,0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(-0.1,-0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( !F<double>::subset(REP<double>(0.0,4.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::subset(REP<double>(-0.0,4.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::subset(REP<double>(-0.1,1.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::subset(REP<double>(-INF_D,+INF_D), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<double>::subset(REP<double>(0.0,4.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,4.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.1,1.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<double>(-0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.1,0.2), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.1,0.2), REP<double>(-0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.1,-0.1), REP<double>(-4.0, 3.4)) );

    BOOST_CHECK( F<double>::subset(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,0.0), REP<double>(0.0,-0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.0,-0.0), REP<double>(-0.0,0.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_subset_mixedtype_test)
{
    BOOST_CHECK( F<double>::subset(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( F<double>::subset(REP<float>(NaN_F,NaN_F), REP<double>(-0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<float>(-0.1f,1.0f)) );
    BOOST_CHECK( F<double>::subset(REP<float>(NaN_F,NaN_F), REP<double>(-0.1,0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(NaN_D,NaN_D), REP<float>(-0.1f,-0.0f)) );
    BOOST_CHECK( F<double>::subset(REP<float>(NaN_F,NaN_F), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( !F<double>::subset(REP<double>(0.0,4.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<double>::subset(REP<float>(-0.0f,4.0f), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::subset(REP<double>(-0.1,1.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<double>::subset(REP<float>(-INF_F,+INF_F), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<double>::subset(REP<float>(0.0f,4.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,4.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( F<double>::subset(REP<float>(-0.1f,1.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );

    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<double>::subset(REP<float>(1.0f,2.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(1.0,2.0), REP<float>(-0.0f,4.0f)) );
    BOOST_CHECK( F<double>::subset(REP<float>(0.1f,0.2f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.1,0.2), REP<float>(-0.0f,4.0f)) );
    BOOST_CHECK( F<double>::subset(REP<float>(-0.1f,-0.1f), REP<double>(-4.0, 3.4)) );

    BOOST_CHECK( F<double>::subset(REP<double>(0.0,0.0), REP<float>(-0.0f,-0.0f)) );
    BOOST_CHECK( F<double>::subset(REP<float>(-0.0f,-0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(-0.0,0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::subset(REP<float>(-0.0f,0.0f), REP<double>(0.0,-0.0)) );
    BOOST_CHECK( F<double>::subset(REP<double>(0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::subset(REP<float>(0.0f,-0.0f), REP<double>(-0.0,0.0)) );


    BOOST_CHECK( F<float>::subset(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<float>::subset(REP<double>(NaN_D,NaN_D), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( F<float>::subset(REP<float>(NaN_F,NaN_F), REP<double>(-0.0,4.0)) );
    BOOST_CHECK( F<float>::subset(REP<double>(NaN_D,NaN_D), REP<float>(-0.1f,1.0f)) );
    BOOST_CHECK( F<float>::subset(REP<float>(NaN_F,NaN_F), REP<double>(-0.1,0.0)) );
    BOOST_CHECK( F<float>::subset(REP<double>(NaN_D,NaN_D), REP<float>(-0.1f,-0.0f)) );
    BOOST_CHECK( F<float>::subset(REP<float>(NaN_F,NaN_F), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( !F<float>::subset(REP<double>(0.0,4.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<float>::subset(REP<float>(-0.0f,4.0f), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<float>::subset(REP<double>(-0.1,1.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<float>::subset(REP<float>(-INF_F,+INF_F), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<float>::subset(REP<float>(0.0f,4.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<float>::subset(REP<double>(-0.0,4.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( F<float>::subset(REP<float>(-0.1f,1.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<float>::subset(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );

    BOOST_CHECK( F<float>::subset(REP<double>(1.0,2.0), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<float>::subset(REP<float>(1.0f,2.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<float>::subset(REP<double>(1.0,2.0), REP<float>(-0.0f,4.0f)) );
    BOOST_CHECK( F<float>::subset(REP<float>(0.1f,0.2f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<float>::subset(REP<double>(0.1,0.2), REP<float>(-0.0f,4.0f)) );
    BOOST_CHECK( F<float>::subset(REP<float>(-0.1f,-0.1f), REP<double>(-4.0, 3.4)) );

    BOOST_CHECK( F<float>::subset(REP<double>(0.0,0.0), REP<float>(-0.0f,-0.0f)) );
    BOOST_CHECK( F<float>::subset(REP<float>(-0.0f,-0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::subset(REP<double>(-0.0,0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<float>::subset(REP<float>(-0.0f,0.0f), REP<double>(0.0,-0.0)) );
    BOOST_CHECK( F<float>::subset(REP<double>(0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<float>::subset(REP<float>(0.0f,-0.0f), REP<double>(-0.0,0.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_subset_dec_test)
{
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(-0.0,4.0),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(-0.1,1.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(-0.1,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(-0.1,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(-0.0,4.0), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(-0.1,1.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.1,1.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<double>(REP<double>(-0.0,4.0),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.1,0.2), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.1,0.2), DEC::trv), REP_DEC<double>(REP<double>(-0.0,4.0),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.1,-0.1), DEC::trv), REP_DEC<double>(REP<double>(-4.0, 3.4),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::def), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );
}


BOOST_AUTO_TEST_CASE(minimal_subset_dec_mixedtype_test)
{
    BOOST_CHECK( !F<double>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(-0.0,4.0),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(-0.1f,1.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(-0.1,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(-0.1f,-0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<float>(REP<float>(-0.0f,4.0f), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<double>(REP<double>(-0.1,1.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::subset(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<float>(REP<float>(-0.1f,1.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<float>(REP<float>(-0.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<float>(REP<float>(0.1f,0.2f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.1,0.2), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<float>(REP<float>(-0.1f,-0.1f), DEC::trv), REP_DEC<double>(REP<double>(-4.0, 3.4),DEC::trv)) );

    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,-0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::def), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::def)) );
    BOOST_CHECK( F<double>::subset(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );

    BOOST_CHECK( !F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );

    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(-0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(-0.1f,1.0f),DEC::def)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(-0.1,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(-0.1f,-0.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( !F<float>::subset(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<float>::subset(REP_DEC<float>(REP<float>(-0.0f,4.0f), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::subset(REP_DEC<double>(REP<double>(-0.1,1.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<float>::subset(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<double>(REP<double>(-0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(-0.1f,1.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );

    BOOST_CHECK( F<float>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<float>(REP<float>(-0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(0.1f,0.2f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<double>(REP<double>(0.1,0.2), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(-0.1f,-0.1f), DEC::trv), REP_DEC<double>(REP<double>(-4.0, 3.4),DEC::trv)) );

    BOOST_CHECK( F<float>::subset(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,-0.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,-0.0),DEC::def)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::subset(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );
}


BOOST_AUTO_TEST_CASE(minimal_less_test)
{
    BOOST_CHECK( F<double>::less(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(1.0,2.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(NaN_D,NaN_D), REP<double>(1.0,2.0)) );

    BOOST_CHECK( F<double>::less(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(1.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(0.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-0.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-INF_D,+INF_D), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-INF_D,+INF_D), REP<double>(0.0,2.0)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-INF_D,+INF_D), REP<double>(-0.0,2.0)) );

    BOOST_CHECK( F<double>::less(REP<double>(0.0,2.0), REP<double>(0.0,2.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,2.0), REP<double>(-0.0,2.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,2.0), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,2.0), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,2.0), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,2.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,3.5), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,4.0), REP<double>(3.0,4.0)) );

    BOOST_CHECK( F<double>::less(REP<double>(-2.0,-1.0), REP<double>(-2.0,-1.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-3.0,-1.5), REP<double>(-2.0,-1.0)) );

    BOOST_CHECK( F<double>::less(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,0.0), REP<double>(0.0,-0.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,-0.0), REP<double>(-0.0,0.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_less_mixedtype_test)
{
    BOOST_CHECK( F<double>::less(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(1.0,2.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<double>::less(REP<float>(NaN_F,NaN_F), REP<double>(1.0,2.0)) );

    BOOST_CHECK( F<double>::less(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::less(REP<float>(1.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(0.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::less(REP<float>(-0.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-INF_D,+INF_D), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( !F<double>::less(REP<float>(-INF_F,+INF_F), REP<double>(0.0,2.0)) );
    BOOST_CHECK( !F<double>::less(REP<double>(-INF_D,+INF_D), REP<float>(-0.0f,2.0f)) );

    BOOST_CHECK( F<double>::less(REP<float>(0.0f,2.0f), REP<double>(0.0,2.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,2.0), REP<float>(-0.0f,2.0f)) );
    BOOST_CHECK( F<double>::less(REP<float>(0.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,2.0), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<double>::less(REP<float>(1.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,2.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<double>::less(REP<float>(1.0f,3.5f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(1.0,4.0), REP<float>(3.0f,4.0f)) );

    BOOST_CHECK( F<double>::less(REP<float>(-2.0f,-1.0f), REP<double>(-2.0,-1.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-3.0,-1.5), REP<float>(-2.0f,-1.0f)) );

    BOOST_CHECK( F<double>::less(REP<float>(0.0f,0.0f), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::less(REP<float>(-0.0f,0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(-0.0,0.0), REP<float>(0.0f,-0.0f)) );
    BOOST_CHECK( F<double>::less(REP<float>(0.0f,-0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::less(REP<double>(0.0,-0.0), REP<float>(-0.0f,0.0f)) );


    BOOST_CHECK( F<float>::less(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<float>::less(REP<double>(1.0,2.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<float>::less(REP<float>(NaN_F,NaN_F), REP<double>(1.0,2.0)) );

    BOOST_CHECK( F<float>::less(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<float>::less(REP<float>(1.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::less(REP<double>(0.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<float>::less(REP<float>(-0.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::less(REP<double>(-INF_D,+INF_D), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( !F<float>::less(REP<float>(-INF_F,+INF_F), REP<double>(0.0,2.0)) );
    BOOST_CHECK( !F<float>::less(REP<double>(-INF_D,+INF_D), REP<float>(-0.0f,2.0f)) );

    BOOST_CHECK( F<float>::less(REP<float>(0.0f,2.0f), REP<double>(0.0,2.0)) );
    BOOST_CHECK( F<float>::less(REP<double>(0.0,2.0), REP<float>(-0.0f,2.0f)) );
    BOOST_CHECK( F<float>::less(REP<float>(0.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<float>::less(REP<double>(-0.0,2.0), REP<float>(1.0f,2.0f)) );
    BOOST_CHECK( F<float>::less(REP<float>(1.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<float>::less(REP<double>(1.0,2.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<float>::less(REP<float>(1.0f,3.5f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<float>::less(REP<double>(1.0,4.0), REP<float>(3.0f,4.0f)) );

    BOOST_CHECK( F<float>::less(REP<float>(-2.0f,-1.0f), REP<double>(-2.0,-1.0)) );
    BOOST_CHECK( F<float>::less(REP<double>(-3.0,-1.5), REP<float>(-2.0f,-1.0f)) );

    BOOST_CHECK( F<float>::less(REP<float>(0.0f,0.0f), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( F<float>::less(REP<double>(-0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<float>::less(REP<float>(-0.0f,0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::less(REP<double>(-0.0,0.0), REP<float>(0.0f,-0.0f)) );
    BOOST_CHECK( F<float>::less(REP<float>(0.0f,-0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::less(REP<double>(0.0,-0.0), REP<float>(-0.0f,0.0f)) );
}

BOOST_AUTO_TEST_CASE(minimal_less_dec_test)
{
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::def)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-0.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::def), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,3.5), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-2.0,-1.0), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-3.0,-1.5), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::def), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );
}


BOOST_AUTO_TEST_CASE(minimal_less_dec_mixedtype_test)
{
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::def)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::def), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<float>(REP<float>(-0.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::def)) );
    BOOST_CHECK( !F<double>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,2.0f),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<float>(REP<float>(0.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<float>(REP<float>(0.0f,2.0f), DEC::def), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<double>::less(REP_DEC<float>(REP<float>(1.0f,3.5f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<float>(REP<float>(-2.0f,-1.0f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-3.0,-1.5), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,-1.0f),DEC::trv)) );

    BOOST_CHECK( F<double>::less(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::def), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,-0.0f),DEC::def)) );
    BOOST_CHECK( F<double>::less(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::less(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,0.0f),DEC::trv)) );


    BOOST_CHECK( !F<float>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<float>::less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<float>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::def), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(-0.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::def)) );
    BOOST_CHECK( !F<float>::less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,2.0f),DEC::trv)) );

    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(0.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<double>(REP<double>(0.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,2.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(0.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<double>(REP<double>(-0.0,2.0), DEC::def), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::def)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(1.0f,3.5f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( F<float>::less(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );

    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(-2.0f,-1.0f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<double>(REP<double>(-3.0,-1.5), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,-1.0f),DEC::trv)) );

    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)) );
    BOOST_CHECK( F<float>::less(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,-0.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::def), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::less(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,0.0f),DEC::trv)) );
}


BOOST_AUTO_TEST_CASE(minimal_precedes_test)
{
    BOOST_CHECK( F<double>::precedes(REP<double>(NaN_D,NaN_D), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(3.0,4.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );


    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(0.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-0.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-INF_D,+INF_D), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( F<double>::precedes(REP<double>(1.0,2.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(1.0,3.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-3.0, -1.0), REP<double>(-1.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-3.0, -1.0), REP<double>(-1.0,-0.0)) );

    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,3.5), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,4.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-3.0, -0.1), REP<double>(-1.0,0.0)) );

    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-0.0,0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-0.0,0.0), REP<double>(0.0,-0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,-0.0), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,-0.0), REP<double>(-0.0,0.0)) );
}

BOOST_AUTO_TEST_CASE(minimal_precedes_mixedtype_test)
{
    BOOST_CHECK( F<double>::precedes(REP<float>(NaN_F,NaN_F), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(3.0,4.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( F<double>::precedes(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::precedes(REP<float>(0.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-0.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::precedes(REP<float>(-INF_F,+INF_F), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );

    BOOST_CHECK( F<double>::precedes(REP<float>(1.0f,2.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(1.0,3.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<double>::precedes(REP<float>(-3.0f, -1.0f), REP<double>(-1.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-3.0, -1.0), REP<float>(-1.0f,-0.0f)) );

    BOOST_CHECK( !F<double>::precedes(REP<float>(1.0f,3.5f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::precedes(REP<double>(1.0,4.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<double>::precedes(REP<float>(-3.0f, -0.1f), REP<double>(-1.0,0.0)) );

    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,0.0), REP<float>(-0.0f,-0.0f)) );
    BOOST_CHECK( F<double>::precedes(REP<float>(-0.0f,-0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(-0.0,0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::precedes(REP<float>(-0.0f,0.0f), REP<double>(0.0,-0.0)) );
    BOOST_CHECK( F<double>::precedes(REP<double>(0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<double>::precedes(REP<float>(0.0f,-0.0f), REP<double>(-0.0,0.0)) );

    BOOST_CHECK( F<float>::precedes(REP<float>(NaN_F,NaN_F), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<float>::precedes(REP<double>(3.0,4.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( !F<float>::precedes(REP<double>(1.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<float>::precedes(REP<float>(0.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::precedes(REP<double>(-0.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<float>::precedes(REP<float>(-INF_F,+INF_F), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<float>::precedes(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );

    BOOST_CHECK( F<float>::precedes(REP<float>(1.0f,2.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<float>::precedes(REP<double>(1.0,3.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(-3.0f, -1.0f), REP<double>(-1.0,0.0)) );
    BOOST_CHECK( F<float>::precedes(REP<double>(-3.0, -1.0), REP<float>(-1.0f,-0.0f)) );

    BOOST_CHECK( !F<float>::precedes(REP<float>(1.0f,3.5f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<float>::precedes(REP<double>(1.0,4.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<float>::precedes(REP<float>(-3.0f, -0.1f), REP<double>(-1.0,0.0)) );

    BOOST_CHECK( F<float>::precedes(REP<double>(0.0,0.0), REP<float>(-0.0f,-0.0f)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(-0.0f,-0.0f), REP<double>(0.0,0.0)) );
    BOOST_CHECK( F<float>::precedes(REP<double>(-0.0,0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(-0.0f,0.0f), REP<double>(0.0,-0.0)) );
    BOOST_CHECK( F<float>::precedes(REP<double>(0.0,-0.0), REP<float>(0.0f,0.0f)) );
    BOOST_CHECK( F<float>::precedes(REP<float>(0.0f,-0.0f), REP<double>(-0.0,0.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_precedes_dec_test)
{
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );


    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-3.0, -1.0), DEC::def), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-3.0, -1.0), DEC::trv), REP_DEC<double>(REP<double>(-1.0,-0.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(1.0,3.5), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-3.0, -0.1), DEC::trv), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)) );

    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::def), REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );
}

BOOST_AUTO_TEST_CASE(minimal_precedes_dec_mixedtype_test)
{
    BOOST_CHECK( !F<double>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<double>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<float>(REP<float>(0.0f,2.0f), DEC::def), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );

    BOOST_CHECK( F<double>::precedes(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<float>(REP<float>(-3.0f, -1.0f), DEC::trv), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::def)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-3.0, -1.0), DEC::trv), REP_DEC<float>(REP<float>(-1.0f,-0.0f),DEC::trv)) );

    BOOST_CHECK( !F<double>::precedes(REP_DEC<float>(REP<float>(1.0f,3.5f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<double>(REP<double>(1.0,4.0), DEC::def), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::precedes(REP_DEC<float>(REP<float>(-3.0f, -0.1f), DEC::trv), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)) );

    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,-0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::def), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::def)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::precedes(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );

    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( !F<float>::precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(0.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<double>(REP<double>(-0.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );

    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<double>(REP<double>(1.0,3.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(-3.0f, -1.0f), DEC::def), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<double>(REP<double>(-3.0, -1.0), DEC::def), REP_DEC<float>(REP<float>(-1.0f,-0.0f),DEC::def)) );

    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(1.0f,3.5f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<float>::precedes(REP_DEC<float>(REP<float>(-3.0f, -0.1f), DEC::trv), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)) );

    BOOST_CHECK( F<float>::precedes(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,-0.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::def), REP_DEC<double>(REP<double>(0.0,0.0),DEC::def)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<double>(REP<double>(-0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::def)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(-0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::precedes(REP_DEC<float>(REP<float>(0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );
}


BOOST_AUTO_TEST_CASE(minimal_is_interior_test)
{
    BOOST_CHECK( F<double>::is_interior(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::is_interior(REP<double>(NaN_D,NaN_D), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::is_interior(REP<double>(0.0,4.0), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<double>::is_interior(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::is_interior(REP<double>(0.0,4.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::is_interior(REP<double>(NaN_D,NaN_D), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::is_interior(REP<double>(-INF_D,+INF_D), REP<double>(0.0,4.0)) );

    BOOST_CHECK( !F<double>::is_interior(REP<double>(0.0,4.0), REP<double>(0.0,4.0)) );
    BOOST_CHECK( F<double>::is_interior(REP<double>(1.0,2.0), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::is_interior(REP<double>(-2.0,2.0), REP<double>(-2.0,4.0)) );
    BOOST_CHECK( F<double>::is_interior(REP<double>(-0.0,-0.0), REP<double>(-2.0,4.0)) );
    BOOST_CHECK( F<double>::is_interior(REP<double>(0.0,0.0), REP<double>(-2.0,4.0)) );
    BOOST_CHECK( !F<double>::is_interior(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );

    BOOST_CHECK( !F<double>::is_interior(REP<double>(0.0,4.4), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::is_interior(REP<double>(-1.0,-1.0), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::is_interior(REP<double>(2.0,2.0), REP<double>(-2.0,-1.0)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_interior_mixedtype_test)
{
    BOOST_CHECK( F<double>::is_interior(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::is_interior(REP<double>(NaN_D,NaN_D), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( !F<double>::is_interior(REP<float>(0.0f,4.0f), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<double>::is_interior(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( F<double>::is_interior(REP<float>(0.0f,4.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<double>::is_interior(REP<double>(NaN_D,NaN_D), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::is_interior(REP<float>(-INF_F,+INF_F), REP<double>(0.0,4.0)) );

    BOOST_CHECK( !F<double>::is_interior(REP<double>(0.0,4.0), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( F<double>::is_interior(REP<float>(1.0f,2.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::is_interior(REP<double>(-2.0,2.0), REP<float>(-2.0f,4.0f)) );
    BOOST_CHECK( F<double>::is_interior(REP<float>(-0.0f,-0.0f), REP<double>(-2.0,4.0)) );
    BOOST_CHECK( F<double>::is_interior(REP<double>(0.0,0.0), REP<float>(-2.0f,4.0f)) );
    BOOST_CHECK( !F<double>::is_interior(REP<float>(0.0f,0.0f), REP<double>(-0.0,-0.0)) );

    BOOST_CHECK( !F<double>::is_interior(REP<double>(0.0,4.4), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( !F<double>::is_interior(REP<float>(-1.0f,-1.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::is_interior(REP<double>(2.0,2.0), REP<float>(-2.0f,-1.0f)) );

    BOOST_CHECK( F<float>::is_interior(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<float>::is_interior(REP<double>(NaN_D,NaN_D), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( !F<float>::is_interior(REP<float>(0.0f,4.0f), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<float>::is_interior(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( F<float>::is_interior(REP<float>(0.0f,4.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( F<float>::is_interior(REP<double>(NaN_D,NaN_D), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<float>::is_interior(REP<float>(-INF_F,+INF_F), REP<double>(0.0,4.0)) );

    BOOST_CHECK( !F<float>::is_interior(REP<double>(0.0,4.0), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( F<float>::is_interior(REP<float>(1.0f,2.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<float>::is_interior(REP<double>(-2.0,2.0), REP<float>(-2.0f,4.0f)) );
    BOOST_CHECK( F<float>::is_interior(REP<float>(-0.0f,-0.0f), REP<double>(-2.0,4.0)) );
    BOOST_CHECK( F<float>::is_interior(REP<double>(0.0,0.0), REP<float>(-2.0f,4.0f)) );
    BOOST_CHECK( !F<float>::is_interior(REP<float>(0.0f,0.0f), REP<double>(-0.0,-0.0)) );

    BOOST_CHECK( !F<float>::is_interior(REP<double>(0.0,4.4), REP<float>(0.0f,4.0f)) );
    BOOST_CHECK( !F<float>::is_interior(REP<float>(-1.0f,-1.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<float>::is_interior(REP<double>(2.0,2.0), REP<float>(-2.0f,-1.0f)) );
}


BOOST_AUTO_TEST_CASE(minimal_is_interior_dec_test)
{
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<double>::is_interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<double>::is_interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<double>::is_interior(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::is_interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::is_interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::is_interior(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(-2.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-2.0,4.0),DEC::def)) );
    BOOST_CHECK( F<double>::is_interior(REP_DEC<double>(REP<double>(-0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(-2.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::is_interior(REP_DEC<double>(REP<double>(0.0,0.0), DEC::def), REP_DEC<double>(REP<double>(-2.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(0.0,4.4), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(-1.0,-1.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(2.0,2.0), DEC::def), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );
}

BOOST_AUTO_TEST_CASE(minimal_is_interior_dec_mixedtype_test)
{
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<double>::is_interior(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<double>::is_interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<double>::is_interior(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( F<double>::is_interior(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<double>::is_interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::is_interior(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::def), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(-2.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<double>::is_interior(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::is_interior(REP_DEC<double>(REP<double>(0.0,0.0), DEC::def), REP_DEC<float>(REP<float>(-2.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(0.0,4.4), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<float>(REP<float>(-1.0f,-1.0f), DEC::def), REP_DEC<double>(REP<double>(0.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::is_interior(REP_DEC<double>(REP<double>(2.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,-1.0f),DEC::trv)) );

    BOOST_CHECK( !F<float>::is_interior(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::is_interior(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::is_interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<float>::is_interior(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<float>::is_interior(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<float>::is_interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<float>::is_interior(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::def)) );

    BOOST_CHECK( F<float>::is_interior(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( F<float>::is_interior(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( F<float>::is_interior(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<float>::is_interior(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );

    BOOST_CHECK( !F<float>::is_interior(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::is_interior(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::def), REP_DEC<double>(REP<double>(0.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<float>::is_interior(REP_DEC<double>(REP<double>(-2.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<float>::is_interior(REP_DEC<float>(REP<float>(-0.0f,-0.0f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<float>::is_interior(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<float>::is_interior(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );

    BOOST_CHECK( !F<float>::is_interior(REP_DEC<double>(REP<double>(0.0,4.4), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<float>::is_interior(REP_DEC<float>(REP<float>(-1.0f,-1.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::is_interior(REP_DEC<double>(REP<double>(2.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,-1.0f),DEC::trv)) );
}


BOOST_AUTO_TEST_CASE(minimal_strictly_less_test)
{
    BOOST_CHECK( F<double>::strictly_less(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<double>(1.0,2.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<double>(NaN_D,NaN_D), REP<double>(1.0,2.0)) );

    BOOST_CHECK( F<double>::strictly_less(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<double>(1.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<double>(-INF_D,+INF_D), REP<double>(1.0,2.0)) );

    BOOST_CHECK( !F<double>::strictly_less(REP<double>(1.0,2.0), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::strictly_less(REP<double>(1.0,2.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::strictly_less(REP<double>(1.0,3.5), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<double>(1.0,4.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<double>(0.0,4.0), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<double>(-0.0,4.0), REP<double>(0.0,4.0)) );

    BOOST_CHECK( !F<double>::strictly_less(REP<double>(-2.0,-1.0), REP<double>(-2.0,-1.0)) );
    BOOST_CHECK( F<double>::strictly_less(REP<double>(-3.0,-1.5), REP<double>(-2.0,-1.0)) );
}

BOOST_AUTO_TEST_CASE(minimal_strictly_less_mixedtype_test)
{
    BOOST_CHECK( F<double>::strictly_less(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<double>(1.0,2.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<float>(NaN_F,NaN_F), REP<double>(1.0,2.0)) );

    BOOST_CHECK( F<double>::strictly_less(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<float>(1.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<double>(-INF_D,+INF_D), REP<float>(1.0f,2.0f)) );

    BOOST_CHECK( !F<double>::strictly_less(REP<float>(1.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<double>::strictly_less(REP<double>(1.0,2.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<double>::strictly_less(REP<float>(1.0f,3.5f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<double>(1.0,4.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<float>(0.0f,4.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_less(REP<double>(-0.0,4.0), REP<float>(0.0f,4.0f)) );

    BOOST_CHECK( !F<double>::strictly_less(REP<float>(-2.0f,-1.0f), REP<double>(-2.0,-1.0)) );
    BOOST_CHECK( F<double>::strictly_less(REP<double>(-3.0,-1.5), REP<float>(-2.0f,-1.0f)) );

    BOOST_CHECK( F<float>::strictly_less(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( !F<float>::strictly_less(REP<double>(1.0,2.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( !F<float>::strictly_less(REP<float>(NaN_F,NaN_F), REP<double>(1.0,2.0)) );

    BOOST_CHECK( F<float>::strictly_less(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<float>::strictly_less(REP<float>(1.0f,2.0f), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<float>::strictly_less(REP<double>(-INF_D,+INF_D), REP<float>(1.0f,2.0f)) );

    BOOST_CHECK( !F<float>::strictly_less(REP<float>(1.0f,2.0f), REP<double>(1.0,2.0)) );
    BOOST_CHECK( F<float>::strictly_less(REP<double>(1.0,2.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<float>::strictly_less(REP<float>(1.0f,3.5f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<float>::strictly_less(REP<double>(1.0,4.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<float>::strictly_less(REP<float>(0.0f,4.0f), REP<double>(0.0,4.0)) );
    BOOST_CHECK( !F<float>::strictly_less(REP<double>(-0.0,4.0), REP<float>(0.0f,4.0f)) );

    BOOST_CHECK( !F<float>::strictly_less(REP<float>(-2.0f,-1.0f), REP<double>(-2.0,-1.0)) );
    BOOST_CHECK( F<float>::strictly_less(REP<double>(-3.0,-1.5), REP<float>(-2.0f,-1.0f)) );
}


BOOST_AUTO_TEST_CASE(minimal_strictly_less_dec_test)
{
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );

    BOOST_CHECK( F<double>::strictly_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );

    BOOST_CHECK( F<double>::strictly_less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<double>::strictly_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::strictly_less(REP_DEC<double>(REP<double>(1.0,3.5), DEC::def), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(0.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(-0.0,4.0), DEC::def), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(-2.0,-1.0), DEC::def), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::def)) );
    BOOST_CHECK( F<double>::strictly_less(REP_DEC<double>(REP<double>(-3.0,-1.5), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );
}

BOOST_AUTO_TEST_CASE(minimal_strictly_less_dec_mixedtype_test)
{
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<double>::strictly_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );

    BOOST_CHECK( F<double>::strictly_less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );

    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::def), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );
    BOOST_CHECK( F<double>::strictly_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::strictly_less(REP_DEC<float>(REP<float>(1.0f,3.5f), DEC::def), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<double>(REP<double>(-0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );

    BOOST_CHECK( !F<double>::strictly_less(REP_DEC<float>(REP<float>(-2.0f,-1.0f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );
    BOOST_CHECK( F<double>::strictly_less(REP_DEC<double>(REP<double>(-3.0,-1.5), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,-1.0f),DEC::trv)) );

    BOOST_CHECK( !F<float>::strictly_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::strictly_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<float>::strictly_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<float>::strictly_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_less(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );

    BOOST_CHECK( F<float>::strictly_less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_less(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );

    BOOST_CHECK( !F<float>::strictly_less(REP_DEC<float>(REP<float>(1.0f,2.0f), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( F<float>::strictly_less(REP_DEC<double>(REP<double>(1.0,2.0), DEC::def), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::strictly_less(REP_DEC<float>(REP<float>(1.0f,3.5f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_less(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::def)) );
    BOOST_CHECK( !F<float>::strictly_less(REP_DEC<float>(REP<float>(0.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_less(REP_DEC<double>(REP<double>(-0.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(0.0f,4.0f),DEC::trv)) );

    BOOST_CHECK( !F<float>::strictly_less(REP_DEC<float>(REP<float>(-2.0f,-1.0f), DEC::trv), REP_DEC<double>(REP<double>(-2.0,-1.0),DEC::trv)) );
    BOOST_CHECK( F<float>::strictly_less(REP_DEC<double>(REP<double>(-3.0,-1.5), DEC::trv), REP_DEC<float>(REP<float>(-2.0f,-1.0f),DEC::trv)) );
}



BOOST_AUTO_TEST_CASE(minimal_strictly_precedes_test)
{
    BOOST_CHECK( F<double>::strictly_precedes(REP<double>(NaN_D,NaN_D), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::strictly_precedes(REP<double>(3.0,4.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::strictly_precedes(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );


    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(1.0,2.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-INF_D,+INF_D), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );

    BOOST_CHECK( F<double>::strictly_precedes(REP<double>(1.0,2.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(1.0,3.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-3.0, -1.0), REP<double>(-1.0,0.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-3.0, -0.0), REP<double>(0.0,1.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-3.0, 0.0), REP<double>(-0.0,1.0)) );

    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(1.0,3.5), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(1.0,4.0), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-3.0, -0.1), REP<double>(-1.0,0.0)) );
}


BOOST_AUTO_TEST_CASE(minimal_strictly_precedes_mixedtype_test)
{
    BOOST_CHECK( F<double>::strictly_precedes(REP<double>(NaN_D,NaN_D), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<double>::strictly_precedes(REP<double>(3.0,4.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( F<double>::strictly_precedes(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );


    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(1.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<float>(-INF_F,+INF_F), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );

    BOOST_CHECK( F<double>::strictly_precedes(REP<double>(1.0,2.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<float>(1.0f,3.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-3.0, -1.0), REP<float>(-1.0f,0.0f)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<float>(-3.0f, -0.0f), REP<double>(0.0,1.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-3.0, 0.0), REP<float>(-0.0f,1.0f)) );

    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(1.0,3.5), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<float>(1.0f,4.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP<double>(-3.0, -0.1), REP<float>(-1.0f,0.0f)) );

    BOOST_CHECK( F<float>::strictly_precedes(REP<double>(NaN_D,NaN_D), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<float>::strictly_precedes(REP<double>(3.0,4.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( F<float>::strictly_precedes(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );


    BOOST_CHECK( !F<float>::strictly_precedes(REP<double>(1.0,2.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP<float>(-INF_F,+INF_F), REP<double>(1.0,2.0)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );

    BOOST_CHECK( F<float>::strictly_precedes(REP<double>(1.0,2.0), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP<float>(1.0f,3.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP<double>(-3.0, -1.0), REP<float>(-1.0f,0.0f)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP<float>(-3.0f, -0.0f), REP<double>(0.0,1.0)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP<double>(-3.0, 0.0), REP<float>(-0.0f,1.0f)) );

    BOOST_CHECK( !F<float>::strictly_precedes(REP<double>(1.0,3.5), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP<float>(1.0f,4.0f), REP<double>(3.0,4.0)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP<double>(-3.0, -0.1), REP<float>(-1.0f,0.0f)) );
}


BOOST_AUTO_TEST_CASE(minimal_strictly_precedes_dec_test)
{
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<double>::strictly_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::strictly_precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::def), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<double>::strictly_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );

    BOOST_CHECK( F<double>::strictly_precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(1.0,3.0), DEC::def), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(-3.0, -1.0), DEC::trv), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::def)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(-3.0, -0.0), DEC::def), REP_DEC<double>(REP<double>(0.0,1.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(-3.0, 0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,1.0),DEC::trv)) );

    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(1.0,3.5), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(1.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(-3.0, -0.1), DEC::trv), REP_DEC<double>(REP<double>(-1.0,0.0),DEC::trv)) );
}


BOOST_AUTO_TEST_CASE(minimal_strictly_precedes_dec_mixedtype_test)
{
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<double>::strictly_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<double>::strictly_precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( F<double>::strictly_precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::def)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );

    BOOST_CHECK( F<double>::strictly_precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<float>(REP<float>(1.0f,3.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(-3.0, -1.0), DEC::def), REP_DEC<float>(REP<float>(-1.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<float>(REP<float>(-3.0f, -0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,1.0),DEC::def)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(-3.0, 0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,1.0f),DEC::trv)) );

    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(1.0,3.5), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<float>(REP<float>(1.0f,4.0f), DEC::def), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::strictly_precedes(REP_DEC<double>(REP<double>(-3.0, -0.1), DEC::trv), REP_DEC<float>(REP<float>(-1.0f,0.0f),DEC::trv)) );

    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<float>::strictly_precedes(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::strictly_precedes(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( F<float>::strictly_precedes(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );

    BOOST_CHECK( F<float>::strictly_precedes(REP_DEC<double>(REP<double>(1.0,2.0), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<float>(REP<float>(1.0f,3.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<double>(REP<double>(-3.0, -1.0), DEC::def), REP_DEC<float>(REP<float>(-1.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<float>(REP<float>(-3.0f, -0.0f), DEC::trv), REP_DEC<double>(REP<double>(0.0,1.0),DEC::def)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<double>(REP<double>(-3.0, 0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,1.0f),DEC::trv)) );

    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<double>(REP<double>(1.0,3.5), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<float>(REP<float>(1.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::strictly_precedes(REP_DEC<double>(REP<double>(-3.0, -0.1), DEC::trv), REP_DEC<float>(REP<float>(-1.0f,0.0f),DEC::trv)) );
}


BOOST_AUTO_TEST_CASE(minimal_are_disjoint_test)
{
    BOOST_CHECK( F<double>::are_disjoint(REP<double>(NaN_D,NaN_D), REP<double>(3.0,4.0)) );
    BOOST_CHECK( F<double>::are_disjoint(REP<double>(3.0,4.0), REP<double>(NaN_D,NaN_D)) );
    BOOST_CHECK( F<double>::are_disjoint(REP<double>(NaN_D,NaN_D), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<double>::are_disjoint(REP<double>(3.0,4.0), REP<double>(1.0,2.0)) );

    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(0.0,0.0), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(0.0,-0.0), REP<double>(-0.0,0.0)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(3.0,4.0), REP<double>(1.0,7.0)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(3.0,4.0), REP<double>(-INF_D,+INF_D)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(-INF_D,+INF_D), REP<double>(1.0,7.0)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(-INF_D,+INF_D), REP<double>(-INF_D,+INF_D)) );
}

BOOST_AUTO_TEST_CASE(minimal_are_disjoint_mixedtype_test)
{
    BOOST_CHECK( F<double>::are_disjoint(REP<double>(NaN_D,NaN_D), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<double>::are_disjoint(REP<double>(3.0,4.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( F<double>::are_disjoint(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<double>::are_disjoint(REP<double>(3.0,4.0), REP<float>(1.0f,2.0f)) );

    BOOST_CHECK( !F<double>::are_disjoint(REP<float>(0.0f,0.0f), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(0.0,-0.0), REP<float>(-0.0f,0.0f)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP<float>(3.0f,4.0f), REP<double>(1.0,7.0)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(3.0,4.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP<float>(-INF_F,+INF_F), REP<double>(1.0,7.0)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );

    BOOST_CHECK( F<float>::are_disjoint(REP<double>(NaN_D,NaN_D), REP<float>(3.0f,4.0f)) );
    BOOST_CHECK( F<float>::are_disjoint(REP<double>(3.0,4.0), REP<float>(NaN_F,NaN_F)) );
    BOOST_CHECK( F<float>::are_disjoint(REP<float>(NaN_F,NaN_F), REP<double>(NaN_D,NaN_D)) );

    BOOST_CHECK( F<float>::are_disjoint(REP<double>(3.0,4.0), REP<float>(1.0f,2.0f)) );

    BOOST_CHECK( !F<float>::are_disjoint(REP<float>(0.0f,0.0f), REP<double>(-0.0,-0.0)) );
    BOOST_CHECK( !F<float>::are_disjoint(REP<double>(0.0,-0.0), REP<float>(-0.0f,0.0f)) );
    BOOST_CHECK( !F<float>::are_disjoint(REP<float>(3.0f,4.0f), REP<double>(1.0,7.0)) );
    BOOST_CHECK( !F<float>::are_disjoint(REP<double>(3.0,4.0), REP<float>(-INF_F,+INF_F)) );
    BOOST_CHECK( !F<float>::are_disjoint(REP<float>(-INF_F,+INF_F), REP<double>(1.0,7.0)) );
    BOOST_CHECK( !F<float>::are_disjoint(REP<double>(-INF_D,+INF_D), REP<float>(-INF_F,+INF_F)) );
}


BOOST_AUTO_TEST_CASE(minimal_are_disjoint_dec_test)
{
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<double>::are_disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv)) );
    BOOST_CHECK( F<double>::are_disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );
    BOOST_CHECK( F<double>::are_disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<double>::are_disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)) );

    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(0.0,0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<double>(REP<double>(-0.0,0.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::def), REP_DEC<double>(REP<double>(1.0,7.0),DEC::def)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(1.0,7.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<double>(REP<double>(-INF_D,+INF_D),DEC::trv)) );
}

BOOST_AUTO_TEST_CASE(minimal_are_disjoint_dec_mixedtype_test)
{
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<double>::are_disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::def)) );
    BOOST_CHECK( F<double>::are_disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( F<double>::are_disjoint(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<double>::are_disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );

    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::trv), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::def), REP_DEC<float>(REP<float>(-0.0f,0.0f),DEC::def)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<float>(REP<float>(3.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(1.0,7.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::def)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,7.0),DEC::trv)) );
    BOOST_CHECK( !F<double>::are_disjoint(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );

    BOOST_CHECK( !F<float>::are_disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::ill), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( !F<float>::are_disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::ill)) );
    BOOST_CHECK( !F<float>::are_disjoint(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );
    BOOST_CHECK( !F<float>::are_disjoint(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::ill), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::ill)) );

    BOOST_CHECK( F<float>::are_disjoint(REP_DEC<double>(REP<double>(NaN_D,NaN_D), DEC::trv), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)) );
    BOOST_CHECK( F<float>::are_disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(NaN_F,NaN_F),DEC::trv)) );
    BOOST_CHECK( F<float>::are_disjoint(REP_DEC<float>(REP<float>(NaN_F,NaN_F), DEC::trv), REP_DEC<double>(REP<double>(NaN_D,NaN_D),DEC::trv)) );

    BOOST_CHECK( F<float>::are_disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)) );

    BOOST_CHECK( !F<float>::are_disjoint(REP_DEC<float>(REP<float>(0.0f,0.0f), DEC::def), REP_DEC<double>(REP<double>(-0.0,-0.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::are_disjoint(REP_DEC<double>(REP<double>(0.0,-0.0), DEC::trv), REP_DEC<float>(REP<float>(-0.0f,0.0f),DEC::trv)) );
    BOOST_CHECK( !F<float>::are_disjoint(REP_DEC<float>(REP<float>(3.0f,4.0f), DEC::trv), REP_DEC<double>(REP<double>(1.0,7.0),DEC::def)) );
    BOOST_CHECK( !F<float>::are_disjoint(REP_DEC<double>(REP<double>(3.0,4.0), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
    BOOST_CHECK( !F<float>::are_disjoint(REP_DEC<float>(REP<float>(-INF_F,+INF_F), DEC::trv), REP_DEC<double>(REP<double>(1.0,7.0),DEC::trv)) );
    BOOST_CHECK( !F<float>::are_disjoint(REP_DEC<double>(REP<double>(-INF_D,+INF_D), DEC::trv), REP_DEC<float>(REP<float>(-INF_F,+INF_F),DEC::trv)) );
}
