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

#ifndef LIBIEEEP1788_TEST_UTIL_INSTANTIATE_HEADERS_HPP
#define LIBIEEEP1788_TEST_UTIL_INSTANTIATE_HEADERS_HPP

#include "p1788/p1788.hpp"

namespace p1788
{

namespace test
{

template<typename T>
using flavor = p1788::flavor::infsup::mpfr_flavor<T, p1788::flavor::infsup::subnormalize::yes>;

} // namespace test

} // namespace p1788


namespace p1788
{

namespace infsup
{
template class p1788::infsup::interval<float, p1788::test::flavor>;
template class p1788::infsup::interval<double, p1788::test::flavor>;
} // namespace infsup

namespace flavor
{

namespace infsup
{

template class p1788::flavor::infsup::mpfr_flavor<double, p1788::flavor::infsup::subnormalize::yes>;

} // namespace infsup

} // namespace flavor

} // namespace p1788



namespace p1788
{

namespace infsup {


typedef p1788::infsup::interval<double, p1788::test::flavor> I;


typedef std::ostream& (*op_out) (std::ostream&, I const&);
typedef std::istream& (*op_in) (std::istream&, I&);

typedef I (*f_id__idcr_idcr) (I const&, I const&);

typedef double (*f_d__idcr) (I const&);
typedef std::pair<double,double> (*f_pdd__idcr) (I const&);



// \name IO operators
op_out operator_out_ = &p1788::infsup::operator<<;

op_in operator_in_ = &p1788::infsup::operator>>;


// \name Non-arithmetic set operations, see P1788/D7.1 Sect. 9.6.7

f_id__idcr_idcr intersect_ = &p1788::infsup::intersect;

f_id__idcr_idcr hull_ = &p1788::infsup::hull;

// \name Numeric functions on intervals, see P1788/D7.1 Sect. 9.6.9
f_d__idcr inf_ = &p1788::infsup::inf;

f_d__idcr sup_ = &p1788::infsup::sup;

f_d__idcr mid_ = &p1788::infsup::mid;

f_d__idcr rad_ = &p1788::infsup::rad;

f_pdd__idcr mid_rad_ = &p1788::infsup::mid_rad;

 f_d__idcr wid_ = &p1788::infsup::wid;

f_d__idcr mag_ = &p1788::infsup::mag;

f_d__idcr mig_ = &p1788::infsup::mig;




//// \name Boolean functions on intervals, see P1788/D7.0 Sect. 9.6.10
//
//
//is_empty
//
//is_entire
//
//is_equal
//
//operator==
//
//operator!=
//
//contained_in
//
//contains
//
//less
//
//
//greater
//
//
//precedes
//
//succeeds
//
//is_interior
//
//
//contains_interior
//
//strictly_less
//
//
//strictly_greater
//
//strictly_precedes
//
//strictly_succeeds
//
//are_disjoint
//
//
//
//
//// \name Forward elementary functions
//
//
//pos
//
//
//operator+
//
//neg
//
//operator-
//
//add
//
//operator+
//
//sub
//
//operator-
//
//
//mul
//
//operator*
//
//div
//
//operator/
//
//
//inv
//
//
//sqrt
//fma
//
//
//interval_case
//
//
//
//sqr
//
//pown
//
//pow
//
//exp
//
//
//exp2
//
//exp10
//
//log
//
//log2
//
//log10
//
//sin
//
//cos
//
//tan
//
//asin
//
//acos
//
//atan
//
//atan2
//
//sinh
//
//cosh
//
//tanh
//
//asinh
//
//acosh
//atanh
//
//sign
//
//ceil
//
//floor
//
//trunc
//
//round_ties_to_even
//
//round_ties_to_away
//
//abs
//min
//
//max
//
//// \name Reverse elementary functions, see P1788/D7.0 Sect. 9.6.5 Table 2
//
//
//sqr_rev
//
//inv_rev
//
//abs_rev
//
//pown_rev
//
//sin_rev
//
//cos_rev
//
//tan_rev
//
//cosh_rev
//
//mul_rev
//
//div_rev1
//
//div_rev2
//
//pow_rev1
//
//pow_rev2
//
//atan2_rev1
//
//atan2_rev2
//
//
//
//// \name Cancellative addition and subtraction, see P1788/D7.0 Sect. 9.6.6
//
//
//cancel_plus
//
//cancel_minus
//
//
//// \name Recommended forward elementary functions on intervals, see P1788/D7.0 Sect. 9.7.1 Table 5
//
//
//rootn
//
//expm1
//
//exp2m1
//
//exp10m1
//
//logp1
//
//log2p1
//
//log10p1
//
//compoundm1
//
//hypot
//
//r_sqrt
//
//sin_pi
//
//cos_pi
//
//tan_pi
//
//asin_pi
//
//acos_pi
//
//atan_pi
//atan2_pi
//
//// \name Recommended interval overlapping, see P1788/D7.0 Sect. 9.7.2
//
//overlap
//
//// \name Recommended slope functions, see P1788/D7.0 Sect. 9.7.3 Table 7
//
//exp_slope1
//
//
//exp_slope2
//
//log_slope1
//
//log_slope2
//
//cos_slope2
//
//sin_slope3
//
//asin_slope3
//
//atan_slope3
//
//cosh_slope2
//
//sinh_slope3
//


} // namespace infsup

} // namespace p1788


#endif // LIBIEEEP1788_TEST_UTIL_INSTANTIATE_HEADERS_HPP
