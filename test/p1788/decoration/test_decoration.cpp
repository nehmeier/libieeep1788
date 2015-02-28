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

#define BOOST_TEST_MODULE "Decorations [p1788/decoration/decoration]"
#include "test/util/boost_test_wrapper.hpp"

#include <sstream>

#include <boost/test/output_test_stream.hpp>

#include "p1788/decoration/decoration.hpp"
#include "p1788/io/io_manip.hpp"


typedef p1788::decoration::decoration DEC;


BOOST_AUTO_TEST_CASE(minimal_decoration_equal_test)
{
    BOOST_CHECK( (DEC::trv == DEC::trv) );
    BOOST_CHECK( !(DEC::trv == DEC::def) );
    BOOST_CHECK( !(DEC::trv == DEC::dac) );
    BOOST_CHECK( !(DEC::trv == DEC::com) );
    BOOST_CHECK( !(DEC::trv == DEC::ill) );

    BOOST_CHECK( !(DEC::def == DEC::trv) );
    BOOST_CHECK( (DEC::def == DEC::def) );
    BOOST_CHECK( !(DEC::def == DEC::dac) );
    BOOST_CHECK( !(DEC::def == DEC::com) );
    BOOST_CHECK( !(DEC::def == DEC::ill) );

    BOOST_CHECK( !(DEC::dac == DEC::trv) );
    BOOST_CHECK( !(DEC::dac == DEC::def) );
    BOOST_CHECK( (DEC::dac == DEC::dac) );
    BOOST_CHECK( !(DEC::dac == DEC::com) );
    BOOST_CHECK( !(DEC::dac == DEC::ill) );

    BOOST_CHECK( !(DEC::com == DEC::trv) );
    BOOST_CHECK( !(DEC::com == DEC::def) );
    BOOST_CHECK( !(DEC::com == DEC::dac) );
    BOOST_CHECK( (DEC::com == DEC::com) );
    BOOST_CHECK( !(DEC::com == DEC::ill) );

    BOOST_CHECK( !(DEC::ill == DEC::trv) );
    BOOST_CHECK( !(DEC::ill == DEC::def) );
    BOOST_CHECK( !(DEC::ill == DEC::dac) );
    BOOST_CHECK( !(DEC::ill == DEC::com) );
    BOOST_CHECK( (DEC::ill == DEC::ill) );
}

BOOST_AUTO_TEST_CASE(minimal_decoration_not_equal_test)
{
    BOOST_CHECK( !(DEC::trv != DEC::trv) );
    BOOST_CHECK( (DEC::trv != DEC::def) );
    BOOST_CHECK( (DEC::trv != DEC::dac) );
    BOOST_CHECK( (DEC::trv != DEC::com) );
    BOOST_CHECK( (DEC::trv != DEC::ill) );

    BOOST_CHECK( (DEC::def != DEC::trv) );
    BOOST_CHECK( !(DEC::def != DEC::def) );
    BOOST_CHECK( (DEC::def != DEC::dac) );
    BOOST_CHECK( (DEC::def != DEC::com) );
    BOOST_CHECK( (DEC::def != DEC::ill) );

    BOOST_CHECK( (DEC::dac != DEC::trv) );
    BOOST_CHECK( (DEC::dac != DEC::def) );
    BOOST_CHECK( !(DEC::dac != DEC::dac) );
    BOOST_CHECK( (DEC::dac != DEC::com) );
    BOOST_CHECK( (DEC::dac != DEC::ill) );

    BOOST_CHECK( (DEC::com != DEC::trv) );
    BOOST_CHECK( (DEC::com != DEC::def) );
    BOOST_CHECK( (DEC::com != DEC::dac) );
    BOOST_CHECK( !(DEC::com != DEC::com) );
    BOOST_CHECK( (DEC::com != DEC::ill) );

    BOOST_CHECK( (DEC::ill != DEC::trv) );
    BOOST_CHECK( (DEC::ill != DEC::def) );
    BOOST_CHECK( (DEC::ill != DEC::dac) );
    BOOST_CHECK( (DEC::ill != DEC::com) );
    BOOST_CHECK( !(DEC::ill != DEC::ill) );
}

