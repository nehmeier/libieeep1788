//
//                              libieeep1788
//
//   An implementation of the preliminary IEEE P1788 standard for
//   interval arithmetic
//
//
//   Copyright 2013 - 2015
//
//   Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
//   Department of Computer Science,
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
#include "p1788/decoration/decoration.hpp"




//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                       Definition of class decorated_interval
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


namespace p1788
{

namespace infsup
{


/// \brief Decorated interval class
///
/// Front end of an inf-sup decorated interval.
/// All the behavior of the decorated interval type is specified by the
/// template policy class <c>Flavor</c>.
///
/// \tparam T type used for the interval bounds
/// \tparam Flavor template policy class specifying the behavior
///
template<typename T, template<typename> class Flavor>
class decorated_interval final
    : public base_interval<T, Flavor, typename Flavor<T>::representation_dec, decorated_interval<T, Flavor>>
{
private:

    // base interval type
    typedef base_interval<T, Flavor, typename Flavor<T>::representation_dec, decorated_interval<T, Flavor>> base_interval_type;


public:


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

///@name Constructors
///
///
///@{

    /// \brief Creates an empty decorated interval
    ///
    /// \return \f$\emptyset\f$<sub>\link p1788::decoration::decoration trv\endlink</sub>
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::empty_dec()</c>
    /// which creates the representation for an empty decorated interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::empty_dec() \endlink
    ///
    inline
    decorated_interval()
        : base_interval_type(Flavor<T>::empty_dec())
    { }


    /// \brief Creates a decorated interval with a lower and an upper bound
    ///
    /// \param lower lower bound
    /// \param upper upper bound
    ///
    /// \return \li \f$[lower,upper]\f$<sub>\link p1788::decoration::decoration com\endlink</sub> if \p \f$ lower \leq upper \wedge lower \not= \pm\infty \wedge upper \not= \pm\infty \f$
    ///         \li \f$[lower,upper]\f$<sub>\link p1788::decoration::decoration dac\endlink</sub> if \p \f$ lower \leq upper \wedge (lower = -\infty \vee upper = +\infty) \f$
    ///         \li NaI otherwise
    ///
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::nums_to_decorated_interval(T lower, T upper)</c>
    /// which creates the representation for a decorated interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::nums_to_decorated_interval(T lower , T upper) \endlink
    ///
    inline
    decorated_interval(T lower, T upper)
        : base_interval_type(Flavor<T>::nums_to_decorated_interval(lower, upper))
    { }

    /// \brief (Mixed type version) Creates a decorated interval with a lower and an upper bound
    ///
    /// \param lower lower bound
    /// \param upper upper bound
    ///
    /// \return \li \f$[lower,upper]\f$<sub>\link p1788::decoration::decoration com\endlink</sub> if \p \f$ lower \leq upper \wedge lower \not= \pm\infty \wedge upper \not= \pm\infty \f$
    ///         \li \f$[lower,upper]\f$<sub>\link p1788::decoration::decoration dac\endlink</sub> if \p \f$ lower \leq upper \wedge (lower = -\infty \vee upper = +\infty) \f$
    ///         \li NaI otherwise
    ///
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::nums_to_decorated_interval(L lower, U upper)</c>
    /// which creates the representation for a decorated interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::nums_to_decorated_interval(L_ lower , U_ upper) \endlink
    ///
    template<typename L, typename U>
    inline
    decorated_interval(L lower, U upper)
        : base_interval_type(Flavor<T>::nums_to_decorated_interval(lower, upper))
    { }


    /// \brief Creates a decorated interval with a lower and an upper bound and a specified decoration
    ///
    /// \param lower lower bound
    /// \param upper upper bound
    /// \param dec Decoration
    ///
    /// \return \li Decorated interval combined out of \p other, \p upper and \p dec if the combination is valid
    ///         \li NaI otherwise
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::nums_dec_to_decorated_interval(T lower, T upper, p1788::decoration::decoration dec)</c>
    /// which creates the representation for a decorated interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::nums_dec_to_decorated_interval(T lower, T upper, p1788::decoration::decoration dec) \endlink
    ///
    inline
    decorated_interval(T lower, T upper, p1788::decoration::decoration dec)
        : base_interval_type(Flavor<T>::nums_dec_to_decorated_interval(lower, upper, dec))
    { }

    /// \brief (Mixed type version) Creates a decorated interval with a lower and an upper bound and a specified decoration
    ///
    /// \param lower lower bound
    /// \param upper upper bound
    /// \param dec Decoration
    ///
    /// \return \li Decorated interval combined out of \p other, \p upper and \p dec if the combination is valid
    ///         \li NaI otherwise
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::nums_dec_to_decorated_interval(L lower, U upper, p1788::decoration::decoration dec)</c>
    /// which creates the representation for a decorated interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::nums_dec_to_decorated_interval(L_ lower, U_ upper, p1788::decoration::decoration dec) \endlink
    ///
    template<typename L, typename U>
    inline
    decorated_interval(L lower, U upper, p1788::decoration::decoration dec)
        : base_interval_type(Flavor<T>::nums_dec_to_decorated_interval(lower, upper, dec))
    { }


    /// \brief Creates a decorated interval out of an interval literal
    ///
    /// \param str interval literal
    ///
    /// \return \li decorated interval enclosing the provided interval literal if it is a valid inf-sup form or uncertain form literal
    ///         \li NaI otherwise
    ///
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::text_to_decorated_interval(std::string const& str)</c>
    /// which creates the representation for a decorated interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::text_to_decorated_interval(std::string const& str) \endlink
    ///
    inline explicit
    decorated_interval(std::string const& str)
        : base_interval_type(Flavor<T>::text_to_decorated_interval(str))
    { }

    /// \brief Copy constructor
    ///
    /// \param other Decorated interval to be copied
    ///
    /// \return Copy of \p other
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::copy(representation_dec const& other)</c>
    /// which creates the representation for a decorated interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::copy(representation_dec const& other) \endlink
    ///
    inline
    decorated_interval(decorated_interval<T, Flavor> const& other)
        : base_interval_type(Flavor<T>::copy(other.rep_))
    { }

    /// \brief Convert constructor
    ///
    /// \param other Decorated interval to be converted
    ///
    /// \return Hull of \p other
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::convert_type(representation_dec_type<T_> const& other)</c>
    /// which creates the representation for a decorated interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::convert_type(representation_dec_type<T_> const& other) \endlink
    ///
    template<typename T_>
    inline explicit
    decorated_interval(decorated_interval<T_, Flavor> const& other)
        : base_interval_type(Flavor<T>::convert_type(other.rep_))
    { }

    /// \brief Decorated interval out of a bare interval constructor
    ///
    /// \param other Bare interval to be converted
    ///
    /// \return \li \p other <sub> \link p1788::decoration::decoration com \endlink </sub> if \p other is finite
    ///         \li \p other <sub> \link p1788::decoration::decoration dac \endlink </sub> if \p other is infinite
    ///         \li \p other <sub> \link p1788::decoration::decoration trv \endlink </sub> if \p other is empty
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::new_dec(representation const& other)</c>
    /// which creates the representation for a decorated interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::new_dec(representation const& other) \endlink
    ///
    inline
    decorated_interval(interval<T, Flavor> const& other)
        : base_interval_type(Flavor<T>::new_dec(other.rep_))
    { }

    /// \brief Decorated interval out of a converted bare interval constructor
    ///
    /// \param other Bare interval to be converted
    ///
    /// \return Hull of
    ///         \li \p other <sub> \link p1788::decoration::decoration com \endlink </sub> if hull of \p other is finite
    ///         \li \p other <sub> \link p1788::decoration::decoration dac \endlink </sub> if hull \p other is infinite
    ///         \li \p other <sub> \link p1788::decoration::decoration trv \endlink </sub> if hull \p other is empty
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::new_dec(representation_type<T_> const& other)</c>
    /// which creates the representation for a decorated interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::new_dec(representation_type<T_> const& other) \endlink
    ///
    template<typename T_>
    inline explicit
    decorated_interval(interval<T_, Flavor> const& other)
        : base_interval_type(Flavor<T>::new_dec(other.rep_))
    { }

    /// \brief Decorated interval out of a bare interval and a decoration constructor
    ///
    /// \param other Bare interval to be converted
    /// \param dec Decoration
    ///
    /// \return \li Decorated interval combined out of \p other and \p dec if the combination is valid
    ///         \li NaI otherwise
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::set_dec(representation const& other, p1788::decoration::decoration dec)</c>
    /// which creates the representation for a decorated interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::set_dec(representation const& other, p1788::decoration::decoration dec) \endlink
    ///
    inline
    decorated_interval(interval<T, Flavor> const& other, p1788::decoration::decoration dec)
        : base_interval_type(Flavor<T>::set_dec(other.rep_, dec))
    { }

    /// \brief Decorated interval out of a converted bare interval and a decoration constructor
    ///
    /// \param other Bare interval to be converted
    /// \param dec Decoration
    ///
    /// \return \li Decorated interval combined out of hull of \p other and \p dec if the combination is valid
    ///         \li NaI otherwise
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::set_dec(representation_type<T_> const& other, p1788::decoration::decoration dec)</c>
    /// which creates the representation for a decorated interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::set_dec(representation_type<T_> const& other, p1788::decoration::decoration dec) \endlink
    ///
    template<typename T_>
    inline explicit
    decorated_interval(interval<T_, Flavor> const& other, p1788::decoration::decoration dec)
        : base_interval_type(Flavor<T>::set_dec(other.rep_, dec))
    { }

///@}

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
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::empty_dec() \endlink
    ///
    inline
    static decorated_interval empty()
    {
        return decorated_interval(Flavor<T>::empty_dec());
    }

    /// \brief Returns an entire decorated interval
    ///
    /// \return \f$[-\infty,+\infty]\f$<sub>\link p1788::decoration::decoration dac\endlink</sub>
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::entire_dec()</c>
    /// which creates the representation for an entire decorated interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::entire_dec() \endlink
    ///
    inline
    static decorated_interval entire()
    {
        return decorated_interval(Flavor<T>::entire_dec());
    }

    /// \brief Returns an ill-formed decorated interval (Not an Interval)
    ///
    /// \return  NaI (= \f$\emptyset\f$<sub>\link p1788::decoration::decoration ill\endlink</sub>)
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::nai()</c>
    /// which creates the representation for an ill-formed decorated interval (NaI).
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::nai() \endlink
    ///
    inline
    static decorated_interval nai()
    {
        return decorated_interval(Flavor<T>::nai());
    }

///@}



// -----------------------------------------------------------------------------
// Decorated interval specific methods
// -----------------------------------------------------------------------------

///@name Decorated interval specific functions
///
///
///@{

    /// \brief Checks if the interval is NaI
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::is_nai(representation_dec const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param x decorated interval
    ///
    /// \retval true    \p x is NaI
    /// \retval false   otherwise
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::is_nai(representation_dec const& x) mpfr_bin_ieee754_flavor::is_nai(representation_dec const& x) \endlink</c>
    ///
    inline
    static bool is_nai(decorated_interval<T,Flavor> const& x)
    {
        return Flavor<T>::is_nai(x.rep_);
    }


    /// \brief Returns the decoration of an decorated interval
    ///
    /// The computation is delegated to the static function
    /// <c>Flavor<T>::decoration(representation_dec const& x)</c>
    /// of the policy class <c>Flavor<T></c> by passing only the internal
    /// representation of the interval.
    ///
    /// \param x decorated interval
    ///
    /// \return decoration of \p x
    ///
    /// \see <c>\link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor::decoration_part(representation_dec const& x) mpfr_bin_ieee754_flavor::decoration_part(representation_dec const& x) \endlink</c>
    ///
    inline
    static p1788::decoration::decoration decoration(decorated_interval<T,Flavor> const& x)
    {
        return Flavor<T>::decoration_part(x.rep_);
    }

///@}

private:

    // private constructor which is used by the base_interval to create concrete decorated intervals
    inline explicit
    decorated_interval(typename Flavor<T>::representation_dec rep)
        : base_interval_type(rep)
    {}

    friend class base_interval<T, Flavor, typename Flavor<T>::representation_dec, decorated_interval<T, Flavor>>;

    template<typename, template<typename> class>
    friend class interval;


}; // class decorated_interval




///@name Decorated interval specific functions
///
///
///@{


/// \brief Checks if the interval is NaI
///
/// The computation is delegated to the static function
/// \link decorated_interval<T,Flavor>::is_nai(decorated_interval<T, Flavor> const& x) \endlink.
///
/// \param x decorated interval
///
/// \retval true    \p x is NaI
/// \retval false   otherwise
template<typename T, template<typename> class Flavor>
inline
bool is_nai(decorated_interval<T, Flavor> const& x)
{
    return decorated_interval<T, Flavor>::is_nai(x);
}

/// \brief Returns the decoration of an decorated interval
///
/// The computation is delegated to the static function
/// \link decorated_interval<T,Flavor>::decoration(decorated_interval<T, Flavor> const& x) \endlink.
///
/// \param x decorated interval
///
/// \return decoration of \p x
template<typename T, template<typename> class Flavor>
inline
p1788::decoration::decoration decoration(decorated_interval<T, Flavor> const& x)
{
    return decorated_interval<T, Flavor>::decoration(x);
}

///@}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_HPP
