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

#ifndef LIBIEEEP1788_P1788_INFSUP_INTERVAL_REV_ELEM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_INTERVAL_REV_ELEM_FUNC_IMPL_HPP

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
interval<T, Flavor> sqr_rev(interval<T, Flavor> const& c, interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::sqr_rev(c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
interval<T, Flavor> sqr_rev(interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::sqr_rev(x.rep_));
}


// recip_rev

template<typename T, template<typename> class Flavor>
interval<T, Flavor> recip_rev(interval<T, Flavor> const& c, interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::recip_rev(c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
interval<T, Flavor> recip_rev(interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::recip_rev(x.rep_));
}


// abs_rev

template<typename T, template<typename> class Flavor>
interval<T, Flavor> abs_rev(interval<T, Flavor> const& c, interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::abs_rev(c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
interval<T, Flavor> abs_rev(interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::abs_rev(x.rep_));
}


// pown_rev

template<typename T, template<typename> class Flavor>
interval<T, Flavor> pown_rev(interval<T, Flavor> const& c,
                                    interval<T, Flavor> const& x, int n) {   ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::pown_rev(c.rep_, x.rep_, n));
}


template<typename T, template<typename> class Flavor>
interval<T, Flavor> pown_rev(interval<T, Flavor> const& x, int n) {   ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::pown_rev(x.rep_, n));
}


// sin_rev

template<typename T, template<typename> class Flavor>
interval<T, Flavor> sin_rev(interval<T, Flavor> const& c, interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::sin_rev(c.rep_, x.rep_));
}


template<typename T, template<typename> class Flavor>
interval<T, Flavor> sin_rev(interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::sin_rev(x.rep_));
}


// cos_rev

template<typename T, template<typename> class Flavor>
interval<T, Flavor> cos_rev(interval<T, Flavor> const& c, interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::cos_rev(c.rep_, x.rep_));
}


template<typename T, template<typename> class Flavor>
interval<T, Flavor> cos_rev(interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::cos_rev(x.rep_));
}


// tan_rev

template<typename T, template<typename> class Flavor>
interval<T, Flavor> tan_rev(interval<T, Flavor> const& c,
                                   interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::tan_rev(c.rep_, x.rep_));
}


template<typename T, template<typename> class Flavor>
interval<T, Flavor> tan_rev(interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::tan_rev(x.rep_));
}


// cosh_rev

template<typename T, template<typename> class Flavor>
interval<T, Flavor> cosh_rev(interval<T, Flavor> const& c, interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::cosh_rev(c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
interval<T, Flavor> cosh_rev(interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::cosh_rev(x.rep_));
}



// reverse versions of binary point functions


// mul_rev

template<typename T, template<typename> class Flavor>
interval<T, Flavor> mul_rev(interval<T, Flavor> const& b,
                                   interval<T, Flavor> const& c,
                                   interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::mul_rev(b.rep_, c.rep_, x.rep_));
}


template<typename T, template<typename> class Flavor>
interval<T, Flavor> mul_rev(interval<T, Flavor> const& c,
                                   interval<T, Flavor> const& x) {     ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::mul_rev(c.rep_, x.rep_));
}


// div_rev1

template<typename T, template<typename> class Flavor>
interval<T, Flavor> div_rev1(interval<T, Flavor> const& b,
                                    interval<T, Flavor> const& c,
                                    interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::div_rev1(b.rep_, c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
interval<T, Flavor> div_rev1(interval<T, Flavor> const& c,
                                    interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::div_rev1(c.rep_, x.rep_));
}


// div_rev2

template<typename T, template<typename> class Flavor>
interval<T, Flavor> div_rev2(interval<T, Flavor> const& a,
                                    interval<T, Flavor> const& c,
                                    interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::div_rev2(a.rep_, c.rep_, x.rep_));
}


template<typename T, template<typename> class Flavor>
interval<T, Flavor> div_rev2(interval<T, Flavor> const& c,
                                    interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::div_rev2(c.rep_, x.rep_));
}

// pow_rev1

template<typename T, template<typename> class Flavor>
interval<T, Flavor> pow_rev1(interval<T, Flavor> const& b,
                                    interval<T, Flavor> const& c,
                                    interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::pow_rev1(b.rep_, c.rep_, x.rep_));
}


template<typename T, template<typename> class Flavor>
interval<T, Flavor> pow_rev1(interval<T, Flavor> const& c,
                                    interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::pow_rev1(c.rep_, x.rep_));
}


// pow_rev2

template<typename T, template<typename> class Flavor>
interval<T, Flavor> pow_rev2(interval<T, Flavor> const& a,
                                    interval<T, Flavor> const& c,
                                    interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::pow_rev2(a.rep_, c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
interval<T, Flavor> pow_rev2(interval<T, Flavor> const& c,
                                    interval<T, Flavor> const& x) {    ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::pow_rev2(c.rep_, x.rep_));
}


// atan2_rev1

template<typename T, template<typename> class Flavor>
interval<T, Flavor> atan2_rev1(interval<T, Flavor> const& b,
                                      interval<T, Flavor> const& c,
                                      interval<T, Flavor> const& x) {  ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::atan2_rev1(b.rep_, c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
interval<T, Flavor> atan2_rev1(interval<T, Flavor> const& c,
                                      interval<T, Flavor> const& x) {  ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::atan2_rev1(c.rep_, x.rep_));
}


// atan2_rev2

template<typename T, template<typename> class Flavor>
interval<T, Flavor> atan2_rev2(interval<T, Flavor> const& a,
                                      interval<T, Flavor> const& c,
                                      interval<T, Flavor> const& x) {  ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::atan2_rev2(a.rep_, c.rep_, x.rep_));
}

template<typename T, template<typename> class Flavor>
interval<T, Flavor> atan2_rev2(interval<T, Flavor> const& c,
                                      interval<T, Flavor> const& x) {  ///< Required, accurate
    return interval<T, Flavor>(Flavor<T>::atan2_rev2(c.rep_, x.rep_));
}


///@}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_INTERVAL_REV_ELEM_FUNC_IMPL_HPP
