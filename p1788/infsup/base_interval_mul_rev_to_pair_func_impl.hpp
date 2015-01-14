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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_MUL_REV_TO_PAIR_FUNC_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_MUL_REV_TO_PAIR_FUNC_HPP

namespace p1788
{

namespace infsup
{

// cancel_plus

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
std::pair<ConcreteInterval, ConcreteInterval>
base_interval<T,Flavor,RepType,ConcreteInterval>::mul_rev_to_pair(base_interval<T, Flavor, RepType, ConcreteInterval> const& b,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    auto tmp = Flavor<T>::mul_rev_to_pair(b.rep_, c.rep_);

    return std::pair<ConcreteInterval, ConcreteInterval>(concrete_interval(tmp.first), concrete_interval(tmp.second));
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
std::pair<ConcreteInterval, ConcreteInterval>
base_interval<T,Flavor,RepType,ConcreteInterval>::mul_rev_to_pair(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& b,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& c)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T1>::representation, RepType1>::value
                    && std::is_same<typename Flavor<T2>::representation, RepType2>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T1>::representation_dec, RepType1>::value
                       && std::is_same<typename Flavor<T2>::representation_dec, RepType2>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    auto tmp = Flavor<T>::mul_rev_to_pair(b.rep_, c.rep_);

    return std::pair<ConcreteInterval, ConcreteInterval>(concrete_interval(tmp.first), concrete_interval(tmp.second));
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
std::pair<ConcreteInterval, ConcreteInterval>
mul_rev_to_pair(base_interval<T, Flavor, RepType, ConcreteInterval> const& b,
                base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::mul_rev_to_pair(b, c);
}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_MUL_REV_TO_PAIR_FUNC_HPP

