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

#include <initializer_list>
#include <utility>
#include <string>
#include <istream>
#include <ostream>
#include <vector>
#include <algorithm>

#include "p1788/overlapping/overlapping.hpp"
#include "p1788/util/mixed_type_traits.hpp"
#include "p1788/util/variadic_templates.hpp"


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                        Forward declaration
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


/// \brief Namespace for all IEEE P1788 interval types
///
namespace p1788
{

/// \brief Namespace for all IEEE P1788 infsup interval types
///
namespace infsup
{


//TODO hull, see P1788/D7.0 Sect. 9.3

//TODO Mixed-type with different Flavors?


// Forward declaration
template<typename T, template<typename> class Flavor> class interval;


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
// Trait is_infsup_interval
//------------------------------------------------------------------------------

// Ignore the warning about non-virtual destructors
// on GCC  push the last diagnostic state and disable -Weffc++
//TODO support other compiler
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"


/// \brief Trait to check if type T is an p1788::infsup::interval
///
/// \param T type
/// \return field value contains boolean result of the check
///
///
template<typename T>
class is_infsup_interval
    : public std::integral_constant<bool, false>
{ };

template<typename T, template<typename> class Flavor>
class is_infsup_interval<p1788::infsup::interval<T,Flavor>>
            : public std::integral_constant<bool, true>
{ };

// on GCC  enable the diagnostic state -Weffc++ again
#pragma GCC diagnostic pop


//------------------------------------------------------------------------------
// Trait infsup_max_precision_type
//------------------------------------------------------------------------------

template<typename... Types> class infsup_max_precision_type
{
    static_assert(sizeof...(Types) > 0,
                  "infsup_max_precision_type for an empty argument list!");
};

template<typename First, typename Second, typename... Tail>
class infsup_max_precision_type<First, Second, Tail...>
{
public:
    static_assert(is_infsup_interval<First>::value, "Type is not supported!");
    static_assert(is_infsup_interval<Second>::value, "Type is not supported!");

    static_assert(
        std::is_same<
        typename type_precision_order<typename First::bound_type>::value_type,
        typename type_precision_order<typename Second::bound_type>::value_type
        >::value,
        "Different type groups!");

    typedef typename infsup_max_precision_type<
    typename std::conditional<
    (type_precision_order<typename First::bound_type>::value >
     type_precision_order<typename Second::bound_type>::value),
                          First,
                          Second
                          >::type,
                          Tail...
                          >::type type;
};

template<typename Type>
class infsup_max_precision_type<Type>
{
public:
    typedef Type type;
};



} // namespace util

} // namespace p1788







//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//                       Definition of class interval
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------




namespace p1788
{

namespace infsup
{



/// \brief Level 2 (bare) infsup interval
///
///
/// Class representing a level 2 (bare) infsup interval, see P1788/D7.0 Sect. 4.1.
///
/// This class only serves as a uniform interface/representation of an (bare)
/// interval. All the behavior will be specified by the template policy class
/// Flavor which implements the flavors concept of the standard in coherent way,
/// see P1788/D7.0 Sect. 5.
///
/// \param T                  Number system /parent format
/// \param Flavor<typename>   Generic flavor which will be instantiated with the
///                           number system T
///
template<typename T, template<typename> class Flavor>
class interval final
{

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// public
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


public:

    typedef T bound_type;

    // TODO type alias ?
    //template<typename TT> using flavor_type = Flavor<TT>;
    typedef Flavor<T> flavor_type;


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

// TODO Constructor specification

    interval()
        : rep_(Flavor<T>::constructor_infsup())
    { }

    interval(T lower, T upper)
        : rep_(Flavor<T>::constructor_infsup(lower, upper))
    { }

    explicit interval(T point)
        : rep_(Flavor<T>::constructor_infsup(point))
    { }

    explicit interval(std::initializer_list<T> points)
        : rep_(Flavor<T>::constructor_infsup(points.begin(), points.end()))
    { }

    explicit interval(std::string const& str)
        : rep_(Flavor<T>::constructor_infsup(str))
    { }

    interval(interval<T, Flavor> const& other)  ///< Copy-constructor
        : rep_(Flavor<T>::constructor_infsup(other.rep_))
    { }

    template<typename TT>
    explicit interval(interval<TT, Flavor> const& other)  ///< Copy-constructor
        : rep_(Flavor<T>::constructor_infsup(other.rep_))
    { }



// TODO public representation,




// -----------------------------------------------------------------------------
// Methods
// -----------------------------------------------------------------------------


// Implementation specific
    T lower() const {
        return Flavor<T>::method_lower(rep_);
    }

// Implementation specific
    T upper() const {
        return Flavor<T>::method_upper(rep_);
    }

// Implementation specific
    T mid() const {
        return Flavor<T>::method_mid(rep_);
    }

// Implementation specific
    T rad() const {
        return Flavor<T>::method_rad(rep_);
    }


// -----------------------------------------------------------------------------
// Static methods
// -----------------------------------------------------------------------------

// Required, Creates an empty interval, see P1788/D7.0 Sect. 9.6.2

    static interval<T, Flavor> empty() {
        return interval<T, Flavor>(Flavor<T>::static_method_empty());
    }

// Required, Creates an entire interval, see P1788/D7.0 Sect. 9.6.2
    static interval<T, Flavor> entire() {
        return interval<T, Flavor>(Flavor<T>::static_method_entire());
    }




// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// private
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

private:


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

    interval(typename Flavor<T>::representation const& rep)
        : rep_(rep)
    { }


// -----------------------------------------------------------------------------
// Members
// -----------------------------------------------------------------------------

    typename Flavor<T>::representation rep_;








//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Friends
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


    template<typename, template<typename> class>
    friend class p1788::infsup::interval;



// -----------------------------------------------------------------------------
// IO operators
// -----------------------------------------------------------------------------


    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(
        std::basic_ostream<CharT, Traits>& os,
        interval<T, Flavor> const& x) {
        return Flavor<T>::operator_output(os, x.rep_);
    }

    template<typename CharT, typename Traits>
    friend std::basic_istream<CharT, Traits>& operator>>(
        std::basic_istream<CharT, Traits>& is,
        interval<T, Flavor>& x ) {
        return Flavor<T>::operator_input(is, x.rep_);
    }



// -----------------------------------------------------------------------------
// Forward elementary functions
// -----------------------------------------------------------------------------


// pos

    friend interval<T, Flavor> pos(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::pos(x.rep_));
    }

    template<typename Interval>
    friend Interval pos(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(pos(static_cast<interval<Tmax, Flavor>>(x)));
    }

    friend interval<T, Flavor> operator+(interval<T, Flavor> const& x) {
        return pos(x);
    }


// neg

    friend interval<T, Flavor> neg(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::neg(x.rep_));
    }

    template<typename Interval>
    friend Interval neg(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(neg(static_cast<interval<Tmax, Flavor>>(x)));
    }

    friend interval<T, Flavor> operator-(interval<T, Flavor> const& x) {
        return neg(x);
    }


// add

