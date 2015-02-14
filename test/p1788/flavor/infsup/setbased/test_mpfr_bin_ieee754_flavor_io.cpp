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

#define BOOST_TEST_MODULE "Flavor: IO [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include "p1788/exception/exception.hpp"
#include "p1788/decoration/decoration.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"

#include "test/util/mpfr_bin_ieee754_flavor_io_test_util.hpp"

#include <boost/test/output_test_stream.hpp>

#include <limits>
#include <sstream>

template<typename T>
using F = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>;

template<typename T>
using REP = typename F<T>::representation;

template<typename T>
using REP_DEC = typename F<T>::representation_dec;

typedef p1788::decoration::decoration DEC;

const double INF_D = std::numeric_limits<double>::infinity();
const double MAX_D = std::numeric_limits<double>::max();


BOOST_AUTO_TEST_CASE(minimal_empty_output_test)
{
    boost::test_tools::output_test_stream output;

    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[empty]" ) );


    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[EMPTY]" ) );

    output << p1788::io::hex;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(12);
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[  empty   ]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "   EMPTY    " ) );

    output << p1788::io::string_width(11);
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "   EMPTY   " ) );

    output << p1788::io::decimal;
    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[  empty  ]" ) );

    output << p1788::io::dec_numeric;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_no_bounds;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[ ]" ) );

    output << p1788::io::hex;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[ ]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(9);
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[       ]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "  EMPTY  " ) );

    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_bounds;
    output << p1788::io::punctuation;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[inf,-inf]" ) );

    output << p1788::io::dec_alpha;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[INF,-INF]" ) );

    output << p1788::io::hex;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(9);
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[inf,-inf]" ) );

    output << p1788::io::string_width(15);
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[  inf,   -inf]" ) );

    output << p1788::io::string_width(16);
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[   inf,   -inf]" ) );

    output << p1788::io::decimal;
    output << p1788::io::string_width(17);
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[   INF,    -INF]" ) );

    output << p1788::io::string_width(18);
    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[    inf,    -inf]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "     INF      -INF" ) );

    output << p1788::io::hex;
    output << p1788::io::upper_case;
    output << p1788::io::string_width(0);
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "INF -INF" ) );

    output << p1788::io::special_text;
    output << p1788::io::punctuation;
    output << p1788::io::width(10);
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[        EMPTY        ]" ) );

    output << p1788::io::special_bounds;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[       INF,      -INF]" ) );

    output << p1788::io::string_width(23);
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[       INF,      -INF]" ) );

    output << p1788::io::string_width(25);
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[        INF,       -INF]" ) );

    output << p1788::io::special_no_bounds;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[                       ]" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[                     ]" ) );

    output << p1788::io::special_bounds;
    output << p1788::io::precision(27);
    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[       inf,      -inf]" ) );
}



BOOST_AUTO_TEST_CASE(minimal_empty_dec_output_test)
{
    boost::test_tools::output_test_stream output;

    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[empty]" ) );

    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[EMPTY]" ) );

    output << p1788::io::hex;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(12);
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[  empty   ]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "   EMPTY    " ) );

    output << p1788::io::string_width(11);
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "   EMPTY   " ) );

    output << p1788::io::decimal;
    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[  empty  ]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_no_bounds;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[ ]" ) );

    output << p1788::io::dec_numeric;
    output << p1788::io::hex;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[ ]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(9);
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[       ]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "  EMPTY  " ) );

    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_bounds;
    output << p1788::io::punctuation;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[inf,-inf]" ) );

    output << p1788::io::dec_alpha;
    output << p1788::io::hex;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[INF,-INF]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(9);
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[inf,-inf]" ) );

    output << p1788::io::string_width(15);
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[  inf,   -inf]" ) );

    output << p1788::io::string_width(16);
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[   inf,   -inf]" ) );

    output << p1788::io::decimal;
    output << p1788::io::string_width(17);
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[   INF,    -INF]" ) );

    output << p1788::io::hex;
    output << p1788::io::string_width(18);
    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[    inf,    -inf]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "     INF      -INF" ) );

    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "inf -inf" ) );

    output << p1788::io::hex;
    output << p1788::io::special_text;
    output << p1788::io::punctuation;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[empty]" ) );

    output << p1788::io::inf_sup_form;
    output << p1788::io::width(10);
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[        empty        ]" ) );

    output << p1788::io::special_bounds;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[       inf,      -inf]" ) );

    output << p1788::io::string_width(23);
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[       inf,      -inf]" ) );

    output << p1788::io::string_width(25);
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[        inf,       -inf]" ) );

    output << p1788::io::special_no_bounds;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[                       ]" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[                     ]" ) );

    output << p1788::io::special_bounds;
    output << p1788::io::precision(27);
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[       INF,      -INF]" ) );
}


