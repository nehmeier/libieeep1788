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

#define BOOST_TEST_MODULE "MPFR wrapper class [p1788/util/mpfr_var]"
#include "test/util/boost_test_wrapper.hpp"

#include <cmath>
#include <limits>
#include <string>

#include "p1788/util/mpfr_var.hpp"

template<typename T>
using mpfr_var = p1788::util::mpfr_var<
                 std::numeric_limits<T>::digits,
                 std::numeric_limits<T>::has_denorm != std::denorm_present ? std::numeric_limits<T>::min_exponent
                 : std::numeric_limits<T>::min_exponent - std::numeric_limits<T>::digits + 1,
                 std::numeric_limits<T>::max_exponent,
                 std::numeric_limits<T>::has_denorm == std::denorm_present
                 >;

BOOST_AUTO_TEST_CASE(minimal_default_constructor_test)
{
    mpfr_var<float>::setup();
    mpfr_var<float> var_float;
    BOOST_CHECK( std::isnan(var_float.template get<float>(MPFR_RNDN)) );
    BOOST_CHECK( std::isnan(var_float.template get<double>(MPFR_RNDD)) );
    BOOST_CHECK( std::isnan(var_float.template get<long double>(MPFR_RNDD)) );
    BOOST_CHECK( mpfr_nan_p( var_float() ) );

    mpfr_var<double>::setup();
    mpfr_var<double> var_double;
    BOOST_CHECK( std::isnan(var_double.template get<float>(MPFR_RNDU)) );
    BOOST_CHECK( std::isnan(var_double.template get<double>(MPFR_RNDN)) );
    BOOST_CHECK( std::isnan(var_double.template get<long double>(MPFR_RNDN)) );
    BOOST_CHECK( mpfr_nan_p( var_double() ) );
}

BOOST_AUTO_TEST_CASE(minimal_ulong_test)
{
    mpfr_var<float>::setup();
    mpfr_var<float> var_float1;
    var_float1.set(12ul, MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_float1.template get<float>(MPFR_RNDN), 12.0f );
    BOOST_CHECK_EQUAL( var_float1.template get<double>(MPFR_RNDU), 12.0 );
    BOOST_CHECK_EQUAL( var_float1.template get<long double>(MPFR_RNDU), 12.0L );
    BOOST_CHECK_EQUAL( var_float1.template get<long int>(MPFR_RNDU), 12l );
    BOOST_CHECK_EQUAL( var_float1.template get<unsigned long int>(MPFR_RNDU), 12ul );
    BOOST_CHECK(mpfr_cmp_ui(var_float1(), 12ul) == 0);

    mpfr_var<float> var_float2(47ul, MPFR_RNDU);
    BOOST_CHECK_EQUAL( var_float2.template get<float>(MPFR_RNDD), 47.0f );
    BOOST_CHECK_EQUAL( var_float2.template get<double>(MPFR_RNDN), 47.0 );
    BOOST_CHECK_EQUAL( var_float2.template get<long double>(MPFR_RNDN), 47.0L );
    BOOST_CHECK_EQUAL( var_float2.template get<long int>(MPFR_RNDN), 47l );
    BOOST_CHECK_EQUAL( var_float2.template get<unsigned long int>(MPFR_RNDN), 47ul );
    BOOST_CHECK(mpfr_cmp_ui(var_float2(), 47ul) == 0);


    mpfr_var<double>::setup();
    mpfr_var<double> var_double1;
    var_double1.set(12ul, MPFR_RNDD);
    BOOST_CHECK_EQUAL( var_double1.template get<float>(MPFR_RNDU), 12.0f );
    BOOST_CHECK_EQUAL( var_double1.template get<double>(MPFR_RNDN), 12.0 );
    BOOST_CHECK_EQUAL( var_double1.template get<long double>(MPFR_RNDN), 12.0L );
    BOOST_CHECK_EQUAL( var_double1.template get<long int>(MPFR_RNDN), 12l );
    BOOST_CHECK_EQUAL( var_double1.template get<unsigned long int>(MPFR_RNDN), 12ul );
    BOOST_CHECK(mpfr_cmp_ui(var_double1(), 12ul) == 0);

    mpfr_var<float> var_double2(47ul, MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_double2.template get<float>(MPFR_RNDN), 47.0f );
    BOOST_CHECK_EQUAL( var_double2.template get<double>(MPFR_RNDD), 47.0 );
    BOOST_CHECK_EQUAL( var_double2.template get<long double>(MPFR_RNDD), 47.0L );
    BOOST_CHECK_EQUAL( var_double2.template get<long int>(MPFR_RNDD), 47l );
    BOOST_CHECK_EQUAL( var_double2.template get<unsigned long int>(MPFR_RNDD), 47ul );
    BOOST_CHECK(mpfr_cmp_ui(var_double2(), 47ul) == 0);
}

