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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REC_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REC_ELEM_FUNC_IMPL_HPP

namespace p1788
{

namespace infsup
{


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// \name Recommended forward elementary functions on intervals, see P1788/D7.0 Sect. 9.7.1 Table 5
//
//@{


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval rootn(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, int n) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::rootn(x.rep_, n));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval rootn(interval<T, Flavor> const& x, int n) {
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
//             >::type TMax;
//
//    return Interval(rootn(static_cast<interval<TMax, Flavor>>(x), n));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval expm1(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::expm1(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval expm1(interval<T, Flavor> const& x) {
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
//             >::type TMax;
//
//    return Interval(expm1(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval exp2m1(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::exp2m1(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval exp2m1(interval<T, Flavor> const& x) {
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
//             >::type TMax;
//
//    return Interval(exp2m1(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval exp10m1(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::exp10m1(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval exp10m1(interval<T, Flavor> const& x) {
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
//             >::type TMax;
//
//    return Interval(exp10m1(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval logp1(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::logp1(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval logp1(interval<T, Flavor> const& x) {
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
//             >::type TMax;
//
//    return Interval(logp1(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval log2p1(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::log2p1(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval log2p1(interval<T, Flavor> const& x) {
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
//             >::type TMax;
//
//    return Interval(log2p1(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval log10p1(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::log10p1(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval log10p1(interval<T, Flavor> const& x) {
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
//             >::type TMax;
//
//    return Interval(log10p1(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval compoundm1(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                      base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::compoundm1(x.rep_, y.rep_));
}

//template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
//Interval compoundm1(interval<T, Flavor> const& x,
//                           interval<Ty, Flavor> const& y) {
//    static_assert(p1788::util::is_infsup_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T,
//             Ty
//             >::type TMax;
//
//    return Interval(compoundm1(static_cast<interval<TMax, Flavor>>(x),
//                               static_cast<interval<TMax, Flavor>>(y)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval hypot(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                 base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {   //< tightest, required or recommended?
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::hypot(x.rep_, y.rep_));
}

//template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
//Interval hypot(interval<T, Flavor> const& x,
//                      interval<Ty, Flavor> const& y) {
//    static_assert(p1788::util::is_infsup_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T,
//             Ty
//             >::type TMax;
//
//    return Interval(hypot(static_cast<interval<TMax, Flavor>>(x),
//                          static_cast<interval<TMax, Flavor>>(y)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval r_sqrt(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::r_sqrt(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval r_sqrt(interval<T, Flavor> const& x) {
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
//             >::type TMax;
//
//    return Interval(r_sqrt(static_cast<interval<TMax, Flavor>>(x)));
//}


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sin_pi(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sin_pi(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval sin_pi(interval<T, Flavor> const& x) {
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
//             >::type TMax;
//
//    return Interval(sin_pi(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval cos_pi(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::cos_pi(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval cos_pi(interval<T, Flavor> const& x) {
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
//             >::type TMax;
//
//    return Interval(cos_pi(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval tan_pi(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::tan_pi(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval tan_pi(interval<T, Flavor> const& x) {
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
//             >::type TMax;
//
//    return Interval(tan_pi(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval asin_pi(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::asin_pi(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval asin_pi(interval<T, Flavor> const& x) {
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
//             >::type TMax;
//
//    return Interval(asin_pi(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval acos_pi(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::acos_pi(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval acos_pi(interval<T, Flavor> const& x) {
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
//             >::type TMax;
//
//    return Interval(acos_pi(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval atan_pi(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::atan_pi(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval atan_pi(interval<T, Flavor> const& x) {
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
//             >::type TMax;
//
//    return Interval(atan_pi(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval atan2_pi(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                                    base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::atan2_pi(x.rep_, y.rep_));
}

//template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
//Interval atan2_pi(interval<T, Flavor> const& x,
//                         interval<Ty, Flavor> const& y) {
//    static_assert(p1788::util::is_infsup_interval<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//
//    typedef typename p1788::util::max_precision_type<
//    typename Interval::bound_type,
//             T,
//             Ty
//             >::type TMax;
//
//    return Interval(atan2_pi(static_cast<interval<TMax, Flavor>>(x),
//                             static_cast<interval<TMax, Flavor>>(y)));
//}

//@}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REC_ELEM_FUNC_IMPL_HPP
