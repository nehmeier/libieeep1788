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

#ifndef LIBIEEEP1788_P1788_DECORATION_DECORATION_HPP
#define LIBIEEEP1788_P1788_DECORATION_DECORATION_HPP

#include <iostream>
#include <algorithm>
#include <cstdint>

#include "p1788/io/io_manip.hpp"
#include "p1788/util/io.hpp"


namespace p1788
{

namespace decoration
{

/// \brief Enum describing the 5 different interval decorations
///
/// The 5 different values are an ordered set with the following
/// property
///
/// <c>com</c> > <c>dac</c> > <c>def</c> > <c>trv</c> > <c>ill</c>
///
/// and the common comparison operators (<c>==</c>, <c>!=</c>, <c><</c>, <c><=</c>, <c>></c>, <c>>=</c>)
/// are supported.
///
/// \note To follow the interchange representations specified by IEEE P1788
/// the decoration enum is based on an unsigned 8Bit integer using the
/// the corresponding Bit patterns for the particular values.
enum class decoration : uint8_t
{
    ill = 0x00,    ///< ill (00000000)
    trv = 0x04,    ///< trivial (00000100)
    def = 0x08,    ///< defined (00001000)
    dac = 0x0C,   ///< defined and continuous (00001100)
    com = 0x10    ///< common (00010000)
};





// -----------------------------------------------------------------------------
// Input and output
// -----------------------------------------------------------------------------


/// \brief Operator for writing a decoration onto an output stream.
///
/// \param os Output stream
/// \param dec Decoration to write onto the output stream \p os
/// \return Output stream \p os to support operator chaining
///
/// \note The function pays attention to the output manipulators
/// \link p1788::io::dec_alpha(std::basic_ostream<CharT, Traits>& os) dec_alpha \endlink ,
/// and \link p1788::io::dec_numeric(std::basic_ostream<CharT, Traits>& os) dec_numeric \endlink
/// as well as to
/// \link p1788::io::lower_case(std::basic_ostream<CharT, Traits>& os) lower_case \endlink
/// and \link p1788::io::upper_case(std::basic_ostream<CharT, Traits>& os) upper_case \endlink .
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os,
    decoration dec)
{
    // numeric
    if (os.iword(p1788::io::dec_manip_id) == p1788::io::dec_numeric_representation)
    {
        return os << static_cast<unsigned int>(dec);
    }

    // alphabetic
    switch (dec)
    {
    case decoration::ill:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "ILL";
        default:
            return os << "ill";
        }
    case decoration::trv:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "TRV";
        default:
            return os << "trv";
        }
    case decoration::def:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "DEF";
        default:
            return os << "def";
        }
    case decoration::dac:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "DAC";
        default:
            return os << "dac";
        }
    case decoration::com:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "COM";
        default:
            return os << "com";
        }
    }

    // Something went wrong ;-)
    return os;
}

/// \brief Operator for reading a decoration from an input stream.
///
/// \param is Input stream
/// \param dec Decoration read from the input stream \p is
/// \return Input stream \p is to support operator chaining
///
/// \note The function pays attention to the standard manipulator <c>std::ios_base::skipws</c>.
///
/// \note If no valid textual or numeric representation could be read from the input stream \p is
/// then \p dec is set to decoration::ill and the <c>failbit</c>
/// of the stream is set.
template<typename CharT, typename Traits>
std::basic_istream<CharT, Traits>& operator>>(
    std::basic_istream<CharT, Traits>& is,
    decoration& dec )
{
    std::string head = "";

    // remove whitespaces if necessary
    if (is.flags() & std::ios_base::skipws)
    {
        head = p1788::util::remove_ws(is);
    }

    if (is)
    {
        // starts with digit
        if (std::isdigit(is.peek()))
        {
            unsigned int n;
            is >> n;

            if (is)
            {
                switch (n)
                {
                case 0x00:  // ill
                    dec = decoration::ill;
                    return is;
                case 0x04:  // trv
                    dec = decoration::trv;
                    return is;
                case 0x08:  // def
                    dec = decoration::def;
                    return is;
                case 0x0C:  // dac
                    dec = decoration::dac;
                    return is;
                case 0x10:  // com
                    dec = decoration::com;
                    return is;
                }
            }
        }
        else    // alphabetic
        {
            std::string s;
            s.resize(3);
            is.read(&s[0], 3);

            if (is)
            {
                p1788::util::ascii_to_lower(s);

                if (s == "ill")
                {
                    dec = decoration::ill;
                    return is;
                }
                else if (s == "trv")
                {
                    dec = decoration::trv;
                    return is;
                }
                else if (s == "def")
                {
                    dec = decoration::def;
                    return is;
                }
                else if (s == "dac")
                {
                    dec = decoration::dac;
                    return is;
                }
                else if (s == "com")
                {
                    dec = decoration::com;
                    return is;
                }
            }
        }
    }

    // failed
    dec = decoration::ill;
    is.setstate(std::ios_base::failbit);
    return is;
}


} // namespace decoration

} // namespace p1788


#endif // LIBIEEEP1788_P1788_DECORATION_DECORATION_HPP