BOOST_AUTO_TEST_CASE(minimal_long_test)
{
    mpfr_var<float>::setup();
    mpfr_var<float> var_float1;
    var_float1.set(12l, MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_float1.template get<float>(MPFR_RNDU), 12.0f );
    BOOST_CHECK_EQUAL( var_float1.template get<double>(MPFR_RNDN), 12.0 );
    BOOST_CHECK_EQUAL( var_float1.template get<long double>(MPFR_RNDN), 12.0L );
    BOOST_CHECK_EQUAL( var_float1.template get<long int>(MPFR_RNDN), 12l );
    BOOST_CHECK_EQUAL( var_float1.template get<unsigned long int>(MPFR_RNDN), 12ul );
    BOOST_CHECK(mpfr_cmp_si(var_float1(), 12l) == 0);

    mpfr_var<float> var_float2(-47l, MPFR_RNDD);
    BOOST_CHECK_EQUAL( var_float2.template get<float>(MPFR_RNDN), -47.0f );
    BOOST_CHECK_EQUAL( var_float2.template get<double>(MPFR_RNDD), -47.0 );
    BOOST_CHECK_EQUAL( var_float2.template get<long double>(MPFR_RNDD), -47.0L );
    BOOST_CHECK_EQUAL( var_float2.template get<long int>(MPFR_RNDD), -47l );
    BOOST_CHECK_EQUAL( var_float2.template get<unsigned long int>(MPFR_RNDD), 0ul);
    BOOST_CHECK(mpfr_cmp_si(var_float2(), -47l) == 0);


    mpfr_var<double>::setup();
    mpfr_var<double> var_double1;
    var_double1.set(-12l, MPFR_RNDU);
    BOOST_CHECK_EQUAL( var_double1.template get<float>(MPFR_RNDN), -12.0f );
    BOOST_CHECK_EQUAL( var_double1.template get<double>(MPFR_RNDD), -12.0 );
    BOOST_CHECK_EQUAL( var_double1.template get<long double>(MPFR_RNDD), -12.0L );
    BOOST_CHECK_EQUAL( var_double1.template get<long int>(MPFR_RNDD), -12l );
    BOOST_CHECK_EQUAL( var_double1.template get<unsigned long int>(MPFR_RNDD), 0ul );
    BOOST_CHECK(mpfr_cmp_si(var_double1(), -12l) == 0);

    mpfr_var<float> var_double2(47l, MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_double2.template get<float>(MPFR_RNDU), 47.0f );
    BOOST_CHECK_EQUAL( var_double2.template get<double>(MPFR_RNDN), 47.0 );
    BOOST_CHECK_EQUAL( var_double2.template get<long double>(MPFR_RNDN), 47.0L );
    BOOST_CHECK_EQUAL( var_double2.template get<long int>(MPFR_RNDN), 47l );
    BOOST_CHECK_EQUAL( var_double2.template get<unsigned long int>(MPFR_RNDN), 47ul );
    BOOST_CHECK(mpfr_cmp_si(var_double2(), 47l) == 0);
}

BOOST_AUTO_TEST_CASE(minimal_float_test)
{
    mpfr_var<float>::setup();
    mpfr_var<float> var_float1;
    var_float1.set(12.3f, MPFR_RNDU);
    BOOST_CHECK_EQUAL( var_float1.template get<float>(MPFR_RNDN), 12.3f );
    BOOST_CHECK_EQUAL( var_float1.template get<double>(MPFR_RNDU), 12.3f );
    BOOST_CHECK_EQUAL( var_float1.template get<long double>(MPFR_RNDU), 12.3f );
    BOOST_CHECK_EQUAL( var_float1.template get<long int>(MPFR_RNDU), 13l );
    BOOST_CHECK_EQUAL( var_float1.template get<unsigned long int>(MPFR_RNDU), 13ul );
    BOOST_CHECK(mpfr_cmp_d(var_float1(), 12.3f) == 0);

    mpfr_var<float> var_float2(-4.7f, MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_float2.template get<float>(MPFR_RNDN), -4.7f );
    BOOST_CHECK_EQUAL( var_float2.template get<double>(MPFR_RNDD), -4.7f );
    BOOST_CHECK_EQUAL( var_float2.template get<long double>(MPFR_RNDD), -4.7f );
    BOOST_CHECK_EQUAL( var_float2.template get<long int>(MPFR_RNDD), -5l );
    BOOST_CHECK_EQUAL( var_float2.template get<unsigned long int>(MPFR_RNDD), 0ul );
    BOOST_CHECK(mpfr_cmp_d(var_float2(), -4.7f) == 0);


    mpfr_var<double>::setup();
    mpfr_var<double> var_double1;
    var_double1.set(-12.3f, MPFR_RNDD);
    BOOST_CHECK_EQUAL( var_double1.template get<float>(MPFR_RNDN), -12.3f );
    BOOST_CHECK_EQUAL( var_double1.template get<double>(MPFR_RNDD), -12.3f );
    BOOST_CHECK_EQUAL( var_double1.template get<long double>(MPFR_RNDD), -12.3f );
    BOOST_CHECK_EQUAL( var_double1.template get<long int>(MPFR_RNDD), -13l );
    BOOST_CHECK_EQUAL( var_double1.template get<unsigned long int>(MPFR_RNDD), 0ul );
    BOOST_CHECK(mpfr_cmp_d(var_double1(), -12.3f) == 0);

    mpfr_var<float> var_double2(47.5f, MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_double2.template get<float>(MPFR_RNDN), 47.5f );
    BOOST_CHECK_EQUAL( var_double2.template get<double>(MPFR_RNDU), 47.5f );
    BOOST_CHECK_EQUAL( var_double2.template get<long double>(MPFR_RNDU), 47.5f );
    BOOST_CHECK_EQUAL( var_double2.template get<long int>(MPFR_RNDU), 48l );
    BOOST_CHECK_EQUAL( var_double2.template get<unsigned long int>(MPFR_RNDU), 48ul );
    BOOST_CHECK(mpfr_cmp_d(var_double2(), 47.5f) == 0);
}

