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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_ELEM_FUNC_IMPL_HPP


namespace p1788
{

namespace infsup
{

// pos

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::pos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::pos(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::pos(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::pos(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval pos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::pos(x);
}

// operator
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval operator+(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::pos(x);
}



// neg

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::neg(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::neg(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::neg(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::neg(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval neg(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::neg(x);
}

// operator
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval operator-(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::neg(x);
}



// add

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::add(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return concrete_interval( Flavor<T>::add(x.rep_, y.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::add(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
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
    return concrete_interval( Flavor<T>::add(x.rep_, y.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval add(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::add(x, y);
}

// operator
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval operator+(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                           base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::add(x, y);
}


// sub

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sub(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return concrete_interval( Flavor<T>::sub(x.rep_, y.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sub(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
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
    return concrete_interval( Flavor<T>::sub(x.rep_, y.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sub(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::sub(x, y);
}

// operator
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval operator-(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                           base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::sub(x, y);
}


// mul

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::mul(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return concrete_interval( Flavor<T>::mul(x.rep_, y.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::mul(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
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
    return concrete_interval( Flavor<T>::mul(x.rep_, y.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval mul(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::mul(x, y);
}

// operator
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval operator*(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                           base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::mul(x, y);
}



// div

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::div(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return concrete_interval( Flavor<T>::div(x.rep_, y.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::div(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
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
    return concrete_interval( Flavor<T>::div(x.rep_, y.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval div(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::div(x, y);
}

// operator
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval operator/(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                           base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::div(x, y);
}



// recip

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::recip(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::recip(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::recip(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::recip(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval recip(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::recip(x);
}



// sqr

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sqr(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::sqr(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sqr(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::sqr(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sqr(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::sqr(x);
}



// sqrt

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sqrt(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::sqrt(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sqrt(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::sqrt(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sqrt(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::sqrt(x);
}



// fma

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::fma(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& y,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& z)
{
    return concrete_interval( Flavor<T>::fma(x.rep_, y.rep_, z.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1,
         typename T2, typename RepType2, class ConcreteInterval2,
         typename T3, typename RepType3, class ConcreteInterval3>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::fma(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y,
        base_interval<T3, Flavor, RepType3, ConcreteInterval3> const& z)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T1>::representation, RepType1>::value
                    && std::is_same<typename Flavor<T2>::representation, RepType2>::value
                    && std::is_same<typename Flavor<T3>::representation, RepType3>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T1>::representation_dec, RepType1>::value
                       && std::is_same<typename Flavor<T2>::representation_dec, RepType2>::value
                       && std::is_same<typename Flavor<T3>::representation_dec, RepType3>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::fma(x.rep_, y.rep_, z.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval fma(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& z)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::fma(x, y, z);
}



// pown

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::pown(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, int p)
{
    return concrete_interval( Flavor<T>::pown(x.rep_, p) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::pown(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x, int p)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::pown(x.rep_, p) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval pown(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, int p)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::pown(x, p);
}



// pow

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::pow(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return concrete_interval( Flavor<T>::pow(x.rep_, y.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::pow(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
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
    return concrete_interval( Flavor<T>::pow(x.rep_, y.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval pow(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::pow(x, y);
}



// exp

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::exp(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::exp(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::exp(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::exp(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval exp(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::exp(x);
}



// exp2

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::exp2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::exp2(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::exp2(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::exp2(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval exp2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::exp2(x);
}



// exp10

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::exp10(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::exp10(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::exp10(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::exp10(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval exp10(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::exp10(x);
}


// log

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::log(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::log(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::log(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::log(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval log(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::log(x);
}



// log2

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::log2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::log2(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::log2(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::log2(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval log2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::log2(x);
}



// log10

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::log10(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::log10(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::log10(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::log10(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval log10(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::log10(x);
}




// sin

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sin(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::sin(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sin(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::sin(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sin(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::sin(x);
}


// cos

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::cos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::cos(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::cos(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::cos(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval cos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::cos(x);
}


// tan

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::tan(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::tan(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::tan(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::tan(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval tan(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::tan(x);
}








// asin

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::asin(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::asin(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::asin(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::asin(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval asin(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::asin(x);
}


// acos

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::acos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::acos(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::acos(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::acos(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval acos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::acos(x);
}


// atan

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::atan(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::atan(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::atan(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::atan(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval atan(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::atan(x);
}








// sinh

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sinh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::sinh(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sinh(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::sinh(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sinh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::sinh(x);
}


// cosh

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::cosh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::cosh(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::cosh(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::cosh(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval cosh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::cosh(x);
}


// tanh

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::tanh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::tanh(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::tanh(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::tanh(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval tanh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::tanh(x);
}



// asinh

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::asinh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::asinh(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::asinh(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::asinh(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval asinh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::asinh(x);
}


// acosh

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::acosh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::acosh(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::acosh(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::acosh(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval acosh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::acosh(x);
}


// atanh

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::atanh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::atanh(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::atanh(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::atanh(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval atanh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::atanh(x);
}



// sign

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sign(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::sign(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sign(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::sign(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sign(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::sign(x);
}




// ceil

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::ceil(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::ceil(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::ceil(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::ceil(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval ceil(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::ceil(x);
}




// floor

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::floor(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::floor(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::floor(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::floor(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval floor(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::floor(x);
}




// trunc

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::trunc(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::trunc(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::trunc(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::trunc(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval trunc(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::trunc(x);
}




// round_ties_to_even

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::round_ties_to_even(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::round_ties_to_even(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::round_ties_to_even(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::round_ties_to_even(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval round_ties_to_even(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::round_ties_to_even(x);
}




// round_ties_to_away

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::round_ties_to_away(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::round_ties_to_away(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::round_ties_to_away(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::round_ties_to_away(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval round_ties_to_away(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::round_ties_to_away(x);
}




// abs

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::abs(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::abs(x.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::abs(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& x)
{
    // assert that only bare intervals or decorated intervals are used
    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
                    && std::is_same<typename Flavor<T_>::representation, RepType_>::value)
                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
                       && std::is_same<typename Flavor<T_>::representation_dec, RepType_>::value),
                   "It is not supported by mixed type operations to use "
                   "interval and decorated_interval types together!"
                 );

    // call of mixed-type version
    return concrete_interval( Flavor<T>::abs(x.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval abs(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::abs(x);
}




// min

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::min(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return concrete_interval( Flavor<T>::min(x.rep_, y.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::min(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
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
    return concrete_interval( Flavor<T>::min(x.rep_, y.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval min(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::min(x, y);
}


// max

// static
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::max(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return concrete_interval( Flavor<T>::max(x.rep_, y.rep_) );
}

// static mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::max(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& x,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& y)
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
    return concrete_interval( Flavor<T>::max(x.rep_, y.rep_) );
}

// function
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval max(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::max(x, y);
}



//// pow
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval pow(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
//                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::pow(x.rep_, y.rep_));
//}
//


//
//// atan2
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval atan2(base_interval<T, Flavor, RepType, ConcreteInterval> const& y,
//                       base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::atan2(y.rep_, x.rep_));
//}



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_ELEM_FUNC_IMPL_HPP
