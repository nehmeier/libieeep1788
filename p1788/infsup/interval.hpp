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


//TODO move this trait into an other header?
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
};



// -----------------------------------------------------------------------------
// Reverse elementary functions, see P1788/D7.0 Sect. 9.6.5 Table 2
// -----------------------------------------------------------------------------

// reverse version of unary point functions

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> sqr_rev(interval<T, Flavor> const&, interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> sqr_rev(interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> inv_rev(interval<T, Flavor> const&, interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> inv_rev(interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> abs_rev(interval<T, Flavor> const&, interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> abs_rev(interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> pown_rev(interval<T, Flavor> const&, interval<T, Flavor> const&, int);   ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> pown_rev(interval<T, Flavor> const&, int);   ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> sin_rev(interval<T, Flavor> const&, interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> sin_rev(interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> cos_rev(interval<T, Flavor> const&, interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> cos_rev(interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> tan_rev(interval<T, Flavor> const&, interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> tan_rev(interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> cosh_rev(interval<T, Flavor> const&, interval<T, Flavor> const&);    ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> cosh_rev(interval<T, Flavor> const&);    ///< Required, accurate


// reverse versions of binary point functions

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> mul_rev(interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> mul_rev(interval<T, Flavor> const&, interval<T, Flavor> const&);     ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> div_rev1(interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const&);    ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> div_rev1(interval<T, Flavor> const&, interval<T, Flavor> const&);    ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> div_rev2(interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const&);    ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> div_rev2(interval<T, Flavor> const&, interval<T, Flavor> const&);    ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> pow_rev1(interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const&);    ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> pow_rev1(interval<T, Flavor> const&, interval<T, Flavor> const&);    ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> pow_rev2(interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const&);    ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> pow_rev2(interval<T, Flavor> const&, interval<T, Flavor> const&);    ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> atan2_rev1(interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const&);  ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> atan2_rev1(interval<T, Flavor> const&, interval<T, Flavor> const&);  ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> atan2_rev2(interval<T, Flavor> const&, interval<T, Flavor> const&, interval<T, Flavor> const&);  ///< Required, accurate

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> atan2_rev2(interval<T, Flavor> const&, interval<T, Flavor> const&);  ///< Required, accurate


// -----------------------------------------------------------------------------
// Cancellative addition and subtraction, see P1788/D7.0 Sect. 9.6.6
// -----------------------------------------------------------------------------

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> cancel_plus(interval<T, Flavor> const&, interval<T, Flavor> const&);     ///< Required, necessary for bare intervals? see, 11.11.6 // TODO nicht fuer bare interval

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> cancel_minus(interval<T, Flavor> const&, interval<T, Flavor> const&);    ///< Required, necessary for bare intervals? see, 11.11.6 // TODO nicht fuer bare interval


// -----------------------------------------------------------------------------
// Non-arithmetic set operations, see P1788/D7.0 Sect. 9.6.6
// -----------------------------------------------------------------------------

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> intersect(interval<T, Flavor> const&, interval<T, Flavor> const&);       ///< Required

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> hull(interval<T, Flavor> const&, interval<T, Flavor> const&);            ///< Required

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> hull(std::initializer_list<T>);      ///< interval hull, see P1788/D7.0 Sect. 11.8.1

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> widen(interval<T, Flavor> const&);  ///< necessary as  a function?, see P1788/D7.0 Sect. 11.10  // TODO nicht notwendig

// -----------------------------------------------------------------------------
// Numeric functions on intervals, see P1788/D7.0 Sect. 9.6.9
// -----------------------------------------------------------------------------

template<typename T, template<typename>  class Flavor>
T inf(interval<T, Flavor> const&);       ///< Required

template<typename T, template<typename>  class Flavor>
T sup(interval<T, Flavor> const&);       ///< Required

template<typename T, template<typename>  class Flavor>
T mid(interval<T, Flavor> const&);       ///< Required

template<typename T, template<typename>  class Flavor>
T wid(interval<T, Flavor> const&);       ///< Required

template<typename T, template<typename>  class Flavor>
T rad(interval<T, Flavor> const&);       ///< Required

template<typename T, template<typename>  class Flavor>
T mag(interval<T, Flavor> const&);       ///< Required

template<typename T, template<typename>  class Flavor>
T mig(interval<T, Flavor> const&);       ///< Required

template<typename T, template<typename>  class Flavor>
std::pair<T, T> mid_rad(interval<T, Flavor> const&);     ///< Recommended, see Note in P1788/D7.0 Sect. 9.6.9


// -----------------------------------------------------------------------------
// Boolean functions on intervals, see P1788/D7.0 Sect. 9.6.10
// -----------------------------------------------------------------------------

// set op
template<typename T, template<typename>  class Flavor>
bool is_empty(interval<T, Flavor> const&);   ///< Required

template<typename T, template<typename>  class Flavor>
bool is_entire(interval<T, Flavor> const&);  ///< Required

// comparisons see P1788/D7.0 Sect. 9.6.10 Table 4
template<typename T, template<typename>  class Flavor>
bool is_equal(interval<T, Flavor> const&, interval<T, Flavor> const&);   ///< Required, Mixed Type

template<typename T, template<typename>  class Flavor>
bool contained_in(interval<T, Flavor> const&, interval<T, Flavor> const&);   ///< Required, Mixed Type

template<typename T, template<typename>  class Flavor>
bool less(interval<T, Flavor> const&, interval<T, Flavor> const&);   ///< Required, Mixed Type

template<typename T, template<typename>  class Flavor>
bool precedes(interval<T, Flavor> const&, interval<T, Flavor> const&);   ///< Required, Mixed Type

template<typename T, template<typename>  class Flavor>
bool is_interior(interval<T, Flavor> const&, interval<T, Flavor> const&);    ///< Required, Mixed Type

template<typename T, template<typename>  class Flavor>
bool strictly_less(interval<T, Flavor> const&, interval<T, Flavor> const&);  ///< Required, Mixed Type

template<typename T, template<typename>  class Flavor>
bool strictly_precedes(interval<T, Flavor> const&, interval<T, Flavor> const&);  ///< Required, Mixed Type

template<typename T, template<typename>  class Flavor>
bool are_disjoint(interval<T, Flavor> const&, interval<T, Flavor> const&);   ///< Required, Mixed Type


// Equal and Unequal operator : short form of is_equal and !is_equal
template<typename T, template<typename>  class Flavor>
bool operator==(interval<T, Flavor> const&, interval<T, Flavor> const&);     ///< Implementation specific, short hand for is_equal

template<typename T, template<typename>  class Flavor>
bool operator!=(interval<T, Flavor> const&, interval<T, Flavor> const&);     ///< Implementation specific, short hand for !is_equal

// -----------------------------------------------------------------------------
// Recommended forward elementary functions on intervals, see P1788/D7.0 Sect. 9.7.1 Table 5
// -----------------------------------------------------------------------------

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> rootn(interval<T, Flavor> const&, int);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> expm1(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> exp2m1(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> exp10m1(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> logp1(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> log2p1(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> log10p1(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> compoundm1(interval<T, Flavor> const&,
                               interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> hypot(interval<T, Flavor> const&, interval<T, Flavor> const&);   ///< tightest, required or recommended?

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> r_sqrt(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> sin_pi(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> cos_pi(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> tan_pi(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> asin_pi(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> acos_pi(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> atan_pi(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> atan2_pi(interval<T, Flavor> const&,
                             interval<T, Flavor> const&);


// -----------------------------------------------------------------------------
// Recommended interval overlapping, see P1788/D7.0 Sect. 9.7.2
// -----------------------------------------------------------------------------

template<typename T, template<typename>  class Flavor>
p1788::overlapping_state overlap(interval<T, Flavor> const&, interval<T, Flavor> const&);


// -----------------------------------------------------------------------------
// Recommended slope functions, see P1788/D7.0 Sect. 9.7.3 Table 7
// -----------------------------------------------------------------------------

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> exp_slope1(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> exp_slope2(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> log_slope1(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> log_slope2(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> cos_slope2(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> sin_slope3(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> asin_slope3(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> atan_slope3(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> cosh_slope2(interval<T, Flavor> const&);

template<typename T, template<typename>  class Flavor>
interval<T, Flavor> sinh_slope3(interval<T, Flavor> const&);


} // namespace infsup

} // namespace p1788




#endif // LIBIEEEP1788_P1788_INFSUP_INTERVAL_HPP
