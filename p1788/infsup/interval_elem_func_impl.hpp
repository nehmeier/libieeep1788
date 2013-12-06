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

namespace p1788
{

namespace infsup
{


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
/// \name Forward elementary functions
///
///@{


// pos

/// \brief Identity of an interval <B>x</B>
///
/// <B>Implementation specific</B>
///
/// Only provided for consistency with #neg(interval<T,Flavor> const& x).
///
/// \see #neg(interval<T,Flavor> const& x)
/// \see #operator+(interval<T,Flavor> const& x)
///
/// \param x interval
/// \return <B>x</B>
///
template<typename T, template<typename> class Flavor>
interval<T, Flavor> pos(interval<T, Flavor> const& x) {
    return x;
}

/// \brief Identity of an interval <B>x</B>
///
/// <B>Short hand of</B> #pos(interval<T,Flavor> const& x)
///
/// <B>Implementation specific</B>
///
template<typename T, template<typename> class Flavor>
interval<T, Flavor> operator+(interval<T, Flavor> const& x) {
    return pos(x);
}


// neg

/// \brief Negation of an interval <B>x</B>
///
/// <B>Required by IEEE P1788</B>
///
///
/// \see #operator-(interval<T,Flavor> const& x)
/// \see #pos(interval<T,Flavor> const& x)
///
/// \param x interval
/// \return -<B>x</B>
///
template<typename T, template<typename> class Flavor>
interval<T, Flavor> neg(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::neg(x.rep_));
}

/// \brief Negation of an interval <B>x</B>
///
/// <B>Short hand of</B> #neg(interval<T,Flavor> const& x)
///
/// <B>Implementation specific</B>
///
template<typename T, template<typename> class Flavor>
interval<T, Flavor> operator-(interval<T, Flavor> const& x) {
    return neg(x);
}


// add

template<typename T, template<typename> class Flavor>
interval<T, Flavor> add (interval<T, Flavor> const& x,
                                interval<T, Flavor> const& y) {
    return interval<T, Flavor>(Flavor<T>::add(x.rep_, y.rep_));
}

template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
Interval add(interval<T, Flavor> const& x,
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

template<typename T, template<typename> class Flavor>
interval<T, Flavor> operator+(interval<T, Flavor> const& x,
                                     interval<T, Flavor> const& y) {
    return add(x, y);
}


// sub

template<typename T, template<typename> class Flavor>
interval<T, Flavor> sub(interval<T, Flavor> const& x,
                               interval<T, Flavor> const& y) {
    return interval<T, Flavor>(Flavor<T>::sub(x.rep_, y.rep_));
}

template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
Interval sub(interval<T, Flavor> const& x,
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

template<typename T, template<typename> class Flavor>
interval<T, Flavor> operator-(interval<T, Flavor> const& x,
                                     interval<T, Flavor> const& y) {
    return sub(x, y);
}


// mul

template<typename T, template<typename> class Flavor>
interval<T, Flavor> mul(interval<T, Flavor> const& x,
                               interval<T, Flavor> const& y) {
    return interval<T, Flavor>(Flavor<T>::mul(x.rep_, y.rep_));
}

template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
Interval mul(interval<T, Flavor> const& x,
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

template<typename T, template<typename> class Flavor>
interval<T, Flavor> operator*(interval<T, Flavor> const& x,
                                     interval<T, Flavor> const& y) {
    return mul(x, y);
}


// div

template<typename T, template<typename> class Flavor>
interval<T, Flavor> div(interval<T, Flavor> const& x,
                               interval<T, Flavor> const& y) {
    return interval<T, Flavor>(Flavor<T>::div(x.rep_, y.rep_));
}

template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
Interval div(interval<T, Flavor> const& x,
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

template<typename T, template<typename> class Flavor>
interval<T, Flavor> operator/(interval<T, Flavor> const& x,
                                     interval<T, Flavor> const& y) {
    return div(x, y);
}


// recip

template<typename T, template<typename> class Flavor>
interval<T, Flavor> recip(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::recip(x.rep_));
}

template<typename Interval, typename T, template<typename> class Flavor>
Interval recip(interval<T, Flavor> const& x) {
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

    return Interval(recip(static_cast<interval<Tmax, Flavor>>(x)));
}


// sqr

template<typename T, template<typename> class Flavor>
interval<T, Flavor> sqr(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::sqr(x.rep_));
}

template<typename Interval, typename T, template<typename> class Flavor>
Interval sqr(interval<T, Flavor> const& x) {
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


// sqrt

template<typename T, template<typename> class Flavor>
interval<T, Flavor> sqrt(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::sqrt(x.rep_));
}

template<typename Interval, typename T, template<typename> class Flavor>
Interval sqrt(interval<T, Flavor> const& x) {
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

template<typename T, template<typename> class Flavor>
interval<T, Flavor> fma(interval<T, Flavor> const& x,
                               interval<T, Flavor> const& y,
                               interval<T, Flavor> const& z) {
    return interval<T, Flavor>(Flavor<T>::fma(x.rep_, y.rep_, z.rep_));
}

template<typename Interval, typename T, typename Ty, typename Tz, template<typename> class Flavor>
Interval fma(interval<T, Flavor> const& x,
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

template<typename T, template<typename> class Flavor>
interval<T, Flavor> interval_case(interval<T, Flavor> const& c,
        interval<T, Flavor> const& g,
        interval<T, Flavor> const& h) {
    return interval<T, Flavor>(Flavor<T>::interval_case(c.rep_,
                               g.rep_, h.rep_));
}


// pown

template<typename T, template<typename> class Flavor>
interval<T, Flavor> pown(interval<T, Flavor> const& x,
                                int p) {
    return interval<T, Flavor>(Flavor<T>::pown(x.rep_, p));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval pown(interval<T, Flavor> const& x,
//                     int p) {
//    static_assert(p1788::util::is_infsup_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T
//             >::type Tmax;
//
//    return Interval(pown(static_cast<interval<Tmax, Flavor>>(x), p));
//}


// pow

template<typename T, template<typename> class Flavor>
interval<T, Flavor> pow(interval<T, Flavor> const& x,
                               interval<T, Flavor> const& y) {
    return interval<T, Flavor>(Flavor<T>::pow(x.rep_, y.rep_));
}


// exp

template<typename T, template<typename> class Flavor>
interval<T, Flavor> exp(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::exp(x.rep_));
}


// exp2

template<typename T, template<typename> class Flavor>
interval<T, Flavor> exp2(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::exp2(x.rep_));
}


// exp10

template<typename T, template<typename> class Flavor>
interval<T, Flavor> exp10(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::exp10(x.rep_));
}


// log

template<typename T, template<typename> class Flavor>
interval<T, Flavor> log(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::log(x.rep_));
}


// log2

template<typename T, template<typename> class Flavor>
interval<T, Flavor> log2(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::log2(x.rep_));
}


// log10

template<typename T, template<typename> class Flavor>
interval<T, Flavor> log10(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::log10(x.rep_));
}


// sin

template<typename T, template<typename> class Flavor>
interval<T, Flavor> sin(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::sin(x.rep_));
}


