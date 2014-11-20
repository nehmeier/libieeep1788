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

#define BOOST_TEST_MODULE "Flavor: IO [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"
#include "p1788/infsup/base_interval.hpp"

#include <boost/test/output_test_stream.hpp>

#include <limits>

template<typename T>
using F = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>;

template<typename T>
using REP = typename F<T>::representation;

template<typename T>
using REP_DEC = typename F<T>::representation_dec;

typedef p1788::decoration::decoration DEC;

const double INF_D = std::numeric_limits<double>::infinity();


BOOST_AUTO_TEST_CASE(minimal_empty_output_test)
{
    boost::test_tools::output_test_stream output;

    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[empty]" ) );


    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[EMPTY]" ) );

    output << p1788::io::hex;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(12);
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[  empty   ]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "   EMPTY    " ) );

    output << p1788::io::string_width(11);
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "   EMPTY   " ) );

    output << p1788::io::decimal;
    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[  empty  ]" ) );

    output << p1788::io::dec_numeric;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_no_bounds;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[ ]" ) );

    output << p1788::io::hex;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[ ]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(9);
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[       ]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "  EMPTY  " ) );

    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_bounds;
    output << p1788::io::punctuation;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[inf,-inf]" ) );

    output << p1788::io::dec_alpha;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[INF,-INF]" ) );

    output << p1788::io::hex;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(9);
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[inf,-inf]" ) );

    output << p1788::io::string_width(15);
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[  inf,   -inf]" ) );

    output << p1788::io::string_width(16);
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[   inf,   -inf]" ) );

    output << p1788::io::decimal;
    output << p1788::io::string_width(17);
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[   INF,    -INF]" ) );

    output << p1788::io::string_width(18);
    output << p1788::io::lower_case;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[    inf,    -inf]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "     INF      -INF" ) );

    output << p1788::io::hex;
    output << p1788::io::upper_case;
    output << p1788::io::string_width(0);
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "INF -INF" ) );

    output << p1788::io::uncertain_form;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "INF -INF" ) );

    output << p1788::io::decimal;
    output << p1788::io::special_text;
    output << p1788::io::punctuation;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[EMPTY]" ) );

    output << p1788::io::inf_sup_form;
    output << p1788::io::width(10);
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[        EMPTY        ]" ) );

    output << p1788::io::special_bounds;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[       INF,      -INF]" ) );

    output << p1788::io::string_width(23);
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[       INF,      -INF]" ) );

    output << p1788::io::string_width(25);
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[        INF,       -INF]" ) );

    output << p1788::io::special_no_bounds;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[                       ]" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[                     ]" ) );

    output << p1788::io::special_bounds;
    output << p1788::io::precision(27);
    output << p1788::io::lower_case;
    F<double>::operator_output(output, F<double>::empty());
    BOOST_CHECK( output.is_equal( "[       inf,      -inf]" ) );
}