BOOST_AUTO_TEST_CASE(minimal_double_test)
{
    mpfr_var<float>::setup();
    mpfr_var<float> var_float1;
    var_float1.set(12.3, MPFR_RNDD);
    BOOST_CHECK_EQUAL( var_float1.template get<float>(MPFR_RNDU), std::stof("0X1.899998P+3") );
    BOOST_CHECK_EQUAL( var_float1.template get<double>(MPFR_RNDN), std::stof("0X1.899998P+3") );
    BOOST_CHECK_EQUAL( var_float1.template get<long double>(MPFR_RNDN), std::stof("0X1.899998P+3") );
    BOOST_CHECK_EQUAL( var_float1.template get<long int>(MPFR_RNDN), 12l );
    BOOST_CHECK_EQUAL( var_float1.template get<unsigned long int>(MPFR_RNDN), 12ul );
    BOOST_CHECK(mpfr_cmp_d(var_float1(), std::stof("0X1.899998P+3")) == 0);

    mpfr_var<float> var_float2(-4.7, MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_float2.template get<float>(MPFR_RNDD), -4.7f );
    BOOST_CHECK_EQUAL( var_float2.template get<double>(MPFR_RNDN), -4.7f );
    BOOST_CHECK_EQUAL( var_float2.template get<long double>(MPFR_RNDN), -4.7f );
    BOOST_CHECK_EQUAL( var_float2.template get<long int>(MPFR_RNDN), -5l );
    BOOST_CHECK_EQUAL( var_float2.template get<unsigned long int>(MPFR_RNDN), 0ul );
    BOOST_CHECK(mpfr_cmp_d(var_float2(), -4.7f) == 0);


    mpfr_var<double>::setup();
    mpfr_var<double> var_double1;
    var_double1.set(-12.3, MPFR_RNDU);
    BOOST_CHECK_EQUAL( var_double1.template get<float>(MPFR_RNDN), -12.3f );
    BOOST_CHECK_EQUAL( var_double1.template get<double>(MPFR_RNDU), -12.3 );
    BOOST_CHECK_EQUAL( var_double1.template get<long double>(MPFR_RNDU), -12.3 );
    BOOST_CHECK_EQUAL( var_double1.template get<long int>(MPFR_RNDU), -12l );
    BOOST_CHECK_EQUAL( var_double1.template get<unsigned long int>(MPFR_RNDU), 0ul );
    BOOST_CHECK(mpfr_cmp_d(var_double1(), -12.3) == 0);

    mpfr_var<float> var_double2(47.5, MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_double2.template get<float>(MPFR_RNDN), 47.5f );
    BOOST_CHECK_EQUAL( var_double2.template get<double>(MPFR_RNDD), 47.5 );
    BOOST_CHECK_EQUAL( var_double2.template get<long double>(MPFR_RNDD), 47.5 );
    BOOST_CHECK_EQUAL( var_double2.template get<long int>(MPFR_RNDD), 47l );
    BOOST_CHECK_EQUAL( var_double2.template get<unsigned long int>(MPFR_RNDD), 47ul );
    BOOST_CHECK(mpfr_cmp_d(var_double2(), 47.5) == 0);
}

