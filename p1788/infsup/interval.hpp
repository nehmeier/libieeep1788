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

#include "p1788/infsup/base_interval.hpp"


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                        Forward declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


namespace p1788
{

namespace infsup
{


template<typename T, template<typename> class Flavor>
class interval;



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
// Trait is_infsup_base_interval_implementation
//------------------------------------------------------------------------------

// Ignore the warning about non-virtual destructors
// on GCC  push the last diagnostic state and disable -Weffc++
//TODO support other compiler
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"


template<typename T, template<typename> class Flavor>
class is_infsup_base_interval_implementation<p1788::infsup::interval<T,Flavor>>
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

// TODO Constructor specification

    interval()
        : base_interval_type(Flavor<T>::constructor_infsup())
    { }

    interval(T lower, T upper)
        : base_interval_type(Flavor<T>::constructor_infsup(lower, upper))
    { }

    explicit interval(T point)
        : base_interval_type(Flavor<T>::constructor_infsup(point))
    { }

    explicit interval(std::initializer_list<T> points)
        : base_interval_type(Flavor<T>::constructor_infsup(points.begin(), points.end()))
    { }

    explicit interval(std::string const& str)
        : base_interval_type(Flavor<T>::constructor_infsup(str))
    { }

    interval(interval<T, Flavor> const& other)  ///< Copy-constructor
        : base_interval_type(Flavor<T>::constructor_infsup(other.rep_))
    { }

    template<typename T_>
    explicit interval(interval<T_, Flavor> const& other)  ///< Copy-constructor
        : base_interval_type(Flavor<T>::constructor_infsup(other.rep_))
    { }


// -----------------------------------------------------------------------------
// Static methods
// -----------------------------------------------------------------------------

// Required, Creates an empty interval, see P1788/D8.1 Sect. 10.6.2

    static interval empty() {
        return interval(Flavor<T>::static_method_empty());
    }

// Required, Creates an entire interval, see P1788/D8.1 Sect. 10.6.2
    static interval entire() {
        return interval(Flavor<T>::static_method_entire());
    }


private:

    interval(typename Flavor<T>::representation rep)
        : base_interval_type(rep)
    {}




    friend class base_interval<T, Flavor, typename Flavor<T>::representation, interval<T, Flavor>>;

    template<typename, template<typename> class>
    friend class interval;


}; // class interval



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_INTERVAL_HPP
