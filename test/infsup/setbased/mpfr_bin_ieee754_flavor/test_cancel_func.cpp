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

#define BOOST_TEST_MODULE "Cancellative addition and subtraction [infsup/interval, infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include <limits>
#include "p1788/p1788.hpp"

const double INF = std::numeric_limits<double>::infinity();
const double MAX = std::numeric_limits<double>::max();
const double MIN = std::numeric_limits<double>::min();

template<typename T>
using flavor = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T, p1788::flavor::infsup::setbased::subnormalize::yes, p1788::flavor::infsup::setbased::auto_setup::yes>;

template<typename T>
using I = p1788::infsup::interval<T, flavor>;


BOOST_AUTO_TEST_CASE(minimal_cancel_plus_test)
{
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-INF, -1.0), I<double>::empty()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-1.0, INF), I<double>::empty()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>::entire(), I<double>::empty()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-INF, -1.0), I<double>(-5.0,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-1.0, INF), I<double>(-5.0,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>::entire(), I<double>(-5.0,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>::empty(), I<double>(1.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>::empty(), I<double>(-INF,1.0)),I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>::empty(), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-1.0,5.0), I<double>(1.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-1.0,5.0), I<double>(-INF,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-1.0,5.0), I<double>::entire() ), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>::entire(), I<double>(1.0,INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>::entire(), I<double>(-INF,1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-5.0, -1.0), I<double>(1.0,5.1)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-5.0, -1.0), I<double>(0.9,5.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-5.0, -1.0), I<double>(0.9,5.1)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-10.0, 5.0), I<double>(-5.0,10.1)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-10.0, 5.0), I<double>(-5.1,10.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-10.0, 5.0), I<double>(-5.1,10.1)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(1.0, 5.0), I<double>(-5.0,-0.9)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(1.0, 5.0), I<double>(-5.1,-1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(1.0, 5.0), I<double>(-5.1,-0.9)), I<double>::entire() );

    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-10.0, -1.0), I<double>::empty()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-10.0, 5.0), I<double>::empty()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(1.0, 5.0), I<double>::empty()), I<double>::entire() );


    BOOST_CHECK_EQUAL( cancel_plus(I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>::empty(), I<double>(1.0,10.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>::empty(), I<double>(-5.0,10.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>::empty(), I<double>(-5.0,-1.0)), I<double>::empty() );

    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-5.1,-0.0), I<double>(0.0,5.0)), I<double>(-0X1.999999999998P-4,0.0) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-5.1,-1.0), I<double>(1.0,5.0)), I<double>(-0X1.999999999998P-4,0.0) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-5.0,-0.9), I<double>(1.0,5.0)), I<double>(0.0, 0X1.9999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-5.1,-0.9), I<double>(1.0,5.0)), I<double>(-0X1.999999999998P-4,0X1.9999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-5.0,-1.0), I<double>(1.0,5.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-10.1, 5.0), I<double>(-5.0,10.0)), I<double>(-0X1.999999999998P-4,0.0) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-10.0, 5.1), I<double>(-5.0,10.0)), I<double>(0.0,0X1.999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-10.1, 5.1), I<double>(-5.0,10.0)), I<double>(-0X1.999999999998P-4,0X1.999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-10.0, 5.0), I<double>(-5.0,10.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(0.9, 5.0), I<double>(-5.0,-1.0)), I<double>(-0X1.9999999999998P-4,0.0) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(1.0, 5.1), I<double>(-5.0,-1.0)), I<double>(0.0,0X1.999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(0.0, 5.1), I<double>(-5.0,-0.0)), I<double>(0.0,0X1.999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(0.9, 5.1), I<double>(-5.0,-1.0)), I<double>(-0X1.9999999999998P-4,0X1.999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(1.0, 5.0), I<double>(-5.0,-1.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(0.0, 5.0), I<double>(-5.0,-0.0)), I<double>(0.0) );

    BOOST_CHECK_EQUAL( cancel_plus(I<double>(0X1.FFFFFFFFFFFFP+0), I<double>(-0X1.999999999999AP-4)), I<double>(0X1.E666666666656P+0,0X1.E666666666657P+0) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0), I<double>(-0X1.999999999999AP-4,0.01)), I<double>(-0X1.70A3D70A3D70BP-4,0X1.E666666666657P+0) );

    BOOST_CHECK_EQUAL( cancel_plus(I<double>(MAX), I<double>(MAX)), I<double>(MAX,INF) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-MAX,MAX), I<double>(-MAX,MAX)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-MAX,MAX), I<double>(-0X1.FFFFFFFFFFFFEP+1023,MAX)), I<double>(0.0,0X1P+971) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-MAX,MAX), I<double>(-MAX,0X1.FFFFFFFFFFFFEP+1023)), I<double>(-0X1P+971,0.0) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-MAX,0X1.FFFFFFFFFFFFEP+1023), I<double>(-MAX,MAX)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-0X1.FFFFFFFFFFFFEP+1023,MAX), I<double>(-MAX,MAX)), I<double>::entire() );

    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-0X1P+0,0X1.FFFFFFFFFFFFFP-53), I<double>(-0X1P+0,0X1.FFFFFFFFFFFFEP-53)), I<double>(-0X1.FFFFFFFFFFFFFP-1,-0X1.FFFFFFFFFFFFEP-1) );
    BOOST_CHECK_EQUAL( cancel_plus(I<double>(-0X1P+0,0X1.FFFFFFFFFFFFEP-53), I<double>(-0X1P+0,0X1.FFFFFFFFFFFFFP-53)), I<double>::entire() );
}

