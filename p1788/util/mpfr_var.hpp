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

#ifndef LIBIEEEP1788_P1788_UTIL_MPFR_VAR_HPP
#define LIBIEEEP1788_P1788_UTIL_MPFR_VAR_HPP

#define MPFR_USE_INTMAX_T

#include <mpfr.h>

//------------------------------------------------------------------------------
// Generic wrapper for MPFR mpfr_t types
//------------------------------------------------------------------------------

namespace p1788
{

namespace util
{

template<mpfr_prec_t PREC_, mpfr_exp_t EMIN_, mpfr_exp_t EMAX_, bool SUBNORMALIZE_, bool AUTOSETUP_>
class mpfr_var
{
public:

    static const mpfr_prec_t PREC = PREC_;
    static const mpfr_exp_t EMIN = EMIN_;
    static const mpfr_exp_t EMAX = EMAX_;
    static const bool SUBNORMALIZE = SUBNORMALIZE_;
    static const bool AUTOSETUP = AUTOSETUP_;

    static void setup();
    static void forced_setup();
    static void free_cache();

    mpfr_var();
    mpfr_var(unsigned long int op, mpfr_rnd_t rnd);
    mpfr_var(long int op, mpfr_rnd_t rnd);
    mpfr_var(float op, mpfr_rnd_t rnd);
    mpfr_var(double op, mpfr_rnd_t rnd);
    mpfr_var(long double op, mpfr_rnd_t rnd);

    ~mpfr_var();

    void set(unsigned long int op, mpfr_rnd_t rnd);
    void set(long int op, mpfr_rnd_t rnd);
    void set(float op, mpfr_rnd_t rnd);
    void set(double op, mpfr_rnd_t rnd);
    void set(long double op, mpfr_rnd_t rnd);

    template<typename T>
    T get(mpfr_rnd_t rnd);

    std::string get_str(mpfr_rnd_t rnd, int b = 10, size_t n = 0);

    mpfr_t& operator() ();

    int subnormalize(int t, mpfr_rnd_t rnd);

private:
    mpfr_t var_;


// Ignore effective C++ warnings
// on GCC  push the last diagnostic state and disable -Weffc++
//FIXME support other compiler
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
    class mpfr_str
    {
    public:
        mpfr_str(mpfr_t var, mpfr_rnd_t rnd, int b, size_t n);

        ~mpfr_str();

        std::string operator() () const;
    private:
        char * char_;
        std::string str_;
    };
// on GCC  enable the diagnostic state -Weffc++ again
#pragma GCC diagnostic pop

};


} // namespace util

} // namespace p1788


#include "p1788/util/mpfr_var_impl.hpp"

#endif // LIBIEEEP1788_P1788_UTIL_MPFR_VAR_HPP
