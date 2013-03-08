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

#ifndef LIBIEEEP1788_P1788_INFSUP_INTERVAL_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_INTERVAL_ELEM_FUNC_IMPL_HPP

#include <vector>
#include <algorithm>

#include "p1788/util/mixed_type_traits.hpp"

namespace p1788
{

namespace infsup
{

// -----------------------------------------------------------------------------
// Forward elementary functions
// -----------------------------------------------------------------------------


// pos

template< typename T, template< typename > class Flavor >
interval<T, Flavor> pos ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::pos(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval pos ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(pos(x));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator+ ( interval<T, Flavor> const& x )
{
    return pos(x);
}


// neg

template< typename T, template< typename > class Flavor >
interval<T, Flavor> neg ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::neg(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval neg ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(neg(x));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator- ( interval<T, Flavor> const& x )
{
    return neg(x);
}


// add

template< typename T, template< typename > class Flavor >
interval<T, Flavor> add ( interval<T, Flavor> const& x,
                          interval<T, Flavor> const& y )
{
    return interval<T, Flavor>(Flavor<T>::add(x.rep(), y.rep()));
}

template< typename Interval, typename Tx, typename Ty,
          template< typename > class Flavor >
Interval add ( interval<Tx, Flavor> const& x, interval<Ty, Flavor> const& y )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
             Tx,
             Ty
             >::type Tmax;

    return Interval(add(static_cast<interval<Tmax, Flavor>>(x),
                        static_cast<interval<Tmax, Flavor>>(y)));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator+ ( interval<T, Flavor> const& x,
                                interval<T, Flavor> const& y )
{
    return add(x, y);
}


// sub

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sub ( interval<T, Flavor> const& x,
                          interval<T, Flavor> const& y )
{
    return interval<T, Flavor>(Flavor<T>::sub(x.rep(), y.rep()));
}

template< typename Interval, typename Tx, typename Ty,
          template< typename > class Flavor >
Interval sub ( interval<Tx, Flavor> const& x, interval<Ty, Flavor> const& y )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
             Tx,
             Ty
             >::type Tmax;

    return Interval(sub(static_cast<interval<Tmax, Flavor>>(x),
                        static_cast<interval<Tmax, Flavor>>(y)));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator- ( interval<T, Flavor> const& x,
                                interval<T, Flavor> const& y )
{
    return sub(x, y);
}


// mul

template< typename T, template< typename > class Flavor >
interval<T, Flavor> mul ( interval<T, Flavor> const& x,
                          interval<T, Flavor> const& y )
{
    return interval<T, Flavor>(Flavor<T>::mul(x.rep(), y.rep()));
}

template< typename Interval, typename Tx, typename Ty,
          template< typename > class Flavor >
Interval mul ( interval<Tx, Flavor> const& x, interval<Ty, Flavor> const& y )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
             Tx,
             Ty
             >::type Tmax;

    return Interval(mul(static_cast<interval<Tmax, Flavor>>(x),
                        static_cast<interval<Tmax, Flavor>>(y)));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator* ( interval<T, Flavor> const& x,
                                interval<T, Flavor> const& y )
{
    return mul(x, y);
}


// div

template< typename T, template< typename > class Flavor >
interval<T, Flavor> div ( interval<T, Flavor> const& x,
                          interval<T, Flavor> const& y )
{
    return interval<T, Flavor>(Flavor<T>::div(x.rep(), y.rep()));
}

template< typename Interval, typename Tx, typename Ty,
          template< typename > class Flavor >
Interval div ( interval<Tx, Flavor> const& x, interval<Ty, Flavor> const& y )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
             Tx,
             Ty
             >::type Tmax;

    return Interval(div(static_cast<interval<Tmax, Flavor>>(x),
                        static_cast<interval<Tmax, Flavor>>(y)));
}

template< typename T, template< typename > class Flavor >
interval<T, Flavor> operator/ ( interval<T, Flavor> const& x,
                                interval<T, Flavor> const& y )
{
    return div(x, y);
}


// inv

template< typename T, template< typename > class Flavor >
interval<T, Flavor> inv ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::inv(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval inv ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(inv(x));
}


// sqrt

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sqrt ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::sqrt(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval sqrt ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(sqrt(x));
}


// fma

template< typename T, template< typename > class Flavor >
interval<T, Flavor> fma ( interval<T, Flavor> const& x,
                          interval<T, Flavor> const& y,
                          interval<T, Flavor> const& z )
{
    return interval<T, Flavor>(Flavor<T>::fma(x.rep(), y.rep(), z.rep()));
}

template< typename Interval, typename Tx, typename Ty, typename Tz,
          template< typename > class Flavor >
Interval fma ( interval<Tx, Flavor> const& x,
               interval<Ty, Flavor> const& y,
               interval<Tz, Flavor> const& z )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
             Tx,
             Ty,
             Tz
             >::type Tmax;

    return Interval(fma(static_cast<interval<Tmax, Flavor>>(x),
                        static_cast<interval<Tmax, Flavor>>(y),
                        static_cast<interval<Tmax, Flavor>>(z)));
}


// interval case

template< typename T, template< typename > class Flavor >
interval<T, Flavor> interval_case ( interval<T, Flavor> const& c,
                                    interval<T, Flavor> const& g,
                                    interval<T, Flavor> const& h )
{
    return interval<T, Flavor>(Flavor<T>::interval_case(c.rep(),
                               g.rep(), h.rep()));
}

template< typename Interval, typename Tc, typename Tg, typename Th,
          template< typename > class Flavor >
Interval interval_case ( interval<Tc, Flavor> const& c,
                         interval<Tg, Flavor> const& g,
                         interval<Th, Flavor> const& h )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
             Tc,
             Tg,
             Th
             >::type Tmax;

