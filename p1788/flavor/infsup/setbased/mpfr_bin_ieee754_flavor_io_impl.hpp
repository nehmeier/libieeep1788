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
mpfr_bin_ieee754_flavor<T>::operator_interval_to_text(std::basic_ostream<CharT, Traits>& os,
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
mpfr_bin_ieee754_flavor<T>::operator_interval_to_text(std::basic_ostream<CharT, Traits>& os,
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
        operator_interval_to_text(os, x.first);
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
    operator_interval_to_text(os, x.first);

    // append decoration
    return os << buf.str();
}


template<typename T>
template< typename CharT, typename Traits >
std::basic_istream<CharT, Traits>&
mpfr_bin_ieee754_flavor<T>::operator_text_to_interval(std::basic_istream<CharT, Traits>& is,
        mpfr_bin_ieee754_flavor<T>::representation& x)
{
    representation_dec x_dec;

    operator_text_to_interval(is, x_dec);

    if (is)
        x = interval_part(x_dec);

    return is;
}

template<typename T>
template< typename CharT, typename Traits >
std::basic_istream<CharT, Traits>&
mpfr_bin_ieee754_flavor<T>::operator_text_to_interval(std::basic_istream<CharT, Traits>& is,
        mpfr_bin_ieee754_flavor<T>::representation_dec& x)
{

    // RAII for mpz_t
    struct mpz_var
    {
        mpz_var() : var_()
        {
            mpz_init(var_);
        }

        ~mpz_var()
        {
            mpz_clear(var_);
        }

        mpz_t var_;
    };

    // RAII for mpq_t
    struct mpq_var
    {
        mpq_var() : var_()
        {
            mpq_init(var_);
        }

        ~mpq_var()
        {
            mpq_clear(var_);
        }

        mpq_t var_;
    };

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
            //is.get(); // remove '['

            if (is)
            {
                std::string input;
                //std::getline(is, input, ']');

                // read string
                for (auto c = is.peek(); is; c = is.peek())
                {
                    input += is.get();

                    if (c == ']')
                        break;
                }

                if (is)
                {
                    // regex to match valid literal
                    // Subgroups:
                    //    [0] :  whole string
                    //
                    // only one argument is specified:
                    //    [1] :  whole argument
                    //    [2] :  float representation: number
                    //    [3] :  float representation: exponent
                    //    [4] :  hex representation: number
                    //    [5] :  hex representation: exponent
                    //    [6] :  rational representation: nominator
                    //    [7] :  rational representation: denominator
                    //    [8] :  string if argument is "empty"
                    //    [9] : string if argument is "entire"
                    //    [10] : string if argument is "nai"
                    //
                    // two arguments are specified:
                    //    [11] :  whole first argument
                    //    [12] :  float representation: number
                    //    [13] :  float representation: exponent
                    //    [14] :  hex representation: number
                    //    [15] :  hex representation: exponent
                    //    [16] :  rational representation: nominator
                    //    [17] :  rational representation: denominator
                    //    [18] :  string if first argument is "-inf" or "-infinity"
                    //    [19] : separator
                    //    [20] :  whole second argument
                    //    [21] :  float representation: number
                    //    [22] :  float representation: exponent
                    //    [23] :  hex representation: number
                    //    [24] :  hex representation: exponent
                    //    [25] :  rational representation: nominator
                    //    [26] :  rational representation: denominator
                    //    [27] :  string if second argument is "+inf" or "+infinity"
                    static std::regex inf_sup_regex(
                        //one argument or empty
                        "(?:\\[\\s*("
                        "|(?:([+-]?(?:(?:[0-9]*\\.[0-9]+)|(?:[0-9]+[\\.])|(?:[0-9]+)))(?:e([+-]?[0-9]+))?)"             // float
                        "|(?:([+-]?0x(?:(?:[0-9a-f]*\\.[0-9a-f]+)|(?:[0-9a-f]+[\\.])|(?:[0-9a-f]+)))(?:p([+-]?[0-9]+)))"   // hex
                        "|(?:([+-]?[0-9]+)\\s*/\\s*([0]*[1-9][0-9]*))"                                              // rational
                        "|(?:(empty)|(entire)|(nai))"                                                               // empty, entire, nai strings
                        ")?\\s*\\])"
                        // two arguments separated by a comma
                        "|(?:\\[\\s*("
                        "|(?:([+-]?(?:(?:[0-9]*\\.[0-9]+)|(?:[0-9]+[\\.])|(?:[0-9]+)))(?:e([+-]?[0-9]+))?)"             // float
                        "|(?:([+-]?0x(?:(?:[0-9a-f]*\\.[0-9a-f]+)|(?:[0-9a-f]+[\\.])|(?:[0-9a-f]+)))(?:p([+-]?[0-9]+)))"   // hex
                        "|(?:([+-]?[0-9]+)\\s*/\\s*([0]*[1-9][0-9]*))"                                              // rational
                        "|(?:-(inf|infinity))"                                                                // inf string
                        ")?\\s*(,)\\s*("
                        "|(?:([+-]?(?:(?:[0-9]*\\.[0-9]+)|(?:[0-9]+[\\.])|(?:[0-9]+)))(?:e([+-]?[0-9]+))?)"             // float
                        "|(?:([+-]?0x(?:(?:[0-9a-f]*\\.[0-9a-f]+)|(?:[0-9a-f]+[\\.])|(?:[0-9a-f]+)))(?:p([+-]?[0-9]+)))"   // hex
                        "|(?:([+-]?[0-9]+)\\s*/\\s*([0]*[1-9][0-9]*))"                                              // rational
                        "|(?:[+]?(inf|infinity))"                                                             // inf string
                        ")?\\s*\\])",
                        std::regex_constants::icase                                                     // ignore case
                    );


                    std::smatch match;
                    if (std::regex_match(input, match, inf_sup_regex))
                    {

                        // temporary storage of lower and upper bound
                        representation bare;
                        bare.first = 1.0;
                        bare.second = -1.0;

                        // for valid decorations
                        p1788::decoration::decoration dec = p1788::decoration::decoration::com;

                        mpfr_var::setup();

                        // only one argument or empty string
                        if (match[19].length() == 0)
                        {
                            // empty :  string "empty" or only whitespaces
                            if (match[8].length() > 0 || match[1].length() == 0)
                            {
                                bare = empty();
                                dec = p1788::decoration::decoration::trv;
                            }
                            else if (match[9].length() > 0) // entire
                            {
                                bare = entire();
                                dec = p1788::decoration::decoration::dac;
                            }
                            else if (match[10].length() > 0) // nai
                            {
                                bare = empty();
                                dec = p1788::decoration::decoration::ill;
                            }
                            else if (match[2].length() > 0) // float
                            {
                                // number string
                                std::string n_str = match[2].str();

                                // compute precision and remove point
                                int p = n_str.find('.');
                                if (p >= 0)
                                {
                                    n_str.erase(p,1);
                                    p = -(n_str.size() - p);
                                }
                                else
                                {
                                    p = 0;
                                }

                                // parse number as integer
                                mpz_var n;
                                int i = mpz_set_str(n.var_, n_str.c_str(), 10);

                                // everything ok
                                if (i == 0)
                                {
                                    // exponent (and precision)
                                    if (match[3].length() > 0)
                                    {
                                        p += std::stoi(match[3].str());
                                    }

                                    mpz_var e;
                                    mpz_ui_pow_ui(e.var_, 10, std::abs(p));

                                    mpq_var exp;
                                    mpq_set_z(exp.var_, e.var_);

                                    // invert if exponent (and precision) is negative
                                    if (p < 0)
                                        mpq_inv(exp.var_, exp.var_);

                                    mpq_var q;

                                    mpq_set_z(q.var_, n.var_);
                                    mpq_mul(q.var_, q.var_, exp.var_);

                                    mpfr_var l;
                                    mpfr_var u;

                                    l.subnormalize(mpfr_set_q(l(), q.var_, MPFR_RNDD), MPFR_RNDD);
                                    u.subnormalize(mpfr_set_q(u(), q.var_, MPFR_RNDU), MPFR_RNDU);

                                    if (mpfr_lessequal_p(l(),u()))
                                    {
                                        bare.first = l.template get<T>(MPFR_RNDD);
                                        bare.second = u.template get<T>(MPFR_RNDU);
                                    }
                                }
                            }
                            else if (match[4].length() > 0) // hex
                            {
                                // number string
                                std::string n_str = match[4].str();

                                // compute precision and remove point
                                int p = n_str.find('.');
                                if (p >= 0)
                                {
                                    n_str.erase(p,1);
                                    p = -(n_str.size() - p);
                                }
                                else
                                {
                                    p = 0;
                                }

                                p *= 4;

                                // parse number as integer
                                mpz_var n;
                                int i = mpz_set_str(n.var_, n_str.c_str(), 0);

                                // everything ok
                                if (i == 0)
                                {
                                    // exponent (and precision)
                                    p += std::stoi(match[5].str());


                                    mpz_var e;
                                    mpz_ui_pow_ui(e.var_, 2, std::abs(p));

                                    mpq_var exp;
                                    mpq_set_z(exp.var_, e.var_);

                                    // invert if exponent (and precision) is negative
                                    if (p < 0)
                                        mpq_inv(exp.var_, exp.var_);

                                    mpq_var q;

                                    mpq_set_z(q.var_, n.var_);
                                    mpq_mul(q.var_, q.var_, exp.var_);

                                    mpfr_var l;
                                    mpfr_var u;

                                    l.subnormalize(mpfr_set_q(l(), q.var_, MPFR_RNDD), MPFR_RNDD);
                                    u.subnormalize(mpfr_set_q(u(), q.var_, MPFR_RNDU), MPFR_RNDU);

                                    if (mpfr_lessequal_p(l(),u()))
                                    {
                                        bare.first = l.template get<T>(MPFR_RNDD);
                                        bare.second = u.template get<T>(MPFR_RNDU);
                                    }
                                }
                            }
                            else if (match[6].length() > 0) // rational
                            {
                                mpq_var q;

                                int i = mpq_set_str(q.var_, (match[6].str() + "/" + match[7].str()).c_str(), 10);

                                mpfr_var l;
                                mpfr_var u;

                                l.subnormalize(mpfr_set_q(l(), q.var_, MPFR_RNDD), MPFR_RNDD);
                                u.subnormalize(mpfr_set_q(u(), q.var_, MPFR_RNDU), MPFR_RNDU);

                                if (i == 0 && mpfr_lessequal_p(l(),u()))
                                {
                                    bare.first = l.template get<T>(MPFR_RNDD);
                                    bare.second = u.template get<T>(MPFR_RNDU);
                                }
                                else
                                {
                                    bare.first = 1.0;
                                    bare.second = -1.0;
                                }
                            }
                        }

                        else    // two arguments
                        {
                            mpfr_var l;
                            mpfr_var u;

                            mpq_var ql;
                            mpq_var qu;

                            mpz_var zl;
                            mpz_var zu;

                            // lower bound

                            // -inf or empty
                            if (match[18].length() > 0 || match[11].length() == 0)
                            {
                                l.set(-std::numeric_limits<T>::infinity(), MPFR_RNDD);
                                dec = p1788::decoration::decoration::dac;
                            }
                            else if (match[12].length() > 0) // float
                            {
                                // number string
                                std::string n_str = match[12].str();

                                // compute precision and remove point
                                int p = n_str.find('.');
                                if (p >= 0)
                                {
                                    n_str.erase(p,1);
                                    p = -(n_str.size() - p);
                                }
                                else
                                {
                                    p = 0;
                                }

                                // parse number as integer
                                int i = mpz_set_str(zl.var_, n_str.c_str(), 10);

                                // everything ok
                                if (i == 0)
                                {
                                    // exponent (and precision)
                                    if (match[13].length() > 0)
                                    {
                                        p += std::stoi(match[13].str());
                                    }

                                    mpz_var e;
                                    mpz_ui_pow_ui(e.var_, 10, std::abs(p));

                                    mpq_var exp;
                                    mpq_set_z(exp.var_, e.var_);

                                    // invert if exponent (and precision) is negative
                                    if (p < 0)
                                        mpq_inv(exp.var_, exp.var_);

                                    mpq_set_z(ql.var_, zl.var_);
                                    mpq_mul(ql.var_, ql.var_, exp.var_);

                                    l.subnormalize(mpfr_set_q(l(), ql.var_, MPFR_RNDD), MPFR_RNDD);
                                }
                                else
                                    l.set(std::numeric_limits<T>::infinity(), MPFR_RNDU);
                            }
                            else if (match[14].length() > 0) // hex
                            {
                                // number string
                                std::string n_str = match[14].str();

                                // compute precision and remove point
                                int p = n_str.find('.');
                                if (p >= 0)
                                {
                                    n_str.erase(p,1);
                                    p = -(n_str.size() - p);
                                }
                                else
                                {
                                    p = 0;
                                }

                                p *= 4;

                                // parse number as integer
                                int i = mpz_set_str(zl.var_, n_str.c_str(), 0);

                                // everything ok
                                if (i == 0)
                                {
                                    // exponent (and precision)
                                    p += std::stoi(match[15].str());

                                    mpz_var e;
                                    mpz_ui_pow_ui(e.var_, 2, std::abs(p));

                                    mpq_var exp;
                                    mpq_set_z(exp.var_, e.var_);

                                    // invert if exponent (and precision) is negative
                                    if (p < 0)
                                        mpq_inv(exp.var_, exp.var_);

                                    mpq_set_z(ql.var_, zl.var_);
                                    mpq_mul(ql.var_, ql.var_, exp.var_);

                                    l.subnormalize(mpfr_set_q(l(), ql.var_, MPFR_RNDD), MPFR_RNDD);
                                }
                                else
                                    l.set(std::numeric_limits<T>::infinity(), MPFR_RNDU);
                            }
                            else if (match[16].length() > 0) // rational
                            {
                                int i = mpq_set_str(ql.var_, (match[16].str() + "/" + match[17].str()).c_str(), 10);

                                if (i == 0)
                                    l.subnormalize(mpfr_set_q(l(), ql.var_, MPFR_RNDD), MPFR_RNDD);
                                else
                                    l.set(std::numeric_limits<T>::infinity(), MPFR_RNDU);
                            }


                            // upper bound

                            // +inf or empty
                            if (match[27].length() > 0 || match[20].length() == 0)
                            {
                                u.set(std::numeric_limits<T>::infinity(), MPFR_RNDU);
                                dec = p1788::decoration::decoration::dac;
                            }
                            else if (match[21].length() > 0) // float
                            {
                                // number string
                                std::string n_str = match[21].str();

                                // compute precision and remove point
                                int p = n_str.find('.');
                                if (p >= 0)
                                {
                                    n_str.erase(p,1);
                                    p = -(n_str.size() - p);
                                }
                                else
                                {
                                    p = 0;
                                }

                                // parse number as integer
                                int i = mpz_set_str(zu.var_, n_str.c_str(), 10);

                                // everything ok
                                if (i == 0)
                                {
                                    // exponent (and precision)
                                    if (match[22].length() > 0)
                                    {
                                        p += std::stoi(match[22].str());
                                    }

                                    mpz_var e;
                                    mpz_ui_pow_ui(e.var_, 10, std::abs(p));

                                    mpq_var exp;
                                    mpq_set_z(exp.var_, e.var_);

                                    // invert if exponent (and precision) is negative
                                    if (p < 0)
                                        mpq_inv(exp.var_, exp.var_);

                                    mpq_set_z(qu.var_, zu.var_);
                                    mpq_mul(qu.var_, qu.var_, exp.var_);

                                    u.subnormalize(mpfr_set_q(u(), qu.var_, MPFR_RNDU), MPFR_RNDU);
                                }
                                else
                                    u.set(-std::numeric_limits<T>::infinity(), MPFR_RNDD);
                            }
                            else if (match[23].length() > 0) // hex
                            {
                                // number string
                                std::string n_str = match[23].str();

                                // compute precision and remove point
                                int p = n_str.find('.');
                                if (p >= 0)
                                {
                                    n_str.erase(p,1);
                                    p = -(n_str.size() - p);
                                }
                                else
                                {
                                    p = 0;
                                }

                                p *= 4;

                                // parse number as integer
                                int i = mpz_set_str(zu.var_, n_str.c_str(), 0);

                                // everything ok
                                if (i == 0)
                                {
                                    // exponent (and precision)
                                    p += std::stoi(match[24].str());

                                    mpz_var e;
                                    mpz_ui_pow_ui(e.var_, 2, std::abs(p));

                                    mpq_var exp;
                                    mpq_set_z(exp.var_, e.var_);

                                    // invert if exponent (and precision) is negative
                                    if (p < 0)
                                        mpq_inv(exp.var_, exp.var_);

                                    mpq_set_z(qu.var_, zu.var_);
                                    mpq_mul(qu.var_, qu.var_, exp.var_);

                                    u.subnormalize(mpfr_set_q(u(), qu.var_, MPFR_RNDU), MPFR_RNDU);
                                }
                                else
                                    u.set(-std::numeric_limits<T>::infinity(), MPFR_RNDD);
                            }
                            else if (match[25].length() > 0) // rational
                            {
                                int i = mpq_set_str(qu.var_, (match[25].str() + "/" + match[26].str()).c_str(), 10);

                                if (i == 0)
                                    u.subnormalize(mpfr_set_q(u(), qu.var_, MPFR_RNDU), MPFR_RNDU);
                                else
                                    u.set(-std::numeric_limits<T>::infinity(), MPFR_RNDD);
                            }


                            if (mpfr_lessequal_p(l(),u())
                                    && (
                                        (match[18].length() > 0 || match[11].length() == 0)
                                        || (match[27].length() > 0 || match[20].length() == 0)
                                        || (mpq_cmp(ql.var_, qu.var_) <= 0)
                                    )
                               )
                            {
                                bare.first = l.template get<T>(MPFR_RNDD);
                                bare.second = u.template get<T>(MPFR_RNDU);
                            }
                        }

                        // Check if bounds are valid
                        if ((std::isnan(bare.first) && std::isnan(bare.second))
                                || (bare.first <= bare.second
                                    &&  bare.first != std::numeric_limits<T>::infinity()
                                    && bare.second != -std::numeric_limits<T>::infinity()))
                        {

                            // check if it is necessary to read a decoration
                            bool read_decoration = false;
                            try
                            {
                                read_decoration = is && is.peek() == '_';
                            }
                            catch (std::ios_base::failure& e)
                            {
                                // rethrow exception if it is not an eof failure
                                if (!is.eof())
                                    throw;
                            }

                            // default decoration
                            if (!read_decoration)
                            {
                                // if is.peek() == '_' reached eof than reset state
                                if (is.eof())
                                    is.clear(std::ios_base::goodbit);

                                x = dec == p1788::decoration::decoration::ill ? nai() : new_dec(bare);

                                // everything was ok
                                return is;
                            }

                            // read decoration
                            if (is && dec != p1788::decoration::decoration::ill)
                            {
                                is.get();   // remove underscore

                                p1788::decoration::decoration d;
                                is >> d;

                                if (is && d <= dec && d != p1788::decoration::decoration::ill)
                                {
                                    // create dec interval
                                    // and adjust decoration in case of an overflow
                                    x = set_dec(bare,
                                                        std::isinf(bare.first) || std::isinf(bare.second) ?
                                                        std::min(d, p1788::decoration::decoration::dac)
                                                        : d);

                                    // everything was ok
                                    return is;
                                }
                            }
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
                for (auto c = is.peek(); is && (std::isdigit(c) || c == '.' || c == '?' || c == '+' || c == '-'); c = is.peek())
                {
                    input += is.get();

                    if (c == '?')
                        break;
                }

                try
                {
                    // read ulps
                    if(is && is.peek() == '?')
                    {
                        input += is.get();
                    }
                    else
                    {
                        while (is && std::isdigit(is.peek()))
                            input += is.get();
                    }

                    // read direction
                    if(is && (is.peek() == 'd' || is.peek() == 'D' || is.peek() == 'u' || is.peek() == 'U'))
                        input += is.get();


                    // read exponent
                    if(is && (is.peek() == 'e' || is.peek() == 'E' ))
                    {
                        input += is.get();


                        if(is.good() && (is.peek() == '-' || is.peek() == '+'))
                            input += is.get();

                        while (is.good() && std::isdigit(is.peek()))
                            input += is.get();
                    }

                }
                catch (std::ios_base::failure& e)
                {
                    // rethrow if failure was not eof
                    if (!is.eof())
                        throw;
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
                        "([+-]?(?:(?:[0-9]*\\.[0-9]+)|(?:[0-9]+[\\.])|(?:[0-9]+)))"          // number
                        "\\?"                                                               // ?
                        "(?:(\\?)|([0-9]+))?"                                               // radius
                        "(?:(u|U)|(d|D))?"                                                  // direction
                        "(?:[eE]([+-]?[0-9]+))?",                                           // exponent
                        std::regex_constants::icase                                         // ignore case
                    );

                    std::smatch match;
                    if (std::regex_match(input, match, uncertain_regex))
                    {
                        // temporary storage of lower and upper bound
                        representation bare;

                        // for valid decorations
                        p1788::decoration::decoration dec = p1788::decoration::decoration::com;

                        mpfr_var::setup();

                        mpfr_var l;
                        mpfr_var u;

                        // number string
                        std::string m_str = match[1].str();

                        // compute precision and remove point
                        int p = m_str.find('.');
                        if (p >= 0)
                        {
                            m_str.erase(p,1);
                            p = -(m_str.size() - p);
                        }
                        else
                        {
                            p = 0;
                        }

                        // parse number as integer
                        mpz_var m;
                        int im = mpz_set_str(m.var_, m_str.c_str(), 10);

                        mpz_var ulps;
                        int iu = 0;

                        // computing ulps
                        if (match[3].length() > 0 )
                            iu = mpz_set_str(ulps.var_, match[3].str().c_str(), 10);
                        else
                        {
                            // 1/2 ulp => m * 10 and ulps=5
                            mpz_set_si(ulps.var_, 5);
                            p--;
                            mpz_mul_si(m.var_, m.var_, 10);
                        }

                        // everything ok
                        if (im == 0 && iu == 0)
                        {
                            // exponent (and precision)
                            if (match[6].length() > 0)
                            {
                                p += std::stoi(match[6].str());
                            }

                            mpz_var e;
                            mpz_ui_pow_ui(e.var_, 10, std::abs(p));

                            mpq_var exp;
                            mpq_set_z(exp.var_, e.var_);

                            // invert if exponent (and precision) is negative
                            if (p < 0)
                                mpq_inv(exp.var_, exp.var_);


                            // compute radius
                            if (match[2].length() > 0)  // "?" => infinity
                            {
                                // compute bounds
                                if (match[4].length() > 0)  // upward
                                {
                                    mpq_var q;
                                    mpq_set_z(q.var_, m.var_);
                                    mpq_mul(q.var_, q.var_, exp.var_);

                                    l.subnormalize(mpfr_set_q(l(), q.var_, MPFR_RNDD), MPFR_RNDD);
                                    u.set(std::numeric_limits<T>::infinity(), MPFR_RNDU);
                                }
                                else if (match[5].length() > 0) // downward
                                {
                                    mpq_var q;
                                    mpq_set_z(q.var_, m.var_);
                                    mpq_mul(q.var_, q.var_, exp.var_);

                                    l.set(-std::numeric_limits<T>::infinity(), MPFR_RNDD);
                                    u.subnormalize(mpfr_set_q(u(), q.var_, MPFR_RNDU), MPFR_RNDU);
                                }
                                else    // symmetric
                                {
                                    l.set(-std::numeric_limits<T>::infinity(), MPFR_RNDD);
                                    u.set(std::numeric_limits<T>::infinity(), MPFR_RNDU);
                                }

                                dec = p1788::decoration::decoration::dac;
                            }
                            else
                            {

                                // compute bounds
                                if (match[4].length() > 0)  // upward
                                {
                                    mpq_var q;

                                    mpq_set_z(q.var_, m.var_);
                                    mpq_mul(q.var_, q.var_, exp.var_);

                                    l.subnormalize(mpfr_set_q(l(), q.var_, MPFR_RNDD), MPFR_RNDD);

                                    mpz_add(m.var_, m.var_, ulps.var_);
                                    mpq_set_z(q.var_, m.var_);
                                    mpq_mul(q.var_, q.var_, exp.var_);

                                    u.subnormalize(mpfr_set_q(u(), q.var_, MPFR_RNDU), MPFR_RNDU);
                                }
                                else if (match[5].length() > 0) // downward
                                {
                                    mpq_var q;

                                    mpq_set_z(q.var_, m.var_);
                                    mpq_mul(q.var_, q.var_, exp.var_);

                                    u.subnormalize(mpfr_set_q(u(), q.var_, MPFR_RNDU), MPFR_RNDU);

                                    mpz_sub(m.var_, m.var_, ulps.var_);
                                    mpq_set_z(q.var_, m.var_);
                                    mpq_mul(q.var_, q.var_, exp.var_);

                                    l.subnormalize(mpfr_set_q(l(), q.var_, MPFR_RNDD), MPFR_RNDD);
                                }
                                else    // symmetric
                                {
                                    mpz_var tmp;
                                    mpq_var q;

                                    mpz_sub(tmp.var_, m.var_, ulps.var_);
                                    mpq_set_z(q.var_, tmp.var_);
                                    mpq_mul(q.var_, q.var_, exp.var_);

                                    l.subnormalize(mpfr_set_q(l(), q.var_, MPFR_RNDD), MPFR_RNDD);

                                    mpz_add(tmp.var_, m.var_, ulps.var_);
                                    mpq_set_z(q.var_, tmp.var_);
                                    mpq_mul(q.var_, q.var_, exp.var_);

                                    u.subnormalize(mpfr_set_q(u(), q.var_, MPFR_RNDU), MPFR_RNDU);
                                }

                            }

                            bare.first = l.template get<T>(MPFR_RNDD);
                            bare.second = u.template get<T>(MPFR_RNDU);

                            // Check if bounds are valid
                            if (bare.first <= bare.second
                                    && bare.first != std::numeric_limits<T>::infinity()
                                    && bare.second != -std::numeric_limits<T>::infinity())
                            {

                                // check if it is necessary to read a decoration
                                bool read_decoration = false;
                                try
                                {
                                    read_decoration = is && is.peek() == '_';
                                }
                                catch (std::ios_base::failure& e)
                                {
                                    // rethrow exception if it is not an eof failure
                                    if (!is.eof())
                                        throw;
                                }

                                // default decoration
                                if (!read_decoration)
                                {
                                    // if is.peek() == '_' reached eof than reset state
                                    if (is.eof())
                                        is.clear(std::ios_base::goodbit);

                                    x = dec == p1788::decoration::decoration::ill ? nai() : new_dec(bare);

                                    // everything was ok
                                    return is;
                                }

                                // read decoration
                                if (is && dec != p1788::decoration::decoration::ill)
                                {
                                    is.get();   // remove underscore

                                    p1788::decoration::decoration d;
                                    is >> d;

                                    if (is && d <= dec && d != p1788::decoration::decoration::ill)
                                    {
                                        // create dec interval
                                        // and adjust decoration in case of an overflow
                                        x = set_dec(bare,
                                                            std::isinf(bare.first) || std::isinf(bare.second) ?
                                                            std::min(d, p1788::decoration::decoration::dac)
                                                            : d);

                                        // everything was ok
                                        return is;
                                    }
                                }
                            }
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
