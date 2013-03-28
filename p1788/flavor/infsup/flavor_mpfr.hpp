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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_HPP

#include <utility>
#include <limits>

#include <mpfr.h>

//------------------------------------------------------------------------------
// MPFR infsup Flavor
//------------------------------------------------------------------------------

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T>
class mpfr_flavor {

static_assert(std::numeric_limits<T>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

public:

    template<typename TT>
    using representation_type = std::pair<TT,TT>;

    // Internal representation
    typedef representation_type<T> representation;



// -----------------------------------------------------------------------------
// Class constructors and methods
// -----------------------------------------------------------------------------

    // Constructors
    static representation constructor_infsup();
    static representation constructor_infsup(T lower, T upper);
    static representation constructor_infsup(T point);

    template<typename ConstRandomAccessIterator>
    static representation constructor_infsup(ConstRandomAccessIterator first,
            ConstRandomAccessIterator last);

    static representation constructor_infsup(std::string const& str);

    static representation constructor_infsup(representation const& other);

    template<typename TT>
    static representation constructor_infsup(representation_type<TT> const& other);

    // Methods
    static T method_lower(representation const& x);
    static T method_upper(representation const& x);
    static T method_mid(representation const& x);
    static T method_rad(representation const& x);

    // Static Methods
    static representation static_method_empty();
    static representation static_method_entire();


// -----------------------------------------------------------------------------
// Input and output
// -----------------------------------------------------------------------------

    template< typename CharT, typename Traits >
    static std::basic_ostream<CharT, Traits>& operator_output(
        std::basic_ostream<CharT, Traits>& os,
        representation const& x);

    template< typename CharT, typename Traits >
    static std::basic_istream<CharT, Traits>& operator_input(
        std::basic_istream<CharT, Traits>& is,
        representation& x);



// -----------------------------------------------------------------------------
// Forward elementary functions
// -----------------------------------------------------------------------------


    static representation pos(representation const& x);

    static representation neg(representation const& x);

    static representation add(representation const& x, representation const& y);

    static representation sub(representation const& x, representation const& y);

    static representation mul(representation const& x, representation const& y);

    static representation div(representation const& x, representation const& y);

    static representation inv(representation const& x);

    static representation sqrt(representation const& x);

    static representation fma(representation const& x, representation const& y,
                              representation const& z );

    static representation interval_case(representation const& c,
                                        representation const& g,
                                        representation const& h );

    static representation sqr(representation const& x);

    static representation pown(representation const& x, int p);

    static representation pow(representation const& x, representation const& y);

    static representation exp(representation const& x);

    static representation exp2(representation const& x);

    static representation exp10(representation const& x);

    static representation log(representation const& x);

    static representation log2(representation const& x);

    static representation log10(representation const& x);

    static representation sin(representation const& x);

    static representation cos(representation const& x);

    static representation tan(representation const& x);

    static representation asin(representation const& x);

    static representation acos(representation const& x);

    static representation atan(representation const& x);

    static representation atan2(representation const& y,
                                representation const& x);

    static representation sinh(representation const& x);

    static representation cosh(representation const& x);

    static representation tanh(representation const& x);

    static representation asinh(representation const& x);

    static representation acosh(representation const& x);

    static representation atanh(representation const& x);

    static representation sign(representation const& x);

    static representation ceil(representation const& x);

    static representation floor(representation const& x);

    static representation trunc(representation const& x);

    static representation round_ties_to_even(representation const& x);

    static representation round_ties_to_away(representation const& x);

    static representation abs(representation const& x);

    template<typename ConstRandomAccessIterator>
    static representation min(ConstRandomAccessIterator first,
                              ConstRandomAccessIterator last);

    template<typename ConstRandomAccessIterator>
    static representation max(ConstRandomAccessIterator first,
                              ConstRandomAccessIterator last);




// -----------------------------------------------------------------------------
// Reverse elementary functions
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Cancellative addition and subtraction
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Non-arithmetic set operations
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Numeric functions on intervals
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Boolean functions on intervals
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Recommended forward elementary functions on intervals
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Recommended interval overlapping
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Recommended slope functions
// -----------------------------------------------------------------------------




private:


class mpfr_var {
public:

    static void setup();


    mpfr_var();
    mpfr_var(float op, mpfr_rnd_t rnd);
    mpfr_var(double op, mpfr_rnd_t rnd);
    mpfr_var(long double op, mpfr_rnd_t rnd);

    ~mpfr_var();

    void set(float op, mpfr_rnd_t rnd);
    void set(double op, mpfr_rnd_t rnd);
    void set(long double op, mpfr_rnd_t rnd);

    T get(mpfr_rnd_t rnd);

    mpfr_t& operator() ();


private:
    mpfr_t var_;
};


};


} // namespace infsup

} // namespace flavor

} // namespace p1788


#include "p1788/flavor/infsup/flavor_mpfr_class_impl.hpp"
#include "p1788/flavor/infsup/flavor_mpfr_io_impl.hpp"
#include "p1788/flavor/infsup/flavor_mpfr_elem_func_impl.hpp"


#include "p1788/flavor/infsup/flavor_mpfr_class_mpfr_var_impl.hpp"

#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_HPP
