//
//                              libieeep1788
//
//   An implementation of the preliminary IEEE P1788 standard for
//   interval arithmetic
//
//
//   Copyright 2013 - 2015
//
//   Marco Nehmeier (nehmeier@informatik.uni-wuerzburg.de)
//   Department of Computer Science,
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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_REC_OVERLAP_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_REC_OVERLAP_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{

// overlap ( bare interval, bare interval )
template<typename T>
p1788::overlapping::overlapping_state
mpfr_bin_ieee754_flavor<T>::overlap(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                    mpfr_bin_ieee754_flavor<T>::representation const& y)
{
    // call bare mixed type version
    return overlap<T>(x,y);
}


// overlap ( bare interval, bare interval ) mixedtype
template<typename T>
template<typename T_>
p1788::overlapping::overlapping_state
mpfr_bin_ieee754_flavor<T>::overlap(mpfr_bin_ieee754_flavor<T>::representation const& x,
                                    mpfr_bin_ieee754_flavor<T>::representation_type<T_> const& y)
{
    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y))
        return p1788::overlapping::overlapping_state::undefined;

    if (is_empty(x))
    {
        if (mpfr_bin_ieee754_flavor<T_>::is_empty(y))
        {
            return p1788::overlapping::overlapping_state::both_empty;
        }
        else
        {
            return p1788::overlapping::overlapping_state::first_empty;
        }
    }
    if (mpfr_bin_ieee754_flavor<T_>::is_empty(y))
    {
        return p1788::overlapping::overlapping_state::second_empty;
    }

    // !before
    if (x.second >= y.first)
    {

        if (x.second <= y.second)
        {
            if (x.first == y.first)
            {
                if (x.second < y.second)
                {
                    return p1788::overlapping::overlapping_state::starts;
                }
                else
                {
                    return p1788::overlapping::overlapping_state::equal;
                }
            }

            if (x.second == y.second)
            {
                if (x.first < y.first)
                {
                    return p1788::overlapping::overlapping_state::finished_by;
                }
                else
                {
                    return p1788::overlapping::overlapping_state::finishes;
                }
            }

            if (x.second > y.first)
            {
                if (x.first < y.first)
                {
                    return p1788::overlapping::overlapping_state::overlaps;
                }
                else
                {
                    return p1788::overlapping::overlapping_state::contained_by;
                }
            }

            return p1788::overlapping::overlapping_state::meets;
        }

        if (x.first <= y.second)
        {
            if (x.first <= y.first)
            {
                if (x.first < y.first)
                {
                    return p1788::overlapping::overlapping_state::contains;
                }
                else
                {
                    return p1788::overlapping::overlapping_state::started_by;
                }
            }

            if (x.first < y.second)
            {
                return p1788::overlapping::overlapping_state::overlapped_by;
            }

            return p1788::overlapping::overlapping_state::met_by;
        }

        return p1788::overlapping::overlapping_state::after;
    }
    // before
    return p1788::overlapping::overlapping_state::before;
}


// overlap ( decorated interval, decorated interval )
template<typename T>
p1788::overlapping::overlapping_state
mpfr_bin_ieee754_flavor<T>::overlap(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec const& y)
{
    // call decorated mixed type version
    return overlap<T>(x,y);
}


// overlap ( decorated interval, decorated interval ) mixedtyoe
template<typename T>
template<typename T_>
p1788::overlapping::overlapping_state
mpfr_bin_ieee754_flavor<T>::overlap(mpfr_bin_ieee754_flavor<T>::representation_dec const& x,
                                    mpfr_bin_ieee754_flavor<T>::representation_dec_type<T_> const& y)
{
    if (!is_valid(x) || !mpfr_bin_ieee754_flavor<T_>::is_valid(y) || is_nai(x) || mpfr_bin_ieee754_flavor<T_>::is_nai(y))
        return p1788::overlapping::overlapping_state::undefined;


    // call bare mixed type version
    return overlap(x.first, y.first);
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_REC_OVERLAP_IMPL_HPP
