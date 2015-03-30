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

#ifndef LIBIEEEP1788_P1788_UTIL_MPFR_VAR_HPP
#define LIBIEEEP1788_P1788_UTIL_MPFR_VAR_HPP

#define MPFR_USE_INTMAX_T

#include <mpfr.h>
#include <string>

#include "p1788/io/io_manip.hpp"

//------------------------------------------------------------------------------
// Generic wrapper for MPFR mpfr_t types
//------------------------------------------------------------------------------

namespace p1788
{

namespace util
{

// Wrapper class for mpfr_t
template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_>
class mpfr_var
{
    // Check range
    static_assert(PREC_ > 0, "PREC_ is not greater then 0!");
    static_assert(EMIN_ < 0, "EMIN_ is not less than 0!");
    static_assert(EMAX_ > 0, "EMAX_ is not less than 0!");

public:

    static const mpfr_prec_t PREC = PREC_;
    static const mpfr_exp_t EMIN = EMIN_;
    static const mpfr_exp_t EMAX = EMAX_;
    static const bool SUBNORMALIZE = SUBNORMALIZE_;

    // initialze mpfr system
    static void setup();

    // clears mpfr cache
    static void free_cache();

    // Constructors - initialize mpfr_t var with corresponding value  using the rounding mode rnd
    mpfr_var();

    mpfr_var(unsigned long int op, mpfr_rnd_t rnd);
    mpfr_var(long int op, mpfr_rnd_t rnd);
    mpfr_var(float op, mpfr_rnd_t rnd);
    mpfr_var(double op, mpfr_rnd_t rnd);
    mpfr_var(long double op, mpfr_rnd_t rnd);

    // Destructor
    ~mpfr_var();

    // writes corresponding value to mpfr_t var using the rounding mode rnd
    void set(unsigned long int op, mpfr_rnd_t rnd);
    void set(long int op, mpfr_rnd_t rnd);
    void set(float op, mpfr_rnd_t rnd);
    void set(double op, mpfr_rnd_t rnd);
    void set(long double op, mpfr_rnd_t rnd);

    // Generic getter - it is possible to round the value to a preferred type using the rounding mode rnd
    template<typename T>
    T get(mpfr_rnd_t rnd);

    // Returns a string representation
    // It is possible to specify the outputformat
    std::string get_str(mpfr_rnd_t rnd,
                        p1788::io::number_representation_flags rep,
                        size_t width,
                        size_t precision,
                        p1788::io::text_representation_flags text_rep);

    // Reference to the underlying mpfr_t
    mpfr_t& operator() ();
    mpfr_t const& operator() () const;

    // subnormalization
    int subnormalize(int t, mpfr_rnd_t rnd);

private:
    mpfr_t var_;

};


} // namespace util

} // namespace p1788


#include "p1788/util/mpfr_var_impl.hpp"

#endif // LIBIEEEP1788_P1788_UTIL_MPFR_VAR_HPP
