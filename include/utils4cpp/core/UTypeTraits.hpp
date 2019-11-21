/************************************************************************************
**
**  BSD 3-Clause License
**
**  Copyright (c) 2019, shaoguang. All rights reserved.
**
**  Redistribution and use in source and binary forms, with or without
**  modification, are permitted provided that the following conditions are met:
**
**  1. Redistributions of source code must retain the above copyright notice, this
**     list of conditions and the following disclaimer.
**
**  2. Redistributions in binary form must reproduce the above copyright notice,
**     this list of conditions and the following disclaimer in the documentation
**     and/or other materials provided with the distribution.
**
**  3. Neither the name of the copyright holder nor the names of its
**     contributors may be used to endorse or promote products derived from
**     this software without specific prior written permission.
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
**  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
**  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
**  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
**  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
**  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
**  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
**  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
************************************************************************************/

#ifndef UTILS4CPP_CORE_UTYPETRAITS_HPP
#define UTILS4CPP_CORE_UTYPETRAITS_HPP

#include <type_traits>

namespace utils4cpp {

/**
    \brief variadic logical AND metafunction.

    Forms the logical conjunction of the type traits \c B..., effectively performing a 
    logical AND on the sequence of traits.

    \tparam B... every template argument Bi for which \c Bi::value is instantiated must 
    be usable as a base class and define member value that is convertible to bool.
*/
template<class...B>
using u_and = std::conjunction<B...>;

/**
    \brief variadic logical OR metafunction.

    Forms the logical disjunction of the type traits \c B..., effectively performing a 
    logical OR on the sequence of traits.
    
    \tparam B... every template argument Bi for which \c Bi::value is instantiated must 
    be usable as a base class and define member value that is convertible to bool.
*/
template<class...B>
using u_or = std::disjunction<B...>;

/** 
    \brief logical NOT metafunction.

    Forms the logical negation of the type trait \c B.
    
    \tparam B any type such that the expression \c bool(B::value) is a valid constant expression.
*/
template<class B>
using u_not = std::negation<B>;

/** The result of applying the decay type conversions to \b T */
template<class T>
using primitive_t = std::decay_t<T>;

/**
    If \c T is an arithmetic type, \b if_arithmetic has a public member typedef \c type, equal to \c T;
    otherwise, there is no member typedef.
*/
template<class T>
using if_arithmetic = std::enable_if_t<std::is_arithmetic_v<T>, T>;

/**
    Identifies bool types.
    Checks whether \c T is a bool type.
*/
template<class T>
using is_bool = std::is_same<bool, T>;

/**
    Checks if type \c T is a bool type.
    \b is_bool_v equals to \c true if \c T is a bool type, otherwise equals to \c flase.
*/
template<class T>
inline constexpr bool is_bool_v = is_bool<T>::value;

/**
    If \c T is a bool type, \b if_bool has a public member typedef \c type, equal to \c bool;
    otherwise, there is no member typedef.
*/
template<class T>
using if_bool = std::enable_if_t<is_bool_v<T>, T>;

/**
    If \c T is an integral type, \b if_integral has a public member typedef \c type, equal to \c T;
    otherwise, there is no member typedef.
*/
template<class T>
using if_integral = std::enable_if_t<std::is_integral_v<T>, T>;

/**
    If \c T is a floating-point type, \b if_floating_point has a public member typedef \c type, equal to \c T;
    otherwise, there is no member typedef.
*/
template<class T>
using if_floating_point = std::enable_if_t<std::is_floating_point_v<T>, T>;

/**
    Checks whether \c T is an integral type but not a bool type.
*/
template<class T>
using is_integral_not_bool = u_and<std::is_integral<T>, u_not<is_bool<T>>>;

/**
    Checks if type \c T is an integral type but not a bool type.
    \b is_integral_not_bool_v equals to \c true if \c T is an integral type but not a bool type, 
    otherwise equals to \c flase.
*/
template<class T>
inline constexpr bool is_integral_not_bool_v = is_integral_not_bool<T>::value;

/**
    If \c T is an integral type but not a bool type, \b if_integral_not_bool has a public member typedef \c type, 
    equal to \c T; otherwise, there is no member typedef.
*/
template<class T>
using if_integral_not_bool = std::enable_if_t<is_integral_not_bool_v<T>, T>;

/**
    If \c T is a signed arithmetic type, \b if_signed has a public member
    typedef \c type, equal to \c T; otherwise, there is no member typedef.
*/
template<class T>
using if_signed = std::enable_if_t<std::is_signed_v<T>, T>;

/**
    If \c T is a unsigned arithmetic type, \b if_signed has a public member
    typedef \c type, equal to \c T; otherwise, there is no member typedef.
*/
template<class T>
using if_unsigned = std::enable_if_t<std::is_unsigned_v<T>, T>;

/**
    If \c T is a signed integeral type, \b is_signed_interger has a public member
    typedef \c type, equal to \c T; otherwise, there is no member typedef.
*/
template<class T>
using is_signed_integral = std::conjunction<std::is_integral<T>, std::is_signed<T>>;

/**
    Checks if type \c T is a signed integeral type.
    \b is_signed_integeral_v equals to \c true if \c T is a signed interger type, 
    otherwise equals to \c flase.
*/
template<class T>
inline constexpr bool is_signed_integeral_v = is_signed_integral<T>::value;

/**
    If \c T is a signed integeral type, \b if_signed_integeral has a public member
    typedef \c type, equal to \c T; otherwise, there is no member typedef.
*/
template<class T>
using if_signed_integeral = std::enable_if_t<is_signed_integeral_v<T>, T>;

/**
    Checks if type \c T is an unsigned integeral type.\b is_unsigned_interger
    equals to true if \c T is a unsigned integeral type, otherwise equals to flase.
*/
template<class T>
using is_unsigned_integeral = std::conjunction<std::is_integral<T>, std::is_unsigned<T>>;

/**
    Checks if type \c T is an unsigned integeral type.
    \b is_unsigned_integeral_v equals to \c true if \c T is an unsigned integeral type, 
    otherwise equals to \c flase.
*/
template<class T>
inline constexpr bool is_unsigned_integeral_v = is_unsigned_integeral<T>::value;

/**
    If \c T is an unsigned integeral type, \b if_unsigned_integeral has a public member
    typedef \c type, equal to \c T; otherwise, there is no member typedef.
*/
template<class T>
using if_unsigned_integeral = std::enable_if_t<is_unsigned_integeral_v<T>, T>;

}

#endif // UTILS4CPP_CORE_UTYPETRAITS_HPP