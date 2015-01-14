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

#define BOOST_TEST_MODULE "Integration: Extended interval comparisons  [infsup/interval, infsup/decorated_interval, p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include <limits>

#include "p1788/p1788.hpp"

template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

typedef p1788::decoration::decoration DEC;
typedef p1788::overlapping::overlapping_state OS;


BOOST_AUTO_TEST_CASE(integration_overlap_test)
{
    BOOST_CHECK_EQUAL( overlap(I<double>(1.0,2.0), I<double>(1.5,2.5)), OS::overlaps );
    BOOST_CHECK_EQUAL( overlap(I<float>(1.0f,2.0f), I<double>(2.0,2.5)), OS::meets );
    BOOST_CHECK_EQUAL( I<double>::overlap(I<double>(1.0,2.0), I<double>(1.5,1.5)), OS::contains );
    BOOST_CHECK_EQUAL( I<float>::overlap(I<float>(1.0f,2.0f), I<double>(2.5,2.5)), OS::before );


    BOOST_CHECK_EQUAL( overlap(DI<double>(1.0,2.0,DEC::trv), DI<double>(1.5,2.5,DEC::def)), OS::overlaps );
    BOOST_CHECK_EQUAL( overlap(DI<float>(1.0f,2.0f,DEC::dac), DI<double>(2.0,2.5,DEC::com)), OS::meets );
    BOOST_CHECK_EQUAL( DI<double>::overlap(DI<double>(1.0,2.0,DEC::def), DI<double>(1.5,1.5,DEC::trv)), OS::contains );
    BOOST_CHECK_EQUAL( DI<float>::overlap(DI<float>(1.0f,2.0f,DEC::com), DI<double>(2.5,2.5,DEC::def)), OS::before );
}

