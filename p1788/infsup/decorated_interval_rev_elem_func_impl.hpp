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

#ifndef LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_REV_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_REV_ELEM_FUNC_IMPL_HPP

namespace p1788
{

namespace infsup
{


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
/// \name Reverse elementary functions, see P1788/D7.0 Sect. 9.6.5 Table 2
///
///@{


// reverse version of unary point functions


// sqr_rev

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> sqr_rev(decorated_interval<T, Flavor> const& c, decorated_interval<T, Flavor> const& x) {     ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::sqr_rev_dec(c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> sqr_rev(decorated_interval<T, Flavor> const& x) {     ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::sqr_rev_dec(x.rep_));
}


// recip_rev

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> recip_rev(decorated_interval<T, Flavor> const& c, decorated_interval<T, Flavor> const& x) {     ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::recip_rev_dec(c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> recip_rev(decorated_interval<T, Flavor> const& x) {     ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::recip_rev_dec(x.rep_));
}


// abs_rev

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> abs_rev(decorated_interval<T, Flavor> const& c, decorated_interval<T, Flavor> const& x) {     ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::abs_rev_dec(c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> abs_rev(decorated_interval<T, Flavor> const& x) {     ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::abs_rev_dec(x.rep_));
}


// pown_rev

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> pown_rev(decorated_interval<T, Flavor> const& c,
                                    decorated_interval<T, Flavor> const& x, int n) {   ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::pown_rev_dec(c.rep_, x.rep_, n));
}


template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> pown_rev(decorated_interval<T, Flavor> const& x, int n) {   ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::pown_rev_dec(x.rep_, n));
}


// sin_rev

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> sin_rev(decorated_interval<T, Flavor> const& c, decorated_interval<T, Flavor> const& x) {     ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::sin_rev_dec(c.rep_, x.rep_));
}


template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> sin_rev(decorated_interval<T, Flavor> const& x) {     ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::sin_rev_dec(x.rep_));
}


// cos_rev

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> cos_rev(decorated_interval<T, Flavor> const& c, decorated_interval<T, Flavor> const& x) {     ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::cos_rev_dec(c.rep_, x.rep_));
}


template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> cos_rev(decorated_interval<T, Flavor> const& x) {     ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::cos_rev_dec(x.rep_));
}


// tan_rev

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> tan_rev(decorated_interval<T, Flavor> const& c,
                                   decorated_interval<T, Flavor> const& x) {     ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::tan_rev_dec(c.rep_, x.rep_));
}


template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> tan_rev(decorated_interval<T, Flavor> const& x) {     ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::tan_rev_dec(x.rep_));
}


// cosh_rev

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> cosh_rev(decorated_interval<T, Flavor> const& c, decorated_interval<T, Flavor> const& x) {    ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::cosh_rev_dec(c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> cosh_rev(decorated_interval<T, Flavor> const& x) {    ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::cosh_rev_dec(x.rep_));
}



// reverse versions of binary point functions


// mul_rev

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> mul_rev(decorated_interval<T, Flavor> const& b,
                                   decorated_interval<T, Flavor> const& c,
                                   decorated_interval<T, Flavor> const& x) {    ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::mul_rev_dec(b.rep_, c.rep_, x.rep_));
}


template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> mul_rev(decorated_interval<T, Flavor> const& c,
                                   decorated_interval<T, Flavor> const& x) {     ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::mul_rev_dec(c.rep_, x.rep_));
}


// div_rev1

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> div_rev1(decorated_interval<T, Flavor> const& b,
                                    decorated_interval<T, Flavor> const& c,
                                    decorated_interval<T, Flavor> const& x) {    ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::div_rev1_dec(b.rep_, c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> div_rev1(decorated_interval<T, Flavor> const& c,
                                    decorated_interval<T, Flavor> const& x) {    ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::div_rev1_dec(c.rep_, x.rep_));
}


// div_rev2

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> div_rev2(decorated_interval<T, Flavor> const& a,
                                    decorated_interval<T, Flavor> const& c,
                                    decorated_interval<T, Flavor> const& x) {    ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::div_rev2_dec(a.rep_, c.rep_, x.rep_));
}


template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> div_rev2(decorated_interval<T, Flavor> const& c,
                                    decorated_interval<T, Flavor> const& x) {    ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::div_rev2_dec(c.rep_, x.rep_));
}

// pow_rev1

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> pow_rev1(decorated_interval<T, Flavor> const& b,
                                    decorated_interval<T, Flavor> const& c,
                                    decorated_interval<T, Flavor> const& x) {    ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::pow_rev1_dec(b.rep_, c.rep_, x.rep_));
}


template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> pow_rev1(decorated_interval<T, Flavor> const& c,
                                    decorated_interval<T, Flavor> const& x) {    ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::pow_rev1_dec(c.rep_, x.rep_));
}


// pow_rev2

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> pow_rev2(decorated_interval<T, Flavor> const& a,
                                    decorated_interval<T, Flavor> const& c,
                                    decorated_interval<T, Flavor> const& x) {    ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::pow_rev2_dec(a.rep_, c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> pow_rev2(decorated_interval<T, Flavor> const& c,
                                    decorated_interval<T, Flavor> const& x) {    ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::pow_rev2_dec(c.rep_, x.rep_));
}


// atan2_rev1

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> atan2_rev1(decorated_interval<T, Flavor> const& b,
                                      decorated_interval<T, Flavor> const& c,
                                      decorated_interval<T, Flavor> const& x) {  ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::atan2_rev1_dec(b.rep_, c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> atan2_rev1(decorated_interval<T, Flavor> const& c,
                                      decorated_interval<T, Flavor> const& x) {  ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::atan2_rev1_dec(c.rep_, x.rep_));
}


// atan2_rev2

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> atan2_rev2(decorated_interval<T, Flavor> const& a,
                                      decorated_interval<T, Flavor> const& c,
                                      decorated_interval<T, Flavor> const& x) {  ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::atan2_rev2_dec(a.rep_, c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
decorated_interval<T, Flavor> atan2_rev2(decorated_interval<T, Flavor> const& c,
                                      decorated_interval<T, Flavor> const& x) {  ///< Required, accurate
    return decorated_interval<T, Flavor>(Flavor<T>::atan2_rev2_dec(c.rep_, x.rep_));
}


///@}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_REV_ELEM_FUNC_IMPL_HPP
