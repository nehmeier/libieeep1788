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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REC_SLOPE_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REC_SLOPE_FUNC_IMPL_HPP

namespace p1788
{

namespace infsup
{

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// \name Recommended slope functions, see P1788/D7.0 Sect. 9.7.3 Table 7
//
//@{


template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval exp_slope1(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::exp_slope1(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval exp_slope1(interval<T, Flavor> const& x) {
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
//    return Interval(exp_slope1(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval exp_slope2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::exp_slope2(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval exp_slope2(interval<T, Flavor> const& x) {
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
//    return Interval(exp_slope2(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval log_slope1(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::log_slope1(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval log_slope1(interval<T, Flavor> const& x) {
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
//    return Interval(log_slope1(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval log_slope2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::log_slope2(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval log_slope2(interval<T, Flavor> const& x) {
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
//    return Interval(log_slope2(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval cos_slope2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::cos_slope2(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval cos_slope2(interval<T, Flavor> const& x) {
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
//    return Interval(cos_slope2(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sin_slope3(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sin_slope3(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval sin_slope3(interval<T, Flavor> const& x) {
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
//    return Interval(sin_slope3(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval asin_slope3(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::asin_slope3(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval asin_slope3(interval<T, Flavor> const& x) {
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
//    return Interval(asin_slope3(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval atan_slope3(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::atan_slope3(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval atan_slope3(interval<T, Flavor> const& x) {
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
//    return Interval(atan_slope3(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval cosh_slope2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::cosh_slope2(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval cosh_slope2(interval<T, Flavor> const& x) {
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
//    return Interval(cosh_slope2(static_cast<interval<TMax, Flavor>>(x)));
//}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sinh_slope3(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sinh_slope3(x.rep_));
}

//template<typename Interval, typename T, template<typename> class Flavor>
//Interval sinh_slope3(interval<T, Flavor> const& x) {
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
//    return Interval(sinh_slope3(static_cast<interval<TMax, Flavor>>(x)));
//}

//@}



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REC_SLOPE_FUNC_IMPL_HPP
