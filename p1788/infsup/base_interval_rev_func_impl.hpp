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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REV_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REV_ELEM_FUNC_IMPL_HPP

namespace p1788
{

namespace infsup
{


// sqr_rev

// static unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sqr_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return concrete_interval( Flavor<T>::sqr_rev(c.rep_) );
}

// static unary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sqr_rev(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& c)
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
    return concrete_interval( Flavor<T>::sqr_rev(c.rep_) );
}

// function unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sqr_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::sqr_rev(c);
}


// static binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sqr_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::sqr_rev(c.rep_, x.rep_) );
}

// static binary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sqr_rev(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& c,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& x)
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
    return concrete_interval( Flavor<T>::sqr_rev(c.rep_, x.rep_) );
}

// function binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sqr_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
                         base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::sqr_rev(c, x);
}




// abs_rev

// static unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::abs_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return concrete_interval( Flavor<T>::abs_rev(c.rep_) );
}

// static unary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::abs_rev(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& c)
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
    return concrete_interval( Flavor<T>::abs_rev(c.rep_) );
}

// function unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval abs_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::abs_rev(c);
}


// static binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::abs_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::abs_rev(c.rep_, x.rep_) );
}

// static binary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::abs_rev(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& c,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& x)
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
    return concrete_interval( Flavor<T>::abs_rev(c.rep_, x.rep_) );
}

// function binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval abs_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
                         base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::abs_rev(c, x);
}




// pown_rev

// static unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::pown_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c, int p)
{
    return concrete_interval( Flavor<T>::pown_rev(c.rep_, p) );
}

// static unary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::pown_rev(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& c, int p)
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
    return concrete_interval( Flavor<T>::pown_rev(c.rep_, p) );
}

// function unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval pown_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c, int p)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::pown_rev(c, p);
}


// static binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::pown_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
        int p)
{
    return concrete_interval( Flavor<T>::pown_rev(c.rep_, x.rep_, p) );
}

// static binary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::pown_rev(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& c,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& x,
        int p)
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
    return concrete_interval( Flavor<T>::pown_rev(c.rep_, x.rep_, p) );
}

// function binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval pown_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
                          base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
                          int p)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::pown_rev(c, x, p);
}





// sin_rev

// static unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sin_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return concrete_interval( Flavor<T>::sin_rev(c.rep_) );
}

// static unary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sin_rev(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& c)
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
    return concrete_interval( Flavor<T>::sin_rev(c.rep_) );
}

// function unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sin_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::sin_rev(c);
}


// static binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sin_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::sin_rev(c.rep_, x.rep_) );
}

// static binary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::sin_rev(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& c,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& x)
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
    return concrete_interval( Flavor<T>::sin_rev(c.rep_, x.rep_) );
}

// function binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval sin_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
                         base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::sin_rev(c, x);
}




// cos_rev

// static unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::cos_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return concrete_interval( Flavor<T>::cos_rev(c.rep_) );
}

// static unary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::cos_rev(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& c)
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
    return concrete_interval( Flavor<T>::cos_rev(c.rep_) );
}

// function unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval cos_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::cos_rev(c);
}


// static binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::cos_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::cos_rev(c.rep_, x.rep_) );
}

// static binary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::cos_rev(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& c,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& x)
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
    return concrete_interval( Flavor<T>::cos_rev(c.rep_, x.rep_) );
}

// function binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval cos_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
                         base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::cos_rev(c, x);
}



// tan_rev

// static unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::tan_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return concrete_interval( Flavor<T>::tan_rev(c.rep_) );
}

// static unary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::tan_rev(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& c)
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
    return concrete_interval( Flavor<T>::tan_rev(c.rep_) );
}

// function unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval tan_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::tan_rev(c);
}


// static binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::tan_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::tan_rev(c.rep_, x.rep_) );
}

// static binary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::tan_rev(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& c,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& x)
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
    return concrete_interval( Flavor<T>::tan_rev(c.rep_, x.rep_) );
}

// function binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval tan_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
                         base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::tan_rev(c, x);
}



// cosh_rev

// static unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::cosh_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return concrete_interval( Flavor<T>::cosh_rev(c.rep_) );
}

// static unary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T_, typename RepType_, class ConcreteInterval_>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::cosh_rev(base_interval<T_, Flavor, RepType_, ConcreteInterval_> const& c)
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
    return concrete_interval( Flavor<T>::cosh_rev(c.rep_) );
}

// function unary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval cosh_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::cosh_rev(c);
}


// static binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::cosh_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::cosh_rev(c.rep_, x.rep_) );
}

// static binary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::cosh_rev(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& c,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& x)
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
    return concrete_interval( Flavor<T>::cosh_rev(c.rep_, x.rep_) );
}

// function binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval cosh_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
                          base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::cosh_rev(c, x);
}







// mul_rev

// static binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::mul_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& b,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return concrete_interval( Flavor<T>::mul_rev(b.rep_, c.rep_) );
}

// static binary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1, typename T2, typename RepType2, class ConcreteInterval2>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::mul_rev(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& b,
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
    return concrete_interval( Flavor<T>::mul_rev(b.rep_, c.rep_) );
}

// function binary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval mul_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& b,
                         base_interval<T, Flavor, RepType, ConcreteInterval> const& c)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::mul_rev(b, c);
}


// static ternary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::mul_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& b,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
        base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return concrete_interval( Flavor<T>::mul_rev(b.rep_, c.rep_, x.rep_) );
}

// static ternary mixed type
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
template<typename T1, typename RepType1, class ConcreteInterval1,
         typename T2, typename RepType2, class ConcreteInterval2,
         typename T3, typename RepType3, class ConcreteInterval3>
ConcreteInterval base_interval<T,Flavor,RepType,ConcreteInterval>::mul_rev(base_interval<T1, Flavor, RepType1, ConcreteInterval1> const& b,
        base_interval<T2, Flavor, RepType2, ConcreteInterval2> const& c,
        base_interval<T3, Flavor, RepType3, ConcreteInterval3> const& x)
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
    return concrete_interval( Flavor<T>::mul_rev(b.rep_, c.rep_, x.rep_) );
}

// function ternary
template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
ConcreteInterval mul_rev(base_interval<T, Flavor, RepType, ConcreteInterval> const& b,
                         base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
                         base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
{
    return base_interval<T,Flavor,RepType,ConcreteInterval>::mul_rev(b, c, x);
}



} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_REV_ELEM_FUNC_IMPL_HPP
