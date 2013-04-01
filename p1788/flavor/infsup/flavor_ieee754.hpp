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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_HPP

#include <utility>


//------------------------------------------------------------------------------
// IEEE 754 infsup Flavor - general implementation
//                          fall back for unsupported types
//                          => generates a compile time error
//------------------------------------------------------------------------------

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T>
class ieee754_flavor
{
public:
    typedef struct {} representation;

    static_assert(!std::is_same<T,T>::value,
                  "Type is not supported by this flavor!");
};


} // namespace infsup

} // namespace flavor

} // namespace p1788




//------------------------------------------------------------------------------
// IEEE 754 infsup Flavor - double
//------------------------------------------------------------------------------

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<>
class ieee754_flavor<double>
{
public:

    template<typename T>
    using representation_type = std::pair<T,T>;

    // Internal representation
    typedef representation_type<double> representation;



// -----------------------------------------------------------------------------
// Class constructors and methods
// -----------------------------------------------------------------------------

    // Constructors
    static representation constructor_infsup();
    static representation constructor_infsup(double lower, double upper);
    static representation constructor_infsup(double point);

    template<typename ConstRandomAccessIterator>
    static representation constructor_infsup(ConstRandomAccessIterator first,
            ConstRandomAccessIterator last);

    static representation constructor_infsup(std::string const& str);

    static representation constructor_infsup(representation const& other);

    template<typename T>
    static representation constructor_infsup(representation_type<T> const& other);

    // Methods
    static double method_lower(representation const& x);
    static double method_upper(representation const& x);
    static double method_mid(representation const& x);
    static double method_rad(representation const& x);

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

  static representation sqr_rev(representation const& c,
                                representation const& x);

  static representation sqr_rev(representation const& x);

  static representation inv_rev(representation const& c,
                                representation const& x);

  static representation inv_rev(representation const& x);

  static representation abs_rev(representation const& c,
                                representation const& x);

  static representation abs_rev(representation const& x);

  static representation pown_rev(representation const& c,
                                 representation const& x,
                                 int n);

  static representation pown_rev(representation const& x,
                                 int n);

  static representation sin_rev(representation const& c,
                                representation const& x);

  static representation sin_rev(representation const& x);

  static representation cos_rev(representation const& c,
                                representation const& x);

  static representation cos_rev(representation const& x);

  static representation tan_rev(representation const& c,
                                representation const& x);

  static representation tan_rev(representation const& x);

  static representation cosh_rev(representation const& c,
                                 representation const& x);

  static representation cosh_rev(representation const& x);

  static representation mul_rev(representation const& b,
                                representation const& c,
                                representation const& x);

  static representation mul_rev(representation const& c,
                                representation const& x);

  static representation div_rev1(representation const& b,
                                 representation const& c,
                                 representation const& x);

  static representation div_rev1(representation const& c,
                                 representation const& x);

  static representation div_rev2(representation const& a,
                                 representation const& c,
                                 representation const& x);

  static representation div_rev2(representation const& c,
                                 representation const& x);

  static representation pow_rev1(representation const& b,
                                 representation const& c,
                                 representation const& x);

  static representation pow_rev1(representation const& c,
                                 representation const& x);

  static representation pow_rev2(representation const& a,
                                 representation const& c,
                                 representation const& x);

  static representation pow_rev2(representation const& c,
                                 representation const& x);

  static representation atan2_rev1(representation const& b,
                                   representation const& c,
                                   representation const& x);

  static representation atan2_rev1(representation const& c,
                                   representation const& x);

  static representation atan2_rev2(representation const& a,
                                   representation const& c,
                                   representation const& x);

  static representation atan2_rev2(representation const& c,
                                   representation const& x);


// -----------------------------------------------------------------------------
// Cancellative addition and subtraction
// -----------------------------------------------------------------------------

  static representation cancel_plus(representation const& a,
                                    representation const& b);

  static representation cancel_minus(representation const& a,
                                     representation const& b);

// -----------------------------------------------------------------------------
// Non-arithmetic set operations
// -----------------------------------------------------------------------------

  static representation intersect(representation const& x,
                                  representation const& y);

  static representation hull(representation const& x,
                             representation const& y);

  static representation widen(representation const& x);
// -----------------------------------------------------------------------------
// Numeric functions on intervals
// -----------------------------------------------------------------------------

  static double inf(representation const& x);

  static double sup(representation const& x);

  static double mid(representation const& x);

  static double wid(representation const& x);

  static double rad(representation const& x);

  static double mag(representation const& x);

  static double mig(representation const& x);

  static std::pair<double, double> mid_rad(representation const& x);

// -----------------------------------------------------------------------------
// Boolean functions on intervals
// -----------------------------------------------------------------------------

