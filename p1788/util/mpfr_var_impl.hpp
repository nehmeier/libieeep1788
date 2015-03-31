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

#include <assert.h>

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

template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
mpfr_t const& mpfr_var<PREC_,EMIN_,EMAX_,SUBNORMALIZE_>::operator() () const
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


// Possible MPFR extensions

// Set rop to the kth root of op rounded in the direction rnd.
// For k odd (resp. even) and op negative (including −Inf), set rop to a negative number (resp. NaN).
// The kth root of −0 is defined to be -inf for negative odd k, NaN for negative even k
// and −0 for k nonnegative, whatever the parity of k.
int mpfr_root_si(mpfr_ptr rop, mpfr_srcptr op, long int k, mpfr_rnd_t rnd)
{
    if (k >= 0)
        return mpfr_root(rop, op, (unsigned long int) k, rnd);
    if (k == -1)
        return mpfr_ui_div(rop, 1, op, rnd);
    if (k == -2)
        return mpfr_rec_sqrt(rop, op, rnd);
    if (mpfr_nan_p(op) || ((k & 1) == 0 && mpfr_signbit(op)))
        return mpfr_set_nan(rop), 0;
    if (mpfr_inf_p(op))
        return mpfr_set_zero(rop, mpfr_signbit(op) ? -1 : 1), 0;
    if (mpfr_zero_p(op))
        return mpfr_set_inf(rop, mpfr_signbit(op) ? -1 : 1), 0;

    mpfr_rnd_t rnd_opp = rnd == MPFR_RNDU ? MPFR_RNDD : (assert(rnd == MPFR_RNDD), MPFR_RNDU);
    int t1;
    if (k != -k)
    {
        t1 = mpfr_root(rop, op, -k, rnd_opp);
    }
    else
    {
        int t2 = mpfr_sqrt(rop, op, rnd_opp);
        t1 = mpfr_root(rop, rop, -(k >> 1), rnd_opp);
        if (t1 == 0) t1 = t2;
    }
    int t = mpfr_ui_div(rop, 1, rop, rnd);
    if (t == 0) t = -t1;
    if (t == 0) return 0;

    mpfr_t opm;
    mpfr_init2(opm, mpfr_get_prec(op));
    for (;;)
    {
        if (rnd == MPFR_RNDU)
            mpfr_nextbelow(rop);
        else
            mpfr_nextabove(rop);
        if (!mpfr_regular_p(rop)) break;
        t1 = mpfr_pow_si(opm, rop, k, rnd_opp);
        t = mpfr_cmp(op, opm);
        if (t == 0) t = t1;
        if (t == 0) return mpfr_clear(opm), 0;
        if (rnd == MPFR_RNDU ? t < 0 : t > 0) break;
    }
    mpfr_clear(opm);
    if (rnd == MPFR_RNDU)
    {
        mpfr_nextabove(rop);
        return 1;
    }
    else
    {
        mpfr_nextbelow(rop);
        return -1;
    }
}


// Set k to the integer part of the division of x by Pi/2
// the result is exact
void mpfr_quadrant (mpz_ptr k, mpfr_srcptr op)
{
    mpfr_prec_t prec = mpfr_get_prec(op);
    if (mpfr_sgn(op) == 0)
    {
        mpz_set_ui(k, 0);
        return;
    }

    mpfr_exp_t saved_emin = mpfr_get_emin();
    mpfr_exp_t saved_emax = mpfr_get_emax();
    mpfr_set_emin(mpfr_get_emin_min());
    mpfr_set_emax(mpfr_get_emax_max());
    for (;;) 
    {
        mpfr_t k_inf, k_sup;

        mpfr_init2(k_inf, prec);
        mpfr_const_pi(k_inf, MPFR_RNDU);
        mpfr_div(k_inf, op, k_inf, MPFR_RNDD);
        mpfr_mul_2ui(k_inf, k_inf, 1, MPFR_RNDD);
        mpfr_floor(k_inf, k_inf);

        mpfr_init2(k_sup, prec);
        mpfr_const_pi(k_sup, MPFR_RNDD);
        mpfr_div(k_sup, op, k_sup, MPFR_RNDU);
        mpfr_mul_2ui(k_sup, k_sup, 1, MPFR_RNDU);
        mpfr_floor(k_sup, k_sup);

        if (mpfr_cmp(k_inf, k_sup) == 0)
        {
            mpfr_get_z(k, k_inf, MPFR_RNDN);
            mpfr_clear(k_inf);
            mpfr_clear(k_sup);
            mpfr_set_emin(saved_emin);
            mpfr_set_emax(saved_emax);
            return;
        }
        mpfr_clear(k_inf);
        mpfr_clear(k_sup);
        prec += mpfr_get_prec(op);
    }
}

