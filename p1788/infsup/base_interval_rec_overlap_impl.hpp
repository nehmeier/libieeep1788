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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REC_OVERLAP_FUNC_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REC_OVERLAP_FUNC_HPP

namespace p1788
{

namespace infsup
{


// overlap

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
p1788::overlapping::overlapping_state
base_interval<T, Flavor, RepType, ConcreteInterval>::overlap(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
        base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& y)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    return Flavor<T>::overlap(x.rep_, y.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
p1788::overlapping::overlapping_state
overlap(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::overlap(x, y);
}



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REC_OVERLAP_FUNC_HPP