BOOST_AUTO_TEST_CASE(minimal_entire_output_test)
{
    boost::test_tools::output_test_stream output;

    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[entire]" ) );

    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[ENTIRE]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(12);
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[  entire  ]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "   ENTIRE   " ) );

    output << p1788::io::hex;
    output << p1788::io::string_width(11);
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "  ENTIRE   " ) );

    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[ entire  ]" ) );

    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_no_bounds;
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[,]" ) );

    output << p1788::io::dec_numeric;
    output << p1788::io::hex;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[,]" ) );

    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(9);
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[   ,   ]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( " ENTIRE  " ) );

    output << p1788::io::hex;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_bounds;
    output << p1788::io::punctuation;
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[-inf,inf]" ) );

    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[-INF,INF]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(6);
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[-inf,inf]" ) );

    output << p1788::io::dec_alpha;
    output << p1788::io::decimal;
    output << p1788::io::string_width(15);
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[  -inf,   inf]" ) );

    output << p1788::io::string_width(16);
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[   -INF,   INF]" ) );

    output << p1788::io::hex;
    output << p1788::io::string_width(17);
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[   -INF,    INF]" ) );

    output << p1788::io::string_width(18);
    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[    -inf,    inf]" ) );

    output << p1788::io::decimal;
    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "     -INF      INF" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_interval_to_text(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "-INF INF" ) );

    output << p1788::io::special_text;
    output << p1788::io::punctuation;
    output << p1788::io::inf_sup_form;
    output << p1788::io::width(10);
    F<double>::operator_interval_to_text(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[        ENTIRE       ]" ) );

    output << p1788::io::special_bounds;
    F<double>::operator_interval_to_text(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[      -INF,       INF]" ) );

    output << p1788::io::string_width(23);
    F<double>::operator_interval_to_text(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[      -INF,       INF]" ) );

    output << p1788::io::string_width(25);
    F<double>::operator_interval_to_text(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[       -INF,        INF]" ) );

    output << p1788::io::special_no_bounds;
    F<double>::operator_interval_to_text(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[           ,           ]" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_interval_to_text(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[          ,          ]" ) );

    output << p1788::io::special_bounds;
    output << p1788::io::precision(27);
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[      -INF,       INF]" ) );
}

BOOST_AUTO_TEST_CASE(minimal_entire_dec_output_test)
{
    boost::test_tools::output_test_stream output;

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[entire]_trv" ) );

    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[ENTIRE]_DAC" ) );

    output << p1788::io::hex;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(13);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[entire ]_trv" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( " ENTIRE   DEF" ) );

    output << p1788::io::decimal;
    output << p1788::io::string_width(11);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "ENTIRE  DAC" ) );

    output << p1788::io::hex;
    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[entire]_trv" ) );

    output << p1788::io::dec_numeric;
    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_no_bounds;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[,]_8" ) );

    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[,]_4" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(9);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[  ,  ]_8" ) );

    output << p1788::io::hex;
    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "ENTIRE 12" ) );

    output << p1788::io::dec_alpha;
    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_bounds;
    output << p1788::io::punctuation;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[-inf,inf]_trv" ) );

    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[-INF,INF]_DAC" ) );

    output << p1788::io::hex;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(6);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[-inf,inf]_trv" ) );

    output << p1788::io::string_width(15);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[-inf, inf]_def" ) );

    output << p1788::io::decimal;
    output << p1788::io::string_width(16);
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[ -INF, INF]_DAC" ) );

    output << p1788::io::string_width(17);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[ -INF,  INF]_TRV" ) );

    output << p1788::io::hex;
    output << p1788::io::string_width(18);
    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[  -inf,  inf]_def" ) );

    output << p1788::io::decimal;
    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "   -INF    INF TRV" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "-INF INF DAC" ) );

    output << p1788::io::lower_case;
    output << p1788::io::special_text;
    output << p1788::io::punctuation;
    output << p1788::io::inf_sup_form;
    output << p1788::io::width(10);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[        entire       ]_trv" ) );

    output << p1788::io::special_bounds;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[      -inf,       inf]_def" ) );

    output << p1788::io::string_width(27);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[      -inf,       inf]_dac" ) );

    output << p1788::io::string_width(29);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[       -inf,        inf]_trv" ) );

    output << p1788::io::special_no_bounds;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[           ,           ]_def" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[          ,          ]_dac" ) );

    output << p1788::io::special_bounds;
    output << p1788::io::precision(27);
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[      -INF,       INF]_TRV" ) );
}


