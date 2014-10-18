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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_ELEM_FUNC_IMPL_HPP

#include "p1788/util/mixed_type_traits.hpp"


namespace p1788
{

namespace infsup
{


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// \name Forward elementary functions
//
//@{


// pos

// \brief Identity of an interval <B>x</B>
//
// <B>Implementation specific</B>
//
// Only provided for consistency with #neg(interval<T,Flavor> const& x).
//
// \see #neg(interval<T,Flavor> const& x)
// \see #operator+(interval<T,Flavor> const& x)
//
// \param x interval
// \return <B>x</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval pos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(x.rep_);
}

// \brief Identity of an interval <B>x</B>
//
// <B>Short hand of</B> #pos(interval<T,Flavor> const& x)
//
// <B>Implementation specific</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval operator+(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return pos(x);
}


// neg

// \brief Negation of an interval <B>x</B>
//
// <B>Required by IEEE P1788</B>
//
//
// \see #operator-(interval<T,Flavor> const& x)
// \see #pos(interval<T,Flavor> const& x)
//
// \param x interval
// \return -<B>x</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval neg(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::neg(x.rep_));
}

// \brief Negation of an interval <B>x</B>
//
// <B>Short hand of</B> #neg(interval<T,Flavor> const& x)
//
// <B>Implementation specific</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval operator-(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return neg(x);
}


// add

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval add (base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::add(x.rep_, y.rep_));
}

template<typename Interval, typename T, typename T_y, template<typename> class Flavor,
    typename RepType, class ConcreteInterval, typename RepType_y, class ConcreteInterval_y>
Interval add(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
             base_interval<T_y, Flavor, RepType_y, ConcreteInterval_y> const& y) {
    // assert that Interval is an implementation of base_interval
    static_assert(p1788::util::is_infsup_base_interval_implementation<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    // assert that Interval uses the same flavor
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_y>::representation, RepType_y>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation,
                        typename Interval::representation_type>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T_y>::representation_dec, RepType_y>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation_dec,
                        typename Interval::representation_type>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    typedef typename p1788::util::max_precision_interval_type<
        Interval,
        ConcreteInterval,
        ConcreteInterval_y
             >::type Interval_max;

    return Interval(add(static_cast<Interval_max>(x),
                        static_cast<Interval_max>(y)));
}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval operator+(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return add(x, y);
}


// sub

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sub(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                               base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sub(x.rep_, y.rep_));
}

template<typename Interval, typename T, typename T_y, template<typename> class Flavor,
    typename RepType, class ConcreteInterval, typename RepType_y, class ConcreteInterval_y>
Interval sub(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
             base_interval<T_y, Flavor, RepType_y, ConcreteInterval_y> const& y) {
    // assert that Interval is an implementation of base_interval
    static_assert(p1788::util::is_infsup_base_interval_implementation<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    // assert that Interval uses the same flavor
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_y>::representation, RepType_y>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation,
                        typename Interval::representation_type>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T_y>::representation_dec, RepType_y>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation_dec,
                        typename Interval::representation_type>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    typedef typename p1788::util::max_precision_interval_type<
        Interval,
        ConcreteInterval,
        ConcreteInterval_y
             >::type Interval_max;

    return Interval(sub(static_cast<Interval_max>(x),
                        static_cast<Interval_max>(y)));
}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval operator-(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return sub(x, y);
}


// mul

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval mul(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                               base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::mul(x.rep_, y.rep_));
}

template<typename Interval, typename T, typename T_y, template<typename> class Flavor,
    typename RepType, class ConcreteInterval, typename RepType_y, class ConcreteInterval_y>
Interval mul(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
             base_interval<T_y, Flavor, RepType_y, ConcreteInterval_y> const& y) {
    // assert that Interval is an implementation of base_interval
    static_assert(p1788::util::is_infsup_base_interval_implementation<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    // assert that Interval uses the same flavor
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_y>::representation, RepType_y>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation,
                        typename Interval::representation_type>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T_y>::representation_dec, RepType_y>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation_dec,
                        typename Interval::representation_type>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    typedef typename p1788::util::max_precision_interval_type<
        Interval,
        ConcreteInterval,
        ConcreteInterval_y
             >::type Interval_max;

    return Interval(mul(static_cast<Interval_max>(x),
                        static_cast<Interval_max>(y)));
}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval operator*(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return mul(x, y);
}


// div

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval div(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                               base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::div(x.rep_, y.rep_));
}

template<typename Interval, typename T, typename T_y, template<typename> class Flavor,
    typename RepType, class ConcreteInterval, typename RepType_y, class ConcreteInterval_y>
Interval div(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
             base_interval<T_y, Flavor, RepType_y, ConcreteInterval_y> const& y) {
    // assert that Interval is an implementation of base_interval
    static_assert(p1788::util::is_infsup_base_interval_implementation<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    // assert that Interval uses the same flavor
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_y>::representation, RepType_y>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation,
                        typename Interval::representation_type>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T_y>::representation_dec, RepType_y>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation_dec,
                        typename Interval::representation_type>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    typedef typename p1788::util::max_precision_interval_type<
        Interval,
        ConcreteInterval,
        ConcreteInterval_y
             >::type Interval_max;

    return Interval(div(static_cast<Interval_max>(x),
                        static_cast<Interval_max>(y)));
}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval operator/(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return div(x, y);
}


// recip

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval recip(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::recip(x.rep_));
}

