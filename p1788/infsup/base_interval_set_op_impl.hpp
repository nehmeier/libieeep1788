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

#include "p1788/util/mixed_type_traits.hpp"

namespace p1788
{

namespace infsup
{


// intersect( base_interval, base_interval )
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval
intersect(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::intersect(x.rep_, y.rep_));
}


// intersect( base_interval, base_interval ) mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1_, typename RepType1_, class ConcreteInterval1_, typename T2_, typename RepType2_, class ConcreteInterval2_>
ConcreteInterval
base_interval<T,Flavor,RepType,ConcreteInterval>::intersect(base_interval<T1_, Flavor, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor, RepType2_, ConcreteInterval2_> const& y) {

    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T1_>::representation, RepType1_>::value
                    && std::is_same<typename Flavor<T2_>::representation, RepType2_>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T1_>::representation_dec, RepType1_>::value
                    && std::is_same<typename Flavor<T2_>::representation_dec, RepType2_>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    // call of mixed type version
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::intersect(x.rep_, y.rep_));
}


// hull( base_interval, base_interval )
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval
hull(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T, Flavor, RepType, ConcreteInterval> const& y) {
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::hull(x.rep_, y.rep_));
}

// hull( base_interval, base_interval ) mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1_, typename RepType1_, class ConcreteInterval1_, typename T2_, typename RepType2_, class ConcreteInterval2_>
ConcreteInterval
base_interval<T,Flavor,RepType,ConcreteInterval>::hull(base_interval<T1_, Flavor, RepType1_, ConcreteInterval1_> const& x, base_interval<T2_, Flavor, RepType2_, ConcreteInterval2_> const& y) {

    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T1_>::representation, RepType1_>::value
                    && std::is_same<typename Flavor<T2_>::representation, RepType2_>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T1_>::representation_dec, RepType1_>::value
                    && std::is_same<typename Flavor<T2_>::representation_dec, RepType2_>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    // call of mixed type version
    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::hull(x.rep_, y.rep_));
}



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_SET_OP_IMPL_HPP
