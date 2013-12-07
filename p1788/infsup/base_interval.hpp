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
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
class base_interval;



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
// Trait is_infsup_base_interval
//------------------------------------------------------------------------------

// Ignore the warning about non-virtual destructors
// on GCC  push the last diagnostic state and disable -Weffc++
//TODO support other compiler
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"


/// \brief Trait to check if type T is an p1788::infsup::base_interval
///
/// \param T type
/// \return field value contains boolean result of the check
///
///
template<typename T>
class is_infsup_base_interval
    : public std::integral_constant<bool, false>
{ };

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
class is_infsup_base_interval<p1788::infsup::base_interval<T,Flavor,RepType,ConcreteInterval>>
            : public std::integral_constant<bool, true>
{ };

// on GCC  enable the diagnostic state -Weffc++ again
#pragma GCC diagnostic pop


} // namespace util

} // namespace p1788



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                       Definition of class base_interval
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------




namespace p1788
{

namespace infsup
{



/// \brief Base class for a level 2 infsup interval
///
///
/// Base class representing a level 2 infsup interval, see P1788/D7.0 Sect. 4.1.
///
/// This class only serves as a uniform interface/representation of an
/// interval. All the behavior will be specified by the template policy class
/// Flavor<T> which implements the flavors concept of the standard in coherent way,
/// see P1788/D7.0 Sect. 5.
///
/// \param T                  Number system / parent format
/// \param Flavor<typename>   Generic flavor which will be instantiated with the
///                           number system T
/// \param RepType            Type of the internal representation
/// \param ConcreteInterval   Type of the concrete interval type (sub class)
///
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
class base_interval
{
    static_assert(
    std::is_same<typename Flavor<T>::representation_type, RepType>::value
        || std::is_same<typename Flavor<T>::representation_dec_type, RepType>::value,
        "Representation is not supported!");

    static_assert(p1788::util::is_infsup_base_interval<ConcreteInterval>::value, "Concrete interval type is not supported!");

    static_assert(std::is_same<typename ConcreteInterval::bound_type, T>::value, "Bound types are different!");

    static_assert(std::is_same<typename ConcreteInterval::flavor_type, Flavor<T>>::value, "Flavor types are different!");



// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// public
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


public:

    typedef T bound_type;

    typedef Flavor<T> flavor_type;


// -----------------------------------------------------------------------------
// Methods
// -----------------------------------------------------------------------------


    /// \brief Foo Bar baz
    /// Implementation specific
    /// \return T
    ///
    ///
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
// Static methods
// -----------------------------------------------------------------------------

// Required, Creates an empty interval, see P1788/D8.1 Sect. 10.6.2

    static interval<T, Flavor> empty() {
        return interval<T, Flavor>(Flavor<T>::static_method_empty());
    }

// Required, Creates an entire interval, see P1788/D8.1 Sect. 10.6.2
    static interval<T, Flavor> entire() {
        return interval<T, Flavor>(Flavor<T>::static_method_entire());
    }




// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// protected
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

protected:

    typedef RepType representation_type;


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

    base_interval(representation_type const& rep) : rep_(rep)
    { }


// -----------------------------------------------------------------------------
// Static methods
// -----------------------------------------------------------------------------

    static ConcreteInterval concrete_interval(representation_type rep)
    {
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




};

} // namespace infsup

} // namespace p1788

#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_HPP