    friend interval<T, Flavor> add (interval<T, Flavor> const& x,
                                    interval<T, Flavor> const& y) {
        return interval<T, Flavor>(Flavor<T>::add(x.rep_, y.rep_));
    }

    template<typename Interval, typename Ty>
    friend Interval add(interval<T, Flavor> const& x,
                        interval<Ty, Flavor> const& y) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T,
                 Ty
                 >::type Tmax;

        return Interval(add(static_cast<interval<Tmax, Flavor>>(x),
                            static_cast<interval<Tmax, Flavor>>(y)));
    }

    friend interval<T, Flavor> operator+(interval<T, Flavor> const& x,
                                         interval<T, Flavor> const& y) {
        return add(x, y);
    }


// sub

    friend interval<T, Flavor> sub(interval<T, Flavor> const& x,
                                   interval<T, Flavor> const& y) {
        return interval<T, Flavor>(Flavor<T>::sub(x.rep_, y.rep_));
    }

    template<typename Interval, typename Ty>
    friend Interval sub(interval<T, Flavor> const& x,
                        interval<Ty, Flavor> const& y) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T,
                 Ty
                 >::type Tmax;

        return Interval(sub(static_cast<interval<Tmax, Flavor>>(x),
                            static_cast<interval<Tmax, Flavor>>(y)));
    }

    friend interval<T, Flavor> operator-(interval<T, Flavor> const& x,
                                         interval<T, Flavor> const& y) {
        return sub(x, y);
    }


// mul

    friend interval<T, Flavor> mul(interval<T, Flavor> const& x,
                                   interval<T, Flavor> const& y) {
        return interval<T, Flavor>(Flavor<T>::mul(x.rep_, y.rep_));
    }

    template<typename Interval, typename Ty>
    friend Interval mul(interval<T, Flavor> const& x,
                        interval<Ty, Flavor> const& y) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T,
                 Ty
                 >::type Tmax;

        return Interval(mul(static_cast<interval<Tmax, Flavor>>(x),
                            static_cast<interval<Tmax, Flavor>>(y)));
    }

    friend interval<T, Flavor> operator*(interval<T, Flavor> const& x,
                                         interval<T, Flavor> const& y) {
        return mul(x, y);
    }


// div

    friend interval<T, Flavor> div(interval<T, Flavor> const& x,
                                   interval<T, Flavor> const& y) {
        return interval<T, Flavor>(Flavor<T>::div(x.rep_, y.rep_));
    }

    template<typename Interval, typename Ty>
    friend Interval div(interval<T, Flavor> const& x,
                        interval<Ty, Flavor> const& y) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T,
                 Ty
                 >::type Tmax;

        return Interval(div(static_cast<interval<Tmax, Flavor>>(x),
                            static_cast<interval<Tmax, Flavor>>(y)));
    }

    friend interval<T, Flavor> operator/(interval<T, Flavor> const& x,
                                         interval<T, Flavor> const& y) {
        return div(x, y);
    }


// inv

    friend interval<T, Flavor> inv(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::inv(x.rep_));
    }

    template<typename Interval>
    friend Interval inv(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(inv(static_cast<interval<Tmax, Flavor>>(x)));
    }


// sqrt

    friend interval<T, Flavor> sqrt(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::sqrt(x.rep_));
    }

    template<typename Interval>
    friend Interval sqrt(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(sqrt(static_cast<interval<Tmax, Flavor>>(x)));
    }


// fma

    friend interval<T, Flavor> fma(interval<T, Flavor> const& x,
                                   interval<T, Flavor> const& y,
                                   interval<T, Flavor> const& z) {
        return interval<T, Flavor>(Flavor<T>::fma(x.rep_, y.rep_, z.rep_));
    }

    template<typename Interval, typename Ty, typename Tz>
    friend Interval fma(interval<T, Flavor> const& x,
                        interval<Ty, Flavor> const& y,
                        interval<Tz, Flavor> const& z) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T,
                 Ty,
                 Tz
                 >::type Tmax;

        return Interval(fma(static_cast<interval<Tmax, Flavor>>(x),
                            static_cast<interval<Tmax, Flavor>>(y),
                            static_cast<interval<Tmax, Flavor>>(z)));
    }


// interval case

    friend interval<T, Flavor> interval_case(interval<T, Flavor> const& c,
            interval<T, Flavor> const& g,
            interval<T, Flavor> const& h) {
        return interval<T, Flavor>(Flavor<T>::interval_case(c.rep_,
                                   g.rep_, h.rep_));
    }

    template<typename Interval, typename Tg, typename Th>
    friend Interval interval_case(interval<T, Flavor> const& c,
                                  interval<Tg, Flavor> const& g,
                                  interval<Th, Flavor> const& h) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T,
                 Tg,
                 Th
                 >::type Tmax;

        return Interval(interval_case(static_cast<interval<Tmax, Flavor>>(c),
                                      static_cast<interval<Tmax, Flavor>>(g),
                                      static_cast<interval<Tmax, Flavor>>(h)));
    }


// sqr

    friend interval<T, Flavor> sqr(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::sqr(x.rep_));
    }

    template<typename Interval>
    friend Interval sqr(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(sqr(static_cast<interval<Tmax, Flavor>>(x)));
    }


// pown

    friend interval<T, Flavor> pown(interval<T, Flavor> const& x,
                                    int p) {
        return interval<T, Flavor>(Flavor<T>::pown(x.rep_, p));
    }

    template<typename Interval>
    friend Interval pown(interval<T, Flavor> const& x,
                         int p) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(pown(static_cast<interval<Tmax, Flavor>>(x), p));
    }


// pow

    friend interval<T, Flavor> pow(interval<T, Flavor> const& x,
                                   interval<T, Flavor> const& y) {
        return interval<T, Flavor>(Flavor<T>::pow(x.rep_, y.rep_));
    }

    template<typename Interval, typename Ty>
    friend Interval pow(interval<T, Flavor> const& x,
                        interval<Ty, Flavor> const& y) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T,
                 Ty
                 >::type Tmax;

        return Interval(pow(static_cast<interval<Tmax, Flavor>>(x),
                            static_cast<interval<Tmax, Flavor>>(y)));
    }


// exp

    friend interval<T, Flavor> exp(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::exp(x.rep_));
    }

    template<typename Interval>
    friend Interval exp(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(exp(static_cast<interval<Tmax, Flavor>>(x)));
    }


// exp2

    friend interval<T, Flavor> exp2(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::exp2(x.rep_));
    }

    template<typename Interval>
    friend Interval exp2(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(exp2(static_cast<interval<Tmax, Flavor>>(x)));
    }


// exp10

    friend interval<T, Flavor> exp10(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::exp10(x.rep_));
    }

    template<typename Interval>
    friend Interval exp10(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(exp10(static_cast<interval<Tmax, Flavor>>(x)));
    }


// log

    friend interval<T, Flavor> log(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::log(x.rep_));
    }

    template<typename Interval>
    friend Interval log(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(log(static_cast<interval<Tmax, Flavor>>(x)));
    }


