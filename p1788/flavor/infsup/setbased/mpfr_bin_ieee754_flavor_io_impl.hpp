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


namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{


// writing a bare interval onto an output stream
// taking care of io manipulators
template<typename T>
template< typename CharT, typename Traits >
std::basic_ostream<CharT, Traits>&
mpfr_bin_ieee754_flavor<T>::operator_output(std::basic_ostream<CharT, Traits>& os,
        mpfr_bin_ieee754_flavor<T>::representation const& x)
{
    if (!is_valid(x))
        return os;

    //-------------------------------------
    // uncertain and not empty
    //-------------------------------------
    if ((os.iword(p1788::io::representation_manip_id) == p1788::io::uncertain_representation
            || os.iword(p1788::io::representation_manip_id) == p1788::io::uncertain_up_representation
            || os.iword(p1788::io::representation_manip_id) == p1788::io::uncertain_down_representation)
            && !is_empty(x))
    {
        std::string str;
        int prec = os.iword(p1788::io::precision_manip_id);
        p1788::io::text_representation_flags text_rep =  static_cast<p1788::io::text_representation_flags>(os.iword(p1788::io::text_representation_manip_id));
        p1788::io::uncertain_exponent_flags uc_exp = static_cast<p1788::io::uncertain_exponent_flags>(os.iword(p1788::io::uncertain_exponent_manip_id));

        // Default precision is 6
        if (prec == 0)
            prec = 6;

        // entire
        if (is_entire(x))
        {
            mpfr_var::setup();
            mpfr_var xu(mid(x), MPFR_RNDN);

            // generate number string
            str = xu.get_str(MPFR_RNDN,
                             uc_exp == p1788::io::show_uncertain_exponent ? p1788::io::scientific_representation : p1788::io::decimal_representation,
                             0,
                             prec,
                             text_rep);

            // find exponent
            int p = std::max(static_cast<int>(str.find('E')), static_cast<int>(str.find('e')));

            // insert ??
            if (p >= 0)
                str.insert(p, "??");
            else
                str += "??";
        }
        else if (std::isinf(x.first))    // [-oo,x]
        {
            mpfr_var::setup();
            mpfr_var xu(x.second, MPFR_RNDU);

            // generate number string
            str = xu.get_str(MPFR_RNDU,
                             uc_exp == p1788::io::show_uncertain_exponent ? p1788::io::scientific_representation : p1788::io::decimal_representation,
                             0,
                             prec,
                             static_cast<p1788::io::text_representation_flags>(os.iword(p1788::io::text_representation_manip_id)));

            // find exponent
            int p = std::max(static_cast<int>(str.find('E')), static_cast<int>(str.find('e')));

            // add ??d
            if (p >= 0)
                str.insert(p, text_rep == p1788::io::upper_case_text_representation ? "??D" : "??d");
            else
                str += (text_rep == p1788::io::upper_case_text_representation ? "??D" : "??d");
        }
        else if (std::isinf(x.second))  // [x,+oo]
        {
            mpfr_var::setup();
            mpfr_var xl(x.first, MPFR_RNDD);

            // generate number string
            str = xl.get_str(MPFR_RNDD,
                             uc_exp == p1788::io::show_uncertain_exponent ? p1788::io::scientific_representation : p1788::io::decimal_representation,
                             0,
                             prec,
                             text_rep);

            // find exponent
            int p = std::max(static_cast<int>(str.find('E')), static_cast<int>(str.find('e')));

            // add ??d
            if (p >= 0)
                str.insert(p, text_rep == p1788::io::upper_case_text_representation ? "??U" : "??u");
            else
                str += (text_rep == p1788::io::upper_case_text_representation ? "??U" : "??u");
        }
        else    // all other
        {
            mpfr_var::setup();
            mpfr_var xl(x.first, MPFR_RNDD);
            mpfr_var xu(x.second, MPFR_RNDU);

            // lower bound representation
            std::string tmp_l = xl.get_str(MPFR_RNDD,
                                           uc_exp == p1788::io::show_uncertain_exponent ? p1788::io::scientific_representation : p1788::io::decimal_representation,
                                           0,
                                           prec,
                                           text_rep);

            // upper bound representation
            std::string tmp_u = xu.get_str(MPFR_RNDU,
                                           uc_exp == p1788::io::show_uncertain_exponent ? p1788::io::scientific_representation : p1788::io::decimal_representation,
                                           0,
                                           prec,
                                           text_rep);

            // find exponent part
            int p_l = std::max(static_cast<int>(tmp_l.find('E')), static_cast<int>(tmp_l.find('e')));
            int p_u = std::max(static_cast<int>(tmp_u.find('E')), static_cast<int>(tmp_u.find('e')));

            std::string exp_str = "";

            long long int ulps = 0;

            // symmetric
            if (os.iword(p1788::io::representation_manip_id) == p1788::io::uncertain_representation)
            {
                // midpoint string
                mpfr_var m(mid(x), MPFR_RNDN);
                std::string tmp_m = m.get_str(MPFR_RNDN,
                                              uc_exp == p1788::io::show_uncertain_exponent ? p1788::io::scientific_representation : p1788::io::decimal_representation,
                                              0,
                                              prec,
                                              text_rep);

                // find exponent part
                int p_m = std::max(static_cast<int>(tmp_m.find('E')), static_cast<int>(tmp_m.find('e')));

                // split number and exponent part if necessary
                str = p_m >= 0 ? tmp_m.substr(0, p_m) : tmp_m;
                if (p_m >= 0)
                {
                    exp_str = tmp_m.substr(p_m, tmp_m.size() - p_m);
                    tmp_m = str;
                }

                // remove seperator
                tmp_m.erase(tmp_m.size() - prec - 1, 1);

                // compute exponent difference
                int exp_m = p_m >= 0 ? std::stoi(exp_str.substr(1, tmp_m.size() - 1)) : 0;
                int ulp_l = 0;
                int ulp_u = 0;
                if (p_l >= 0)
                {
                    int exp_l = std::stoi(tmp_l.substr(p_l + 1, tmp_l.size() - p_l - 1)) - exp_m;
                    // remove exponent and seperator
                    tmp_l.erase(p_l);
                    tmp_l.erase(tmp_l.size() - prec - 1, 1);

                    if (exp_l < 0)
                    {
                        // remove trailing digits and remind ulp if necessary
                        ulp_l = std::stoll(tmp_l.substr(tmp_l.size() + exp_l)) != 0 && x.first < 0.0 ? 1 : 0;
                        tmp_l.resize(tmp_l.size() + exp_l);
                    }
                    else if (exp_l > 0)
                        // add some digits
                        tmp_l.append(exp_l, '0');

                }
                else
                {
                    // remove seperator
                    tmp_l.erase(tmp_l.size() - prec - 1, 1);
                }

                if (p_u >= 0)
                {
                    int exp_u = exp_m - std::stoi(tmp_u.substr(p_u + 1, tmp_u.size() - p_u - 1));
                    // remove exponent and seperator
                    tmp_u.erase(p_u);
                    tmp_u.erase(tmp_u.size() - prec - 1, 1);
                    if (exp_u > 0)
                    {
                        // remove trailing digits and remind ulp if necessary
                        ulp_u = std::stoll(tmp_u.substr(tmp_u.size() - exp_u)) != 0 && x.second > 0.0  ? 1 : 0;
                        tmp_u.resize(tmp_u.size() - exp_u);
                    }
                    else if (exp_u < 0)
                        // add some digits
                        tmp_u.append(-exp_u, '0');
                }
                else
                {
                    // remove seperator
                    tmp_u.erase(tmp_u.size() - prec - 1, 1);
                }

                // compute max ulps to lower and upper bound
                long long int tmp = std::stoll(tmp_m);

                ulps = std::max(-std::stoll(tmp_l) + tmp + ulp_l,
                                -tmp + std::stoll(tmp_u) + ulp_u);
            }
            else // downward or upward
            {
                if (os.iword(p1788::io::representation_manip_id) == p1788::io::uncertain_down_representation)
                {
                    // split number and exponent part if necessary
                    str = p_u >= 0 ? tmp_u.substr(0, p_u) : tmp_u;
                    if (p_u >= 0)
                        exp_str = tmp_u.substr(p_u, tmp_u.size() - p_u);
                }
                else if (os.iword(p1788::io::representation_manip_id) == p1788::io::uncertain_up_representation)
                {
                    // split number and exponent part if necessary
                    str = p_l >= 0 ? tmp_l.substr(0, p_l) : tmp_l;
                    if (p_l >= 0)
                        exp_str = tmp_l.substr(p_l, tmp_l.size() - p_l);
                }

                // compute exponent difference
                int exp = 0;
                if (p_l >= 0)
                {
                    exp = std::stoi(tmp_l.substr(p_l + 1, tmp_l.size() - p_l - 1));
                    tmp_l.erase(p_l);
                }
                if (p_u >= 0)
                {
                    exp -= std::stoi(tmp_u.substr(p_u + 1, tmp_u.size() - p_u - 1));
                    tmp_u.erase(p_u);
                }

                // remove seperator
                tmp_l.erase(tmp_l.size() - prec - 1, 1);
                tmp_u.erase(tmp_u.size() - prec - 1, 1);

                // adjust string length to balance exponent difference
                if (os.iword(p1788::io::representation_manip_id) == p1788::io::uncertain_down_representation)
                {
                    if (exp < 0)
                    {
                        // remove trailing digits and adjust ulps if necessary
                        ulps += std::stoll(tmp_l.substr(tmp_l.size() + exp)) != 0 && x.first < 0.0 ? 1 : 0;
                        tmp_l.resize(tmp_l.size() + exp);
                    }
                    else if (exp > 0)
                        // add some digits
                        tmp_l.append(exp, '0');
                }
                else if (os.iword(p1788::io::representation_manip_id) == p1788::io::uncertain_up_representation)
                {
                    if (exp > 0)
                    {
                        // remove trailing digits and adjust ulps if necessary
                        ulps += std::stoll(tmp_u.substr(tmp_u.size() - exp)) != 0 && x.second > 0.0  ? 1 : 0;
                        tmp_u.resize(tmp_u.size() - exp);
                    }
                    else if (exp < 0)
                        // add some digits
                        tmp_u.append(-exp, '0');
                }

                // compute ulps
                ulps += -std::stoll(tmp_l) +  std::stoll(tmp_u);
            }

            str += "?" + std::to_string(ulps);

            // add downward or upward flag
            switch(os.iword(p1788::io::representation_manip_id))
            {
            case p1788::io::uncertain_down_representation:
                str += text_rep == p1788::io::upper_case_text_representation ? "D" : "d";
                break;
            case p1788::io::uncertain_up_representation:
                str += text_rep == p1788::io::upper_case_text_representation ? "U" : "u";
                break;
            }

            // add exponent
            str += exp_str;
        }

        int w = os.iword(p1788::io::string_width_manip_id) - str.size();

        // adjust width
        if (w > 0)
            str = std::string(w, ' ') + str;

        return os << str;
    }

    //-------------------------------------
    // inf sup representation or empty
    //-------------------------------------
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


// writing a decorated interval onto an output stream
// taking care of io manipulators
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
    representation_dec x_dec;

    operator_input(is, x_dec);

    x = constructor(x_dec);

    return is;
}

template<typename T>
template< typename CharT, typename Traits >
std::basic_istream<CharT, Traits>&
mpfr_bin_ieee754_flavor<T>::operator_input(std::basic_istream<CharT, Traits>& is,
        mpfr_bin_ieee754_flavor<T>::representation_dec& x)
{
    // remove whitespaces if necessary
    if (is.flags() & std::ios_base::skipws)
    {
        p1788::util::remove_ws(is);
    }


    if (is)
    {
        //---------------------------------------------------------------------------------
        // inf sup
        //---------------------------------------------------------------------------------

        if (is.peek() == '[') // check if first char is '[' than remove it and check if stream is ok
        {
            is.get(); // remove '['

            if (is)
            {
                std::string input;
                std::getline(is, input, ']');

                if (is)
                {
                    // regex to match valid literal
                    // Subgroups:
                    //    [0] :  whole string
                    //    [1] :    string of argument if only one argument is specified
                    //    [2] :      nominator if argument is rational
                    //    [3] :      denominator if argument is rational
                    //    [4] :      string if argument is "empty"
                    //    [5] :      string if argument is "entire"
                    //    [6] :      string if argument is "nai"
                    //    [7] :    string of first argument if two arguments are specified
                    //    [8] :      nominator if first argument is rational
                    //    [9] :      denominator if first argument is rational
                    //    [10] :     string if first argument is "-inf" or "-infinity"
                    //    [11] : separator
                    //    [12] :   string of second argument if two arguments are specified
                    //    [13] :     nominator if second argument is rational
                    //    [14] :     denominator if second argument is rational
                    //    [15] :     string if second argument is "+inf" or "+infinity"
                    static std::regex inf_sup_regex(
                        //one argument or empty
                        "(?:"
                        "\\s*((?:[+-]?[0-9]+)"                                                                      //int
                        "|(?:[+-]?(?:(?:[0-9]+[\\.]?[0-9]*)|(?:[0-9]*\\.[0-9]+))(?:e[+-]?[0-9]+)?)"                 // float
                        "|(?:[+-]?0x(?:(?:[0-9a-f]+[\\.]?[0-9a-f]*)|(?:[0-9a-f]*\\.[0-9a-f]+))(?:p[+-]?[0-9]+)?)"   // hex
                        "|(?:([+-]?[0-9]+)\\s*/\\s*([+]?[0-9]+))"                                                   // rational
                        "|(?:(empty)|(entire)|(nai)))?\\s*"                                                         // empty, entire, nai strings
                        ")"
                        // two arguments separated by a comma
                        "|(?:"
                        "\\s*((?:[+-]?[0-9]+)"                                                                      //int
                        "|(?:[+-]?(?:(?:[0-9]+[\\.]?[0-9]*)|(?:[0-9]*\\.[0-9]+))(?:e[+-]?[0-9]+)?)"                 // float
                        "|(?:[+-]?0x(?:(?:[0-9a-f]+[\\.]?[0-9a-f]*)|(?:[0-9a-f]*\\.[0-9a-f]+))(?:p[+-]?[0-9]+)?)"   // hex
                        "|(?:([+-]?[0-9]+)\\s*/\\s*([+]?[0-9]+))"                                                   // rational
                        "|(?:-(inf|infinity)))?\\s*"                                                                // inf string
                        "(,)"
                        "\\s*((?:[+-]?[0-9]+)"                                                                      //int
                        "|(?:[+-]?(?:(?:[0-9]+[\\.]?[0-9]*)|(?:[0-9]*\\.[0-9]+))(?:e[+-]?[0-9]+)?)"                 // float
                        "|(?:[+-]?0x(?:(?:[0-9a-f]+[\\.]?[0-9a-f]*)|(?:[0-9a-f]*\\.[0-9a-f]+))(?:p[+-]?[0-9]+)?)"   // hex
                        "|(?:([+-]?[0-9]+)\\s*/\\s*([+]?[0-9]+))"                                                   // rational
                        "|(?:[+]?(inf|infinity)))?\\s*"                                                             // inf string
                        ")",
                        std::regex_constants::icase                                                     // ignore case
                    );


                    std::smatch match;
                    if (std::regex_match(input, match, inf_sup_regex))
                    {
                        // temporary storage of lower and
                        representation bare;

                        // upper bound for valid decorations
                        p1788::decoration::decoration dec = p1788::decoration::decoration::com;

                        mpfr_var::setup();

                        // only one argument or empty string
                        if (match[11].length() == 0)
                        {
                            // empty :  string "empty" or only whitespaces
                            if (match[4].length() > 0 || match[1].length() == 0)
                            {
                                bare = empty();
                                dec = p1788::decoration::decoration::trv;
                            }
                            else if (match[5].length() > 0) // entire
                            {
                                bare = entire();
                                dec = p1788::decoration::decoration::dac;
                            }
                            else if (match[6].length() > 0) // nai
                            {
                                dec = p1788::decoration::decoration::ill;
                            }
                            else // number
                            {
                                mpfr_var l;
                                mpfr_var u;

                                if (match[2].length() > 0) // rational
                                {
                                    mpfr_set_str(l(), match[2].str().c_str(), 0, MPFR_RNDN);
                                    mpfr_set_str(u(), match[2].str().c_str(), 0, MPFR_RNDN);

                                    mpfr_var d;
                                    mpfr_set_str(d(), match[3].str().c_str(), 0, MPFR_RNDN);

                                    mpfr_div(l(), l(), d(), MPFR_RNDD);
                                    mpfr_div(u(), u(), d(), MPFR_RNDU);
                                }
                                else
                                {
                                    mpfr_set_str(l(), match[1].str().c_str(), 0, MPFR_RNDD);
                                    mpfr_set_str(u(), match[1].str().c_str(), 0, MPFR_RNDU);
                                }

                                bare.first = l.template get<T>(MPFR_RNDD);
                                bare.second = u.template get<T>(MPFR_RNDU);
                            }

                        }
                        else    // two arguments
                        {
                            // -inf or empty lower bound
                            if (match[10].length() > 0 || match[7].length() == 0)
                            {
                                bare.first = -std::numeric_limits<T>::infinity();
                                dec = p1788::decoration::decoration::dac;
                            }
                            else // number lower bound
                            {
                                mpfr_var l;

                                if (match[8].length() > 0) // rational
                                {
                                    mpfr_set_str(l(), match[8].str().c_str(), 0, MPFR_RNDN);

                                    mpfr_var d;
                                    mpfr_set_str(d(), match[9].str().c_str(), 0, MPFR_RNDN);

                                    mpfr_div(l(), l(), d(), MPFR_RNDD);
                                }
                                else
                                {
                                    mpfr_set_str(l(), match[7].str().c_str(), 0, MPFR_RNDD);
                                }

                                bare.first = l.template get<T>(MPFR_RNDD);
                            }

                            // +inf or empty upper bound
                            if (match[15].length() > 0 || match[12].length() == 0)
                            {
                                bare.second = std::numeric_limits<T>::infinity();
                                dec = p1788::decoration::decoration::dac;
                            }
                            else    // number upper bound
                            {
                                mpfr_var u;

                                if (match[13].length() > 0) // rational
                                {
                                    mpfr_set_str(u(), match[13].str().c_str(), 0, MPFR_RNDN);

                                    mpfr_var d;
                                    mpfr_set_str(d(), match[14].str().c_str(), 0, MPFR_RNDN);

                                    mpfr_div(u(), u(), d(), MPFR_RNDU);
                                }
                                else
                                {
                                    mpfr_set_str(u(), match[12].str().c_str(), 0, MPFR_RNDU);
                                }

                                bare.second = u.template get<T>(MPFR_RNDU);
                            }
                        }

                        if (is.peek() == '_')
                        {
                            if (dec != p1788::decoration::decoration::ill)
                            {
                                is.get();

                                p1788::decoration::decoration d;
                                is >> d;

                                if (is && d <= dec && d != p1788::decoration::decoration::ill)
                                {
                                    // create dec interval
                                    // and adjust decoration in case of an overflow
                                    x = constructor_dec(bare,
                                                        std::isinf(bare.first) || std::isinf(bare.second) ?
                                                        std::min(d, p1788::decoration::decoration::dac)
                                                        : d);

                                    // everything was ok
                                    return is;
                                }
                            }
                        }
                        else
                        {
                            x = dec == p1788::decoration::decoration::ill ? nai() : constructor_dec(bare);

                            // everything was ok
                            return is;
                        }
                    }
                }
            }
        }
        else    // uncertain
        {
            if (is && (is.peek() == '+' || is.peek() == '-' || is.peek() == '.' || std::isdigit(is.peek())))
            {
                // read string from stream
                std::string input;

                // read number
                std::getline(is, input, '?');

                if (is)
                    input += '?';

                // read ulps
                if(is.good() && is.peek() == '?')
                {
                    input += is.get();
                }
                else
                {
                    while (is.good() && std::isdigit(is.peek()))
                        input += is.get();
                }

                // read direction
                if(is.good() && (is.peek() == 'd' || is.peek() == 'D' || is.peek() == 'u' || is.peek() == 'U'))
                    input += is.get();


                // read exponent
                if(is.good() && (is.peek() == 'e' || is.peek() == 'E' ))
                {
                    input += is.get();


                    if(is.good() && (is.peek() == '-' || is.peek() == '+'))
                        input += is.get();

                    while (is.good() && std::isdigit(is.peek()))
                        input += is.get();
                }


                if (is || is.eof())
                {
                    // regex to match valid literal
                    // subgroups
                    // [1]   number
                    // [2]   infinite radius
                    // [3]   ulps radius
                    // [4]   direction upward
                    // [5]   direction downward
                    // [6]   exponent
                    static std::regex uncertain_regex(
                        "([+-]?(?:(?:[0-9]+[\\.]?[0-9]*)|(?:[0-9]*\\.[0-9]+)))"                // number
                        "\\?"                                                               // ?
                        "(?:(\\?)|([0-9]+))?"                                               // radius
                        "(?:(u|U)|(d|D))?"                                                  // direction
                        "(?:[eE]([+-]?[0-9]+))?",                                               // exponent
                        std::regex_constants::icase                                                     // ignore case
                    );

                    std::smatch match;
                    if (std::regex_match(input, match, uncertain_regex))
                    {
                        // temporary storage of lower and
                        representation bare;

                        // upper bound for valid decorations
                        p1788::decoration::decoration dec = p1788::decoration::decoration::com;

                        mpfr_var::setup();
                        mpfr_var rad;
                        mpfr_var l;
                        mpfr_var u;

                        // read number
                        std::string n_str = match[1].str();
                        mpfr_set_str(l(), n_str.c_str(), 0, MPFR_RNDD);
                        mpfr_set_str(u(), n_str.c_str(), 0, MPFR_RNDU);

                        // compute radius
                        if (match[2].length() > 0)  // "?" => infinity
                        {
                            rad.set(std::numeric_limits<T>::infinity(), MPFR_RNDU);
                            dec = p1788::decoration::decoration::dac;
                        }
                        else
                        {
                            // compute precision
                            int p = n_str.find('.');
                            int prec =  p >= 0 ?  -(n_str.size() - 1 - p) : 0;

                            std::string r_str;

                            if (match[3].length() > 0)      // ulps are specified
                            {
                                r_str = match[3].str();
                            }
                            else if (match[4].length() > 0 || match[5].length() > 0)    // direction is specified
                            {
                                r_str = "1";
                            }
                            else    // nothing is specified
                            {
                                r_str = "0.5";
                            }

                            r_str += "E";
                            r_str += std::to_string(prec);

                            mpfr_set_str(rad(), r_str.c_str(), 0, MPFR_RNDU);
                        }

                        // compute bounds
                        if (match[4].length() > 0)  // upward
                        {
                            mpfr_add(u(), u(), rad(), MPFR_RNDU);
                        }
                        else if (match[5].length() > 0) // downward
                        {
                            mpfr_sub(l(), l(), rad(), MPFR_RNDD);
                        }
                        else    // symmetric
                        {
                            mpfr_sub(l(), l(), rad(), MPFR_RNDD);
                            mpfr_add(u(), u(), rad(), MPFR_RNDU);
                        }

                        bare.first = l.template get<T>(MPFR_RNDD);
                        bare.second = u.template get<T>(MPFR_RNDU);

                        // exponent
                        if (match[6].length() > 0)
                        {
                            std::string exp_str = "1.0E";
                            exp_str += match[6].str();

                            mpfr_var el;
                            mpfr_var eu;
                            mpfr_set_str(el(), exp_str.c_str(), 0, MPFR_RNDD);
                            mpfr_set_str(eu(), exp_str.c_str(), 0, MPFR_RNDU);

                            representation exp(el.template get<T>(MPFR_RNDD), eu.template get<T>(MPFR_RNDU));

                            bare = mul(bare, exp);
                        }

                        if (is && is.peek() == '_')
                        {
                            if (dec != p1788::decoration::decoration::ill)
                            {
                                is.get();

                                p1788::decoration::decoration d;
                                is >> d;

                                if (is && d <= dec && d != p1788::decoration::decoration::ill)
                                {
                                    // create dec interval
                                    // and adjust decoration in case of an overflow
                                    x = constructor_dec(bare,
                                                        std::isinf(bare.first) || std::isinf(bare.second) ?
                                                        std::min(d, p1788::decoration::decoration::dac)
                                                        : d);

                                    // everything was ok
                                    return is;
                                }
                            }
                        }
                        else
                        {
                            x = dec == p1788::decoration::decoration::ill ? nai() : constructor_dec(bare);

                            // everything was ok
                            return is;
                        }
                    }
                }
            }
        }
    }

    // failed
    is.setstate(std::ios_base::failbit);

    return is;
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_IO_IMPL_HPP
