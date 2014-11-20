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

#define BOOST_TEST_MODULE "IO utility [p1788/util/io]"
#include "test/util/boost_test_wrapper.hpp"

#include <iostream>

#include "p1788/util/io.hpp"



using namespace p1788;

BOOST_AUTO_TEST_CASE(minimal_remove_ws_test)
{
    {
        std::stringstream ss("");
        p1788::util::remove_ws(ss);

        BOOST_CHECK(ss);

        std::string str;
        ss >> str;
        BOOST_CHECK_EQUAL(str, "");
        BOOST_CHECK(!ss);
    }

    {
        std::stringstream ss("foo");
        p1788::util::remove_ws(ss);

        BOOST_CHECK(ss);

        std::string str;
        ss >> str;
        BOOST_CHECK_EQUAL(str, "foo");
        BOOST_CHECK(ss);
    }


    {
        std::stringstream ss("  test");
        p1788::util::remove_ws(ss);

        BOOST_CHECK(ss);

        std::string str;
        ss >> str;
        BOOST_CHECK_EQUAL(str, "test");
        BOOST_CHECK(ss);
    }
}
