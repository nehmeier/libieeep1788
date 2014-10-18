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

#define BOOST_TEST_MODULE "Recommended interval overlapping [infsup/interval, infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include <limits>
#include "p1788/p1788.hpp"

template<typename T>
using flavor = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T, p1788::flavor::infsup::setbased::subnormalize::yes, p1788::flavor::infsup::setbased::auto_setup::yes>;

template<typename T>
using I = p1788::infsup::interval<T, flavor>;

const double INF = std::numeric_limits<double>::infinity();


using p1788::overlapping::overlapping_state;

BOOST_AUTO_TEST_CASE(minimal_overlap_test)
{
    BOOST_CHECK_EQUAL(overlap(I<double>::empty(), I<double>::empty()), overlapping_state::both_empty);
    BOOST_CHECK_EQUAL(overlap(I<double>::empty(), I<double>(1.0,2.0)), overlapping_state::first_empty);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,2.0), I<double>::empty()), overlapping_state::second_empty);

    BOOST_CHECK_EQUAL(overlap(I<double>(-2.0,-1.0), I<double>(1.0,2.0)), overlapping_state::before);
    BOOST_CHECK_EQUAL(overlap(I<double>(-2.0,-1.0), I<double>(1.0,1.0)), overlapping_state::before);
    BOOST_CHECK_EQUAL(overlap(I<double>(-1.0,-1.0), I<double>(1.0,2.0)), overlapping_state::before);
    BOOST_CHECK_EQUAL(overlap(I<double>(-1.0,-1.0), I<double>(1.0,1.0)), overlapping_state::before);
    BOOST_CHECK_EQUAL(overlap(I<double>(-INF,-1.0), I<double>(1.0,1.0)), overlapping_state::before);
    BOOST_CHECK_EQUAL(overlap(I<double>(-1.0,-1.0), I<double>(1.0,INF)), overlapping_state::before);
    BOOST_CHECK_EQUAL(overlap(I<double>(-INF,-1.0), I<double>(1.0,INF)), overlapping_state::before);

    BOOST_CHECK_EQUAL(overlap(I<double>(-2.0,1.0), I<double>(1.0,2.0)), overlapping_state::meets);
    BOOST_CHECK_EQUAL(overlap(I<double>(0.0,1.0), I<double>(1.0,2.0)), overlapping_state::meets);
    BOOST_CHECK_EQUAL(overlap(I<double>(-INF,1.0), I<double>(1.0,2.0)), overlapping_state::meets);
    BOOST_CHECK_EQUAL(overlap(I<double>(-1.0,1.0), I<double>(1.0,INF)), overlapping_state::meets);
    BOOST_CHECK_EQUAL(overlap(I<double>(-INF,1.0), I<double>(1.0,INF)), overlapping_state::meets);

    BOOST_CHECK_EQUAL(overlap(I<double>(-2.0,1.0), I<double>(0.0,2.0)), overlapping_state::overlaps);
    BOOST_CHECK_EQUAL(overlap(I<double>(-INF,1.0), I<double>(-1.0,2.0)), overlapping_state::overlaps);
    BOOST_CHECK_EQUAL(overlap(I<double>(0.0,2.0), I<double>(1.0,INF)), overlapping_state::overlaps);
    BOOST_CHECK_EQUAL(overlap(I<double>(-INF,2.0), I<double>(1.0,INF)), overlapping_state::overlaps);

    BOOST_CHECK_EQUAL(overlap(I<double>(-2.0,1.0), I<double>(-2.0,2.0)), overlapping_state::starts);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,1.0), I<double>(1.0,2.0)), overlapping_state::starts);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,2.0), I<double>(1.0,INF)), overlapping_state::starts);

    BOOST_CHECK_EQUAL(overlap(I<double>(-1.0,1.0), I<double>(-2.0,2.0)), overlapping_state::contained_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,1.0), I<double>(0.0,2.0)), overlapping_state::contained_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(-1.0,1.0), I<double>(-INF,2.0)), overlapping_state::contained_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,1.0), I<double>(0.0,INF)), overlapping_state::contained_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,1.0), I<double>::entire()), overlapping_state::contained_by);

    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,2.0), I<double>(-2.0,2.0)), overlapping_state::finishes);
    BOOST_CHECK_EQUAL(overlap(I<double>(2.0,2.0), I<double>(1.0,2.0)), overlapping_state::finishes);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,2.0), I<double>(-INF,2.0)), overlapping_state::finishes);

    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,2.0), I<double>(1.0,2.0)), overlapping_state::equal);
    BOOST_CHECK_EQUAL(overlap(I<double>(-INF,2.0), I<double>(-INF,2.0)), overlapping_state::equal);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,INF), I<double>(1.0,INF)), overlapping_state::equal);
    BOOST_CHECK_EQUAL(overlap(I<double>::entire(), I<double>::entire()), overlapping_state::equal);


    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,2.0), I<double>(-2.0,-1.0)), overlapping_state::after);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,1.0), I<double>(-2.0,-1.0)), overlapping_state::after);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,2.0), I<double>(-1.0,-1.0)), overlapping_state::after);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,1.0), I<double>(-1.0,-1.0)), overlapping_state::after);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,1.0), I<double>(-INF,-1.0)), overlapping_state::after);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,INF), I<double>(-1.0,-1.0)), overlapping_state::after);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,INF), I<double>(-INF,-1.0)), overlapping_state::after);

    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,2.0), I<double>(-2.0,1.0)), overlapping_state::met_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,2.0), I<double>(-INF,1.0)), overlapping_state::met_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,INF), I<double>(-1.0,1.0)), overlapping_state::met_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,INF), I<double>(-INF,1.0)), overlapping_state::met_by);

    BOOST_CHECK_EQUAL(overlap(I<double>(0.0,2.0), I<double>(-2.0,1.0)), overlapping_state::overlapped_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(-1.0,2.0), I<double>(-INF,1.0)), overlapping_state::overlapped_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,INF), I<double>(0.0,2.0)), overlapping_state::overlapped_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,INF), I<double>(-INF,2.0)), overlapping_state::overlapped_by);

    BOOST_CHECK_EQUAL(overlap(I<double>(-2.0,2.0), I<double>(-2.0,1.0)), overlapping_state::started_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,2.0), I<double>(1.0,1.0)), overlapping_state::started_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,INF), I<double>(1.0,2.0)), overlapping_state::started_by);

    BOOST_CHECK_EQUAL(overlap(I<double>(-2.0,2.0), I<double>(-1.0,1.0)), overlapping_state::contains);
    BOOST_CHECK_EQUAL(overlap(I<double>(0.0,2.0), I<double>(1.0,1.0)), overlapping_state::contains);
    BOOST_CHECK_EQUAL(overlap(I<double>(-INF,2.0), I<double>(-1.0,1.0)), overlapping_state::contains);
    BOOST_CHECK_EQUAL(overlap(I<double>(0.0,INF), I<double>(1.0,1.0)), overlapping_state::contains);
    BOOST_CHECK_EQUAL(overlap(I<double>::entire(), I<double>(1.0,1.0)), overlapping_state::contains);

    BOOST_CHECK_EQUAL(overlap(I<double>(-2.0,2.0), I<double>(1.0,2.0)), overlapping_state::finished_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(1.0,2.0), I<double>(2.0,2.0)), overlapping_state::finished_by);
    BOOST_CHECK_EQUAL(overlap(I<double>(-INF,2.0), I<double>(1.0,2.0)), overlapping_state::finished_by);


}
