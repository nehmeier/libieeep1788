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

#ifndef LIBIEEEP1788_P1788_IO_IO_MANIP_HPP
#define LIBIEEEP1788_P1788_IO_IO_MANIP_HPP

#include <iostream>

#include "p1788/util/io.hpp"

namespace p1788
{

namespace io
{

// Unique ID for a manipulator to choose between lower and upper case
int const text_representation_manip_id =  std::ios_base::xalloc();

enum text_representation_flags
{
    lower_case_text_representation,
    first_upper_case_text_representation,
    upper_case_text_representation
};

///@name Output manipulators to choose between lower and upper case text representation.
///
/// Default manipulator is \link lower_case(std::basic_ostream<CharT, Traits>& os) lower_case \endlink .
///
///@{

/// \brief Output manipulator to print the text representation in lower case.
/// \param os Output stream which should be manipulated
/// \return Output stream \p os to support operator chaining
///
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& lower_case(std::basic_ostream<CharT, Traits>& os)
{
    os.iword(text_representation_manip_id) = lower_case_text_representation;
    return os;
}

/// \brief Output manipulator to print the first character of a text representation in upper case.
/// \param os Output stream which should be manipulated
/// \return Output stream \p os to support operator chaining
///
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& upper_case(std::basic_ostream<CharT, Traits>& os)
{
    os.iword(text_representation_manip_id) = upper_case_text_representation;
    return os;
}

/// \brief Output manipulator to print the text representation in upper case.
/// \param os Output stream which should be manipulated
/// \return Output stream \p os to support operator chaining
///
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& first_upper_case(std::basic_ostream<CharT, Traits>& os)
{
    os.iword(text_representation_manip_id) = first_upper_case_text_representation;
    return os;
}

///@}



// Unique ID for a manipulator to choose the preferred string width of an interval
int const string_width_manip_id =  std::ios_base::xalloc();

///@name Output manipulators to choose the preferred string width of an interval.
///
/// Default manipulator is \link string_width(0) \endlink .
///
///@{

/// \brief Class used as an output manipulator to set the preferred string width of an interval.
struct string_width
{
    unsigned int width_;

    string_width(unsigned int width) : width_(width) {}
};

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<< (std::basic_ostream<CharT, Traits>& os, string_width const& w)
{
    os.iword(string_width_manip_id) = w.width_;
    return os;
}

///@}



// Unique ID for a manipulator to choose between inf sup and uncertain representation
int const representation_manip_id =  std::ios_base::xalloc();

enum representation_flags
{
    inf_sup_representation,
    uncertain_representation
};

///@name Output manipulators to choose between inf sup and uncertain representation.
///
/// Default manipulator is \link inf_sup_form(std::basic_ostream<CharT, Traits>& os) inf_sup_form \endlink .
///
///@{

/// \brief Output manipulator to print intervals in inf sup form.
/// \param os Output stream which should be manipulated
/// \return Output stream \p os to support operator chaining
///
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& inf_sup_form(std::basic_ostream<CharT, Traits>& os)
{
    os.iword(representation_manip_id) = inf_sup_representation;
    return os;
}

/// \brief Output manipulator to print intervals in uncertain form.
/// \param os Output stream which should be manipulated
/// \return Output stream \p os to support operator chaining
///
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& uncertain_form(std::basic_ostream<CharT, Traits>& os)
{
    os.iword(representation_manip_id) = uncertain_representation;
    return os;
}

///@}



// Unique ID for a manipulator to choose between different text representaions for special intervals
int const special_representation_manip_id =  std::ios_base::xalloc();

enum interval_special_representation_flags
{
    text_special_representation,
    bounds_special_representation,
    no_bounds_special_representation
};

///@name Output manipulators to choose between different text representaions for special intervals.
///
/// Default manipulator is \link special_text(std::basic_ostream<CharT, Traits>& os) special_text \endlink .
///
///@{

/// \brief Output manipulator to print a textual representation for special intervals.
/// \param os Output stream which should be manipulated
/// \return Output stream \p os to support operator chaining
///
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& special_text(std::basic_ostream<CharT, Traits>& os)
{
    os.iword(special_representation_manip_id) = text_special_representation;
    return os;
}

/// \brief Output manipulator to print the bounds for special intervals.
/// \param os Output stream which should be manipulated
/// \return Output stream \p os to support operator chaining
///
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& special_bounds(std::basic_ostream<CharT, Traits>& os)
{
    os.iword(special_representation_manip_id) = bounds_special_representation;
    return os;
}

/// \brief Output manipulator to print special intervals without bounds.
/// \param os Output stream which should be manipulated
/// \return Output stream \p os to support operator chaining
///
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& special_no_bounds(std::basic_ostream<CharT, Traits>& os)
{
    os.iword(special_representation_manip_id) = no_bounds_special_representation;
    return os;
}

///@}



// Unique ID for a manipulator to choose between interval representaions with or without punctuation
int const punctuation_manip_id =  std::ios_base::xalloc();

enum interval_punctuation_flags
{
    show_punctuation,
    show_no_punctuation
};

///@name Output manipulators to choose between interval representaions with or without punctuation.
///
/// Default manipulator is \link punctuation(std::basic_ostream<CharT, Traits>& os) punctuation \endlink .
///
///@{

/// \brief Output manipulator to print a textual representation with punctuation.
/// \param os Output stream which should be manipulated
/// \return Output stream \p os to support operator chaining
///
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& punctuation(std::basic_ostream<CharT, Traits>& os)
{
    os.iword(punctuation_manip_id) = show_punctuation;
    return os;
}

/// \brief Output manipulator to print a textual representation without punctuation.
/// \param os Output stream which should be manipulated
/// \return Output stream \p os to support operator chaining
///
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& no_punctuation(std::basic_ostream<CharT, Traits>& os)
{
    os.iword(punctuation_manip_id) = show_no_punctuation;
    return os;
}


///@}

//-----------------------------------------------------------------------------
//  Decoration specific
//-----------------------------------------------------------------------------

// Unique ID for a manipulator to print decorations
int const dec_manip_id =  std::ios_base::xalloc();

// enum for the manipulator to print decorations
enum dec_manip_flags
{
    dec_alpha_representation,
    dec_numeric_representation
};

///@name Decoration specific Output manipulators
///
/// Default manipulator is \link dec_alpha(std::basic_ostream<CharT, Traits>& os) dec_alpha \endlink .
///
///@{


/// \brief Output manipulator to use the text representation for decorations.
/// \param os Output stream which should be manipulated
/// \return Output stream \p os to support operator chaining
///
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& dec_alpha(std::basic_ostream<CharT, Traits>& os)
{
    os.iword(dec_manip_id) = dec_alpha_representation;
    return os;
}

/// \brief IO manipulator to use the numeric representation for decorations.
/// \param os Output stream which should be manipulated
/// \return Output stream \p os to support operator chaining
///
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& dec_numeric(std::basic_ostream<CharT, Traits>& os)
{
    os.iword(dec_manip_id) = dec_numeric_representation;
    return os;
}

///@}



} // namespace io

} // namespace p1788


#endif // LIBIEEEP1788_P1788_IO_IO_MANIP_HPP
