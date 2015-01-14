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

#define BOOST_TEST_MODULE "Flavor: Extended interval comparisons [p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor]"
#include "test/util/boost_test_wrapper.hpp"

#include "p1788/overlapping/overlapping.hpp"
#include "p1788/exception/exception.hpp"
#include "p1788/decoration/decoration.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor.hpp"
#include "test/util/mpfr_bin_ieee754_flavor_io_test_util.hpp"


#include <limits>


template<typename T>
using F = p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>;

template<typename T>
using REP = typename F<T>::representation;

template<typename T>
using REP_DEC = typename F<T>::representation_dec;

typedef p1788::decoration::decoration DEC;

typedef p1788::overlapping::overlapping_state OS;

const double INF_D = std::numeric_limits<double>::infinity();


BOOST_AUTO_TEST_CASE(minimal_overlap_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::overlap(F<double>::empty(), F<double>::empty()), OS::both_empty );
    BOOST_CHECK_EQUAL( F<double>::overlap(F<double>::empty(), REP<double>(1.0,2.0)), OS::first_empty );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), F<double>::empty()), OS::second_empty );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(-INF_D,2.0), REP<double>(3.0,INF_D)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(-INF_D,2.0), REP<double>(3.0,4.0)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(2.0,2.0), REP<double>(3.0,4.0)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<double>(3.0,4.0)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<double>(3.0,3.0)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(2.0,2.0), REP<double>(3.0,3.0)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(2.0,2.0), REP<double>(3.0,INF_D)), OS::before );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(-INF_D,2.0), REP<double>(2.0,3.0)), OS::meets );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<double>(2.0,3.0)), OS::meets );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<double>(2.0,INF_D)), OS::meets );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<double>(1.5,2.5)), OS::overlaps );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<double>(1.0,INF_D)), OS::starts );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<double>(1.0,3.0)), OS::starts );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,1.0), REP<double>(1.0,3.0)), OS::starts );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<double>(-INF_D,INF_D)), OS::contained_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<double>(-INF_D,3.0)), OS::contained_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<double>(0.0,3.0)), OS::contained_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(2.0,2.0), REP<double>(0.0,3.0)), OS::contained_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(2.0,2.0), REP<double>(0.0,INF_D)), OS::contained_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<double>(-INF_D,2.0)), OS::finishes );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<double>(0.0,2.0)), OS::finishes );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(2.0,2.0), REP<double>(0.0,2.0)), OS::finishes );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<double>(1.0,2.0)), OS::equal );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,1.0), REP<double>(1.0,1.0)), OS::equal );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(-INF_D,1.0), REP<double>(-INF_D,1.0)), OS::equal );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(-INF_D,INF_D), REP<double>(-INF_D,INF_D)), OS::equal );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(3.0,4.0), REP<double>(2.0,2.0)), OS::after );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(3.0,4.0), REP<double>(1.0,2.0)), OS::after );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(3.0,3.0), REP<double>(1.0,2.0)), OS::after );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(3.0,3.0), REP<double>(2.0,2.0)), OS::after );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(3.0,INF_D), REP<double>(2.0,2.0)), OS::after );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(2.0,3.0), REP<double>(1.0,2.0)), OS::met_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(2.0,3.0), REP<double>(-INF_D,2.0)), OS::met_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.5,2.5), REP<double>(1.0,2.0)), OS::overlapped_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.5,2.5), REP<double>(-INF_D,2.0)), OS::overlapped_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,INF_D), REP<double>(1.0,2.0)), OS::started_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,3.0), REP<double>(1.0,2.0)), OS::started_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,3.0), REP<double>(1.0,1.0)), OS::started_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(-INF_D,3.0), REP<double>(1.0,2.0)), OS::contains );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(-INF_D,INF_D), REP<double>(1.0,2.0)), OS::contains );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(0.0,3.0), REP<double>(1.0,2.0)), OS::contains );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(0.0,3.0), REP<double>(2.0,2.0)), OS::contains );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(-INF_D,2.0), REP<double>(1.0,2.0)), OS::finished_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(0.0,2.0), REP<double>(1.0,2.0)), OS::finished_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(0.0,2.0), REP<double>(2.0,2.0)), OS::finished_by );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,-2.4), REP<double>(1.0,2.0)), OS::undefined );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::overlap(REP<double>(1.0,2.4), REP<double>(1.0,-2.0)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_overlap_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::overlap(F<double>::empty(), F<float>::empty()), OS::both_empty );
    BOOST_CHECK_EQUAL( F<double>::overlap(F<double>::empty(), REP<float>(1.0f,2.0f)), OS::first_empty );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), F<float>::empty()), OS::second_empty );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(2.0,2.0), REP<float>(3.0f,4.0f)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<float>(3.0f,4.0f)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<float>(3.0f,3.0f)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(2.0,2.0), REP<float>(3.0f,3.0f)), OS::before );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<float>(2.0f,3.0f)), OS::meets );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<float>(1.5f,2.5f)), OS::overlaps );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<float>(1.0f,3.0f)), OS::starts );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,1.0), REP<float>(1.0f,3.0f)), OS::starts );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<float>(0.0f,3.0f)), OS::contained_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(2.0,2.0), REP<float>(0.0f,3.0f)), OS::contained_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<float>(0.0f,2.0f)), OS::finishes );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(2.0,2.0), REP<float>(0.0f,2.0f)), OS::finishes );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,2.0), REP<float>(1.0f,2.0f)), OS::equal );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,1.0), REP<float>(1.0f,1.0f)), OS::equal );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(3.0,4.0), REP<float>(2.0f,2.0f)), OS::after );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(3.0,4.0), REP<float>(1.0f,2.0f)), OS::after );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(3.0,3.0), REP<float>(1.0f,2.0f)), OS::after );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(3.0,3.0), REP<float>(2.0f,2.0f)), OS::after );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(2.0,3.0), REP<float>(1.0f,2.0f)), OS::met_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.5,2.5), REP<float>(1.0f,2.0f)), OS::overlapped_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,3.0), REP<float>(1.0f,2.0f)), OS::started_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,3.0), REP<float>(1.0f,1.0f)), OS::started_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(0.0,3.0), REP<float>(1.0f,2.0f)), OS::contains );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(0.0,3.0), REP<float>(2.0f,2.0f)), OS::contains );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(0.0,2.0), REP<float>(1.0f,2.0f)), OS::finished_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(0.0,2.0), REP<float>(2.0f,2.0f)), OS::finished_by );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK_EQUAL( F<double>::overlap(REP<double>(1.0,-2.4), REP<float>(1.0f,2.0f)), OS::undefined );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::overlap(REP<double>(1.0,2.4), REP<float>(1.0f,-2.0f)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_overlap_dec_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::overlap(F<double>::nai(), F<double>::nai()), OS::both_nai );
    BOOST_CHECK_EQUAL( F<double>::overlap(F<double>::nai(), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)), OS::first_nai );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::dac), F<double>::nai()), OS::second_nai );

    BOOST_CHECK_EQUAL( F<double>::overlap(F<double>::empty_dec(), F<double>::empty_dec()), OS::both_empty );
    BOOST_CHECK_EQUAL( F<double>::overlap(F<double>::empty_dec(), REP_DEC<double>(REP<double>(1.0,2.0),DEC::com)), OS::first_empty );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::def), F<double>::empty_dec()), OS::second_empty );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(2.0,2.0),DEC::def), REP_DEC<double>(REP<double>(3.0,4.0),DEC::def)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::dac), REP_DEC<double>(REP<double>(3.0,4.0),DEC::com)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::com), REP_DEC<double>(REP<double>(3.0,3.0),DEC::trv)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(2.0,2.0),DEC::trv), REP_DEC<double>(REP<double>(3.0,3.0),DEC::def)), OS::before );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::def), REP_DEC<double>(REP<double>(2.0,3.0),DEC::def)), OS::meets );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::dac), REP_DEC<double>(REP<double>(1.5,2.5),DEC::def)), OS::overlaps );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::def), REP_DEC<double>(REP<double>(1.0,3.0),DEC::com)), OS::starts );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,1.0),DEC::trv), REP_DEC<double>(REP<double>(1.0,3.0),DEC::def)), OS::starts );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::def), REP_DEC<double>(REP<double>(0.0,3.0),DEC::dac)), OS::contained_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(2.0,2.0),DEC::trv), REP_DEC<double>(REP<double>(0.0,3.0),DEC::def)), OS::contained_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv), REP_DEC<double>(REP<double>(0.0,2.0),DEC::com)), OS::finishes );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(2.0,2.0),DEC::def), REP_DEC<double>(REP<double>(0.0,2.0),DEC::dac)), OS::finishes );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::def), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)), OS::equal );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,1.0),DEC::dac), REP_DEC<double>(REP<double>(1.0,1.0),DEC::dac)), OS::equal );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(3.0,4.0),DEC::trv), REP_DEC<double>(REP<double>(2.0,2.0),DEC::trv)), OS::after );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(3.0,4.0),DEC::def), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)), OS::after );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(3.0,3.0),DEC::com), REP_DEC<double>(REP<double>(1.0,2.0),DEC::dac)), OS::after );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(3.0,3.0),DEC::def), REP_DEC<double>(REP<double>(2.0,2.0),DEC::trv)), OS::after );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(2.0,3.0),DEC::def), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)), OS::met_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.5,2.5),DEC::com), REP_DEC<double>(REP<double>(1.0,2.0),DEC::com)), OS::overlapped_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,3.0),DEC::dac), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)), OS::started_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,3.0),DEC::com), REP_DEC<double>(REP<double>(1.0,1.0),DEC::dac)), OS::started_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(0.0,3.0),DEC::com), REP_DEC<double>(REP<double>(1.0,2.0),DEC::dac)), OS::contains );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(0.0,3.0),DEC::com), REP_DEC<double>(REP<double>(2.0,2.0),DEC::def)), OS::contains );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(0.0,2.0),DEC::def), REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv)), OS::finished_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(0.0,2.0),DEC::dac), REP_DEC<double>(REP<double>(2.0,2.0),DEC::def)), OS::finished_by );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,-2.4),DEC::trv), REP_DEC<double>(REP<double>(1.0,2.0),DEC::def)), OS::undefined );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.4),DEC::ill), REP_DEC<double>(REP<double>(1.0,-2.0),DEC::def)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}

