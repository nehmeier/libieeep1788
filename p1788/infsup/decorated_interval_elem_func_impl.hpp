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

#ifndef LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_ELEM_FUNC_IMPL_HPP

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
/// Only provided for consistency with #neg(decorated_interval<T,Flavor> const& x).
///
/// \see #neg(decorated_interval<T,Flavor> const& x)
/// \see #operator+(decorated_interval<T,Flavor> const& x)
///
/// \param x interval
/// \return <B>x</B>
///
template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> pos(decorated_interval<T, Flavor> const& x) {
    return x;
}

/// \brief Identity of an interval <B>x</B>
///
/// <B>Short hand of</B> #pos(interval<T,Flavor> const& x)
///
/// <B>Implementation specific</B>
///
template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> operator+(decorated_interval<T, Flavor> const& x) {
    return pos(x);
}


// neg

/// \brief Negation of an interval <B>x</B>
///
/// <B>Required by IEEE P1788</B>
///
///
/// \see #operator-(interval<T,Flavor> const& x)
/// \see #pos(decorated_interval<T,Flavor> const& x)
///
/// \param x interval
/// \return -<B>x</B>
///
template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> neg(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::neg_dec(x.rep_));
}

/// \brief Negation of an interval <B>x</B>
///
/// <B>Short hand of</B> #neg(decorated_interval<T,Flavor> const& x)
///
/// <B>Implementation specific</B>
///
template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> operator-(decorated_interval<T, Flavor> const& x) {
    return neg(x);
}


// add

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> add (decorated_interval<T, Flavor> const& x,
                                decorated_interval<T, Flavor> const& y) {
    return decorated_interval<T, Flavor>(Flavor<T>::add_dec(x.rep_, y.rep_));
}

template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
Interval add(decorated_interval<T, Flavor> const& x,
                    decorated_interval<Ty, Flavor> const& y) {
    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
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

    return Interval(add(static_cast<decorated_interval<Tmax, Flavor>>(x),
                        static_cast<decorated_interval<Tmax, Flavor>>(y)));
}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> operator+(decorated_interval<T, Flavor> const& x,
                                     decorated_interval<T, Flavor> const& y) {
    return add(x, y);
}


// sub

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> sub(decorated_interval<T, Flavor> const& x,
                               decorated_interval<T, Flavor> const& y) {
    return decorated_interval<T, Flavor>(Flavor<T>::sub_dec(x.rep_, y.rep_));
}

template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
Interval sub(decorated_interval<T, Flavor> const& x,
                    decorated_interval<Ty, Flavor> const& y) {
    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
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

    return Interval(sub(static_cast<decorated_interval<Tmax, Flavor>>(x),
                        static_cast<decorated_interval<Tmax, Flavor>>(y)));
}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> operator-(decorated_interval<T, Flavor> const& x,
                                     decorated_interval<T, Flavor> const& y) {
    return sub(x, y);
}


// mul

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> mul(decorated_interval<T, Flavor> const& x,
                               decorated_interval<T, Flavor> const& y) {
    return decorated_interval<T, Flavor>(Flavor<T>::mul_dec(x.rep_, y.rep_));
}

template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
Interval mul(decorated_interval<T, Flavor> const& x,
                    decorated_interval<Ty, Flavor> const& y) {
    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
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

    return Interval(mul(static_cast<decorated_interval<Tmax, Flavor>>(x),
                        static_cast<decorated_interval<Tmax, Flavor>>(y)));
}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> operator*(decorated_interval<T, Flavor> const& x,
                                     decorated_interval<T, Flavor> const& y) {
    return mul(x, y);
}


// div

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> div(decorated_interval<T, Flavor> const& x,
                               decorated_interval<T, Flavor> const& y) {
    return decorated_interval<T, Flavor>(Flavor<T>::div_dec(x.rep_, y.rep_));
}

template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
Interval div(decorated_interval<T, Flavor> const& x,
                    decorated_interval<Ty, Flavor> const& y) {
    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
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

    return Interval(div(static_cast<decorated_interval<Tmax, Flavor>>(x),
                        static_cast<decorated_interval<Tmax, Flavor>>(y)));
}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> operator/(decorated_interval<T, Flavor> const& x,
                                     decorated_interval<T, Flavor> const& y) {
    return div(x, y);
}


// recip

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> recip(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::recip_dec(x.rep_));
}

template<typename Interval, typename T, template<typename> class Flavor>
Interval recip(decorated_interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
             T
             >::type Tmax;

    return Interval(recip(static_cast<decorated_interval<Tmax, Flavor>>(x)));
}


// sqr

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> sqr(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::sqr_dec(x.rep_));
}

template<typename Interval, typename T, template<typename> class Flavor>
Interval sqr(decorated_interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
             T
             >::type Tmax;

    return Interval(sqr(static_cast<decorated_interval<Tmax, Flavor>>(x)));
}