template<typename Interval, typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
Interval recip(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    // assert that Interval is an implementation of base_interval
    static_assert(p1788::util::is_infsup_base_interval_implementation<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    // assert that Interval uses the same flavor
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation,
                        typename Interval::representation_type>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation_dec,
                        typename Interval::representation_type>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    typedef typename p1788::util::max_precision_interval_type<
        Interval,
        ConcreteInterval
             >::type Interval_max;

    return Interval(recip(static_cast<Interval_max>(x)));
}


// sqr

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sqr(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sqr(x.rep_));
}

template<typename Interval, typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
Interval sqr(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    // assert that Interval is an implementation of base_interval
    static_assert(p1788::util::is_infsup_base_interval_implementation<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    // assert that Interval uses the same flavor
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation,
                        typename Interval::representation_type>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation_dec,
                        typename Interval::representation_type>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    typedef typename p1788::util::max_precision_interval_type<
        Interval,
        ConcreteInterval
             >::type Interval_max;

    return Interval(sqr(static_cast<Interval_max>(x)));
}


// sqrt

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sqrt(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sqrt(x.rep_));
}

template<typename Interval, typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
Interval sqrt(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    // assert that Interval is an implementation of base_interval
    static_assert(p1788::util::is_infsup_base_interval_implementation<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    // assert that Interval uses the same flavor
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation,
                        typename Interval::representation_type>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation_dec,
                        typename Interval::representation_type>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    typedef typename p1788::util::max_precision_interval_type<
        Interval,
        ConcreteInterval
             >::type Interval_max;

    return Interval(recip(static_cast<Interval_max>(x)));
}


// fma

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval fma(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                               base_interval<T, Flavor, RepType, ConcreteInterval> const& y,
                               base_interval<T, Flavor, RepType, ConcreteInterval> const& z) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::fma(x.rep_, y.rep_, z.rep_));
}

template<typename Interval, typename T, typename T_y, typename T_z, template<typename> class Flavor,
    typename RepType, class ConcreteInterval, typename RepType_y, class ConcreteInterval_y,
    typename RepType_z, class ConcreteInterval_z>
Interval fma(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
             base_interval<T_y, Flavor, RepType_y, ConcreteInterval_y> const& y,
             base_interval<T_z, Flavor, RepType_z, ConcreteInterval_z> const& z) {
    // assert that Interval is an implementation of base_interval
    static_assert(p1788::util::is_infsup_base_interval_implementation<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    // assert that Interval uses the same flavor
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_y>::representation, RepType_y>::value
                    && std::is_same<typename Flavor<T_z>::representation, RepType_z>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation,
                        typename Interval::representation_type>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T_y>::representation_dec, RepType_y>::value
                    && std::is_same<typename Flavor<T_z>::representation_dec, RepType_z>::value
                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation_dec,
                        typename Interval::representation_type>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    typedef typename p1788::util::max_precision_interval_type<
        Interval,
        ConcreteInterval,
        ConcreteInterval_y
             >::type Interval_max;

    return Interval(fma(static_cast<Interval_max>(x),
                        static_cast<Interval_max>(y),
                        static_cast<Interval_max>(z)));
}


// interval case
//TODO notwendig?
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval interval_case(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
//        base_interval<T, Flavor, RepType, ConcreteInterval> const& g,
//        base_interval<T, Flavor, RepType, ConcreteInterval> const& h) {
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::interval_case(c.rep_,
//                               g.rep_, h.rep_));
//}


// pown

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval pown(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                int p) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::pown(x.rep_, p));
}


// pow

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval pow(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                               base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::pow(x.rep_, y.rep_));
}


// exp

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval exp(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::exp(x.rep_));
}


// exp2

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval exp2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::exp2(x.rep_));
}


// exp10

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval exp10(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::exp10(x.rep_));
}


// log

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval log(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::log(x.rep_));
}


// log2

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval log2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::log2(x.rep_));
}


// log10

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval log10(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::log10(x.rep_));
}


// sin

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sin(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sin(x.rep_));
}


// cos

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval cos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::cos(x.rep_));
}


// tan

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval tan(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::tan(x.rep_));
}


// asin

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval asin(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::asin(x.rep_));
}


// acos

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval acos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::acos(x.rep_));
}


// atan

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval atan(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::atan(x.rep_));
}


// atan2

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval atan2(base_interval<T, Flavor, RepType, ConcreteInterval> const& y,
                                 base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::atan2(y.rep_, x.rep_));
}


// sinh

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sinh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sinh(x.rep_));
}


// cosh

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval cosh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::cosh(x.rep_));
}


// tanh

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval tanh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::tanh(x.rep_));
}


// asinh

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval asinh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::asinh(x.rep_));
}


// acosh

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval acosh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::acosh(x.rep_));
}


// atanh

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval atanh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::atanh(x.rep_));
}


// sign

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sign(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sign(x.rep_));
}


// ceil

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval ceil(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::ceil(x.rep_));
}


// floor

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval floor(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::floor(x.rep_));
}


// trunc

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval trunc(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::trunc(x.rep_));
}


// round_ties_to_even

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval round_ties_to_even(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::round_ties_to_even(x.rep_));
}


// round_ties_to_away

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval round_ties_to_away(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::round_ties_to_away(x.rep_));
}


// abs

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval abs(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::abs(x.rep_));
}


// min

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval min(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::min(x.rep_, y.rep_));
}

// max

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval max(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::max(x.rep_, y.rep_));
}


//@}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_ELEM_FUNC_IMPL_HPP
