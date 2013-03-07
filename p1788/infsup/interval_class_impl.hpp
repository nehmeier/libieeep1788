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

#ifndef LIBIEEEP1788_P1788_INFSUP_INTERVAL_CLASS_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_INTERVAL_CLASS_IMPL_HPP

namespace p1788
{

namespace infsup
{


// -----------------------------------------------------------------------------
// public
// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
interval<T, Flavor>::interval ( )
    : rep_( Flavor<T>::constructor_infsup() )
{
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor>::interval ( T lower, T upper )
    : rep_( Flavor<T>::constructor_infsup(lower, upper) )
{
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor>::interval ( T point )
    : rep_( Flavor<T>::constructor_infsup(point) )
{
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor>::interval ( std::initializer_list<T> points )
    : rep_( Flavor<T>::constructor_infsup(points.begin(), points.end()) )
{
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor>::interval ( std::string const& str )
    : rep_( Flavor<T>::constructor_infsup(str) )
{
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor>::interval (interval<T, Flavor> const& other)  ///< Copy-constructor
    : rep_(Flavor<T>::constructor_infsup( other.rep_ ))
{
}


template< typename T, template< typename > class Flavor>
template<typename TT>
interval<T, Flavor>::interval (interval<TT, Flavor> const& other)  ///< Copy-constructor
    : rep_(Flavor<T>::constructor_infsup( other.rep_ ))
{
}


// -----------------------------------------------------------------------------
// Methods
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
T interval<T, Flavor>::lower ( ) const
{
    return Flavor<T>::method_lower(rep_);
}

template< typename T, template< typename > class Flavor >
T interval<T, Flavor>::upper ( ) const
{
    return Flavor<T>::method_upper(rep_);
}

template< typename T, template< typename > class Flavor >
T interval<T, Flavor>::mid ( ) const
{
    return Flavor<T>::method_mid(rep_);
}

template< typename T, template< typename > class Flavor >
T interval<T, Flavor>::rad ( ) const
{
    return Flavor<T>::method_rad(rep_);
}



// -----------------------------------------------------------------------------
// Static methods
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
interval<T, Flavor> interval<T, Flavor>::empty ( )
{
    return interval<T, Flavor>(Flavor<T>::static_method_empty());
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> interval<T, Flavor>::entire ( )
{
    return interval<T, Flavor>(Flavor<T>::static_method_entire());
}




// -----------------------------------------------------------------------------
// private
// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
interval<T, Flavor>::interval ( typename Flavor<T>::representation const& rep)
    : rep_( rep )
{
}


// -----------------------------------------------------------------------------
// Methods
// -----------------------------------------------------------------------------

template< typename T, template< typename > class Flavor >
typename Flavor<T>::representation& interval<T, Flavor>::rep()
{
    return rep_;
}

template< typename T, template< typename > class Flavor >
typename Flavor<T>::representation const& interval<T, Flavor>::rep() const
{
    return rep_;
}



} // namespace infsup

} // namespace p1788

#endif // LIBIEEEP1788_P1788_INFSUP_INTERVAL_CLASS_IMPL_HPP