  static bool is_empty(representation const& x);

  static bool is_entire(representation const& x);

  static bool is_equal(representation const& x, representation const& y);

  static bool contained_in(representation const& x, representation const& y);

  static bool precedes(representation const& x, representation const& y);

  static bool is_enterior(representation const& x, representation const& y);

  static bool strictly_less(representation const& x, representation const& y);

  static bool strictly_precedes(representation const& x, representation const& y);

  static bool are_disjoint(representation const& x, representation const& y);


// -----------------------------------------------------------------------------
// Recommended forward elementary functions on intervals
// -----------------------------------------------------------------------------

  static representation rootn(representation const&, int);

  static representation expm1(representation const&);

  static representation exp2m1(representation const&);

  static representation exp10m1(representation const&);

  static representation logp1(representation const&);

  static representation log2p1(representation const&);

  static representation log10p1(representation const&);

  static representation compoundm1(representation const&,
                                   representation const&);

  static representation hypot(representation const&,
                              representation const&);

  static representation r_sqrt(representation const&);

  static representation sin_pi(representation const&);

  static representation cos_pi(representation const&);

  static representation tan_pi(representation const&);

  static representation asin_pi(representation const&);

  static representation acos_pi(representation const&);

  static representation atan_pi(representation const&);

  static representation atan2_pi(representation const&,
                                 representation const&);


// -----------------------------------------------------------------------------
// Recommended interval overlapping
// -----------------------------------------------------------------------------

  static p1788::overlapping_state overlap(representation const&,
                                          representation const&);


// -----------------------------------------------------------------------------
// Recommended slope functions
// -----------------------------------------------------------------------------

  static representation exp_slope1(representation const&);

  static representation exp_slope2(representation const&);

  static representation log_slope1(representation const&);

  static representation log_slope2(representation const&);

  static representation cos_slope2(representation const&);

  static representation sin_slope3(representation const&);

  static representation asin_slope3(representation const&);

  static representation atan_slope3(representation const&);

  static representation cosh_slope2(representation const&);

  static representation sinh_slope3(representation const&);

};


} // namespace infsup

} // namespace flavor

} // namespace p1788



#include "p1788/flavor/infsup/flavor_ieee754_double_class_impl.hpp"
#include "p1788/flavor/infsup/flavor_ieee754_double_io_impl.hpp"
#include "p1788/flavor/infsup/flavor_ieee754_double_elem_func_impl.hpp"
#include "p1788/flavor/infsup/flavor_ieee754_double_rev_elem_func_impl.hpp"
#include "p1788/flavor/infsup/flavor_ieee754_double_cancel_func_impl.hpp"
#include "p1788/flavor/infsup/flavor_ieee754_double_set_op_impl.hpp"
#include "p1788/flavor/infsup/flavor_ieee754_double_num_func_impl.hpp"
#include "p1788/flavor/infsup/flavor_ieee754_double_bool_func_impl.hpp"
#include "p1788/flavor/infsup/flavor_ieee754_double_rec_elem_func_impl.hpp"
#include "p1788/flavor/infsup/flavor_ieee754_double_rec_overlap_impl.hpp"
#include "p1788/flavor/infsup/flavor_ieee754_double_rec_slope_func_impl.hpp"





//------------------------------------------------------------------------------
// IEEE 754 infsup Flavor - float
//------------------------------------------------------------------------------

namespace p1788
{

namespace flavor
{

namespace infsup
{

template<>
class ieee754_flavor<float>
{
public:

    template<typename T>
    using representation_type = std::pair<T,T>;

    // Internal representation
    typedef representation_type<float> representation;



// -----------------------------------------------------------------------------
// Class constructors and methods
// -----------------------------------------------------------------------------

    // Constructors
    static representation constructor_infsup();
    static representation constructor_infsup(float lower, float upper);
    static representation constructor_infsup(float point);

    template<typename ConstRandomAccessIterator>
    static representation constructor_infsup(ConstRandomAccessIterator first,
            ConstRandomAccessIterator last);

    static representation constructor_infsup(std::string const& str);

    static representation constructor_infsup(representation const& other);

    template<typename T>
    static representation constructor_infsup(representation_type<T> const& other);

    // Methods
    static float method_lower(representation const& x);
    static float method_upper(representation const& x);
    static float method_mid(representation const& x);
    static float method_rad(representation const& x);

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


};


} // namespace infsup

} // namespace flavor

} // namespace p1788



#include "p1788/flavor/infsup/flavor_ieee754_float_class_impl.hpp"
#include "p1788/flavor/infsup/flavor_ieee754_float_io_impl.hpp"
#include "p1788/flavor/infsup/flavor_ieee754_float_elem_func_impl.hpp"







#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_HPP
