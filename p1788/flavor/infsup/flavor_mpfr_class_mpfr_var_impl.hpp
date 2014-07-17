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



template<p1788::flavor::infsup::subnormalize SN>
class subnormalization_trait
{
public:
    static void apply(mpfr_t&, int, mpfr_rnd_t) {
        // Nothing to do
    }
};


template<>
class subnormalization_trait<p1788::flavor::infsup::subnormalize::yes>
{
public:
    static void apply(mpfr_t& x, int t, mpfr_rnd_t rnd) {
        mpfr_subnormalize(x, t, rnd);
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

template<typename T, subnormalize SUBNORMALIZE>
void mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::setup()
{

    mpfr_set_default_prec(std::numeric_limits<T>::digits);

    //TODO Ueberarbeiten: normalized/súbnormalized ueber Traits
    if (SUBNORMALIZE == p1788::flavor::infsup::subnormalize::yes)
        mpfr_set_emin(std::numeric_limits<T>::min_exponent - std::numeric_limits<T>::digits + 1);
    else
        mpfr_set_emin(std::numeric_limits<T>::min_exponent);

    mpfr_set_emax(std::numeric_limits<T>::max_exponent);
}



template<typename T, subnormalize SUBNORMALIZE>
mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::mpfr_var()
{
    mpfr_init(var_);
}

template<typename T, subnormalize SUBNORMALIZE>
mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::mpfr_var(unsigned long int op, mpfr_rnd_t rnd) : mpfr_var()
{
    set(op, rnd);
}

template<typename T, subnormalize SUBNORMALIZE>
mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::mpfr_var(long int op, mpfr_rnd_t rnd) : mpfr_var()
{
    set(op, rnd);
}

template<typename T, subnormalize SUBNORMALIZE>
mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::mpfr_var(float op, mpfr_rnd_t rnd) : mpfr_var()
{
    set(op, rnd);
}

template<typename T, subnormalize SUBNORMALIZE>
mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::mpfr_var(double op, mpfr_rnd_t rnd) : mpfr_var()
{
    set(op, rnd);
}

template<typename T, subnormalize SUBNORMALIZE>
mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::mpfr_var(long double op, mpfr_rnd_t rnd) : mpfr_var()
{
    set(op, rnd);
}

template<typename T, subnormalize SUBNORMALIZE>
mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::~mpfr_var()
{
    mpfr_clear(var_);
}

template<typename T, subnormalize SUBNORMALIZE>
void mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::set(unsigned long int op, mpfr_rnd_t rnd)
{
    subnormalize(mpfr_set_ui(var_, op, rnd), rnd);
}

template<typename T, subnormalize SUBNORMALIZE>
void mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::set(long int op, mpfr_rnd_t rnd)
{
    subnormalize(mpfr_set_si(var_, op, rnd), rnd);
}

template<typename T, subnormalize SUBNORMALIZE>
void mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::set(float op, mpfr_rnd_t rnd)
{
    subnormalize(mpfr_set_flt(var_, op, rnd), rnd);
}

template<typename T, subnormalize SUBNORMALIZE>
void mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::set(double op, mpfr_rnd_t rnd)
{
    subnormalize(mpfr_set_d(var_, op, rnd), rnd);
}

template<typename T, subnormalize SUBNORMALIZE>
void mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::set(long double op, mpfr_rnd_t rnd)
{
    subnormalize(mpfr_set_ld(var_, op, rnd), rnd);
}



template<typename T, subnormalize SUBNORMALIZE>
T mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::get(mpfr_rnd_t rnd)
{
    return p1788::util::mpfr_get_trait<T>::apply(var_, rnd);
}

template<typename T, subnormalize SUBNORMALIZE>
std::string mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::get_str(mpfr_rnd_t rnd, int b, size_t n)
{
    mpfr_str str(var_, rnd, b, n);

    return str();
}


template<typename T, subnormalize SUBNORMALIZE>
mpfr_t& mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::operator() ()
{
    return var_;
}


//TODO notwendig?
template<typename T, subnormalize SUBNORMALIZE>
void mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::subnormalize(int t, mpfr_rnd_t rnd)
{
    p1788::util::subnormalization_trait<SUBNORMALIZE>::apply(var_, t, rnd);
}



// TODO current local decimal point!!!!
// TODO Hex etc
// TODO Check
template<typename T, subnormalize SUBNORMALIZE>
mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::mpfr_str::mpfr_str(mpfr_t var, mpfr_rnd_t rnd, int b, size_t n)
    : char_(nullptr), str_()
{
    mpfr_exp_t exp;

    char_ = mpfr_get_str(nullptr, &exp, b, n, var, rnd);
    str_ = char_;

    if (mpfr_regular_p(var)) {
        if (exp > str_.length()) {
            str_.insert(mpfr_sgn(var) > 0 ? 1 : 2, ".");
            str_ = str_ + "e" + std::to_string(exp - 1);
        } else if (exp) {
            str_.insert(mpfr_sgn(var) > 0 ? exp : exp + 1, ".");
        } else {
            str_.insert(mpfr_sgn(var) < 0 ? 1 : 0, "0.");
        }
    }

    if (mpfr_zero_p(var)) {
        if (str_[0] == '-') {
            str_.replace(0, 2, "0.");
        } else {
            str_.insert(1, ".");
        }
    }

    if (mpfr_nan_p(var)) {
        str_ = "nan";
    }

    if (mpfr_inf_p(var)) {
        str_ = mpfr_sgn(var) > 0 ? "Inf" : "-Inf";
    }
}

template<typename T, subnormalize SUBNORMALIZE>
mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::mpfr_str::~mpfr_str()
{
    mpfr_free_str(char_);
}

template<typename T, subnormalize SUBNORMALIZE>
std::string mpfr_flavor<T, SUBNORMALIZE>::mpfr_var::mpfr_str::operator() () const
{
    return str_;
}



} // namespace infsup

} // namespace flavor

} // namespace p1788


#endif // LIBIEEEP1788_P1788_FLAVOR_INFSUP_FLAVOR_MPFR_CLASS_MPFR_VAR_IMPL_HPP
