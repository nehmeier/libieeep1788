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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_DIV_PAIR_FUNC_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_DIV_PAIR_FUNC_IMPL_HPP

namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{

template<typename T>
std::pair<typename mpfr_bin_ieee754_flavor<T>::representation, typename mpfr_bin_ieee754_flavor<T>::representation>
mpfr_bin_ieee754_flavor<T>::mul_rev_to_pair(mpfr_bin_ieee754_flavor<T>::representation const& b,
        mpfr_bin_ieee754_flavor<T>::representation const& c)
{
    if (is_empty(x))
        return x;

    if (is_empty(b))
        return b;

    if (is_empty(c))
        return c;

    // b == entire  or  c == entire
    if (is_entire(b) || is_entire(c))
        return x;                               // intersect(entire, x)

    // c contains 0.0
    if (c.first <= 0.0 && c.second >= 0.0)
    {
        // and b contains 0.0
        if (b.first <= 0.0 && b.second >= 0.0)
            return x;                           // intersect(entire, x)


        mpfr_var::setup();

        mpfr_var bl(b.first == 0.0 ? +0.0 : b.first , MPFR_RNDD);
        mpfr_var bu(b.second == 0.0 ? -0.0 : b.second, MPFR_RNDU);

        mpfr_var cl(c.first == 0.0 ? +0.0 : c.first , MPFR_RNDD);
        mpfr_var cu(c.second == 0.0 ? -0.0 : c.second, MPFR_RNDU);

        if (b.second < 0.0)
        {
            mpfr_div(cu(), cu(), bu(), MPFR_RNDD);
            mpfr_div(cl(), cl(), bu(), MPFR_RNDU);

            return intersect(representation(cu.template get<T>(MPFR_RNDD), cl.template get<T>(MPFR_RNDU)), x);
        }

        // b.first > 0.0
        mpfr_div(cl(), cl(), bl(), MPFR_RNDD);
        mpfr_div(cu(), cu(), bl(), MPFR_RNDU);

        return intersect(representation(cl.template get<T>(MPFR_RNDD), cu.template get<T>(MPFR_RNDU)), x);
    }


    if (c.second < 0.0)
    {
        if (b.first == 0.0 && b.second == 0.0)
            return empty();

        mpfr_var::setup();

        mpfr_var bl(b.first == 0.0 ? +0.0 : b.first , MPFR_RNDD);
        mpfr_var bu(b.second == 0.0 ? -0.0 : b.second, MPFR_RNDU);

        mpfr_var cl(c.first == 0.0 ? +0.0 : c.first , MPFR_RNDD);
        mpfr_var cu(c.second == 0.0 ? -0.0 : c.second, MPFR_RNDU);

        if (b.second <= 0.0)
        {
            mpfr_div(cu(), cu(), bl(), MPFR_RNDD);
            mpfr_div(cl(), cl(), bu(), MPFR_RNDU);

            return intersect(representation(cu.template get<T>(MPFR_RNDD), cl.template get<T>(MPFR_RNDU)), x);
        }

        if (b.first >= 0.0)
        {
            mpfr_div(cl(), cl(), bl(), MPFR_RNDD);
            mpfr_div(cu(), cu(), bu(), MPFR_RNDU);

            return intersect(representation(cl.template get<T>(MPFR_RNDD), cu.template get<T>(MPFR_RNDU)), x);
        }

        return x;                           // intersect(entire, x)
    }

    // c.first > 0.0
    if (b.first == 0.0 && b.second == 0.0)
        return empty();

    mpfr_var::setup();

    mpfr_var bl(b.first == 0.0 ? +0.0 : b.first , MPFR_RNDD);
    mpfr_var bu(b.second == 0.0 ? -0.0 : b.second, MPFR_RNDU);

    mpfr_var cl(c.first == 0.0 ? +0.0 : c.first , MPFR_RNDD);
    mpfr_var cu(c.second == 0.0 ? -0.0 : c.second, MPFR_RNDU);

    if (b.second <= 0.0)
    {
        mpfr_div(cu(), cu(), bu(), MPFR_RNDD);
        mpfr_div(cl(), cl(), bl(), MPFR_RNDU);

        return intersect(representation(cu.template get<T>(MPFR_RNDD), cl.template get<T>(MPFR_RNDU)), x);
    }

    if (b.first >= 0.0)
    {
        mpfr_div(cl(), cl(), bu(), MPFR_RNDD);
        mpfr_div(cu(), cu(), bl(), MPFR_RNDU);

        return intersect(representation(cl.template get<T>(MPFR_RNDD), cu.template get<T>(MPFR_RNDU)), x);
    }

    return x;                           // intersect(entire, x)
}

template<typename T>
std::pair<typename mpfr_bin_ieee754_flavor<T>::representation_dec, typename mpfr_bin_ieee754_flavor<T>::representation_dec>
mpfr_bin_ieee754_flavor<T>::mul_rev_to_pair(mpfr_bin_ieee754_flavor<T>::representation_dec const& b,
        mpfr_bin_ieee754_flavor<T>::representation_dec const& c)
{
    if (y.first.first < 0.0 && y.first.second > 0.0)
        return std::pair<typename mpfr_bin_ieee754_flavor<T>::representation_dec, typename mpfr_bin_ieee754_flavor<T>::representation_dec>
               (div(x, representation_dec(representation(y.first.first, 0.0), y.second)),
                div(x, representation_dec(representation(0.0, y.first.second), y.second)));

    return std::pair<typename mpfr_bin_ieee754_flavor<T>::representation_dec, typename mpfr_bin_ieee754_flavor<T>::representation_dec>
           (div(x, y), empty_dec());
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_DIV_PAIR_FUNC_IMPL_HPP