    return Interval(interval_case(static_cast<interval<Tmax, Flavor>>(c),
                                  static_cast<interval<Tmax, Flavor>>(g),
                                  static_cast<interval<Tmax, Flavor>>(h)));
}


// sqr

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sqr ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::sqr(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval sqr ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(sqr(x));
}


// pown

template< typename T, template< typename > class Flavor >
interval<T, Flavor> pown ( interval<T, Flavor> const& x,
                           int p )
{
    return interval<T, Flavor>(Flavor<T>::pown(x.rep(), p));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval pown ( interval<T, Flavor> const& x,
                int p )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(pown(x, p));
}


// pow

template< typename T, template< typename > class Flavor >
interval<T, Flavor> pow ( interval<T, Flavor> const& x,
                          interval<T, Flavor> const& y )
{
    return interval<T, Flavor>(Flavor<T>::pow(x.rep(), y.rep()));
}

template< typename Interval, typename Tx, typename Ty,
          template< typename > class Flavor >
Interval pow ( interval<Tx, Flavor> const& x,
               interval<Ty, Flavor> const& y )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
             Tx,
             Ty
             >::type Tmax;

    return Interval(pow(static_cast<interval<Tmax, Flavor>>(x),
                        static_cast<interval<Tmax, Flavor>>(y)));
}


// exp

template< typename T, template< typename > class Flavor >
interval<T, Flavor> exp ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::exp(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval exp ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(exp(x));
}


// exp2

template< typename T, template< typename > class Flavor >
interval<T, Flavor> exp2 ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::exp2(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval exp2 ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(exp2(x));
}


// exp10

template< typename T, template< typename > class Flavor >
interval<T, Flavor> exp10 ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::exp10(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval exp10 ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(exp10(x));
}


// log

template< typename T, template< typename > class Flavor >
interval<T, Flavor> log ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::log(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval log ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(log(x));
}


// log2

template< typename T, template< typename > class Flavor >
interval<T, Flavor> log2 ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::log2(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval log2 ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(log2(x));
}


// log10

template< typename T, template< typename > class Flavor >
interval<T, Flavor> log10 ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::log10(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval log10 ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(log10(x));
}


// sin

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sin ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::sin(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval sin ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(sin(x));
}


// cos

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cos ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::cos(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval cos ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(cos(x));
}


// tan

template< typename T, template< typename > class Flavor >
interval<T, Flavor> tan ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::tan(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval tan ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(tan(x));
}


// asin

template< typename T, template< typename > class Flavor >
interval<T, Flavor> asin ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::asin(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval asin ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(asin(x));
}

// acos

template< typename T, template< typename > class Flavor >
interval<T, Flavor> acos ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::acos(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval acos ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(acos(x));
}


