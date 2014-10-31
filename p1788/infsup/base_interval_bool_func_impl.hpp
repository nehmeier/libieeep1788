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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_BOOL_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_BOOL_FUNC_IMPL_HPP

namespace p1788
{

namespace infsup
{

template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
bool is_empty(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x) {
    return Flavor_<T_>::is_empty(x.rep_);
}


template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
bool is_entire(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x) {
    return Flavor_<T_>::is_entire(x.rep_);
}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool
base_interval<T,Flavor,RepType,ConcreteInterval>::is_equal(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y) {
    return Flavor<T>::is_equal(x.rep_, y.rep_);
}

template<typename T1_, template<typename> class Flavor1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, template<typename> class Flavor2_, typename RepType2_, class ConcreteInterval2_>
bool is_equal(base_interval<T1_, Flavor1_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor2_, RepType2_, ConcreteInterval2_> const& y) {
    return base_interval<T1_, Flavor1_, RepType1_, ConcreteInterval1_>::is_equal(x, y);
}


//template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
//bool is_equal(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
//    return Flavor_<T1_>::is_equal(x.rep_, y.rep_);
//}

template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
bool operator==(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& y) {
    return Flavor_<T_>::is_equal(x.rep_, y.rep_);
}

template<typename T_, template<typename> class Flavor_, typename RepType_, class ConcreteInterval_>
bool operator!=(base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& x, base_interval<T_, Flavor_, RepType_, ConcreteInterval_> const& y) {
    return !Flavor_<T_>::is_equal(x.rep_, y.rep_);
}

//template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
//bool is_equal(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
//    return Flavor_<T1_>::is_equal(x.rep_, y.rep_);
//}
//
//template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
//bool operator==(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
//    return Flavor_<T1_>::is_equal(x.rep_, y.rep_);
//}
//
//template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
//bool operator!=(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
//    return !Flavor_<T1_>::is_equal(x.rep_, y.rep_);
//}


template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
bool subset(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
    return Flavor_<T1_>::subset(x.rep_, y.rep_);
}

template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
bool superset(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
    return Flavor_<T2_>::subset(y.rep_, x.rep_);
}


template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
bool less(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
    return Flavor_<T1_>::less(x.rep_, y.rep_);
}

template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
bool greater(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
    return Flavor_<T2_>::less(y.rep_, x.rep_);
}


template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
bool precedes(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
    return Flavor_<T1_>::precedes(x.rep_, y.rep_);
}

template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
bool succeeds(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
    return Flavor_<T2_>::precedes(y.rep_, x.rep_);
}


template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
bool is_interior(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
    return Flavor_<T1_>::is_interior(x.rep_, y.rep_);
}

template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
bool contains_interior(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
    return Flavor_<T2_>::is_interior(y.rep_, x.rep_);
}


template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
bool strictly_less(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
    return Flavor_<T1_>::strictly_less(x.rep_, y.rep_);
}

template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
bool strictly_greater(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
    return Flavor_<T2_>::strictly_less(y.rep_, x.rep_);
}


template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
bool strictly_precedes(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
    return Flavor_<T1_>::strictly_precedes(x.rep_, y.rep_);
}

template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
bool strictly_succeeds(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
    return Flavor_<T2_>::strictly_precedes(y.rep_, x.rep_);
}


template<template<typename> class Flavor_, typename T1_, typename RepType1_, class ConcreteInterval1_,  typename T2_, typename RepType2_, class ConcreteInterval2_>
bool are_disjoint(base_interval<T1_, Flavor_, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor_, RepType2_, ConcreteInterval2_> const& y) {
    return Flavor_<T1_>::are_disjoint(x.rep_, y.rep_);
}



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_BOOL_FUNC_IMPL_HPP