BOOST_AUTO_TEST_CASE(minimal_overlap_dec_mixedtype_test)
{
    p1788::exception::clear();

    BOOST_CHECK_EQUAL( F<double>::overlap(F<double>::nai(), F<float>::nai()), OS::both_nai );
    BOOST_CHECK_EQUAL( F<double>::overlap(F<double>::nai(), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::trv)), OS::first_nai );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::def), F<float>::nai()), OS::second_nai );

    BOOST_CHECK_EQUAL( F<double>::overlap(F<double>::empty_dec(), F<float>::empty_dec()), OS::both_empty );
    BOOST_CHECK_EQUAL( F<double>::overlap(F<double>::empty_dec(), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::def)), OS::first_empty );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::def), F<float>::empty_dec()), OS::second_empty );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(2.0,2.0),DEC::def), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::trv)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::dac), REP_DEC<float>(REP<float>(3.0f,4.0f),DEC::def)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::dac), REP_DEC<float>(REP<float>(3.0f,3.0f),DEC::dac)), OS::before );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(2.0,2.0),DEC::def), REP_DEC<float>(REP<float>(3.0f,3.0f),DEC::com)), OS::before );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv), REP_DEC<float>(REP<float>(2.0f,3.0f),DEC::dac)), OS::meets );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv), REP_DEC<float>(REP<float>(1.5f,2.5f),DEC::dac)), OS::overlaps );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::def), REP_DEC<float>(REP<float>(1.0f,3.0f),DEC::trv)), OS::starts );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,1.0),DEC::dac), REP_DEC<float>(REP<float>(1.0f,3.0f),DEC::com)), OS::starts );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::com), REP_DEC<float>(REP<float>(0.0f,3.0f),DEC::def)), OS::contained_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(2.0,2.0),DEC::com), REP_DEC<float>(REP<float>(0.0f,3.0f),DEC::dac)), OS::contained_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::dac), REP_DEC<float>(REP<float>(0.0f,2.0f),DEC::dac)), OS::finishes );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(2.0,2.0),DEC::def), REP_DEC<float>(REP<float>(0.0f,2.0f),DEC::dac)), OS::finishes );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.0),DEC::trv), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::def)), OS::equal );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,1.0),DEC::def), REP_DEC<float>(REP<float>(1.0f,1.0f),DEC::trv)), OS::equal );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(3.0,4.0),DEC::dac), REP_DEC<float>(REP<float>(2.0f,2.0f),DEC::def)), OS::after );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(3.0,4.0),DEC::def), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::com)), OS::after );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(3.0,3.0),DEC::dac), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::com)), OS::after );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(3.0,3.0),DEC::def), REP_DEC<float>(REP<float>(2.0f,2.0f),DEC::def)), OS::after );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(2.0,3.0),DEC::com), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::dac)), OS::met_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.5,2.5),DEC::def), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::def)), OS::overlapped_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,3.0),DEC::com), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::def)), OS::started_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,3.0),DEC::com), REP_DEC<float>(REP<float>(1.0f,1.0f),DEC::dac)), OS::started_by );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(0.0,3.0),DEC::def), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::com)), OS::contains );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(0.0,3.0),DEC::trv), REP_DEC<float>(REP<float>(2.0f,2.0f),DEC::trv)), OS::contains );

    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(0.0,2.0),DEC::dac), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::dac)), OS::finished_by );
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(0.0,2.0),DEC::dac), REP_DEC<float>(REP<float>(2.0f,2.0f),DEC::def)), OS::finished_by );

    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::none_bit);

    p1788::exception::clear();
    BOOST_CHECK_EQUAL( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,-2.4),DEC::dac), REP_DEC<float>(REP<float>(1.0f,2.0f),DEC::dac)), OS::undefined );
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::invalid_operand_bit);
    BOOST_CHECK_THROW( F<double>::overlap(REP_DEC<double>(REP<double>(1.0,2.4),DEC::trv), REP_DEC<float>(REP<float>(1.0f,-2.0f),DEC::trv)), p1788::exception::invalid_operand_exception);
    BOOST_CHECK_EQUAL(p1788::exception::state(), p1788::exception::invalid_operand_bit);
    p1788::exception::clear();
    p1788::exception::set_throw_exception_cwd(p1788::exception::none_bit);
}
