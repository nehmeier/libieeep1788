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

#define BOOST_TEST_MODULE "Class members [infsup/interval, infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include <limits>

#include "p1788/p1788.hpp"

template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;



BOOST_AUTO_TEST_CASE(minimal_default_constructor_test)
{
    BOOST_CHECK_EQUAL(is_empty(I<double>()), true);
}

BOOST_AUTO_TEST_CASE(minimal_nums_to_interval_constructor_test)
{
    BOOST_CHECK_EQUAL(is_empty(I<double>(-1.0, 1.0)), false);
    BOOST_CHECK_EQUAL(is_empty(I<double>(1.0, -1.0)), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN())), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(std::numeric_limits<double>::quiet_NaN(), 5.0)), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::infinity())), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(0.0, std::numeric_limits<double>::quiet_NaN())), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::quiet_NaN())), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity())), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity())), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity())), false);
    BOOST_CHECK_EQUAL(is_entire(I<double>(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity())), true);
    BOOST_CHECK_EQUAL(inf(I<double>(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity())), -std::numeric_limits<double>::infinity());
    BOOST_CHECK_EQUAL(sup(I<double>(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity())), std::numeric_limits<double>::infinity());
    BOOST_CHECK_EQUAL(inf(I<double>(-1.0, 1.0)), -1.0);
    BOOST_CHECK_EQUAL(sup(I<double>(-1.0, 1.0)), 1.0);
    BOOST_CHECK_EQUAL(inf(I<double>(1.0, 1.0)), 1.0);
    BOOST_CHECK_EQUAL(sup(I<double>(1.0, 1.0)), 1.0);
    BOOST_CHECK_EQUAL(inf(I<double>(1.1, 27.3)), 1.1);
    BOOST_CHECK_EQUAL(sup(I<double>(1.1, 27.3)), 27.3);
    BOOST_CHECK_EQUAL(inf(I<double>(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest())), std::numeric_limits<double>::lowest());
    BOOST_CHECK_EQUAL(sup(I<double>(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest())), std::numeric_limits<double>::lowest());
    BOOST_CHECK_EQUAL(inf(I<double>(std::numeric_limits<double>::max(), std::numeric_limits<double>::max())), std::numeric_limits<double>::max());
    BOOST_CHECK_EQUAL(sup(I<double>(std::numeric_limits<double>::max(), std::numeric_limits<double>::max())), std::numeric_limits<double>::max());
    BOOST_CHECK_EQUAL(inf(I<double>(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())), std::numeric_limits<double>::min());
    BOOST_CHECK_EQUAL(sup(I<double>(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())), std::numeric_limits<double>::max());
    BOOST_CHECK_EQUAL(inf(I<double>(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max())), std::numeric_limits<double>::lowest());
    BOOST_CHECK_EQUAL(is_entire(I<double>(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max())), false);
}

BOOST_AUTO_TEST_CASE(minimal_singleton_constructor_test)
{
    BOOST_CHECK_EQUAL(is_empty(I<double>(-1.0)), false);
    BOOST_CHECK_EQUAL(is_empty(I<double>(1.0)), false);
    BOOST_CHECK_EQUAL(is_empty(I<double>(std::numeric_limits<double>::quiet_NaN())), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(-std::numeric_limits<double>::infinity())), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(std::numeric_limits<double>::infinity())), true);
    BOOST_CHECK_EQUAL(inf(I<double>(1.1)), 1.1);
    BOOST_CHECK_EQUAL(sup(I<double>(1.1)), 1.1);
    BOOST_CHECK_EQUAL(inf(I<double>(27.3)), 27.3);
    BOOST_CHECK_EQUAL(sup(I<double>(27.3)), 27.3);
    BOOST_CHECK_EQUAL(inf(I<double>(std::numeric_limits<double>::min())), std::numeric_limits<double>::min());
    BOOST_CHECK_EQUAL(sup(I<double>(std::numeric_limits<double>::min())), std::numeric_limits<double>::min());
    BOOST_CHECK_EQUAL(inf(I<double>(std::numeric_limits<double>::max())), std::numeric_limits<double>::max());
    BOOST_CHECK_EQUAL(sup(I<double>(std::numeric_limits<double>::max())), std::numeric_limits<double>::max());
    BOOST_CHECK_EQUAL(inf(I<double>(std::numeric_limits<double>::lowest())), std::numeric_limits<double>::lowest());
    BOOST_CHECK_EQUAL(sup(I<double>(std::numeric_limits<double>::lowest())), std::numeric_limits<double>::lowest());
}

