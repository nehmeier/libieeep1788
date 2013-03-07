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

#ifndef LIBIEEEP1788_P1788_INFSUP_INTERVAL_HPP
#define LIBIEEEP1788_P1788_INFSUP_INTERVAL_HPP

#include <initializer_list>
#include <utility>
#include <string>
#include <istream>
#include <ostream>
#include "p1788/overlapping/overlapping.hpp"


/// \brief Namespace for all IEEE P1788 interval types
///
namespace p1788
{

/// \brief Namespace for all IEEE P1788 infsup interval types
///
namespace infsup
{


//TODO hull, see P1788/D7.0 Sect. 9.3

//TODO Mixed-type with different Flavors?

template< typename T, template< typename > class Flavor > class interval;





// -----------------------------------------------------------------------------
// Input and output, see P1788/D7.0 Sect. 13
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
std::ostream& operator<< ( std::ostream& os, interval<T, Flavor> const& x );

template< typename T, template< typename > class Flavor >
std::istream& operator>> ( std::istream& is, interval<T, Flavor>& x );


//TODO basic_ostream & basic_istream

//template< typename CharT, typename Traits, typename T, template< typename > class Flavor >
//std::basic_ostream<CharT, Traits>& operator<< ( std::basic_ostream<CharT, Traits>& os, interval<T, Flavor> const& x );

//template< typename CharT, typename Traits, typename T, template< typename > class Flavor >
//std::basic_istream<CharT, Traits>& operator>> ( std::basic_istream<CharT, Traits>& is, interval<T, Flavor>& x );


// -----------------------------------------------------------------------------
// Forward elementary functions, see P1788/D7.0 Sect. 9.6.3 Table 1
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator+ ( interval<T, Flavor> const& x );   ///< Implementation specific, for consistency with -x, not mentioned in the standard

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator- ( interval<T, Flavor> const& x );    ///< Required, -x

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator+ ( interval<T, Flavor> const& x, interval<T, Flavor> const& y );   ///< Required, tightest, Mixed-Type

template< typename Interval, typename Tx, typename Ty, template< typename > class Flavor >
Interval add ( interval<Tx, Flavor> const& x, interval<Ty, Flavor> const& y );  ///< Required, tightest, Mixed-Type-implementation

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator- ( interval<T, Flavor> const& x, interval<T, Flavor> const& y );   ///< Required, tightest, Mixed-Type

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator* ( interval<T, Flavor> const& x, interval<T, Flavor> const& y );   ///< Required, tightest, Mixed-Type

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator/ ( interval<T, Flavor> const& x, interval<T, Flavor> const& y );   ///< Required, tightest, Mixed-Type

template< typename T, template< typename > class Flavor >
interval<T, Flavor> inv ( interval<T, Flavor> const& x );     ///< Required, tightest, Mixed-Type, called recip in Table 1 and inv in Table 10

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sqrt ( interval<T, Flavor> const& x );    ///< Required, tightest, Mixed-Type

template< typename T, template< typename > class Flavor >
interval<T, Flavor> fma ( interval<T, Flavor> const& x, interval<T, Flavor> const& y, interval<T, Flavor> const& z ); ///< Required, accuracy ? Mixed-Type


/// Required, tightest
///
/// P1788/D7.0 Sect. 9.6.4 (9)
///
/// case(c,g,h) :=   empty if c == empty
///                  g     if c_upper < 0
///                  h     if c_lower >= 0
///                  hull(g,h) else
///
template< typename T, template< typename > class Flavor >
interval<T, Flavor> interval_case ( interval<T, Flavor> const& c, interval<T, Flavor> const& g, interval<T, Flavor> const& h );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sqr ( interval<T, Flavor> const& x );     ///< Required, tightest, Mixed-Type

template< typename T, template< typename > class Flavor >
interval<T, Flavor> pown ( interval<T, Flavor> const& x, int p );   ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> pow ( interval<T, Flavor> const& x, interval<T, Flavor> const& y );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> exp ( interval<T, Flavor> const& x );     ///< Required, tightest

template< typename T, template< typename > class Flavor >
interval<T, Flavor> exp2 ( interval<T, Flavor> const& x );    ///< Required, tightest

template< typename T, template< typename > class Flavor >
interval<T, Flavor> exp10 ( interval<T, Flavor> const& x );   ///< Required, tightest

template< typename T, template< typename > class Flavor >
interval<T, Flavor> log ( interval<T, Flavor> const& x );     ///< Required, tightest

template< typename T, template< typename > class Flavor >
interval<T, Flavor> log2 ( interval<T, Flavor> const& x );    ///< Required, tightest

template< typename T, template< typename > class Flavor >
interval<T, Flavor> log10 ( interval<T, Flavor> const& x );   ///< Required, tightest

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sin ( interval<T, Flavor> const& x );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cos ( interval<T, Flavor> const& x );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> tan ( interval<T, Flavor> const& x );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> asin ( interval<T, Flavor> const& x );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> acos ( interval<T, Flavor> const& x );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atan ( interval<T, Flavor> const& x );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atan2 ( interval<T, Flavor> const& y, interval<T, Flavor> const& x );   ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sinh ( interval<T, Flavor> const& x );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cosh ( interval<T, Flavor> const& x );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> tanh ( interval<T, Flavor> const& x );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> asinh ( interval<T, Flavor> const& x );   ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> acosh ( interval<T, Flavor> const& x );   ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atanh ( interval<T, Flavor> const& x );   ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sign ( interval<T, Flavor> const& x );        ///< Required, tightest, Mixed-Type

template< typename T, template< typename > class Flavor >
interval<T, Flavor> ceil ( interval<T, Flavor> const& x );        ///< Required, tightest, Mixed-Type

template< typename T, template< typename > class Flavor >
interval<T, Flavor> floor ( interval<T, Flavor> const& x );       ///< Required, tightest, Mixed-Type

template< typename T, template< typename > class Flavor >
interval<T, Flavor> trunc ( interval<T, Flavor> const& x );       ///< Required, tightest, Mixed-Type

template< typename T, template< typename > class Flavor >
interval<T, Flavor> round_ties_to_even ( interval<T, Flavor> const& x );      ///< Required, tightest, Mixed-Type

template< typename T, template< typename > class Flavor >
interval<T, Flavor> round_ties_to_away ( interval<T, Flavor> const& x );      ///< Required, tightest, Mixed-Type

template< typename T, template< typename > class Flavor >
interval<T, Flavor> abs ( interval<T, Flavor> const& x );         ///< Required, tightest, Mixed-Type

template< typename T, template< typename > class Flavor >
interval<T, Flavor> min ( std::initializer_list< interval<T, Flavor>> intervals );    ///< Required, Mixed-Type, tightest, hull(menge der untergrenzen)

template< typename T, template< typename > class Flavor >
interval<T, Flavor> max ( std::initializer_list< interval<T, Flavor>> intervals );    ///<  Required, Mixed-Type, tightest, hull(menge der obergrenzen)



// -----------------------------------------------------------------------------
// Reverse elementary functions, see P1788/D7.0 Sect. 9.6.5 Table 2
// -----------------------------------------------------------------------------

// reverse version of unary point functions

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sqr_rev ( interval<T, Flavor> const&, interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sqr_rev ( interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> inv_rev ( interval<T, Flavor> const&, interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> inv_rev ( interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> abs_rev ( interval<T, Flavor> const&, interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> abs_rev ( interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> pown_rev ( interval<T, Flavor> const&, interval<T, Flavor> const&, int );   ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> pown_rev ( interval<T, Flavor> const&, int );   ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sin_rev ( interval<T, Flavor> const&, interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sin_rev ( interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cos_rev ( interval<T, Flavor> const&, interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cos_rev ( interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> tan_rev ( interval<T, Flavor> const&, interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> tan_rev ( interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cosh_rev ( interval<T, Flavor> const&, interval<T, Flavor> const& );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cosh_rev ( interval<T, Flavor> const& );    ///< Required, accurate


// reverse versions of binary point functions

template< typename T, template< typename > class Flavor >
interval<T, Flavor> mul_rev ( interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> mul_rev ( interval<T, Flavor> const&, interval<T, Flavor> const& );     ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> div_rev1 ( interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const& );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> div_rev1 ( interval<T, Flavor> const&, interval<T, Flavor> const& );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> div_rev2 ( interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const& );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> div_rev2 ( interval<T, Flavor> const&, interval<T, Flavor> const& );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> pow_rev1 ( interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const& );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> pow_rev1 ( interval<T, Flavor> const&, interval<T, Flavor> const& );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> pow_rev2 ( interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const& );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> pow_rev2 ( interval<T, Flavor> const&, interval<T, Flavor> const& );    ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atan2_rev1 ( interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const& );  ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atan2_rev1 ( interval<T, Flavor> const&, interval<T, Flavor> const& );  ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atan2_rev2 ( interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const& );  ///< Required, accurate

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atan2_rev2 ( interval<T, Flavor> const&, interval<T, Flavor> const& );  ///< Required, accurate


// -----------------------------------------------------------------------------
// Cancellative addition and subtraction, see P1788/D7.0 Sect. 9.6.6
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cancel_plus ( interval<T, Flavor> const&, interval<T, Flavor> const& );     ///< Required, necessary for bare intervals? see, 11.11.6 // TODO nicht fuer bare interval

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cancel_minus ( interval<T, Flavor> const&, interval<T, Flavor> const& );    ///< Required, necessary for bare intervals? see, 11.11.6 // TODO nicht fuer bare interval


// -----------------------------------------------------------------------------
// Non-arithmetic set operations, see P1788/D7.0 Sect. 9.6.6
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
interval<T, Flavor> intersect ( interval<T, Flavor> const&, interval<T, Flavor> const& );       ///< Required

template< typename T, template< typename > class Flavor >
interval<T, Flavor> hull ( interval<T, Flavor> const&, interval<T, Flavor> const& );            ///< Required

template< typename T, template< typename > class Flavor >
interval<T, Flavor> hull ( std::initializer_list<T> );      ///< interval hull, see P1788/D7.0 Sect. 11.8.1

template< typename T, template< typename > class Flavor >
interval<T, Flavor> widen ( interval<T, Flavor> const&  );  ///< necessary as  a function?, see P1788/D7.0 Sect. 11.10  // TODO nicht notwendig

// -----------------------------------------------------------------------------
// Numeric functions on intervals, see P1788/D7.0 Sect. 9.6.9
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
T inf ( interval<T, Flavor> const& );       ///< Required

template< typename T, template< typename > class Flavor >
T sup ( interval<T, Flavor> const& );       ///< Required

template< typename T, template< typename > class Flavor >
T mid ( interval<T, Flavor> const& );       ///< Required

template< typename T, template< typename > class Flavor >
T wid ( interval<T, Flavor> const& );       ///< Required

template< typename T, template< typename > class Flavor >
T rad ( interval<T, Flavor> const& );       ///< Required

template< typename T, template< typename > class Flavor >
T mag ( interval<T, Flavor> const& );       ///< Required

template< typename T, template< typename > class Flavor >
T mig ( interval<T, Flavor> const& );       ///< Required

template< typename T, template< typename > class Flavor >
std::pair<T, T> mid_rad ( interval<T, Flavor> const& );     ///< Recommended, see Note in P1788/D7.0 Sect. 9.6.9


// -----------------------------------------------------------------------------
// Boolean functions on intervals, see P1788/D7.0 Sect. 9.6.10
// -----------------------------------------------------------------------------

// set op
template< typename T, template< typename > class Flavor >
bool is_empty ( interval<T, Flavor> const& );   ///< Required

template< typename T, template< typename > class Flavor >
bool is_entire ( interval<T, Flavor> const& );  ///< Required

// comparisons see P1788/D7.0 Sect. 9.6.10 Table 4
template< typename T, template< typename > class Flavor >
bool is_equal ( interval<T, Flavor> const&, interval<T, Flavor> const& );   ///< Required, Mixed Type

template< typename T, template< typename > class Flavor >
bool contained_in ( interval<T, Flavor> const&, interval<T, Flavor> const& );   ///< Required, Mixed Type

template< typename T, template< typename > class Flavor >
bool less ( interval<T, Flavor> const&, interval<T, Flavor> const& );   ///< Required, Mixed Type

template< typename T, template< typename > class Flavor >
bool precedes ( interval<T, Flavor> const&, interval<T, Flavor> const& );   ///< Required, Mixed Type

template< typename T, template< typename > class Flavor >
bool is_interior ( interval<T, Flavor> const&, interval<T, Flavor> const& );    ///< Required, Mixed Type

template< typename T, template< typename > class Flavor >
bool strictly_less ( interval<T, Flavor> const&, interval<T, Flavor> const& );  ///< Required, Mixed Type

template< typename T, template< typename > class Flavor >
bool strictly_precedes ( interval<T, Flavor> const&, interval<T, Flavor> const& );  ///< Required, Mixed Type

template< typename T, template< typename > class Flavor >
bool are_disjoint ( interval<T, Flavor> const&, interval<T, Flavor> const& );   ///< Required, Mixed Type


// Equal and Unequal operator : short form of is_equal and !is_equal
template< typename T, template< typename > class Flavor >
bool operator== ( interval<T, Flavor> const&, interval<T, Flavor> const& );     ///< Implementation specific, short hand for is_equal

template< typename T, template< typename > class Flavor >
bool operator!= ( interval<T, Flavor> const&, interval<T, Flavor> const& );     ///< Implementation specific, short hand for !is_equal

// -----------------------------------------------------------------------------
// Recommended forward elementary functions on intervals, see P1788/D7.0 Sect. 9.7.1 Table 5
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
interval<T, Flavor> rootn ( interval<T, Flavor> const&, int );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> expm1 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> exp2m1 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> exp10m1 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> logp1 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> log2p1 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> log10p1 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> compoundm1 ( interval<T, Flavor> const&, interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> hypot ( interval<T, Flavor> const&, interval<T, Flavor> const& );   ///< tightest, required or recommended?

template< typename T, template< typename > class Flavor >
interval<T, Flavor> r_sqrt ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sin_pi ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cos_pi ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> tan_pi ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> asin_pi ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> acos_pi ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atan_pi ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atan2_pi ( interval<T, Flavor> const&, interval<T, Flavor> const& );


// -----------------------------------------------------------------------------
// Recommended interval overlapping, see P1788/D7.0 Sect. 9.7.2
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
p1788::overlapping_state overlap ( interval<T, Flavor> const&, interval<T, Flavor> const& );


// -----------------------------------------------------------------------------
// Recommended slope functions, see P1788/D7.0 Sect. 9.7.3 Table 7
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
interval<T, Flavor> exp_slope1 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> exp_slope2 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> log_slope1 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> log_slope2 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cos_slope2 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sin_slope3 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> asin_slope3 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atan_slope3 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cosh_slope2 ( interval<T, Flavor> const& );

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sinh_slope3 ( interval<T, Flavor> const& );







/// \brief Level 2 (bare) infsup interval
///
///
/// Class representing a level 2 (bare) infsup interval, see P1788/D7.0 Sect. 4.1.
///
/// This class only serves as a uniform interface/representation of an (bare)
/// interval. All the behavior will be specified by the template policy class
/// Flavor which implements the flavors concept of the standard in coherent way,
/// see P1788/D7.0 Sect. 5.
///
/// \param T                  Number system /parent format
/// \param Flavor<typename>   Generic flavor which will be instantiated with the
///                           number system T
///
template< typename T, template< typename > class Flavor >
class interval  // TODO final
{
public:

    typedef T bound_type;

    // TODO type alias ?
    //template<typename TT> using flavor_type = Flavor<TT>;

    typedef Flavor<T> flavor_type;

    // TODO Constructor specification

    interval ( );                               ///< Implementation specific, default constructor

    interval ( T lower, T upper );           ///< Required, nums2Interval, see P1788/D7.0 Sect. 9.6.8

    explicit interval ( T point );          ///< Implementation specific, point interval, not in the standard    // TODO pruefen Wvg

    explicit interval ( std::initializer_list<T> points );  ///< interval hull, see P1788/D7.0 Sect. 11.8.1

    explicit interval ( std::string const& str);     ///< Required, text2Interval, see P1788/D7.0 Sect. 9.6.8
    //interval (char const *);     ///< Required, text2Interval, see P1788/D7.0 Sect. 9.6.8 //TODO String
    // TODO literal, see P1788/D7.0 Sect. 9.6.1  (c++11 literal)


    interval (interval<T, Flavor> const& other);  ///< Copy-constructor

    template<typename TT>
    interval (interval<TT, Flavor> const& other);  ///< Copy-constructor


    // TODO public representation,

    T lower ( ) const;      ///< Implementation specific
    T upper ( ) const;      ///< Implementation specific

    T mid ( ) const;      ///< Implementation specific
    T rad ( ) const;      ///< Implementation specific

    static interval<T, Flavor > empty ( );     ///< Required, Creates an empty interval, see P1788/D7.0 Sect. 9.6.2
    static interval<T, Flavor > entire ( );    ///< Required, Creates an entire interval, see P1788/D7.0 Sect. 9.6.2

private:

    explicit inline interval ( typename Flavor<T>::representation const& rep );

    inline typename Flavor<T>::representation& rep();
    inline typename Flavor<T>::representation const& rep() const;

    typename Flavor<T>::representation rep_;


//------------------------------------------------------------------------------
// Friends
//------------------------------------------------------------------------------

    template<typename, template<typename> class> friend class p1788::infsup::interval;

    // IO
    friend std::ostream& operator<< <> ( std::ostream& os, interval<T, Flavor> const& x );
    friend std::istream& operator>> <> ( std::istream& is, interval<T, Flavor>& x );

    // Elementary functions
    friend interval<T, Flavor> operator+ <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> operator- <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> operator+ <> ( interval<T, Flavor> const& x, interval<T, Flavor> const& y );
    friend interval<T, Flavor> operator- <> ( interval<T, Flavor> const& x, interval<T, Flavor> const& y );
    friend interval<T, Flavor> operator* <> ( interval<T, Flavor> const& x, interval<T, Flavor> const& y );
    friend interval<T, Flavor> operator/ <> ( interval<T, Flavor> const& x, interval<T, Flavor> const& y );
    friend interval<T, Flavor> inv <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> sqrt <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> fma <> ( interval<T, Flavor> const& x, interval<T, Flavor> const& y, interval<T, Flavor> const& z );
    friend interval<T, Flavor> interval_case <> ( interval<T, Flavor> const& c, interval<T, Flavor> const& g, interval<T, Flavor> const& h );
    friend interval<T, Flavor> sqr <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> pown <> ( interval<T, Flavor> const& x, int p );
    friend interval<T, Flavor> pow <> ( interval<T, Flavor> const& x, interval<T, Flavor> const& y );
    friend interval<T, Flavor> exp <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> exp2 <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> exp10 <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> log <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> log2 <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> log10 <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> sin <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> cos <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> tan <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> asin <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> acos <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> atan <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> atan2 <> ( interval<T, Flavor> const& y, interval<T, Flavor> const& x );
    friend interval<T, Flavor> sinh <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> cosh <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> tanh <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> asinh <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> acosh <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> atanh <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> sign <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> ceil <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> floor <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> trunc <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> round_ties_to_even <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> round_ties_to_away <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> abs <> ( interval<T, Flavor> const& x );
    friend interval<T, Flavor> min <> ( std::initializer_list< interval<T, Flavor>> intervals );
    friend interval<T, Flavor> max <> ( std::initializer_list< interval<T, Flavor>> intervals );


};



} // namespace infsup

} // namespace p1788


#include "p1788/infsup/interval_class_impl.hpp"
#include "p1788/infsup/interval_io_impl.hpp"
#include "p1788/infsup/interval_elem_func_impl.hpp"
#include "p1788/infsup/interval_rev_elem_func_impl.hpp"
#include "p1788/infsup/interval_cancel_func_impl.hpp"
#include "p1788/infsup/interval_set_op_impl.hpp"
#include "p1788/infsup/interval_num_func_impl.hpp"
#include "p1788/infsup/interval_bool_func_impl.hpp"
#include "p1788/infsup/interval_rec_elem_func_impl.hpp"
#include "p1788/infsup/interval_rec_overlap_impl.hpp"
#include "p1788/infsup/interval_rec_slope_func_impl.hpp"


#endif // LIBIEEEP1788_P1788_INFSUP_INTERVAL_HPP
