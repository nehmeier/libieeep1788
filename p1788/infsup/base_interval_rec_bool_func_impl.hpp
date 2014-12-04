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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REC_BOOL_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REC_BOOL_FUNC_IMPL_HPP

namespace p1788
{

namespace infsup
{

// is_common

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::is_common(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return Flavor<T>::is_common(x.rep_);
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
bool is_common(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T, Flavor, RepType, ConcreteInterval>::is_common(x);
}


// is_singleton

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::is_singleton(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return Flavor<T>::is_singleton(x.rep_);
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
bool is_singleton(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T, Flavor, RepType, ConcreteInterval>::is_singleton(x);
}


// is_member

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::is_member(T_ m, base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return Flavor<T>::is_member(m, x.rep_);
}

// function
template<typename T_, typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
bool is_member(T_ m, base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T, Flavor, RepType, ConcreteInterval>::is_member(m, x);
}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REC_BOOL_FUNC_IMPL_HPP