BOOST_AUTO_TEST_CASE(minimal_long_double_test)
{
    mpfr_var<float>::setup();
    mpfr_var<float> var_float1;
    var_float1.set(12.3L, MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_float1.template get<float>(MPFR_RNDN), 12.3f );
    BOOST_CHECK_EQUAL( var_float1.template get<double>(MPFR_RNDD), 12.3f );
    BOOST_CHECK_EQUAL( var_float1.template get<long double>(MPFR_RNDD), 12.3f );
    BOOST_CHECK_EQUAL( var_float1.template get<long int>(MPFR_RNDD), 12l );
    BOOST_CHECK_EQUAL( var_float1.template get<unsigned long int>(MPFR_RNDD), 12ul );
    BOOST_CHECK(mpfr_cmp_ld(var_float1(), 12.3f) == 0);

    mpfr_var<float> var_float2(-4.7L, MPFR_RNDU);
    BOOST_CHECK_EQUAL( var_float2.template get<float>(MPFR_RNDN), -4.7f );
    BOOST_CHECK_EQUAL( var_float2.template get<double>(MPFR_RNDU), -4.7f );
    BOOST_CHECK_EQUAL( var_float2.template get<long double>(MPFR_RNDU), -4.7f );
    BOOST_CHECK_EQUAL( var_float2.template get<long int>(MPFR_RNDU), -4l );
    BOOST_CHECK_EQUAL( var_float2.template get<unsigned long int>(MPFR_RNDU), 0ul );
    BOOST_CHECK(mpfr_cmp_ld(var_float2(), -4.7f) == 0);


    mpfr_var<double>::setup();
    mpfr_var<double> var_double1;
    var_double1.set(-12.3L, MPFR_RNDD);
    BOOST_CHECK_EQUAL( var_double1.template get<float>(MPFR_RNDD), -12.3f );
    BOOST_CHECK_EQUAL( var_double1.template get<double>(MPFR_RNDU), -12.3 );
    BOOST_CHECK_EQUAL( var_double1.template get<long double>(MPFR_RNDU), -12.3 );
    BOOST_CHECK_EQUAL( var_double1.template get<long int>(MPFR_RNDU), -12l );
    BOOST_CHECK_EQUAL( var_double1.template get<unsigned long int>(MPFR_RNDU), 0ul );
    BOOST_CHECK(mpfr_cmp_ld(var_double1(), -12.3) == 0);

    mpfr_var<float> var_double2(47.5L, MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_double2.template get<float>(MPFR_RNDN), 47.5f );
    BOOST_CHECK_EQUAL( var_double2.template get<double>(MPFR_RNDN), 47.5 );
    BOOST_CHECK_EQUAL( var_double2.template get<long double>(MPFR_RNDN), 47.5 );
    BOOST_CHECK_EQUAL( var_double2.template get<long int>(MPFR_RNDN), 48l );
    BOOST_CHECK_EQUAL( var_double2.template get<unsigned long int>(MPFR_RNDN), 48ul );
    BOOST_CHECK(mpfr_cmp_ld(var_double2(), 47.5) == 0);
}

