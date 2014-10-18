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



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                       Definition of class base_interval
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------




namespace p1788
{

namespace infsup
{



// \brief Base class for a level 2 infsup interval
//
//
// Base class representing a level 2 infsup interval, see P1788/D7.0 Sect. 4.1.
//
// This class only serves as a uniform interface/representation of an
// interval. All the behavior will be specified by the template policy class
// Flavor<T> which implements the flavors concept of the standard in coherent way,
// see P1788/D7.0 Sect. 5.
//
// \param T                  Number system / parent format
// \param Flavor<typename>   Generic flavor which will be instantiated with the
//                           number system T
// \param RepType            Type of the internal representation
// \param ConcreteInterval   Type of the concrete interval type (sub class)
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
class base_interval
{
//    static_assert(
//    std::is_same<typename Flavor<T>::representation, RepType>::value
//        || std::is_same<typename Flavor<T>::representation_dec, RepType>::value,
//        "Representation is not supported!");
//
//    static_assert(p1788::util::is_infsup_base_interval_implementation<ConcreteInterval>::value, "Concrete interval type is not supported!");
//
//    static_assert(std::is_same<typename ConcreteInterval::bound_type, T>::value, "Bound types are different!");
//
//    static_assert(std::is_same<typename ConcreteInterval::flavor_type, Flavor<T>>::value, "Flavor types are different!");



// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// public
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


public:

    typedef T bound_type;

    typedef Flavor<T> flavor_type;

    typedef RepType representation_type;


// -----------------------------------------------------------------------------
// Methods
// -----------------------------------------------------------------------------


    // \brief Foo Bar baz
    // Implementation specific
    // \return T
    //
    //
    T lower() const {
        return Flavor<T>::method_lower(rep_);
    }

// Implementation specific
    T upper() const {
        return Flavor<T>::method_upper(rep_);
    }

// Implementation specific
    T mid() const {
        return Flavor<T>::method_mid(rep_);
    }

// Implementation specific
    T rad() const {
        return Flavor<T>::method_rad(rep_);
    }


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// protected
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

protected:


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

    explicit base_interval(representation_type const& rep) : rep_(rep)
    { }


// -----------------------------------------------------------------------------
// Static methods
// -----------------------------------------------------------------------------

    static ConcreteInterval concrete_interval(representation_type rep) {
        return ConcreteInterval(rep);
    }

// -----------------------------------------------------------------------------
// Members
// -----------------------------------------------------------------------------

    representation_type rep_;



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Friends
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

    template<typename, template<typename> class, typename, class>
    friend class base_interval;

    template<typename, template<typename> class>
    friend class interval;

    template<typename, template<typename> class>
    friend class decorated_interval;


// -----------------------------------------------------------------------------
// IO operators
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_, typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_, typename CharT, typename Traits>
    friend std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_>&);


// -----------------------------------------------------------------------------
// Non-arithmetic set operations
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_
    intersect(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_
    hull(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Numeric functions on intervals
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ inf(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ sup(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ mid(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ rad(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend std::pair<T_, T_> mid_rad(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ wid(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ mag(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend T_ mig(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Boolean functions on intervals
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool is_empty(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool is_entire(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

//TODO operator==?
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool is_equal(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

//TODO subset oder contained_in?
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool subset(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

//TODO superset oder contains?
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool superset(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool less(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool greater(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool precedes(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool succeeds(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool is_interior(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool contains_interior(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool strictly_less(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool strictly_greater(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool strictly_precedes(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool strictly_succeeds(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool are_disjoint(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Forward elementary functions
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pos(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ neg(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ add (base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sub(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ mul(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ div(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ recip(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sqr(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sqrt(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ fma(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                 base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                 base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

//TODO notwendig?
//    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
//    friend ConcreteInterval_ interval_case(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                           base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
//                                           base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pown(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, int p);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pow(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp10(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log10(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sin(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cos(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ tan(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ asin(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ acos(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sinh(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cosh(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ tanh(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ asinh(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ acosh(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atanh(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sign(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ ceil(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ floor(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ trunc(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ round_ties_to_even(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ round_ties_to_away(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ abs(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ min(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ max(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
//  Recommended div to pair function
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend std::pair<ConcreteInterval_, ConcreteInterval_>
    div_to_pair(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Reverse elementary functions
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sqr_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sqr_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ recip_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ recip_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ abs_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ abs_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pown_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, int);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pown_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, int);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sin_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sin_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cos_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cos_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ tan_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ tan_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cosh_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cosh_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ mul_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                       base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                       base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ mul_rev(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ div_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ div_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ div_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ div_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pow_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pow_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pow_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                        base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ pow_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan2_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                          base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                          base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan2_rev1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan2_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                          base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
                                          base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan2_rev2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Cancellative addition and subtraction
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cancel_plus(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cancel_minus(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Recommended boolean functions on intervals
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool is_common(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool is_singleton(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool is_member(T_ m, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Recommended forward elementary functions on intervals
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ rootn(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, int);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ expm1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp2m1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp10m1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ logp1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log2p1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log10p1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ compoundm1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ hypot(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ r_sqrt(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sin_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cos_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ tan_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ asin_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ acos_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan2_pi(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Recommended interval overlapping
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend p1788::overlapping::overlapping_state overlap(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&,
            base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


// -----------------------------------------------------------------------------
// Recommended slope functions
// -----------------------------------------------------------------------------

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp_slope1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ exp_slope2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log_slope1(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ log_slope2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cos_slope2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sin_slope3(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ asin_slope3(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ atan_slope3(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ cosh_slope2(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);

    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend ConcreteInterval_ sinh_slope3(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const&);


};

} // namespace infsup

} // namespace p1788


#include "p1788/infsup/base_interval_io_impl.hpp"
#include "p1788/infsup/base_interval_set_op_impl.hpp"
#include "p1788/infsup/base_interval_num_func_impl.hpp"
#include "p1788/infsup/base_interval_bool_func_impl.hpp"
#include "p1788/infsup/base_interval_elem_func_impl.hpp"
#include "p1788/infsup/base_interval_div_pair_func_impl.hpp"
#include "p1788/infsup/base_interval_rev_elem_func_impl.hpp"
#include "p1788/infsup/base_interval_cancel_func_impl.hpp"
#include "p1788/infsup/base_interval_rec_bool_func_impl.hpp"
#include "p1788/infsup/base_interval_rec_elem_func_impl.hpp"
#include "p1788/infsup/base_interval_rec_overlap_impl.hpp"
#include "p1788/infsup/base_interval_rec_slope_func_impl.hpp"

#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_HPP
