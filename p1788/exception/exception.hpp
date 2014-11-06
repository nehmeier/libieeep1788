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

#ifndef LIBIEEEP1788_P1788_EXCEPTION_EXCEPTION_HPP
#define LIBIEEEP1788_P1788_EXCEPTION_EXCEPTION_HPP

namespace p1788
{

namespace exception
{

//TODO Exception Handler!


/// \brief Bit-patterns for the different kinds of exceptions
///
/// \note The bitwise operators <c>&</c>, <c>|</c>, <c>^</c>, <c>~</c>,
/// <c>&=</c>, <c>|=</c>, <c>^=</c> are supported.
enum exception_bits
{
    good_bit = 0,                           ///<  Every thing fine
    undefined_operation_bit = 1,            ///<  No level 1 value exists
    possibly_undefined_operation_bit = 2,   ///<  Not sure if a level 1 value exists
    interval_part_of_nai_bit = 4,           ///<  A NaI is converted into a bare interval
    invalid_operand_bit = 8                 ///< Invalid input for an operation
};


// bitwise AND for exception_bits
inline exception_bits operator& (exception_bits x, exception_bits y)
{
    return exception_bits(static_cast<int>(x) & static_cast<int>(y));
}

// bitwise OR for exception_bits
inline exception_bits operator| (exception_bits x, exception_bits y)
{
    return exception_bits(static_cast<int>(x) | static_cast<int>(y));
}

// bitwise XOR for exception_bits
inline exception_bits operator^ (exception_bits x, exception_bits y)
{
    return exception_bits(static_cast<int>(x) ^ static_cast<int>(y));
}

// bitwise NOT for exception_bits
inline exception_bits operator~ (exception_bits x)
{
    return exception_bits(~static_cast<int>(x));
}

// bitwise AND assignment for exception_bits
inline exception_bits& operator&= (exception_bits& x, exception_bits y)
{
    return x = x & y;
}

// bitwise OR assignment for exception_bits
inline exception_bits& operator|= (exception_bits& x, exception_bits y)
{
    return x = x | y;
}

// bitwise NOT assignment for exception_bits
inline exception_bits& operator^= (exception_bits& x, exception_bits y)
{
    return x = x ^ y;
}


// Thread local exception state
thread_local exception_bits exception_state_ = good_bit;


/// \brief The current exception state.
///
/// \return The current exception state of the active thread.
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline exception_bits state()
{
    return exception_state_;
}

/// \brief Clears the exception state.
///
/// \return The current exception state of the active thread (= <c>good_bit</c>).
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline exception_bits clear()
{
    return exception_state_ = good_bit;
}

/// \brief Checks exception state for an undefined operation.
/// \return true if the <c>undefined_operation_bit</c> is set.
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline bool undefined_operation()
{
    return exception_state_ & undefined_operation_bit;
}

/// \brief Checks exception state for a possibly undefined operation.
/// \return true if the <c>possibly_undefined_operation_bit</c> is set.
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline bool possibly_undefined_operation()
{
    return exception_state_ & possibly_undefined_operation_bit;
}

/// \brief Checks exception state for an interval part of NaI exception.
/// \return true if the <c>interval_part_of_nai_bit</c> is set.
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline bool interval_part_of_nai()
{
    return exception_state_ & interval_part_of_nai_bit;
}

/// \brief Checks exception state for an invalid operation.
/// \return true if the <c>interval_part_of_nai_bit</c> is set.
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline bool invalid_operand()
{
    return exception_state_ & invalid_operand_bit;
}

/// \brief Adds the flag for an undefined operation to the exception state.
///
/// \return The current exception state of the active thread (= old exception state <c>| undefined_operation_bit</c>).
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline exception_bits raise_undefined_operation()
{
    return exception_state_ |= undefined_operation_bit;
}

/// \brief Adds the flag for a possibly undefined operation to the exception state.
///
/// \return The current exception state of the active thread (= old exception state <c>| possibly_undefined_operation_bit</c>).
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline exception_bits raise_possibly_undefined_operation()
{
    return exception_state_ |= possibly_undefined_operation_bit;
}

/// \brief Adds the flag for an interval part of NaI exception to the exception state.
///
/// \return The current exception state of the active thread (= old exception state <c>| interval_part_of_nai_bit</c>).
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline exception_bits raise_interval_part_of_nai()
{
    return exception_state_ |= interval_part_of_nai_bit;
}

/// \brief Adds the flag for an invalid operand to the exception state.
///
/// \return The current exception state of the active thread (= old exception state <c>| invalid_operand_bit</c>).
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline exception_bits raise_invalid_operand()
{
    return exception_state_ |= invalid_operand_bit;
}


} // namespace exception

} // namespace p1788


#endif // LIBIEEEP1788_P1788_EXCEPTION_EXCEPTION_HPP
