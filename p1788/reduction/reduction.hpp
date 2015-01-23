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


#ifndef LIBIEEEP1788_P1788_REDUCTION_REDUCTION_HPP
#define LIBIEEEP1788_P1788_REDUCTION_REDUCTION_HPP

#include <iterator>
#include <initializer_list>

#include "p1788/util/mpfr_var.hpp"

namespace p1788
{

namespace reduction
{


// enum for rounding modes
enum class rnd_mode
{
    downward = MPFR_RNDD,
    upward = MPFR_RNDU,
    to_nearest = MPFR_RNDN,
    to_zero = MPFR_RNDZ
};

// convert rnd_mode to mpfr rndmode
inline mpfr_rnd_t get_mpfr_rnd_mode(rnd_mode rnd)
{
    switch (rnd)
    {
    case rnd_mode::downward:
        return MPFR_RNDD;
    case rnd_mode::upward:
        return MPFR_RNDU;
    case rnd_mode::to_nearest:
        return MPFR_RNDN;
    case rnd_mode::to_zero:
        return MPFR_RNDZ;
    }

    // Something went wrong
    return MPFR_RNDN;
}



// class to perform the accumulation with a combined memory handling (RAII)
template<class Iter>
class reduction_sum_op
{
    static_assert(std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::is_iec559,
                  "Only IEEE 754 binary compliant types are supported!");

    // Typedef for the corresponding mpfr wrapper class representing the IEEE 754 binary floating point format of the iterator value type
    typedef p1788::util::mpfr_var<
    std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::has_denorm != std::denorm_present
        ? std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::min_exponent
        : std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::min_exponent - std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits + 1,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::max_exponent,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::has_denorm == std::denorm_present
        > mpfr_var;

public:

    // perform op on one iterator
    reduction_sum_op(void (*op) (Iter, mpfr_ptr*), Iter begin, Iter end, rnd_mode rnd) : n_(end - begin)
    {
        mpfr_var::setup();
        tab_ = new mpfr_ptr[n_];    // array of elemets

        mpfr_ptr* p = tab_;

        // perform op on iterator
        while (begin != end)
            op(begin++, p++);

        mpfr_var res;

        // accumulate
        res.subnormalize(mpfr_sum(res(), tab_, n_, get_mpfr_rnd_mode(rnd)), get_mpfr_rnd_mode(rnd));

        // get result
        result_ = res.template get<typename std::iterator_traits<Iter>::value_type>(get_mpfr_rnd_mode(rnd));

        if (result_ == 0.0)
            result_ = rnd == rnd_mode::downward ? -0.0 : 0.0;
    }

    // perform op on two interators
    reduction_sum_op(void (*op) (Iter, Iter, mpfr_ptr*), Iter begin_a, Iter end_a, Iter begin_b, rnd_mode rnd) : n_(end_a - begin_a)
    {
        mpfr_var::setup();
        tab_ = new mpfr_ptr[n_];    // array of elemets

        mpfr_ptr* p = tab_;

        // perform op on iterator
        while (begin_a != end_a)
            op(begin_a++, begin_b++, p++);

        mpfr_var res;

        // accumulate
        res.subnormalize(mpfr_sum(res(), tab_, n_, get_mpfr_rnd_mode(rnd)), get_mpfr_rnd_mode(rnd));

        // get result
        result_ = res.template get<typename std::iterator_traits<Iter>::value_type>(get_mpfr_rnd_mode(rnd));

        if (result_ == 0.0)
            result_ = rnd == rnd_mode::downward ? -0.0 : 0.0;
    }

    // cleanup
    ~reduction_sum_op()
    {
        for(mpfr_ptr* b = tab_; b != tab_ + n_; ++b)
            mpfr_clear(*b);

        delete[] tab_;

    }

