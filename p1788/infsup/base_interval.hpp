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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_HPP


#include "p1788/infsup/forward_declaration.hpp"
#include "p1788/overlapping/overlapping.hpp"



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                       Definition of class base_interval
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


namespace p1788
{

namespace infsup
{


/// \brief Base class for an infsup interval
///
///
/// Base class representing an infsup interval
///
/// This class only serves as a uniform interface/representation of an
/// interval. All the behavior will be specified by the template policy class
/// <c>Flavor<T></c> which implements the flavors concept of the standard in coherent way.
///
/// \tparam T                  Number system / parent format
/// \tparam Flavor<typename>   Generic flavor which will be instantiated with the
///                           number system T
/// \tparam RepType            Type of the internal representation
/// \tparam ConcreteInterval   Type of the concrete interval type (sub class)
///
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
class base_interval
{
public:

// typedefs
    typedef T bound_type;

    typedef Flavor<T> flavor_type;

    typedef RepType representation_type;    // Type for the internal representation


protected:

    // Constructor used by the derived classes
    inline
    explicit base_interval(representation_type const& rep) : rep_(rep)
    { }

    // function to create an instance of a derived class
    inline
    static ConcreteInterval concrete_interval(representation_type rep)
    {
        return ConcreteInterval(rep);
    }



    // internal representation
    representation_type rep_;




// Friends

    template<typename, template<typename> class, typename, class>
    friend class base_interval;

    template<typename, template<typename> class>
    friend class interval;

    template<typename, template<typename> class>
    friend class decorated_interval;





//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Operations on intervals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

public:


// -----------------------------------------------------------------------------
// IO operators
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_, typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_, typename CharT, typename Traits>
    friend std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_>&);





// -----------------------------------------------------------------------------
// Boolean functions on intervals
// -----------------------------------------------------------------------------

///@name Boolean functions on intervals
///
///
///@{