BOOST_AUTO_TEST_CASE(minimal_nai_output_test)
{
    boost::test_tools::output_test_stream output;


    F<double>::operator_interval_to_text(output, F<double>::nai());
    BOOST_CHECK( output.is_equal( "[nai]" ) );

    output << p1788::io::hex;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, F<double>::nai());
    BOOST_CHECK( output.is_equal( "[NAI]" ) );

    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(12);
    F<double>::operator_interval_to_text(output, F<double>::nai());
    BOOST_CHECK( output.is_equal( "[   nai    ]" ) );

    output << p1788::io::dec_numeric;
    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    output << p1788::io::hex;
    F<double>::operator_interval_to_text(output, F<double>::nai());
    BOOST_CHECK( output.is_equal( "    NAI     " ) );

    output << p1788::io::string_width(11);
    output << p1788::io::decimal;
    F<double>::operator_interval_to_text(output, F<double>::nai());
    BOOST_CHECK( output.is_equal( "    NAI    " ) );

    output << p1788::io::dec_alpha;
    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, F<double>::nai());
    BOOST_CHECK( output.is_equal( "[   nai   ]" ) );

    output << p1788::io::upper_case;
    output << p1788::io::special_text;
    output << p1788::io::no_punctuation;
    output << p1788::io::inf_sup_form;
    output << p1788::io::punctuation;
    output << p1788::io::width(10);
    F<double>::operator_interval_to_text(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[         NAI         ]" ) );

    output << p1788::io::special_bounds;
    F<double>::operator_interval_to_text(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[         NAI         ]" ) );

    output << p1788::io::string_width(23);
    F<double>::operator_interval_to_text(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[         NAI         ]" ) );

    output << p1788::io::string_width(25);
    F<double>::operator_interval_to_text(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[          NAI          ]" ) );

    output << p1788::io::special_no_bounds;
    F<double>::operator_interval_to_text(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[          NAI          ]" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_interval_to_text(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[         NAI         ]" ) );

    output << p1788::io::special_bounds;
    output << p1788::io::precision(27);
    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[         nai         ]" ) );
}



BOOST_AUTO_TEST_CASE(minimal_bare_interval_output_test)
{
    boost::test_tools::output_test_stream output;

    F<double>::operator_interval_to_text(output, REP<double>(0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[0.1,0.100001]" ) );

    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP<double>(-0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[-0.100001,0.100001]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(22);
    F<double>::operator_interval_to_text(output, REP<double>(-0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[ -0.100001, 0.100001]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP<double>(-0.1,0.1) );
    BOOST_CHECK( output.is_equal( "  -0.100001   0.100001" ) );

    output << p1788::io::hex;
    output << p1788::io::string_width(0);
    F<double>::operator_interval_to_text(output, REP<double>(-0.1,1.3) );
    BOOST_CHECK( output.is_equal( "-0X1.999999999999AP-4 0X1.4CCCCCCCCCCCDP+0" ) );

    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    output << p1788::io::precision(5);
    output << p1788::io::width(15);
    F<double>::operator_interval_to_text(output, REP<double>(-0.1,1.3) );
    BOOST_CHECK( output.is_equal( "[  -0x1.9999ap-4,   0x1.4cccdp+0]" ) );

    output << p1788::io::string_width(35);
    output << p1788::io::special_no_bounds;
    F<double>::operator_interval_to_text(output, REP<double>(0.1,1.3) );
    BOOST_CHECK( output.is_equal( "[    0x1.99999p-4,    0x1.4cccdp+0]" ) );

    output << p1788::io::string_width(0);
    output << p1788::io::precision(20);
    F<double>::operator_interval_to_text(output, REP<double>(0.1,1.3) );
    BOOST_CHECK( output.is_equal( "[0x1.999999999999a0000000p-4,0x1.4cccccccccccd0000000p+0]" ) );

    output << p1788::io::decimal;
    output << p1788::io::precision(0);
    output << p1788::io::width(10);
    F<double>::operator_interval_to_text(output, REP<double>(0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[  0.100000,  0.100001]" ) );

    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP<double>(-0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[ -0.100001,  0.100001]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(25);
    output << p1788::io::precision(7);
    F<double>::operator_interval_to_text(output, REP<double>(0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[  0.1000000,  0.1000001]" ) );

    output << p1788::io::decimal_scientific;
    output << p1788::io::string_width(0);
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP<double>(0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[       0.1, 0.1000001]" ) );

    output << p1788::io::scientific;
    F<double>::operator_interval_to_text(output, REP<double>(0.1,1.3) );
    BOOST_CHECK( output.is_equal( "[1.0000000E-01,1.3000001E+00]" ) );

    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, REP<double>(-INF_D,0.1) );
    BOOST_CHECK( output.is_equal( "[      -inf,1.0000001e-01]" ) );

    output << p1788::io::decimal_scientific;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP<double>(0.1,INF_D) );
    BOOST_CHECK( output.is_equal( "[       0.1,       INF]" ) );

    output << p1788::io::hex;
    F<double>::operator_interval_to_text(output, REP<double>(-INF_D,0.1) );
    BOOST_CHECK( output.is_equal( "[      -INF,0X1.999999AP-4]" ) );

    output << p1788::io::decimal;
    F<double>::operator_interval_to_text(output, REP<double>(0.1,INF_D) );
    BOOST_CHECK( output.is_equal( "[ 0.1000000,       INF]" ) );

}



BOOST_AUTO_TEST_CASE(minimal_decorated_interval_output_test)
{
    boost::test_tools::output_test_stream output;

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1,0.1), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[0.1,0.100001]_trv" ) );

    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-0.1,0.1), DEC::def) );
    BOOST_CHECK( output.is_equal( "[-0.100001,0.100001]_DEF" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(26);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-0.1,0.1), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[ -0.100001, 0.100001]_dac" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-0.1,0.1), DEC::com) );
    BOOST_CHECK( output.is_equal( "  -0.100001   0.100001 COM" ) );

    output << p1788::io::dec_numeric;
    output << p1788::io::hex;
    output << p1788::io::string_width(0);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-0.1,1.3), DEC::trv) );
    BOOST_CHECK( output.is_equal( "-0X1.999999999999AP-4 0X1.4CCCCCCCCCCCDP+0 4" ) );

    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    output << p1788::io::precision(5);
    output << p1788::io::width(15);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-0.1,1.3), DEC::def) );
    BOOST_CHECK( output.is_equal( "[  -0x1.9999ap-4,   0x1.4cccdp+0]_8" ) );

    output << p1788::io::string_width(35);
    output << p1788::io::special_no_bounds;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1,1.3), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[   0x1.99999p-4,   0x1.4cccdp+0]_12" ) );

    output << p1788::io::string_width(0);
    output << p1788::io::precision(20);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1,1.3), DEC::com) );
    BOOST_CHECK( output.is_equal( "[0x1.999999999999a0000000p-4,0x1.4cccccccccccd0000000p+0]_16" ) );

    output << p1788::io::decimal;
    output << p1788::io::precision(0);
    output << p1788::io::width(10);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1,0.1), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[  0.100000,  0.100001]_4" ) );

    output << p1788::io::dec_alpha;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-0.1,0.1), DEC::def) );
    BOOST_CHECK( output.is_equal( "[ -0.100001,  0.100001]_DEF" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(29);
    output << p1788::io::precision(7);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1,0.1), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[  0.1000000,  0.1000001]_dac" ) );

    output << p1788::io::decimal_scientific;
    output << p1788::io::string_width(0);
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1,0.1), DEC::com) );
    BOOST_CHECK( output.is_equal( "[       0.1, 0.1000001]_COM" ) );

    output << p1788::io::scientific;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1,1.3), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[1.0000000E-01,1.3000001E+00]_TRV" ) );

    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,0.1), DEC::def) );
    BOOST_CHECK( output.is_equal( "[      -inf,1.0000001e-01]_def" ) );

    output << p1788::io::decimal_scientific;
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[       0.1,       INF]_DAC" ) );

    output << p1788::io::hex;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,0.1), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[      -INF,0X1.999999AP-4]_TRV" ) );

    output << p1788::io::decimal;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[ 0.1000000,       INF]_DEF" ) );

}


