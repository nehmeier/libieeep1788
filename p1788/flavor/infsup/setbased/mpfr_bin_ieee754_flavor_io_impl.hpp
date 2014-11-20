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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_IO_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_IO_IMPL_HPP


#include "p1788/infsup/base_interval.hpp"
#include <cctype>

namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{


// IO
template<typename T>
template< typename CharT, typename Traits >
std::basic_ostream<CharT, Traits>&
mpfr_bin_ieee754_flavor<T>::operator_output(std::basic_ostream<CharT, Traits>& os,
        mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return os;

    // uncertain and not empty
    if (os.iword(p1788::io::representation_manip_id) == p1788::io::uncertain_representation
            && !is_empty(x))
    {
        if (is_entire(x))
            return os << "0.0??";

        mpfr_var::setup();
        mpfr_var xl(x.first , MPFR_RNDD);
        mpfr_var xu(x.second, MPFR_RNDU);

        return os << "[  ]";
    }

    // inf sup representation or empty
    std::string part1 = os.iword(p1788::io::punctuation_manip_id) == p1788::io::show_no_punctuation ? "" : "[";
    std::string part2;
    std::string part3 = os.iword(p1788::io::punctuation_manip_id) == p1788::io::show_no_punctuation ? " " : ",";
    std::string part4;
    std::string part5 = os.iword(p1788::io::punctuation_manip_id) == p1788::io::show_no_punctuation ? "" : "]";

    // empty or entire with no bounds
    if ((is_empty(x) || is_entire(x))
            && os.iword(p1788::io::special_representation_manip_id) != p1788::io::bounds_special_representation)
    {
        switch (os.iword(p1788::io::special_representation_manip_id))
        {
        case p1788::io::no_bounds_special_representation:
            if (os.iword(p1788::io::punctuation_manip_id) == p1788::io::show_punctuation)
            {
                part3 = is_empty(x) ? " " : ",";
                break;
            }
        default:
            switch (os.iword(p1788::io::text_representation_manip_id))
            {
            case p1788::io::upper_case_text_representation:
                part3 = is_empty(x) ? "EMPTY" : "ENTIRE";
                break;
            default:
                part3 = is_empty(x) ? "empty" : "entire";
                break;
            }
            break;
        }

        // Adjust width
        size_t w = os.iword(p1788::io::width_manip_id);
        int w2 = w - ((part3.size() - 1) / 2);
        int w4 =w - (part3.size() -1 - (part3.size() - 1) / 2);

        part2 =  w2 > 0 ? std::string(w2, ' ') : "";
        part4 =  w4 > 0 ? std::string(w4, ' ') : "";
    }
    else // print bounds
    {
        mpfr_var::setup();

        p1788::io::number_representation_flags nr = static_cast<p1788::io::number_representation_flags>(os.iword(p1788::io::number_representation_manip_id));
        size_t w = os.iword(p1788::io::width_manip_id);
        size_t p = os.iword(p1788::io::precision_manip_id);
        p1788::io::text_representation_flags tr =  static_cast<p1788::io::text_representation_flags>(os.iword(p1788::io::text_representation_manip_id));

        mpfr_var xl(inf(x), MPFR_RNDD);
        part2 = xl.get_str(MPFR_RNDD, nr, w, p, tr);

        mpfr_var xu(sup(x), MPFR_RNDU);
        part4 = xu.get_str(MPFR_RNDU, nr, w, p, tr);
    }


    // Adjust width
    int width = os.iword(p1788::io::string_width_manip_id)
                - part1.size() - part2.size() - part3.size() - part4.size() - part5.size();

    if (width < 0)
        width = 0;

    return os << part1 << std::string(width / 2, ' ')
           << part2
           << part3 << std::string(width - width / 2, ' ')
           << part4 << part5;
}


template<typename T>
template< typename CharT, typename Traits >
std::basic_ostream<CharT, Traits>&
mpfr_bin_ieee754_flavor<T>::operator_output(std::basic_ostream<CharT, Traits>& os,
        mpfr_bin_ieee754_flavor<T>::representation_dec const& x)
{
    if (!is_valid(x))
        return os;

    // Generate Nai
    if (is_nai(x))
    {
        std::string part1 = os.iword(p1788::io::punctuation_manip_id) == p1788::io::show_no_punctuation ? "" : "[";
        std::string part2 = os.iword(p1788::io::text_representation_manip_id) == p1788::io::upper_case_text_representation ? "NAI" : "nai";
        std::string part3 = os.iword(p1788::io::punctuation_manip_id) == p1788::io::show_no_punctuation ? "" : "]";

        // Adjust width
        size_t w = os.iword(p1788::io::width_manip_id);
        int w2 = w - ((part2.size() - 1) / 2);
        int w3 =w - (part2.size() -1 - (part2.size() - 1) / 2);

        part1 +=  w2 > 0 ? std::string(w2, ' ') : "";
        part3 =  (w3 > 0 ? std::string(w3, ' ') : "") + part3;


        int width = os.iword(p1788::io::string_width_manip_id)
                    - part1.size() - part2.size() - part3.size();

        if (width < 0)
            width = 0;

        return os << part1 << std::string(width / 2, ' ')
               << part2 << std::string(width - width / 2, ' ')
               << part3;
    }


    // no decorations for empty intervals
    if (is_empty(x))
    {
        // bare interval
        operator_output(os, x.first);
        return os;
    }

    // generate the decoration string
    std::stringstream buf;
    buf.copyfmt(os);
    buf << ((os.iword(p1788::io::punctuation_manip_id) == p1788::io::show_no_punctuation) ? " " : "_") << x.second;


    // RAII class to handle the string_width_manip
    class string_width_helper
    {
        std::basic_ostream<CharT, Traits>& os_;
        int size_;
    public:
        // adjust string size
        string_width_helper(std::basic_ostream<CharT, Traits>& os, int dec_width)
            : os_(os), size_(os.iword(p1788::io::string_width_manip_id))
        {
            os_.iword(p1788::io::string_width_manip_id) = size_ - dec_width;
        }

        // reset size
        ~string_width_helper()
        {
            os_.iword(p1788::io::string_width_manip_id) = size_;
        }
    } swh(os, buf.str().size());

    // generate bare output
    operator_output(os, x.first);

    // append decoration
    return os << buf.str();
}


template<typename T>
template< typename CharT, typename Traits >
std::basic_istream<CharT, Traits>&
mpfr_bin_ieee754_flavor<T>::operator_input(std::basic_istream<CharT, Traits>& is,
        mpfr_bin_ieee754_flavor<T>::representation& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    std::string str;
    std::getline(std::cin, str);

    x = constructor(str);

    return is;
}

template<typename T>
template< typename CharT, typename Traits >
std::basic_istream<CharT, Traits>&
mpfr_bin_ieee754_flavor<T>::operator_input(std::basic_istream<CharT, Traits>& is,
        mpfr_bin_ieee754_flavor<T>::representation_dec& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    std::string str;
    std::getline(std::cin, str);

    x = constructor_dec(str);

    return is;
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_IO_IMPL_HPP