BOOST_AUTO_TEST_CASE(minimal_format_of_nums_to_interval_constructor_test)
{
    BOOST_CHECK_EQUAL(is_empty(I<double>(-1.0f, 1.0)), false);
    BOOST_CHECK_EQUAL(is_empty(I<float>(1.0f, -1.0)), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN())), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(std::numeric_limits<float>::quiet_NaN(), 5.0)), true);
    BOOST_CHECK_EQUAL(is_empty(I<float>(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<float>::infinity())), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(0.0f, std::numeric_limits<double>::quiet_NaN())), true);
    BOOST_CHECK_EQUAL(is_empty(I<float>(-std::numeric_limits<float>::infinity(), std::numeric_limits<double>::quiet_NaN())), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity())), true);
    BOOST_CHECK_EQUAL(is_empty(I<float>(std::numeric_limits<double>::infinity(), std::numeric_limits<float>::infinity())), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(-std::numeric_limits<double>::infinity(), std::numeric_limits<float>::infinity())), false);
    BOOST_CHECK_EQUAL(is_entire(I<float>(-std::numeric_limits<double>::infinity(), std::numeric_limits<float>::infinity())), true);
    BOOST_CHECK_EQUAL(inf(I<double>(-std::numeric_limits<float>::infinity(), std::numeric_limits<double>::infinity())), -std::numeric_limits<double>::infinity());
    BOOST_CHECK_EQUAL(sup(I<double>(-std::numeric_limits<double>::infinity(), std::numeric_limits<float>::infinity())), std::numeric_limits<double>::infinity());
    BOOST_CHECK_EQUAL(inf(I<double>(-1.0f, 1.0f)), -1.0);
    BOOST_CHECK_EQUAL(sup(I<double>(-1.0f, 1.0f)), 1.0);
    BOOST_CHECK_EQUAL(inf(I<float>(1.0f, 1.0)), 1.0f);
    BOOST_CHECK_EQUAL(sup(I<double>(1.0, 1.0f)), 1.0);
    BOOST_CHECK_EQUAL(inf(I<float>(1.1, 27.3f)), 1.1f);
    BOOST_CHECK_EQUAL(sup(I<double>(1.1, 27.3f)), 27.3);
    BOOST_CHECK_EQUAL(inf(I<double>(std::numeric_limits<double>::lowest(), std::numeric_limits<float>::lowest())), static_cast<double>(std::numeric_limits<float>::lowest()));
    BOOST_CHECK_EQUAL(sup(I<double>(std::numeric_limits<double>::lowest(), std::numeric_limits<float>::lowest())), static_cast<double>(std::numeric_limits<float>::lowest()));
    BOOST_CHECK_EQUAL(inf(I<double>(std::numeric_limits<float>::max(), std::numeric_limits<double>::max())), static_cast<double>(std::numeric_limits<float>::max()));
    BOOST_CHECK_EQUAL(sup(I<double>(std::numeric_limits<float>::max(), std::numeric_limits<double>::max())), std::numeric_limits<double>::max());
    BOOST_CHECK_EQUAL(inf(I<double>(std::numeric_limits<float>::min(), std::numeric_limits<double>::max())), static_cast<double>(std::numeric_limits<float>::min()));
    BOOST_CHECK_EQUAL(sup(I<double>(std::numeric_limits<double>::min(), std::numeric_limits<float>::max())), static_cast<double>(std::numeric_limits<float>::max()));
    BOOST_CHECK_EQUAL(inf(I<double>(std::numeric_limits<float>::lowest(), std::numeric_limits<double>::max())), static_cast<double>(std::numeric_limits<float>::lowest()));
    BOOST_CHECK_EQUAL(sup(I<double>(std::numeric_limits<float>::lowest(), std::numeric_limits<double>::max())), std::numeric_limits<double>::max());
    BOOST_CHECK_EQUAL(inf(I<float>(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest())), -std::numeric_limits<float>::infinity());
    BOOST_CHECK_EQUAL(sup(I<float>(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest())), std::numeric_limits<float>::lowest());
    BOOST_CHECK_EQUAL(inf(I<float>(std::numeric_limits<double>::max(), std::numeric_limits<double>::max())), std::numeric_limits<float>::max());
    BOOST_CHECK_EQUAL(sup(I<float>(std::numeric_limits<double>::max(), std::numeric_limits<double>::max())), std::numeric_limits<float>::infinity());
    BOOST_CHECK_EQUAL(inf(I<float>(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())), -std::numeric_limits<float>::infinity());
    BOOST_CHECK_EQUAL(sup(I<float>(std::numeric_limits<double>::min(), std::numeric_limits<double>::max())), std::numeric_limits<float>::infinity());
    BOOST_CHECK_EQUAL(inf(I<float>(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max())), -std::numeric_limits<float>::infinity());
    BOOST_CHECK_EQUAL(sup(I<float>(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max())), std::numeric_limits<float>::infinity());
    BOOST_CHECK_EQUAL(is_entire(I<float>(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max())), true);
}

