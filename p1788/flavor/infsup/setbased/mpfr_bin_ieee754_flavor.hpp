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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_HPP

#include <utility>
#include <limits>
#include <cfenv>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "p1788/decoration/decoration.hpp"
#include "p1788/overlapping/overlapping.hpp"
#include "p1788/util/eft.hpp"
#include "p1788/util/assert.hpp"
#include "p1788/util/mpfr_var.hpp"
#include "p1788/util/mixed_type_traits.hpp"


//------------------------------------------------------------------------------
// MPFR infsup Flavor
//------------------------------------------------------------------------------

namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{



/// \brief tesxt
///
/// \tparam T Type of the interval bounds
///
///
template<typename T>
class mpfr_bin_ieee754_flavor
{

    static_assert(std::numeric_limits<T>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

public:

    // Typedef for the corresponding mpfr wrapper class representing the IEEE 754 binary floating point format of type T
    typedef p1788::util::mpfr_var<
    std::numeric_limits<T>::digits,
        std::numeric_limits<T>::has_denorm != std::denorm_present ? std::numeric_limits<double>::min_exponent
        : std::numeric_limits<double>::min_exponent - std::numeric_limits<double>::digits + 1,
        std::numeric_limits<double>::max_exponent,
        std::numeric_limits<T>::has_denorm == std::denorm_present
        >   mpfr_var;


    /// \brief Type-structure for the internal representation of bare intervals
    ///
    /// It is a <c>std::pair\<TT,TT\></c> of two values of type \p TT to store the lower (<c>first</c>) and
    /// the upper (<c>second</c>) bound of an bare interval.
    ///
    /// \tparam TT Type of the lower and upper bound of a bare interval.
    ///
    template<typename TT>
    using representation_type = std::pair<TT,TT>;


    /// \brief Type-structure for the internal representation of decorated intervals
    ///
    /// It is a <c>std::pair\<\link mpfr_bin_ieee754_flavor::representation_type representation_type\<TT\>\endlink,p1788::decoration::decoration\></c>
    /// to store a bare interval of type <c>\link mpfr_bin_ieee754_flavor::representation_type representation_type\<TT\>\endlink</c> in the <c>first</c> member and the
    /// the decoration of type p1788::decoration::decoration in the (<c>second</c>) member.
    ///
    /// \tparam TT Type of the lower and upper bound of a decorated interval.
    ///
    template<typename TT>
    using representation_dec_type = std::pair<representation_type<TT>, p1788::decoration::decoration>;



// -----------------------------------------------------------------------------
// Typed for internal representation
// -----------------------------------------------------------------------------

    /// \brief Type for the internal representation of bare intervals
    ///
    /// Type-structure <c>\link mpfr_bin_ieee754_flavor::representation_type representation_type\<T\>\endlink</c>
    /// distincted with with the type \p T.
    ///
    typedef representation_type<T> representation;

    /// \brief Type for the internal representation of decorated intervals
    ///
    /// Type-structure <c>\link mpfr_bin_ieee754_flavor::representation_dec_type representation_dec_type\<T\>\endlink</c>
    /// distincted with with the type \p T.
    ///
    typedef representation_dec_type<T> representation_dec;


// -----------------------------------------------------------------------------
// Setup functions
//
// p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_setup_func_impl.hpp
// -----------------------------------------------------------------------------

///@name Setup functions
///
///
///@{

    /// \todo document
    ///
    ///
    static void setup();

    /// \todo document
    ///
    ///
    static void teardown();
///@}


// -----------------------------------------------------------------------------
// Utility functions
//
// p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_util_func_impl.hpp
// -----------------------------------------------------------------------------

///@name Utility functions
///
///
///@{

    /// \brief Converts a floating point number of type \p T_ to a floating point number of type \p T using rounding to \f$-\infty\f$.
    ///
    /// \tparam T_ Type of the original number format.
    /// \pre \p T_ hast to fulfill the requirements of IEC559 / IEEE754, see \c std::numeric_limits::is_iec559.
    ///
    /// \param x Value in the original number format \p T_.
    ///
    /// \return Largest number of type \p T \f$\leq\f$ \p x. It returns -0.0 in case of a zero.
    ///
    /// \note Round toward negative follows the IEEE754 specification.
    ///
    ///
    template<typename T_>
    static T convert_rndd(T_ x);

    /// \brief Converts a floating point number of type \p T_ to the closest floating point number of type \p T.
    ///
    /// \tparam T_ Type of the original number format.
    /// \pre \p T_ hast to fulfill the requirements of IEC559 / IEEE754, see \c std::numeric_limits::is_iec559.
    ///
    /// \param x Value in the original number format \p T_.
    ///
    /// \return Closest number of type \p T to the number \p x.
    /// If \p x lies exactly in the middle of two consecutive numbers of type \p T than it is rounded to the one with least significant equal to zero.
    /// It returns +0.0 in case of a zero.
    ///
    /// \note Round to nearest follows the IEEE754 specification.
    ///
    ///
    template<typename T_>
    static T convert_rndn(T_ x);

    /// \brief Converts a floating point number of type \p T_ to a floating point number of type \p T using rounding to \f$+\infty\f$.
    ///
    /// \tparam T_ Type of the original number format.
    /// \pre \p T_ hast to fulfill the requirements of IEC559 / IEEE754, see \c std::numeric_limits::is_iec559.
    ///
    /// \param x Value in the original number format \p T_.
    ///
    /// \return Smallest number of type \p T \f$\geq\f$ \p x. It returns +0.0 in case of a zero.
    ///
    /// \note Round toward positive follows the IEEE754 specification.
    ///
    ///
    template<typename T_>
    static T convert_rndu(T_ x);

    /// \brief Converts an interval representation of type \p mpfr_bin_ieee754_flavor<T_>::representation to
    /// an interval representation of type \p mpfr_bin_ieee754_flavor<T>::representation by using the interval hull (outward rounding).
    ///
    /// \tparam T_ Type of the number format of the original bound type.
    /// \pre \p T_ hast to fulfill the requirements of IEC559 / IEEE754, see \c std::numeric_limits::is_iec559.
    ///
    /// \param x Interval representation with the original bound type \p T_.
    ///
    /// \return Tightest interval representation with bound type \p T containing \p x.
    ///
    /// \note \ref pageAccuracy "Accuracy:" Tightest
    /// \note Outward rounding uses round toward negative and positive which follow the IEEE754 specification.
    ///
    ///
    template<typename T_>
    static representation convert_hull(representation_type<T_> const& x);

    /// \brief Converts an decorated interval representation of type \p mpfr_bin_ieee754_flavor<T_>::representation_dec to
    /// an decorated interval representation of type \p mpfr_bin_ieee754_flavor<T>::representation_dec by using the interval hull (outward rounding).
    ///
    /// \tparam T_ Type of the number format of the original bound type.
    /// \pre \p T_ hast to fulfill the requirements of IEC559 / IEEE754, see \c std::numeric_limits::is_iec559.
    ///
    /// \param x Decorated interval representation with the original bound type \p T_.
    ///
    /// \return Tightest decorated interval representation with bound type \p T containing \p x. The decoration is unchanged.
    ///
    /// \note \ref pageAccuracy "Accuracy:" Tightest
    /// \note Outward rounding uses round toward negative and positive which follow the IEEE754 specification.
    ///
    ///
    template<typename T_>
    static representation_dec convert_hull(representation_dec_type<T_> const& x);

///@}



// -----------------------------------------------------------------------------
// Constructors, Methods, Interval constants
//
// p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_class_impl.hpp
// -----------------------------------------------------------------------------

    // Constructors
    static representation constructor_infsup();
    static representation_dec constructor_infsup_dec();

    static representation constructor_infsup(T lower, T upper);
    static representation_dec constructor_infsup_dec(T lower, T upper);

    static representation constructor_infsup(T point);
    static representation_dec constructor_infsup_dec(T point);

    template<typename L, typename U>
    static representation constructor_infsup(L lower, U upper);
    template<typename L, typename U>
    static representation_dec constructor_infsup_dec(L lower, U upper);

    template<typename T_>
    static representation constructor_infsup(T_ point);
    template<typename T_>
    static representation_dec constructor_infsup_dec(T_ point);

    static representation constructor_infsup(std::string const& str);
    static representation_dec constructor_infsup_dec(std::string const& str);

//TODO Points constructor necessary? initializer list?
//    template<typename ConstRandomAccessIterator>
//    static representation constructor_infsup(ConstRandomAccessIterator first,
//            ConstRandomAccessIterator last);
//    template<typename ConstRandomAccessIterator>
//    static representation_dec constructor_infsup_dec(ConstRandomAccessIterator first,
//            ConstRandomAccessIterator last);

    static representation constructor_infsup(representation const& other);
    static representation_dec constructor_infsup_dec(representation_dec const& other);

    template<typename TT>
    static representation constructor_infsup(representation_type<TT> const& other);
    template<typename TT>
    static representation_dec constructor_infsup_dec(representation_dec_type<TT> const& other);

    // Methods
    static T method_lower(representation const& x);
    static T method_lower(representation_dec const& x);

    static T method_upper(representation const& x);
    static T method_upper(representation_dec const& x);

    static T method_mid(representation const& x);
    static T method_mid(representation_dec const& x);

    static T method_rad(representation const& x);
    static T method_rad(representation_dec const& x);

    static p1788::decoration::decoration method_decoration(representation_dec const& x);


///@name Interval constants
///
///
///@{

    /// \brief Returns a \link mpfr_bin_ieee754_flavor::representation representation\endlink for an empty bare interval
    ///
    /// \return representation(NaN, NaN)
    ///
    ///
    static representation empty();

    /// \brief Returns a \link mpfr_bin_ieee754_flavor::representation_dec representation_dec\endlink for an empty decorated interval
    ///
    /// \return representation_dec(representation(NaN, NaN), \link p1788::decoration::decoration trv\endlink)
    ///
    ///
    static representation_dec empty_dec();

    /// \brief Returns a \link mpfr_bin_ieee754_flavor::representation representation\endlink for an entire bare interval
    ///
    /// \return representation(\f$-\infty\f$, \f$+\infty\f$)
    ///
    ///
    static representation entire();

    /// \brief Returns a \link mpfr_bin_ieee754_flavor::representation_dec representation_dec\endlink for an entire decorated interval
    ///
    /// \return representation_dec(representation(\f$-\infty\f$, \f$+\infty\f$), \link p1788::decoration::decoration dac\endlink)
    ///
    ///
    static representation_dec entire_dec();

    /// \brief Returns a \link mpfr_bin_ieee754_flavor::representation_dec representation_dec\endlink for an ill-formend decorated interval (Not an Interval)
    ///
    /// \return representation_dec(representation(NaN, NaN), \link p1788::decoration::decoration ill\endlink)
    ///
    ///
    static representation_dec nai();

///@}

// -----------------------------------------------------------------------------
// Input and output
// -----------------------------------------------------------------------------


//template<typename T_, typename CharT, typename Traits>
//friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>&, typename mpfr_bin_ieee754_flavor<T_>::representation_type const&);

///@name Input and output
///
///
///@{

    /// \todo TODO
    ///
    ///
    template< typename CharT, typename Traits >
    static std::basic_ostream<CharT, Traits>& operator_output(
        std::basic_ostream<CharT, Traits>& os,
        representation const& x);

    /// \todo TODO
    ///
    ///
    template< typename CharT, typename Traits >
    static std::basic_ostream<CharT, Traits>& operator_output(
        std::basic_ostream<CharT, Traits>& os,
        representation_dec const& x);

    /// \todo TODO
    ///
    ///
    template< typename CharT, typename Traits >
    static std::basic_istream<CharT, Traits>& operator_input(
        std::basic_istream<CharT, Traits>& is,
        representation& x);

    /// \todo TODO
    ///
    ///
    template< typename CharT, typename Traits >
    static std::basic_istream<CharT, Traits>& operator_input(
        std::basic_istream<CharT, Traits>& is,
        representation_dec& x);

///@}

// -----------------------------------------------------------------------------
// Set operations
//
// p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_set_op_impl.hpp
// -----------------------------------------------------------------------------

///@name Set operations
///
///
///@{

    /// \todo Docu, Test
    ///
    ///
    static representation intersect(representation const& x,
                                    representation const& y);


    /// \todo Docu, Test
    ///
    ///
    template<typename T1_, typename T2_>
    static representation intersect(representation_type<T1_> const& x,
                                    representation_type<T2_> const& y);

    /// \todo Docu, Test
    ///
    ///
    static representation_dec intersect(representation_dec const& x,
                                        representation_dec const& y);

    /// \todo Docu, Test
    ///
    ///
    template<typename T1_, typename T2_>
    static representation_dec intersect(representation_dec_type<T1_> const& x,
                                        representation_dec_type<T2_> const& y);

    /// \todo Docu, Test
    ///
    ///
    static representation hull(representation const& x,
                               representation const& y);

    /// \todo Docu, Test
    ///
    ///
    template<typename T1_, typename T2_>
    static representation hull(representation_type<T1_> const& x,
                               representation_type<T2_> const& y);

    /// \todo Docu, Test
    ///
    ///
    static representation_dec hull(representation_dec const& x,
                                   representation_dec const& y);

    /// \todo Docu, Test
    ///
    ///
    template<typename T1_, typename T2_>
    static representation_dec hull(representation_dec_type<T1_> const& x,
                                   representation_dec_type<T2_> const& y);

///@}

// -----------------------------------------------------------------------------
// Numeric functions on intervals
// -----------------------------------------------------------------------------

///@name Numeric functions on intervals
///
///
///@{


    /// \brief Infimum of a bare interval representation
    ///
    /// \param x Interval representation
    /// \return \li \f$+\infty\f$ if \p x is empty
    ///         \li -0 if the lower bound of \p x is zero
    ///         \li lower bound of \p x otherwise
    ///
    static T inf(representation const& x);

    /// \brief Mixed-type version of <c>\link mpfr_bin_ieee754_flavor::inf(representation const& x) inf\endlink</c>.
    ///
    /// \param x Interval representation
    /// \return Result of <c>\link mpfr_bin_ieee754_flavor::inf(representation const& x) inf\endlink</c> converted
    ///         to the type \p T_ using rounding to \f$-\infty\f$.
    ///
    ///
    template<typename T_>
    static T inf(representation_type<T_> const& x);


    /// \brief Infimum of a decorated interval representation
    ///
    /// \param x Decorated interval representation
    /// \return \li NaN if \p is NaI
    ///         \li \f$+\infty\f$ if \p x is empty
    ///         \li -0 if the lower bound of \p x is zero
    ///         \li lower bound of \p x otherwise
    ///
    static T inf(representation_dec const& x);

    /// \brief Mixed-type version of <c>\link mpfr_bin_ieee754_flavor::inf(representation_dec const& x) inf\endlink</c>.
    ///
    /// \param x Decorated interval representation
    /// \return Result of <c>\link mpfr_bin_ieee754_flavor::inf(representation_dec const& x) inf\endlink</c> converted
    ///         to the type \p T_ using rounding to \f$-\infty\f$.
    ///
    ///
    template<typename T_>
    static T inf(representation_dec_type<T_> const& x);

    /// \brief Supremum of a bare interval representation
    ///
    /// \param x Interval representation
    /// \return \li \f$-\infty\f$ if \p x is empty
    ///         \li +0 if the upper bound of \p x is zero
    ///         \li upper bound of \p x otherwise
    ///
    static T sup(representation const& x);

    /// \brief Mixed-type version of <c>\link mpfr_bin_ieee754_flavor::sup(representation const& x) sup\endlink</c>.
    ///
    /// \param x Interval representation
    /// \return Result of <c>\link mpfr_bin_ieee754_flavor::sup(representation const& x) sup\endlink</c> converted
    ///         to the type \p T_ using rounding to \f$+\infty\f$.
    ///
    ///
    template<typename T_>
    static T sup(representation_type<T_> const& x);

    /// \brief Supremum of a decorated interval representation
    ///
    /// \param x Decorated interval representation
    /// \return \li NaN if \p is NaI
    ///         \li \f$-\infty\f$ if \p x is empty
    ///         \li +0 if the upper bound of \p x is zero
    ///         \li upper bound of \p x otherwise
    ///
    static T sup(representation_dec const& x);

    /// \brief Mixed-type version of <c>\link mpfr_bin_ieee754_flavor::sup(representation_dec const& x) sup\endlink</c>.
    ///
    /// \param x Decorated interval representation
    /// \return Result of <c>\link mpfr_bin_ieee754_flavor::sup(representation_dec const& x) sup\endlink</c> converted
    ///         to the type \p T_ using rounding to \f$+\infty\f$.
    ///
    ///
    template<typename T_>
    static T sup(representation_dec_type<T_> const& x);

    /// \todo Docu, Test
    ///
    ///
    static T mid(representation const& x);

    /// \todo Docu, Test
    ///
    ///
    template<typename T_>
    static T mid(representation_type<T_> const& x);

    /// \todo Docu, Test
    ///
    ///
    static T mid(representation_dec const& x);

    /// \todo Docu, Test
    ///
    ///
    template<typename T_>
    static T mid(representation_dec_type<T_> const& x);

    /// \todo Docu, Test
    ///
    ///
    static T rad(representation const& x);

    /// \todo Docu, Test
    ///
    ///
    template<typename T_>
    static T rad(representation_type<T_> const& x);

    /// \todo Docu, Test
    ///
    ///
    static T rad(representation_dec const& x);

    /// \todo Docu, Test
    ///
    ///
    template<typename T_>
    static T rad(representation_dec_type<T_> const& x);

    /// \todo Docu, Test
    ///
    ///
    static std::pair<T, T> mid_rad(representation const& x);

    /// \todo Docu, Test
    ///
    ///
    template<typename T_>
    static std::pair<T, T> mid_rad(representation_type<T_> const& x);


    /// \todo Docu, Test
    ///
    ///
    static std::pair<T, T> mid_rad(representation_dec const& x);

    /// \todo Docu, Test
    ///
    ///
    template<typename T_>
    static std::pair<T, T> mid_rad(representation_dec_type<T_> const& x);

    /// \todo Docu, Test
    ///
    ///
    static T wid(representation const& x);

    /// \todo Docu, Test
    ///
    ///
    template<typename T_>
    static T wid(representation_type<T_> const& x);

    /// \todo Docu, Test
    ///
    ///
    static T wid(representation_dec const& x);

    /// \todo Docu, Test
    ///
    ///
    template<typename T_>
    static T wid(representation_dec_type<T_> const& x);

    /// \todo Docu, Test
    ///
    ///
    static T mag(representation const& x);

    /// \todo Docu, Test
    ///
    ///
    template<typename T_>
    static T mag(representation_type<T_> const& x);

    /// \todo Docu, Test
    ///
    ///
    static T mag(representation_dec const& x);

    /// \todo Docu, Test
    ///
    ///
    template<typename T_>
    static T mag(representation_dec_type<T_> const& x);

    /// \todo Docu, Test
    ///
    ///
    static T mig(representation const& x);

    /// \todo Docu, Test
    ///
    ///
    template<typename T_>
    static T mig(representation_type<T_> const& x);

    /// \todo Docu, Test
    ///
    ///
    static T mig(representation_dec const& x);

    /// \todo Docu, Test
    ///
    ///
    template<typename T_>
    static T mig(representation_dec_type<T_> const& x);

///@}

// -----------------------------------------------------------------------------
// Boolean functions of intervals
// -----------------------------------------------------------------------------

///@name Boolean functions of intervals
///
///
///@{


    /// \brief Checks if \p x is a representation for an empty bare interval.
    ///
    /// \param x Interval representation
    /// \return \li <c>true</c> if x is a representation of an empty bare interval
    ///         \li <c>false</c> otherwise.
    ///
    static bool is_empty(representation const& x);

    /// \brief Checks if \p x is a representation for an empty decorated interval.
    ///
    /// \param x Decorated interval representation
    /// \return \li <c>true</c> if x is a representation of an empty decorated interval
    ///         \li <c>false</c> otherwise.
    ///
    static bool is_empty(representation_dec const& x);

    /// \brief Checks if \p x is a representation for an entire bare interval.
    ///
    /// \param x Interval representation
    /// \return \li <c>true</c> if x is a representation of an entire bare interval
    ///         \li <c>false</c> otherwise.
    ///
    static bool is_entire(representation const& x);

    /// \brief Checks if \p x is a representation for an entire decorated interval.
    ///
    /// \param x Interval representation
    /// \return \li <c>true</c> if x is a representation of an entire decorated interval
    ///         \li <c>false</c> otherwise.
    ///
    static bool is_entire(representation_dec const& x);

    /// \brief Checks if \p x is a representation for an ill-formed decorated interval (Not an Interval).
    ///
    /// \param x Interval representation
    /// \return \li <c>true</c> if x is a representation of NaI
    ///         \li <c>false</c> otherwise.
    ///
    static bool is_nai(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static bool is_equal(representation const& x, representation const& y);

    /// \todo TODO
    ///
    ///
    static bool is_equal(representation_dec const& x, representation_dec const& y);

    /// \todo TODO
    ///
    ///
    static bool subset(representation const& x, representation const& y);

    /// \todo TODO
    ///
    ///
    static bool subset(representation_dec const& x, representation_dec const& y);

    /// \todo TODO
    ///
    ///
    static bool less(representation const& x, representation const& y);

    /// \todo TODO
    ///
    ///
    static bool less(representation_dec const& x, representation_dec const& y);

    /// \todo TODO
    ///
    ///
    static bool precedes(representation const& x, representation const& y);

    /// \todo TODO
    ///
    ///
    static bool precedes(representation_dec const& x, representation_dec const& y);

    /// \todo TODO
    ///
    ///
    static bool is_interior(representation const& x, representation const& y);

    /// \todo TODO
    ///
    ///
    static bool is_interior(representation_dec const& x, representation_dec const& y);

    /// \todo TODO
    ///
    ///
    static bool strictly_less(representation const& x, representation const& y);

    /// \todo TODO
    ///
    ///
    static bool strictly_less(representation_dec const& x, representation_dec const& y);

    /// \todo TODO
    ///
    ///
    static bool strictly_precedes(representation const& x, representation const& y);

    /// \todo TODO
    ///
    ///
    static bool strictly_precedes(representation_dec const& x, representation_dec const& y);

    /// \todo TODO
    ///
    ///
    static bool are_disjoint(representation const& x, representation const& y);

    /// \todo TODO
    ///
    ///
    static bool are_disjoint(representation_dec const& x, representation_dec const& y);

///@}

// -----------------------------------------------------------------------------
// Forward-mode elementary functions
// -----------------------------------------------------------------------------

///@name Forward-mode elementary functions
///
///
///@{


    /// \todo TODO
    ///
    ///
    static representation pos(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec pos(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation neg(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec neg(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation add(representation const& x, representation const& y);

    /// \todo TODO
    ///
    ///
    static representation_dec add(representation_dec const& x, representation_dec const& y);

    /// \todo TODO
    ///
    ///
    static representation sub(representation const& x, representation const& y);

    /// \todo TODO
    ///
    ///
    static representation_dec sub(representation_dec const& x, representation_dec const& y);

    /// \todo TODO
    ///
    ///
    static representation mul(representation const& x, representation const& y);

    /// \todo TODO
    ///
    ///
    static representation_dec mul(representation_dec const& x, representation_dec const& y);

    /// \todo TODO
    ///
    ///
    static representation div(representation const& x, representation const& y);

    /// \todo TODO
    ///
    ///
    static representation_dec div(representation_dec const& x, representation_dec const& y);

    /// \todo TODO
    ///
    ///
    static representation recip(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec recip(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation sqrt(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec sqrt(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation fma(representation const& x, representation const& y,
                              representation const& z );

    /// \todo TODO
    ///
    ///
    static representation_dec fma(representation_dec const& x, representation_dec const& y,
                                  representation_dec const& z );

//TODO notwendig?
//    static representation interval_case(representation const& c,
//                                        representation const& g,
//                                        representation const& h );
//    static representation_dec interval_case(representation_dec const& c,
//                                        representation_dec const& g,
//                                        representation_dec const& h );

    /// \todo TODO
    ///
    ///
    static representation sqr(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec sqr(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation pown(representation const& x, int p);

    /// \todo TODO
    ///
    ///
    static representation_dec pown(representation_dec const& x, int p);

    /// \todo TODO
    ///
    ///
    static representation pow(representation const& x, representation const& y);

    /// \todo TODO
    ///
    ///
    static representation_dec pow(representation_dec const& x, representation_dec const& y);

    /// \todo TODO
    ///
    ///
    static representation exp(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec exp(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation exp2(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec exp2(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation exp10(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec exp10(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation log(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec log(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation log2(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec log2(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation log10(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec log10(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation sin(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec sin(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation cos(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec cos(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation tan(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec tan(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation asin(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec asin(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation acos(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec acos(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation atan(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec atan(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation atan2(representation const& y,
                                representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec atan2(representation_dec const& y,
                                    representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation sinh(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec sinh(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation cosh(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec cosh(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation tanh(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec tanh(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation asinh(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec asinh(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation acosh(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec acosh(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation atanh(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec atanh(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation sign(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec sign(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation ceil(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec ceil(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation floor(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec floor(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation trunc(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec trunc(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation round_ties_to_even(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec round_ties_to_even(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation round_ties_to_away(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec round_ties_to_away(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation abs(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec abs(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation min(representation const& x,
                              representation const& y);

    /// \todo TODO
    ///
    ///
    static representation_dec min(representation_dec const& x,
                                  representation_dec const& y);

    /// \todo TODO
    ///
    ///
    static representation max(representation const& x,
                              representation const& y);

    /// \todo TODO
    ///
    ///
    static representation_dec max(representation_dec const& x,
                                  representation_dec const& y);

///@}

// -----------------------------------------------------------------------------
// Two-output division
// -----------------------------------------------------------------------------

///@name Two-output division
///
///
///@{

    /// \todo TODO
    ///
    ///
    static std::pair<representation,representation> div_to_pair(representation const& x,
            representation const& y);

    /// \todo TODO
    ///
    ///
    static std::pair<representation_dec,representation_dec> div_to_pair(representation_dec const& x,
            representation_dec const& y);

///@}

// -----------------------------------------------------------------------------
// Reverse-mode elementary functions
// -----------------------------------------------------------------------------

///@name Reverse-mode elementary functions
///
///
///@{

    /// \todo TODO
    ///
    ///
    static representation sqr_rev(representation const& c,
                                  representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec sqr_rev(representation_dec const& c,
                                      representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation sqr_rev(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec sqr_rev(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation recip_rev(representation const& c,
                                    representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec recip_rev(representation_dec const& c,
                                        representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation recip_rev(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec recip_rev(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation abs_rev(representation const& c,
                                  representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec abs_rev(representation_dec const& c,
                                      representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation abs_rev(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec abs_rev(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation pown_rev(representation const& c,
                                   representation const& x,
                                   int n);

    /// \todo TODO
    ///
    ///
    static representation_dec pown_rev(representation_dec const& c,
                                       representation_dec const& x,
                                       int n);

    /// \todo TODO
    ///
    ///
    static representation pown_rev(representation const& x,
                                   int n);

    /// \todo TODO
    ///
    ///
    static representation_dec pown_rev(representation_dec const& x,
                                       int n);

    /// \todo TODO
    ///
    ///
    static representation sin_rev(representation const& c,
                                  representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec sin_rev(representation_dec const& c,
                                      representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation sin_rev(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec sin_rev(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation cos_rev(representation const& c,
                                  representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec cos_rev(representation_dec const& c,
                                      representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation cos_rev(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec cos_rev(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation tan_rev(representation const& c,
                                  representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec tan_rev(representation_dec const& c,
                                      representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation tan_rev(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec tan_rev(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation cosh_rev(representation const& c,
                                   representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec cosh_rev(representation_dec const& c,
                                       representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation cosh_rev(representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec cosh_rev(representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation mul_rev(representation const& b,
                                  representation const& c,
                                  representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec mul_rev(representation_dec const& b,
                                      representation_dec const& c,
                                      representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation mul_rev(representation const& c,
                                  representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec mul_rev(representation_dec const& c,
                                      representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation div_rev1(representation const& b,
                                   representation const& c,
                                   representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec div_rev1(representation_dec const& b,
                                       representation_dec const& c,
                                       representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation div_rev1(representation const& c,
                                   representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec div_rev1(representation_dec const& c,
                                       representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation div_rev2(representation const& a,
                                   representation const& c,
                                   representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec div_rev2(representation_dec const& a,
                                       representation_dec const& c,
                                       representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation div_rev2(representation const& c,
                                   representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec div_rev2(representation_dec const& c,
                                       representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation pow_rev1(representation const& b,
                                   representation const& c,
                                   representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec pow_rev1(representation_dec const& b,
                                       representation_dec const& c,
                                       representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation pow_rev1(representation const& c,
                                   representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec pow_rev1(representation_dec const& c,
                                       representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation pow_rev2(representation const& a,
                                   representation const& c,
                                   representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec pow_rev2(representation_dec const& a,
                                       representation_dec const& c,
                                       representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation pow_rev2(representation const& c,
                                   representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec pow_rev2(representation_dec const& c,
                                       representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation atan2_rev1(representation const& b,
                                     representation const& c,
                                     representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec atan2_rev1(representation_dec const& b,
                                         representation_dec const& c,
                                         representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation atan2_rev1(representation const& c,
                                     representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec atan2_rev1(representation_dec const& c,
                                         representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation atan2_rev2(representation const& a,
                                     representation const& c,
                                     representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec atan2_rev2(representation_dec const& a,
                                         representation_dec const& c,
                                         representation_dec const& x);

    /// \todo TODO
    ///
    ///
    static representation atan2_rev2(representation const& c,
                                     representation const& x);

    /// \todo TODO
    ///
    ///
    static representation_dec atan2_rev2(representation_dec const& c,
                                         representation_dec  const& x);

///@}

// -----------------------------------------------------------------------------
// Cancellative addition and subtraction
// -----------------------------------------------------------------------------

///@name Cancellative addition and subtraction
///
///
///@{

    /// \todo TODO
    ///
    ///
    static representation cancel_plus(representation const& a,
                                      representation const& b);

    /// \todo TODO
    ///
    ///
    static representation_dec cancel_plus(representation_dec const& a,
                                          representation_dec const& b);

    /// \todo TODO
    ///
    ///
    static representation cancel_minus(representation const& a,
                                       representation const& b);

    /// \todo TODO
    ///
    ///
    static representation_dec cancel_minus(representation_dec const& a,
                                           representation_dec const& b);

///@}

// -----------------------------------------------------------------------------
// Forward-mode elementary functions (Recommended)
// -----------------------------------------------------------------------------

///@name Forward-mode elementary functions (Recommended)
///
///
///@{

    /// \todo TODO
    ///
    ///
    static representation rootn(representation const&, int);

    /// \todo TODO
    ///
    ///
    static representation_dec rootn(representation_dec const&, int);

    /// \todo TODO
    ///
    ///
    static representation expm1(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec expm1(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation exp2m1(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec exp2m1(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation exp10m1(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec exp10m1(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation logp1(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec logp1(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation log2p1(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec log2p1(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation log10p1(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec log10p1(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation compoundm1(representation const&,
                                     representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec compoundm1(representation_dec const&,
                                         representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation hypot(representation const&,
                                representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec hypot(representation_dec const&,
                                    representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation r_sqrt(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec r_sqrt(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation sin_pi(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec sin_pi(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation cos_pi(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec cos_pi(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation tan_pi(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec tan_pi(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation asin_pi(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec asin_pi(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation acos_pi(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec acos_pi(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation atan_pi(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec atan_pi(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation atan2_pi(representation const&,
                                   representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec atan2_pi(representation_dec const&,
                                       representation_dec const&);

///@}

// -----------------------------------------------------------------------------
// Extended interval comparisons (Recommended)
// -----------------------------------------------------------------------------

///@name Extended interval comparisons (Recommended)
///
///
///@{

    /// \todo TODO
    ///
    ///
    static p1788::overlapping::overlapping_state overlap(representation const&,
            representation const&);


    /// \todo TODO
    ///
    ///
    static p1788::overlapping::overlapping_state overlap(representation_dec const&,
            representation_dec const&);

// -----------------------------------------------------------------------------
// Boolean functions of intervals (Recommended)
// -----------------------------------------------------------------------------

///@name Boolean functions of intervals (Recommended)
///
///
///@{

    /// \todo TODO
    ///
    ///
    static bool is_common(representation const&);

    /// \todo TODO
    ///
    ///
    static bool is_common(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static bool is_singleton(representation const&);

    /// \todo TODO
    ///
    ///
    static bool is_singleton(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static bool is_member(T, representation const&);

    /// \todo TODO
    ///
    ///
    static bool is_member(T, representation_dec const&);

///@}

// -----------------------------------------------------------------------------
// Slope functions (Recommended)
// -----------------------------------------------------------------------------

///@name Slope functions (Recommended)
///
///
///@{

    /// \todo TODO
    ///
    ///
    static representation exp_slope1(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec exp_slope1(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation exp_slope2(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec exp_slope2(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation log_slope1(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec log_slope1(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation log_slope2(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec log_slope2(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation cos_slope2(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec cos_slope2(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation sin_slope3(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec sin_slope3(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation asin_slope3(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec asin_slope3(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation atan_slope3(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec atan_slope3(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation cosh_slope2(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec cosh_slope2(representation_dec const&);

    /// \todo TODO
    ///
    ///
    static representation sinh_slope3(representation const&);

    /// \todo TODO
    ///
    ///
    static representation_dec sinh_slope3(representation_dec const&);

///@}

};


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_class_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_io_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_set_op_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_num_func_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_bool_func_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_elem_func_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_div_pair_func_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_rev_elem_func_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_cancel_func_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_rec_elem_func_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_rec_overlap_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_rec_bool_func_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_rec_slope_func_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_setup_func_impl.hpp"
#include "p1788/flavor/infsup/setbased/mpfr_bin_ieee754_flavor_util_func_impl.hpp"

#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_HPP