BOOST_AUTO_TEST_CASE(minimal_decoration_lower_test)
{
    BOOST_CHECK( !(DEC::trv < DEC::trv) );
    BOOST_CHECK( (DEC::trv < DEC::def) );
    BOOST_CHECK( (DEC::trv < DEC::dac) );
    BOOST_CHECK( (DEC::trv < DEC::com) );
    BOOST_CHECK( !(DEC::trv < DEC::ill) );

    BOOST_CHECK( !(DEC::def < DEC::trv) );
    BOOST_CHECK( !(DEC::def < DEC::def) );
    BOOST_CHECK( (DEC::def < DEC::dac) );
    BOOST_CHECK( (DEC::def < DEC::com) );
    BOOST_CHECK( !(DEC::def < DEC::ill) );

    BOOST_CHECK( !(DEC::dac < DEC::trv) );
    BOOST_CHECK( !(DEC::dac < DEC::def) );
    BOOST_CHECK( !(DEC::dac < DEC::dac) );
    BOOST_CHECK( (DEC::dac < DEC::com) );
    BOOST_CHECK( !(DEC::dac < DEC::ill) );

    BOOST_CHECK( !(DEC::com < DEC::trv) );
    BOOST_CHECK( !(DEC::com < DEC::def) );
    BOOST_CHECK( !(DEC::com < DEC::dac) );
    BOOST_CHECK( !(DEC::com < DEC::com) );
    BOOST_CHECK( !(DEC::com < DEC::ill) );

    BOOST_CHECK( (DEC::ill < DEC::trv) );
    BOOST_CHECK( (DEC::ill < DEC::def) );
    BOOST_CHECK( (DEC::ill < DEC::dac) );
    BOOST_CHECK( (DEC::ill < DEC::com) );
    BOOST_CHECK( !(DEC::ill < DEC::ill) );
}

BOOST_AUTO_TEST_CASE(minimal_decoration_lower_equal_test)
{
    BOOST_CHECK( (DEC::trv <= DEC::trv) );
    BOOST_CHECK( (DEC::trv <= DEC::def) );
    BOOST_CHECK( (DEC::trv <= DEC::dac) );
    BOOST_CHECK( (DEC::trv <= DEC::com) );
    BOOST_CHECK( !(DEC::trv <= DEC::ill) );

    BOOST_CHECK( !(DEC::def <= DEC::trv) );
    BOOST_CHECK( (DEC::def <= DEC::def) );
    BOOST_CHECK( (DEC::def <= DEC::dac) );
    BOOST_CHECK( (DEC::def <= DEC::com) );
    BOOST_CHECK( !(DEC::def <= DEC::ill) );

    BOOST_CHECK( !(DEC::dac <= DEC::trv) );
    BOOST_CHECK( !(DEC::dac <= DEC::def) );
    BOOST_CHECK( (DEC::dac <= DEC::dac) );
    BOOST_CHECK( (DEC::dac <= DEC::com) );
    BOOST_CHECK( !(DEC::dac <= DEC::ill) );

    BOOST_CHECK( !(DEC::com <= DEC::trv) );
    BOOST_CHECK( !(DEC::com <= DEC::def) );
    BOOST_CHECK( !(DEC::com <= DEC::dac) );
    BOOST_CHECK( (DEC::com <= DEC::com) );
    BOOST_CHECK( !(DEC::com <= DEC::ill) );

    BOOST_CHECK( (DEC::ill <= DEC::trv) );
    BOOST_CHECK( (DEC::ill <= DEC::def) );
    BOOST_CHECK( (DEC::ill <= DEC::dac) );
    BOOST_CHECK( (DEC::ill <= DEC::com) );
    BOOST_CHECK( (DEC::ill <= DEC::ill) );
}