BOOST_AUTO_TEST_CASE(minimal_empty_dec_output_test)
{
    boost::test_tools::output_test_stream output;

    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[empty]" ) );

    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[EMPTY]" ) );

    output << p1788::io::hex;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(12);
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[  empty   ]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "   EMPTY    " ) );

    output << p1788::io::string_width(11);
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "   EMPTY   " ) );

    output << p1788::io::decimal;
    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[  empty  ]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_no_bounds;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[ ]" ) );

    output << p1788::io::dec_numeric;
    output << p1788::io::hex;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[ ]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(9);
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[       ]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "  EMPTY  " ) );

    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_bounds;
    output << p1788::io::punctuation;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[inf,-inf]" ) );

    output << p1788::io::dec_alpha;
    output << p1788::io::hex;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[INF,-INF]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(9);
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[inf,-inf]" ) );

    output << p1788::io::string_width(15);
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[  inf,   -inf]" ) );

    output << p1788::io::string_width(16);
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[   inf,   -inf]" ) );

    output << p1788::io::decimal;
    output << p1788::io::string_width(17);
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[   INF,    -INF]" ) );

    output << p1788::io::hex;
    output << p1788::io::string_width(18);
    output << p1788::io::lower_case;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[    inf,    -inf]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "     INF      -INF" ) );

    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "inf -inf" ) );

    output << p1788::io::uncertain_form;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "inf -inf" ) );

    output << p1788::io::hex;
    output << p1788::io::special_text;
    output << p1788::io::punctuation;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[empty]" ) );

    output << p1788::io::inf_sup_form;
    output << p1788::io::width(10);
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[        empty        ]" ) );

    output << p1788::io::special_bounds;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[       inf,      -inf]" ) );

    output << p1788::io::string_width(23);
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[       inf,      -inf]" ) );

    output << p1788::io::string_width(25);
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[        inf,       -inf]" ) );

    output << p1788::io::special_no_bounds;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[                       ]" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[                     ]" ) );

    output << p1788::io::special_bounds;
    output << p1788::io::precision(27);
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::empty_dec());
    BOOST_CHECK( output.is_equal( "[       INF,      -INF]" ) );
}


BOOST_AUTO_TEST_CASE(minimal_entire_output_test)
{
    boost::test_tools::output_test_stream output;

    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[entire]" ) );

    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[ENTIRE]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(12);
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[  entire  ]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "   ENTIRE   " ) );

    output << p1788::io::hex;
    output << p1788::io::string_width(11);
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "  ENTIRE   " ) );

    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[ entire  ]" ) );

    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_no_bounds;
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[,]" ) );

    output << p1788::io::dec_numeric;
    output << p1788::io::hex;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[,]" ) );

    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(9);
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[   ,   ]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( " ENTIRE  " ) );

    output << p1788::io::hex;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_bounds;
    output << p1788::io::punctuation;
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[-inf,inf]" ) );

    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[-INF,INF]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(6);
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[-inf,inf]" ) );

    output << p1788::io::dec_alpha;
    output << p1788::io::decimal;
    output << p1788::io::string_width(15);
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[  -inf,   inf]" ) );

    output << p1788::io::string_width(16);
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[   -INF,   INF]" ) );

    output << p1788::io::hex;
    output << p1788::io::string_width(17);
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[   -INF,    INF]" ) );

    output << p1788::io::string_width(18);
    output << p1788::io::lower_case;
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "[    -inf,    inf]" ) );

    output << p1788::io::decimal;
    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "     -INF      INF" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "-INF INF" ) );

    output << p1788::io::hex;
    output << p1788::io::uncertain_form;
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "0.0??" ) );

    output << p1788::io::special_text;
    output << p1788::io::punctuation;
    F<double>::operator_output(output, F<double>::entire() );
    BOOST_CHECK( output.is_equal( "0.0??" ) );

    output << p1788::io::inf_sup_form;
    output << p1788::io::width(10);
    F<double>::operator_output(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[        ENTIRE       ]" ) );

    output << p1788::io::special_bounds;
    F<double>::operator_output(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[      -INF,       INF]" ) );

    output << p1788::io::string_width(23);
    F<double>::operator_output(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[      -INF,       INF]" ) );

    output << p1788::io::string_width(25);
    F<double>::operator_output(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[       -INF,        INF]" ) );

    output << p1788::io::special_no_bounds;
    F<double>::operator_output(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[           ,           ]" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_output(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[          ,          ]" ) );

    output << p1788::io::special_bounds;
    output << p1788::io::precision(27);
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::entire());
    BOOST_CHECK( output.is_equal( "[      -INF,       INF]" ) );
}

BOOST_AUTO_TEST_CASE(minimal_entire_dec_output_test)
{
    boost::test_tools::output_test_stream output;

    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[entire]_trv" ) );

    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[ENTIRE]_DAC" ) );

    output << p1788::io::hex;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(13);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[entire ]_trv" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( " ENTIRE   DEF" ) );

    output << p1788::io::decimal;
    output << p1788::io::string_width(11);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "ENTIRE  DAC" ) );

    output << p1788::io::hex;
    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[entire]_trv" ) );

    output << p1788::io::dec_numeric;
    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_no_bounds;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[,]_8" ) );

    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[,]_4" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(9);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[  ,  ]_8" ) );

    output << p1788::io::hex;
    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "ENTIRE 12" ) );

    output << p1788::io::dec_alpha;
    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(0);
    output << p1788::io::special_bounds;
    output << p1788::io::punctuation;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[-inf,inf]_trv" ) );

    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[-INF,INF]_DAC" ) );

    output << p1788::io::hex;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(6);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[-inf,inf]_trv" ) );

    output << p1788::io::string_width(15);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[-inf, inf]_def" ) );

    output << p1788::io::decimal;
    output << p1788::io::string_width(16);
    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[ -INF, INF]_DAC" ) );

    output << p1788::io::string_width(17);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[ -INF,  INF]_TRV" ) );

    output << p1788::io::hex;
    output << p1788::io::string_width(18);
    output << p1788::io::lower_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[  -inf,  inf]_def" ) );

    output << p1788::io::decimal;
    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "   -INF    INF TRV" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "-INF INF DAC" ) );

    output << p1788::io::uncertain_form;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "0.0?? TRV" ) );

    output << p1788::io::lower_case;
    output << p1788::io::special_text;
    output << p1788::io::punctuation;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "0.0??_def" ) );

    output << p1788::io::inf_sup_form;
    output << p1788::io::width(10);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[        entire       ]_trv" ) );

    output << p1788::io::special_bounds;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[      -inf,       inf]_def" ) );

    output << p1788::io::string_width(27);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[      -inf,       inf]_dac" ) );

    output << p1788::io::string_width(29);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[       -inf,        inf]_trv" ) );

    output << p1788::io::special_no_bounds;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[           ,           ]_def" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[          ,          ]_dac" ) );

    output << p1788::io::special_bounds;
    output << p1788::io::precision(27);
    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,INF_D), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[      -INF,       INF]_TRV" ) );
}


