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

#include "p1788/infsup/base_interval.hpp"


namespace p1788
{

namespace infsup
{


template<typename T, template<typename> class Flavor>
class decorated_interval final
    : public base_interval<T, Flavor, typename Flavor<T>::rep_dec, decorated_interval<T, Flavor>>
{

private:
    typedef base_interval<T, Flavor, typename Flavor<T>::rep_dec, decorated_interval<T, Flavor>> base_interval_type;



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
    explicit decorated_interval(decorated_interval<T_, Flavor> const& other)  ///< Copy-constructor
        : base_interval_type(Flavor<T>::constructor_infsup_dec(other.rep_))
    { }


// -----------------------------------------------------------------------------
// Methods
// -----------------------------------------------------------------------------


    p1788::decoration::decoration lower() const {
        return Flavor<T>::method_decoration(base_interval_type::rep_);
    }


private:

    decorated_interval(typename Flavor<T>::rep_dec rep)
        : base_interval_type(rep)
    {}




    friend class base_interval<T, Flavor, typename Flavor<T>::rep_dec, decorated_interval<T, Flavor>>;

    template<typename, template<typename> class>
    friend class interval;


}; // class decorated_interval



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_HPP
