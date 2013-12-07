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

#ifndef LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_HPP
#define LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_HPP

/*
#include <initializer_list>
#include <utility>
#include <string>
#include <istream>
#include <ostream>
#include <vector>
#include <algorithm>

#include "p1788/overlapping/overlapping.hpp"
#include "p1788/util/mixed_type_traits.hpp"
#include "p1788/util/variadic_templates.hpp"


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                        Forward declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


namespace p1788
{

namespace infsup
{


//TODO hull, see P1788/D7.0 Sect. 9.3


// Forward declaration
template<typename T, template<typename> class Flavor> class decorated_interval;



} // namespace infsup


} // namespace p1788




//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                        Traits and meta TMP functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


namespace p1788
{

namespace util
{

//------------------------------------------------------------------------------
// Trait is_infsup_interval
//------------------------------------------------------------------------------

// Ignore the warning about non-virtual destructors
// on GCC  push the last diagnostic state and disable -Weffc++
//TODO support other compiler
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"


/// \brief Trait to check if type T is an p1788::infsup::decorated_interval
///
/// \param T type
/// \return field value contains boolean result of the check
///
///
template<typename T>
class is_infsup_decorated_interval
    : public std::integral_constant<bool, false>
{ };

template<typename T, template<typename> class Flavor>
class is_infsup_decorated_interval<p1788::infsup::decorated_interval<T,Flavor>>
            : public std::integral_constant<bool, true>
{ };

// on GCC  enable the diagnostic state -Weffc++ again
#pragma GCC diagnostic pop


////------------------------------------------------------------------------------
//// Trait infsup_max_precision_type
////------------------------------------------------------------------------------
//
//template<typename... Types> class infsup_max_precision_type
//{
//    static_assert(sizeof...(Types) > 0,
//                  "infsup_max_precision_type for an empty argument list!");
//};
//
//template<typename First, typename Second, typename... Tail>
//class infsup_max_precision_type<First, Second, Tail...>
//{
//public:
//    static_assert(is_infsup_interval<First>::value, "Type is not supported!");
//    static_assert(is_infsup_interval<Second>::value, "Type is not supported!");
//
//    static_assert(
//        std::is_same<
//        typename type_precision_order<typename First::bound_type>::value_type,
//        typename type_precision_order<typename Second::bound_type>::value_type
//        >::value,
//        "Different type groups!");
//
//    typedef typename infsup_max_precision_type<
//    typename std::conditional<
//    (type_precision_order<typename First::bound_type>::value >
//     type_precision_order<typename Second::bound_type>::value),
//                          First,
//                          Second
//                          >::type,
//                          Tail...
//                          >::type type;
//};
//
//template<typename Type>
//class infsup_max_precision_type<Type>
//{
//public:
//    typedef Type type;
//};
//


} // namespace util

} // namespace p1788







//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                       Definition of class interval
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------




namespace p1788
{

namespace infsup
{



/// \brief Level 2 (bare) infsup interval
///
///
/// Class representing a level 2 (bare) infsup interval, see P1788/D7.0 Sect. 4.1.
///
/// This class only serves as a uniform interface/representation of an (bare)
/// interval. All the behavior will be specified by the template policy class
/// Flavor<T> which implements the flavors concept of the standard in coherent way,
/// see P1788/D7.0 Sect. 5.
///
/// \param T                  Number system / parent format
/// \param Flavor<typename>   Generic flavor which will be instantiated with the
///                           number system T
///
template<typename T, template<typename> class Flavor>
class decorated_interval //TODO final
{

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// public
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


public:

    typedef T bound_type;

    // TODO type alias ?
    //template<typename TT> using flavor_type = Flavor<TT>;
    typedef Flavor<T> flavor_type;


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

// TODO Constructor specification

    decorated_interval()
        : rep_(Flavor<T>::constructor_infsup_dec())
    { }

    decorated_interval(T lower, T upper)
        : rep_(Flavor<T>::constructor_infsup_dec(lower, upper))
    { }

    explicit decorated_interval(T point)
        : rep_(Flavor<T>::constructor_infsup_dec(point))
    { }

    explicit decorated_interval(std::initializer_list<T> points)
        : rep_(Flavor<T>::constructor_infsup_dec(points.begin(), points.end()))
    { }

    explicit decorated_interval(std::string const& str)
        : rep_(Flavor<T>::constructor_infsup_dec(str))
    { }

    decorated_interval(decorated_interval<T, Flavor> const& other)  ///< Copy-constructor
        : rep_(Flavor<T>::constructor_infsup_dec(other.rep_))
    { }

    template<typename TT>
    explicit decorated_interval(decorated_interval<TT, Flavor> const& other)  ///< Copy-constructor
        : rep_(Flavor<T>::constructor_infsup_dec(other.rep_))
    { }



// TODO public representation,




// -----------------------------------------------------------------------------
// Methods
// -----------------------------------------------------------------------------


    /// \brief Foo Bar baz
    /// Implementation specific
    /// \return T
    ///
    ///
    T lower() const {
        return Flavor<T>::method_lower_dec(rep_);
    }

// Implementation specific
    T upper() const {
        return Flavor<T>::method_upper_dec(rep_);
    }

// Implementation specific
    T mid() const {
        return Flavor<T>::method_mid_dec(rep_);
    }

// Implementation specific
    T rad() const {
        return Flavor<T>::method_rad_dec(rep_);
    }


// -----------------------------------------------------------------------------
// Static methods
// -----------------------------------------------------------------------------

// Required, Creates an empty interval, see P1788/D8.1 Sect. 10.6.2

    static decorated_interval<T, Flavor> empty() {
        return decorated_interval<T, Flavor>(Flavor<T>::static_method_empty_dec());
    }

// Required, Creates an entire interval, see P1788/D8.1 Sect. 10.6.2
    static decorated_interval<T, Flavor> entire() {
        return decorated_interval<T, Flavor>(Flavor<T>::static_method_entire_dec());
    }




// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// private
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

private:


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

    decorated_interval(typename Flavor<T>::representation_dec const& rep)
        : rep_(rep)
    { }


// -----------------------------------------------------------------------------
// Members
// -----------------------------------------------------------------------------

    typename Flavor<T>::representation_dec rep_;








//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Friends
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


    template<typename, template<typename> class>
    friend class decorated_interval;



// -----------------------------------------------------------------------------
// IO operators
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_, typename CharT, typename Traits>
    friend std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>&, decorated_interval<T_, Flavor_>&);


// -----------------------------------------------------------------------------
// Non-arithmetic set operations
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> intersect(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> hull(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);


// -----------------------------------------------------------------------------
// Numeric functions on intervals
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_>
    friend T_ inf(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend T_ sup(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend T_ mid(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend T_ rad(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend std::pair<T_, T_> mid_rad(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend T_ wid(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend T_ mag(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend T_ mig(decorated_interval<T_, Flavor_> const&);


// -----------------------------------------------------------------------------
// Boolean functions on intervals
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_>
    friend bool is_empty(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool is_entire(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool is_equal(decorated_interval<T_, Flavor_> const&, interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool contained_in(decorated_interval<T_, Flavor_> const&, interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool contains(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool less(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool greater(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool precedes(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool succeeds(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool is_interior(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool contains_interior(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool strictly_less(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool strictly_greater(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool strictly_precedes(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool strictly_succeeds(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend bool are_disjoint(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);


// -----------------------------------------------------------------------------
// Forward elementary functions
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> pos(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> neg(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> add (decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> sub(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> mul(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> div(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> recip(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> sqr(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> sqrt(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> fma(decorated_interval<T_, Flavor_> const&,
                                   decorated_interval<T_, Flavor_> const&,
                                   decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> interval_case(decorated_interval<T_, Flavor_> const&,
                                   decorated_interval<T_, Flavor_> const&,
                                   decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> pown(decorated_interval<T_, Flavor_> const&, int p);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> pow(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> exp(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> exp2(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> exp10(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> log(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> log2(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> log10(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> sin(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> cos(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> tan(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> asin(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> acos(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> atan(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> atan2(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> sinh(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> cosh(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> tanh(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> asinh(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> acosh(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> atanh(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> sign(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> ceil(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> floor(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> trunc(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> round_ties_to_even(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> round_ties_to_away(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> abs(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> min(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    friend decorated_interval<T_, Flavor_> max(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);


// -----------------------------------------------------------------------------
//  Recommended div to pair function
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_>
    friend std::pair<decorated_interval<T_, Flavor_>, decorated_interval<T_, Flavor_>>
    div_to_pair(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);




// -----------------------------------------------------------------------------
// Reverse elementary functions
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> sqr_rev(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> sqr_rev(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> recip_rev(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> recip_rev(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> abs_rev(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> abs_rev(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> pown_rev(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&, int);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> pown_rev(decorated_interval<T_, Flavor_> const&, int);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> sin_rev(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> sin_rev(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> cos_rev(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> cos_rev(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> tan_rev(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> tan_rev(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> cosh_rev(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> cosh_rev(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> mul_rev(decorated_interval<T_, Flavor_> const&,
                                       decorated_interval<T_, Flavor_> const&,
                                       decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> mul_rev(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> div_rev1(decorated_interval<T_, Flavor_> const&,
                                        decorated_interval<T_, Flavor_> const&,
                                        decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> div_rev1(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> div_rev2(decorated_interval<T_, Flavor_> const&,
                                        decorated_interval<T_, Flavor_> const&,
                                        decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> div_rev2(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> pow_rev1(decorated_interval<T_, Flavor_> const&,
                                        decorated_interval<T_, Flavor_> const&,
                                        decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> pow_rev1(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> pow_rev2(decorated_interval<T_, Flavor_> const&,
                                        decorated_interval<T_, Flavor_> const&,
                                        decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> pow_rev2(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> atan2_rev1(decorated_interval<T_, Flavor_> const&,
                                          decorated_interval<T_, Flavor_> const&,
                                          decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> atan2_rev1(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> atan2_rev2(decorated_interval<T_, Flavor_> const&,
                                          decorated_interval<T_, Flavor_> const&,
                                          decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> atan2_rev2(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);


// -----------------------------------------------------------------------------
// Cancellative addition and subtraction
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> cancel_plus(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> cancel_minus(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);


// -----------------------------------------------------------------------------
// Recommended boolean functions on intervals
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_>
    bool is_common(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    bool is_singleton(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    bool is_member(T_ m, decorated_interval<T_, Flavor_> const&);


// -----------------------------------------------------------------------------
// Recommended forward elementary functions on intervals
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> rootn(decorated_interval<T_, Flavor_> const&, int);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> expm1(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> exp2m1(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> exp10m1(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> logp1(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> log2p1(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> log10p1(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> compoundm1(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> hypot(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> r_sqrt(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> sin_pi(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> cos_pi(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> tan_pi(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> asin_pi(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> acos_pi(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> atan_pi(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> atan2_pi(decorated_interval<T_, Flavor_> const&, decorated_interval<T_, Flavor_> const&);


// -----------------------------------------------------------------------------
// Recommended interval overlapping
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_>
    p1788::overlapping::overlapping_state overlap(decorated_interval<T_, Flavor_> const&,
            decorated_interval<T_, Flavor_> const&);


// -----------------------------------------------------------------------------
// Recommended slope functions
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> exp_slope1(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> exp_slope2(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> log_slope1(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> log_slope2(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> cos_slope2(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> sin_slope3(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> asin_slope3(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> atan_slope3(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> cosh_slope2(decorated_interval<T_, Flavor_> const&);

    template<typename T_, template<typename> class Flavor_>
    decorated_interval<T_, Flavor_> sinh_slope3(decorated_interval<T_, Flavor_> const&);



};

} // namespace infsup

} // namespace p1788


#include "p1788/infsup/decorated_interval_io_impl.hpp"
#include "p1788/infsup/decorated_interval_set_op_impl.hpp"
#include "p1788/infsup/decorated_interval_num_func_impl.hpp"
#include "p1788/infsup/decorated_interval_bool_func_impl.hpp"
#include "p1788/infsup/decorated_interval_elem_func_impl.hpp"
#include "p1788/infsup/decorated_interval_div_pair_func_impl.hpp"
#include "p1788/infsup/decorated_interval_rev_elem_func_impl.hpp"
#include "p1788/infsup/decorated_interval_cancel_func_impl.hpp"
#include "p1788/infsup/decorated_interval_rec_elem_func_impl.hpp"
#include "p1788/infsup/decorated_interval_rec_overlap_impl.hpp"
#include "p1788/infsup/decorated_interval_rec_bool_func_impl.hpp"
#include "p1788/infsup/decorated_interval_rec_slope_func_impl.hpp"

*/
#endif // LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_HPP
