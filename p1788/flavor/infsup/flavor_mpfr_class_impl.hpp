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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_CLASS_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_CLASS_IMPL_HPP

#include "p1788/util/assert.hpp"

namespace p1788
{

namespace flavor
{

namespace infsup
{


// Constructors

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::constructor_infsup()
{
    return static_method_empty();
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::constructor_infsup(T lower, T upper)
{
//TODO  invalid arguments => exception?

    return representation(lower, upper);
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::constructor_infsup(T point)
{
//TODO  invalid argument => exception?

    return representation(point, point);
}

template<typename T>
template<typename ConstRandomAccessIterator>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::constructor_infsup(ConstRandomAccessIterator first,
        ConstRandomAccessIterator last)
{
    //TODO check iterator
    auto result = std::minmax_element(first, last);

//TODO  invalid argument => exception?
    return representation(*result.first, *result.second);
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::constructor_infsup(std::string const& str)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    std::string tmp = str;

    tmp.erase(remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);

    if (tmp == "ENTIRE")
        return static_method_entire();

    if (tmp == "EMPTY")
        return static_method_empty();

    return representation(0.0, 0.0);
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::constructor_infsup(representation const& other)
{
    return other;
}

template<typename T>
template<typename TT>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::constructor_infsup(representation_type<TT> const& other)
{
    mpfr_var::setup();

    mpfr_var lower(other.first, MPFR_RNDD);
    mpfr_var upper(other.second, MPFR_RNDU);

    return representation(lower.get(MPFR_RNDD), upper.get(MPFR_RNDU));
}


// Methods

template<typename T>
T
mpfr_flavor<T>::method_lower(mpfr_flavor<T>::representation const& x)
{
    return x.first;
}

template<typename T>
T
mpfr_flavor<T>::method_upper(mpfr_flavor<T>::representation const& x)
{
    return x.second;
}

template<typename T>
T
mpfr_flavor<T>::method_mid(mpfr_flavor<T>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    mpfr_var::setup();

    mpfr_var lower(x.first, MPFR_RNDD);
    mpfr_var upper(x.second, MPFR_RNDU);

    return (x.first + x.second) / 2.0;
}

template<typename T>
T
mpfr_flavor<T>::method_rad(mpfr_flavor<T>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return (x.second - x.first) / 2.0;
}

// Static Methods

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::static_method_empty()
{
    return representation(std::numeric_limits<double>::quiet_NaN(),
                          std::numeric_limits<double>::quiet_NaN());
}

template<typename T>
typename mpfr_flavor<T>::representation
mpfr_flavor<T>::static_method_entire()
{
    return representation(-std::numeric_limits<double>::infinity(),
                          std::numeric_limits<double>::infinity());
}



} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_CLASS_IMPL_HPP
