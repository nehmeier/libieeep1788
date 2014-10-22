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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_CANCEL_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_CANCEL_FUNC_IMPL_HPP


namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{

template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cancel_plus(mpfr_bin_ieee754_flavor<T>::representation const& x,
        mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    return cancel_minus(x, neg(y));
}

template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cancel_plus(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
        mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(cancel_plus(x.first, y.first), p1788::decoration::decoration::trv);
}



template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::cancel_minus(mpfr_bin_ieee754_flavor<T>::representation const& x,
        mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    if (x.first == -std::numeric_limits<T>::infinity()
            || x.second == +std::numeric_limits<T>::infinity()
            || y.first == -std::numeric_limits<T>::infinity()
            || y.second == +std::numeric_limits<T>::infinity())
        return static_method_entire();

    p1788::overlapping::overlapping_state os = overlap(x, y);

    //    if (is_empty(x))
    if (os == p1788::overlapping::overlapping_state::first_empty
        || os == p1788::overlapping::overlapping_state::both_empty)
        return x;

    //    if (is_empty(y))
    if (os == p1788::overlapping::overlapping_state::second_empty)
        return static_method_entire();



    //    if (wid(x) < wid(y))

    if (os == p1788::overlapping::overlapping_state::starts
        || os == p1788::overlapping::overlapping_state::contained_by
        || os == p1788::overlapping::overlapping_state::finishes)
        return static_method_entire();

    if (os == p1788::overlapping::overlapping_state::before
        || os == p1788::overlapping::overlapping_state::meets
        || os == p1788::overlapping::overlapping_state::met_by
        || os == p1788::overlapping::overlapping_state::after)
    {
          // Normale EFT

        //TODO EFT über MPFR und nicht über FPU (nicht denormalisierte Zahlen)
        auto x_wid = p1788::util::two_sum(x.second, -x.first);
        auto y_wid = p1788::util::two_sum(y.second, -y.first);
        if (x_wid.first < y_wid.first || (x_wid.first == y_wid.first && x_wid.second < y_wid.second))
            return static_method_entire();
    }

    if (os == p1788::overlapping::overlapping_state::overlaps
        || os == p1788::overlapping::overlapping_state::overlapped_by)
    {
        // EFT auf Grenzen

        //TODO EFT über MPFR und nicht über FPU (nicht denormalisierte Zahlen)
        auto upper_dist = p1788::util::two_sum(y.second, -x.second);
        auto lower_dist = p1788::util::two_sum(y.first, -x.first);
        if (lower_dist.first < upper_dist.first || (lower_dist.first == upper_dist.first && lower_dist.second < upper_dist.second))
            return static_method_entire();
    }




    mpfr_var::setup();

    mpfr_var xl(x.first, MPFR_RNDD);
    mpfr_var xu(x.second, MPFR_RNDU);

    mpfr_var yl(y.first, MPFR_RNDD);
    mpfr_var yu(y.second, MPFR_RNDU);


    mpfr_sub(xl(), xl(), yl(), MPFR_RNDD);
    mpfr_sub(xu(), xu(), yu(), MPFR_RNDU);

    return representation(xl.template get<T>(MPFR_RNDD), xu.template get<T>(MPFR_RNDU));
}

template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::cancel_minus(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
        mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    LIBIEEEP1788_NOT_IMPLEMENTED;

    return representation_dec(cancel_minus(x.first, y.first), p1788::decoration::decoration::trv);
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_CANCEL_FUNC_IMPL_HPP
