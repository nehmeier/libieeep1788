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

#ifndef LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_BOOL_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_BOOL_FUNC_IMPL_HPP

namespace p1788
{

namespace infsup
{

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
/// \name Boolean functions on intervals, see P1788/D7.0 Sect. 9.6.10
///
///@{


/// \brief Check if an interval <B>x</B> is the empty set
///
/// <B>Required by IEEE P1788</B>
///
/// The computation is delegated to the static function
/// \code
/// Flavor<T>::is_empty(Flavor<T>::representation const&)
/// \endcode
/// of the policy class <TT>Flavor<T></TT> by passing only the internal
/// representation of the interval.
///
/// \param x   interval
/// \retval true    <B>x</B> is the empty set
/// \retval false   otherwise
///
template<typename T, template<typename> class Flavor>
bool is_empty(decorated_interval<T, Flavor> const& x) {
    return Flavor<T>::is_empty_dec(x.rep_);
}




/// \brief Check if an interval <B>x</B> is the whole line
///
/// <B>Required by IEEE P1788</B>
///
/// The computation is delegated to the static function
/// \code
/// Flavor<T>::is_entire(Flavor<T>::representation const&)
/// \endcode
/// of the policy class <TT>Flavor<T></TT> by passing only the internal
/// representation of the interval.
///
/// \param x interval
/// \retval true    <B>x</B> is the whole line
/// \retval false   otherwise
///
template<typename T, template<typename> class Flavor>
bool is_entire(decorated_interval<T, Flavor> const& x) {
    return Flavor<T>::is_entire_dec(x.rep_);
}




/// \brief Check if two intervals <B>x</B> and <B>y</B> are equal
///
/// <B>Required by IEEE P1788</B>
///
/// Two intervals <B>x</B> and <B>y</B> are equal if the condition
/// \f[
///     \forall_{x \in \mathbf{x}}\exists_{y \in \mathbf{y}} \, x = y  \,
///     \wedge \, \forall_{y \in \mathbf{y}}\exists_{x \in \mathbf{x}} \, y = x
/// \f]
/// is fulfilled.
///
/// The computation is delegated to the static function
/// \code
/// Flavor<T>::is_equal(Flavor<T>::representation const&, Flavor<T>::representation const&)
/// \endcode
/// of the policy class <TT>Flavor<T></TT> by passing only the internal
/// representation of the intervals.
///
///
/// \see #is_equal(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
///
/// \param x interval
/// \param y interval
/// \retval true    <B>x</B> and <B>y</B> are equal
/// \retval false   otherwise
///
template<typename T, template<typename> class Flavor>
bool is_equal(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return Flavor<T>::is_equal_dec(x.rep_, y.rep_);
}

/// \brief Check if two intervals <B>x</B> and <B>y</B> are equal
///
/// <B>Mixed type operation of</B> #is_equal(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Required by IEEE P1788</B>
///
/// If <TT>T</TT> and <TT>Ty</TT> are of the same radix, the maximum precision
/// <TT>Tmax</TT> of <TT>T</TT> and <TT>Ty</TT> is determined at compile time
/// using template meta programming. Then the intervals
/// <B>x</B> and <B>y</B> are converted to intervals of type
/// <TT>interval<Tmax,Flavor></TT> and are passed to the function
/// #is_equal(interval<T,Flavor> const& x, interval<T,Flavor> const& y).
///
template<typename T, typename Ty, template<typename> class Flavor>
bool is_equal(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
    T,
    Ty
    >::type TMax;

    return is_equal(static_cast<decorated_interval<TMax, Flavor>>(x),
                    static_cast<decorated_interval<TMax, Flavor>>(y));
}

/// \brief Check if two intervals <B>x</B> and <B>y</B> are equal
///
/// <B>Short hand of</B> #is_equal(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Implementation specific</B>
///
template<typename T, template<typename> class Flavor>
bool operator==(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return is_equal(x, y);
}

/// \brief Check if two intervals <B>x</B> and <B>y</B> are equal
///
/// <B>Short hand of</B> #is_equal(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
///
/// <B>Implementation specific</B>
///
template<typename T, typename Ty, template<typename> class Flavor>
bool operator==(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    return is_equal(x, y);
}

/// \brief Check if two intervals <B>x</B> and <B>y</B> are <B>not</B> equal
///
/// <B>Short hand of</B> !#is_equal(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Implementation specific</B>
///
template<typename T, template<typename> class Flavor>
bool operator!=(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return !is_equal(x, y);
}

/// \brief Check if two intervals <B>x</B> and <B>y</B> are <B>not</B> equal
///
/// <B>Short hand of</B> !#is_equal(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
///
/// <B>Implementation specific</B>
///
template<typename T, typename Ty, template<typename> class Flavor>
bool operator!=(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    return !is_equal(x, y);
}




/// \brief Check if intervals <B>x</B> is a subset of interval <B>y</B>
///
/// <B>Required by IEEE P1788</B>
///
/// An interval <B>x</B> is a subset of an interval <B>y</B> if the condition
/// \f[
///     \forall_{x \in \mathbf{x}}\exists_{y \in \mathbf{y}} \, x = y
/// \f]
/// is fulfilled.
///
/// The computation is delegated to the static function
/// \code
/// Flavor<T>::contained_in(Flavor<T>::representation const&, Flavor<T>::representation const&)
/// \endcode
/// of the policy class <TT>Flavor<T></TT> by passing only the internal
/// representation of the intervals.
///
///
/// \see #contained_in(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
///
/// \param x interval
/// \param y interval
/// \retval true    <B>x</B> is subset of <B>y</B>
/// \retval false   otherwise
///
template<typename T, template<typename> class Flavor>
bool contained_in(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return Flavor<T>::contained_in_dec(x.rep_, y.rep_);
}

/// \brief Check if intervals <B>x</B> is a subset of interval <B>y</B>
///
/// <B>Mixed type operation of</B> #contained_in(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Required by IEEE P1788</B>
///
/// If <TT>T</TT> and <TT>Ty</TT> are of the same radix, the maximum precision
/// <TT>Tmax</TT> of <TT>T</TT> and <TT>Ty</TT> is determined at compile time
/// using template meta programming. Then the intervals
/// <B>x</B> and <B>y</B> are converted to intervals of type
/// <TT>interval<Tmax,Flavor></TT> and are passed to the function
/// #contained_in(interval<T,Flavor> const& x, interval<T,Flavor> const& y).
///
template<typename T, typename Ty, template<typename> class Flavor>
bool contained_in(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
    T,
    Ty
    >::type TMax;

    return contained_in(static_cast<decorated_interval<TMax, Flavor>>(x),
                        static_cast<decorated_interval<TMax, Flavor>>(y));
}

/// \brief Check if interval <B>x</B> is a superset of interval <B>y</B>
///
/// <B>Calls</B> #contained_in(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
/// <B>with swapped arguments.</B>
///
/// <B>Implementation specific</B>
///
template<typename T, template<typename> class Flavor>
bool contains(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return contained_in(y, x);
}

/// \brief Check if interval <B>x</B> is a superset of interval <B>y</B>
///
/// <B>Mixed type operation of</B> #contains(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Calls</B> #contained_in(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
/// <B>with swapped arguments.</B>
///
/// <B>Implementation specific</B>
///
template<typename T, typename Ty, template<typename> class Flavor>
bool contains(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    return contained_in(y, x);
}




/// \brief Check if intervals <B>x</B> is weakly less then interval <B>y</B>
///
/// <B>Required by IEEE P1788</B>
///
/// An interval <B>x</B> is weakly less then an interval <B>y</B> if the condition
/// \f[
///     \forall_{x \in \mathbf{x}}\exists_{y \in \mathbf{y}} \, x \leq y  \,
///     \wedge \, \forall_{y \in \mathbf{y}}\exists_{x \in \mathbf{x}} \, x \leq y
/// \f]
/// is fulfilled.
///
/// The computation is delegated to the static function
/// \code
/// Flavor<T>::less(Flavor<T>::representation const&, Flavor<T>::representation const&)
/// \endcode
/// of the policy class <TT>Flavor<T></TT> by passing only the internal
/// representation of the intervals.
///
///
/// \see #less(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
///
/// \param x interval
/// \param y interval
/// \retval true    <B>x</B> is weakly less then <B>y</B>
/// \retval false   otherwise
///
template<typename T, template<typename> class Flavor>
bool less(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return Flavor<T>::less_dec(x.rep_, y.rep_);
}

/// \brief Check if intervals <B>x</B> is weakly less then interval <B>y</B>
///
/// <B>Mixed type operation of</B> #less(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Required by IEEE P1788</B>
///
/// If <TT>T</TT> and <TT>Ty</TT> are of the same radix, the maximum precision
/// <TT>Tmax</TT> of <TT>T</TT> and <TT>Ty</TT> is determined at compile time
/// using template meta programming. Then the intervals
/// <B>x</B> and <B>y</B> are converted to intervals of type
/// <TT>interval<Tmax,Flavor></TT> and are passed to the function
/// #less(interval<T,Flavor> const& x, interval<T,Flavor> const& y).
///
template<typename T, typename Ty, template<typename> class Flavor>
bool less(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
    T,
    Ty
    >::type TMax;

    return less(static_cast<decorated_interval<TMax, Flavor>>(x),
                static_cast<decorated_interval<TMax, Flavor>>(y));
}

/// \brief Check if intervals <B>x</B> is weakly greater then interval <B>y</B>
///
/// <B>Calls</B> #less(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
/// <B>with swapped arguments.</B>
///
/// <B>Implementation specific</B>
///
template<typename T, template<typename> class Flavor>
bool greater(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return less(y, x);
}

/// \brief Check if intervals <B>x</B> is weakly greater then interval <B>y</B>
///
/// <B>Mixed type operation of</B> #greater(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Calls</B> #less(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
/// <B>with swapped arguments.</B>
///
/// <B>Implementation specific</B>
///
template<typename T, typename Ty, template<typename> class Flavor>
bool greater(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    return less(y, x);
}




/// \brief Check if intervals <B>x</B> is to left of but may touch interval <B>y</B>
///
/// <B>Required by IEEE P1788</B>
///
/// An interval <B>x</B> is to left of but may touch an interval <B>y</B> if the condition
/// \f[
///     \forall_{x \in \mathbf{x}}\forall_{y \in \mathbf{y}} \, x \leq y
/// \f]
/// is fulfilled.
///
/// The computation is delegated to the static function
/// \code
/// Flavor<T>::precedes(Flavor<T>::representation const&, Flavor<T>::representation const&)
/// \endcode
/// of the policy class <TT>Flavor<T></TT> by passing only the internal
/// representation of the intervals.
///
///
/// \see #precedes(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
///
/// \param x interval
/// \param y interval
/// \retval true    <B>x</B> is to left of but may touch <B>y</B>
/// \retval false   otherwise
///
template<typename T, template<typename> class Flavor>
bool precedes(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return Flavor<T>::precedes_dec(x.rep_, y.rep_);
}

/// \brief Check if intervals <B>x</B> is to left of but may touch interval <B>y</B>
///
/// <B>Mixed type operation of</B> #precedes(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Required by IEEE P1788</B>
///
/// If <TT>T</TT> and <TT>Ty</TT> are of the same radix, the maximum precision
/// <TT>Tmax</TT> of <TT>T</TT> and <TT>Ty</TT> is determined at compile time
/// using template meta programming. Then the intervals
/// <B>x</B> and <B>y</B> are converted to intervals of type
/// <TT>interval<Tmax,Flavor></TT> and are passed to the function
/// #precedes(interval<T,Flavor> const& x, interval<T,Flavor> const& y).
///
template<typename T, typename Ty, template<typename> class Flavor>
bool precedes(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
    T,
    Ty
    >::type TMax;

    return precedes(static_cast<decorated_interval<TMax, Flavor>>(x),
                    static_cast<decorated_interval<TMax, Flavor>>(y));
}

/// \brief Check if intervals <B>x</B> is to right of but may touch interval <B>y</B>
///
/// <B>Calls</B> #precedes(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
/// <B>with swapped arguments.</B>
///
/// <B>Implementation specific</B>
///
template<typename T, template<typename> class Flavor>
bool succeeds(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return precedes(y, x);
}

/// \brief Check if intervals <B>x</B> is to right of but may touch interval <B>y</B>
///
/// <B>Mixed type operation of</B> #succeeds(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Calls</B> #precedes(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
/// <B>with swapped arguments.</B>
///
/// <B>Implementation specific</B>
///
template<typename T, typename Ty, template<typename> class Flavor>
bool succeeds(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    return precedes(y, x);
}


/// \brief Check if intervals <B>x</B> is interior to interval <B>y</B>
///
/// <B>Required by IEEE P1788</B>
///
/// An interval <B>x</B> is interior to an interval <B>y</B> if the condition
/// \f[
///     \forall_{x \in \mathbf{x}}\exists_{y \in \mathbf{y}} \, x < y  \,
///     \wedge \, \forall_{x \in \mathbf{x}}\exists_{y \in \mathbf{y}} \, y < x
/// \f]
/// is fulfilled.
///
/// The computation is delegated to the static function
/// \code
/// Flavor<T>::is_interior(Flavor<T>::representation const&, Flavor<T>::representation const&)
/// \endcode
/// of the policy class <TT>Flavor<T></TT> by passing only the internal
/// representation of the intervals.
///
///
/// \see #is_interior(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
///
/// \param x interval
/// \param y interval
/// \retval true    <B>x</B> is interior to <B>y</B>
/// \retval false   otherwise
///
template<typename T, template<typename> class Flavor>
bool is_interior(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return Flavor<T>::is_interior_dec(x.rep_, y.rep_);
}

/// \brief Check if intervals <B>x</B> is interior to interval <B>y</B>
///
/// <B>Mixed type operation of</B> #is_interior(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Required by IEEE P1788</B>
///
/// If <TT>T</TT> and <TT>Ty</TT> are of the same radix, the maximum precision
/// <TT>Tmax</TT> of <TT>T</TT> and <TT>Ty</TT> is determined at compile time
/// using template meta programming. Then the intervals
/// <B>x</B> and <B>y</B> are converted to intervals of type
/// <TT>interval<Tmax,Flavor></TT> and are passed to the function
/// #is_interior(interval<T,Flavor> const& x, interval<T,Flavor> const& y).
///
template<typename T, typename Ty, template<typename> class Flavor>
bool is_interior(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
    T,
    Ty
    >::type TMax;

    return is_interior(static_cast<decorated_interval<TMax, Flavor>>(x),
                       static_cast<decorated_interval<TMax, Flavor>>(y));
}

/// \brief Check if intervals <B>x</B> contains interval <B>y</B> in the interior
///
/// <B>Calls</B> #is_interior(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
/// <B>with swapped arguments.</B>
///
/// <B>Implementation specific</B>
///
template<typename T, template<typename> class Flavor>
bool contains_interior(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return is_interior(y, x);
}

/// \brief Check if intervals <B>x</B> contains interval <B>y</B> in the interior
///
/// <B>Mixed type operation of</B> #contains_interior(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Calls</B> #is_interior(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
/// <B>with swapped arguments.</B>
///
/// <B>Implementation specific</B>
///
template<typename T, typename Ty, template<typename> class Flavor>
bool contains_interior(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    return is_interior(y, x);
}




/// \brief Check if intervals <B>x</B> is strictly less then interval <B>y</B>
///
/// <B>Required by IEEE P1788</B>
///
/// An interval <B>x</B> is strictly less then an interval <B>y</B> if the condition
/// \f[
///     \forall_{x \in \mathbf{x}}\exists_{y \in \mathbf{y}} \, x < y  \,
///     \wedge \, \forall_{y \in \mathbf{y}}\exists_{x \in \mathbf{x}} \, x < y
/// \f]
/// is fulfilled.
///
/// The computation is delegated to the static function
/// \code
/// Flavor<T>::strictly_less(Flavor<T>::representation const&, Flavor<T>::representation const&)
/// \endcode
/// of the policy class <TT>Flavor<T></TT> by passing only the internal
/// representation of the intervals.
///
///
/// \see #strictly_less(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
///
/// \param x interval
/// \param y interval
/// \retval true    <B>x</B> is strictly less then <B>y</B>
/// \retval false   otherwise
///
template<typename T, template<typename> class Flavor>
bool strictly_less(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return Flavor<T>::strictly_less_dec(x.rep_, y.rep_);
}

/// \brief Check if intervals <B>x</B> is strictly less then interval <B>y</B>
///
/// <B>Mixed type operation of</B> #strictly_less(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Required by IEEE P1788</B>
///
/// If <TT>T</TT> and <TT>Ty</TT> are of the same radix, the maximum precision
/// <TT>Tmax</TT> of <TT>T</TT> and <TT>Ty</TT> is determined at compile time
/// using template meta programming. Then the intervals
/// <B>x</B> and <B>y</B> are converted to intervals of type
/// <TT>interval<Tmax,Flavor></TT> and are passed to the function
/// #strictly_less(interval<T,Flavor> const& x, interval<T,Flavor> const& y).
///
template<typename T, typename Ty, template<typename> class Flavor>
bool strictly_less(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
    T,
    Ty
    >::type TMax;

    return strictly_less(static_cast<decorated_interval<TMax, Flavor>>(x),
                         static_cast<decorated_interval<TMax, Flavor>>(y));
}

/// \brief Check if intervals <B>x</B> is strictly greater then interval <B>y</B>
///
/// <B>Calls</B> #strictly_less(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
/// <B>with swapped arguments.</B>
///
/// <B>Implementation specific</B>
///
template<typename T, template<typename> class Flavor>
bool strictly_greater(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return strictly_less(y, x);
}

/// \brief Check if intervals <B>x</B> is strictly greater then interval <B>y</B>
///
/// <B>Mixed type operation of</B> #strictly_greater(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Calls</B> #strictly_less(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
/// <B>with swapped arguments.</B>
///
/// <B>Implementation specific</B>
///
template<typename T, typename Ty, template<typename> class Flavor>
bool strictly_greater(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    return strictly_less(y, x);
}




/// \brief Check if intervals <B>x</B> is strictly to left of interval <B>y</B>
///
/// <B>Required by IEEE P1788</B>
///
/// An interval <B>x</B> is strictly to left of an interval <B>y</B> if the condition
/// \f[
///     \forall_{x \in \mathbf{x}}\forall_{y \in \mathbf{y}} \, x < y
/// \f]
/// is fulfilled.
///
/// The computation is delegated to the static function
/// \code
/// Flavor<T>::strictly_precedes(Flavor<T>::representation const&, Flavor<T>::representation const&)
/// \endcode
/// of the policy class <TT>Flavor<T></TT> by passing only the internal
/// representation of the intervals.
///
///
/// \see #strictly_precedes(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
///
/// \param x interval
/// \param y interval
/// \retval true    <B>x</B> is strictly to left of <B>y</B>
/// \retval false   otherwise
///
template<typename T, template<typename> class Flavor>
bool strictly_precedes(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return Flavor<T>::strictly_precedes_dec(x.rep_, y.rep_);
}

/// \brief Check if intervals <B>x</B> is strictly to left of interval <B>y</B>
///
/// <B>Mixed type operation of</B> #strictly_precedes(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Required by IEEE P1788</B>
///
/// If <TT>T</TT> and <TT>Ty</TT> are of the same radix, the maximum precision
/// <TT>Tmax</TT> of <TT>T</TT> and <TT>Ty</TT> is determined at compile time
/// using template meta programming. Then the intervals
/// <B>x</B> and <B>y</B> are converted to intervals of type
/// <TT>interval<Tmax,Flavor></TT> and are passed to the function
/// #strictly_precedes(interval<T,Flavor> const& x, interval<T,Flavor> const& y).
///
template<typename T, typename Ty, template<typename> class Flavor>
bool strictly_precedes(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
    T,
    Ty
    >::type TMax;

    return strictly_precedes(static_cast<decorated_interval<TMax, Flavor>>(x),
                             static_cast<decorated_interval<TMax, Flavor>>(y));
}

/// \brief Check if intervals <B>x</B> is strictly to right of interval <B>y</B>
///
/// <B>Calls</B> #strictly_precedes(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
/// <B>with swapped arguments.</B>
///
/// <B>Implementation specific</B>
///
template<typename T, template<typename> class Flavor>
bool strictly_succeeds(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return strictly_precedes(y, x);
}

/// \brief Check if intervals <B>x</B> is strictly to right of interval <B>y</B>
///
/// <B>Mixed type operation of</B> #strictly_succeeds(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Calls</B> #strictly_precedes(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
/// <B>with swapped arguments.</B>
///
/// <B>Implementation specific</B>
///
template<typename T, typename Ty, template<typename> class Flavor>
bool strictly_succeeds(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    return strictly_precedes(y, x);
}




/// \brief Check if intervals <B>x</B> and interval <B>y</B> are disjoint
///
/// <B>Required by IEEE P1788</B>
///
/// The intervals <B>x</B> and <B>y</B> are disjoint if the condition
/// \f[
///     \forall_{x \in \mathbf{x}}\forall_{y \in \mathbf{y}} \, x \not= y
/// \f]
/// is fulfilled.
///
/// The computation is delegated to the static function
/// \code
/// Flavor<T>::are_disjoint(Flavor<T>::representation const&, Flavor<T>::representation const&)
/// \endcode
/// of the policy class <TT>Flavor<T></TT> by passing only the internal
/// representation of the intervals.
///
///
/// \see #are_disjoint(interval<T,Flavor> const& x, interval<Ty,Flavor> const& y)
///
/// \param x interval
/// \param y interval
/// \retval true    <B>x</B> and <B>y</B> are disjoint
/// \retval false   otherwise
///
template<typename T, template<typename> class Flavor>
bool are_disjoint(decorated_interval<T, Flavor> const& x, decorated_interval<T, Flavor> const& y) {
    return Flavor<T>::are_disjoint_dec(x.rep_, y.rep_);
}

/// \brief Check if intervals <B>x</B> and interval <B>y</B> are disjoint
///
/// <B>Mixed type operation of</B> #are_disjoint(interval<T,Flavor> const& x, interval<T,Flavor> const& y)
///
/// <B>Required by IEEE P1788</B>
///
/// If <TT>T</TT> and <TT>Ty</TT> are of the same radix, the maximum precision
/// <TT>Tmax</TT> of <TT>T</TT> and <TT>Ty</TT> is determined at compile time
/// using template meta programming. Then the intervals
/// <B>x</B> and <B>y</B> are converted to intervals of type
/// <TT>interval<Tmax,Flavor></TT> and are passed to the function
/// #are_disjoint(interval<T,Flavor> const& x, interval<T,Flavor> const& y).
///
template<typename T, typename Ty, template<typename> class Flavor>
bool are_disjoint(decorated_interval<T, Flavor> const& x, decorated_interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
    T,
    Ty
    >::type TMax;

    return are_disjoint(static_cast<decorated_interval<TMax, Flavor>>(x),
                        static_cast<decorated_interval<TMax, Flavor>>(y));
}


///@}



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_BOOL_FUNC_IMPL_HPP
