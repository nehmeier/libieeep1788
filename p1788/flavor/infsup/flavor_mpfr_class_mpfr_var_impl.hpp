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

#ifndef LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_CLASS_MPFR_VAR_IMPL_HPP
#define LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_CLASS_MPFR_VAR_IMPL_HPP


namespace p1788
{

namespace util
{

template<typename T> class mpfr_get_trait
{
    static_assert(!std::is_same<T,T>::value,
                  "Type is not supported by mpfr_get_trait!");
};

template<> class mpfr_get_trait<float>
{
public:
    static float apply(mpfr_t& mp, mpfr_rnd_t rnd) {
        return mpfr_get_flt(mp, rnd);
    }
};

template<> class mpfr_get_trait<double>
{
public:
    static double apply(mpfr_t& mp, mpfr_rnd_t rnd) {
        return mpfr_get_d(mp, rnd);
    }
};

template<> class mpfr_get_trait<long double>
{
public:
    static long double apply(mpfr_t& mp, mpfr_rnd_t rnd) {
        return mpfr_get_ld(mp, rnd);
    }
};


} // namespace util

} // namespace p1788


namespace p1788
{

namespace flavor
{

namespace infsup
{

template<typename T>
void mpfr_flavor<T>::mpfr_var::setup()
{
    //TODO Check!!!
    //TODO necessary???
    mpfr_set_default_prec(std::numeric_limits<T>::digits);
    mpfr_set_emin(std::numeric_limits<T>::min_exponent);
    mpfr_set_emax(std::numeric_limits<T>::max_exponent);
}



template<typename T>
mpfr_flavor<T>::mpfr_var::mpfr_var()
{
    mpfr_init(var_);
}

template<typename T>
mpfr_flavor<T>::mpfr_var::mpfr_var(float op, mpfr_rnd_t rnd) : mpfr_var()
{
    set(op, rnd);
}

template<typename T>
mpfr_flavor<T>::mpfr_var::mpfr_var(double op, mpfr_rnd_t rnd) : mpfr_var()
{
    set(op, rnd);
}

template<typename T>
mpfr_flavor<T>::mpfr_var::mpfr_var(long double op, mpfr_rnd_t rnd) : mpfr_var()
{
    set(op, rnd);
}

template<typename T>
mpfr_flavor<T>::mpfr_var::~mpfr_var()
{
    mpfr_clear(var_);
}

template<typename T>
void mpfr_flavor<T>::mpfr_var::set(float op, mpfr_rnd_t rnd)
{
    mpfr_set_flt(var_, op, rnd);
}

template<typename T>
void mpfr_flavor<T>::mpfr_var::set(double op, mpfr_rnd_t rnd)
{
    mpfr_set_d(var_, op, rnd);
}

template<typename T>
void mpfr_flavor<T>::mpfr_var::set(long double op, mpfr_rnd_t rnd)
{
    mpfr_set_ld(var_, op, rnd);
}



template<typename T>
T mpfr_flavor<T>::mpfr_var::get(mpfr_rnd_t rnd)
{
    return p1788::util::mpfr_get_trait<T>::apply(var_, rnd);
}



template<typename T>
mpfr_t& mpfr_flavor<T>::mpfr_var::operator() ()
{
    return var_;
}


} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_CLASS_MPFR_VAR_IMPL_HPP
