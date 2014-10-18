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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_NUM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_NUM_FUNC_IMPL_HPP

namespace p1788
{

namespace infsup
{

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// \name Numeric functions on intervals, see P1788/D7.1 Sect. 9.6.9
//
//@{

// \brief Infimum of an interval <B>x</B>
//
// <B>Required by IEEE P1788</B>
//
// The infimum of an interval <B>x</B> is defined as:
// \f[
//    \operatorname{inf}(\mathbf{x}) = \begin{cases}
//        \underline{x} & \text{if } \mathbf{x} \text{ is nonempty} \br
//        +\infty & \text{if } \mathbf{x} \text{ is empty}
//    \end{cases}
// \f]
//
// The computation is delegated to the static function
// \code
// Flavor<T>::inf(Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the interval.
//
//
// \see interval<T,Flavor>.lower()
//
// \param x interval
// \return infimum of <B>x</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T inf(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::inf(x.rep_);
}


// \brief Supremum of an interval <B>x</B>
//
// <B>Required by IEEE P1788</B>
//
// The supremum of an interval <B>x</B> is defined as:
// \f[
//    \operatorname{sup}(\mathbf{x}) = \begin{cases}
//        \overline{x} & \text{if } \mathbf{x} \text{ is nonempty} \br
//        -\infty & \text{if } \mathbf{x} \text{ is empty}
//    \end{cases}
// \f]
//
// The computation is delegated to the static function
// \code
// Flavor<T>::sup(Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the interval.
//
//
// \see interval<T,Flavor>.upper()
//
// \param x interval
// \return supremum of <B>x</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T sup(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::sup(x.rep_);
}

// \brief Midpoint of an interval <B>x</B>
//
// <B>Required by IEEE P1788</B>
//
// The midpoint of an interval <B>x</B> is defined as:
// \f[
//    \operatorname{mid}(\mathbf{x}) = \begin{cases}
//        (\underline{x} + \overline{x}) / 2 & \text{if } \mathbf{x} \text{ is nonempty bounded} \br
//         \text{no value } & \text{if } \mathbf{x} \text{ is empty or unbounded}
//    \end{cases}
// \f]
//
// The computation is delegated to the static function
// \code
// Flavor<T>::mid(Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the interval.
//
//
// \see interval<T,Flavor>.mid()
//
// \param x interval
// \return midpoint of <B>x</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T mid(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::mid(x.rep_);
}

// \brief Radius of an interval <B>x</B>
//
// <B>Required by IEEE P1788</B>
//
// The radius of an interval <B>x</B> is defined as:
// \f[
//    \operatorname{rad}(\mathbf{x}) = \begin{cases}
//        (\overline{x} - \underline{x}) / 2 & \text{if } \mathbf{x} \text{ is nonempty} \br
//         \text{no value } & \text{if } \mathbf{x} \text{ is empty}
//    \end{cases}
// \f]
//
// The computation is delegated to the static function
// \code
// Flavor<T>::rad(Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the interval.
//
//
// \see interval<T,Flavor>.rad()
//
// \param x interval
// \return radius of <B>x</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T rad(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::rad(x.rep_);
}

//TODO Eigener Struct mit Elementen mid und rad?
// \brief Midpoint and radius of an interval <B>x</B>
//
// <B>Recommended by IEEE P1788</B>
// see Note in P1788/D7.0 Sect. 9.6.9
//
// Computes the midpoint and the radius of an interval <B>x</B>.
//
// The computation is delegated to the static function
// \code
// Flavor<T>::mid_rad(Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the interval.
//
// \see #mid(interval<T,Flavor> const& x)
// \see #rad(interval<T,Flavor> const& x)
//
// \param x interval
// \return std::pair<T,T> containing the midpoint (first value) and the radius (second value) of <B>x</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
std::pair<T, T> mid_rad(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::mid_rad(x.rep_);
}

// \brief Width of an interval <B>x</B>
//
// <B>Required by IEEE P1788</B>
//
// The width of an interval <B>x</B> is defined as:
// \f[
//    \operatorname{wid}(\mathbf{x}) = \begin{cases}
//        (\overline{x} - \underline{x}) & \text{if } \mathbf{x} \text{ is nonempty} \br
//         \text{no value } & \text{if } \mathbf{x} \text{ is empty}
//    \end{cases}
// \f]
//
// The computation is delegated to the static function
// \code
// Flavor<T>::wid(Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the interval.
//
// \param x interval
// \return width of <B>x</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T wid(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::wid(x.rep_);
}

// \brief Magnitude of an interval <B>x</B>
//
// <B>Required by IEEE P1788</B>
//
// The magnitude of an interval <B>x</B> is defined as:
// \f[
//    \operatorname{mag}(\mathbf{x}) = \begin{cases}
//        \operatorname{sup}\{ |x| \mid x \in \mathbf{x}\} & \text{if } \mathbf{x} \text{ is nonempty} \br
//         \text{no value } & \text{if } \mathbf{x} \text{ is empty}
//    \end{cases}
// \f]
//
// The computation is delegated to the static function
// \code
// Flavor<T>::mag(Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the interval.
//
// \param x interval
// \return magnitude of <B>x</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T mag(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::mag(x.rep_);
}

// \brief Mignitude of an interval <B>x</B>
//
// <B>Required by IEEE P1788</B>
//
// The mignitude of an interval <B>x</B> is defined as:
// \f[
//    \operatorname{mig}(\mathbf{x}) = \begin{cases}
//        \operatorname{inf}\{ |x| \mid x \in \mathbf{x}\} & \text{if } \mathbf{x} \text{ is nonempty} \br
//         \text{no value } & \text{if } \mathbf{x} \text{ is empty}
//    \end{cases}
// \f]
//
// The computation is delegated to the static function
// \code
// Flavor<T>::mig(Flavor<T>::representation const&)
// \endcode
// of the policy class <TT>Flavor<T></TT> by passing only the internal
// representation of the interval.
//
// \param x interval
// \return mignutude of <B>x</B>
//
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T mig(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::mig(x.rep_);
}

//@}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_NUM_FUNC_IMPL_HPP