BOOST_AUTO_TEST_CASE(minimal_decoration_greater_test)
{
    BOOST_CHECK( !(DEC::trv > DEC::trv) );
    BOOST_CHECK( !(DEC::trv > DEC::def) );
    BOOST_CHECK( !(DEC::trv > DEC::dac) );
    BOOST_CHECK( !(DEC::trv > DEC::com) );
    BOOST_CHECK( (DEC::trv > DEC::ill) );

    BOOST_CHECK( (DEC::def > DEC::trv) );
    BOOST_CHECK( !(DEC::def > DEC::def) );
    BOOST_CHECK( !(DEC::def > DEC::dac) );
    BOOST_CHECK( !(DEC::def > DEC::com) );
    BOOST_CHECK( (DEC::def > DEC::ill) );

    BOOST_CHECK( (DEC::dac > DEC::trv) );
    BOOST_CHECK( (DEC::dac > DEC::def) );
    BOOST_CHECK( !(DEC::dac > DEC::dac) );
    BOOST_CHECK( !(DEC::dac > DEC::com) );
    BOOST_CHECK( (DEC::dac > DEC::ill) );

    BOOST_CHECK( (DEC::com > DEC::trv) );
    BOOST_CHECK( (DEC::com > DEC::def) );
    BOOST_CHECK( (DEC::com > DEC::dac) );
    BOOST_CHECK( !(DEC::com > DEC::com) );
    BOOST_CHECK( (DEC::com > DEC::ill) );

    BOOST_CHECK( !(DEC::ill > DEC::trv) );
    BOOST_CHECK( !(DEC::ill > DEC::def) );
    BOOST_CHECK( !(DEC::ill > DEC::dac) );
    BOOST_CHECK( !(DEC::ill > DEC::com) );
    BOOST_CHECK( !(DEC::ill > DEC::ill) );
}

BOOST_AUTO_TEST_CASE(minimal_decoration_greater_equal_test)
{
    BOOST_CHECK( (DEC::trv >= DEC::trv) );
    BOOST_CHECK( !(DEC::trv >= DEC::def) );
    BOOST_CHECK( !(DEC::trv >= DEC::dac) );
    BOOST_CHECK( !(DEC::trv >= DEC::com) );
    BOOST_CHECK( (DEC::trv >= DEC::ill) );

    BOOST_CHECK( (DEC::def >= DEC::trv) );
    BOOST_CHECK( (DEC::def >= DEC::def) );
    BOOST_CHECK( !(DEC::def >= DEC::dac) );
    BOOST_CHECK( !(DEC::def >= DEC::com) );
    BOOST_CHECK( (DEC::def >= DEC::ill) );

    BOOST_CHECK( (DEC::dac >= DEC::trv) );
    BOOST_CHECK( (DEC::dac >= DEC::def) );
    BOOST_CHECK( (DEC::dac >= DEC::dac) );
    BOOST_CHECK( !(DEC::dac >= DEC::com) );
    BOOST_CHECK( (DEC::dac >= DEC::ill) );

    BOOST_CHECK( (DEC::com >= DEC::trv) );
    BOOST_CHECK( (DEC::com >= DEC::def) );
    BOOST_CHECK( (DEC::com >= DEC::dac) );
    BOOST_CHECK( (DEC::com >= DEC::com) );
    BOOST_CHECK( (DEC::com >= DEC::ill) );

    BOOST_CHECK( !(DEC::ill >= DEC::trv) );
    BOOST_CHECK( !(DEC::ill >= DEC::def) );
    BOOST_CHECK( !(DEC::ill >= DEC::dac) );
    BOOST_CHECK( !(DEC::ill >= DEC::com) );
    BOOST_CHECK( (DEC::ill >= DEC::ill) );
}

