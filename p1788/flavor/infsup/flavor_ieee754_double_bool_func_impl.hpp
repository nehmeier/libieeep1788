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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_BOOL_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_BOOL_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

bool
ieee754_flavor<double>::is_empty(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

bool
ieee754_flavor<double>::is_entire(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

bool
ieee754_flavor<double>::is_equal(ieee754_flavor<double>::representation const&,
                                 ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

bool
ieee754_flavor<double>::contained_in(ieee754_flavor<double>::representation const&,
                                     ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

bool
ieee754_flavor<double>::less(ieee754_flavor<double>::representation const&,
                             ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

bool
ieee754_flavor<double>::precedes(ieee754_flavor<double>::representation const&,
                                 ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

bool
ieee754_flavor<double>::is_enterior(ieee754_flavor<double>::representation const&,
                                    ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

bool
ieee754_flavor<double>::strictly_less(ieee754_flavor<double>::representation const&,
                                      ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

bool
ieee754_flavor<double>::strictly_precedes(ieee754_flavor<double>::representation const&,
        ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

bool
ieee754_flavor<double>::are_disjoint(ieee754_flavor<double>::representation const&,
                                     ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return false;
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_BOOL_FUNC_IMPL_HPP
