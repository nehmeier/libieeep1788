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

#ifndef LIBIEEEP1788_P1788_INFSUP_INTERVAL_DIV_PAIR_FUNC_HPP
#define LIBIEEEP1788_P1788_INFSUP_INTERVAL_DIV_PAIR_FUNC_HPP

namespace p1788
{

namespace infsup
{

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
/// \name Recommended div to pair function, see P1788/D8.1 Sect. 10.6.5
///
///@{


template<typename T, template<typename> class Flavor>
std::pair<interval<T, Flavor>, interval<T, Flavor>>
div_to_pair(interval<T, Flavor> const& x, interval<T, Flavor> const& y) {
    std::pair<typename Flavor<T>::representation, typename Flavor<T>::representation> tmp = Flavor<T>::div_to_pair(x.rep_, y.rep_);

    return std::pair<interval<T, Flavor>, interval<T, Flavor>>(tmp.first, tmp.second);
}

///@}


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_INTERVAL_DIV_PAIR_FUNC_HPP

