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

#ifndef LIBIEEEP1788_P1788_EXCEPTION_EXCEPTION_HPP
#define LIBIEEEP1788_P1788_EXCEPTION_EXCEPTION_HPP

#include <stdexcept>

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
    none_bit = 0,                           ///< No exception
    undefined_operation_bit = 1,            ///< No level 1 value exists
    possibly_undefined_operation_bit = 2,   ///< Not sure if a level 1 value exists
    interval_part_of_nai_bit = 4,           ///< A NaI is converted into a bare interval
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


// CWD specifying which exception type should be thrown
exception_bits throw_exception_cwd_ = none_bit;

/// \brief Set the control word specifying which exception type should be thrown.
///
/// \param new_state New control word
/// \return New control word
///
inline exception_bits set_throw_exception_cwd(exception_bits new_state)
{
    return (throw_exception_cwd_ = new_state);
}

/// \brief Control word specifying which exception type should be thrown.
///
/// \return exception_bits Current control word
inline exception_bits get_throw_exception_cwd()
{
    return throw_exception_cwd_;
}


/// \brief Exception class specifying an undefined operation
///
class undefined_operation_exception : public std::runtime_error
{
public:
    undefined_operation_exception()
        : std::runtime_error("Undefined operation exception!")
    { }
};

/// \brief Exception class specifying a possibly undefined operation
///
class possibly_undefined_operation_exception : public std::runtime_error
{
public:
    possibly_undefined_operation_exception()
        : std::runtime_error("possibly undefined operation exception!")
    { }
};

/// \brief Exception class specifying an interval part of NaI exception
///
class interval_part_of_nai_exception : public std::runtime_error
{
public:
    interval_part_of_nai_exception()
        : std::runtime_error("Interval part of NaI exception!")
    { }
};

/// \brief Exception class specifying an invalid operand
///
class invalid_operand_exception : public std::runtime_error
{
public:
    invalid_operand_exception()
        : std::runtime_error("Invalid operand exception!")
    { }
};



// Thread local exception state
thread_local exception_bits exception_state_ = none_bit;


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
/// \return The current exception state of the active thread (= <c>none_bit</c>).
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline exception_bits clear()
{
    return exception_state_ = none_bit;
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
/// \return The current exception state of the active thread (= old exception state <c>| undefined_operation_bit</c>) if no exception is thrown.
/// \exception undefined_operation_exception  Throws exception if the <c>undefined_operation_bit</c> is set for the <c>throw_exception_cwd</c>.
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline exception_bits signal_undefined_operation()
{
    exception_state_ |= undefined_operation_bit;

    // Throw exception if necessary
    if (throw_exception_cwd_ & undefined_operation_bit)
        throw undefined_operation_exception();

    return exception_state_;
}

/// \brief Adds the flag for a possibly undefined operation to the exception state.
///
/// \return The current exception state of the active thread (= old exception state <c>| possibly_undefined_operation_bit</c>) if no exception is thrown.
/// \exception possibly_undefined_operation_exception  Throws exception if the <c>possibly_undefined_operation_bit</c> is set for the <c>throw_exception_cwd</c>.
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline exception_bits signal_possibly_undefined_operation()
{
    exception_state_ |= possibly_undefined_operation_bit;

    // Throw exception if necessary
    if (throw_exception_cwd_ & possibly_undefined_operation_bit)
        throw possibly_undefined_operation_exception();

    return exception_state_;
}

/// \brief Adds the flag for an interval part of NaI exception to the exception state.
///
/// \return The current exception state of the active thread (= old exception state <c>| interval_part_of_nai_bit</c>) if no exception is thrown.
/// \exception interval_part_of_nai_exception  Throws exception if the <c>interval_part_of_nai_bit</c> is set for the <c>throw_exception_cwd</c>.
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline exception_bits signal_interval_part_of_nai()
{
    exception_state_ |= interval_part_of_nai_bit;

    // Throw exception if necessary
    if (throw_exception_cwd_ & interval_part_of_nai_bit)
        throw interval_part_of_nai_exception();

    return exception_state_;
}

/// \brief Adds the flag for an invalid operand to the exception state.
///
/// \return The current exception state of the active thread (= old exception state <c>| invalid_operand_bit</c>) if no exception is thrown.
/// \exception invalid_operand_exception  Throws exception if the <c>invalid_operand_bit</c> is set for the <c>throw_exception_cwd</c>.
/// \note Thread local storage is used for the exception state.
/// See C++11 specification of <c>thread_local</c> for more details.
inline exception_bits signal_invalid_operand()
{
    exception_state_ |= invalid_operand_bit;

    // Throw exception if necessary
    if (throw_exception_cwd_ & invalid_operand_bit)
        throw invalid_operand_exception();

    return exception_state_;
}


} // namespace exception

} // namespace p1788


#endif // LIBIEEEP1788_P1788_EXCEPTION_EXCEPTION_HPP
