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

#define BOOST_TEST_MODULE "Integration: Numeric functions on intervals [infsup/interval, infsup/decorated_interval, p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include <limits>

#include "p1788/p1788.hpp"

template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

const double MAX_D = std::numeric_limits<double>::max();
const double DNORM_MIN_D = std::numeric_limits<double>::denorm_min();

const float INF_F = std::numeric_limits<float>::infinity();


BOOST_AUTO_TEST_CASE(integration_inf_test)
{
    BOOST_CHECK_EQUAL( inf(I<double>(DNORM_MIN_D, 2.0)), DNORM_MIN_D );
    BOOST_CHECK_EQUAL( I<double>::inf(I<double>(DNORM_MIN_D, 2.0)), DNORM_MIN_D );
    BOOST_CHECK_EQUAL( I<float>::inf(I<double>(DNORM_MIN_D, 2.0)), 0.0f );

    BOOST_CHECK_EQUAL( inf(DI<double>(DNORM_MIN_D, 2.0)), DNORM_MIN_D );
    BOOST_CHECK_EQUAL( DI<double>::inf(DI<double>(DNORM_MIN_D, 2.0)), DNORM_MIN_D );
    BOOST_CHECK_EQUAL( DI<float>::inf(DI<double>(DNORM_MIN_D, 2.0)), 0.0f );
}

BOOST_AUTO_TEST_CASE(integration_sup_test)
{
    BOOST_CHECK_EQUAL( sup(I<double>(0.0, MAX_D)), MAX_D );
    BOOST_CHECK_EQUAL( I<double>::sup(I<double>(0.0, MAX_D)), MAX_D );
    BOOST_CHECK_EQUAL( I<float>::sup(I<double>(0.0, MAX_D)), INF_F );

    BOOST_CHECK_EQUAL( sup(DI<double>(0.0, MAX_D)), MAX_D );
    BOOST_CHECK_EQUAL( DI<double>::sup(DI<double>(0.0, MAX_D)), MAX_D );
    BOOST_CHECK_EQUAL( DI<float>::sup(DI<double>(0.0, MAX_D)), INF_F );
}

BOOST_AUTO_TEST_CASE(integration_mid_test)
{
    BOOST_CHECK_EQUAL( mid(I<double>(0.0, 2.0)), 1.0 );
    BOOST_CHECK_EQUAL( I<double>::mid(I<double>(0.0, 2.0)), 1.0 );
    BOOST_CHECK_EQUAL( I<float>::mid(I<double>(std::stod("0X1.FFFFD90000000P+0"),std::stod("0X1.FFFFD90000001P+0"))), std::stof("0X1.FFFFDAP+0") );

    BOOST_CHECK_EQUAL( mid(DI<double>(0.0, 2.0)), 1.0 );
    BOOST_CHECK_EQUAL( DI<double>::mid(DI<double>(0.0, 2.0)), 1.0 );
    BOOST_CHECK_EQUAL( DI<float>::mid(DI<double>(std::stod("0X1.FFFFD90000000P+0"),std::stod("0X1.FFFFD90000001P+0"))), std::stof("0X1.FFFFDAP+0") );
}

BOOST_AUTO_TEST_CASE(integration_rad_test)
{
    BOOST_CHECK_EQUAL( rad(I<double>(0.0, 2.0)), 1.0 );
    BOOST_CHECK_EQUAL( I<double>::rad(I<double>(0.0, 2.0)), 1.0 );
    BOOST_CHECK_EQUAL( I<float>::rad(I<double>(std::stod("0X1.FFFFFCP+127"), std::stod("0X1.FFFFFFP+127"))), std::stof("0X1P+104") );

    BOOST_CHECK_EQUAL( rad(DI<double>(0.0, 2.0)), 1.0 );
    BOOST_CHECK_EQUAL( DI<double>::rad(DI<double>(0.0, 2.0)), 1.0 );
    BOOST_CHECK_EQUAL( DI<float>::rad(DI<double>(std::stod("0X1.FFFFFCP+127"), std::stod("0X1.FFFFFFP+127"))), std::stof("0X1P+104") );
}