// sqrt

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> sqrt(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::sqrt_dec(x.rep_));
}

template<typename Interval, typename T, template<typename> class Flavor>
Interval sqrt(decorated_interval<T, Flavor> const& x) {
    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
                  "Return type is not supported by mixed type operations!");
    static_assert(std::is_same<typename Interval::flavor_type,
                  Flavor<typename Interval::bound_type>>::value,
                  "Different flavors are not supported by "
                  "mixed type operations!");

    typedef typename p1788::util::max_precision_type<
    typename Interval::bound_type,
             T
             >::type Tmax;

    return Interval(sqrt(static_cast<decorated_interval<Tmax, Flavor>>(x)));
}


// fma

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> fma(decorated_interval<T, Flavor> const& x,
                               decorated_interval<T, Flavor> const& y,
                               decorated_interval<T, Flavor> const& z) {
    return decorated_interval<T, Flavor>(Flavor<T>::fma_dec(x.rep_, y.rep_, z.rep_));
}

template<typename Interval, typename T, typename Ty, typename Tz, template<typename> class Flavor>
Interval fma(decorated_interval<T, Flavor> const& x,
                    decorated_interval<Ty, Flavor> const& y,
                    decorated_interval<Tz, Flavor> const& z) {
    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
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

    return Interval(fma(static_cast<decorated_interval<Tmax, Flavor>>(x),
                        static_cast<decorated_interval<Tmax, Flavor>>(y),
                        static_cast<decorated_interval<Tmax, Flavor>>(z)));
}


// interval case

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> interval_case(decorated_interval<T, Flavor> const& c,
        decorated_interval<T, Flavor> const& g,
        decorated_interval<T, Flavor> const& h) {
    return decorated_interval<T, Flavor>(Flavor<T>::interval_case_dec(c.rep_,
                               g.rep_, h.rep_));
}


// pown

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> pown(decorated_interval<T, Flavor> const& x,
                                int p) {
    return decorated_interval<T, Flavor>(Flavor<T>::pown_dec(x.rep_, p));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval pown(decorated_interval<T, Flavor> const& x,
//                     int p) {
//    static_assert(p1788::util::is_infsup_decorated_interval<Interval>::value,
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
//    return Interval(pown(static_cast<decorated_interval<Tmax, Flavor>>(x), p));
//}


// pow

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> pow(decorated_interval<T, Flavor> const& x,
                               decorated_interval<T, Flavor> const& y) {
    return decorated_interval<T, Flavor>(Flavor<T>::pow_dec(x.rep_, y.rep_));
}


// exp

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> exp(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::exp_dec(x.rep_));
}


// exp2

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> exp2(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::exp2_dec(x.rep_));
}


// exp10

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> exp10(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::exp10_dec(x.rep_));
}


// log

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> log(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::log_dec(x.rep_));
}


// log2

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> log2(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::log2_dec(x.rep_));
}


// log10

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> log10(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::log10_dec(x.rep_));
}


// sin

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> sin(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::sin_dec(x.rep_));
}


// cos

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> cos(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::cos_dec(x.rep_));
}


// tan

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> tan(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::tan_dec(x.rep_));
}


// asin

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> asin(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::asin_dec(x.rep_));
}


// acos

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> acos(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::acos_dec(x.rep_));
}


// atan

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> atan(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::atan_dec(x.rep_));
}


// atan2

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> atan2(decorated_interval<T, Flavor> const& y,
                                 decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::atan2_dec(y.rep_, x.rep_));
}


// sinh

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> sinh(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::sinh_dec(x.rep_));
}


// cosh

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> cosh(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::cosh_dec(x.rep_));
}


// tanh

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> tanh(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::tanh_dec(x.rep_));
}


// asinh

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> asinh(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::asinh_dec(x.rep_));
}


// acosh

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> acosh(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::acosh_dec(x.rep_));
}


// atanh

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> atanh(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::atanh_dec(x.rep_));
}


// sign

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> sign(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::sign_dec(x.rep_));
}


// ceil

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> ceil(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::ceil_dec(x.rep_));
}


// floor

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> floor(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::floor_dec(x.rep_));
}


// trunc

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> trunc(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::trunc_dec(x.rep_));
}


// round_ties_to_even

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> round_ties_to_even(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::round_ties_to_even_dec(x.rep_));
}


// round_ties_to_away

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> round_ties_to_away(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::round_ties_to_away_dec(x.rep_));
}


// abs

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> abs(decorated_interval<T, Flavor> const& x) {
    return decorated_interval<T, Flavor>(Flavor<T>::abs_dec(x.rep_));
}


// min

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> min(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return decorated_interval<T, Flavor>(Flavor<T>::min_dec(x.rep_, y.rep_));
}

// max

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> max(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return decorated_interval<T, Flavor>(Flavor<T>::max_dec(x.rep_, y.rep_));
}


///@}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_ELEM_FUNC_IMPL_HPP