BOOST_AUTO_TEST_CASE(minimal_decoration_is_valid_test)
{
    p1788::exception::clear();

    BOOST_CHECK( p1788::decoration::is_valid(DEC::ill) );
    BOOST_CHECK( p1788::decoration::is_valid(DEC::trv) );
    BOOST_CHECK( p1788::decoration::is_valid(DEC::def) );
    BOOST_CHECK( p1788::decoration::is_valid(DEC::dac) );
    BOOST_CHECK( p1788::decoration::is_valid(DEC::com) );

    BOOST_CHECK(!p1788::exception::invalid_operand());

    DEC bad_dec = static_cast<p1788::decoration::decoration>(13);

    BOOST_CHECK( !p1788::decoration::is_valid(bad_dec) );
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();

    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW(p1788::decoration::is_valid(bad_dec), p1788::exception::invalid_operand_exception);
    BOOST_CHECK(p1788::exception::invalid_operand());
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(minimal_decoration_output_test)
{
    boost::test_tools::output_test_stream output;


    output << DEC::trv;
    BOOST_CHECK( output.is_equal( "trv" ) );

    output << DEC::def;
    BOOST_CHECK( output.is_equal( "def" ) );

    output << DEC::dac;
    BOOST_CHECK( output.is_equal( "dac" ) );

    output << DEC::com;
    BOOST_CHECK( output.is_equal( "com" ) );

    output << DEC::ill;
    BOOST_CHECK( output.is_equal( "ill" ) );


    output << p1788::io::dec_numeric;

    output << DEC::trv;
    BOOST_CHECK( output.is_equal( "4" ) );

    output << DEC::def;
    BOOST_CHECK( output.is_equal( "8" ) );

    output << DEC::dac;
    BOOST_CHECK( output.is_equal( "12" ) );

    output << DEC::com;
    BOOST_CHECK( output.is_equal( "16" ) );

    output << DEC::ill;
    BOOST_CHECK( output.is_equal( "0" ) );


    output << p1788::io::dec_alpha;
    output << p1788::io::upper_case;

    output << DEC::com;
    BOOST_CHECK( output.is_equal( "COM" ) );

    output << DEC::ill;
    BOOST_CHECK( output.is_equal( "ILL" ) );

    output << DEC::trv;
    BOOST_CHECK( output.is_equal( "TRV" ) );

    output << DEC::def;
    BOOST_CHECK( output.is_equal( "DEF" ) );

    output << DEC::dac;
    BOOST_CHECK( output.is_equal( "DAC" ) );

    output << p1788::io::lower_case;
    output << DEC::com;
    BOOST_CHECK( output.is_equal( "com" ) );

    output << DEC::ill;
    BOOST_CHECK( output.is_equal( "ill" ) );
}

BOOST_AUTO_TEST_CASE(minimal_decoration_input_test)
{
    {
        DEC dec;
        std::istringstream is("ill");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::ill);
        BOOST_CHECK(is);
    }


    {
        DEC dec;
        std::istringstream is("0");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::ill);
        BOOST_CHECK(is);
    }


    {
        DEC dec;
        std::istringstream is("trv");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::trv);
        BOOST_CHECK(is);
    }


    {
        DEC dec;
        std::istringstream is("4");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::trv);
        BOOST_CHECK(is);
    }


    {
        DEC dec;
        std::istringstream is("def");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::def);
        BOOST_CHECK(is);
    }


    {
        DEC dec;
        std::istringstream is("8");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::def);
        BOOST_CHECK(is);
    }


    {
        DEC dec;
        std::istringstream is("dac");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::dac);
        BOOST_CHECK(is);
    }


    {
        DEC dec;
        std::istringstream is("12");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::dac);
        BOOST_CHECK(is);
    }


    {
        DEC dec;
        std::istringstream is("com");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::com);
        BOOST_CHECK(is);
    }


    {
        DEC dec;
        std::istringstream is("16");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::com);
        BOOST_CHECK(is);
    }


    {
        DEC dec;
        std::istringstream is("dac4");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::dac);
        BOOST_CHECK(is);
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::trv);
        BOOST_CHECK(is);
    }

    {
        DEC dec;
        std::istringstream is("8 dac 4");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::def);
        BOOST_CHECK(is);
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::dac);
        BOOST_CHECK(is);
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::trv);
        BOOST_CHECK(is);
    }

    {
        DEC dec;
        std::istringstream is("  DAC  16");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::dac);
        BOOST_CHECK(is);
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::com);
        BOOST_CHECK(is);
    }


    {
        DEC dec = DEC::com;
        std::istringstream is("  def");
        is >> std::noskipws;
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::com);
        BOOST_CHECK(is.fail());
    }

    {
        DEC dec = DEC::trv;
        std::istringstream is("  12");
        is >> std::noskipws;
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::trv);
        BOOST_CHECK(is.fail());
    }

    {
        DEC dec;
        std::istringstream is("\n 4 \t DEF \n");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::trv);
        BOOST_CHECK(is);
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::def);
        BOOST_CHECK(is);
    }

    {
        DEC dec = DEC::trv;
        std::istringstream is("foo com");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::trv);
        BOOST_CHECK(is.fail());
    }


    {
        DEC dec = DEC::dac;
        std::istringstream is(" \t \n \t ");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::dac);
        BOOST_CHECK(is.fail());
    }


    {
        DEC dec = DEC::com;
        std::istringstream is("7");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::com);
        BOOST_CHECK(is.fail());
    }

    {
        DEC dec = DEC::def;
        std::istringstream is("-2");
        is >> dec;
        BOOST_CHECK_EQUAL(dec, DEC::def);
        BOOST_CHECK(is.fail());
    }
}
