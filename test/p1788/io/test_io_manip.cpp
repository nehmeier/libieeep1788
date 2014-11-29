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

#define BOOST_TEST_MODULE "IO manipulators [p1788/io/io_manip]"
#include "test/util/boost_test_wrapper.hpp"

#include <iostream>

#include "p1788/io/io_manip.hpp"



using namespace p1788;

BOOST_AUTO_TEST_CASE(minimal_text_representation_test)
{
    std::stringstream stream;

    BOOST_CHECK_EQUAL( stream.iword(p1788::io::text_representation_manip_id), p1788::io::lower_case_text_representation );

    stream << p1788::io::upper_case;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::text_representation_manip_id), p1788::io::upper_case_text_representation );

    stream << p1788::io::lower_case;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::text_representation_manip_id), p1788::io::lower_case_text_representation );
}

BOOST_AUTO_TEST_CASE(minimal_string_width_test)
{
    std::stringstream stream;

    BOOST_CHECK_EQUAL( stream.iword(p1788::io::string_width_manip_id), 0 );

    stream << p1788::io::string_width(12);
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::string_width_manip_id), 12 );

    stream << p1788::io::string_width(27);
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::string_width_manip_id), 27 );

    stream << p1788::io::string_width(0);
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::string_width_manip_id), 0 );
}

BOOST_AUTO_TEST_CASE(minimal_representation_test)
{
    std::stringstream stream;

    BOOST_CHECK_EQUAL( stream.iword(p1788::io::representation_manip_id), p1788::io::inf_sup_representation );

    stream << p1788::io::uncertain_form;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::representation_manip_id), p1788::io::uncertain_representation );

    stream << p1788::io::uncertain_up_form;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::representation_manip_id), p1788::io::uncertain_up_representation );

    stream << p1788::io::uncertain_down_form;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::representation_manip_id), p1788::io::uncertain_down_representation );

    stream << p1788::io::inf_sup_form;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::representation_manip_id), p1788::io::inf_sup_representation );
}

BOOST_AUTO_TEST_CASE(minimal_number_representation_test)
{
    std::stringstream stream;

    BOOST_CHECK_EQUAL( stream.iword(p1788::io::number_representation_manip_id), p1788::io::decimal_scientific_representation );

    stream << p1788::io::decimal;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::number_representation_manip_id), p1788::io::decimal_representation );

    stream << p1788::io::scientific;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::number_representation_manip_id), p1788::io::scientific_representation );

    stream << p1788::io::hex;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::number_representation_manip_id), p1788::io::hex_representation );

    stream << p1788::io::decimal_scientific;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::number_representation_manip_id), p1788::io::decimal_scientific_representation );
}

BOOST_AUTO_TEST_CASE(minimal_width_test)
{
    std::stringstream stream;

    BOOST_CHECK_EQUAL( stream.iword(p1788::io::width_manip_id), 0 );

    stream << p1788::io::width(9);
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::width_manip_id), 9 );

    stream << p1788::io::width(15);
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::width_manip_id), 15 );

    stream << p1788::io::width(0);
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::width_manip_id), 0 );
}

BOOST_AUTO_TEST_CASE(minimal_precision_test)
{
    std::stringstream stream;

    BOOST_CHECK_EQUAL( stream.iword(p1788::io::precision_manip_id), 0 );

    stream << p1788::io::precision(16);
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::precision_manip_id), 16 );

    stream << p1788::io::precision(8);
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::precision_manip_id), 8 );

    stream << p1788::io::precision(0);
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::precision_manip_id), 0 );
}

BOOST_AUTO_TEST_CASE(minimal_special_representation_test)
{
    std::stringstream stream;

    BOOST_CHECK_EQUAL( stream.iword(p1788::io::special_representation_manip_id), p1788::io::text_special_representation );

    stream << p1788::io::special_bounds;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::special_representation_manip_id), p1788::io::bounds_special_representation );

    stream << p1788::io::special_no_bounds;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::special_representation_manip_id), p1788::io::no_bounds_special_representation );

    stream << p1788::io::special_text;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::special_representation_manip_id), p1788::io::text_special_representation );
}

BOOST_AUTO_TEST_CASE(minimal_punctuation_test)
{
    std::stringstream stream;

    BOOST_CHECK_EQUAL( stream.iword(p1788::io::punctuation_manip_id), p1788::io::show_punctuation );

    stream << p1788::io::no_punctuation;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::punctuation_manip_id), p1788::io::show_no_punctuation );

    stream << p1788::io::punctuation;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::punctuation_manip_id), p1788::io::show_punctuation );
}

BOOST_AUTO_TEST_CASE(minimal_uncertain_exponent_test)
{
    std::stringstream stream;

    BOOST_CHECK_EQUAL( stream.iword(p1788::io::uncertain_exponent_manip_id), p1788::io::show_no_uncertain_exponent );

    stream << p1788::io::uncertain_exponent;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::uncertain_exponent_manip_id), p1788::io::show_uncertain_exponent );

    stream << p1788::io::no_uncertain_exponent;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::uncertain_exponent_manip_id), p1788::io::show_no_uncertain_exponent );
}


BOOST_AUTO_TEST_CASE(minimal_decoration_test)
{
    std::stringstream stream;

    BOOST_CHECK_EQUAL( stream.iword(p1788::io::dec_manip_id), p1788::io::dec_alpha_representation );

    stream << p1788::io::dec_numeric;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::dec_manip_id), p1788::io::dec_numeric_representation );

    stream << p1788::io::dec_alpha;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::dec_manip_id), p1788::io::dec_alpha_representation );
}


BOOST_AUTO_TEST_CASE(minimal_overlapping_test)
{
    std::stringstream stream;

    BOOST_CHECK_EQUAL( stream.iword(p1788::io::overlapping_manip_id), p1788::io::overlapping_alpha_representation );

    stream << p1788::io::overlapping_numeric;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::overlapping_manip_id), p1788::io::overlapping_numeric_representation );

    stream << p1788::io::overlapping_alpha;
    BOOST_CHECK_EQUAL( stream.iword(p1788::io::overlapping_manip_id), p1788::io::overlapping_alpha_representation );
}