// log2

    friend interval<T, Flavor> log2(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::log2(x.rep_));
    }

    template<typename Interval>
    friend Interval log2(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(log2(static_cast<interval<Tmax, Flavor>>(x)));
    }


// log10

    friend interval<T, Flavor> log10(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::log10(x.rep_));
    }

    template<typename Interval>
    friend Interval log10(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(log10(static_cast<interval<Tmax, Flavor>>(x)));
    }


// sin

    friend interval<T, Flavor> sin(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::sin(x.rep_));
    }

    template<typename Interval>
    friend Interval sin(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(sin(static_cast<interval<Tmax, Flavor>>(x)));
    }


// cos

    friend interval<T, Flavor> cos(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::cos(x.rep_));
    }

    template<typename Interval>
    friend Interval cos(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(cos(static_cast<interval<Tmax, Flavor>>(x)));
    }


// tan

    friend interval<T, Flavor> tan(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::tan(x.rep_));
    }

    template<typename Interval>
    friend Interval tan(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(tan(static_cast<interval<Tmax, Flavor>>(x)));
    }


// asin

    friend interval<T, Flavor> asin(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::asin(x.rep_));
    }

    template<typename Interval>
    friend Interval asin(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(asin(static_cast<interval<Tmax, Flavor>>(x)));
    }

// acos

    friend interval<T, Flavor> acos( interval<T, Flavor> const& x ) {
        return interval<T, Flavor>(Flavor<T>::acos(x.rep_));
    }

    template<typename Interval>
    friend Interval acos(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(acos(static_cast<interval<Tmax, Flavor>>(x)));
    }


// atan

    friend interval<T, Flavor> atan(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::atan(x.rep_));
    }

    template<typename Interval>
    friend Interval atan(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(atan(static_cast<interval<Tmax, Flavor>>(x)));
    }

// atan2

    friend interval<T, Flavor> atan2(interval<T, Flavor> const& y,
                                     interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::atan2(y.rep_, x.rep_));
    }

    template<typename Interval, typename Tx>
    friend Interval atan2(interval<T, Flavor> const& y,
                          interval<Tx, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T,
                 Tx
                 >::type Tmax;

        return Interval(atan2(static_cast<interval<Tmax, Flavor>>(y),
                              static_cast<interval<Tmax, Flavor>>(x)));
    }


// sinh

    friend interval<T, Flavor> sinh(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::sinh(x.rep_));
    }

    template<typename Interval>
    friend Interval sinh(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(sinh(static_cast<interval<Tmax, Flavor>>(x)));
    }


// cosh

    friend interval<T, Flavor> cosh(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::cosh(x.rep_));
    }

    template<typename Interval>
    friend Interval cosh(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(cosh(static_cast<interval<Tmax, Flavor>>(x)));
    }


// tanh

    friend interval<T, Flavor> tanh(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::tanh(x.rep_));
    }

    template<typename Interval>
    friend Interval tanh(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(tanh(static_cast<interval<Tmax, Flavor>>(x)));
    }


// asinh

    friend interval<T, Flavor> asinh(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::asinh(x.rep_));
    }

    template<typename Interval>
    friend Interval asinh(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(asinh(static_cast<interval<Tmax, Flavor>>(x)));
    }


// acosh

    friend interval<T, Flavor> acosh(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::acosh(x.rep_));
    }

    template<typename Interval>
    friend Interval acosh(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(acosh(static_cast<interval<Tmax, Flavor>>(x)));
    }


// atanh

    friend interval<T, Flavor> atanh(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::atanh(x.rep_));
    }

    template<typename Interval>
    friend Interval atanh(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(atanh(static_cast<interval<Tmax, Flavor>>(x)));
    }


// sign

    friend interval<T, Flavor> sign(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::sign(x.rep_));
    }

    template<typename Interval>
    friend Interval sign(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(sign(static_cast<interval<Tmax, Flavor>>(x)));
    }


// ceil

    friend interval<T, Flavor> ceil(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::ceil(x.rep_));
    }

    template<typename Interval>
    friend Interval ceil(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(ceil(static_cast<interval<Tmax, Flavor>>(x)));
    }


// floor

    friend interval<T, Flavor> floor(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::floor(x.rep_));
    }

    template<typename Interval>
    friend Interval floor(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(floor(static_cast<interval<Tmax, Flavor>>(x)));
    }


// trunc

    friend interval<T, Flavor> trunc(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::trunc(x.rep_));
    }

    template<typename Interval>
    friend Interval trunc(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(trunc(static_cast<interval<Tmax, Flavor>>(x)));
    }


// round_ties_to_even

    friend interval<T, Flavor> round_ties_to_even(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::round_ties_to_even(x.rep_));
    }

    template<typename Interval>
    friend Interval round_ties_to_even(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(
                   round_ties_to_even(static_cast<interval<Tmax, Flavor>>(x)));
    }


// round_ties_to_away

    friend interval<T, Flavor> round_ties_to_away(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::round_ties_to_away(x.rep_));
    }

    template<typename Interval>
    friend Interval round_ties_to_away(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(
                   round_ties_to_away(static_cast<interval<Tmax, Flavor>>(x)));
    }


// abs

    friend interval<T, Flavor> abs(interval<T, Flavor> const& x) {
        return interval<T, Flavor>(Flavor<T>::abs(x.rep_));
    }

    template<typename Interval>
    friend Interval abs(interval<T, Flavor> const& x) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T
                 >::type Tmax;

        return Interval(abs(static_cast<interval<Tmax, Flavor>>(x)));
    }


// min

    template<typename... Intervals>
    friend interval<T, Flavor> min(interval<T, Flavor> const& x,
                                   Intervals const& ... intervals) {
        std::vector<typename Flavor<T>::representation> v;

        p1788::util::for_each<interval<T, Flavor>,
              Intervals...>::apply(
        [&v] (interval<T, Flavor> const & a) {
            v.push_back(a.rep_);
        },
        x,
        intervals...
              );

        typename std::vector<
        typename Flavor<T>::representation>::const_iterator first = v.begin();
        typename std::vector<
        typename Flavor<T>::representation>::const_iterator last = v.end();

        return interval<T, Flavor>(Flavor<T>::min(first, last));
    }


    template<typename Interval, typename... Intervals>
    friend Interval min(interval<T, Flavor> const& x,
                        Intervals const& ... intervals) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T,
                 typename p1788::util::infsup_max_precision_type<Intervals...>::
                 type::bound_type>::type Tmax;


        std::vector<interval<Tmax, Flavor>> iv;

        p1788::util::for_each<interval<T, Flavor>,
              Intervals...>::apply(
                  p1788::util::inserter_func<interval<Tmax, Flavor>,
                  decltype(std::back_inserter(iv))>(std::back_inserter(iv)),
                  x,
                  intervals...
              );

        std::vector<typename Flavor<Tmax>::representation> v;

        std::transform(iv.begin(), iv.end(), std::back_inserter(v),
        [] (interval<Tmax, Flavor> const & x) {
            return x.rep_;
        } );

        typename std::vector<
        typename Flavor<Tmax>::representation>::const_iterator first = v.begin();
        typename std::vector<
        typename Flavor<Tmax>::representation>::const_iterator last = v.end();

        return Interval(interval<Tmax, Flavor>(Flavor<Tmax>::min(first, last)));
    }


