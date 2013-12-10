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

// TODO Constructor specification

    decorated_interval()
        : base_interval_type(Flavor<T>::constructor_infsup_dec())
    { }

    decorated_interval(T lower, T upper)
        : base_interval_type(Flavor<T>::constructor_infsup_dec(lower, upper))
    { }

    explicit decorated_interval(T point)
        : base_interval_type(Flavor<T>::constructor_infsup_dec(point))
    { }

    explicit decorated_interval(std::initializer_list<T> points)
        : base_interval_type(Flavor<T>::constructor_infsup_dec(points.begin(), points.end()))
    { }

    explicit decorated_interval(std::string const& str)
        : base_interval_type(Flavor<T>::constructor_infsup_dec(str))
    { }

    decorated_interval(decorated_interval<T, Flavor> const& other)  ///< Copy-constructor
        : base_interval_type(Flavor<T>::constructor_infsup_dec(other.rep_))
    { }

    template<typename T_>
    explicit decorated_interval(base_interval<T_, Flavor, typename Flavor<T_>::representation_dec, decorated_interval<T_, Flavor>> const& other)  ///< Copy-constructor
        : base_interval_type(Flavor<T>::constructor_infsup_dec(other.rep_))
    { }


// -----------------------------------------------------------------------------
// Methods
// -----------------------------------------------------------------------------


    p1788::decoration::decoration decoration() const {
        return Flavor<T>::method_decoration(base_interval_type::rep_);
    }


// -----------------------------------------------------------------------------
// Static methods
// -----------------------------------------------------------------------------

// Required, Creates an empty interval, see P1788/D8.1 Sect. 10.6.2

    static decorated_interval empty() {
        return decorated_interval(Flavor<T>::static_method_empty_dec());
    }

// Required, Creates an entire interval, see P1788/D8.1 Sect. 10.6.2
    static decorated_interval entire() {
        return decorated_interval(Flavor<T>::static_method_entire_dec());
    }


private:

    explicit decorated_interval(typename Flavor<T>::representation_dec rep)
        : base_interval_type(rep)
    {}




    friend class base_interval<T, Flavor, typename Flavor<T>::representation_dec, decorated_interval<T, Flavor>>;

    template<typename, template<typename> class>
    friend class interval;


}; // class decorated_interval



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_HPP