BOOST_AUTO_TEST_CASE(minimal_get_str_test)
{
    mpfr_var<float>::setup();

    mpfr_var<float> var_float1(12.3, MPFR_RNDD);
    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDD, p1788::io::hex_representation, 0, 0, p1788::io::upper_case_text_representation), "0XC.4CCCCP+0" );
    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDU, p1788::io::hex_representation, 0, 3, p1788::io::lower_case_text_representation), "0xc.4cdp+0" );
    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDU, p1788::io::hex_representation, 20, 7, p1788::io::lower_case_text_representation), "      0xc.4cccc00p+0" );
    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDD, p1788::io::hex_representation, 3, 7, p1788::io::upper_case_text_representation), "0XC.4CCCC00P+0" );

    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDD, p1788::io::scientific_representation, 0, 0, p1788::io::upper_case_text_representation), "1.229999E+01" );
    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDU, p1788::io::scientific_representation, 0, 3, p1788::io::lower_case_text_representation), "1.230e+01" );
    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDU, p1788::io::scientific_representation, 20, 7, p1788::io::lower_case_text_representation), "       1.2300000e+01" );
    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDD, p1788::io::scientific_representation, 3, 7, p1788::io::upper_case_text_representation), "1.2299999E+01" );

    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDD, p1788::io::decimal_representation, 0, 0, p1788::io::upper_case_text_representation), "12.299999" );
    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDU, p1788::io::decimal_representation, 0, 3, p1788::io::lower_case_text_representation), "12.300" );
    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDU, p1788::io::decimal_representation, 20, 7, p1788::io::lower_case_text_representation), "          12.2999993" );
    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDD, p1788::io::decimal_representation, 3, 7, p1788::io::upper_case_text_representation), "12.2999992" );

    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 0, 0, p1788::io::upper_case_text_representation), "12.2999" );
    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDU, p1788::io::decimal_scientific_representation, 0, 3, p1788::io::lower_case_text_representation), "12.3" );
    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDU, p1788::io::decimal_scientific_representation, 20, 7, p1788::io::lower_case_text_representation), "                12.3" );
    BOOST_CHECK_EQUAL( var_float1.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 3, 7, p1788::io::upper_case_text_representation), "12.29999" );


    mpfr_var<float> var_float2(-0.1, MPFR_RNDU);
    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDD, p1788::io::hex_representation, 0, 0, p1788::io::upper_case_text_representation), "-0X1.999998P-4" );
    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDU, p1788::io::hex_representation, 0, 3, p1788::io::lower_case_text_representation), "-0x1.999p-4" );
    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDU, p1788::io::hex_representation, 20, 7, p1788::io::lower_case_text_representation), "     -0x1.9999980p-4" );
    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDD, p1788::io::hex_representation, 3, 7, p1788::io::upper_case_text_representation), "-0X1.9999980P-4" );

    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDU, p1788::io::scientific_representation, 0, 0, p1788::io::upper_case_text_representation), "-9.999999E-02" );
    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDU, p1788::io::scientific_representation, 0, 3, p1788::io::lower_case_text_representation), "-9.999e-02" );
    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDU, p1788::io::scientific_representation, 20, 7, p1788::io::lower_case_text_representation), "      -9.9999994e-02" );
    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDD, p1788::io::scientific_representation, 3, 7, p1788::io::upper_case_text_representation), "-9.9999995E-02" );

    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDD, p1788::io::decimal_representation, 0, 0, p1788::io::upper_case_text_representation), "-0.100000" );
    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDU, p1788::io::decimal_representation, 0, 3, p1788::io::lower_case_text_representation), "-0.099" );
    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDU, p1788::io::decimal_representation, 20, 7, p1788::io::lower_case_text_representation), "          -0.0999999" );
    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDD, p1788::io::decimal_representation, 3, 7, p1788::io::upper_case_text_representation), "-0.1000000" );

    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 0, 0, p1788::io::upper_case_text_representation), "-0.1" );
    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDU, p1788::io::decimal_scientific_representation, 0, 3, p1788::io::lower_case_text_representation), "-0.0999" );
    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDU, p1788::io::decimal_scientific_representation, 20, 7, p1788::io::lower_case_text_representation), "         -0.09999999" );
    BOOST_CHECK_EQUAL( var_float2.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 3, 7, p1788::io::upper_case_text_representation), "-0.1" );

    mpfr_var<float> var_float3;
    BOOST_CHECK_EQUAL( var_float3.get_str(MPFR_RNDD, p1788::io::hex_representation, 0, 0, p1788::io::upper_case_text_representation), "NAN" );
    BOOST_CHECK_EQUAL( var_float3.get_str(MPFR_RNDN, p1788::io::scientific_representation, 20, 7, p1788::io::lower_case_text_representation), "                 nan" );
    BOOST_CHECK_EQUAL( var_float3.get_str(MPFR_RNDU, p1788::io::decimal_representation, 3, 7, p1788::io::lower_case_text_representation), "nan" );
    BOOST_CHECK_EQUAL( var_float3.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 0, 0, p1788::io::lower_case_text_representation), "nan" );


    mpfr_var<float> var_float4(std::numeric_limits<float>::infinity(), MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_float4.get_str(MPFR_RNDD, p1788::io::hex_representation, 0, 0, p1788::io::upper_case_text_representation), "INF" );
    BOOST_CHECK_EQUAL( var_float4.get_str(MPFR_RNDN, p1788::io::scientific_representation, 20, 7, p1788::io::lower_case_text_representation), "                 inf" );
    BOOST_CHECK_EQUAL( var_float4.get_str(MPFR_RNDD, p1788::io::decimal_representation, 3, 7, p1788::io::lower_case_text_representation), "inf" );
    BOOST_CHECK_EQUAL( var_float4.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 0, 0, p1788::io::lower_case_text_representation), "inf" );

    mpfr_var<float> var_float5(-std::numeric_limits<float>::infinity(), MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_float5.get_str(MPFR_RNDD, p1788::io::hex_representation, 0, 0, p1788::io::upper_case_text_representation), "-INF" );
    BOOST_CHECK_EQUAL( var_float5.get_str(MPFR_RNDN, p1788::io::scientific_representation, 20, 7, p1788::io::lower_case_text_representation), "                -inf" );
    BOOST_CHECK_EQUAL( var_float5.get_str(MPFR_RNDD, p1788::io::decimal_representation, 3, 7, p1788::io::lower_case_text_representation), "-inf" );
    BOOST_CHECK_EQUAL( var_float5.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 0, 0, p1788::io::lower_case_text_representation), "-inf" );


    mpfr_var<double>::setup();

    mpfr_var<double> var_double1(12.3, MPFR_RNDD);
    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDD, p1788::io::hex_representation, 0, 0, p1788::io::upper_case_text_representation), "0XC.4CCCCCCCCCCDP+0" );
    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDU, p1788::io::hex_representation, 0, 3, p1788::io::lower_case_text_representation), "0xc.4cdp+0" );
    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDU, p1788::io::hex_representation, 20, 7, p1788::io::lower_case_text_representation), "      0xc.4cccccdp+0" );
    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDD, p1788::io::hex_representation, 3, 7, p1788::io::upper_case_text_representation), "0XC.4CCCCCCP+0" );

    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDD, p1788::io::scientific_representation, 0, 0, p1788::io::upper_case_text_representation), "1.230000E+01" );
    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDU, p1788::io::scientific_representation, 0, 3, p1788::io::lower_case_text_representation), "1.231e+01" );
    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDU, p1788::io::scientific_representation, 20, 7, p1788::io::lower_case_text_representation), "       1.2300001e+01" );
    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDD, p1788::io::scientific_representation, 3, 7, p1788::io::upper_case_text_representation), "1.2300000E+01" );

    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDD, p1788::io::decimal_representation, 0, 0, p1788::io::upper_case_text_representation), "12.300000" );
    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDU, p1788::io::decimal_representation, 0, 3, p1788::io::lower_case_text_representation), "12.301" );
    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDU, p1788::io::decimal_representation, 20, 7, p1788::io::lower_case_text_representation), "          12.3000001" );
    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDD, p1788::io::decimal_representation, 3, 7, p1788::io::upper_case_text_representation), "12.3000000" );

    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 0, 0, p1788::io::upper_case_text_representation), "12.3" );
    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDU, p1788::io::decimal_scientific_representation, 0, 3, p1788::io::lower_case_text_representation), "12.4" );
    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDU, p1788::io::decimal_scientific_representation, 20, 7, p1788::io::lower_case_text_representation), "            12.30001" );
    BOOST_CHECK_EQUAL( var_double1.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 3, 7, p1788::io::upper_case_text_representation), "12.3" );


    mpfr_var<double> var_double2(-0.1, MPFR_RNDU);
    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDD, p1788::io::hex_representation, 0, 0, p1788::io::upper_case_text_representation), "-0X1.999999999999AP-4" );
    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDU, p1788::io::hex_representation, 0, 3, p1788::io::lower_case_text_representation), "-0x1.999p-4" );
    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDN, p1788::io::hex_representation, 20, 7, p1788::io::lower_case_text_representation), "     -0x1.999999ap-4" );
    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDD, p1788::io::hex_representation, 3, 7, p1788::io::upper_case_text_representation), "-0X1.999999AP-4" );

    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDD, p1788::io::scientific_representation, 0, 0, p1788::io::upper_case_text_representation), "-1.000001E-01" );
    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDU, p1788::io::scientific_representation, 0, 3, p1788::io::lower_case_text_representation), "-1.000e-01" );
    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDU, p1788::io::scientific_representation, 20, 7, p1788::io::lower_case_text_representation), "      -1.0000000e-01" );
    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDD, p1788::io::scientific_representation, 3, 7, p1788::io::upper_case_text_representation), "-1.0000001E-01" );

    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDD, p1788::io::decimal_representation, 0, 0, p1788::io::upper_case_text_representation), "-0.100001" );
    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDU, p1788::io::decimal_representation, 0, 3, p1788::io::lower_case_text_representation), "-0.100" );
    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDU, p1788::io::decimal_representation, 20, 7, p1788::io::lower_case_text_representation), "          -0.1000000" );
    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDD, p1788::io::decimal_representation, 3, 7, p1788::io::upper_case_text_representation), "-0.1000001" );

    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 0, 0, p1788::io::upper_case_text_representation), "-0.100001" );
    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDU, p1788::io::decimal_scientific_representation, 0, 3, p1788::io::lower_case_text_representation), "-0.1" );
    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDU, p1788::io::decimal_scientific_representation, 20, 7, p1788::io::lower_case_text_representation), "                -0.1" );
    BOOST_CHECK_EQUAL( var_double2.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 3, 7, p1788::io::upper_case_text_representation), "-0.1000001" );


    mpfr_var<double> var_double3;
    BOOST_CHECK_EQUAL( var_double3.get_str(MPFR_RNDD, p1788::io::decimal_representation, 0, 0, p1788::io::upper_case_text_representation), "NAN" );
    BOOST_CHECK_EQUAL( var_double3.get_str(MPFR_RNDN, p1788::io::hex_representation, 20, 7, p1788::io::lower_case_text_representation), "                 nan" );
    BOOST_CHECK_EQUAL( var_double3.get_str(MPFR_RNDD, p1788::io::scientific_representation, 3, 7, p1788::io::lower_case_text_representation), "nan" );
    BOOST_CHECK_EQUAL( var_double3.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 0, 0, p1788::io::lower_case_text_representation), "nan" );

    mpfr_var<double> var_double4(std::numeric_limits<double>::infinity(), MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_double4.get_str(MPFR_RNDD, p1788::io::decimal_representation, 0, 0, p1788::io::upper_case_text_representation), "INF" );
    BOOST_CHECK_EQUAL( var_double4.get_str(MPFR_RNDN, p1788::io::hex_representation, 20, 7, p1788::io::lower_case_text_representation), "                 inf" );
    BOOST_CHECK_EQUAL( var_double4.get_str(MPFR_RNDD, p1788::io::scientific_representation, 3, 7, p1788::io::lower_case_text_representation), "inf" );
    BOOST_CHECK_EQUAL( var_double4.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 0, 0, p1788::io::lower_case_text_representation), "inf" );

    mpfr_var<double> var_double5(-std::numeric_limits<double>::infinity(), MPFR_RNDN);
    BOOST_CHECK_EQUAL( var_double5.get_str(MPFR_RNDD, p1788::io::decimal_representation, 0, 0, p1788::io::upper_case_text_representation), "-INF" );
    BOOST_CHECK_EQUAL( var_double5.get_str(MPFR_RNDN, p1788::io::hex_representation, 20, 7, p1788::io::lower_case_text_representation), "                -inf" );
    BOOST_CHECK_EQUAL( var_double5.get_str(MPFR_RNDD, p1788::io::scientific_representation, 3, 7, p1788::io::lower_case_text_representation), "-inf" );
    BOOST_CHECK_EQUAL( var_double5.get_str(MPFR_RNDD, p1788::io::decimal_scientific_representation, 0, 0, p1788::io::lower_case_text_representation), "-inf" );
}