    // get result
    typename std::iterator_traits<Iter>::value_type
    result()
    {
        return result_;
    }

private:
    size_t const n_;
    typename std::iterator_traits<Iter>::value_type result_;
    mpfr_ptr* tab_;
};




// sum
template<class Iter>
typename std::iterator_traits<Iter>::value_type
inline sum(Iter begin, Iter end, rnd_mode rnd)
{
    // Typedef for the corresponding mpfr wrapper class representing the IEEE 754 binary floating point format of the iterator value type
    typedef p1788::util::mpfr_var<
    std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::has_denorm != std::denorm_present
        ? std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::min_exponent
        : std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::min_exponent - std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits + 1,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::max_exponent,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::has_denorm == std::denorm_present
        > mpfr_var;

    reduction_sum_op<Iter> op(
        [] (Iter i, mpfr_ptr* p)
    {
        *p = new mpfr_t;

        mpfr_init2(*p, std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits);

        mpfr_var tmp(*i, MPFR_RNDN);

        mpfr_set(*p, tmp(), MPFR_RNDN);
    },
    begin, end, rnd
    );

    return op.result();
}

// sum
template<typename T>
T
inline sum(std::initializer_list<T> l, rnd_mode rnd)
{
    return sum(std::begin(l), std::end(l), rnd);
}


// sum_abs
template<class Iter>
typename std::iterator_traits<Iter>::value_type
inline sum_abs(Iter begin, Iter end, rnd_mode rnd)
{
    // Typedef for the corresponding mpfr wrapper class representing the IEEE 754 binary floating point format of the iterator value type
    typedef p1788::util::mpfr_var<
    std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::has_denorm != std::denorm_present
        ? std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::min_exponent
        : std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::min_exponent - std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits + 1,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::max_exponent,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::has_denorm == std::denorm_present
        > mpfr_var;

    reduction_sum_op<Iter> op(
        [] (Iter i, mpfr_ptr* p)
    {
        *p = new mpfr_t;

        mpfr_init2(*p, std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits);

        mpfr_var tmp(*i, MPFR_RNDN);
        mpfr_abs(tmp(), tmp(), MPFR_RNDN);

        mpfr_set(*p, tmp(), MPFR_RNDN);
    },
    begin, end, rnd
    );

    return op.result();
}

// sum_abs
template<typename T>
T
inline sum_abs(std::initializer_list<T> l, rnd_mode rnd)
{
    return sum_abs(std::begin(l), std::end(l), rnd);
}


// sum_sqr
template<class Iter>
typename std::iterator_traits<Iter>::value_type
inline sum_sqr(Iter begin, Iter end, rnd_mode rnd)
{
    // Typedef for the corresponding mpfr wrapper class representing the IEEE 754 binary floating point format of the iterator value type with twice the mantissa size
    typedef p1788::util::mpfr_var<
    std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits * 2,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::has_denorm != std::denorm_present
        ? std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::min_exponent
        : std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::min_exponent - std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits * 2 + 1,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::max_exponent,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::has_denorm == std::denorm_present
        > mpfr_var;

    reduction_sum_op<Iter> op(
        [] (Iter i, mpfr_ptr* p)
    {
        *p = new mpfr_t;

        mpfr_init2(*p, std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits);

        mpfr_var tmp(*i, MPFR_RNDN);
        mpfr_sqr(tmp(), tmp(), MPFR_RNDN);

        mpfr_set(*p, tmp(), MPFR_RNDN);
    },
    begin, end, rnd
    );

    return op.result();
}

// sum_sqr
template<typename T>
T
inline sum_sqr(std::initializer_list<T> l, rnd_mode rnd)
{
    return sum_sqr(std::begin(l), std::end(l), rnd);
}


// dot
template<class Iter>
typename std::iterator_traits<Iter>::value_type
inline dot(Iter begin_a, Iter end_a, Iter begin_b, rnd_mode rnd)
{
    // Typedef for the corresponding mpfr wrapper class representing the IEEE 754 binary floating point format of the iterator value type with twice the mantissa size
    typedef p1788::util::mpfr_var<
    std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits * 2,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::has_denorm != std::denorm_present
        ? std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::min_exponent
        : std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::min_exponent - std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits * 2 + 1,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::max_exponent,
        std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::has_denorm == std::denorm_present
        > mpfr_var;

    reduction_sum_op<Iter> op(
        [] (Iter a, Iter b, mpfr_ptr* p)
    {
        *p = new mpfr_t;

        mpfr_init2(*p, std::numeric_limits<typename std::iterator_traits<Iter>::value_type>::digits);

        mpfr_var tmp_a(*a, MPFR_RNDN);
        mpfr_var tmp_b(*b, MPFR_RNDN);

        mpfr_mul(tmp_a(), tmp_a(), tmp_b(), MPFR_RNDN);

        mpfr_set(*p, tmp_a(), MPFR_RNDN);
    },
    begin_a, end_a, begin_b, rnd
    );

    return op.result();
}

// dot
template<typename T>
T
inline dot(std::initializer_list<T> a, std::initializer_list<T> b, rnd_mode rnd)
{
    return dot(std::begin(a), std::end(a), std::begin(b), rnd);
}



} // namespace reduction

} // namespace p1788



#endif // LIBIEEEP1788_P1788_REDUCTION_REDUCTION_HPP