// cos

template<typename T, template<typename> class Flavor>
interval<T, Flavor> cos(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::cos(x.rep_));
}


// tan

template<typename T, template<typename> class Flavor>
interval<T, Flavor> tan(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::tan(x.rep_));
}


// asin

template<typename T, template<typename> class Flavor>
interval<T, Flavor> asin(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::asin(x.rep_));
}


// acos

template<typename T, template<typename> class Flavor>
interval<T, Flavor> acos(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::acos(x.rep_));
}


// atan

template<typename T, template<typename> class Flavor>
interval<T, Flavor> atan(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::atan(x.rep_));
}


// atan2

template<typename T, template<typename> class Flavor>
interval<T, Flavor> atan2(interval<T, Flavor> const& y,
                                 interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::atan2(y.rep_, x.rep_));
}


// sinh

template<typename T, template<typename> class Flavor>
interval<T, Flavor> sinh(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::sinh(x.rep_));
}


// cosh

template<typename T, template<typename> class Flavor>
interval<T, Flavor> cosh(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::cosh(x.rep_));
}


// tanh

template<typename T, template<typename> class Flavor>
interval<T, Flavor> tanh(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::tanh(x.rep_));
}


// asinh

template<typename T, template<typename> class Flavor>
interval<T, Flavor> asinh(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::asinh(x.rep_));
}


// acosh

template<typename T, template<typename> class Flavor>
interval<T, Flavor> acosh(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::acosh(x.rep_));
}


// atanh

template<typename T, template<typename> class Flavor>
interval<T, Flavor> atanh(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::atanh(x.rep_));
}


// sign

template<typename T, template<typename> class Flavor>
interval<T, Flavor> sign(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::sign(x.rep_));
}


// ceil

template<typename T, template<typename> class Flavor>
interval<T, Flavor> ceil(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::ceil(x.rep_));
}


// floor

template<typename T, template<typename> class Flavor>
interval<T, Flavor> floor(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::floor(x.rep_));
}


// trunc

template<typename T, template<typename> class Flavor>
interval<T, Flavor> trunc(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::trunc(x.rep_));
}


// round_ties_to_even

template<typename T, template<typename> class Flavor>
interval<T, Flavor> round_ties_to_even(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::round_ties_to_even(x.rep_));
}


// round_ties_to_away

template<typename T, template<typename> class Flavor>
interval<T, Flavor> round_ties_to_away(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::round_ties_to_away(x.rep_));
}


// abs

template<typename T, template<typename> class Flavor>
interval<T, Flavor> abs(interval<T, Flavor> const& x) {
    return interval<T, Flavor>(Flavor<T>::abs(x.rep_));
}


// min

template<typename T, template<typename> class Flavor>
interval<T, Flavor> min(interval<T, Flavor> const& x, interval<T, Flavor> const& y) {
    return interval<T, Flavor>(Flavor<T>::min(x.rep_, y.rep_));
}

// max

template<typename T, template<typename> class Flavor>
interval<T, Flavor> max(interval<T, Flavor> const& x, interval<T, Flavor> const& y) {
    return interval<T, Flavor>(Flavor<T>::max(x.rep_, y.rep_));
}


///@}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_INTERVAL_ELEM_FUNC_IMPL_HPP