BOOST_AUTO_TEST_CASE(minimal_subnormalize_test)
{
    // Example from MPFR documentation

    // if subnormal numbers are supported
    if (std::numeric_limits<double>::has_denorm == std::denorm_present)
    {
        mpfr_var<double>::setup();

        mpfr_var<double> a(std::stod("0x1.1235P-1021"), MPFR_RNDN);
        mpfr_var<double> b(34.3, MPFR_RNDN);
        mpfr_var<double> x(std::stod("0x0.0ffd1e99bfd04p-1022"), MPFR_RNDN);

        int t1 = mpfr_div(a(), a(), b(), MPFR_RNDN);

        BOOST_CHECK(!mpfr_equal_p(a(), x()));

        int t2 = a.subnormalize(t1, MPFR_RNDN);

        BOOST_CHECK(mpfr_equal_p(a(), x()));
        BOOST_CHECK(t1 != t2);
    }


    // only with normalized numbers

    typedef p1788::util::mpfr_var<
    std::numeric_limits<double>::digits,
        std::numeric_limits<double>::min_exponent,
        std::numeric_limits<double>::max_exponent,
        false
        > normalized_only;

    normalized_only::setup();

    // Example from MPFR documentation
    normalized_only a(std::stod("0x1.1235P-1021"), MPFR_RNDN);
    normalized_only b(34.3, MPFR_RNDN);
    normalized_only x(0.0, MPFR_RNDN);

    int t1 = mpfr_div(a(), a(), b(), MPFR_RNDN);

    BOOST_CHECK(mpfr_equal_p(a(), x()));

    int t2 = a.subnormalize(t1, MPFR_RNDN);

    BOOST_CHECK(mpfr_equal_p(a(), x()));
    BOOST_CHECK(t1 == t2);
}

