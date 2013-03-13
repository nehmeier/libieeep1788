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

#ifndef LIBIEEEP1788_P1788_UTIL_VARIADIC_TEMPLATES_HPP
#define LIBIEEEP1788_P1788_UTIL_VARIADIC_TEMPLATES_HPP


namespace p1788
{

namespace util
{



//------------------------------------------------------------------------------
// for_each
//------------------------------------------------------------------------------


template<typename... Args>
class for_each;


/// \brief For each loop over a set of variadic template parameters.
///
template<typename First, typename... Tail>
class for_each<First, Tail...>
{
public:

    /// \brief Applies each element out of the set of variadic template
    /// parameters onto the functor f of type Func.
    ///
    template<typename Func>
    inline static void apply(Func f, First const& first, Tail const& ... tail) {
        f(first);
        for_each<Tail...>::apply(f, tail...);
    }
};

template<>
class for_each<>
{
public:
    template<typename Func>
    inline static void apply(Func f) {
    }
};




//------------------------------------------------------------------------------
// inserter_func
//------------------------------------------------------------------------------

/// \brief Functor to insert different types into a back insert sequence.
///        All types are converted to the type Target.
///
/// \param Target type
/// \param BackInsertIterator iterator
///
///
template<typename Target, typename BackInsertIterator>
class inserter_func
{
private:
    BackInsertIterator iter_;

public:
    inserter_func(BackInsertIterator iter) : iter_(iter) {}

    template<typename T>
    void operator()(T const& x) {
        ++iter_ = static_cast<Target>(x);
    }
};



} // namespace util

} // namespace p1788

#endif // LIBIEEEP1788_P1788_UTIL_VARIADIC_TEMPLATES_HPP
