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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_SET_OP_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_SET_OP_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

ieee754_flavor<double>::representation
ieee754_flavor<double>::intersect(ieee754_flavor<double>::representation const&,
                                  ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::hull(ieee754_flavor<double>::representation const&,
                                  ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

ieee754_flavor<double>::representation
ieee754_flavor<double>::widen(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_SET_OP_IMPL_HPP
