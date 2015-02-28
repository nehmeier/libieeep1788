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

#define BOOST_TEST_MODULE "Integration: Constructors, Methods, Interval constants [infsup/interval, infsup/decorated_interval, p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"


#include <limits>

#include "p1788/p1788.hpp"

template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

typedef p1788::decoration::decoration DEC;


const double INF_D = std::numeric_limits<double>::infinity();

BOOST_AUTO_TEST_CASE(integration_default_constructor_test)
{
    p1788::exception::clear();

    BOOST_CHECK( is_empty( I<double>() ) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(integration_default_constructor_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( is_empty( DI<double>() ) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(integration_infsup_constructor_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( inf( I<double>(-1.0, 2.0) ), -1.0 );
    BOOST_CHECK_EQUAL( sup( I<double>(-1.0, 2.0) ), 2.0 );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( is_empty( I<double>(-1.0, -2.0) )  );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
}

BOOST_AUTO_TEST_CASE(integration_infsup_constructor_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( inf( DI<double>(-1.0, 2.0) ), -1.0 );
    BOOST_CHECK_EQUAL( sup( DI<double>(-1.0, 2.0) ), 2.0 );
    BOOST_CHECK_EQUAL( decoration( DI<double>(-1.0, 2.0) ), DEC::com );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( is_nai( DI<double>(-1.0, -2.0) )  );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
}


BOOST_AUTO_TEST_CASE(integration_infsup_mixedtype_constructor_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( inf( I<float>(0.1, 2.1f) ), std::stof("0X1.999998P-4") );
    BOOST_CHECK_EQUAL( sup( I<float>(0.1, 2.1f) ), 2.1f );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( is_empty( I<float>(-1.0, -2.0) )  );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
}

BOOST_AUTO_TEST_CASE(integration_infsup_mixedtype_constructor_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( inf( DI<float>(0.1, 2.1f) ), std::stof("0X1.999998P-4") );
    BOOST_CHECK_EQUAL( sup( DI<float>(0.1, 2.1f) ), 2.1f );
    BOOST_CHECK_EQUAL( decoration( DI<float>(0.1, 2.1f) ), DEC::com );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( is_nai( DI<float>(-1.0, -2.0) )  );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
}

BOOST_AUTO_TEST_CASE(integration_infsupdec_constructor_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( inf( DI<double>(-1.0, 2.0, DEC::def) ), -1.0 );
    BOOST_CHECK_EQUAL( sup( DI<double>(-1.0, 2.0, DEC::def) ), 2.0 );
    BOOST_CHECK_EQUAL( decoration( DI<double>(-1.0, 2.0, DEC::def) ), DEC::def );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( is_nai( DI<double>(-INF_D, 2.0, DEC::com) )  );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();

    BOOST_CHECK( is_nai( DI<double>(-INF_D, 2.0, static_cast<p1788::decoration::decoration>(13)) )  );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
}

BOOST_AUTO_TEST_CASE(integration_infsupdec_mixedtype_constructor_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( inf( DI<float>(0.1, 2.1f, DEC::def) ), std::stof("0X1.999998P-4") );
    BOOST_CHECK_EQUAL( sup( DI<float>(0.1, 2.1f, DEC::def) ), 2.1f );
    BOOST_CHECK_EQUAL( decoration( DI<float>(0.1, 2.1f, DEC::def) ), DEC::def );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( is_nai( DI<float>(-INF_D, 2.0, DEC::com) )  );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
    p1788::exception::clear();

    BOOST_CHECK( is_nai( DI<float>(-INF_D, 2.0, static_cast<p1788::decoration::decoration>(13)) )  );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
}

BOOST_AUTO_TEST_CASE(integration_text_constructor_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( inf( I<double>("[0.1, 2.1]_def") ), std::stod("0X1.9999999999999P-4") );
    BOOST_CHECK_EQUAL( sup( I<double>("[0.1, 2.1]_def") ), 2.1 );

    BOOST_CHECK_EQUAL( inf( I<double>("[0.1]") ), std::stod("0X1.9999999999999P-4") );
    BOOST_CHECK_EQUAL( sup( I<double>("[0.1]") ), std::stod("0X1.999999999999AP-4") );

    BOOST_CHECK_EQUAL( inf( I<double>("2.500?5") ), std::stod("0x1.3f5c28f5c28f5p+1") );
    BOOST_CHECK_EQUAL( sup( I<double>("2.500?5") ), std::stod("0x1.40a3d70a3d70bp+1") );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( is_empty( I<float>("[3.0,-1.0]") )  );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
}

BOOST_AUTO_TEST_CASE(integration_text_constructor_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( inf( DI<double>("[0.1, 2.1]_def") ), std::stod("0X1.9999999999999P-4") );
    BOOST_CHECK_EQUAL( sup( DI<double>("[0.1, 2.1]_def") ), 2.1 );
    BOOST_CHECK_EQUAL( decoration( DI<float>("[0.1, 2.1]_def") ), DEC::def );

    BOOST_CHECK_EQUAL( inf( DI<double>("[0.1]") ), std::stod("0X1.9999999999999P-4") );
    BOOST_CHECK_EQUAL( sup( DI<double>("[0.1]") ), std::stod("0X1.999999999999AP-4") );
    BOOST_CHECK_EQUAL( decoration( DI<float>("[0.1]") ), DEC::com );

    BOOST_CHECK_EQUAL( inf( DI<double>("2.500?5") ), std::stod("0x1.3f5c28f5c28f5p+1") );
    BOOST_CHECK_EQUAL( sup( DI<double>("2.500?5") ), std::stod("0x1.40a3d70a3d70bp+1") );
    BOOST_CHECK_EQUAL( decoration( DI<float>("2.500?5") ), DEC::com );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( is_nai( DI<float>("[3.0,-1.0]") )  );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::undefined_operation_bit);
}


BOOST_AUTO_TEST_CASE(integration_copy_constructor_test)
{
    p1788::exception::clear();

    I<double> x(-1.0, 2.0);

    BOOST_CHECK_EQUAL( inf( I<double>(x) ), -1.0 );
    BOOST_CHECK_EQUAL( sup( I<double>(x) ), 2.0 );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(integration_copy_constructor_dec_test)
{
    p1788::exception::clear();

    DI<double> x(-1.0, 2.0);

    BOOST_CHECK_EQUAL( inf( DI<double>(x) ), -1.0 );
    BOOST_CHECK_EQUAL( sup( DI<double>(x) ), 2.0 );
    BOOST_CHECK_EQUAL( decoration( DI<double>(x) ), DEC::com );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(integration_mixedtype_copy_constructor_test)
{
    p1788::exception::clear();

    I<double> x(0.1, 2.1);

    BOOST_CHECK_EQUAL( inf( I<float>(x) ), std::stof("0X1.999998P-4") );
    BOOST_CHECK_EQUAL( sup( I<float>(x) ), std::stof("0X1.0CCCCEP+1") );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(integration_mixedtype_copy_constructor_dec_test)
{
    p1788::exception::clear();

    DI<double> x(0.1, 2.1);

    BOOST_CHECK_EQUAL( inf( DI<float>(x) ), std::stof("0X1.999998P-4") );
    BOOST_CHECK_EQUAL( sup( DI<float>(x) ), std::stof("0X1.0CCCCEP+1") );
    BOOST_CHECK_EQUAL( decoration( DI<float>(x) ), DEC::com );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(integration_interval_part_test)
{
    p1788::exception::clear();
    DI<double> x(0.1, 2.1);

    BOOST_CHECK_EQUAL( I<double>(x), I<double>(0.1, 2.1) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( is_empty( I<double>(DI<double>::nai() ) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::interval_part_of_nai_bit);
}

BOOST_AUTO_TEST_CASE(integration_mixedtype_interval_part_test)
{
    p1788::exception::clear();
    DI<double> x(0.1, 2.1);

    BOOST_CHECK_EQUAL( I<float>(x), I<float>(std::stof("0X1.999998P-4"), std::stof("0X1.0CCCCEP+1")) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( is_empty( I<float>(DI<double>::nai() ) ) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::interval_part_of_nai_bit);
}

BOOST_AUTO_TEST_CASE(integration_new_dec_test)
{
    p1788::exception::clear();
    I<double> x(0.1, 2.1);

    BOOST_CHECK_EQUAL( DI<double>(x), DI<double>(0.1, 2.1) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(integration_mixedtype_new_dec_test)
{
    p1788::exception::clear();
    I<double> x(0.1, 2.1);

    BOOST_CHECK_EQUAL( DI<float>(x), DI<float>(std::stof("0X1.999998P-4"), std::stof("0X1.0CCCCEP+1")) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(integration_set_dec_test)
{
    p1788::exception::clear();
    I<double> x(0.1, 2.1);

    BOOST_CHECK_EQUAL( DI<double>(x, DEC::def), DI<double>(0.1, 2.1, DEC::def) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( is_nai( DI<double>(x, static_cast<p1788::decoration::decoration>(13)) )  );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
}

BOOST_AUTO_TEST_CASE(integration_mixedtype_set_dec_test)
{
    p1788::exception::clear();
    I<double> x(0.1, 2.1);

    BOOST_CHECK_EQUAL( DI<float>(x, DEC::def), DI<float>(std::stof("0X1.999998P-4"), std::stof("0X1.0CCCCEP+1"), DEC::def) );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    BOOST_CHECK( is_nai( DI<float>(x, static_cast<p1788::decoration::decoration>(13)) )  );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
}

BOOST_AUTO_TEST_CASE(integration_empty_test)
{
    p1788::exception::clear();

    BOOST_CHECK( is_empty( I<double>::empty() ) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(integration_empty_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( is_empty( DI<double>::empty() ) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}


BOOST_AUTO_TEST_CASE(integration_entire_test)
{
    p1788::exception::clear();

    BOOST_CHECK( is_entire( I<double>::entire() ) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(integration_entire_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK( is_entire( DI<double>::entire() ) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(integration_nai_test)
{
    p1788::exception::clear();

    BOOST_CHECK( is_nai( DI<double>::nai() ) );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);
}
