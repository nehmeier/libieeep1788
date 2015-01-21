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
//                     Details about exception handling
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
    std::cout << std::boolalpha;    // activate textual output of boolean values

    I<double>(2.0,-1.0);            // raise the undefined operation exception
    I<double>(DI<double>::nai());   // raise the interval part of nai exception


    // 1) There are five different exception states encoded into an enum exception_bits in namespace p1788::exception
    std::cout << p1788::exception::none_bit << std::endl;
    std::cout << p1788::exception::undefined_operation_bit << std::endl;
    std::cout << p1788::exception::possibly_undefined_operation_bit << std::endl;
    std::cout << p1788::exception::interval_part_of_nai_bit << std::endl;
    std::cout << p1788::exception::invalid_operand_bit << std::endl << std::endl;

    // 2) These five exception states are used to encode the occured exceptions in a sticky (thread local) state variable
    //    which can be accessed by a function in namespace p1788::exception
    std::cout << p1788::exception::state() << std::endl;

    // 2.1) These state can be used to perform bitwise operations to check the occured state
    std::cout << static_cast<bool>(p1788::exception::state() & p1788::exception::undefined_operation_bit) << std::endl;
    std::cout << static_cast<bool>(p1788::exception::state() & p1788::exception::interval_part_of_nai_bit) << std::endl;
    std::cout << static_cast<bool>(p1788::exception::state() & p1788::exception::invalid_operand_bit) << std::endl << std::endl;

    // 2.2) For the sake of convenience there are functions in namespace p1788::exception to check the individual states
    std::cout << p1788::exception::undefined_operation() << std::endl;
    std::cout << p1788::exception::possibly_undefined_operation() << std::endl;
    std::cout << p1788::exception::interval_part_of_nai() << std::endl;
    std::cout << p1788::exception::invalid_operand() << std::endl << std::endl;

    // 3) Due to the fact that the exception state variable is sticky there exists a function to reset the exception state.
    p1788::exception::clear();

    std::cout << p1788::exception::state() << std::endl << std::endl;


    // 4) The default behavior is exception free (no exception is thrown) and only the sticky exception state is used.
    //    But there is also the opportunity to enable the throwing of individual exceptions
    p1788::exception::set_throw_exception_cwd(p1788::exception::interval_part_of_nai_bit    // Throw exceptions for interval part of nai
            | p1788::exception::invalid_operand_bit);     // and invalid operand. All other exceptions are are non-throwing

    // 4.1) And there are four different exception types
    try
    {
        I<double>(2.0,-1.0);            // non throwing
        std::cout << p1788::exception::state() << std::endl;

        I<double>(DI<double>::nai());   // throwing
    }
    catch (p1788::exception::undefined_operation_exception& e)
    {
    }
    catch (p1788::exception::possibly_undefined_operation_exception& e)
    {
    }
    catch (p1788::exception::interval_part_of_nai_exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (p1788::exception::invalid_operand_exception& e)
    {
    }


    // 4.2) which are all derived for p1788::exception::exception
    try
    {
        I<double>(DI<double>::nai());   // throwing
    }
    catch (p1788::exception::exception& e)
    {
        std::cout << e.what() << std::endl;
    }


    return 0;
}