    inline
    static bool is_empty(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


    inline
    static bool is_entire(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool is_equal(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);


    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool subset(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool superset(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);


    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool less(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool greater(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);


    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool precedes(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool succeeds(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);


    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool is_interior(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool contains_interior(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);


    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool strictly_less(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool strictly_greater(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);


    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool strictly_precedes(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool strictly_succeeds(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);


    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static bool are_disjoint(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y);


///@}


// -----------------------------------------------------------------------------
// Recommended boolean functions on intervals
// -----------------------------------------------------------------------------

///@name Recommended boolean functions on intervals
///
///
///@{

    inline
    static bool is_common(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    inline
    static bool is_singleton(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_>
    inline
    static bool is_member(T_ m, base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

///@}


// -----------------------------------------------------------------------------
// Numeric functions on intervals
// -----------------------------------------------------------------------------

///@name Numeric functions on intervals
///
///
///@{

    inline
    static T inf(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static T inf(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static T sup(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static T sup(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static T mid(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static T mid(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static T rad(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static T rad(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static std::pair<T,T> mid_rad(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static std::pair<T,T> mid_rad(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static T wid(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static T wid(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static T mag(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static T mag(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static T mig(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static T mig(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);

///@}




// -----------------------------------------------------------------------------
// Non-arithmetic set operations
// -----------------------------------------------------------------------------

///@name Set operations
///
///
///@{


    inline
    static ConcreteInterval intersect(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                      base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

    template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
    inline
    static ConcreteInterval intersect(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
                                      base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);

    inline
    static ConcreteInterval hull(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                 base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

    template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
    inline
    static ConcreteInterval hull(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
                                 base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);

///@}




// -----------------------------------------------------------------------------
// Forward elementary functions
// -----------------------------------------------------------------------------

///@name Forward elementary functions
///
///
///@{

    inline
    static ConcreteInterval pos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval pos(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval neg(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval neg(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval add(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

    template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
    inline
    static ConcreteInterval add(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
                                base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);


    inline
    static ConcreteInterval sub(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

    template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
    inline
    static ConcreteInterval sub(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
                                base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);


    inline
    static ConcreteInterval mul(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

    template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
    inline
    static ConcreteInterval mul(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
                                base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);


    inline
    static ConcreteInterval div(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

    template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
    inline
    static ConcreteInterval div(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
                                base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);


    inline
    static ConcreteInterval recip(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval recip(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval sqr(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval sqr(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval sqrt(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval sqrt(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval fma(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                base_interval<T, Flavor, RepType, ConcreteInterval> const& y,
                                base_interval<T, Flavor, RepType, ConcreteInterval> const& z);

    template<typename T1, typename RepType1, class ConcreteInterval1,
             typename T2, typename RepType2, class ConcreteInterval2,
             typename T3, typename RepType3, class ConcreteInterval3>
    inline
    static ConcreteInterval fma(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
                                base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y,
                                base_interval<T3, Flavor, RepType3, ConcreteInterval3> const& z);


    inline
    static ConcreteInterval pown(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, int p);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval pown(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x, int p);


    inline
    static ConcreteInterval exp(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval exp(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval exp2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval exp2(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval exp10(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval exp10(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval log(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval log(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval log2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval log2(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval log10(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval log10(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval sin(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval sin(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval cos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval cos(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval tan(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval tan(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval asin(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval asin(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval acos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval acos(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval atan(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval atan(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval sinh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval sinh(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval cosh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval cosh(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval tanh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval tanh(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval asinh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval asinh(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval acosh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval acosh(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval atanh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval atanh(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval sign(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval sign(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval ceil(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval ceil(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval floor(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval floor(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval trunc(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval trunc(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval round_ties_to_even(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval round_ties_to_even(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval round_ties_to_away(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval round_ties_to_away(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval abs(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

    template<typename T_, typename RepType_, class ConcreteInterval_>
    inline
    static ConcreteInterval abs(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x);


    inline
    static ConcreteInterval min(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

    template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
    inline
    static ConcreteInterval min(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
                                base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);


    inline
    static ConcreteInterval max(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

    template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
    inline
    static ConcreteInterval max(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
                                base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);

//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ pow(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ atan2(b///@}ase_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//


///@}

//// -----------------------------------------------------------------------------
////  Recommended div to pair function
//// -----------------------------------------------------------------------------
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend std::pair<ConcreteInterval_, ConcreteInterval_>
//    div_to_pair(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//
//// -----------------------------------------------------------------------------
//// Reverse elementary functions
//// -----------------------------------------------------------------------------
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ sqr_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ sqr_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ recip_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ recip_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ abs_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ abs_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ pown_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, int);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ pown_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, int);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ sin_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ sin_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ cos_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ cos_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ tan_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ tan_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ cosh_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ cosh_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ mul_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                       base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                       base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ mul_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ div_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ div_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ div_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ div_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ pow_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ pow_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ pow_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ pow_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ atan2_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                          base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                          base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ atan2_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ atan2_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                          base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                          base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ atan2_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//
//// -----------------------------------------------------------------------------
//// Cancellative addition and subtraction
//// -----------------------------------------------------------------------------
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ cancel_plus(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ cancel_minus(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//

//// -----------------------------------------------------------------------------
//// Recommended forward elementary functions on intervals
//// -----------------------------------------------------------------------------
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ rootn(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, int);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ expm1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ exp2m1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ exp10m1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ logp1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ log2p1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ log10p1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ compoundm1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ hypot(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ r_sqrt(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ sin_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ cos_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ tan_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ asin_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ acos_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ atan_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ atan2_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//
//// -----------------------------------------------------------------------------
//// Recommended interval overlapping
//// -----------------------------------------------------------------------------
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend p1788::overlapping::overlapping_state overlap(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//            base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//
//// -----------------------------------------------------------------------------
//// Recommended slope functions
//// -----------------------------------------------------------------------------
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ exp_slope1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ exp_slope2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ log_slope1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ log_slope2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ cos_slope2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ sin_slope3(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ asin_slope3(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ atan_slope3(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ cosh_slope2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);
//
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ sinh_slope3(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


};

//
//// funktionen
//template<typename T1_, template<typename> class Flavor1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, template<typename> class Flavor2_, typename RepType2_, class ConcreteInterval2_>
//bool is_equal(base_interval<T1_, Flavor1_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor2_, RepType2_, ConcreteInterval2_> const& y);




///@name Boolean functions on intervals
///
///
///@{


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
bool is_empty(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
bool is_entire(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool is_equal(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);

template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool operator==(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);

template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool operator!=(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);



template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool subset(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);

template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool superset(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);


template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool less(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);

template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool greater(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);


template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool precedes(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);

template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool succeeds(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);


template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool is_interior(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);

template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool contains_interior(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);


template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool strictly_less(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);

template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool strictly_greater(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);


template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool strictly_precedes(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);

template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool strictly_succeeds(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);


template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
inline
bool are_disjoint(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y);


///@}


///@name Recommended boolean functions on intervals
///
///
///@{

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
bool is_common(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
bool is_singleton(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

template<typename T_, typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
bool is_member(T_ m, base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

///@}



///@name Numeric functions on intervals
///
///
///@{

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
T inf(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
T sup(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
T mid(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
T rad(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
std::pair<T,T> mid_rad(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
T wid(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
T mag(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
T mig(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

///@}



///@name Set operations
///
///
///@{


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval intersect(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                           base_interval<T, Flavor, RepType, ConcreteInterval> const& y);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval hull(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                      base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

///@}



///@name Forward elementary functions
///
///
///@{

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval pos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval operator+(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);



template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval neg(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval operator-(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);



template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval add(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval operator+(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                           base_interval<T, Flavor, RepType, ConcreteInterval> const& y);



template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval sub(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval operator-(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                           base_interval<T, Flavor, RepType, ConcreteInterval> const& y);



template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval mul(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval operator*(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                           base_interval<T, Flavor, RepType, ConcreteInterval> const& y);



template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval div(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval operator/(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                           base_interval<T, Flavor, RepType, ConcreteInterval> const& y);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval recip(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval sqr(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval sqrt(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval fma(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& z);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval pown(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, int p);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval exp(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval exp2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval exp10(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval log(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval log2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval log10(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval sin(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval cos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval tan(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval asin(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval acos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval atan(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval sinh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval cosh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval tanh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval asinh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval acosh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval atanh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval sign(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval ceil(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval floor(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval trunc(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval round_ties_to_even(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval round_ties_to_away(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval abs(base_interval<T, Flavor, RepType, ConcreteInterval> const& x);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval min(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y);


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
inline
ConcreteInterval max(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y);

///@}



} // namespace infsup

} // namespace p1788


#include "p1788/infsup/base_interval_io_impl.hpp"
#include "p1788/infsup/base_interval_num_func_impl.hpp"
#include "p1788/infsup/base_interval_bool_func_impl.hpp"
#include "p1788/infsup/base_interval_rec_bool_func_impl.hpp"
#include "p1788/infsup/base_interval_set_op_impl.hpp"
#include "p1788/infsup/base_interval_elem_func_impl.hpp"

//#include "p1788/infsup/base_interval_div_pair_func_impl.hpp"
//#include "p1788/infsup/base_interval_rev_elem_func_impl.hpp"
//#include "p1788/infsup/base_interval_cancel_func_impl.hpp"

//#include "p1788/infsup/base_interval_rec_elem_func_impl.hpp"
//#include "p1788/infsup/base_interval_rec_overlap_impl.hpp"
//#include "p1788/infsup/base_interval_rec_slope_func_impl.hpp"

#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_HPP
