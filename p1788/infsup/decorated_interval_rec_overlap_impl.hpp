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

#ifndef LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_REC_OVERLAP_FUNC_HPP
#define LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_REC_OVERLAP_FUNC_HPP

namespace p1788
{

namespace infsup
{

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
/// \name Recommended interval overlapping, see P1788/D7.0 Sect. 9.7.2
///
///@{


template<typename T, template<typename> class Flavor>
p1788::overlapping::overlapping_state overlap(decorated_interval<T, Flavor> const& x,
        decorated_interval<T, Flavor> const& y) {
    return Flavor<T>::overlap_dec(x.rep_, y.rep_);
}

template<typename T, typename Ty, template<typename> class Flavor>
p1788::overlapping::overlapping_state overlap(decorated_interval<T, Flavor> const& x,
        decorated_interval<Ty, Flavor> const& y) {
    typedef typename p1788::util::max_precision_type<
    T,
    Ty
    >::type TMax;

    return overlap(static_cast<decorated_interval<TMax, Flavor>>(x),
                   static_cast<decorated_interval<TMax, Flavor>>(y));
}

///@}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_DECORATED_INTERVAL_REC_OVERLAP_FUNC_HPP
