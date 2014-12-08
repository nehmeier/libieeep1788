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



//// sqr
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval sqr(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sqr(x.rep_));
//}
//
//template<typename Interval, typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//Interval sqr(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    // assert that Interval is an implementation of base_interval
//    static_assert(p1788::util::is_infsup_base_interval_implementation<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    // assert that Interval uses the same flavor
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//    // assert that only bare intervals or decorated intervals are used
//    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
//                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation,
//                    typename Interval::representation_type>::value)
//                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
//                       && std::is_same<typename Flavor<typename Interval::bound_type>::representation_dec,
//                       typename Interval::representation_type>::value),
//                   "It is not supported by mixed type operations to use "
//                   "interval and decorated_interval types together!"
//                 );
//
//    typedef typename p1788::util::max_precision_interval_type<
//    Interval,
//    ConcreteInterval
//    >::type Interval_max;
//
//    return Interval(sqr(static_cast<Interval_max>(x)));
//}
//
//
//// sqrt
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval sqrt(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sqrt(x.rep_));
//}
//
//template<typename Interval, typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//Interval sqrt(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    // assert that Interval is an implementation of base_interval
//    static_assert(p1788::util::is_infsup_base_interval_implementation<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    // assert that Interval uses the same flavor
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//    // assert that only bare intervals or decorated intervals are used
//    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
//                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation,
//                    typename Interval::representation_type>::value)
//                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
//                       && std::is_same<typename Flavor<typename Interval::bound_type>::representation_dec,
//                       typename Interval::representation_type>::value),
//                   "It is not supported by mixed type operations to use "
//                   "interval and decorated_interval types together!"
//                 );
//
//    typedef typename p1788::util::max_precision_interval_type<
//    Interval,
//    ConcreteInterval
//    >::type Interval_max;
//
//    return Interval(recip(static_cast<Interval_max>(x)));
//}
//
//
//// fma
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval fma(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
//                     base_interval<T, Flavor, RepType, ConcreteInterval> const& y,
//                     base_interval<T, Flavor, RepType, ConcreteInterval> const& z)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::fma(x.rep_, y.rep_, z.rep_));
//}
//
//template<typename Interval, typename T, typename T_y, typename T_z, template<typename> class Flavor,
//         typename RepType, class ConcreteInterval, typename RepType_y, class ConcreteInterval_y,
//         typename RepType_z, class ConcreteInterval_z>
//Interval fma(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
//             base_interval<T_y, Flavor, RepType_y, ConcreteInterval_y> const& y,
//             base_interval<T_z, Flavor, RepType_z, ConcreteInterval_z> const& z)
//{
//    // assert that Interval is an implementation of base_interval
//    static_assert(p1788::util::is_infsup_base_interval_implementation<Interval>::value,
//                  "Return type is not supported by mixed type operations!");
//    // assert that Interval uses the same flavor
//    static_assert(std::is_same<typename Interval::flavor_type,
//                  Flavor<typename Interval::bound_type>>::value,
//                  "Different flavors are not supported by "
//                  "mixed type operations!");
//    // assert that only bare intervals or decorated intervals are used
//    static_assert( (std::is_same<typename Flavor<T>::representation, RepType>::value
//                    && std::is_same<typename Flavor<T_y>::representation, RepType_y>::value
//                    && std::is_same<typename Flavor<T_z>::representation, RepType_z>::value
//                    && std::is_same<typename Flavor<typename Interval::bound_type>::representation,
//                    typename Interval::representation_type>::value)
//                   || (std::is_same<typename Flavor<T>::representation_dec, RepType>::value
//                       && std::is_same<typename Flavor<T_y>::representation_dec, RepType_y>::value
//                       && std::is_same<typename Flavor<T_z>::representation_dec, RepType_z>::value
//                       && std::is_same<typename Flavor<typename Interval::bound_type>::representation_dec,
//                       typename Interval::representation_type>::value),
//                   "It is not supported by mixed type operations to use "
//                   "interval and decorated_interval types together!"
//                 );
//
//    typedef typename p1788::util::max_precision_interval_type<
//    Interval,
//    ConcreteInterval,
//    ConcreteInterval_y
//    >::type Interval_max;
//
//    return Interval(fma(static_cast<Interval_max>(x),
//                        static_cast<Interval_max>(y),
//                        static_cast<Interval_max>(z)));
//}
//
//
//// interval case
////TODO notwendig?
////template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
////ConcreteInterval interval_case(base_interval<T, Flavor, RepType, ConcreteInterval> const& c,
////        base_interval<T, Flavor, RepType, ConcreteInterval> const& g,
////        base_interval<T, Flavor, RepType, ConcreteInterval> const& h) {
////    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::interval_case(c.rep_,
////                               g.rep_, h.rep_));
////}
//
//
//// pown
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval pown(base_interval<T, Flavor, RepType, ConcreteInterval> const& x,
//                      int p)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::pown(x.rep_, p));
//}
//
//
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
//// exp
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval exp(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::exp(x.rep_));
//}
//
//
//// exp2
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval exp2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::exp2(x.rep_));
//}
//
//
//// exp10
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval exp10(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::exp10(x.rep_));
//}
//
//
//// log
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval log(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::log(x.rep_));
//}
//
//
//// log2
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval log2(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::log2(x.rep_));
//}
//
//
//// log10
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval log10(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::log10(x.rep_));
//}
//
//
//// sin
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval sin(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sin(x.rep_));
//}
//
//
//// cos
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval cos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::cos(x.rep_));
//}
//
//
//// tan
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval tan(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::tan(x.rep_));
//}
//
//
//// asin
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval asin(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::asin(x.rep_));
//}
//
//
//// acos
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval acos(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::acos(x.rep_));
//}
//
//
//// atan
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval atan(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::atan(x.rep_));
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
//
//
//// sinh
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval sinh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sinh(x.rep_));
//}
//
//
//// cosh
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval cosh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::cosh(x.rep_));
//}
//
//
//// tanh
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval tanh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::tanh(x.rep_));
//}
//
//
//// asinh
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval asinh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::asinh(x.rep_));
//}
//
//
//// acosh
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval acosh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::acosh(x.rep_));
//}
//
//
//// atanh
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval atanh(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::atanh(x.rep_));
//}
//
//
//// sign
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval sign(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::sign(x.rep_));
//}
//
//
//// ceil
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval ceil(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::ceil(x.rep_));
//}
//
//
//// floor
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval floor(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::floor(x.rep_));
//}
//
//
//// trunc
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval trunc(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::trunc(x.rep_));
//}
//
//
//// round_ties_to_even
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval round_ties_to_even(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::round_ties_to_even(x.rep_));
//}
//
//
//// round_ties_to_away
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval round_ties_to_away(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::round_ties_to_away(x.rep_));
//}
//
//
//// abs
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval abs(base_interval<T, Flavor, RepType, ConcreteInterval> const& x)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::abs(x.rep_));
//}
//
//
//// min
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval min(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::min(x.rep_, y.rep_));
//}
//
//// max
//
//template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval>
//ConcreteInterval max(base_interval<T, Flavor, RepType, ConcreteInterval> const& x, base_interval<T, Flavor, RepType, ConcreteInterval> const& y)
//{
//    return base_interval<T, Flavor, RepType, ConcreteInterval>::concrete_interval(Flavor<T>::max(x.rep_, y.rep_));
//}


//@}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_ELEM_FUNC_IMPL_HPP
