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


// inf( base_interval )
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T inf(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::inf(x.rep_);
}

// inf( base_interval ) mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
T
base_interval<T,Flavor,RepType,ConcreteInterval>::inf(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x) {

    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    // call of mixed-type version
    return Flavor<T>::inf(x.rep_);
}


// sup( base_interval )
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T sup(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::sup(x.rep_);
}

// sup( base_interval ) mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
T
base_interval<T,Flavor,RepType,ConcreteInterval>::sup(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x) {

    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    // call of mixed-type version
    return Flavor<T>::sup(x.rep_);
}


// mid( base_interval )
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T mid(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::mid(x.rep_);
}

// mid( base_interval ) mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
T
base_interval<T,Flavor,RepType,ConcreteInterval>::mid(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x) {

    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    // call of mixed-type version
    return Flavor<T>::mid(x.rep_);
}


// rad( base_interval )
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T rad(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::rad(x.rep_);
}

// rad( base_interval ) mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
T
base_interval<T,Flavor,RepType,ConcreteInterval>::rad(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x) {

    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );
    // call of mixed-type version
    return Flavor<T>::rad(x.rep_);
}

// mid_rad( base_interval )
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
std::pair<T, T> mid_rad(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::mid_rad(x.rep_);
}

// mid_rad( base_interval ) mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
std::pair<T, T>
base_interval<T,Flavor,RepType,ConcreteInterval>::mid_rad(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x) {

    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    // call of mixed-type version
    return Flavor<T>::mid_rad(x.rep_);
}


// wid( base_interval )
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T wid(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::wid(x.rep_);
}

// wid( base_interval ) mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
T
base_interval<T,Flavor,RepType,ConcreteInterval>::wid(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x) {

    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    // call of mixed-type version
    return Flavor<T>::wid(x.rep_);
}


// mag( base_interval )
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T mag(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::mag(x.rep_);
}

// mag( base_interval ) mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
T
base_interval<T,Flavor,RepType,ConcreteInterval>::mag(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x) {

    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    // call of mixed-type version
    return Flavor<T>::mag(x.rep_);
}


// mig( base_interval )
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
T mig(base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::mig(x.rep_);
}

// mig( base_interval ) mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
T
base_interval<T,Flavor,RepType,ConcreteInterval>::mig(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x) {

    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                    || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                    "It is not supported by mixed type operations to use "
                    "interval and decorated_interval types together!"
                   );

    // call of mixed-type version
    return Flavor<T>::mig(x.rep_);
}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_NUM_FUNC_IMPL_HPP
