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

#ifndef LIBIEEEP1788_P1788_INFSUP_INTERVAL_CANCEL_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_INTERVAL_CANCEL_FUNC_IMPL_HPP

namespace p1788
{

namespace infsup
{



// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
/// \name Cancellative addition and subtraction, see P1788/D7.0 Sect. 9.6.6
///
///@{


// cancel_plus

template<typename T, template<typename> class Flavor>
interval<T, Flavor> cancel_plus(interval<T, Flavor> const& a,
                                       interval<T, Flavor> const& b) {     ///< Required, necessary for bare intervals? see, 11.11.6 // TODO nicht fuer bare interval
    return interval<T, Flavor>(Flavor<T>::cancel_plus(a.rep_, b.rep_));
}

//template<typename Interval, typename T, typename Tb, template<typename> class Flavor>
//Interval cancel_plus(interval<T, Flavor> const& a,
//                            interval<Tb, Flavor> const& b) {
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
//             Tb
//             >::type TMax;
//
//    return Interval(cancel_plus(static_cast<interval<TMax, Flavor>>(a),
//                                static_cast<interval<TMax, Flavor>>(b)));
//}


// cancel_minus

template<typename T, template<typename> class Flavor>
interval<T, Flavor> cancel_minus(interval<T, Flavor> const& a,
                                        interval<T, Flavor> const& b) {    ///< Required, necessary for bare intervals? see, 11.11.6 // TODO nicht fuer bare interval
    return interval<T, Flavor>(Flavor<T>::cancel_minus(a.rep_, b.rep_));
}

//template<typename Interval, typename T, typename Tb, template<typename> class Flavor>
//Interval cancel_minus(interval<T, Flavor> const& a,
//                             interval<Tb, Flavor> const& b) {
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
//             Tb
//             >::type TMax;
//
//    return Interval(cancel_minus(static_cast<interval<TMax, Flavor>>(a),
//                                 static_cast<interval<TMax, Flavor>>(b)));
//}

///@}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_INTERVAL_CANCEL_FUNC_IMPL_HPP
