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

#ifndef LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_IO_IMPL_HPP
#define LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_IO_IMPL_HPP

namespace p1788
{

namespace infsup
{

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
/// \name IO operators
///
///@{

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(
    std::basic_ostream<CharT, Traits>& os,
    base_interval<T, Flavor, RepType, ConcreteInterval> const& x) {
    return Flavor<T>::operator_output(os, x.rep_);
}

template<typename T, template<typename> class Flavor, typename RepType, class ConcreteInterval, typename CharT, typename Traits>
std::basic_istream<CharT, Traits>& operator>>(
    std::basic_istream<CharT, Traits>& is,
    base_interval<T, Flavor, RepType, ConcreteInterval>& x) {
    return Flavor<T>::operator_input(is, x.rep_);
}

///@}

} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_P1788_INFSUP_BASE_INTERVAL_IO_IMPL_HPP
