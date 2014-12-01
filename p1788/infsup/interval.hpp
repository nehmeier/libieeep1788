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

#include "p1788/infsup/forward_declaration.hpp"
#include "p1788/infsup/base_interval.hpp"





//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                       Definition of class base_interval
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------




namespace p1788
{

namespace infsup
{


/// \brief ff
///
/// \param
/// \param
/// \return
///
///
template<typename T, template<typename> class Flavor>
class interval final
    : public base_interval<T, Flavor, typename Flavor<T>::representation, interval<T, Flavor>>
{

private:
    typedef base_interval<T, Flavor, typename Flavor<T>::representation, interval<T, Flavor>> base_interval_type;



public:



// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------


    // Implementation specific; Empty interval
    interval()
        : base_interval_type(Flavor<T>::constructor())
    { }

    // Required see numsToInterval(l,u) P1788/D8.1 Sect. 12.12.8.
    interval(T lower, T upper)
        : base_interval_type(Flavor<T>::constructor(lower, upper))
    { }

    // Required for 754-conforming, see numsToInterval(l,u) formatOf P1788/D8.1 Sect. 12.12.8.
    template<typename L, typename U>
    interval(L lower, U upper)
        : base_interval_type(Flavor<T>::constructor(lower, upper))
    { }

    // Required see textToInterval(l,u) P1788/D8.1 Sect. 12.12.8.
    explicit interval(std::string const& str)
        : base_interval_type(Flavor<T>::constructor(str))
    { }

    // Implementation specific Copy-constructor
    interval(interval<T, Flavor> const& other)  //< Copy-constructor
        : base_interval_type(Flavor<T>::constructor(other.rep_))
    { }

    //Todo P1788/D8.1 Sect. ? Copy-constructor/Conversion
    template<typename T_>
    explicit interval(interval<T_, Flavor> const& other)
        : base_interval_type(Flavor<T>::constructor(other.rep_))
    { }

    // Interval part
    interval(decorated_interval<T, Flavor> const& other)  //< Copy-constructor
        : base_interval_type(Flavor<T>::constructor(other.rep_))
    { }

    //  Interval part mixed type
    template<typename T_>
    explicit interval(decorated_interval<T_, Flavor> const& other)
        : base_interval_type(Flavor<T>::constructor(other.rep_))
    { }


// -----------------------------------------------------------------------------
// Interval constants
// -----------------------------------------------------------------------------

///@name Interval constants
///
///
///@{

    /// \brief Returns an empty interval
    ///
    /// \return \f$\emptyset\f$
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::empty()</c>
    /// which creates the representation for an empty interval.
    /// \see p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::empty()
    ///
    static interval empty() {
        return interval(Flavor<T>::empty());
    }

    /// \brief Returns an entire interval
    ///
    /// \return \f$[-\infty,+\infty]\f$
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::entire()</c>
    /// which creates the representation for an entire interval.
    /// \see p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::entire()
    ///
    static interval entire() {
        return interval(Flavor<T>::entire());
    }

///@}


private:

    explicit interval(typename Flavor<T>::representation rep)
        : base_interval_type(rep)
    {}


    friend class base_interval<T, Flavor, typename Flavor<T>::representation, interval<T, Flavor>>;

    template<typename, template<typename> class>
    friend class interval;


}; // class interval



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_INTERVAL_HPP