BOOST_AUTO_TEST_CASE(minimal_uncertain_interval_output_test)
{
    boost::test_tools::output_test_stream output;

    output << p1788::io::uncertain_form;

    F<double>::operator_interval_to_text(output, REP<double>(-INF_D,INF_D) );
    BOOST_CHECK( output.is_equal( "0.000000??" ) );

    F<double>::operator_interval_to_text(output, REP<double>(0.1,INF_D) );
    BOOST_CHECK( output.is_equal( "0.100000??u" ) );

    F<double>::operator_interval_to_text(output, REP<double>(-INF_D,0.1) );
    BOOST_CHECK( output.is_equal( "0.100001??d" ) );

    output << p1788::io::uncertain_exponent;
    F<double>::operator_interval_to_text(output, REP<double>(-INF_D,INF_D) );
    BOOST_CHECK( output.is_equal( "0.000000??e+00" ) );

    F<double>::operator_interval_to_text(output, REP<double>(0.1,INF_D) );
    BOOST_CHECK( output.is_equal( "1.000000??ue-01" ) );

    F<double>::operator_interval_to_text(output, REP<double>(-INF_D,0.1) );
    BOOST_CHECK( output.is_equal( "1.000001??de-01" ) );

    output << p1788::io::precision(1);
    output << p1788::io::string_width(20);
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP<double>(-INF_D,INF_D) );
    BOOST_CHECK( output.is_equal( "           0.0??E+00" ) );

    F<double>::operator_interval_to_text(output, REP<double>(0.1,INF_D) );
    BOOST_CHECK( output.is_equal( "          1.0??UE-01" ) );

    F<double>::operator_interval_to_text(output, REP<double>(-INF_D,0.1) );
    BOOST_CHECK( output.is_equal( "          1.1??DE-01" ) );

    output << p1788::io::no_uncertain_exponent;
    output << p1788::io::no_punctuation;
    F<double>::operator_interval_to_text(output, REP<double>(-INF_D,INF_D) );
    BOOST_CHECK( output.is_equal( "               0.0??" ) );

    F<double>::operator_interval_to_text(output, REP<double>(0.1,INF_D) );
    BOOST_CHECK( output.is_equal( "              0.1??U" ) );

    F<double>::operator_interval_to_text(output, REP<double>(-INF_D,0.1) );
    BOOST_CHECK( output.is_equal( "              0.2??D" ) );


    output << p1788::io::precision(5);
    output << p1788::io::string_width(0);
    output << p1788::io::lower_case;
    F<double>::operator_interval_to_text(output, REP<double>(0.1, 0.2) );
    BOOST_CHECK( output.is_equal( "0.15000?5001" ) );

    output << p1788::io::uncertain_down_form;
    output << p1788::io::precision(7);
    F<double>::operator_interval_to_text(output, REP<double>(0.1, 0.2) );
    BOOST_CHECK( output.is_equal( "0.2000001?1000001d" ) );

    output << p1788::io::uncertain_up_form;
    output << p1788::io::precision(0);
    output << p1788::io::string_width(18);
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP<double>(-0.1, 0.2) );
    BOOST_CHECK( output.is_equal( " -0.100001?300002U" ) );


    output << p1788::io::precision(0);
    output << p1788::io::string_width(0);
    output << p1788::io::lower_case;
    output << p1788::io::uncertain_exponent;
    F<double>::operator_interval_to_text(output, REP<double>(-100, 0.2) );
    BOOST_CHECK( output.is_equal( "-1.000000?1002001ue+02" ) );

    F<double>::operator_interval_to_text(output, REP<double>(-100, 0.0) );
    BOOST_CHECK( output.is_equal( "-1.000000?1000000ue+02" ) );

    F<double>::operator_interval_to_text(output, REP<double>(-100, -0.2) );
    BOOST_CHECK( output.is_equal( "-1.000000?998000ue+02" ) );

    F<double>::operator_interval_to_text(output, REP<double>(-0.2, 100) );
    BOOST_CHECK( output.is_equal( "-2.000001?1002000001ue-01" ) );

    F<double>::operator_interval_to_text(output, REP<double>(0.0,100) );
    BOOST_CHECK( output.is_equal( "0.000000?100000000ue+00" ) );

    F<double>::operator_interval_to_text(output, REP<double>(0.2, 100) );
    BOOST_CHECK( output.is_equal( "2.000000?998000000ue-01" ) );


    output << p1788::io::uncertain_down_form;
    F<double>::operator_interval_to_text(output, REP<double>(-0.2, 100) );
    BOOST_CHECK( output.is_equal( "1.000000?1002001de+02" ) );

    F<double>::operator_interval_to_text(output, REP<double>(0.0,100) );
    BOOST_CHECK( output.is_equal( "1.000000?1000000de+02" ) );

    F<double>::operator_interval_to_text(output, REP<double>(0.2, 100) );
    BOOST_CHECK( output.is_equal( "1.000000?998000de+02" ) );

    F<double>::operator_interval_to_text(output, REP<double>(-100, 0.2) );
    BOOST_CHECK( output.is_equal( "2.000001?1002000001de-01" ) );

    F<double>::operator_interval_to_text(output, REP<double>(-100, 0.0) );
    BOOST_CHECK( output.is_equal( "0.000000?100000000de+00" ) );

    F<double>::operator_interval_to_text(output, REP<double>(-100, -0.2) );
    BOOST_CHECK( output.is_equal( "-2.000000?998000000de-01" ) );

    output << p1788::io::uncertain_form;

    F<double>::operator_interval_to_text(output, REP<double>(-0.2, 100) );
    BOOST_CHECK( output.is_equal( "4.990000?5010001e+01" ) );

    F<double>::operator_interval_to_text(output, REP<double>(0.0,100) );
    BOOST_CHECK( output.is_equal( "5.000000?5000000e+01" ) );

    F<double>::operator_interval_to_text(output, REP<double>(0.2, 100) );
    BOOST_CHECK( output.is_equal( "5.010000?4990000e+01" ) );

    F<double>::operator_interval_to_text(output, REP<double>(-100, 0.2) );
    BOOST_CHECK( output.is_equal( "-4.990000?5010001e+01" ) );

    F<double>::operator_interval_to_text(output, REP<double>(-100, 0.0) );
    BOOST_CHECK( output.is_equal( "-5.000000?5000000e+01" ) );

    F<double>::operator_interval_to_text(output, REP<double>(-100, -0.2) );
    BOOST_CHECK( output.is_equal( "-5.010000?4990000e+01" ) );

    output << p1788::io::uncertain_form;
    output << p1788::io::upper_case;
    output << p1788::io::special_bounds;
    output << p1788::io::no_punctuation;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "INF -INF" ) );

    output << p1788::io::special_text;
    output << p1788::io::punctuation;
    F<double>::operator_interval_to_text(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[EMPTY]" ) );
}