// max

    template<typename... Intervals>
    friend interval<T, Flavor> max(interval<T, Flavor> const& x,
                                   Intervals const& ... intervals) {
        std::vector<typename Flavor<T>::representation> v;

        p1788::util::for_each<interval<T, Flavor>,
              Intervals...>::apply(
        [&v] (interval<T, Flavor> const & a) {
            v.push_back(a.rep_);
        },
        x,
        intervals...
              );

        typename std::vector<
        typename Flavor<T>::representation>::const_iterator first = v.begin();
        typename std::vector<
        typename Flavor<T>::representation>::const_iterator last = v.end();

        return interval<T, Flavor>(Flavor<T>::max(first, last));
    }


    template<typename Interval, typename... Intervals>
    friend Interval max(interval<T, Flavor> const& x,
                        Intervals const& ... intervals) {
        static_assert(p1788::util::is_infsup_interval<Interval>::value,
                      "Return type is not supported by mixed type operations!");
        static_assert(std::is_same<typename Interval::flavor_type,
                      Flavor<typename Interval::bound_type>>::value,
                      "Different flavors are not supported by "
                      "mixed type operations!");

        typedef typename p1788::util::max_precision_type<
        typename Interval::bound_type,
                 T,
                 typename p1788::util::infsup_max_precision_type<Intervals...>::
                 type::bound_type>::type Tmax;


        std::vector<interval<Tmax, Flavor>> iv;

        p1788::util::for_each<interval<T, Flavor>,
              Intervals...>::apply(
                  p1788::util::inserter_func<interval<Tmax, Flavor>,
                  decltype(std::back_inserter(iv))>(std::back_inserter(iv)),
                  x,
                  intervals...
              );

        std::vector<typename Flavor<Tmax>::representation> v;

        std::transform(iv.begin(), iv.end(), std::back_inserter(v),
        [] (interval<Tmax, Flavor> const & x) {
            return x.rep_;
        } );

        typename std::vector<
        typename Flavor<Tmax>::representation>::const_iterator first = v.begin();
        typename std::vector<
        typename Flavor<Tmax>::representation>::const_iterator last = v.end();

        return Interval(interval<Tmax, Flavor>(Flavor<Tmax>::max(first, last)));
    }

    // -----------------------------------------------------------------------------
    // Reverse elementary functions, see P1788/D7.0 Sect. 9.6.5 Table 2
    // -----------------------------------------------------------------------------

    // reverse version of unary point functions


// sqr_rev

    friend interval<T, Flavor> sqr_rev(interval<T, Flavor> const& c, interval<T, Flavor> const& x) {     ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::sqr_rev(c.rep_, x.rep_));
    }

    template<typename Interval, typename Tx>
    friend Interval sqr_rev(interval<T, Flavor> const& c, interval<Tx, Flavor> const& x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T,
               Tx
               >::type TMax;

      return Interval(sqr_rev(static_cast<interval<TMax, Flavor>>(c),
                              static_cast<interval<TMax, Flavor>>(x)));
    }

    friend interval<T, Flavor> sqr_rev(interval<T, Flavor> const& x) {     ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::sqr_rev(x.rep_));
    }

    template<typename Interval>
    friend Interval sqr_rev(interval<T, Flavor> const & x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T
               >::type TMax;

      return Interval(sqr_rev(static_cast<interval<TMax, Flavor>>(x)));
    }


// inv_rev

    friend interval<T, Flavor> inv_rev(interval<T, Flavor> const& c, interval<T, Flavor> const& x) {     ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::inv_rev(c.rep_, x.rep_));
    }

    template<typename Interval, typename Tx>
    friend Interval inv_rev(interval<T, Flavor> const &c, interval<Tx, Flavor> const &x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T,
               Tx
               >::type TMax;

      return Interval(inv_rev(static_cast<interval<TMax, Flavor>>(c),
                              static_cast<interval<TMax, Flavor>>(x)));
    }

    friend interval<T, Flavor> inv_rev(interval<T, Flavor> const& x) {     ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::inv_rev(x.rep_));
    }

    template<typename Interval>
    friend Interval inv_rev(interval<T, Flavor> const& x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T
               >::type TMax;

      return Interval(inv_rev(static_cast<interval<TMax, Flavor>>(x)));
    }


// abs_rev

    friend interval<T, Flavor> abs_rev(interval<T, Flavor> const& c, interval<T, Flavor> const& x) {     ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::abs_rev(c.rep_, x.rep_));
    }

    template<typename Interval, typename Tx>
    friend Interval abs_rev(interval<T, Flavor> const& c, interval<Tx, Flavor> const& x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T,
               Tx
               >::type TMax;

      return Interval(abs_rev(static_cast<interval<TMax, Flavor>>(c),
                              static_cast<interval<TMax, Flavor>>(x)));
    }

    friend interval<T, Flavor> abs_rev(interval<T, Flavor> const& x) {     ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::abs_rev(x.rep_));
    }

    template<typename Interval>
    friend Interval abs_rev(interval<T, Flavor> const& x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T
               >::type TMax;

      return Interval(abs_rev(static_cast<interval<TMax, Flavor>>(x)));
    }


// pown_rev

    friend interval<T, Flavor> pown_rev(interval<T, Flavor> const& c,
                                        interval<T, Flavor> const& x, int n) {   ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::pown_rev(c.rep_, x.rep_, n));
    }

    template<typename Interval, typename Tx>
    friend Interval pown_rev(interval<T, Flavor> const& c,
                             interval<Tx, Flavor> const& x, int n) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T,
               Tx
               >::type TMax;

      return Interval(pown_rev(static_cast<interval<TMax, Flavor>>(c),
                               static_cast<interval<TMax, Flavor>>(x),
                               n));
    }

    friend interval<T, Flavor> pown_rev(interval<T, Flavor> const& x, int n) {   ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::pown_rev(x.rep_, n));
    }

    template<typename Interval>
    friend Interval pown_rev(interval<T, Flavor> const& x, int n) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T
               >::type TMax;

      return Interval(pown_rev(static_cast<interval<TMax, Flavor>>(x), n));
    }


// sin_rev

    friend interval<T, Flavor> sin_rev(interval<T, Flavor> const& c, interval<T, Flavor> const& x) {     ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::sin_rev(c.rep_, x.rep_));
    }

    template<typename Interval, typename Tx>
    friend Interval sin_rev(interval<T, Flavor> const& c, interval<Tx, Flavor> const& x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T,
               Tx
               >::type TMax;

      return Interval(sin_rev(static_cast<interval<TMax, Flavor>>(c),
                              static_cast<interval<TMax, Flavor>>(x)));
    }

    friend interval<T, Flavor> sin_rev(interval<T, Flavor> const& x) {     ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::sin_rev(x.rep_));
    }

    template<typename Interval>
    friend Interval sin_rev(interval<T, Flavor> const& x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T
               >::type TMax;

      return Interval(sin_rev(static_cast<interval<TMax, Flavor>>(x)));
    }


