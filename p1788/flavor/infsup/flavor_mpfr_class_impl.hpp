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

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup()
{
    return static_method_empty();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup_dec()
{
    return static_method_empty_dec();
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup(T lower, T upper)
{
//TODO  invalid arguments => exception?

    return representation(lower, upper);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup_dec(T lower, T upper)
{
//TODO  invalid arguments => exception?

    return representation_dec(representation(lower, upper), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup(T point)
{
//TODO  invalid argument => exception?

    return representation(point, point);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup_dec(T point)
{
//TODO  invalid argument => exception?

    return representation_dec(representation(point, point), p1788::decoration::decoration::trv);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
template<typename L, typename U>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup(L lower, U upper)
{
    return representation(lower, upper);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
template<typename L, typename U>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup_dec(L lower, U upper)
{
    return representation_dec(representation(lower, upper));
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
template<typename T_>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup(T_ point)
{
    return representation(point, point);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
template<typename T_>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup_dec(T_ point)
{
    return representation_dec(representation(point, point));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup(std::string const& str)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    std::string tmp = str;

    tmp.erase(remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);

    if (tmp == "[ENTIRE]")
        return static_method_entire();

    if (tmp == "[EMPTY]")
        return static_method_empty();

    return representation(0.0, 0.0);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup_dec(std::string const& str)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    std::string tmp = str;

    tmp.erase(remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);

    if (tmp == "[ENTIRE]")
        return static_method_entire_dec();

    if (tmp == "[EMPTY]")
        return static_method_empty_dec();

    return representation_dec(representation(0.0, 0.0), p1788::decoration::decoration::trv);
}


//TODO necessary?
//template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
//template<typename ConstRandomAccessIterator>
//typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
//mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup(ConstRandomAccessIterator first,
//                                   ConstRandomAccessIterator last)
//{
//    //TODO check iterator
//    auto result = std::minmax_element(first, last);
//
////TODO  invalid argument => exception?
//    return representation(*result.first, *result.second);
//}
//
//template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
//template<typename ConstRandomAccessIterator>
//typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
//mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup_dec(ConstRandomAccessIterator first,
//                                   ConstRandomAccessIterator last)
//{
//    //TODO check iterator
//    auto result = std::minmax_element(first, last);
//
////TODO  invalid argument => exception?
//    return representation_dec(representation(*result.first, *result.second), p1788::decoration::decoration::trv);
//}



template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup(representation const& other)
{
    return other;
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup_dec(representation_dec const& other)
{
    return other;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
template<typename TT>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup(representation_type<TT> const& other)
{
    mpfr_var::setup();

    mpfr_var lower(other.first, MPFR_RNDD);
    mpfr_var upper(other.second, MPFR_RNDU);

    return representation(lower.template get<T>(MPFR_RNDD), upper.template get<T>(MPFR_RNDU));
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
template<typename TT>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::constructor_infsup_dec(representation_dec_type<TT> const& other)
{
    mpfr_var::setup();

    mpfr_var lower(other.first.first, MPFR_RNDD);
    mpfr_var upper(other.first.second, MPFR_RNDU);

    return representation_dec(representation(lower.template get<T>(MPFR_RNDD), upper.template get<T>(MPFR_RNDU)), other.second);
}


// Methods

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
T
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::method_lower(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    return x.first;
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
T
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::method_lower(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    return x.first.first;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
T
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::method_upper(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    return x.second;
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
T
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::method_upper(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    return x.first.second;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
T
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::method_mid(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return (x.first + x.second) / 2.0;
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
T
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::method_mid(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return (x.first.first + x.first.second) / 2.0;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
T
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::method_rad(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return (x.second - x.first) / 2.0;
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
T
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::method_rad(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return (x.first.second - x.first.first) / 2.0;
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
p1788::decoration::decoration
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::method_decoration(mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec const& x)
{
    return x.second;
}


// Static Methods

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_empty()
{
    return representation(std::numeric_limits<T>::quiet_NaN(),
                          std::numeric_limits<T>::quiet_NaN());
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_empty_dec()
{
    return representation_dec(representation(std::numeric_limits<T>::quiet_NaN(),
                          std::numeric_limits<T>::quiet_NaN()), p1788::decoration::decoration::trv);
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire()
{
    return representation(-std::numeric_limits<T>::infinity(),
                          std::numeric_limits<T>::infinity());
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
typename mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::representation_dec
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::static_method_entire_dec()
{
    return representation_dec(representation(-std::numeric_limits<T>::infinity(),
                          std::numeric_limits<T>::infinity()), p1788::decoration::decoration::trv);
}


template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
void
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::setup()
{
    mpfr_var::forced_setup();
}

template<typename T, subnormalize SUBNORMALIZE, auto_setup AUTOSETUP>
void
mpfr_flavor<T, SUBNORMALIZE, AUTOSETUP>::free_cache()
{
    mpfr_var::free_cache();
}


} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_CLASS_IMPL_HPP
