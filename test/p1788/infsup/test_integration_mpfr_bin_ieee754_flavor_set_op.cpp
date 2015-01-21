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
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#define BOOST_TEST_MODULE "Integration: Set operations [infsup/interval, infsup/decorated_interval, p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include <limits>

#include "p1788/p1788.hpp"

template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;
template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

typedef p1788::decoration::decoration DEC;

BOOST_AUTO_TEST_CASE(integration_intersect_test)
{
    BOOST_CHECK_EQUAL( intersect(I<double>(1.0,3.0), I<double>(2.1,4.0)), I<double>(2.1,3.0) );
    BOOST_CHECK_EQUAL( I<double>::intersect(I<double>(1.0,3.0), I<double>(3.0,4.0)), I<double>(3.0,3.0) );
    BOOST_CHECK_EQUAL( I<double>::intersect(I<float>(1.0f,3.0f), I<long double>::empty()), I<double>::empty()  );

    BOOST_CHECK_EQUAL( intersect(DI<double>(1.0,3.0), DI<double>(2.1,4.0)), DI<double>(2.1,3.0,DEC::trv) );
    BOOST_CHECK_EQUAL( DI<double>::intersect(DI<double>(1.0,3.0), DI<double>(3.0,4.0)), DI<double>(3.0,3.0,DEC::trv) );
    BOOST_CHECK_EQUAL( DI<double>::intersect(DI<float>(1.0f,3.0f), DI<long double>::empty()), DI<double>::empty()  );
}

BOOST_AUTO_TEST_CASE(integration_hull_test)
{
    BOOST_CHECK_EQUAL( hull(I<double>(1.0,3.0), I<double>(2.1,4.0)), I<double>(1.0,4.0) );
    BOOST_CHECK_EQUAL( I<double>::hull(I<double>(1.0,3.0), I<double>(3.0,4.0)), I<double>(1.0,4.0) );
    BOOST_CHECK_EQUAL( I<double>::hull(I<float>(1.0f,3.0f), I<long double>::empty()), I<double>(1.0,3.0)  );

    BOOST_CHECK_EQUAL( hull(DI<double>(1.0,3.0), DI<double>(2.1,4.0)), DI<double>(1.0,4.0,DEC::trv) );
    BOOST_CHECK_EQUAL( DI<double>::hull(DI<double>(1.0,3.0), DI<double>(3.0,4.0)), DI<double>(1.0,4.0,DEC::trv) );
    BOOST_CHECK_EQUAL( DI<double>::hull(DI<float>(1.0f,3.0f), DI<long double>::empty()), DI<double>(1.0,3.0,DEC::trv)  );
}
