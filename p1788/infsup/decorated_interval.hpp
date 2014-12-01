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

    // Implementation specific; Empty interval
    decorated_interval()
        : base_interval_type(Flavor<T>::constructor_dec())
    { }

    // Required see numsToInterval(l,u) P1788/D8.1 Sect. 12.12.8.
    decorated_interval(T lower, T upper)
        : base_interval_type(Flavor<T>::constructor_dec(lower, upper))
    { }

    // Required for 754-conforming, see numsToInterval(l,u) formatOf P1788/D8.1 Sect. 12.12.8.
    template<typename L, typename U>
    decorated_interval(L lower, U upper)
        : base_interval_type(Flavor<T>::constructor_dec(lower, upper))
    { }


    // Kind of setDec
    decorated_interval(T lower, T upper, p1788::decoration::decoration dec)
        : base_interval_type(Flavor<T>::constructor_dec(lower, upper, dec))
    { }

    // Kind of setDec
    template<typename L, typename U>
    decorated_interval(L lower, U upper, p1788::decoration::decoration dec)
        : base_interval_type(Flavor<T>::constructor_dec(lower, upper, dec))
    { }


    // Required see textToInterval(l,u) P1788/D8.1 Sect. 12.12.8.
    explicit decorated_interval(std::string const& str)
        : base_interval_type(Flavor<T>::constructor_dec(str))
    { }

    // Implementation specific Copy-constructor
    decorated_interval(decorated_interval<T, Flavor> const& other)  //< Copy-constructor
        : base_interval_type(Flavor<T>::constructor_dec(other.rep_))
    { }

    //Todo P1788/D8.1 Sect. ? Copy-constructor/Conversion
    template<typename T_>
    explicit decorated_interval(decorated_interval<T_, Flavor> const& other)
        : base_interval_type(Flavor<T>::constructor_dec(other.rep_))
    { }

    // newDec
    decorated_interval(interval<T, Flavor> const& other)  //< Copy-constructor
        : base_interval_type(Flavor<T>::constructor_dec(other.rep_))
    { }

    // newDec mixedtype
    template<typename T_>
    explicit decorated_interval(interval<T_, Flavor> const& other)
        : base_interval_type(Flavor<T>::constructor_dec(other.rep_))
    { }

    // setDec
    decorated_interval(interval<T, Flavor> const& other, p1788::decoration::decoration dec)  //< Copy-constructor
        : base_interval_type(Flavor<T>::constructor_dec(other.rep_, dec))
    { }

    // setDec mixedtype
    template<typename T_>
    explicit decorated_interval(interval<T_, Flavor> const& other, p1788::decoration::decoration dec)
        : base_interval_type(Flavor<T>::constructor_dec(other.rep_, dec))
    { }

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
    /// \note The function is forwarded to the function <c>Flavor\<T\>::empty_dec()</c>
    /// which creates the representation for an empty decorated interval.
    /// \see p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::empty_dec()
    ///
    static decorated_interval empty() {
        return decorated_interval(Flavor<T>::empty_dec());
    }

    /// \brief Returns an entire decorated interval
    ///
    /// \return \f$[-\infty,+\infty]\f$<sub>\link p1788::decoration::decoration dac\endlink</sub>
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::entire_dec()</c>
    /// which creates the representation for an entire decorated interval.
    /// \see p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::entire_dec()
    ///
    static decorated_interval entire() {
        return decorated_interval(Flavor<T>::entire_dec());
    }

    /// \brief Returns an ill-formed decorated interval (Not an Interval)
    ///
    /// \return  NaI (= \f$\emptyset\f$<sub>\link p1788::decoration::decoration ill\endlink</sub>)
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::nai()</c>
    /// which creates the representation for an ill-formed decorated interval (NaI).
    /// \see p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::nai()
    ///
    static decorated_interval nai() {
        return decorated_interval(Flavor<T>::nai());
    }

///@}



// -----------------------------------------------------------------------------
// Decorated interval specific methods
// -----------------------------------------------------------------------------

    /// \brief Checks if the interval is NaI
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::is_nai(representation_dec const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \retval true    \p x is NaI
    /// \retval false   otherwise
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::is_nai(representation_dec const& x) mpfr_bin_ieee754_flavor::is_nai(representation_dec const& x) \endlink</c>
    ///
    static bool is_nai(decorated_interval<T,Flavor> const& x)
    {
        return Flavor<T>::is_nai(x.rep_);
    }


    static p1788::decoration::decoration decoration(decorated_interval<T,Flavor> const& x)
    {
        return Flavor<T>::decoration(x.rep_);
    }


private:

    explicit decorated_interval(typename Flavor<T>::representation_dec rep)
        : base_interval_type(rep)
    {}




    friend class base_interval<T, Flavor, typename Flavor<T>::representation_dec, decorated_interval<T, Flavor>>;

    template<typename, template<typename> class>
    friend class interval;


}; // class decorated_interval





template<typename T, template<typename> class Flavor>
bool is_nai(decorated_interval<T, Flavor> const& x)
{
    return decorated_interval<T, Flavor>::is_nai(x);
}


template<typename T, template<typename> class Flavor>
p1788::decoration::decoration decoration(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>::decoration(x);
}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_HPP