BOOST_AUTO_TEST_CASE(integration_mid_rad_test)
{
    BOOST_CHECK_EQUAL( mid_rad(I<double>(0.0, 2.0)).first, 1.0 );
    BOOST_CHECK_EQUAL( mid_rad(I<double>(0.0, 2.0)).second, 1.0 );
    BOOST_CHECK_EQUAL( I<double>::mid_rad(I<double>(0.0, 2.0)).first, 1.0 );
    BOOST_CHECK_EQUAL( I<double>::mid_rad(I<double>(0.0, 2.0)).second, 1.0 );
    BOOST_CHECK_EQUAL( I<float>::mid_rad(I<double>(std::stod("0X1.FFFFD90000000P+0"),std::stod("0X1.FFFFD90000001P+0"))).first, std::stof("0X1.FFFFDAP+0") );
    BOOST_CHECK_EQUAL( I<float>::mid_rad(I<double>(std::stod("0X1.FFFFFCP+127"),std::stod("0X1.FFFFFFP+127"))).second, std::stof("0X1P+104") );

    BOOST_CHECK_EQUAL( mid_rad(DI<double>(0.0, 2.0)).first, 1.0 );
    BOOST_CHECK_EQUAL( mid_rad(DI<double>(0.0, 2.0)).second, 1.0 );
    BOOST_CHECK_EQUAL( DI<double>::mid_rad(DI<double>(0.0, 2.0)).first, 1.0 );
    BOOST_CHECK_EQUAL( DI<double>::mid_rad(DI<double>(0.0, 2.0)).second, 1.0 );
    BOOST_CHECK_EQUAL( DI<float>::mid_rad(DI<double>(std::stod("0X1.FFFFD90000000P+0"),std::stod("0X1.FFFFD90000001P+0"))).first, std::stof("0X1.FFFFDAP+0") );
    BOOST_CHECK_EQUAL( DI<float>::mid_rad(DI<double>(std::stod("0X1.FFFFFCP+127"),std::stod("0X1.FFFFFFP+127"))).second, std::stof("0X1P+104") );
}

BOOST_AUTO_TEST_CASE(integration_wid_test)
{
    BOOST_CHECK_EQUAL( wid(I<double>(0.0, 2.0)), 2.0 );
    BOOST_CHECK_EQUAL( I<double>::wid(I<double>(0.0, 2.0)), 2.0 );
    BOOST_CHECK_EQUAL( I<float>::wid(I<double>(std::stod("0X1P-1022"), std::stod("0X1.0000000000001P-1022"))), std::stof("0X1P-149") );

    BOOST_CHECK_EQUAL( wid(DI<double>(0.0, 2.0)), 2.0 );
    BOOST_CHECK_EQUAL( DI<double>::wid(DI<double>(0.0, 2.0)), 2.0 );
    BOOST_CHECK_EQUAL( DI<float>::wid(DI<double>(std::stod("0X1P-1022"), std::stod("0X1.0000000000001P-1022"))), std::stof("0X1P-149") );
}

BOOST_AUTO_TEST_CASE(integration_mag_test)
{
    BOOST_CHECK_EQUAL( mag(I<double>(0.0, 2.0)), 2.0 );
    BOOST_CHECK_EQUAL( I<double>::mag(I<double>(0.0, 2.0)), 2.0 );
    BOOST_CHECK_EQUAL( I<float>::mag(I<double>(std::stod("0X1P-1022"), std::stod("0X1.0000000000001P-1022"))), std::stof("0X1P-149") );

    BOOST_CHECK_EQUAL( mag(DI<double>(0.0, 2.0)), 2.0 );
    BOOST_CHECK_EQUAL( DI<double>::mag(DI<double>(0.0, 2.0)), 2.0 );
    BOOST_CHECK_EQUAL( DI<float>::mag(DI<double>(std::stod("0X1P-1022"), std::stod("0X1.0000000000001P-1022"))), std::stof("0X1P-149") );
}

BOOST_AUTO_TEST_CASE(integration_mig_test)
{
    BOOST_CHECK_EQUAL( mig(I<double>(0.0, 2.0)), 0.0 );
    BOOST_CHECK_EQUAL( I<double>::mig(I<double>(0.0, 2.0)), 0.0 );
    BOOST_CHECK_EQUAL( I<float>::mig(I<double>(std::stod("0X1P-1022"), std::stod("0X1.0000000000001P-1022"))), 0.0f );

    BOOST_CHECK_EQUAL( mig(DI<double>(0.0, 2.0)), 0.0 );
    BOOST_CHECK_EQUAL( DI<double>::mig(DI<double>(0.0, 2.0)), 0.0 );
    BOOST_CHECK_EQUAL( DI<float>::mig(DI<double>(std::stod("0X1P-1022"), std::stod("0X1.0000000000001P-1022"))), 0.0f );
}