// cos_rev

    friend interval<T, Flavor> cos_rev(interval<T, Flavor> const& c, interval<T, Flavor> const& x) {     ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::cos_rev(c.rep_, x.rep_));
    }

    template<typename Interval, typename Tx>
    friend Interval cos_rev(interval<T, Flavor> const& c, interval<Tx, Flavor> const& x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T,
               Tx
               >::type TMax;

      return Interval(cos_rev(static_cast<interval<TMax, Flavor>>(c),
                              static_cast<interval<TMax, Flavor>>(x)));
    }

    friend interval<T, Flavor> cos_rev(interval<T, Flavor> const& x) {     ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::cos_rev(x.rep_));
    }

    template<typename Interval>
    friend Interval cos_rev(interval<T, Flavor> const& x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T
               >::type TMax;

      return Interval(cos_rev(static_cast<interval<TMax, Flavor>>(x)));
    }


// tan_rev

    friend interval<T, Flavor> tan_rev(interval<T, Flavor> const& c,
                                       interval<T, Flavor> const& x) {     ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::tan_rev(c.rep_, x.rep_));
    }

    template<typename Interval, typename Tx>
    friend Interval tan_rev(interval<T, Flavor> const& c,
                                       interval<Tx, Flavor> const& x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T,
               Tx
               >::type TMax;

      return Interval(tan_rev(static_cast<interval<TMax, Flavor>>(c),
                              static_cast<interval<TMax, Flavor>>(x)));
    }

    friend interval<T, Flavor> tan_rev(interval<T, Flavor> const& x) {     ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::tan_rev(x.rep_));
    }

    template<typename Interval>
    friend Interval tan_rev(interval<T, Flavor> const& x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T
               >::type TMax;

      return Interval(tan_rev(static_cast<interval<TMax, Flavor>>(x)));
    }


// cosh_rev

    friend interval<T, Flavor> cosh_rev(interval<T, Flavor> const& c, interval<T, Flavor> const& x) {    ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::cosh_rev(c.rep_, x.rep_));
    }

    template<typename Interval, typename Tx>
    friend Interval cosh_rev(interval<T, Flavor> const &c, interval<Tx, Flavor> const& x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T,
               Tx
               >::type TMax;

      return Interval(cosh_rev(static_cast<interval<TMax, Flavor>>(c),
                               static_cast<interval<TMax, Flavor>>(x)));
    }

    friend interval<T, Flavor> cosh_rev(interval<T, Flavor> const& x) {    ///< Required, accurate
      return interval<T, Flavor>(Flavor<T>::cosh_rev(x.rep_));
    }

    template<typename Interval>
    friend Interval cosh_rev(interval<T, Flavor> const& x) {
      static_assert(p1788::util::is_infsup_interval<Interval>::value,
                    "Return type is not supported by mixed type operations!");
      static_assert(std::is_same<typename Interval::flavor_type,
                    Flavor<typename Interval::bound_type>>::value,
                    "Different flavors are not supported by "
                    "mixed type operations!");

      typedef typename p1788::util::max_precision_type<
      typename Interval::bound_type,
               T
               >::type TMax;

      return Interval(cosh_rev(static_cast<interval<TMax, Flavor>>(x)));
    }


  // reverse versions of binary point functions


