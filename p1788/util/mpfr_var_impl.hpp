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

#ifndef LIBIEEEP1788_P1788_UTIL_MPFR_VAR_IMPL_HPP
#define LIBIEEEP1788_P1788_UTIL_MPFR_VAR_IMPL_HPP


namespace p1788
{

namespace util
{

// Trait to return the value as the preferred type
template<typename T> class mpfr_get_trait
{
    static_assert(!std::is_same<T,T>::value,
                  "Type is not supported by mpfr_get_trait!");
};

// float
template<> class mpfr_get_trait<float>
{
public:
    static float apply(mpfr_t& mp, mpfr_rnd_t rnd)
    {
        return mpfr_get_flt(mp, rnd);
    }
};

// double
template<> class mpfr_get_trait<double>
{
public:
    static double apply(mpfr_t& mp, mpfr_rnd_t rnd)
    {
        return mpfr_get_d(mp, rnd);
    }
};

// long double
template<> class mpfr_get_trait<long double>
{
public:
    static long double apply(mpfr_t& mp, mpfr_rnd_t rnd)
    {
        return mpfr_get_ld(mp, rnd);
    }
};

// long int
template<> class mpfr_get_trait<long int>
{
public:
    static long int apply(mpfr_t& mp, mpfr_rnd_t rnd)
    {
        return mpfr_get_si(mp, rnd);
    }
};

// unsigned long int
template<> class mpfr_get_trait<unsigned long int>
{
public:
    static unsigned long int apply(mpfr_t& mp, mpfr_rnd_t rnd)
    {
        return mpfr_get_ui(mp, rnd);
    }
};


// Trait to apply subnormalization if necessary
template<bool SUBNORMALIZE>
class subnormalization_trait
{
public:
    static int apply(mpfr_t&, int t, mpfr_rnd_t)
    {
        // Nothing to do
        return t;
    }
};


// subnormalize
template<>
class subnormalization_trait<true>
{
public:
    static int apply(mpfr_t& x, int t, mpfr_rnd_t rnd)
    {
        return mpfr_subnormalize(x, t, rnd);
    }
};


// setup function - initialize the mpfr system
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
void mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::setup()
{
    mpfr_set_emin(EMIN_);
    mpfr_set_emax(EMAX_);
}

// clears the mpfr cache
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
void mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::free_cache()
{
    mpfr_free_cache();
}

// default constructor - value is NaN
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::mpfr_var()
{
    mpfr_init2(var_, PREC_);
}

// constructor - value is nearest to op in the corresponding rounding direction rnd
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::mpfr_var(unsigned long int op, mpfr_rnd_t rnd) : mpfr_var()
{
    set(op, rnd);
}

// constructor - value is nearest to op in the corresponding rounding direction rnd
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::mpfr_var(long int op, mpfr_rnd_t rnd) : mpfr_var()
{
    set(op, rnd);
}

// constructor - value is nearest to op in the corresponding rounding direction rnd
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::mpfr_var(float op, mpfr_rnd_t rnd) : mpfr_var()
{
    set(op, rnd);
}

// constructor - value is nearest to op in the corresponding rounding direction rnd
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::mpfr_var(double op, mpfr_rnd_t rnd) : mpfr_var()
{
    set(op, rnd);
}

// constructor - value is nearest to op in the corresponding rounding direction rnd
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::mpfr_var(long double op, mpfr_rnd_t rnd) : mpfr_var()
{
    set(op, rnd);
}

// Destructor
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::~mpfr_var()
{
    mpfr_clear(var_);
}

// setter - value is nearest to op in the corresponding rounding direction rnd
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
void mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::set(unsigned long int op, mpfr_rnd_t rnd)
{
    subnormalize(mpfr_set_ui(var_, op, rnd), rnd);
}

// setter - value is nearest to op in the corresponding rounding direction rnd
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
void mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::set(long int op, mpfr_rnd_t rnd)
{
    subnormalize(mpfr_set_si(var_, op, rnd), rnd);
}

// setter - value is nearest to op in the corresponding rounding direction rnd
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
void mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::set(float op, mpfr_rnd_t rnd)
{
    subnormalize(mpfr_set_flt(var_, op, rnd), rnd);
}

// setter - value is nearest to op in the corresponding rounding direction rnd
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
void mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::set(double op, mpfr_rnd_t rnd)
{
    subnormalize(mpfr_set_d(var_, op, rnd), rnd);
}

// setter - value is nearest to op in the corresponding rounding direction rnd
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
void mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::set(long double op, mpfr_rnd_t rnd)
{
    subnormalize(mpfr_set_ld(var_, op, rnd), rnd);
}

// getter - returns the value as the preferred type using the rounding direction rnd
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
template<typename T>
T mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::get(mpfr_rnd_t rnd)
{
    return p1788::util::mpfr_get_trait<T>::apply(var_, rnd);
}

// Returns a string representation
// It is possible to specify the output format
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
std::string mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::get_str(mpfr_rnd_t rnd,
        p1788::io::number_representation_flags rep,
        size_t width,
        size_t precision,
        p1788::io::text_representation_flags text_rep)
{
    std::string format = width > 0 ? "%" + std::to_string(width) : "%";

    size_t req_string_width =  0;

    switch (rep)
    {
    case p1788::io::decimal_representation:
        format += precision > 0 ? "." + std::to_string(precision) : ".6";   // default precision is 6
        format += "R*";
        format += text_rep == p1788::io::upper_case_text_representation ? "F" : "f";

        {
            // Compute  upper bound for required integer digits
            mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_> req_digits;
            mpfr_abs(req_digits(), var_, MPFR_RNDU);
            mpfr_log10(req_digits(), req_digits(), MPFR_RNDU);

            req_string_width = 1                                                             // for the sign
                               + req_digits.template get<unsigned long int>(MPFR_RNDD) + 1   // for the digits
                               + 3                                                           // for dot
                               + precision > 0 ? precision : 6;                              // for the digits

            if (width > req_string_width)
                req_string_width = width;
        }
        break;
    case p1788::io::scientific_representation:
        format += precision > 0 ? "." + std::to_string(precision) : ".6";   // default precision is 6
        format += "R*";
        format += text_rep == p1788::io::upper_case_text_representation ? "E" : "e";
        {
            // Compute  upper bound of required exponent digits
            mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_> req_exp(std::max(-EMIN_, EMAX_) + 1, MPFR_RNDU);
            mpfr_div_d(req_exp(), req_exp(), 3.0, MPFR_RNDU);     // 1/3 is an upper bound for log10(2)
            mpfr_log10(req_exp(), req_exp(), MPFR_RNDU);

            req_string_width = 3                                                            // for the pattern "-1."
                               + precision > 0 ? precision : 6                              // for the digits
                               + 2                                                          // for the pattern "E+"
                               + req_exp.template get<unsigned long int>(MPFR_RNDD) + 1;    // for exponent digits

            if (width > req_string_width)
                req_string_width = width;
        }
        break;
    case p1788::io::hex_representation:
        format += precision > 0 ? "." + std::to_string(precision) : "";     // no precision prints sufficient digits for an exact rep
        format += "R*";
        format += text_rep == p1788::io::upper_case_text_representation ? "A" : "a";
        {
            // Compute  upper bound of required hex digits
            mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_> req_prec(PREC_, MPFR_RNDU);
            mpfr_div_d(req_prec(), req_prec(), 4.0, MPFR_RNDU);     // 4 mantissa bits per hex digit

            // Compute  upper bound of required exponent digits
            mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_> req_exp(std::max(-EMIN_, EMAX_) + 1, MPFR_RNDU);
            mpfr_div_d(req_exp(), req_exp(), 3.0, MPFR_RNDU);     // 1/3 is an upper bound for log10(2)
            mpfr_log10(req_exp(), req_exp(), MPFR_RNDU);

            req_string_width = 5                                                            // for the pattern "-0X1."
                               + req_prec.template get<unsigned long int>(MPFR_RNDU) + 1    // for the hex digits
                               + 2                                                          // for the pattern "P+"
                               + req_exp.template get<unsigned long int>(MPFR_RNDD) + 1;    // for exponent digits

            if (width > req_string_width)
                req_string_width = width;
        }
        break;
    default:    // decimal_scientific
        format += precision > 0 ? "." + std::to_string(precision) : ".6";   // default precision is 6
        format += "R*";
        format += text_rep == p1788::io::upper_case_text_representation ? "G" : "g";
        {
            // Compute  upper bound of required integer digits
            mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_> req_digits;
            mpfr_abs(req_digits(), var_, MPFR_RNDU);
            mpfr_log10(req_digits(), req_digits(), MPFR_RNDU);

            // Compute  upper bound of required exponent digits
            mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_> req_exp(std::max(-EMIN_, EMAX_) + 1, MPFR_RNDU);
            mpfr_div_d(req_exp(), req_exp(), 3.0, MPFR_RNDU);     // 1/3 is an upper bound for log10(2)
            mpfr_log10(req_exp(), req_exp(), MPFR_RNDU);

            req_string_width = 1                                                             // for the sign
                               + req_digits.template get<unsigned long int>(MPFR_RNDD) + 1   // for the digits
                               + 3                                                           // for dot
                               + precision > 0 ? precision : 6                               // for the digits
                               + 2                                                           // for the pattern "E+"
                               + req_exp.template get<unsigned long int>(MPFR_RNDD) + 1;     // for exponent digits

            if (width > req_string_width)
                req_string_width = width;
        }
        break;
    }

    // RAII for char array
    struct string_buffer
    {
        char* data;

        string_buffer(size_t n)
        {
            data = new char[n + 1];     // take "\0" into account
        }

        ~string_buffer()
        {
            delete[] data;
        };
    } buffer(req_string_width);

    // generate string
    mpfr_sprintf(buffer.data, format.c_str(), rnd, var_ );
    return buffer.data;
}

// Reference to the underlying mpfr_t
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
mpfr_t& mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::operator() ()
{
    return var_;
}

// subnormalization of the value
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
int mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::subnormalize(int t, mpfr_rnd_t rnd)
{
    // use traite to distinguish to only apply subnormalization if necessary
    return p1788::util::subnormalization_trait<SUBNORMALIZE_>::apply(var_, t, rnd);
}




} // namespace util

} // namespace p1788


#endif // LIBIEEEP1788_P1788_UTIL_MPFR_VAR_IMPL_HPP
