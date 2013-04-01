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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_NUM_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_NUM_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

double
ieee754_flavor<double>::inf(ieee754_flavor<double>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return method_lower(x);
}

double
ieee754_flavor<double>::sup(ieee754_flavor<double>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return method_upper(x);
}

double
ieee754_flavor<double>::mid(ieee754_flavor<double>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return method_mid(x);
}

double
ieee754_flavor<double>::wid(ieee754_flavor<double>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return x.second - x.first;
}

double
ieee754_flavor<double>::rad(ieee754_flavor<double>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return method_rad(x);
}

double
ieee754_flavor<double>::mag(ieee754_flavor<double>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return 0.;
}

double
ieee754_flavor<double>::mig(ieee754_flavor<double>::representation const& x)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return 0.;
}

std::pair<double, double>
ieee754_flavor<double>::mid_rad(ieee754_flavor<double>::representation const&)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return ieee754_flavor<double>::static_method_entire();
}

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_IEEE754_DOUBLE_NUM_FUNC_IMPL_HPP