static int mpfr_atrig(mpfr_ptr rop, mpfr_srcptr op, int (*fun)(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd), int sub, mpz_t npi, mpfr_rnd_t rnd)
{
    assert(rnd == MPFR_RNDU || rnd == MPFR_RNDD);
    int t;
    if (mpz_sgn(npi) == 0)
    {
        if (sub)
        {
            mpfr_rnd_t rnd1 = rnd == MPFR_RNDU ? MPFR_RNDD : (assert(rnd == MPFR_RNDD), MPFR_RNDU);
            t = -(*fun)(rop, op, rnd1);
            mpfr_neg(rop, rop, rnd);
        }
        else
        {
            t = (*fun)(rop, op, rnd);
        }
        return t;
    }
    mpfr_exp_t emin_rop = mpfr_get_emin();
    mpfr_exp_t emax_rop = mpfr_get_emax();
    mpfr_set_emin(mpfr_get_emin_min());
    mpfr_set_emax(mpfr_get_emax_max());
    mpfr_prec_t prec = mpfr_get_prec(rop) * 2;
    for (;;)
    {
        mpfr_t pi, inf, sup;
        mpfr_init2(pi, prec);
        mpfr_init2(inf, prec);
        mpfr_init2(sup, prec);

        mpfr_const_pi(pi, MPFR_RNDD);
        mpfr_mul_z(pi, pi, npi, MPFR_RNDD);
        if (sub) 
        {
            (*fun)(sup, op, MPFR_RNDU);
            mpfr_sub(sup, pi, sup, MPFR_RNDD);
        }
        else
        {
            (*fun)(inf, op, MPFR_RNDD);
            mpfr_add(inf, pi, inf, MPFR_RNDD);
        }

        mpfr_const_pi(pi, MPFR_RNDU);
        mpfr_mul_z(pi, pi, npi, MPFR_RNDU);
        if (sub) 
        {
            (*fun)(inf, op, MPFR_RNDD);
            mpfr_sub(inf, pi, inf, MPFR_RNDU);
        }
        else
        {
            (*fun)(sup, op, MPFR_RNDU);
            mpfr_add(sup, pi, sup, MPFR_RNDU);
        }

        mpfr_clear(pi);
        mpfr_prec_round(inf, mpfr_get_prec(rop), rnd);
        mpfr_prec_round(sup, mpfr_get_prec(rop), rnd);
        if (mpfr_cmp(inf, sup) == 0)
        {
            mpfr_set(rop, inf, rnd);
            mpfr_clear(inf);
            mpfr_clear(sup);
            mpfr_set_emin(emin_rop);
            mpfr_set_emax(emax_rop);
            return mpfr_check_range(rop, rnd == MPFR_RNDU ? 1 : -1, rnd);
        }
        mpfr_clear(inf);
        mpfr_clear(sup);
        prec += mpfr_get_prec(rop);
    }
}

// rop = (-1)^npi * asin(op) + npi*pi
int mpfr_asin_npi(mpfr_ptr rop, mpfr_srcptr op, mpz_t npi, mpfr_rnd_t rnd)
{
    return mpfr_atrig(rop, op, mpfr_asin, mpz_tstbit(npi, 0), npi, rnd);
}

// rop = (-1)^npi * acos(op) + (npi + (1 - (-1)^npi)/2)*pi
int mpfr_acos_npi(mpfr_ptr rop, mpfr_srcptr op, mpz_t npi, mpfr_rnd_t rnd)
{
    int sub = mpz_tstbit(npi, 0);
    int t;
    if (sub) {
        mpz_t npi1;
        mpz_init(npi1);
        mpz_add_ui(npi1, npi, 1);
        t = mpfr_atrig(rop, op, mpfr_acos, sub, npi1, rnd);
        mpz_clear(npi1);
    }
    else
    {
        t = mpfr_atrig(rop, op, mpfr_acos, sub, npi, rnd);
    }
    return t;
}

// rop = atan(op) + npi*pi
int mpfr_atan_npi(mpfr_ptr rop, mpfr_srcptr op, mpz_t npi, mpfr_rnd_t rnd)
{
    return mpfr_atrig(rop, op, mpfr_atan, 0, npi, rnd);
}

} // namespace util

} // namespace p1788


#endif // LIBIEEEP1788_P1788_UTIL_MPFR_VAR_IMPL_HPP
