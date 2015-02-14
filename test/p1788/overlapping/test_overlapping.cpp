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

#define BOOST_TEST_MODULE "Overlapping [p1788/overlapping/overlapping]"
#include "test/util/boost_test_wrapper.hpp"

#include <boost/test/output_test_stream.hpp>

#include "p1788/overlapping/overlapping.hpp"


typedef p1788::overlapping::overlapping_state OS;

using namespace p1788;

BOOST_AUTO_TEST_CASE(minimal_overlapping_output_test)
{
    boost::test_tools::output_test_stream output;

    output << OS::undefined;
    BOOST_CHECK( output.is_equal( "undefined" ) );

    output << OS::both_empty;
    BOOST_CHECK( output.is_equal( "both_empty" ) );

    output << OS::first_empty;
    BOOST_CHECK( output.is_equal( "first_empty" ) );

    output << OS::second_empty;
    BOOST_CHECK( output.is_equal( "second_empty" ) );

    output << OS::before;
    BOOST_CHECK( output.is_equal( "before" ) );

    output << OS::meets;
    BOOST_CHECK( output.is_equal( "meets" ) );

    output << OS::overlaps;
    BOOST_CHECK( output.is_equal( "overlaps" ) );

    output << OS::starts;
    BOOST_CHECK( output.is_equal( "starts" ) );

    output << OS::contained_by;
    BOOST_CHECK( output.is_equal( "contained_by" ) );

    output << OS::finishes;
    BOOST_CHECK( output.is_equal( "finishes" ) );

    output << OS::equal;
    BOOST_CHECK( output.is_equal( "equal" ) );

    output << OS::finished_by;
    BOOST_CHECK( output.is_equal( "finished_by" ) );

    output << OS::contains;
    BOOST_CHECK( output.is_equal( "contains" ) );

    output << OS::started_by;
    BOOST_CHECK( output.is_equal( "started_by" ) );

    output << OS::overlapped_by;
    BOOST_CHECK( output.is_equal( "overlapped_by" ) );

    output << OS::met_by;
    BOOST_CHECK( output.is_equal( "met_by" ) );

    output << OS::after;
    BOOST_CHECK( output.is_equal( "after" ) );



    output << p1788::io::overlapping_numeric;


    output << OS::undefined;
    BOOST_CHECK( output.is_equal( "0" ) );

    output << OS::both_empty;
    BOOST_CHECK( output.is_equal( "1" ) );

    output << OS::first_empty;
    BOOST_CHECK( output.is_equal( "2" ) );

    output << OS::second_empty;
    BOOST_CHECK( output.is_equal( "4" ) );

    output << OS::before;
    BOOST_CHECK( output.is_equal( "8" ) );

    output << OS::meets;
    BOOST_CHECK( output.is_equal( "16" ) );

    output << OS::overlaps;
    BOOST_CHECK( output.is_equal( "32" ) );

    output << OS::starts;
    BOOST_CHECK( output.is_equal( "64" ) );

    output << OS::contained_by;
    BOOST_CHECK( output.is_equal( "128" ) );

    output << OS::finishes;
    BOOST_CHECK( output.is_equal( "256" ) );

    output << OS::equal;
    BOOST_CHECK( output.is_equal( "512" ) );

    output << OS::finished_by;
    BOOST_CHECK( output.is_equal( "1024" ) );

    output << OS::contains;
    BOOST_CHECK( output.is_equal( "2048" ) );

    output << OS::started_by;
    BOOST_CHECK( output.is_equal( "4096" ) );

    output << OS::overlapped_by;
    BOOST_CHECK( output.is_equal( "8192" ) );

    output << OS::met_by;
    BOOST_CHECK( output.is_equal( "16384" ) );

    output << OS::after;
    BOOST_CHECK( output.is_equal( "32768" ) );


    output << p1788::io::overlapping_alpha;
    output << p1788::io::upper_case;
    output << OS::undefined;
    BOOST_CHECK( output.is_equal( "UNDEFINED" ) );

    output << OS::both_empty;
    BOOST_CHECK( output.is_equal( "BOTH_EMPTY" ) );

    output << OS::first_empty;
    BOOST_CHECK( output.is_equal( "FIRST_EMPTY" ) );

    output << OS::second_empty;
    BOOST_CHECK( output.is_equal( "SECOND_EMPTY" ) );

    output << OS::before;
    BOOST_CHECK( output.is_equal( "BEFORE" ) );

    output << OS::meets;
    BOOST_CHECK( output.is_equal( "MEETS" ) );

    output << OS::overlaps;
    BOOST_CHECK( output.is_equal( "OVERLAPS" ) );

    output << OS::starts;
    BOOST_CHECK( output.is_equal( "STARTS" ) );

    output << OS::contained_by;
    BOOST_CHECK( output.is_equal( "CONTAINED_BY" ) );

    output << OS::finishes;
    BOOST_CHECK( output.is_equal( "FINISHES" ) );

    output << OS::equal;
    BOOST_CHECK( output.is_equal( "EQUAL" ) );

    output << OS::finished_by;
    BOOST_CHECK( output.is_equal( "FINISHED_BY" ) );

    output << OS::contains;
    BOOST_CHECK( output.is_equal( "CONTAINS" ) );

    output << OS::started_by;
    BOOST_CHECK( output.is_equal( "STARTED_BY" ) );

    output << OS::overlapped_by;
    BOOST_CHECK( output.is_equal( "OVERLAPPED_BY" ) );

    output << OS::met_by;
    BOOST_CHECK( output.is_equal( "MET_BY" ) );

    output << OS::after;
    BOOST_CHECK( output.is_equal( "AFTER" ) );
}
