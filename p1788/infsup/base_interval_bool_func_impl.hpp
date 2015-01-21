//
//                              libieeep1788
//
//   An implementation of the preliminary IEEE P1788 standard for
//   interval arithmetic
//
//
//   Copyright 2013 - 2015
//
//   Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
//   Department of Computer Science,
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

// is_empty

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::is_empty(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return Flavor<T>::is_empty(x.rep_);
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
bool is_empty(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T, Flavor, RepType, ConcreteInterval>::is_empty(x);
}


// is_entire

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::is_entire(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return Flavor<T>::is_entire(x.rep_);
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
bool is_entire(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T, Flavor, RepType, ConcreteInterval>::is_entire(x);
}


// is_equal

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::is_equal(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::is_equal(x.rep_, y.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool is_equal(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::is_equal(x, y);
}

// operator
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool operator==(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::is_equal(x, y);
}

// operator
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool operator!=(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return !base_interval<T1, Flavor, RepType1, ConcreteInterval1>::is_equal(x, y);
}


// subset

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::subset(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::subset(x.rep_, y.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool subset(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::subset(x, y);
}


// superset

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::superset(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::subset(y.rep_, x.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool superset(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::superset(x, y);
}


// less

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::less(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::less(x.rep_, y.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool less(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::less(x, y);
}


// greater

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::greater(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::less(y.rep_, x.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool greater(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::greater(x, y);
}


// precedes

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::precedes(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::precedes(x.rep_, y.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool precedes(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::precedes(x, y);
}


// succeeds

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::succeeds(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::precedes(y.rep_, x.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool succeeds(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::succeeds(x, y);
}


// is_interior

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::is_interior(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::is_interior(x.rep_, y.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool is_interior(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::is_interior(x, y);
}


// contains_interior

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::contains_interior(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::is_interior(y.rep_, x.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool contains_interior(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::contains_interior(x, y);
}


// strictly_less

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::strictly_less(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::strictly_less(x.rep_, y.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool strictly_less(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::strictly_less(x, y);
}


// strictly_greater

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::strictly_greater(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::strictly_less(y.rep_, x.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool strictly_greater(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::strictly_greater(x, y);
}


// strictly_precedes

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::strictly_precedes(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::strictly_precedes(x.rep_, y.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool strictly_precedes(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::strictly_precedes(x, y);
}


// strictly_succeeds

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::strictly_succeeds(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::strictly_precedes(y.rep_, x.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool strictly_succeeds(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::strictly_succeeds(x, y);
}


// are_disjoint

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
bool base_interval<T, Flavor, RepType, ConcreteInterval>::are_disjoint(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
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

    return Flavor<T>::are_disjoint(x.rep_, y.rep_);
}

// function
template<typename T1, template<typename> class Flavor, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
bool are_disjoint(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x, base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
{
    return base_interval<T1, Flavor, RepType1, ConcreteInterval1>::are_disjoint(x, y);
}



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_BOOL_FUNC_IMPL_HPP