BOOST_AUTO_TEST_CASE(minimal_uncertain_interval_dec_output_test)
{
    boost::test_tools::output_test_stream output;

    output << p1788::io::uncertain_form;


    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "0.000000??_trv" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "0.100000??u_def" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,0.1), DEC::dac) );
    BOOST_CHECK( output.is_equal( "0.100001??d_dac" ) );

    output << p1788::io::uncertain_exponent;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "0.000000??e+00_trv" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "1.000000??ue-01_def" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,0.1), DEC::dac) );
    BOOST_CHECK( output.is_equal( "1.000001??de-01_dac" ) );

    output << p1788::io::precision(1);
    output << p1788::io::string_width(20);
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "       0.0??E+00_TRV" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "      1.0??UE-01_DEF" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,0.1), DEC::dac) );
    BOOST_CHECK( output.is_equal( "      1.1??DE-01_DAC" ) );

    output << p1788::io::no_uncertain_exponent;
    output << p1788::io::no_punctuation;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "           0.0?? TRV" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "          0.1??U DEF" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-INF_D,0.1), DEC::dac) );
    BOOST_CHECK( output.is_equal( "          0.2??D DAC" ) );


    output << p1788::io::precision(5);
    output << p1788::io::string_width(0);
    output << p1788::io::lower_case;
    output << p1788::io::dec_numeric;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1, 0.2), DEC::trv) );
    BOOST_CHECK( output.is_equal( "0.15000?5001 4" ) );

    output << p1788::io::uncertain_down_form;
    output << p1788::io::precision(7);
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.1, 0.2), DEC::def) );
    BOOST_CHECK( output.is_equal( "0.2000001?1000001d 8" ) );

    output << p1788::io::uncertain_up_form;
    output << p1788::io::precision(0);
    output << p1788::io::string_width(21);
    output << p1788::io::upper_case;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-0.1, 0.2), DEC::dac) );
    BOOST_CHECK( output.is_equal( " -0.100001?300002U 12" ) );


    output << p1788::io::precision(0);
    output << p1788::io::string_width(0);
    output << p1788::io::lower_case;
    output << p1788::io::uncertain_exponent;
    output << p1788::io::punctuation;
    output << p1788::io::dec_alpha;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-100, 0.2), DEC::com) );
    BOOST_CHECK( output.is_equal( "-1.000000?1002001ue+02_com" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-100, 0.0), DEC::trv) );
    BOOST_CHECK( output.is_equal( "-1.000000?1000000ue+02_trv" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-100, -0.2), DEC::def) );
    BOOST_CHECK( output.is_equal( "-1.000000?998000ue+02_def" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-0.2, 100), DEC::dac) );
    BOOST_CHECK( output.is_equal( "-2.000001?1002000001ue-01_dac" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.0,100), DEC::com) );
    BOOST_CHECK( output.is_equal( "0.000000?100000000ue+00_com" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.2, 100), DEC::trv) );
    BOOST_CHECK( output.is_equal( "2.000000?998000000ue-01_trv" ) );


    output << p1788::io::uncertain_down_form;
    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-0.2, 100), DEC::def) );
    BOOST_CHECK( output.is_equal( "1.000000?1002001de+02_def" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.0,100), DEC::dac) );
    BOOST_CHECK( output.is_equal( "1.000000?1000000de+02_dac" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.2, 100), DEC::com) );
    BOOST_CHECK( output.is_equal( "1.000000?998000de+02_com" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-100, 0.2), DEC::trv) );
    BOOST_CHECK( output.is_equal( "2.000001?1002000001de-01_trv" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-100, 0.0), DEC::def) );
    BOOST_CHECK( output.is_equal( "0.000000?100000000de+00_def" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-100, -0.2), DEC::dac) );
    BOOST_CHECK( output.is_equal( "-2.000000?998000000de-01_dac" ) );

    output << p1788::io::uncertain_form;

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-0.2, 100), DEC::com) );
    BOOST_CHECK( output.is_equal( "4.990000?5010001e+01_com" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.0,100), DEC::trv) );
    BOOST_CHECK( output.is_equal( "5.000000?5000000e+01_trv" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(0.2, 100), DEC::def) );
    BOOST_CHECK( output.is_equal( "5.010000?4990000e+01_def" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-100, 0.2), DEC::dac) );
    BOOST_CHECK( output.is_equal( "-4.990000?5010001e+01_dac" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-100, 0.0), DEC::com) );
    BOOST_CHECK( output.is_equal( "-5.000000?5000000e+01_com" ) );

    F<double>::operator_interval_to_text(output, REP_DEC<double>(REP<double>(-100, -0.2), DEC::trv) );
    BOOST_CHECK( output.is_equal( "-5.010000?4990000e+01_trv" ) );

    output << p1788::io::special_bounds;
    output << p1788::io::no_punctuation;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "inf -inf" ) );

    output << p1788::io::hex;
    output << p1788::io::special_text;
    output << p1788::io::punctuation;
    F<double>::operator_interval_to_text(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[empty]" ) );

    F<double>::operator_interval_to_text(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[nai]" ) );

    output << p1788::io::upper_case;
    output << p1788::io::no_punctuation;
    F<double>::operator_interval_to_text(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "NAI" ) );
}



