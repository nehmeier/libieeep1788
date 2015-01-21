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

#define BOOST_TEST_MODULE "IO utility [p1788/util/io]"
#include "test/util/boost_test_wrapper.hpp"

#include <iostream>
#include <string>

#include "p1788/util/io.hpp"

BOOST_AUTO_TEST_CASE(minimal_remove_ws_test)
{
    {
        std::stringstream ss("");
        p1788::util::remove_ws(ss);

        BOOST_CHECK(ss);

        std::string tail;
        ss >> tail;
        BOOST_CHECK_EQUAL(tail, "");
        BOOST_CHECK(ss.eof());
    }

    {
        std::stringstream ss("foo");
        p1788::util::remove_ws(ss);

        BOOST_CHECK(ss);

        std::string tail;
        ss >> tail;
        BOOST_CHECK_EQUAL(tail, "foo");
        BOOST_CHECK(ss);
    }

    {
        std::stringstream ss("  test");
        p1788::util::remove_ws(ss);

        BOOST_CHECK(ss);

        std::string tail;
        ss >> tail;
        BOOST_CHECK_EQUAL(tail, "test");
        BOOST_CHECK(ss);
    }

    {
        std::stringstream ss(" \t \t t \t");
        p1788::util::remove_ws(ss);

        BOOST_CHECK(ss);

        std::string tail;
        ss >> tail;
        BOOST_CHECK_EQUAL(tail, "t");
        BOOST_CHECK(ss);
    }

}

BOOST_AUTO_TEST_CASE(minimal_ascii_to_lower_test)
{
    std::string a = " abcde ";
    p1788::util::ascii_to_lower(a);
    BOOST_CHECK_EQUAL(a, " abcde ");

    std::string b = " ABCDE ";
    p1788::util::ascii_to_lower(b);
    BOOST_CHECK_EQUAL(b, " abcde ");

    std::string c = " abCde ";
    p1788::util::ascii_to_lower(c);
    BOOST_CHECK_EQUAL(c, " abcde ");

    std::string d = " AbCdEF";
    p1788::util::ascii_to_lower(d);
    BOOST_CHECK_EQUAL(d, " abcdef");

    std::string e = "1A2B3C4";
    p1788::util::ascii_to_lower(e);
    BOOST_CHECK_EQUAL(e, "1a2b3c4");

    std::string f = "1A.B?,4";
    p1788::util::ascii_to_lower(f);
    BOOST_CHECK_EQUAL(f, "1a.b?,4");

    std::string g = "";
    p1788::util::ascii_to_lower(g);
    BOOST_CHECK_EQUAL(g, "");

    std::string h = "  ";
    p1788::util::ascii_to_lower(h);
    BOOST_CHECK_EQUAL(h, "  ");
}
