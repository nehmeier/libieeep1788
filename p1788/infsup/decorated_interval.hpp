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

#include "p1788/infsup/forward_declaration.hpp"
#include "p1788/infsup/base_interval.hpp"




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
// Trait is_infsup_base_interval_implementation
//------------------------------------------------------------------------------

// Ignore the warning about non-virtual destructors
// on GCC  push the last diagnostic state and disable -Weffc++
//TODO support other compiler
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"




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


/// \brief
///
/// \param
/// \param
/// \return
///
///
template<typename T, template<typename> class Flavor>
class decorated_interval final
    : public base_interval<T, Flavor, typename Flavor<T>::representation_dec, decorated_interval<T, Flavor>>
{

private:
    typedef base_interval<T, Flavor, typename Flavor<T>::representation_dec, decorated_interval<T, Flavor>> base_interval_type;



public:



// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

    // Implementation specific; Empty interval
    decorated_interval()
        : base_interval_type(Flavor<T>::constructor_infsup_dec())
    { }

    // Required see numsToInterval(l,u) P1788/D8.1 Sect. 12.12.8.
    decorated_interval(T lower, T upper)
        : base_interval_type(Flavor<T>::constructor_infsup_dec(lower, upper))
    { }

    // Implementation specific, Singleton
    explicit decorated_interval(T point)
        : base_interval_type(Flavor<T>::constructor_infsup_dec(point))
    { }

//TODO necessary?
//    // Required for 754-conforming, see numsToInterval(l,u) formatOf P1788/D8.1 Sect. 12.12.8.
//    template<typename L, typename U>
//    decorated_interval(L lower, U upper)
//        : base_interval_type(Flavor<T>::constructor_infsup_dec(lower, upper))
//    {
//        //TODO static_assert hier oder im Flavor?
//        //TODO int-werte landen hier und funktionieren somit nicht
//        static_assert(std::numeric_limits<T>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
//        static_assert(std::numeric_limits<L>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
//        static_assert(std::numeric_limits<U>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
//    }
//
//TODO necessary?
//    // Implementation specificfor 754-conforming, Singleton formatOf
//    template<typename T_>
//    explicit decorated_interval(T_ point)
//        : base_interval_type(Flavor<T>::constructor_infsup_dec(point))
//    {
//        //TODO static_assert hier oder im Flavor?
//        //TODO int-werte landen hier und funktionieren somit nicht
//        static_assert(std::numeric_limits<T>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
//        static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
//    }


    // Required see textToInterval(l,u) P1788/D8.1 Sect. 12.12.8.
    explicit decorated_interval(std::string const& str)
        : base_interval_type(Flavor<T>::constructor_infsup_dec(str))
    { }

// Todo necessary? initializer list
//    explicit decorated_interval(std::initializer_list<T> points)
//        : base_interval_type(Flavor<T>::constructor_infsup(points.begin(), points.end()))
//    { }

    // Implementation specific Copy-constructor
    decorated_interval(base_interval_type const& other)  //< Copy-constructor
        : base_interval_type(Flavor<T>::constructor_infsup_dec(other.rep_))
    { }

    //Todo P1788/D8.1 Sect. ? Copy-constructor/Conversion
    template<typename T_>
    explicit decorated_interval(base_interval<T_, Flavor, typename Flavor<T_>::representation_dec, decorated_interval<T_, Flavor>> const& other)
        : base_interval_type(Flavor<T>::constructor_infsup_dec(other.rep_))
    { }

// -----------------------------------------------------------------------------
// Methods
// -----------------------------------------------------------------------------


    p1788::decoration::decoration decoration() const {
        return Flavor<T>::method_decoration(base_interval_type::rep_);
    }


// -----------------------------------------------------------------------------
// Interval constants
// -----------------------------------------------------------------------------

///@name Interval constants
///
///
///@{

    /// \brief Returns an empty decorated interval
    ///
    /// \return \f$\emptyset\f$<sub>\link p1788::decoration::decoration trv\endlink</sub>
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::static_method_empty_dec()</c>
    /// which creates the representation for an empty decorated interval.
    /// \see p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::static_method_empty_dec()
    ///
    static decorated_interval empty() {
        return decorated_interval(Flavor<T>::static_method_empty_dec());
    }

    /// \brief Returns an entire decorated interval
    ///
    /// \return \f$[-\infty,+\infty]\f$<sub>\link p1788::decoration::decoration dac\endlink</sub>
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::static_method_entire_dec()</c>
    /// which creates the representation for an entire decorated interval.
    /// \see p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::static_method_entire_dec()
    ///
    static decorated_interval entire() {
        return decorated_interval(Flavor<T>::static_method_entire_dec());
    }

    /// \brief Returns an ill-formed decorated interval (Not an Interval)
    ///
    /// \return  NaI (= \f$\emptyset\f$<sub>\link p1788::decoration::decoration ill\endlink</sub>)
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::static_method_nai_dec()</c>
    /// which creates the representation for an ill-formed decorated interval (NaI).
    /// \see p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::static_method_nai_dec()
    ///
    static decorated_interval nai() {
        return decorated_interval(Flavor<T>::static_method_nai_dec());
    }

///@}

private:

    explicit decorated_interval(typename Flavor<T>::representation_dec rep)
        : base_interval_type(rep)
    {}




    friend class base_interval<T, Flavor, typename Flavor<T>::representation_dec, decorated_interval<T, Flavor>>;

    template<typename, template<typename> class>
    friend class interval;



// -----------------------------------------------------------------------------
// Boolean functions on intervals
// -----------------------------------------------------------------------------

//TODO 12.12.9
    template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
    friend bool is_nai(decorated_interval<T_, Flavor_> const&);



}; // class decorated_interval



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_HPP
