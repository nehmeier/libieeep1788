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

#define BOOST_TEST_MODULE "Integration: IO [infsup/interval, infsup/decorated_interval, p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include <boost/test/output_test_stream.hpp>

#include "p1788/p1788.hpp"

#include <sstream>

template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

typedef p1788::decoration::decoration DEC;

const double INF_D = std::numeric_limits<double>::infinity();

BOOST_AUTO_TEST_CASE(integration_output_test)
{
    boost::test_tools::output_test_stream output;

    output << I<double>::empty();
    BOOST_CHECK( output.is_equal( "[empty]" ) );

    output << I<double>::entire();
    BOOST_CHECK( output.is_equal( "[entire]" ) );

    output << I<float>(1.0,2.1);
    BOOST_CHECK( output.is_equal( "[1,2.10001]" ) );

    output << I<double>(0.0,-0.0);
    BOOST_CHECK( output.is_equal( "[-0,0]" ) );

    output << DI<double>::nai();
    BOOST_CHECK( output.is_equal( "[nai]" ) );

    output << DI<double>::empty();
    BOOST_CHECK( output.is_equal( "[empty]" ) );

    output << DI<double>::entire();
    BOOST_CHECK( output.is_equal( "[entire]_dac" ) );

    output << DI<double>(1.0,2.1);
    BOOST_CHECK( output.is_equal( "[1,2.10001]_com" ) );

    output << p1788::io::uncertain_form;

    output << I<double>::entire();
    BOOST_CHECK( output.is_equal( "0.000000??" ) );

    output << DI<double>::entire();
    BOOST_CHECK( output.is_equal( "0.000000??_dac" ) );
}


BOOST_AUTO_TEST_CASE(integration_input_test)
{
    {
        I<double> x;
        std::istringstream is("[empty]");
        is >> x;
        BOOST_CHECK( is_empty( x) );
        BOOST_CHECK(is);
    }

    {
        I<double> x;
        std::istringstream is("[entire]");
        is >> x;
        BOOST_CHECK( is_entire( x) );
        BOOST_CHECK(is);
    }

    {
        I<double> x;
        std::istringstream is("[1,2.1]");
        is >> x;
        BOOST_CHECK_EQUAL( x, I<double>(1.0,2.1) );
        BOOST_CHECK(is);
    }

    {
        I<double> x;
        std::istringstream is("0.000000??");
        is >> x;
        BOOST_CHECK( is_entire( x) );
        BOOST_CHECK(is);
    }

    {
        DI<double> x;
        std::istringstream is("[nai]");
        is >> x;
        BOOST_CHECK( is_nai( x) );
        BOOST_CHECK(is);
    }

    {
        DI<float> x;
        std::istringstream is("[empty]");
        is >> x;
        BOOST_CHECK( is_empty( x) );
        BOOST_CHECK(is);
    }

    {
        DI<double> x;
        std::istringstream is("[entire]_def");
        is >> x;
        BOOST_CHECK_EQUAL( x, DI<double>(-INF_D, INF_D, DEC::def) );
        BOOST_CHECK(is);
    }

    {
        DI<double> x;
        std::istringstream is("[1,2.1]_trv");
        is >> x;
        BOOST_CHECK_EQUAL( x, DI<double>(1.0, 2.1, DEC::trv) );
        BOOST_CHECK(is);
    }

    {
        DI<double> x;
        std::istringstream is("0.000000??");
        is >> x;
        BOOST_CHECK_EQUAL( x, DI<double>(-INF_D, INF_D, DEC::dac) );
        BOOST_CHECK(is);
    }
}
