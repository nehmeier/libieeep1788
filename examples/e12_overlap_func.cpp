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


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//
//                     Details about extended interval comparisons
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



#include <iostream>

// libieeep1788 main header
#include "p1788/p1788.hpp"


// Template type alias to define a generic bare infsup interval with a setbased
// infsup flavor based on mpfr supporting IEEE754 bound types.
template<typename T>
using I = p1788::infsup::interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;

// and the same for decorated intervals
template<typename T>
using DI = p1788::infsup::decorated_interval<T, p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor>;


int main()
{
    // 1) There are sixteen different overlapping states encoded into an enum class overlapping_state in namespace p1788::overlapping
    std::cout << p1788::overlapping::overlapping_state::both_empty << std::endl;
    std::cout << p1788::overlapping::overlapping_state::first_empty << std::endl;
    std::cout << p1788::overlapping::overlapping_state::second_empty << std::endl;
    std::cout << p1788::overlapping::overlapping_state::before << std::endl;
    std::cout << p1788::overlapping::overlapping_state::meets << std::endl;
    std::cout << p1788::overlapping::overlapping_state::overlaps << std::endl;
    std::cout << p1788::overlapping::overlapping_state::starts << std::endl;
    std::cout << p1788::overlapping::overlapping_state::contained_by << std::endl;
    std::cout << p1788::overlapping::overlapping_state::finishes << std::endl;
    std::cout << p1788::overlapping::overlapping_state::equal << std::endl;
    std::cout << p1788::overlapping::overlapping_state::finished_by << std::endl;
    std::cout << p1788::overlapping::overlapping_state::contains << std::endl;
    std::cout << p1788::overlapping::overlapping_state::started_by << std::endl;
    std::cout << p1788::overlapping::overlapping_state::overlapped_by << std::endl;
    std::cout << p1788::overlapping::overlapping_state::met_by << std::endl;
    std::cout << p1788::overlapping::overlapping_state::after << std::endl << std::endl;

    // 1.1) For the sake of convenience it is recommended to use a typedef
    typedef p1788::overlapping::overlapping_state OLS;

    // 2) These states are returned by a (global) overlap function in namespace p1788::infsup
    std::cout << overlap( I<double>(0.0,3.5), I<double>(3.0,4.0) ) << std::endl << std::endl;

    // 2.1) and by a static function of the interval type
    std::cout << I<double>::overlap( I<double>(0.0,2.0), I<double>(3.0,4.0) )  << std::endl << std::endl;

    // 3) The overlap function is implemented for bare and decorated intervals
    std::cout << overlap( DI<double>(1.0,21.0), DI<double>(3.0,4.0) ) << std::endl << std::endl;

    // 3.1) For this case three is an additional state implemented to identify NaIs
    std::cout << OLS::undefined << std::endl;

    std::cout << DI<double>::overlap( DI<double>(0.0,2.0), DI<double>::nai() ) << std::endl << std::endl;


    // 4) Additionally there are output manipulators

    // 4.1) Lower and upper case
    std::cout << p1788::io::upper_case;
    std::cout << OLS::starts << std::endl;

    std::cout << p1788::io::lower_case;     // default
    std::cout << OLS::met_by << std::endl << std::endl;

    // 4.2) Numeric and alphabetic representation
    std::cout << p1788::io::overlapping_numeric;
    std::cout << OLS::meets << std::endl;

    std::cout << p1788::io::overlapping_alpha;     // default
    std::cout << OLS::contains << std::endl << std::endl;


    return 0;
}

