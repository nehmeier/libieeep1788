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

#define BOOST_TEST_MODULE "MPFR utility funcitons [p1788/util/mpfr_util]"
#include "test/util/boost_test_wrapper.hpp"

#include <string>

#include "p1788/util/mpfr_util.hpp"

BOOST_AUTO_TEST_CASE(minimal_two_sum_test)
{
    BOOST_CHECK_EQUAL( p1788::util::two_sum(std::stod("0X1.1111111111111P+100"), std::stod("0X1.1111111111111P+1")).first, std::stod("0X1.1111111111111P+100") );
    BOOST_CHECK_EQUAL( p1788::util::two_sum(std::stod("0X1.1111111111111P+100"), std::stod("0X1.1111111111111P+1")).second, std::stod("0X1.1111111111111P+1") );

    BOOST_CHECK_EQUAL( p1788::util::two_sum(std::stod("0X1.1111111111111P+53"), std::stod("0X1.1111111111111P+1")).first, std::stod("0X1.1111111111112P+53") );
    BOOST_CHECK_EQUAL( p1788::util::two_sum(std::stod("0X1.1111111111111P+53"), std::stod("0X1.1111111111111P+1")).second, std::stod("0X1.111111111111P-3") );

    BOOST_CHECK_EQUAL( p1788::util::two_sum(std::stod("0X1.1111111111111P+2"), std::stod("0X1.1111111111111P+1")).first, std::stod("0X1.999999999999AP+2") );
    BOOST_CHECK_EQUAL( p1788::util::two_sum(std::stod("0X1.1111111111111P+2"), std::stod("0X1.1111111111111P+1")).second, std::stod("-0X1P-51") );
}