BOOST_AUTO_TEST_CASE(minimal_mpfr_root_si_test)
{
    mpfr_var<double>::setup();
    mpfr_var<double> r;
    mpfr_var<double> a;
    mpfr_var<double> x;

    a.set(0x1.7DE3A077D1568p-8, MPFR_RNDN);
    x.set(0x1.a333333333334p+3, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_root_si(r(), a(), -2, MPFR_RNDU), 1);
    BOOST_CHECK(mpfr_equal_p(r(), x()));
    x.set(0x1.a333333333333p+3, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_root_si(r(), a(), -2, MPFR_RNDD), -1);
    BOOST_CHECK(mpfr_equal_p(r(), x()));

    a.set(0x1.D26DF4D8B1831p-12, MPFR_RNDN);
    x.set(0x1.a333333333334p+3, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_root_si(r(), a(), -3, MPFR_RNDU), 1);
    BOOST_CHECK(mpfr_equal_p(r(), x()));
    x.set(0x1.a333333333333p+3, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_root_si(r(), a(), -3, MPFR_RNDD), -1);
    BOOST_CHECK(mpfr_equal_p(r(), x()));

    a.set(-0x1.D26DF4D8B1831p-12, MPFR_RNDN);
    x.set(-0x1.a333333333333p+3, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_root_si(r(), a(), -3, MPFR_RNDU), 1);
    BOOST_CHECK(mpfr_equal_p(r(), x()));
    x.set(-0x1.a333333333334p+3, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_root_si(r(), a(), -3, MPFR_RNDD), -1);
    BOOST_CHECK(mpfr_equal_p(r(), x()));
}

