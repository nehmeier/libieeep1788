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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_SET_OP_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_SET_OP_IMPL_HPP

namespace p1788
{

namespace infsup
{


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// \name Non-arithmetic set operations, see P1788/D7.1 Sect. 9.6.7
//
//@{


// \brief Intersection of two intervals <B>x</B> and <B>y</B>
//
// <B>Required by IEEE P1788</B>
//
// The intersection of two intervals <B>x</B>  and <B>y</B> is defined as:
// \f[
//    \mathbf{x} \cap \mathbf{y}
// \f]
//
// The computation is delegated to the static function
// \code
// Flavor<T>::intersect(Flavor<T>::representation const&, Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the intervals.
//
//
// \see #intersect(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
//
// \param x interval
// \param y interval
// \return intersection of <B>x</B>  and <B>y</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval
intersect(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::intersect(x.rep_, y.rep_));
}

// \brief Intersection of two intervals <B>x</B> and <B>y</B>
//
// <B>Mixed type operation of</B> #intersect(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
//
// <B>Required by IEEE P1788</B>
//
// If <TT>Interval</TT> is of type p1788::infsup::interval and the flavor
// of <TT>Interval</TT> is the same as <TT>Flavor</TT> and the number system
// <TT>Ti</TT> of <TT>Interval</TT> as well as
//  <TT>T</TT> and <TT>Ty</TT> are of the same radix, the maximum precision
// <TT>Tmax</TT> of <TT>Ti</TT>, <TT>T</TT> and <TT>Ty</TT> is determined at compile time
// using template meta programming. Then the intervals
// <B>x</B> and <B>y</B> are converted to intervals of type
// <TT>interval<Tmax,Flavor></TT> and are passed to the function
// #intersect(interval<T,Flavor> const& x, interval<T,Flavor> const& y).
// Afterwards the return value of #intersect(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
// is converted to type <TT>Interval</TT>.
//
//template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
//Interval intersect(interval<T, Flavor> const& x,
//                          interval<Ty, Flavor> const& y) {
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
//    return Interval(intersect(static_cast<interval<TMax, Flavor>>(x),
//                              static_cast<interval<TMax, Flavor>>(y)));
//}




// \brief Interval hull of two intervals <B>x</B> and <B>y</B>
//
// <B>Required by IEEE P1788</B>
//
// The interval hull of two intervals <B>x</B>  and <B>y</B> is defined as:
// \f[
//    \operatorname{hull}(\mathbf{x} \cup\mathbf{y})
// \f]
//
// The computation is delegated to the static function
// \code
// Flavor<T>::intersect(Flavor<T>::representation const&, Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the intervals.
//
//
// \see #hull(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
//
// \param x interval
// \param y interval
// \return interval hull of <B>x</B>  and <B>y</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval
hull(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::hull(x.rep_, y.rep_));
}


// \brief Interval hull of two intervals <B>x</B> and <B>y</B>
//
// <B>Mixed type operation of</B> #hull(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
//
// <B>Required by IEEE P1788</B>
//
// If <TT>Interval</TT> is of type p1788::infsup::interval and the flavor
// of <TT>Interval</TT> is the same as <TT>Flavor</TT> and the number system
// <TT>Ti</TT> of <TT>Interval</TT> as well as
//  <TT>T</TT> and <TT>Ty</TT> are of the same radix, the maximum precision
// <TT>Tmax</TT> of <TT>Ti</TT>, <TT>T</TT> and <TT>Ty</TT> is determined at compile time
// using template meta programming. Then the intervals
// <B>x</B> and <B>y</B> are converted to intervals of type
// <TT>interval<Tmax,Flavor></TT> and are passed to the function
// #hull(interval<T,Flavor> const& x, interval<T,Flavor> const& y).
// Afterwards the return value of #hull(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
// is converted to type <TT>Interval</TT>.
//
//template<typename Interval, typename T, typename Ty, template<typename> class Flavor>
//Interval hull(interval<T, Flavor> const& x,
//                     interval<Ty, Flavor> const& y) {
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
//    return Interval(hull(static_cast<interval<TMax, Flavor>>(x),
//                         static_cast<interval<TMax, Flavor>>(y)));
//}

// TODO
//template<typename T, template<typename> class Flavor> interval<T, Flavor> hull(std::initializer_list<T> ilst);           //< interval hull, see P1788/D7.0 Sect. 11.8.1
// TODO: Mixed type operation


//@}



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_SET_OP_IMPL_HPP