BOOST_AUTO_TEST_CASE(minimal_decorated_interval_input_test)
{
    {
        REP_DEC<double> di;
        std::istringstream is("[ Nai  ]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK( F<double>::is_nai(di) );
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[ Nai  ]_ill");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[ Nai  ]_trv");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[ Empty  ]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK( F<double>::is_empty(di) );
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[ Empty  ]_trv");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK( F<double>::is_empty(di) );
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[ Empty  ]_ill");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[  ]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK( F<double>::is_empty(di) );
        BOOST_CHECK(is);
    }


    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[  ]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[  ]_trv");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK( F<double>::is_empty(di) );
        BOOST_CHECK(is);
    }


    {
        REP_DEC<double> di;
        std::istringstream is("[,]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, F<double>::entire_dec());
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[,]_trv");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::trv));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[,]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[ entire  ]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, F<double>::entire_dec());
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[ ENTIRE ]_dac");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::dac));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[   Entire ]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[ -inf , INF  ]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, F<double>::entire_dec());
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[ -inf, INF ]_def");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::def));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[ -inf ,  INF ]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[-1.0,1.0]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-1.0,1.0),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[  -1.0  ,  1.0  ]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-1.0,1.0),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[  -1.0  , 1.0]_trv");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-1.0,1.0),DEC::trv));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[  -1.0  , 1.0]_ill");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[  -1.0  , 1.0]_fooo");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[  -1.0  , 1.0]_da c");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[  -1.0  , 1.0]_da");
        is.exceptions(is.eofbit);
        BOOST_CHECK_THROW(F<double>::operator_text_to_interval(is, di), std::ios_base::failure);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[-1,]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-1.0,INF_D),DEC::dac));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[-1.0, +inf]_def");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-1.0,INF_D),DEC::def));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[-1.0, +infinity]_def");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-1.0,INF_D),DEC::def));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[-1.0,]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[-Inf, 1.000 ]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-INF_D,1.0),DEC::dac));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[-Infinity, 1.000 ]_trv");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-INF_D,1.0),DEC::trv));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-15.0,27.0),DEC::trv);
        std::istringstream is("[-Inf, 1.000 ]_ill");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-15.0,27.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[1.0E+400 ]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(MAX_D,INF_D),DEC::dac));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[1.0000000000000002E+6000 ]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(MAX_D,INF_D),DEC::dac));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[-1.0000000000000002E+6000 ]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-INF_D,-MAX_D),DEC::dac));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[10000000000000002]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(10000000000000002,10000000000000002),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[-10000000000000002]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-10000000000000002,-10000000000000002),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[-1.0000000000000002E+6000, 1.0000000000000001E+6000]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::dac));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[ -4/2, 10/5 ]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-2.0,2.0),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("[ -1/10, 1/10 ]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-0.1,0.1),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[ 1/-10, 1/10 ]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[ 1/10, 1/+10 ]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[ 1/0, 1/10 ]_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[-I  nf, 1.000 ]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[-Inf, 1.0  00 ]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,12.0),DEC::trv);
        std::istringstream is("[-Inf ]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,12.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[1.0,-1.0]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[-1.0,1.0");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("-1.0,1.0]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[1.0");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("-1.0]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }


    {
        REP_DEC<double> di(REP<double>(-1.0,2.0),DEC::trv);
        std::istringstream is("[Inf , INF]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,2.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[ foo ]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,5.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[1.0000000000000002,1.0000000000000001]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,5.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[1.0000000000000002E+6000,1.0000000000000001E+6000]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,5.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[10000000000000001/10000000000000000,10000000000000002/10000000000000001]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,5.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[0x1.00000000000001p0,0x1.00000000000002p0]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(std::stod("0x1.0p0"),std::stod("0x1.0000000000001p0")),DEC::com) );
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[-0x1.00000000000001p0,0x1.00000000000002p0]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(std::stod("-0x1.0000000000001p0"),std::stod("0x1.0000000000001p0")),DEC::com) );
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[0x1.00000000000001,0x1.00000000000002p0]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,5.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[0x1.00000000000001p0,0x1.00000000000002]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,5.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[0x1.00000000000001,0x1.00000000000002]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,5.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[0x1.00000000000001p0]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(std::stod("0x1.0p0"),std::stod("0x1.0000000000001p0")),DEC::com) );
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[-0x1.00000000000001p0]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(std::stod("-0x1.0000000000001p0"),std::stod("-0x1.0p0")),DEC::com) );
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[0x1.00000000000001]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,5.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[0x1.00000000000001]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,5.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[0x1.00000000000002p0,0x1.00000000000001p0]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,5.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[-0x1.00000000000001p0,-0x1.00000000000002p0]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(-1.0,5.0),DEC::trv) );
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[-0x1.00000000000001p0, 10/5]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(std::stod("-0x1.0000000000001p0"), 2.0),DEC::com) );
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-1.0,5.0),DEC::trv);
        std::istringstream is("[0x1.00000000000001p0, 2.5]");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL( di, REP_DEC<double>(REP<double>(1.0, 2.5),DEC::com) );
        BOOST_CHECK(is);
    }

}