BOOST_AUTO_TEST_CASE(minimal_nai_output_test)
{
    boost::test_tools::output_test_stream output;


    F<double>::operator_output(output, F<double>::nai());
    BOOST_CHECK( output.is_equal( "[nai]" ) );

    output << p1788::io::hex;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, F<double>::nai());
    BOOST_CHECK( output.is_equal( "[NAI]" ) );

    output << p1788::io::decimal;
    output << p1788::io::lower_case;
    output << p1788::io::string_width(12);
    F<double>::operator_output(output, F<double>::nai());
    BOOST_CHECK( output.is_equal( "[   nai    ]" ) );

    output << p1788::io::dec_numeric;
    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    output << p1788::io::hex;
    F<double>::operator_output(output, F<double>::nai());
    BOOST_CHECK( output.is_equal( "    NAI     " ) );

    output << p1788::io::string_width(11);
    output << p1788::io::decimal;
    F<double>::operator_output(output, F<double>::nai());
    BOOST_CHECK( output.is_equal( "    NAI    " ) );

    output << p1788::io::dec_alpha;
    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    F<double>::operator_output(output, F<double>::nai());
    BOOST_CHECK( output.is_equal( "[   nai   ]" ) );

    output << p1788::io::uncertain_form;
    F<double>::operator_output(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[   nai   ]" ) );

    output << p1788::io::upper_case;
    output << p1788::io::special_text;
    output << p1788::io::no_punctuation;
    F<double>::operator_output(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "    NAI    " ) );

    output << p1788::io::inf_sup_form;
    output << p1788::io::punctuation;
    output << p1788::io::width(10);
    F<double>::operator_output(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[         NAI         ]" ) );

    output << p1788::io::special_bounds;
    F<double>::operator_output(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[         NAI         ]" ) );

    output << p1788::io::string_width(23);
    F<double>::operator_output(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[         NAI         ]" ) );

    output << p1788::io::string_width(25);
    F<double>::operator_output(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[          NAI          ]" ) );

    output << p1788::io::special_no_bounds;
    F<double>::operator_output(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[          NAI          ]" ) );

    output << p1788::io::string_width(0);
    F<double>::operator_output(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[         NAI         ]" ) );

    output << p1788::io::special_bounds;
    output << p1788::io::precision(27);
    output << p1788::io::lower_case;
    F<double>::operator_output(output, F<double>::nai() );
    BOOST_CHECK( output.is_equal( "[         nai         ]" ) );
}



BOOST_AUTO_TEST_CASE(minimal_bare_interval_output_test)
{
    boost::test_tools::output_test_stream output;

    F<double>::operator_output(output, REP<double>(0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[0.1,0.100001]" ) );

    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP<double>(-0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[-0.100001,0.100001]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(22);
    F<double>::operator_output(output, REP<double>(-0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[ -0.100001, 0.100001]" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP<double>(-0.1,0.1) );
    BOOST_CHECK( output.is_equal( "  -0.100001   0.100001" ) );

    output << p1788::io::hex;
    output << p1788::io::string_width(0);
    F<double>::operator_output(output, REP<double>(-0.1,1.3) );
    BOOST_CHECK( output.is_equal( "-0X1.999999999999AP-4 0X1.4CCCCCCCCCCCDP+0" ) );

    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    output << p1788::io::precision(5);
    output << p1788::io::width(15);
    F<double>::operator_output(output, REP<double>(-0.1,1.3) );
    BOOST_CHECK( output.is_equal( "[  -0x1.9999ap-4,   0x1.4cccdp+0]" ) );

    output << p1788::io::string_width(35);
    output << p1788::io::special_no_bounds;
    F<double>::operator_output(output, REP<double>(0.1,1.3) );
    BOOST_CHECK( output.is_equal( "[    0x1.99999p-4,    0x1.4cccdp+0]" ) );

    output << p1788::io::string_width(0);
    output << p1788::io::precision(20);
    F<double>::operator_output(output, REP<double>(0.1,1.3) );
    BOOST_CHECK( output.is_equal( "[0x1.999999999999a0000000p-4,0x1.4cccccccccccd0000000p+0]" ) );

    output << p1788::io::decimal;
    output << p1788::io::precision(0);
    output << p1788::io::width(10);
    F<double>::operator_output(output, REP<double>(0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[  0.100000,  0.100001]" ) );

    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP<double>(-0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[ -0.100001,  0.100001]" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(25);
    output << p1788::io::precision(7);
    F<double>::operator_output(output, REP<double>(0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[  0.1000000,  0.1000001]" ) );

    output << p1788::io::decimal_scientific;
    output << p1788::io::string_width(0);
    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP<double>(0.1,0.1) );
    BOOST_CHECK( output.is_equal( "[       0.1, 0.1000001]" ) );

    output << p1788::io::scientific;
    F<double>::operator_output(output, REP<double>(0.1,1.3) );
    BOOST_CHECK( output.is_equal( "[1.0000000E-01,1.3000001E+00]" ) );

    output << p1788::io::lower_case;
    F<double>::operator_output(output, REP<double>(-INF_D,0.1) );
    BOOST_CHECK( output.is_equal( "[      -inf,1.0000001e-01]" ) );

    output << p1788::io::decimal_scientific;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP<double>(0.1,INF_D) );
    BOOST_CHECK( output.is_equal( "[       0.1,       INF]" ) );

    output << p1788::io::hex;
    F<double>::operator_output(output, REP<double>(-INF_D,0.1) );
    BOOST_CHECK( output.is_equal( "[      -INF,0X1.999999AP-4]" ) );

    output << p1788::io::decimal;
    F<double>::operator_output(output, REP<double>(0.1,INF_D) );
    BOOST_CHECK( output.is_equal( "[ 0.1000000,       INF]" ) );

}



BOOST_AUTO_TEST_CASE(minimal_decorated_interval_output_test)
{
    boost::test_tools::output_test_stream output;

    F<double>::operator_output(output, REP_DEC<double>(REP<double>(0.1,0.1), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[0.1,0.100001]_trv" ) );

    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-0.1,0.1), DEC::def) );
    BOOST_CHECK( output.is_equal( "[-0.100001,0.100001]_DEF" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(26);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-0.1,0.1), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[ -0.100001, 0.100001]_dac" ) );

    output << p1788::io::no_punctuation;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-0.1,0.1), DEC::com) );
    BOOST_CHECK( output.is_equal( "  -0.100001   0.100001 COM" ) );

    output << p1788::io::dec_numeric;
    output << p1788::io::hex;
    output << p1788::io::string_width(0);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-0.1,1.3), DEC::trv) );
    BOOST_CHECK( output.is_equal( "-0X1.999999999999AP-4 0X1.4CCCCCCCCCCCDP+0 4" ) );

    output << p1788::io::punctuation;
    output << p1788::io::lower_case;
    output << p1788::io::precision(5);
    output << p1788::io::width(15);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-0.1,1.3), DEC::def) );
    BOOST_CHECK( output.is_equal( "[  -0x1.9999ap-4,   0x1.4cccdp+0]_8" ) );

    output << p1788::io::string_width(35);
    output << p1788::io::special_no_bounds;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(0.1,1.3), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[   0x1.99999p-4,   0x1.4cccdp+0]_12" ) );

    output << p1788::io::string_width(0);
    output << p1788::io::precision(20);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(0.1,1.3), DEC::com) );
    BOOST_CHECK( output.is_equal( "[0x1.999999999999a0000000p-4,0x1.4cccccccccccd0000000p+0]_16" ) );

    output << p1788::io::decimal;
    output << p1788::io::precision(0);
    output << p1788::io::width(10);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(0.1,0.1), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[  0.100000,  0.100001]_4" ) );

    output << p1788::io::dec_alpha;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-0.1,0.1), DEC::def) );
    BOOST_CHECK( output.is_equal( "[ -0.100001,  0.100001]_DEF" ) );

    output << p1788::io::lower_case;
    output << p1788::io::string_width(29);
    output << p1788::io::precision(7);
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(0.1,0.1), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[  0.1000000,  0.1000001]_dac" ) );

    output << p1788::io::decimal_scientific;
    output << p1788::io::string_width(0);
    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(0.1,0.1), DEC::com) );
    BOOST_CHECK( output.is_equal( "[       0.1, 0.1000001]_COM" ) );

    output << p1788::io::scientific;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(0.1,1.3), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[1.0000000E-01,1.3000001E+00]_TRV" ) );

    output << p1788::io::lower_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,0.1), DEC::def) );
    BOOST_CHECK( output.is_equal( "[      -inf,1.0000001e-01]_def" ) );

    output << p1788::io::decimal_scientific;
    output << p1788::io::upper_case;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(0.1,INF_D), DEC::dac) );
    BOOST_CHECK( output.is_equal( "[       0.1,       INF]_DAC" ) );

    output << p1788::io::hex;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(-INF_D,0.1), DEC::trv) );
    BOOST_CHECK( output.is_equal( "[      -INF,0X1.999999AP-4]_TRV" ) );

    output << p1788::io::decimal;
    F<double>::operator_output(output, REP_DEC<double>(REP<double>(0.1,INF_D), DEC::def) );
    BOOST_CHECK( output.is_equal( "[ 0.1000000,       INF]_DEF" ) );

}