// mul_rev

  friend interval<T, Flavor> mul_rev(interval<T, Flavor> const& b,
                                     interval<T, Flavor> const& c,
                                     interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::mul_rev(b.rep_, c.rep_, x.rep_));
  }

  template<typename Interval, typename Tc, typename Tx>
  friend Interval mul_rev(interval<T, Flavor> const& b,
                          interval<Tc, Flavor> const& c,
                          interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tc,
              Tx
              >::type TMax;

    return Interval(mul_rev(static_cast<interval<TMax, Flavor>>(b),
                            static_cast<interval<TMax, Flavor>>(c),
                            static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> mul_rev(interval<T, Flavor> const& c,
                                     interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::mul_rev(c.rep_, x.rep_));
  }

  template<typename Interval, typename Tx>
  friend Interval mul_rev(interval<T, Flavor> const& c,
                          interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tx
              >::type TMax;

    return Interval(mul_rev(static_cast<interval<TMax, Flavor>>(c),
                            static_cast<interval<TMax, Flavor>>(x)));
  }


// div_rev1

  friend interval<T, Flavor> div_rev1(interval<T, Flavor> const& b,
                                      interval<T, Flavor> const& c,
                                      interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::div_rev1(b.rep_, c.rep_, x.rep_));
  }

  template<typename Interval, typename Tc, typename Tx>
  friend Interval div_rev1(interval<T, Flavor> const& b,
                           interval<Tc, Flavor> const& c,
                           interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tc,
              Tx
              >::type TMax;

    return Interval(div_rev1(static_cast<interval<TMax, Flavor>>(b),
                             static_cast<interval<TMax, Flavor>>(c),
                             static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> div_rev1(interval<T, Flavor> const& c,
                                      interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::div_rev1(c.rep_, x.rep_));
  }

  template<typename Interval, typename Tx>
  friend Interval div_rev1(interval<T, Flavor> const& c,
                           interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tx
              >::type TMax;

    return Interval(div_rev1(static_cast<interval<TMax, Flavor>>(c),
                             static_cast<interval<TMax, Flavor>>(x)));
  }


// div_rev2

  friend interval<T, Flavor> div_rev2(interval<T, Flavor> const& a,
                                      interval<T, Flavor> const& c,
                                      interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::div_rev2(a.rep_, c.rep_, x.rep_));
  }

  template<typename Interval, typename Tc, typename Tx>
  friend Interval div_rev2(interval<T, Flavor> const& a,
                           interval<Tc, Flavor> const& c,
                           interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tc,
              Tx
              >::type TMax;

    return Interval(div_rev2(static_cast<interval<TMax, Flavor>>(a),
                             static_cast<interval<TMax, Flavor>>(c),
                             static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> div_rev2(interval<T, Flavor> const& c,
                                      interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::div_rev2(c.rep_, x.rep_));
  }

  template<typename Interval, typename Tx>
  friend Interval div_rev2(interval<T, Flavor> const& c,
                           interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tx
              >::type TMax;

    return Interval(div_rev2(static_cast<interval<TMax, Flavor>>(c),
                             static_cast<interval<TMax, Flavor>>(x)));
  }


// pow_rev1

  friend interval<T, Flavor> pow_rev1(interval<T, Flavor> const& b,
                                      interval<T, Flavor> const& c,
                                      interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::pow_rev1(b.rep_, c.rep_, x.rep_));
  }

  template<typename Interval, typename Tc, typename Tx>
  friend Interval pow_rev1(interval<T, Flavor> const& b,
                           interval<Tc, Flavor> const& c,
                           interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tc,
              Tx
              >::type TMax;

    return Interval(pow_rev1(static_cast<interval<TMax, Flavor>>(b),
                             static_cast<interval<TMax, Flavor>>(c),
                             static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> pow_rev1(interval<T, Flavor> const& c,
                                      interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::pow_rev1(c.rep_, x.rep_));
  }

  template<typename Interval, typename Tx>
  friend Interval pow_rev1(interval<T, Flavor> const& c,
                           interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tx
              >::type TMax;

    return Interval(pow_rev1(static_cast<interval<TMax, Flavor>>(c),
                             static_cast<interval<TMax, Flavor>>(x)));
  }


// pow_rev2

  friend interval<T, Flavor> pow_rev2(interval<T, Flavor> const& a,
                                      interval<T, Flavor> const& c,
                                      interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::pow_rev2(a.rep_, c.rep_, x.rep_));
  }

  template<typename Interval, typename Tc, typename Tx>
  friend Interval pow_rev2(interval<T, Flavor> const& a,
                           interval<Tc, Flavor> const& c,
                           interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tc,
              Tx
              >::type TMax;

    return Interval(pow_rev2(static_cast<interval<TMax, Flavor>>(a),
                             static_cast<interval<TMax, Flavor>>(c),
                             static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> pow_rev2(interval<T, Flavor> const& c,
                                      interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::pow_rev2(c.rep_, x.rep_));
  }

  template<typename Interval, typename Tx>
  friend Interval pow_rev2(interval<T, Flavor> const& c,
                           interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tx
              >::type TMax;

    return Interval(pow_rev2(static_cast<interval<TMax, Flavor>>(c),
                             static_cast<interval<TMax, Flavor>>(x)));
  }


// atan2_rev1

  friend interval<T, Flavor> atan2_rev1(interval<T, Flavor> const& b,
                                        interval<T, Flavor> const& c,
                                        interval<T, Flavor> const& x) {  ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::atan2_rev1(b.rep_, c.rep_, x.rep_));
  }

  template<typename Interval, typename Tc, typename Tx>
  friend Interval atan2_rev1(interval<T, Flavor> const& b,
                             interval<Tc, Flavor> const& c,
                             interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tc,
              Tx
              >::type TMax;

    return Interval(atan2_rev1(static_cast<interval<TMax, Flavor>>(b),
                               static_cast<interval<TMax, Flavor>>(c),
                               static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> atan2_rev1(interval<T, Flavor> const& c,
                                        interval<T, Flavor> const& x) {  ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::atan2_rev1(c.rep_, x.rep_));
  }

  template<typename Interval, typename Tx>
  friend Interval atan2_rev1(interval<T, Flavor> const& c,
                             interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tx
              >::type TMax;

    return Interval(atan2_rev1(static_cast<interval<TMax, Flavor>>(c),
                               static_cast<interval<TMax, Flavor>>(x)));
  }


// atan2_rev2

  friend interval<T, Flavor> atan2_rev2(interval<T, Flavor> const& a,
                                        interval<T, Flavor> const& c,
                                        interval<T, Flavor> const& x) {  ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::atan2_rev2(a.rep_, c.rep_, x.rep_));
  }

  template<typename Interval, typename Tc, typename Tx>
  friend Interval atan2_rev2(interval<T, Flavor> const& a,
                             interval<Tc, Flavor> const& c,
                             interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tc,
              Tx
              >::type TMax;

    return Interval(atan2_rev2(static_cast<interval<TMax, Flavor>>(a),
                               static_cast<interval<TMax, Flavor>>(c),
                               static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> atan2_rev2(interval<T, Flavor> const& c,
                                        interval<T, Flavor> const& x) {  ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::atan2_rev2(c.rep_, x.rep_));
  }

  template<typename Interval, typename Tx>
  friend Interval atan2_rev2(interval<T, Flavor> const& c,
                             interval<Tx, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tx
              >::type TMax;

    return Interval(atan2_rev2(static_cast<interval<TMax, Flavor>>(c),
                               static_cast<interval<TMax, Flavor>>(x)));
  }

  // -----------------------------------------------------------------------------
  // Cancellative addition and subtraction, see P1788/D7.0 Sect. 9.6.6
  // -----------------------------------------------------------------------------


// cancel_plus

  friend interval<T, Flavor> cancel_plus(interval<T, Flavor> const& a,
                                         interval<T, Flavor> const& b) {     ///< Required, necessary for bare intervals? see, 11.11.6 // TODO nicht fuer bare interval
    return interval<T, Flavor>(Flavor<T>::cancel_plus(a.rep_, b.rep_));
  }

  template<typename Interval, typename Tb>
  friend Interval cancel_plus(interval<T, Flavor> const& a,
                              interval<Tb, Flavor> const& b) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tb
              >::type TMax;

    return Interval(cancel_plus(static_cast<interval<TMax, Flavor>>(a),
                                static_cast<interval<TMax, Flavor>>(b)));
  }


// cancel_minus

  friend interval<T, Flavor> cancel_minus(interval<T, Flavor> const& a,
                                          interval<T, Flavor> const& b) {    ///< Required, necessary for bare intervals? see, 11.11.6 // TODO nicht fuer bare interval
    return interval<T, Flavor>(Flavor<T>::cancel_minus(a.rep_, b.rep_));
  }

  template<typename Interval, typename Tb>
  friend Interval cancel_minus(interval<T, Flavor> const& a,
                               interval<Tb, Flavor> const& b) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Tb
              >::type TMax;

    return Interval(cancel_minus(static_cast<interval<TMax, Flavor>>(a),
                                 static_cast<interval<TMax, Flavor>>(b)));
  }


  // -----------------------------------------------------------------------------
  // Non-arithmetic set operations, see P1788/D7.0 Sect. 9.6.6
  // -----------------------------------------------------------------------------


// intersect

  friend interval<T, Flavor> intersect(interval<T, Flavor> const& x,
                                       interval<T, Flavor> const& y) {       ///< Required
    return interval<T, Flavor>(Flavor<T>::intersect(x.rep_, y.rep_));
  }

  template<typename Interval, typename Ty>
  friend Interval intersect(interval<T, Flavor> const& x,
                            interval<Ty, Flavor> const& y) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Ty
              >::type TMax;

    return Interval(intersect(static_cast<interval<TMax, Flavor>>(x),
                              static_cast<interval<TMax, Flavor>>(y)));
  }


// hull

  friend interval<T, Flavor> hull(interval<T, Flavor> const& x,
                                  interval<T, Flavor> const& y) {            ///< Required
    return interval<T, Flavor>(Flavor<T>::hull(x.rep_, y.rep_));
  }

  template<typename Interval, typename Ty>
  friend Interval hull(interval<T, Flavor> const& x,
                       interval<Ty, Flavor> const& y) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Ty
              >::type TMax;

    return Interval(hull(static_cast<interval<TMax, Flavor>>(x),
                         static_cast<interval<TMax, Flavor>>(y)));
  }

  // TODO
  //friend interval<T, Flavor> hull(std::initializer_list<T> ilst);           ///< interval hull, see P1788/D7.0 Sect. 11.8.1
  // TODO: Mixed type operation


// widen

  friend interval<T, Flavor> widen(interval<T, Flavor> const& x) {           ///< necessary as  a function?, see P1788/D7.0 Sect. 11.10  // TODO nicht notwendig
    return interval<T, Flavor>(Flavor<T>::widen(x.rep_));
  }

  template<typename Interval>
  friend Interval widen(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(widen(static_cast<interval<TMax, Flavor>>(x)));
  }


  // -----------------------------------------------------------------------------
  // Numeric functions on intervals, see P1788/D7.0 Sect. 9.6.9
  // -----------------------------------------------------------------------------

  friend T inf(interval<T, Flavor> const& x) {       ///< Required
    return Flavor<T>::inf(x.rep_);
  }

  friend T sup(interval<T, Flavor> const& x) {       ///< Required
    return Flavor<T>::sup(x.rep_);
  }

  friend T mid(interval<T, Flavor> const& x) {       ///< Required
    return Flavor<T>::mid(x.rep_);
  }

  friend T wid(interval<T, Flavor> const& x) {       ///< Required
    return Flavor<T>::wid(x.rep_);
  }

  friend T rad(interval<T, Flavor> const& x) {       ///< Required
    return Flavor<T>::rad(x.rep_);
  }

  friend T mag(interval<T, Flavor> const& x) {       ///< Required
    return Flavor<T>::mag(x.rep_);
  }

  friend T mig(interval<T, Flavor> const& x) {       ///< Required
    return Flavor<T>::mig(x.rep_);
  }

  friend std::pair<T, T> mid_rad(interval<T, Flavor> const& x) {     ///< Recommended, see Note in P1788/D7.0 Sect. 9.6.9
    return Flavor<T>::mid_rad(x.rep_);
  }


  // -----------------------------------------------------------------------------
  // Boolean functions on intervals, see P1788/D7.0 Sect. 9.6.10
  // -----------------------------------------------------------------------------

  // set op
  friend bool is_empty(interval<T, Flavor> const& x) {   ///< Required
    return Flavor<T>::is_empty(x.rep_);
  }

  friend bool is_entire(interval<T, Flavor> const& x) {  ///< Required
    return Flavor<T>::is_entire(x.rep_);
  }

  // comparisons see P1788/D7.0 Sect. 9.6.10 Table 4


// is_equal

  friend bool is_equal(interval<T, Flavor> const& x, interval<T, Flavor> const& y) {   ///< Required, Mixed Type
    return Flavor<T>::is_equal(x.rep_, y.rep_);
  }

  template<typename Ty>
  friend bool is_equal(interval<T, Flavor> const& x, interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
              T,
              Ty
              >::type TMax;

    return is_equal(static_cast<interval<TMax, Flavor>>(x),
                    static_cast<interval<TMax, Flavor>>(y));
  }


// contained_in

  friend bool contained_in(interval<T, Flavor> const& x, interval<T, Flavor> const& y) {   ///< Required, Mixed Type
    return Flavor<T>::contained_in(x.rep_, y.rep_);
  }

  template<typename Ty>
  friend bool contained_in(interval<T, Flavor> const& x, interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
              T,
              Ty
              >::type TMax;

    return contained_in(static_cast<interval<TMax, Flavor>>(x),
                        static_cast<interval<TMax, Flavor>>(y));
  }


// precedes

  friend bool precedes(interval<T, Flavor> const& x, interval<T, Flavor> const& y) {   ///< Required, Mixed Type
    return Flavor<T>::precedes(x.rep_, y.rep_);
  }

  template<typename Ty>
  friend bool precedes(interval<T, Flavor> const& x, interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
              T,
              Ty
              >::type TMax;

    return precedes(static_cast<interval<TMax, Flavor>>(x),
                    static_cast<interval<TMax, Flavor>>(y));
  }


// is_interior

  friend bool is_interior(interval<T, Flavor> const& x, interval<T, Flavor> const& y) {    ///< Required, Mixed Type
    return Flavor<T>::is_interior(x.rep_, y.rep_);
  }

  template<typename Ty>
  friend bool is_interior(interval<T, Flavor> const& x, interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
              T,
              Ty
              >::type TMax;

    return is_interior(static_cast<interval<TMax, Flavor>>(x),
                       static_cast<interval<TMax, Flavor>>(y));
  }


// strictly_less

  friend bool strictly_less(interval<T, Flavor> const& x, interval<T, Flavor> const& y) {  ///< Required, Mixed Type
    return Flavor<T>::strictly_less(x.rep_, y.rep_);
  }

  template<typename Ty>
  friend bool strictly_less(interval<T, Flavor> const& x, interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
              T,
              Ty
              >::type TMax;

    return strictly_less(static_cast<interval<TMax, Flavor>>(x),
                         static_cast<interval<TMax, Flavor>>(y));
  }


// strictly_precedes

  friend bool strictly_precedes(interval<T, Flavor> const& x, interval<T, Flavor> const& y) {  ///< Required, Mixed Type
    return Flavor<T>::strictly_precedes(x.rep_, y.rep_);
  }

  template<typename Ty>
  friend bool strictly_precedes(interval<T, Flavor> const& x, interval<T, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
              T,
              Ty
              >::type TMax;

    return strictly_precedes(static_cast<interval<TMax, Flavor>>(x),
                             static_cast<interval<TMax, Flavor>>(y));
  }


// are_disjoint
  friend bool are_disjoint(interval<T, Flavor> const& x, interval<T, Flavor> const& y) {   ///< Required, Mixed Type
    return Flavor<T>::are_disjoint(x.rep_, y.rep_);
  }

  template<typename Ty>
  friend bool are_disjoint(interval<T, Flavor> const& x, interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
              T,
              Ty
              >::type TMax;

    return are_disjoint(static_cast<interval<TMax, Flavor>>(x),
                        static_cast<interval<TMax, Flavor>>(y));
  }


// Equal and Unequal operator : short form of is_equal and !is_equal
  friend bool operator==(interval<T, Flavor> const& x, interval<T, Flavor> const& y) {    ///< Implementation specific, short hand for is_equal
    return is_equal(x, y);
  }

  template<typename Ty>
  friend bool operator==(interval<T, Flavor> const& x, interval<Ty, Flavor> const& y) {
    return is_equal(x, y);
  }

  friend bool operator!=(interval<T, Flavor> const& x, interval<T, Flavor> const& y) {     ///< Implementation specific, short hand for !is_equal
    return !is_equal(x, y);
  }

  template<typename Ty>
  friend bool operator!=(interval<T, Flavor> const& x, interval<Ty, Flavor> const& y) {
    return !is_equal(x, y);
  }


  // -----------------------------------------------------------------------------
  // Recommended forward elementary functions on intervals, see P1788/D7.0 Sect. 9.7.1 Table 5
  // -----------------------------------------------------------------------------

  friend interval<T, Flavor> rootn(interval<T, Flavor> const& x, int n) {
    return interval<T, Flavor>(Flavor<T>::rootn(x.rep_, n));
  }

  template<typename Interval>
  friend Interval rootn(interval<T, Flavor> const& x, int n) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(rootn(static_cast<interval<TMax, Flavor>>(x), n));
  }

  friend interval<T, Flavor> expm1(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::expm1(x.rep_));
  }

  template<typename Interval>
  friend Interval expm1(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(expm1(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> exp2m1(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::exp2m1(x.rep_));
  }

  template<typename Interval>
  friend Interval exp2m1(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(exp2m1(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> exp10m1(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::exp10m1(x.rep_));
  }

  template<typename Interval>
  friend Interval exp10m1(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(exp10m1(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> logp1(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::logp1(x.rep_));
  }

  template<typename Interval>
  friend Interval logp1(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(logp1(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> log2p1(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::log2p1(x.rep_));
  }

  template<typename Interval>
  friend Interval log2p1(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(log2p1(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> log10p1(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::log10p1(x.rep_));
  }

  template<typename Interval>
  friend Interval log10p1(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(log10p1(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> compoundm1(interval<T, Flavor> const& x,
                                        interval<T, Flavor> const& y) {
    return interval<T, Flavor>(Flavor<T>::compoundm1(x.rep_, y.rep_));
  }

  template<typename Interval, typename Ty>
  friend Interval compoundm1(interval<T, Flavor> const& x,
                        interval<Ty, Flavor> const& y) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Ty
              >::type TMax;

    return Interval(compoundm1(static_cast<interval<TMax, Flavor>>(x),
                               static_cast<interval<TMax, Flavor>>(y)));
  }

  friend interval<T, Flavor> hypot(interval<T, Flavor> const& x,
                                   interval<T, Flavor> const& y) {   ///< tightest, required or recommended?
    return interval<T, Flavor>(Flavor<T>::hypot(x.rep_, y.rep_));
  }

  template<typename Interval, typename Ty>
  friend Interval hypot(interval<T, Flavor> const& x,
                        interval<Ty, Flavor> const& y) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Ty
              >::type TMax;

    return Interval(hypot(static_cast<interval<TMax, Flavor>>(x),
                          static_cast<interval<TMax, Flavor>>(y)));
  }

  friend interval<T, Flavor> r_sqrt(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::r_sqrt(x.rep_));
  }

  template<typename Interval>
  friend Interval r_sqrt(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(r_sqrt(static_cast<interval<TMax, Flavor>>(x)));
  }


  friend interval<T, Flavor> sin_pi(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::sin_pi(x.rep_));
  }

  template<typename Interval>
  friend Interval sin_pi(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(sin_pi(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> cos_pi(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::cos_pi(x.rep_));
  }

  template<typename Interval>
  friend Interval cos_pi(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(cos_pi(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> tan_pi(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::tan_pi(x.rep_));
  }

  template<typename Interval>
  friend Interval tan_pi(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(tan_pi(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> asin_pi(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::asin_pi(x.rep_));
  }

  template<typename Interval>
  friend Interval asin_pi(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(asin_pi(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> acos_pi(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::acos_pi(x.rep_));
  }

  template<typename Interval>
  friend Interval acos_pi(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(acos_pi(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> atan_pi(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::atan_pi(x.rep_));
  }

  template<typename Interval>
  friend Interval atan_pi(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(atan_pi(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> atan2_pi(interval<T, Flavor> const& x,
                                      interval<T, Flavor> const& y) {
    return interval<T, Flavor>(Flavor<T>::atan2_pi(x.rep_, y.rep_));
  }

  template<typename Interval, typename Ty>
  friend Interval atan2_pi(interval<T, Flavor> const& x,
                           interval<Ty, Flavor> const& y) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Ty
              >::type TMax;

    return Interval(atan2_pi(static_cast<interval<TMax, Flavor>>(x),
                             static_cast<interval<TMax, Flavor>>(y)));
  }


  // -----------------------------------------------------------------------------
  // Recommended interval overlapping, see P1788/D7.0 Sect. 9.7.2
  // -----------------------------------------------------------------------------

  friend p1788::overlapping_state overlap(interval<T, Flavor> const& x,
                                          interval<T, Flavor> const& y) {
    return Flavor<T>::overlap(x.rep_, y.rep_);
  }

  template<typename Interval, typename Ty>
  friend p1788::overlapping_state overlap(interval<T, Flavor> const& x,
                           interval<Ty, Flavor> const& y) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T,
              Ty
              >::type TMax;

    return overlap(static_cast<interval<TMax, Flavor>>(x),
                   static_cast<interval<TMax, Flavor>>(y));
  }

  // -----------------------------------------------------------------------------
  // Recommended slope functions, see P1788/D7.0 Sect. 9.7.3 Table 7
  // -----------------------------------------------------------------------------

  friend interval<T, Flavor> exp_slope1(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::exp_slope1(x.rep_));
  }

  template<typename Interval>
  friend Interval exp_slope1(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(exp_slope1(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> exp_slope2(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::exp_slope2(x.rep_));
  }

  template<typename Interval>
  friend Interval exp_slope2(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(exp_slope2(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> log_slope1(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::log_slope1(x.rep_));
  }

  template<typename Interval>
  friend Interval log_slope1(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(log_slope1(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> log_slope2(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::log_slope2(x.rep_));
  }

  template<typename Interval>
  friend Interval log_slope2(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(log_slope2(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> cos_slope2(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::cos_slope2(x.rep_));
  }

  template<typename Interval>
  friend Interval cos_slope2(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(cos_slope2(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> sin_slope3(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::sin_slope3(x.rep_));
  }

  template<typename Interval>
  friend Interval sin_slope3(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(sin_slope3(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> asin_slope3(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::asin_slope3(x.rep_));
  }

  template<typename Interval>
  friend Interval asin_slope3(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(asin_slope3(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> atan_slope3(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::atan_slope3(x.rep_));
  }

  template<typename Interval>
  friend Interval atan_slope3(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(atan_slope3(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> cosh_slope2(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::cosh_slope2(x.rep_));
  }

  template<typename Interval>
  friend Interval cosh_slope2(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(cosh_slope2(static_cast<interval<TMax, Flavor>>(x)));
  }

  friend interval<T, Flavor> sinh_slope3(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::sinh_slope3(x.rep_));
  }

  template<typename Interval>
  friend Interval sinh_slope3(interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
              T
              >::type TMax;

    return Interval(sinh_slope3(static_cast<interval<TMax, Flavor>>(x)));
  }

};

} // namespace infsup

} // namespace p1788




#endif // LIBIEEEP1788_P1788_INFSUP_INTERVAL_HPP