BOOST_AUTO_TEST_CASE(minimal_interval_input_test)
{
    {
        REP<double> i;
        std::istringstream is("[ Empty  ]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK( F<double>::is_empty(i) );
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("[ Empty  ]_trv");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK( F<double>::is_empty(i) );
        BOOST_CHECK(is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[ Empty  ]_ill");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i;
        std::istringstream is("[  ]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK( F<double>::is_empty(i) );
        BOOST_CHECK(is);
    }


    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[  ]_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i;
        std::istringstream is("[  ]_trv");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK( F<double>::is_empty(i) );
        BOOST_CHECK(is);
    }


    {
        REP<double> i;
        std::istringstream is("[,]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, F<double>::entire());
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("[,]_trv");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, F<double>::entire());
        BOOST_CHECK(is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[,]_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i;
        std::istringstream is("[ entire  ]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, F<double>::entire());
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("[ ENTIRE ]_dac");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, F<double>::entire());
        BOOST_CHECK(is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[   Entire ]_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i;
        std::istringstream is("[ -inf , INF  ]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, F<double>::entire());
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("[ -inf, INF ]_def");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, F<double>::entire());
        BOOST_CHECK(is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[ -inf ,  INF ]_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }


    {
        REP<double> i;
        std::istringstream is("[-1.0,1]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-1.0,1.0));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("[  -1.0  ,  1.0  ]_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-1.0,1.0));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("[  -1.0  , 1.0]_trv");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-1.0,1.0));
        BOOST_CHECK(is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[  -1.0  , 1.0]_ill");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[  -1.0  , 1.0]_fooo");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[  -1.0  , 1.0]_da c");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }


    {
        REP<double> i;
        std::istringstream is("[-1.0,]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-1.0,INF_D));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("[-1.0, +inf]_def");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-1.0,INF_D));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("[-1.0, +infinity]_def");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-1.0,INF_D));
        BOOST_CHECK(is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[-1.0,]_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i;
        std::istringstream is("[-Inf, 1.000 ]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-INF_D,1.0));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("[-Infinity, 1.000 ]_trv");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-INF_D,1.0));
        BOOST_CHECK(is);
    }

    {
        REP<double> i(-35.0,-0.7);
        std::istringstream is("[-Inf, 1.000 ]_ill");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(-35.0,-0.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i;
        std::istringstream is("[ 0.1 ]_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(std::stod("0x1.9999999999999p-4"),std::stod("0x1.999999999999ap-4")));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("[ 1/10 ]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(std::stod("0x1.9999999999999p-4"),std::stod("0x1.999999999999ap-4")));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("[1.0E+400 ]_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(MAX_D,INF_D));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("[ -4/2, 10/5 ]_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-2.0,2.0));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("[ -1/10, 1/10 ]_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-0.1,0.1));
        BOOST_CHECK(is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[ 1/-10, 1/10 ]_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(3.5,45.7);
        std::istringstream is("1.0, 1.000]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,45.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(3.5,45.7);
        std::istringstream is("[1.0, 1.000");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,45.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(3.5,45.7);
        std::istringstream is("1.000]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,45.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(3.5,45.7);
        std::istringstream is("[1.0");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,45.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(3.5,45.7);
        std::istringstream is("[-I  nf, 1.000 ]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,45.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(35.0,45.7);
        std::istringstream is("[-Inf, 1.0  00 ]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(35.0,45.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(-1.0,2.0);
        std::istringstream is("[1.0,-1.0]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(-1.0,2.0) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(-0.5,4.7);
        std::istringstream is("[-Inf ]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(-0.5,4.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[Inf , INF]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[ foo ]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[1.0000000000000002,1.0000000000000001]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[10000000000000001/10000000000000000,10000000000000002/10000000000000001]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(3.5,4.7);
        std::istringstream is("[0x1.00000000000002p0,0x1.00000000000001p0]");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(3.5,4.7) );
        BOOST_CHECK(!is);
    }
}


BOOST_AUTO_TEST_CASE(minimal_uncertain_interval_dec_input_test)
{
    {
        REP_DEC<double> di;
        std::istringstream is("0.0?");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-0.05,0.05),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("0.0?u_trv");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(0.0,0.05),DEC::trv));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("0.0?d_dac");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-0.05,0.0),DEC::dac));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("2.5?");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(std::stod("0x1.3999999999999p+1"),std::stod("0x1.4666666666667p+1")),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("2.5?u");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(2.5,std::stod("0x1.4666666666667p+1")),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("2.5?d_trv");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(std::stod("0x1.3999999999999p+1"),2.5),DEC::trv));
        BOOST_CHECK(is);
    }


    {
        REP_DEC<double> di;
        std::istringstream is("0.000?5");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-0.005,0.005),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("0.000?5u_def");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(0.0,0.005),DEC::def));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("0.000?5d");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-0.005,0.0),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("2.500?5");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(std::stod("0x1.3f5c28f5c28f5p+1"),std::stod("0x1.40a3d70a3d70bp+1")),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("2.500?5u");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(2.5,std::stod("0x1.40a3d70a3d70bp+1")),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("2.500?5d");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(std::stod("0x1.3f5c28f5c28f5p+1"),2.5),DEC::com));
        BOOST_CHECK(is);
    }


    {
        REP_DEC<double> di;
        std::istringstream is("0.0??_dac");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::dac));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("0.0??u_trv");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(0.0,INF_D),DEC::trv));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("0.0??d");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-INF_D,0.0),DEC::dac));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("5?");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(4.5,5.5),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("5?d");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(4.5,5.0),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("5?u");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(5.0,5.5),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("-5?");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-5.5,-4.5),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("-5?d");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-5.5,-5.0),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("-5?u");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-5.0,-4.5),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("2.5??");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::dac));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("2.5??u_def");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(2.5,INF_D),DEC::def));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("2.5??d_dac");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-INF_D,2.5),DEC::dac));
        BOOST_CHECK(is);
    }


    {
        REP_DEC<double> di;
        std::istringstream is("2.500?5e+27");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(std::stod("0x1.01fa19a08fe7fp+91"),std::stod("0x1.0302cc4352683p+91")),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("2.500?5ue4_def");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(std::stod("0x1.86ap+14"),std::stod("0x1.8768p+14")),DEC::def));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("2.500?5de-5");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(std::stod("0x1.a2976f1cee4d5p-16"),std::stod("0x1.a36e2eb1c432dp-16")),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::string rep = "10?18";
        rep += std::string(308, '0');
        rep += "_com";
        std::stringstream is(rep);
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-INF_D,INF_D),DEC::dac));
        BOOST_CHECK(is);
    }


    {
        REP_DEC<double> di;
        std::istringstream is("10?3_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(7.0,13.0),DEC::com));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di;
        std::istringstream is("10?3e380_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(MAX_D,INF_D),DEC::dac));
        BOOST_CHECK(is);
    }

    {
        REP_DEC<double> di(REP<double>(-3.3,10.01),DEC::com);
        std::istringstream is("5");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-3.3,10.01),DEC::com));
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-3.7,0.01),DEC::def);
        std::istringstream is("0.0??_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-3.7,0.01),DEC::def));
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(3.7,12.4),DEC::trv);
        std::istringstream is("0.0??u_ill");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(3.7,12.4),DEC::trv));
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-3.3,10.01),DEC::com);
        std::istringstream is("0.0??d_com");
        F<double>::operator_text_to_interval(is, di);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-3.3,10.01),DEC::com));
        BOOST_CHECK(!is);
    }

    {
        REP_DEC<double> di(REP<double>(-3.3,10.01),DEC::com);
        std::istringstream is("0.0?22d_cm");
        is.exceptions(is.eofbit);
        BOOST_CHECK_THROW(F<double>::operator_text_to_interval(is, di), std::ios_base::failure);
        BOOST_CHECK_EQUAL(di, REP_DEC<double>(REP<double>(-3.3,10.01),DEC::com));
        BOOST_CHECK(!is);
    }
}