BOOST_AUTO_TEST_CASE(minimal_cancel_minus_test)
{
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-INF, -1.0), I<double>::empty()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-1.0, INF), I<double>::empty()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>::entire(), I<double>::empty()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-INF, -1.0), I<double>(-1.0,5.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-1.0, INF), I<double>(-1.0,5.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>::entire(), I<double>(-1.0,5.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-INF, -1.0), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-1.0, INF), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>::empty(), I<double>(-INF, -1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>::empty(), I<double>(-1.0, INF)),I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>::empty(), I<double>::entire()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-1.0,5.0), I<double>(-INF, -1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-1.0,5.0), I<double>(-1.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-1.0,5.0), I<double>::entire() ), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>::entire(), I<double>(-INF, -1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>::entire(), I<double>(-1.0, INF)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>::entire(), I<double>::entire()), I<double>::entire() );

    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-5.0, -1.0), I<double>(-5.1,-1.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-5.0, -1.0), I<double>(-5.0,-0.9)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-5.0, -1.0), I<double>(-5.1,-0.9)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-10.0, 5.0), I<double>(-10.1, 5.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-10.0, 5.0), I<double>(-10.0, 5.1)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-10.0, 5.0), I<double>(-10.1, 5.1)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(1.0, 5.0), I<double>(0.9, 5.0)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(1.0, 5.0), I<double>(1.0, 5.1)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(1.0, 5.0), I<double>(0.9, 5.1)), I<double>::entire() );

    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-10.0, -1.0), I<double>::empty()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-10.0, 5.0), I<double>::empty()), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(1.0, 5.0), I<double>::empty()), I<double>::entire() );


    BOOST_CHECK_EQUAL( cancel_minus(I<double>::empty(), I<double>::empty()), I<double>::empty() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>::empty(), I<double>(-10.0, -1.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>::empty(), I<double>(-10.0, 5.0)), I<double>::empty() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>::empty(), I<double>(1.0, 5.0)), I<double>::empty() );

    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-5.1,-0.0), I<double>(-5.0, 0.0)), I<double>(-0X1.999999999998P-4,0.0) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-5.1,-1.0), I<double>(-5.0, -1.0)), I<double>(-0X1.999999999998P-4,0.0) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-5.0,-0.9), I<double>(-5.0, -1.0)), I<double>(0.0, 0X1.9999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-5.1,-0.9), I<double>(-5.0, -1.0)), I<double>(-0X1.999999999998P-4,0X1.9999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-5.0,-1.0), I<double>(-5.0, -1.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-10.1, 5.0), I<double>(-10.0, 5.0)), I<double>(-0X1.999999999998P-4,0.0) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-10.0, 5.1), I<double>(-10.0, 5.0)), I<double>(0.0,0X1.999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-10.1, 5.1), I<double>(-10.0, 5.0)), I<double>(-0X1.999999999998P-4,0X1.999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-10.0, 5.0), I<double>(-10.0, 5.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(0.9, 5.0), I<double>(1.0, 5.0)), I<double>(-0X1.9999999999998P-4,0.0) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-0.0, 5.1), I<double>(0.0, 5.0)), I<double>(0.0,0X1.999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(1.0, 5.1), I<double>(1.0, 5.0)), I<double>(0.0,0X1.999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(0.9, 5.1), I<double>(1.0, 5.0)), I<double>(-0X1.9999999999998P-4,0X1.999999999998P-4) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(1.0, 5.0), I<double>(1.0, 5.0)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-5.0, 1.0), I<double>(-1.0, 5.0)), I<double>(-4.0) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-5.0, 0.0), I<double>(-0.0, 5.0)), I<double>(-5.0) );

    BOOST_CHECK_EQUAL( cancel_minus(I<double>(0X1.FFFFFFFFFFFFP+0), I<double>(0X1.999999999999AP-4)), I<double>(0X1.E666666666656P+0,0X1.E666666666657P+0) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-0X1.999999999999AP-4,0X1.FFFFFFFFFFFFP+0), I<double>(-0.01,0X1.999999999999AP-4)), I<double>(-0X1.70A3D70A3D70BP-4,0X1.E666666666657P+0) );

    BOOST_CHECK_EQUAL( cancel_minus(I<double>(MAX), I<double>(-MAX)), I<double>(MAX,INF) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-MAX,MAX), I<double>(-MAX,MAX)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-MAX,MAX), I<double>(-MAX,0X1.FFFFFFFFFFFFEP+1023)), I<double>(0.0,0X1P+971) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-MAX,MAX), I<double>(-0X1.FFFFFFFFFFFFEP+1023,MAX)), I<double>(-0X1P+971,0.0) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-MAX,0X1.FFFFFFFFFFFFEP+1023), I<double>(-MAX,MAX)), I<double>::entire() );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-0X1.FFFFFFFFFFFFEP+1023,MAX), I<double>(-MAX,MAX)), I<double>::entire() );

    BOOST_CHECK_EQUAL( cancel_minus(I<double>(MIN), I<double>(MIN)), I<double>(0.0) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(MIN), I<double>(-MIN)), I<double>(0X1P-1021) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(0X1P-1022,0X1.0000000000002P-1022), I<double>(0X1P-1022,0X1.0000000000001P-1022)), I<double>(0.0,0X0.0000000000001P-1022) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(0X1P-1022,0X1.0000000000001P-1022), I<double>(0X1P-1022,0X1.0000000000002P-1022)), I<double>::entire() );


    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-0X1P+0,0X1.FFFFFFFFFFFFFP-53), I<double>(-0X1.FFFFFFFFFFFFEP-53,0X1P+0)), I<double>(-0X1.FFFFFFFFFFFFFP-1,-0X1.FFFFFFFFFFFFEP-1) );
    BOOST_CHECK_EQUAL( cancel_minus(I<double>(-0X1P+0,0X1.FFFFFFFFFFFFEP-53), I<double>(-0X1.FFFFFFFFFFFFFP-53,0X1P+0)), I<double>::entire() );
}
