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

#define BOOST_TEST_MODULE "Exceptions [p1788/exception/exception]"
#include "test/util/boost_test_wrapper.hpp"

#include "p1788/exception/exception.hpp"

using namespace p1788;

BOOST_AUTO_TEST_CASE(minimal_exception_test)
{
    BOOST_CHECK_EQUAL(exception::get_throw_exception_cwd(), exception::none_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::none_bit);
    BOOST_CHECK(!exception::state());
    BOOST_CHECK(!exception::undefined_operation());
    BOOST_CHECK(!exception::possibly_undefined_operation());
    BOOST_CHECK(!exception::interval_part_of_nai());
    BOOST_CHECK(!exception::invalid_operand());

    BOOST_CHECK_EQUAL(exception::signal_undefined_operation(), exception::undefined_operation_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::undefined_operation_bit);
    BOOST_CHECK(exception::state());
    BOOST_CHECK(exception::undefined_operation());
    BOOST_CHECK_EQUAL(exception::clear(), exception::none_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::none_bit);
    BOOST_CHECK(!exception::state());
    BOOST_CHECK(!exception::undefined_operation());

    BOOST_CHECK(!exception::state());
    BOOST_CHECK(!exception::possibly_undefined_operation());
    BOOST_CHECK_EQUAL(exception::signal_possibly_undefined_operation(), exception::possibly_undefined_operation_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::possibly_undefined_operation_bit);
    BOOST_CHECK(exception::state());
    BOOST_CHECK(exception::possibly_undefined_operation());
    BOOST_CHECK_EQUAL(exception::clear(), exception::none_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::none_bit);
    BOOST_CHECK(!exception::state());
    BOOST_CHECK(!exception::possibly_undefined_operation());

    BOOST_CHECK(!exception::state());
    BOOST_CHECK(!exception::interval_part_of_nai());
    BOOST_CHECK_EQUAL(exception::signal_interval_part_of_nai(), exception::interval_part_of_nai_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::interval_part_of_nai_bit);
    BOOST_CHECK(exception::state());
    BOOST_CHECK(exception::interval_part_of_nai());
    BOOST_CHECK_EQUAL(exception::clear(), exception::none_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::none_bit);
    BOOST_CHECK(!exception::state());
    BOOST_CHECK(!exception::interval_part_of_nai());

    BOOST_CHECK(!exception::state());
    BOOST_CHECK(!exception::invalid_operand());
    BOOST_CHECK_EQUAL(exception::signal_invalid_operand(), exception::invalid_operand_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::invalid_operand_bit);
    BOOST_CHECK(exception::state());
    BOOST_CHECK(exception::invalid_operand());
    BOOST_CHECK_EQUAL(exception::clear(), exception::none_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::none_bit);
    BOOST_CHECK(!exception::state());
    BOOST_CHECK(!exception::invalid_operand());

    BOOST_CHECK_EQUAL(exception::set_throw_exception_cwd(exception::invalid_operand_bit | exception::interval_part_of_nai_bit | exception::possibly_undefined_operation_bit | exception::undefined_operation_bit), exception::invalid_operand_bit | exception::interval_part_of_nai_bit | exception::possibly_undefined_operation_bit | exception::undefined_operation_bit);
    BOOST_CHECK(!exception::state());
    BOOST_CHECK_THROW(exception::signal_invalid_operand(), exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(exception::state(), exception::invalid_operand_bit);
    BOOST_CHECK(exception::state());
    BOOST_CHECK(exception::invalid_operand());
    BOOST_CHECK_THROW(exception::signal_interval_part_of_nai(), exception::interval_part_of_nai_exception);
    BOOST_CHECK_EQUAL(exception::state(), exception::invalid_operand_bit | exception::interval_part_of_nai_bit);
    BOOST_CHECK(exception::state());
    BOOST_CHECK(exception::interval_part_of_nai());
    BOOST_CHECK_THROW(exception::signal_possibly_undefined_operation(), exception::possibly_undefined_operation_exception);
    BOOST_CHECK_EQUAL(exception::state(), exception::invalid_operand_bit | exception::interval_part_of_nai_bit | exception::possibly_undefined_operation_bit);
    BOOST_CHECK(exception::state());
    BOOST_CHECK(exception::possibly_undefined_operation());
    BOOST_CHECK_THROW(exception::signal_undefined_operation(), exception::undefined_operation_exception);
    BOOST_CHECK_EQUAL(exception::state(), exception::invalid_operand_bit | exception::interval_part_of_nai_bit | exception::possibly_undefined_operation_bit | exception::undefined_operation_bit);
    BOOST_CHECK(exception::state());
    BOOST_CHECK(exception::undefined_operation());
    BOOST_CHECK_EQUAL(exception::clear(), exception::none_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::none_bit);
    BOOST_CHECK(!exception::state());
    BOOST_CHECK(!exception::invalid_operand());
    BOOST_CHECK_EQUAL(exception::set_throw_exception_cwd(exception::none_bit), exception::none_bit);
    BOOST_CHECK_EQUAL(exception::get_throw_exception_cwd(), exception::none_bit);


    BOOST_CHECK(!exception::state());
    BOOST_CHECK_EQUAL(exception::signal_invalid_operand(), exception::invalid_operand_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::invalid_operand_bit);
    BOOST_CHECK(exception::state());
    BOOST_CHECK(exception::invalid_operand());
    BOOST_CHECK_EQUAL(exception::signal_interval_part_of_nai(), exception::invalid_operand_bit | exception::interval_part_of_nai_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::invalid_operand_bit | exception::interval_part_of_nai_bit);
    BOOST_CHECK(exception::state());
    BOOST_CHECK(exception::interval_part_of_nai());
    BOOST_CHECK_EQUAL(exception::signal_possibly_undefined_operation(), exception::invalid_operand_bit | exception::interval_part_of_nai_bit | exception::possibly_undefined_operation_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::invalid_operand_bit | exception::interval_part_of_nai_bit | exception::possibly_undefined_operation_bit);
    BOOST_CHECK(exception::state());
    BOOST_CHECK(exception::possibly_undefined_operation());
    BOOST_CHECK_EQUAL(exception::signal_undefined_operation(), exception::invalid_operand_bit | exception::interval_part_of_nai_bit | exception::possibly_undefined_operation_bit | exception::undefined_operation_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::invalid_operand_bit | exception::interval_part_of_nai_bit | exception::possibly_undefined_operation_bit | exception::undefined_operation_bit);
    BOOST_CHECK(exception::state());
    BOOST_CHECK(exception::undefined_operation());
    BOOST_CHECK_EQUAL(exception::clear(), exception::none_bit);
    BOOST_CHECK_EQUAL(exception::state(), exception::none_bit);
    BOOST_CHECK(!exception::state());
    BOOST_CHECK(!exception::invalid_operand());
}
