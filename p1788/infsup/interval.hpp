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
//                       Definition of class interval
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


namespace p1788
{

namespace infsup
{


/// \brief Interval class
///
/// Front end of an inf-sup (bare) interval.
/// All the behavior of the interval type is specified by the
/// template policy class <c>Flavor</c>.
///
/// \tparam T type used for the interval bounds
/// \tparam Flavor template policy class specifying the behavior
///
template<typename T, template<typename> class Flavor>
class interval final
    : public base_interval<T, Flavor, typename Flavor<T>::representation, interval<T, Flavor>>
{
private:

    // base interval type
    typedef base_interval<T, Flavor, typename Flavor<T>::representation, interval<T, Flavor>> base_interval_type;


public:


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

///@name Constructors
///
///
///@{

    /// \brief Creates an empty interval
    ///
    /// \return \f$\emptyset\f$
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::constructor()</c>
    /// which creates the representation for an empty interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::constructor() \endlink
    ///
    inline
    interval()
        : base_interval_type(Flavor<T>::constructor())
    { }

    /// \brief Creates an interval with a lower and an upper bound
    ///
    /// \param lower lower bound
    /// \param upper upper bound
    ///
    /// \return \li \f$[lower,upper]\f$ if \p \f$ lower \leq upper \wedge lower < +\infty \wedge upper > -\infty \f$
    ///         \li \f$\emptyset\f$ otherwise
    ///
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::constructor(T lower, T upper)</c>
    /// which creates the representation for an interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::constructor(T lower , T upper) \endlink
    ///
    inline
    interval(T lower, T upper)
        : base_interval_type(Flavor<T>::constructor(lower, upper))
    { }

    /// \brief (Mixed type version) Creates an interval with a lower and an upper bound
    ///
    /// \param lower lower bound
    /// \param upper upper bound
    ///
    /// \return \li \f$[lower,upper]\f$ if \p \f$ lower \leq upper \wedge lower < +\infty \wedge upper > -\infty \f$
    ///         \li \f$\emptyset\f$ otherwise
    ///
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::constructor(L lower, U upper)</c>
    /// which creates the representation for an interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::constructor(L_ lower , U_ upper) \endlink
    ///
    template<typename L, typename U>
    inline
    interval(L lower, U upper)
        : base_interval_type(Flavor<T>::constructor(lower, upper))
    { }

    /// \brief Creates an interval out of an interval literal
    ///
    /// \param str interval literal
    ///
    /// \return \li interval enclosing the provided interval literal if it is a valid inf-sup form or uncertain form literal
    ///         \li \f$\emptyset\f$ otherwise
    ///
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::constructor(std::string const& str)</c>
    /// which creates the representation for an interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::constructor(std::string const& str) \endlink
    ///
    inline explicit
    interval(std::string const& str)
        : base_interval_type(Flavor<T>::constructor(str))
    { }


    /// \brief Copy constructor
    ///
    /// \param other Interval to be copied
    ///
    /// \return Copy of \p other
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::constructor(representation const& other)</c>
    /// which creates the representation for an interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::constructor(representation const& other) \endlink
    ///
    inline
    interval(interval<T, Flavor> const& other)
        : base_interval_type(Flavor<T>::constructor(other.rep_))
    { }

    /// \brief Convert constructor
    ///
    /// \param other Interval to be converted
    ///
    /// \return Hull of \p other
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::constructor(representation_type<T_> const& other)</c>
    /// which creates the representation for an interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::constructor(representation_type<T_> const& other) \endlink
    ///
    template<typename T_>
    inline explicit
    interval(interval<T_, Flavor> const& other)
        : base_interval_type(Flavor<T>::constructor(other.rep_))
    { }

    /// \brief Interval part constructor
    ///
    /// \param other Decorated interval to be converted
    ///
    /// \return Bare interval of \p other
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::constructor(representation_dec const& other)</c>
    /// which creates the representation for an interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::constructor(representation_dec const& other) \endlink
    ///
    inline
    interval(decorated_interval<T, Flavor> const& other)  //< Copy-constructor
        : base_interval_type(Flavor<T>::constructor(other.rep_))
    { }

    /// \brief Interval part and convert constructor
    ///
    /// \param other Decorated interval to be converted
    ///
    /// \return Hull of bare interval of \p other
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::constructor(representation_dec_type<T_> const& other)</c>
    /// which creates the representation for an interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::constructor(representation_dec_type<T_> const& other) \endlink
    ///
    template<typename T_>
    inline explicit
    interval(decorated_interval<T_, Flavor> const& other)
        : base_interval_type(Flavor<T>::constructor(other.rep_))
    { }

///@}

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
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::empty() \endlink
    ///
    inline
    static interval empty()
    {
        return interval(Flavor<T>::empty());
    }

    /// \brief Returns an entire interval
    ///
    /// \return \f$[-\infty,+\infty]\f$
    ///
    /// \note The function is forwarded to the function <c>Flavor\<T\>::entire()</c>
    /// which creates the representation for an entire interval.
    /// \see \link p1788::flavor::infsup::setbased::mpfr_bin_ieee754_flavor<T>::entire() \endlink
    ///
    inline
    static interval entire()
    {
        return interval(Flavor<T>::entire());
    }

///@}


private:

    // private constructor which is used by the base_interval to create concrete intervals
    inline
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
