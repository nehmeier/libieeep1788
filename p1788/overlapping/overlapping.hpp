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


#ifndef LIBIEEEP1788_P1788_OVERLAPPING_OVERLAPPING_HPP
#define LIBIEEEP1788_P1788_OVERLAPPING_OVERLAPPING_HPP

#include <iostream>
#include "p1788/io/io_manip.hpp"

#include <cstdint>

namespace p1788
{

namespace overlapping
{


// \brief Enum describing the 16 states of the interval overlapping
// see P1788/D7.0 Sect. 9.7.2 Table 6
//
enum class overlapping_state : uint16_t
{
    both_empty      = 0,
    first_empty     = 1,
    second_empty    = 1 << 1,
    before          = 1 << 2,
    meets           = 1 << 3,
    overlaps        = 1 << 4,
    starts          = 1 << 5,
    contained_by    = 1 << 6,
    finishes        = 1 << 7,
    equal           = 1 << 8,
    finished_by     = 1 << 9,
    contains        = 1 << 10,
    started_by      = 1 << 11,
    overlapped_by   = 1 << 12,
    met_by          = 1 << 13,
    after           = 1 << 14
};


/// \brief Operator for writing an overlapping state onto an output stream.
///
/// \param os Output stream
/// \param o Overlapping state to write onto the output stream \p os
/// \return Output stream \p os to support operator chaining
///
/// \note The function pays attention to the output manipulators
/// \link p1788::io::overlapping_alpha(std::basic_ostream<CharT, Traits>& os) overlapping_alpha \endlink ,
/// and \link p1788::io::overlapping_numeric(std::basic_ostream<CharT, Traits>& os) overlapping_numeric \endlink
/// as well as to
/// \link p1788::io::lower_case(std::basic_ostream<CharT, Traits>& os) lower_case \endlink
/// and \link p1788::io::upper_case(std::basic_ostream<CharT, Traits>& os) upper_case \endlink .
template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os, overlapping_state o)
{
    // numeric
    if (os.iword(p1788::io::overlapping_manip_id) == p1788::io::overlapping_numeric_representation)
    {
        return os << static_cast<unsigned int>(o);
    }

    // alphabetic
    switch (o)
    {
    case overlapping_state::both_empty:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "BOTH_EMPTY";
        default:
            return os << "both_empty";
        }
    case overlapping_state::first_empty:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "FIRST_EMPTY";
        default:
            return os << "first_empty";
        }
    case overlapping_state::second_empty:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "SECOND_EMPTY";
        default:
            return os << "second_empty";
        }
    case overlapping_state::before:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "BEFORE";
        default:
            return os << "before";
        }
    case overlapping_state::meets:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "MEETS";
        default:
            return os << "meets";
        }
    case overlapping_state::overlaps:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "OVERLAPS";
        default:
            return os << "overlaps";
        }
    case overlapping_state::starts:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "STARTS";
        default:
            return os << "starts";
        }
    case overlapping_state::contained_by:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "CONTAINED_BY";
        default:
            return os << "contained_by";
        }
    case overlapping_state::finishes:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "FINISHES";
        default:
            return os << "finishes";
        }
    case overlapping_state::equal:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "EQUAL";
        default:
            return os << "equal";
        }
    case overlapping_state::finished_by:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "FINISHED_BY";
        default:
            return os << "finished_by";
        }
    case overlapping_state::contains:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "CONTAINS";
        default:
            return os << "contains";
        }
    case overlapping_state::started_by:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "STARTED_BY";
        default:
            return os << "started_by";
        }
    case overlapping_state::overlapped_by:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "OVERLAPPED_BY";
        default:
            return os << "overlapped_by";
        }
    case overlapping_state::met_by:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "MET_BY";
        default:
            return os << "met_by";
        }
    case overlapping_state::after:
        switch (os.iword(p1788::io::text_representation_manip_id))
        {
        case p1788::io::upper_case_text_representation:
            return os << "AFTER";
        default:
            return os << "after";
        }
    }

    // Something went wrong ;-)
    return os;
}



// TODO overlapping relation, finish implementation, functions ...


} // namespace overlapping

} // namespace p1788



#endif // LIBIEEEP1788_P1788_OVERLAPPING_OVERLAPPING_HPP