BOOST_AUTO_TEST_CASE(minimal_format_of_singleton_constructor_test)
{
    BOOST_CHECK_EQUAL(is_empty(I<double>(-1.0f)), false);
    BOOST_CHECK_EQUAL(is_empty(I<float>(1.0)), false);
    BOOST_CHECK_EQUAL(is_empty(I<double>(std::numeric_limits<float>::quiet_NaN())), true);
    BOOST_CHECK_EQUAL(is_empty(I<float>(-std::numeric_limits<double>::infinity())), true);
    BOOST_CHECK_EQUAL(is_empty(I<double>(std::numeric_limits<float>::infinity())), true);
    BOOST_CHECK_EQUAL(inf(I<float>(1.1)), 1.1f);
    BOOST_CHECK_EQUAL(sup(I<double>(1.1f)), 1.1);
    BOOST_CHECK_EQUAL(inf(I<double>(27.3f)), 27.3f);
    BOOST_CHECK_EQUAL(sup(I<float>(27.3)), 27.3);
    BOOST_CHECK_EQUAL(inf(I<double>(std::numeric_limits<float>::min())), static_cast<double>(std::numeric_limits<float>::min()));
    BOOST_CHECK_EQUAL(sup(I<float>(std::numeric_limits<double>::min())), std::numeric_limits<float>::min());
    BOOST_CHECK_EQUAL(inf(I<float>(std::numeric_limits<double>::min())), 0.0);
    BOOST_CHECK_EQUAL(inf(I<double>(std::numeric_limits<float>::max())), static_cast<double>(std::numeric_limits<float>::max()));
    BOOST_CHECK_EQUAL(sup(I<float>(std::numeric_limits<double>::max())), std::numeric_limits<float>::infinity());
    BOOST_CHECK_EQUAL(inf(I<float>(std::numeric_limits<double>::lowest())), std::numeric_limits<float>::lowest());
    BOOST_CHECK_EQUAL(sup(I<float>(std::numeric_limits<double>::lowest())), -std::numeric_limits<float>::infinity());
}

BOOST_AUTO_TEST_CASE(minimal_text_to_interval_constructor_test)
{
    BOOST_CHECK(false);
}

//TODO necessary?
BOOST_AUTO_TEST_CASE(minimal_points_to_interval_constructor_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_copy_constructor_test)
{
    BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(minimal_conversion_constructor_test)
{
    BOOST_CHECK(false);
}