BOOST_AUTO_TEST_CASE(minimal_uncertain_interval_input_test)
{
    {
        REP<double> i;
        std::istringstream is("0.0?");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-0.05,0.05));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("0.0?u_trv");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(0.0,0.05));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("0.0?d_dac");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-0.05,0.0));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("2.5?");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(std::stod("0x1.3999999999999p+1"),std::stod("0x1.4666666666667p+1")));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("2.5?u");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(2.5,std::stod("0x1.4666666666667p+1")));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("2.5?d_trv");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(std::stod("0x1.3999999999999p+1"),2.5));
        BOOST_CHECK(is);
    }


    {
        REP<double> i;
        std::istringstream is("0.000?5");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-0.005,0.005));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("0.000?5u_def");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(0.0,0.005));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("0.000?5d");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-0.005,0.0));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("2.500?5");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(std::stod("0x1.3f5c28f5c28f5p+1"),std::stod("0x1.40a3d70a3d70bp+1")));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("2.500?5u");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(2.5,std::stod("0x1.40a3d70a3d70bp+1")));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("2.500?5d");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(std::stod("0x1.3f5c28f5c28f5p+1"),2.5));
        BOOST_CHECK(is);
    }


    {
        REP<double> i;
        std::istringstream is("0.0??_dac");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-INF_D,INF_D));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("0.0??u_trv");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(0.0,INF_D));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("0.0??d");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-INF_D,0.0));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("2.5??");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-INF_D,INF_D));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("2.5??u_def");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(2.5,INF_D));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("2.5??d_dac");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-INF_D,2.5));
        BOOST_CHECK(is);
    }


    {
        REP<double> i;
        std::istringstream is("2.500?5e+27");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(std::stod("0x1.01fa19a08fe7fp+91"),std::stod("0x1.0302cc4352683p+91")));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("2.500?5ue4_def");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(std::stod("0x1.86ap+14"),std::stod("0x1.8768p+14")));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("2.500?5de-5");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(std::stod("0x1.a2976f1cee4d5p-16"),std::stod("0x1.a36e2eb1c432dp-16")));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::string rep = "10?18";
        rep += std::string(308, '0');
        rep += "_com";
        std::stringstream is(rep);
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(-INF_D,INF_D));
        BOOST_CHECK(is);
    }


    {
        REP<double> i;
        std::istringstream is("10?3_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(7.0,13.0));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("10?3e380_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(MAX_D,INF_D));
        BOOST_CHECK(is);
    }

    {
        REP<double> i;
        std::istringstream is("1.0000000000000001?1");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(1.0,std::stod("0x1.0000000000001p+0")));
        BOOST_CHECK(is);
    }

    {
        REP<double> i(2.0,3.0);
        std::istringstream is("12");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL(i, REP<double>(2.0,3.0));
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(2.0,3.0);
        std::istringstream is("0.0??_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(2.0,3.0) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(2.5,3.4);
        std::istringstream is("0.0??u_ill");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(2.5,3.4) );
        BOOST_CHECK(!is);
    }

    {
        REP<double> i(-2.0,-1.0);
        std::istringstream is("0.0??d_com");
        F<double>::operator_text_to_interval(is, i);
        BOOST_CHECK_EQUAL( i, REP<double>(-2.0,-1.0) );
        BOOST_CHECK(!is);
    }
}
