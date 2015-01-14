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

#define BOOST_TEST_MODULE "Integration: Reverse elementary functions [infsup/interval, infsup/decorated_interval, p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include <limits>

#include "p1788/p1788.hpp"


const double INF_D = std::numeric_limits<double>::infinity();
const double INF_F = std::numeric_limits<float>::infinity();



template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

typedef p1788::decoration::decoration DEC;

BOOST_AUTO_TEST_CASE(integration_sqr_rev_test)
{
    BOOST_CHECK_EQUAL( sqr_rev(I<double>(0.0,1.0)), I<double>(-1.0,1.0) );
    BOOST_CHECK_EQUAL( I<double>::sqr_rev(I<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7"))), I<double>(std::stod("-0X1.999999999999BP-4"),std::stod("0X1.999999999999BP-4")) );
    BOOST_CHECK_EQUAL( I<float>::sqr_rev(I<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7"))), I<float>(std::stof("-0X1.99999AP-4"),std::stof("0X1.99999AP-4")) );

    BOOST_CHECK_EQUAL( sqr_rev(I<double>(-0.5,1.0), I<double>(-0.1,1.0)), I<double>(-0.1,1.0) );
    BOOST_CHECK_EQUAL( I<double>::sqr_rev(I<double>(0.0,25.0), I<double>(-4.1,6.0)), I<double>(-4.1,5.0) );
    BOOST_CHECK_EQUAL( I<float>::sqr_rev(I<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7")), I<float>(-0.1f,INF_F)), I<float>(-0.1f,std::stof("0X1.99999AP-4")) );

    BOOST_CHECK_EQUAL( sqr_rev(DI<double>(0.0,INF_D,DEC::dac)), DI<double>(-INF_D,INF_D,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( sqr_rev(DI<double>(0.0,INF_D,DEC::dac)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::sqr_rev(DI<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7"),DEC::com)), DI<double>(std::stod("-0X1.999999999999BP-4"),std::stod("0X1.999999999999BP-4"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::sqr_rev(DI<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7"),DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::sqr_rev(DI<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7"),DEC::def)), DI<float>(std::stof("-0X1.99999AP-4"),std::stof("0X1.99999AP-4"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::sqr_rev(DI<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7"),DEC::def)) ), DEC::trv );

    BOOST_CHECK_EQUAL( sqr_rev(DI<double>(0.0,1.0,DEC::dac), DI<double>(-0.1,1.0,DEC::def)), DI<double>(-0.1,1.0,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( sqr_rev(DI<double>(0.0,1.0,DEC::dac), DI<double>(-0.1,1.0,DEC::def)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::sqr_rev(DI<double>(0.0,25.0,DEC::def), DI<double>(-4.1,6.0,DEC::com)), DI<double>(-4.1,5.0,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::sqr_rev(DI<double>(0.0,25.0,DEC::def), DI<double>(-4.1,6.0,DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::sqr_rev(DI<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7"),DEC::dac), DI<float>(-0.1f,INF_F,DEC::dac)), DI<float>(-0.1f,std::stof("0X1.99999AP-4"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::sqr_rev(DI<double>(std::stod("0X1.47AE147AE147BP-7"),std::stod("0X1.47AE147AE147CP-7"),DEC::dac), DI<float>(-0.1f,INF_F,DEC::dac)) ), DEC::trv );
}


BOOST_AUTO_TEST_CASE(integration_abs_rev_test)
{
    BOOST_CHECK_EQUAL( abs_rev(I<double>(-1.1,2.0)), I<double>(-2.0,2.0) );
    BOOST_CHECK_EQUAL( I<double>::abs_rev(I<double>(-1.5,INF_D)), I<double>(-INF_D,INF_D) );
    BOOST_CHECK_EQUAL( I<float>::abs_rev(I<double>(-1.9,0.2)), I<float>(-0.2f,0.2f) );

    BOOST_CHECK_EQUAL( abs_rev(I<double>(-1.1,2.0), I<double>(-1.1,5.0)), I<double>(-1.1,2.0) );
    BOOST_CHECK_EQUAL( I<double>::abs_rev(I<double>(-1.9,0.2), I<double>(-1.1,5.0)), I<double>(-0.2,0.2) );
    BOOST_CHECK_EQUAL( I<float>::abs_rev(I<double>(-1.1,0.0), I<double>(-1.1,5.0)), I<float>(0.0f,0.0f) );

    BOOST_CHECK_EQUAL( abs_rev(DI<double>(-1.1,2.0,DEC::def)), DI<double>(-2.0,2.0,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( abs_rev(DI<double>(-1.1,2.0,DEC::def)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::abs_rev(DI<double>(-1.9,0.2,DEC::com)), DI<double>(-0.2,0.2,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::abs_rev(DI<double>(-1.9,0.2,DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::abs_rev(DI<double>(0.0,0.2,DEC::com)), DI<float>(-0.2f,0.2f,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::abs_rev(DI<double>(0.0,0.2,DEC::com)) ), DEC::trv );

    BOOST_CHECK_EQUAL( abs_rev(DI<double>(1.1,2.1,DEC::dac), DI<double>(-1.0,5.0,DEC::def)), DI<double>(1.1,2.1,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( abs_rev(DI<double>(1.1,2.1,DEC::dac), DI<double>(-1.0,5.0,DEC::def)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::abs_rev(DI<double>(-1.1,0.0,DEC::def), DI<double>(-1.1,5.0,DEC::def)), DI<double>(0.0,0.0,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::abs_rev(DI<double>(-1.1,0.0,DEC::def), DI<double>(-1.1,5.0,DEC::def)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::abs_rev(DI<double>(-1.1,0.0,DEC::com), DI<double>(-1.1,5.0,DEC::dac)), DI<float>(0.0f,0.0f,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::abs_rev(DI<double>(-1.1,0.0,DEC::com), DI<double>(-1.1,5.0,DEC::dac)) ), DEC::trv );
}

BOOST_AUTO_TEST_CASE(integration_pown_rev_test)
{
    BOOST_CHECK_EQUAL( pown_rev(I<double>(std::stod("-0X1.0436D2F418938P+25"),std::stod("0X1.F4P+3")), 3), I<double>(std::stod("-0x1.444cccccccccep+8"),std::stod("0x1.4p+1")) );
    BOOST_CHECK_EQUAL( I<double>::pown_rev(I<double>(std::stod("0X0P+0"),std::stod("0X0.0000000000001P-1022")), -2), I<double>(-INF_D,INF_D) );
    BOOST_CHECK_EQUAL( I<float>::pown_rev(I<double>(std::stod("0X1.5F934D64162A9P-9"),std::stod("0X1.6BCC41E9P+46")), -7), I<float>(std::stof("0x1.47ae14p-7"),std::stof("0x1.2a3d72p+1")) );

    BOOST_CHECK_EQUAL( pown_rev( I<double>(std::stod("0X1.A36E2EB1C432CP-14"),std::stod("0X1.5B7318FC50482P+2")), I<double>(1.0,INF_D), 2 ), I<double>(1.0,std::stod("0x1.2a3d70a3d70a5p+1")) );
    BOOST_CHECK_EQUAL( I<double>::pown_rev(I<double>(-INF_D,-0.0), I<double>(-1.0,1.0), -1), I<double>(-1.0,0.0) );
    BOOST_CHECK_EQUAL( I<float>::pown_rev(I<double>(std::stod("0X1.793D85EF38E47P-3"),std::stod("0X1.388P+13")), I<double>(1.0,INF_D), -2), I<float>(1.0f,std::stof("0x1.2a3d72p+1")) );

    BOOST_CHECK_EQUAL( pown_rev(DI<double>(13.1,13.1,DEC::def), 1), DI<double>(13.1,13.1,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( pown_rev(DI<double>(13.1,13.1,DEC::def), 1) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::pown_rev(DI<double>(std::stod("0X1.9D8FD495853F5P+29"),std::stod("0X1.9D8FD495853F6P+29"), DEC::com), 8), DI<double>(std::stod("-0x1.a333333333334p+3"),std::stod("0x1.a333333333334p+3"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::pown_rev(DI<double>(std::stod("0X1.9D8FD495853F5P+29"),std::stod("0X1.9D8FD495853F6P+29"), DEC::com), 8) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::pown_rev(DI<double>(std::stod("0X1.2DC80DB11AB7CP-10"),std::stod("0X1.1C37937E08P+53"),DEC::def), -8), DI<float>(std::stof("-0x1.2a3d72p+1"),std::stof("0x1.2a3d72p+1"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::pown_rev(DI<double>(std::stod("0X1.2DC80DB11AB7CP-10"),std::stod("0X1.1C37937E08P+53"),DEC::def), -8) ), DEC::trv );

    BOOST_CHECK_EQUAL( pown_rev(DI<double>(0.0,INF_D,DEC::dac), DI<double>(5.6,27.544,DEC::dac), 2), DI<double>(5.6,27.544,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( pown_rev(DI<double>(0.0,INF_D,DEC::dac), DI<double>(5.6,27.544,DEC::dac), 2) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::pown_rev(DI<double>(std::stod("0X1.793D85EF38E47P-3"),std::stod("0X1.388P+13"),DEC::com), DI<double>(1.0,INF_D,DEC::dac), -2), DI<double>(1.0,std::stod("0x1.2a3d70a3d70a5p+1"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::pown_rev(DI<double>(std::stod("0X1.793D85EF38E47P-3"),std::stod("0X1.388P+13"),DEC::com), DI<double>(1.0,INF_D,DEC::dac), -2) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::pown_rev(DI<double>(std::stod("0X1.793D85EF38E47P-3"),std::stod("0X1.388P+13"),DEC::def), DI<double>(1.0,INF_D,DEC::dac), -2), DI<float>(1.0f,std::stof("0x1.2a3d72p+1"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::pown_rev(DI<double>(std::stod("0X1.793D85EF38E47P-3"),std::stod("0X1.388P+13"),DEC::def), DI<double>(1.0,INF_D,DEC::dac), -2) ), DEC::trv );
}

BOOST_AUTO_TEST_CASE(integration_sin_rev_test)
{
    BOOST_CHECK_EQUAL( sin_rev(I<double>(-1.0,1.0)), I<double>(-INF_D, INF_D) );
    BOOST_CHECK_EQUAL( I<double>::sin_rev(I<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53"))), I<double>(-INF_D, INF_D) );
    BOOST_CHECK_EQUAL( I<float>::sin_rev(I<double>(-1.0,1.0)), I<float>(-INF_F, INF_F) );

    BOOST_CHECK_EQUAL( sin_rev(I<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53")), I<double>(3.14,3.15)), I<double>(std::stod("0X1.921FB54442D17P+1"),std::stod("0X1.921FB54442D19P+1")) );
    BOOST_CHECK_EQUAL( I<double>::sin_rev(I<double>(0.0,1.0), I<double>(-0.1,3.15)), I<double>(0.0,std::stod("0X1.921FB54442D19P+1")) );
    BOOST_CHECK_EQUAL( I<float>::sin_rev(I<double>(std::stod("-0X1.72CECE675D1FDP-52"),std::stod("-0X1.72CECE675D1FCP-52")), I<double>(3.14,3.15)), I<float>(std::stof("0x1.921fb4p+1"),std::stof("0x1.921fb6p+1")) );

    BOOST_CHECK_EQUAL( sin_rev(DI<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53"),DEC::def)), DI<double>(-INF_D, INF_D,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( sin_rev(DI<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53"),DEC::def)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::sin_rev(DI<double>(-1.0,1.0,DEC::com)), DI<double>(-INF_D, INF_D,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::sin_rev(DI<double>(-1.0,1.0,DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::sin_rev(DI<double>(-1.0,1.0,DEC::dac)), DI<float>(-INF_F, INF_F,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::sin_rev(DI<double>(-1.0,1.0,DEC::dac)) ), DEC::trv );

    BOOST_CHECK_EQUAL( sin_rev(DI<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53"),DEC::com), DI<double>(3.14,3.15,DEC::def)), DI<double>(std::stod("0X1.921FB54442D17P+1"),std::stod("0X1.921FB54442D19P+1"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( sin_rev(DI<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53"),DEC::com), DI<double>(3.14,3.15,DEC::def)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::sin_rev(DI<double>(std::stod("-0X1.72CECE675D1FDP-52"),1.0,DEC::def), DI<double>(-0.1,3.15,DEC::def)), DI<double>(std::stod("-0x1.72cece675d1fep-52"),std::stod("0X1.921FB54442D1aP+1"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::sin_rev(DI<double>(std::stod("-0X1.72CECE675D1FDP-52"),1.0,DEC::def), DI<double>(-0.1,3.15,DEC::def)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::sin_rev(DI<double>(std::stod("-0X1.72CECE675D1FDP-52"),std::stod("-0X1.72CECE675D1FCP-52"),DEC::def), DI<double>(3.14,3.15,DEC::def)), DI<float>(std::stof("0x1.921fb4p+1"),std::stof("0x1.921fb6p+1"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::sin_rev(DI<double>(std::stod("-0X1.72CECE675D1FDP-52"),std::stod("-0X1.72CECE675D1FCP-52"),DEC::def), DI<double>(3.14,3.15,DEC::def)) ), DEC::trv );
}

BOOST_AUTO_TEST_CASE(integration_cos_rev_test)
{
    BOOST_CHECK_EQUAL( cos_rev(I<double>(-1.0,1.0)), I<double>(-INF_D, INF_D) );
    BOOST_CHECK_EQUAL( I<double>::cos_rev(I<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53"))), I<double>(-INF_D, INF_D) );
    BOOST_CHECK_EQUAL( I<float>::cos_rev(I<double>(1.0,1.0)), I<float>(-INF_F,INF_F) );

    BOOST_CHECK_EQUAL( cos_rev(I<double>(std::stod("0X1.1A62633145C06P-54"),std::stod("0X1.1A62633145C07P-54")), I<double>(1.57,1.58)), I<double>(std::stod("0X1.921FB54442D17P+0"),std::stod("0X1.921FB54442D19P+0")) );
    BOOST_CHECK_EQUAL( I<double>::cos_rev(I<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1")), I<double>(3.14,3.15)), I<double>(std::stod("0x1.921fb52442d18p+1"),std::stod("0x1.921fb56442d1ap+1")) );
    BOOST_CHECK_EQUAL( I<float>::cos_rev(I<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53")), I<double>(-INF_D,1.5)), I<float>(-INF_F,std::stof("-0X1.921FB4P+0")) );

    BOOST_CHECK_EQUAL( cos_rev(DI<double>(-1.0,1.0,DEC::com)), DI<double>(-INF_D, INF_D,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( cos_rev(DI<double>(-1.0,1.0,DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::cos_rev(DI<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53"),DEC::dac)), DI<double>(-INF_D, INF_D,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::cos_rev(DI<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53"),DEC::dac)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::cos_rev(DI<double>(-1.0,1.0,DEC::com)), DI<float>(-INF_F, INF_F,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::cos_rev(DI<double>(-1.0,1.0,DEC::com)) ), DEC::trv );

    BOOST_CHECK_EQUAL( cos_rev(DI<double>(std::stod("0X1.1A62633145C06P-54"),std::stod("0X1.1A62633145C07P-54"),DEC::def), DI<double>(1.57,1.58,DEC::def)), DI<double>(std::stod("0X1.921FB54442D17P+0"),std::stod("0X1.921FB54442D19P+0"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( cos_rev(DI<double>(std::stod("0X1.1A62633145C06P-54"),std::stod("0X1.1A62633145C07P-54"),DEC::def), DI<double>(1.57,1.58,DEC::def)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::cos_rev(DI<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1"),DEC::dac), DI<double>(3.14,3.15,DEC::def)), DI<double>(std::stod("0x1.921fb52442d18p+1"),std::stod("0x1.921fb56442d1ap+1"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::cos_rev(DI<double>(std::stod("-0X1P+0"),std::stod("-0X1.FFFFFFFFFFFFFP-1"),DEC::dac), DI<double>(3.14,3.15,DEC::def)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::cos_rev(DI<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53"),DEC::com), DI<double>(-INF_D,1.5,DEC::dac)), DI<float>(-INF_F,std::stof("-0X1.921FB4P+0"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::cos_rev(DI<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53"),DEC::com), DI<double>(-INF_D,1.5,DEC::dac)) ), DEC::trv );
}

BOOST_AUTO_TEST_CASE(integration_tan_rev_test)
{
    BOOST_CHECK_EQUAL( tan_rev(I<double>(-156.0,-12.0)), I<double>(-INF_D, INF_D) );
    BOOST_CHECK_EQUAL( I<double>::tan_rev(I<double>(0.1,0.1)), I<double>(-INF_D, INF_D) );
    BOOST_CHECK_EQUAL( I<float>::tan_rev(I<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53"))), I<float>(-INF_F, INF_F) );

    BOOST_CHECK_EQUAL( tan_rev(I<double>(std::stod("0X1.72CECE675D1FCP-52"),std::stod("0X1.72CECE675D1FDP-52")), I<double>(-3.15,3.15)), I<double>(std::stod("-0X1.921FB54442D19P+1"),std::stod("0X1.921FB54442D1aP+1")) );
    BOOST_CHECK_EQUAL( I<double>::tan_rev(I<double>(std::stod("-0X1.D02967C31+53"),std::stod("0X1.D02967C31+53")), I<double>(-1.5707965,INF_D)), I<double>(std::stod("-0x1.111858f8568f7p+0"),INF_D) );
    BOOST_CHECK_EQUAL( I<float>::tan_rev(I<double>(std::stod("0X1.D02967C31CDB4P+53"),std::stod("0X1.D02967C31CDB5P+53")), I<double>(-1.5708,1.5708)), I<float>(std::stof("-0x1.921fb6p+0"),std::stof("0x1.921fb6p+0")) );

    BOOST_CHECK_EQUAL( tan_rev(DI<double>(0.0,0.0,DEC::def)), DI<double>(-INF_D, INF_D,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( tan_rev(DI<double>(0.0,0.0,DEC::def)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::tan_rev(DI<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53"),DEC::com)), DI<double>(-INF_D, INF_D,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::tan_rev(DI<double>(std::stod("0X1.1A62633145C06P-53"),std::stod("0X1.1A62633145C07P-53"),DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::tan_rev(DI<double>(-156.0,-12.0,DEC::com)), DI<float>(-INF_F, INF_F,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::tan_rev(DI<double>(-156.0,-12.0,DEC::com)) ), DEC::trv );

    BOOST_CHECK_EQUAL( tan_rev(DI<double>(std::stod("0X1.D02967C31CDB4P+53"),std::stod("0X1.D02967C31CDB5P+53"),DEC::dac), DI<double>(-1.5708,1.5708,DEC::def)), DI<double>(std::stod("-0x1.921fb54442d1bp+0"),std::stod("0x1.921fb54442d19p+0"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( tan_rev(DI<double>(std::stod("0X1.D02967C31CDB4P+53"),std::stod("0X1.D02967C31CDB5P+53"),DEC::dac), DI<double>(-1.5708,1.5708,DEC::def)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::tan_rev(DI<double>(std::stod("-0X1.D02967C31+53"),std::stod("0X1.D02967C31+53"),DEC::def), DI<double>(-INF_D,1.5707965,DEC::def)), DI<double>(-INF_D,std::stod("0x1.111858f8568f7p+0"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::tan_rev(DI<double>(std::stod("-0X1.D02967C31+53"),std::stod("0X1.D02967C31+53"),DEC::def), DI<double>(-INF_D,1.5707965,DEC::def)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::tan_rev(DI<double>(std::stod("0X1.D02967C31CDB4P+53"),std::stod("0X1.D02967C31CDB5P+53"),DEC::trv), DI<double>(-1.5708,1.5708,DEC::trv)), DI<float>(std::stof("-0x1.921fb6p+0"),std::stof("0x1.921fb6p+0"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::tan_rev(DI<double>(std::stod("0X1.D02967C31CDB4P+53"),std::stod("0X1.D02967C31CDB5P+53"),DEC::trv), DI<double>(-1.5708,1.5708,DEC::trv)) ), DEC::trv );
}

BOOST_AUTO_TEST_CASE(integration_cosh_rev_test)
{
    BOOST_CHECK_EQUAL( cosh_rev(I<double>(1.0,1.0)), I<double>(0.0,0.0) );
    BOOST_CHECK_EQUAL( I<double>::cosh_rev(I<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432"))), I<double>(std::stod("-0X1.2C903022DD7ABP+8"),std::stod("0X1.2C903022DD7ABP+8")) );
    BOOST_CHECK_EQUAL( I<float>::cosh_rev(I<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432"))), I<float>(std::stof("-0X1.2C9032P+8"),std::stod("0X1.2C9032P+8")) );

    BOOST_CHECK_EQUAL( cosh_rev(I<double>(0.0,INF_D), I<double>(1.0,2.0)), I<double>(1.0,2.0) );
    BOOST_CHECK_EQUAL( I<double>::cosh_rev(I<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432")), I<double>(-INF_D,0.0)), I<double>(std::stod("-0X1.2C903022DD7ABP+8"),std::stod("-0x1.fffffffffffffp-1")) );
    BOOST_CHECK_EQUAL( I<float>::cosh_rev(I<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432")), I<double>(-INF_D,0.0)), I<float>(std::stof("-0X1.2C9032P+8"),std::stod("-0x1.fffffep-1")) );

    BOOST_CHECK_EQUAL( cosh_rev(DI<double>(1.0,1.0,DEC::def)), DI<double>(0.0,0.0,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( cosh_rev(DI<double>(1.0,1.0,DEC::def)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::cosh_rev(DI<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432"),DEC::com)), DI<double>(std::stod("-0X1.2C903022DD7ABP+8"),std::stod("0X1.2C903022DD7ABP+8"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::cosh_rev(DI<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432"),DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::cosh_rev(DI<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432"),DEC::com)), DI<float>(std::stof("-0X1.2C9032P+8"),std::stod("0X1.2C9032P+8"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::cosh_rev(DI<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432"),DEC::com)) ), DEC::trv );

    BOOST_CHECK_EQUAL( cosh_rev(DI<double>(0.0,INF_D,DEC::def), DI<double>(1.0,2.0,DEC::com)), DI<double>(1.0,2.0,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( cosh_rev(DI<double>(0.0,INF_D,DEC::def), DI<double>(1.0,2.0,DEC::com)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::cosh_rev(DI<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432"),DEC::com), DI<double>(-INF_D,0.0,DEC::dac)), DI<double>(std::stod("-0X1.2C903022DD7ABP+8"),std::stod("-0x1.fffffffffffffp-1"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::cosh_rev(DI<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432"),DEC::com), DI<double>(-INF_D,0.0,DEC::dac)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::cosh_rev(DI<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432"),DEC::def), DI<double>(-INF_D,0.0,DEC::def)), DI<float>(std::stof("-0X1.2C9032P+8"),std::stod("-0x1.fffffep-1"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::cosh_rev(DI<double>(std::stod("0X1.8B07551D9F55P+0"),std::stod("0X1.89BCA168970C6P+432"),DEC::def), DI<double>(-INF_D,0.0,DEC::def)) ), DEC::trv );
}


BOOST_AUTO_TEST_CASE(integration_mul_rev_test)
{
    BOOST_CHECK_EQUAL( mul_rev(I<double>(0.01, 1.1), I<double>(-2.1, 0.0)), I<double>(std::stod("-0X1.A400000000001P+7"), 0.0) );
    BOOST_CHECK_EQUAL( I<double>::mul_rev(I<double>(-2.0, -0.1), I<double>(0.01, 0.12)), I<double>(std::stod("-0X1.3333333333333P+0"), std::stod("-0X1.47AE147AE147BP-8")) );
    BOOST_CHECK_EQUAL( I<float>::mul_rev(I<double>(-2.0, -0.1), I<double>(-2.1, -0.4)), I<float>(std::stof("0X1.999998P-3"), std::stof("0X1.5P+4")) );

    BOOST_CHECK_EQUAL( mul_rev(I<double>(-2.0, -0.1), I<double>(-2.1, -0.4), I<double>(0.1,15.0)), I<double>(std::stod("0X1.999999999999AP-3"), 15.0) );
    BOOST_CHECK_EQUAL( I<double>::mul_rev(I<double>(-2.0, 1.1), I<double>(0.04, INF_D), I<double>(0.0, INF_D)), I<double>(std::stod("0X1.29E4129E4129DP-5"), INF_D) );
    BOOST_CHECK_EQUAL( I<float>::mul_rev(I<double>(-2.0, -0.1), I<double>(-2.1, -0.4), I<double>(0.1,15.0)), I<float>(std::stof("0X1.999998P-3"), 15.0f) );

    BOOST_CHECK_EQUAL( mul_rev(DI<double>(-2.0, -0.1,DEC::dac), DI<double>(-2.1, -0.4,DEC::dac)), DI<double>(std::stod("0X1.999999999999AP-3"), std::stod("0X1.5P+4"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( mul_rev(DI<double>(-2.0, -0.1,DEC::dac), DI<double>(-2.1, -0.4,DEC::dac)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::mul_rev(DI<double>( -2.0, -0.1,DEC::com), DI<double>(-2.1, 0.12,DEC::dac)), DI<double>(std::stod("-0X1.3333333333333P+0"), std::stod("0X1.5P+4"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::mul_rev(DI<double>(-2.0, -0.1,DEC::com), DI<double>(-2.1, 0.12,DEC::dac)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::mul_rev(DI<double>(-2.0, -0.1,DEC::dac), DI<double>(-2.1, -0.4,DEC::dac)), DI<float>(std::stof("0X1.999998P-3"), std::stof("0X1.5P+4"),DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::mul_rev(DI<double>(-2.0, -0.1,DEC::dac), DI<double>(-2.1, -0.4,DEC::dac)) ), DEC::trv );

    BOOST_CHECK_EQUAL( mul_rev(DI<double>(-2.0, -0.1,DEC::dac), DI<double>(-2.1, -0.4,DEC::dac), DI<double>(0.1,15.0,DEC::dac)), DI<double>(std::stod("0X1.999999999999AP-3"), 15.0,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( mul_rev(DI<double>(-2.0, -0.1,DEC::dac), DI<double>(-2.1, -0.4,DEC::dac), DI<double>(0.1,15.0,DEC::dac)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<double>::mul_rev(DI<double>(0.01, 1.1,DEC::com), DI<double>(-2.1, 0.0,DEC::dac), DI<double>(-22.0,-1.0,DEC::dac)), DI<double>(-22.0,-1.0,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<double>::mul_rev(DI<double>(0.01, 1.1,DEC::com), DI<double>(-2.1, 0.0,DEC::dac), DI<double>(-22.0,-1.0,DEC::dac)) ), DEC::trv );
    BOOST_CHECK_EQUAL( DI<float>::mul_rev(DI<double>(-2.0, -0.1,DEC::def), DI<double>(-2.1, -0.4,DEC::def), DI<double>(0.1,15.0,DEC::def)), DI<float>(std::stof("0X1.999998P-3"), 15.0f,DEC::trv) );
    BOOST_CHECK_EQUAL( decoration( DI<float>::mul_rev(DI<double>(-2.0, -0.1,DEC::def), DI<double>(-2.1, -0.4,DEC::def), DI<double>(0.1,15.0,DEC::def)) ), DEC::trv );
}
