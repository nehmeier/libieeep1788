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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_CLASS_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_CLASS_IMPL_HPP


namespace p1788
{

namespace flavor
{

namespace infsup
{

namespace setbased
{

// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

// empty bare interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::constructor()
{
    return empty();
}

// empty decorated interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::constructor_dec()
{
    return empty_dec();
}



// bare inf-sup interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::constructor(T lower, T upper)
{
    // Comparison with NaN is always false!
    if (lower <= upper
            && lower != std::numeric_limits<T>::infinity()
            && upper != -std::numeric_limits<T>::infinity())
    {
        return representation(lower, upper);
    }
    else
    {
        p1788::exception::signal_undefined_operation();
        return empty();
    }
}

// decorated inf-sup interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::constructor_dec(T lower, T upper)
{
    // Comparison with NaN is always false!
    if (lower <= upper
            && lower != std::numeric_limits<T>::infinity()
            && upper != -std::numeric_limits<T>::infinity())
    {
        return constructor_dec(representation(lower,upper));
    }
    else
    {
        p1788::exception::signal_undefined_operation();
        return nai();
    }
}

// bare inf-sup interval mixed type
template<typename T>
template<typename L_, typename U_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::constructor(L_ lower, U_ upper)
{
    static_assert(std::numeric_limits<L_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<U_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // Comparison with NaN is always false!
    if (lower <= upper
            && lower != std::numeric_limits<L_>::infinity()
            && upper != -std::numeric_limits<U_>::infinity())
    {
        return representation(convert_rndd(lower), convert_rndu(upper));
    }
    else
    {
        p1788::exception::signal_undefined_operation();
        return empty();
    }
}

// decorated inf-sup interval mixed type
template<typename T>
template<typename L_, typename U_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::constructor_dec(L_ lower, U_ upper)
{
    static_assert(std::numeric_limits<L_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<U_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // Comparison with NaN is always false!
    if (lower <= upper
            && lower != std::numeric_limits<L_>::infinity()
            && upper != -std::numeric_limits<U_>::infinity())
    {
        return constructor_dec(representation(convert_rndd(lower), convert_rndu(upper)));
    }
    else
    {
        p1788::exception::signal_undefined_operation();
        return nai();
    }
}


// decorated inf-sup-dec interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::constructor_dec(T lower, T upper, p1788::decoration::decoration dec)
{
    // Comparison with NaN is always false!
    if (dec != p1788::decoration::decoration::ill
            && (lower <= upper
                &&  lower != std::numeric_limits<T>::infinity()
                && upper != -std::numeric_limits<T>::infinity()
                && (dec != p1788::decoration::decoration::com
                    || (lower != -std::numeric_limits<T>::infinity()
                        && upper != std::numeric_limits<T>::infinity()))
               )
       )
    {
        return representation_dec(representation(lower,upper), dec);
    }
    else
    {
        p1788::exception::signal_undefined_operation();
        return nai();
    }
}


// decorated inf-sup-dec interval mixed type
template<typename T>
template<typename L_, typename U_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::constructor_dec(L_ lower, U_ upper, p1788::decoration::decoration dec)
{
    static_assert(std::numeric_limits<L_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");
    static_assert(std::numeric_limits<U_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    // Comparison with NaN is always false!
    if (dec != p1788::decoration::decoration::ill
            && (lower <= upper
                &&  lower != std::numeric_limits<L_>::infinity()
                && upper != -std::numeric_limits<U_>::infinity()
                && (dec != p1788::decoration::decoration::com
                    || (lower != -std::numeric_limits<L_>::infinity()
                        && upper != std::numeric_limits<U_>::infinity()))
               )
       )
    {
        representation tmp(convert_rndd(lower), convert_rndu(upper));
        return representation_dec(tmp,
                                  std::min(dec,
                                           std::isinf(tmp.first) || std::isinf(tmp.second)
                                           ? p1788::decoration::decoration::dac
                                           : p1788::decoration::decoration::com ));
    }
    else
    {
        p1788::exception::signal_undefined_operation();
        return nai();
    }
}


// string literal bare interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::constructor(std::string const& str)
{
    representation rep;
    std::istringstream s(str);

    operator_input(s, rep);

    if (!s)
    {
        p1788::exception::signal_undefined_operation();
        return empty();
    }

    char c;
    while(s.get(c))
        if (!std::isspace(c))
        {
            p1788::exception::signal_undefined_operation();
            return empty();
        }

    return rep;
}

// string literal decorated interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::constructor_dec(std::string const& str)
{
    representation_dec rep;
    std::istringstream s(str);

    operator_input(s, rep);

    if (!s)
    {
        p1788::exception::signal_undefined_operation();
        return nai();
    }

    char c;
    while(s.get(c))
        if (!std::isspace(c))
        {
            p1788::exception::signal_undefined_operation();
            return nai();
        }

    return rep;
}


// copy constructor bare interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::constructor(representation const& other)
{
    if (!is_valid(other))
    {
        return empty();
    }

    return other;
}

// copy constructor decorated interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::constructor_dec(representation_dec const& other)
{
    if (!is_valid(other))
    {
        return nai();
    }

    return other;
}


// -----------------------------------------------------------------------------
// Convert
// -----------------------------------------------------------------------------

// convert bare interval mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::constructor(representation_type<T_> const& other)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(other))
    {
        return empty();
    }

    return convert_hull(other);
}

// convert decorated interval mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::constructor_dec(representation_dec_type<T_> const& other)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(other))
    {
        return nai();
    }

    return convert_hull(other);
}


// convert decorated interval -> bare interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::constructor(representation_dec const& other)
{
    if (!is_valid(other))
    {
        return empty();
    }
    else if (is_nai(other))
    {
        p1788::exception::signal_interval_part_of_nai();
        return empty();
    }

    return other.first;
}

// convert decorated interval -> bare interval mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::constructor(representation_dec_type<T_> const& other)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(other))
    {
        return empty();
    }
    else if (mpfr_bin_ieee754_flavor<T_>::is_nai(other))
    {
        p1788::exception::signal_interval_part_of_nai();
        return empty();
    }

    return convert_hull(other.first);
}

// convert bare interval ->  decorated interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::constructor_dec(representation const& other)
{
    if (!is_valid(other))
    {
        return nai();
    }
    else if (is_empty(other))
    {
        return representation_dec(other, p1788::decoration::decoration::trv);
    }
    else if (other.first == -std::numeric_limits<T>::infinity() || other.second == std::numeric_limits<T>::infinity())
    {
        return representation_dec(other, p1788::decoration::decoration::dac);
    }
    else
    {
        return representation_dec(other, p1788::decoration::decoration::com);
    }
}

// convert bare interval ->  decorated interval mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::constructor_dec(representation_type<T_> const& other)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    if (!mpfr_bin_ieee754_flavor<T_>::is_valid(other))
    {
        return nai();
    }

    representation r = convert_hull(other);

    if (is_empty(r))
    {
        return representation_dec(r, p1788::decoration::decoration::trv);
    }
    else if (r.first == -std::numeric_limits<T>::infinity() || r.second == std::numeric_limits<T>::infinity())
    {
        return representation_dec(r, p1788::decoration::decoration::dac);
    }
    else
    {
        return representation_dec(r, p1788::decoration::decoration::com);
    }
}

// set decoration constructor
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::constructor_dec(representation const& other, p1788::decoration::decoration dec)
{
    if (!is_valid(other))
    {
        return nai();
    }

    if (dec == p1788::decoration::decoration::ill)
    {
        p1788::exception::signal_undefined_operation();
        return nai();
    }

    if (is_empty(other) && dec != p1788::decoration::decoration::trv)
    {
        p1788::exception::signal_undefined_operation();
        return empty_dec();
    }

    if (dec == p1788::decoration::decoration::com
            && (other.first == -std::numeric_limits<T>::infinity() || other.second == +std::numeric_limits<T>::infinity()))
    {
        p1788::exception::signal_undefined_operation();
        return representation_dec(other, p1788::decoration::decoration::dac);
    }

    return representation_dec(other, dec);
}

// set decoration constructor mixed type
template<typename T>
template<typename T_>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::constructor_dec(representation_type<T_> const& other, p1788::decoration::decoration dec)
{
    static_assert(std::numeric_limits<T_>::is_iec559, "Only IEEE 754 binary compliant types are supported!");

    return convert_hull(mpfr_bin_ieee754_flavor<T_>::constructor_dec(other, dec));
}


// get decoration
template<typename T>
p1788::decoration::decoration
mpfr_bin_ieee754_flavor<T>::decoration(representation_dec const& other)
{
    if (!is_valid(other))
    {
        return p1788::decoration::decoration::ill;
    }

    return other.second;
}


// -----------------------------------------------------------------------------
// Interval constants
// -----------------------------------------------------------------------------

// empty bare interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::empty()
{
    return representation(std::numeric_limits<T>::quiet_NaN(),
                          std::numeric_limits<T>::quiet_NaN());
}

// empty decorated interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::empty_dec()
{
    return representation_dec(representation(std::numeric_limits<T>::quiet_NaN(),
                              std::numeric_limits<T>::quiet_NaN()), p1788::decoration::decoration::trv);
}

// entire bare interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation
mpfr_bin_ieee754_flavor<T>::entire()
{
    return representation(-std::numeric_limits<T>::infinity(),
                          std::numeric_limits<T>::infinity());
}

// entire decorated interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::entire_dec()
{
    return representation_dec(representation(-std::numeric_limits<T>::infinity(),
                              std::numeric_limits<T>::infinity()), p1788::decoration::decoration::dac);
}



// nai decorated interval
template<typename T>
typename mpfr_bin_ieee754_flavor<T>::representation_dec
mpfr_bin_ieee754_flavor<T>::nai()
{
    return representation_dec(representation(std::numeric_limits<T>::quiet_NaN(),
                              std::numeric_limits<T>::quiet_NaN()), p1788::decoration::decoration::ill);
}


} // namespace setbased

} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_SETBASED_MPFR_BIN_IEEE754_FLAVOR_CLASS_IMPL_HPP