// atan

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atan ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::atan(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval atan ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(atan(x));
}

// atan2

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atan2 ( interval<T, Flavor> const& y,
                            interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::atan2(y.rep(), x.rep()));
}

template< typename Interval, typename Ty, typename Tx,
          template< typename > class Flavor >
Interval atan2 ( interval<Ty, Flavor> const& y,
                 interval<Tx, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
             Ty,
             Tx
             >::type Tmax;

    return Interval(atan2(static_cast<interval<Tmax, Flavor>>(y),
                          static_cast<interval<Tmax, Flavor>>(x)));
}


// sinh

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sinh ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::sinh(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval sinh ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(sinh(x));
}


// cosh

template< typename T, template< typename > class Flavor >
interval<T, Flavor> cosh ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::cosh(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval cosh ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(cosh(x));
}


// tanh

template< typename T, template< typename > class Flavor >
interval<T, Flavor> tanh ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::tanh(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval tanh ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(tanh(x));
}


// asinh

template< typename T, template< typename > class Flavor >
interval<T, Flavor> asinh ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::asinh(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval asinh ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(asinh(x));
}


// acosh

template< typename T, template< typename > class Flavor >
interval<T, Flavor> acosh ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::acosh(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval acosh ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(acosh(x));
}


// atanh

template< typename T, template< typename > class Flavor >
interval<T, Flavor> atanh ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::atanh(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval atanh ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(atanh(x));
}


// sign

template< typename T, template< typename > class Flavor >
interval<T, Flavor> sign ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::sign(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval sign ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(sign(x));
}


// ceil

template< typename T, template< typename > class Flavor >
interval<T, Flavor> ceil ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::ceil(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval ceil ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(ceil(x));
}


// floor

template< typename T, template< typename > class Flavor >
interval<T, Flavor> floor ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::floor(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval floor ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(floor(x));
}


// trunc

template< typename T, template< typename > class Flavor >
interval<T, Flavor> trunc ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::trunc(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval trunc ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(trunc(x));
}


// round_ties_to_even

template< typename T, template< typename > class Flavor >
interval<T, Flavor> round_ties_to_even ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::round_ties_to_even(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval round_ties_to_even ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(round_ties_to_even(x));
}


// round_ties_to_away

template< typename T, template< typename > class Flavor >
interval<T, Flavor> round_ties_to_away ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::round_ties_to_away(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval round_ties_to_away ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(round_ties_to_away(x));
}


// abs

template< typename T, template< typename > class Flavor >
interval<T, Flavor> abs ( interval<T, Flavor> const& x )
{
    return interval<T, Flavor>(Flavor<T>::abs(x.rep()));
}

template< typename Interval, typename T, template< typename > class Flavor >
Interval abs ( interval<T, Flavor> const& x )
{
    static_assert(p1788::util::is_infsup_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by mixed type operations!");

    return Interval(abs(x));
}


// min

template< typename T, template< typename > class Flavor >
interval<T, Flavor> min ( std::initializer_list<interval<T, Flavor>> intervals )
{
    std::vector<typename Flavor<T>::representation> v;

    std::transform(intervals.begin(), intervals.end(), std::back_inserter(v), [] (interval<T, Flavor> const & x) {
        return x.rep();
    } );

    typename std::vector<typename Flavor<T>::representation>::const_iterator first = v.begin();
    typename std::vector<typename Flavor<T>::representation>::const_iterator last = v.end();

    return interval<T, Flavor>(Flavor<T>::min(first, last));
}


// max

template< typename T, template< typename > class Flavor >
interval<T, Flavor> max ( std::initializer_list<interval<T, Flavor>> intervals )
{
    std::vector<typename Flavor<T>::representation> v;

    std::transform(intervals.begin(), intervals.end(), std::back_inserter(v), [] (interval<T, Flavor> const & x) {
        return x.rep();
    } );

    typename std::vector<typename Flavor<T>::representation>::const_iterator first = v.begin();
    typename std::vector<typename Flavor<T>::representation>::const_iterator last = v.end();

    return interval<T, Flavor>(Flavor<T>::max(first, last));
}




} // namespace infsup

} // namespace p1788

#endif // LIBIEEEP1788_P1788_INFSUP_INTERVAL_ELEM_FUNC_IMPL_HPP