BOOST_AUTO_TEST_CASE(minimal_mpfr_quadrant)
{
    mpfr_var<double>::setup();
    mpfr_var<double> a;
    mpz_t k;
    mpz_init(k);

    a.set(214112296674652L, MPFR_RNDN);
    p1788::util::mpfr_quadrant(k, a());
    BOOST_CHECK(mpz_cmp_ui(k, 136308121570116L) == 0);

    a.set(214112296674653L, MPFR_RNDN);
    p1788::util::mpfr_quadrant(k, a());
    BOOST_CHECK(mpz_cmp_ui(k, 136308121570117L) == 0);

    mpz_clear(k);
}

BOOST_AUTO_TEST_CASE(minimal_mpfr_asin_npi)
{
    mpfr_var<double>::setup();
    mpfr_var<double> a;
    mpfr_var<double> x;
    mpz_t npi;
    mpz_init(npi);

    mpz_set_ui(npi, 1); 
    a.set(0x1.fffffffffffffp-1, MPFR_RNDN);
    x.set(0x1.921fb58442d19p0, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_asin_npi(a(), a(), npi, MPFR_RNDU), 1);
    BOOST_CHECK(mpfr_equal_p(a(), x()));
    a.set(0x1.fffffffffffffp-1, MPFR_RNDN);
    x.set(0x1.921fb58442d18p0, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_asin_npi(a(), a(), npi, MPFR_RNDD), -1);
    BOOST_CHECK(mpfr_equal_p(a(), x()));

    mpz_clear(npi);
}

BOOST_AUTO_TEST_CASE(minimal_mpfr_acos_npi)
{
    mpfr_var<double>::setup();
    mpfr_var<double> a;
    mpfr_var<double> x;
    mpz_t npi;
    mpz_init(npi);

    mpz_set_ui(npi, 0); 
    a.set(-1.0, MPFR_RNDN);
    x.set(0x1.921fb54442d19p1, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_acos_npi(a(), a(), npi, MPFR_RNDU), 1);
    BOOST_CHECK(mpfr_equal_p(a(), x()));
    a.set(-1.0, MPFR_RNDN);
    x.set(0x1.921fb54442d18p1, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_acos_npi(a(), a(), npi, MPFR_RNDD), -1);
    BOOST_CHECK(mpfr_equal_p(a(), x()));

    mpz_set_ui(npi, 1); 
    a.set(-1.0, MPFR_RNDN);
    x.set(0x1.921fb54442d19p1, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_acos_npi(a(), a(), npi, MPFR_RNDU), 1);
    BOOST_CHECK(mpfr_equal_p(a(), x()));
    a.set(-1.0, MPFR_RNDN);
    x.set(0x1.921fb54442d18p1, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_acos_npi(a(), a(), npi, MPFR_RNDD), -1);
    BOOST_CHECK(mpfr_equal_p(a(), x()));

    mpz_clear(npi);
}

BOOST_AUTO_TEST_CASE(minimal_mpfr_atan_npi)
{
    mpfr_var<double>::setup();
    mpfr_var<double> a;
    mpfr_var<double> x;
    mpz_t npi;
    mpz_init(npi);

    mpz_set_si(npi, -1); 
    a.set(16331239353195368L, MPFR_RNDN);
    x.set(-0x1.921fb54442d18p0, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_atan_npi(a(), a(), npi, MPFR_RNDU), 1);
    BOOST_CHECK(mpfr_equal_p(a(), x()));
    a.set(16331239353195368, MPFR_RNDN);
    x.set(-0x1.921fb54442d19p0, MPFR_RNDN);
    BOOST_CHECK_EQUAL(p1788::util::mpfr_atan_npi(a(), a(), npi, MPFR_RNDD), -1);
    BOOST_CHECK(mpfr_equal_p(a(), x()));

    mpz_clear(npi);
}

