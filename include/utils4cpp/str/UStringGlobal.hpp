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

#ifndef UTILS4CPP_STR_USTRINGGLOBAL_HPP
#define UTILS4CPP_STR_USTRINGGLOBAL_HPP

#include <cwchar>
#include <cuchar>

#include <locale>
#include <string>
#include <string_view>

#include "utils4cpp/core/UCore.hpp"
#include "utils4cpp/core/UTypeTraits.hpp"

namespace utils4cpp::str {

/** Indicates case sensitive or not. */
enum UCaseSensitivity {
    UCaseInsensitive,                ///< Case insensitive.  (no)
    UCaseSensitive                   ///< Case sensitive.    (yes)
};

/**
    Swap char \a a and \a b with no intermediate variable.
*/
template<typename CharT>
inline void uSwapChar(CharT &a, CharT& b) noexcept
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

//
//  convertible to stl-style string traits
//

template<class StringT>
using is_convertible_to_stlstyle_string = u_and<
    std::is_convertible<const StringT&, std::basic_string<
    typename StringT::value_type, typename StringT::traits_type, typename StringT::allocator_type>>,
    u_not<std::is_convertible<const StringT&, const typename StringT::value_type *>>>;

template<class StringT>
inline constexpr bool is_convertible_to_stlstyle_string_v = is_convertible_to_stlstyle_string<StringT>::value;

template<class StringT>
using if_convertible_to_stlstyle_string = std::enable_if_t<
    is_convertible_to_stlstyle_string_v<StringT>, primitive_t<StringT>>;

namespace detail {

template<class StringT, class CharT>
using _is_stlstyle_string = u_and<
    std::is_same<typename StringT::value_type, CharT>,
    std::is_same<StringT, std::basic_string<
    typename StringT::value_type,
    typename StringT::traits_type,
    typename StringT::allocator_type>>>;

template<class StringT, class CharT>
inline constexpr bool _is_stlstyle_string_v = _is_stlstyle_string<StringT, CharT>::value;

template<class StringT, class CharT>
using _if_stlstyle_string = std::enable_if_t<_is_stlstyle_string_v<StringT, CharT>, StringT>;

} // namespace utils4cpp::str::detail

//
// std::basic_string traits
//

template<class StringT>
using is_std_basic_string = detail::_is_stlstyle_string<StringT, typename StringT::value_type>;

template<class StringT>
inline constexpr bool is_std_basic_string_v = is_std_basic_string<StringT>::value;

template<class StringT>
using if_std_basic_string = std::enable_if_t<is_std_basic_string_v<StringT>, StringT>;

//
// std char string traits
//

template<class StringT>
using is_std_char_string = detail::_is_stlstyle_string<StringT, char>;

template<class StringT>
inline constexpr bool is_std_char_string_v = is_std_char_string<StringT>::value;

template<class StringT>
using if_std_char_string = std::enable_if_t<is_std_char_string_v<StringT>, StringT>;

//
// std wchar_t string traits
//

template<class StringT>
using is_std_wchar_string = detail::_is_stlstyle_string<StringT, wchar_t>;

template<class StringT>
inline constexpr bool is_std_wchar_string_v = is_std_wchar_string<StringT>::value;

template<class StringT>
using if_std_wchar_string = std::enable_if_t<is_std_wchar_string_v<StringT>, StringT>;

//
// std char16 string traits
//

template<class StringT>
using is_std_char16_string = detail::_is_stlstyle_string<StringT, char16_t>;

template<class StringT>
inline constexpr bool is_std_char16_string_v = is_std_char16_string<StringT>::value;

template<class StringT>
using if_std_char16_string = std::enable_if_t<is_std_char16_string_v<StringT>, StringT>;

//
// std char32 string traits
//

template<class StringT>
using is_std_char32_string = detail::_is_stlstyle_string<StringT, char32_t>;

template<class StringT>
inline constexpr bool is_std_char32_string_v = is_std_char32_string<StringT>::value;

template<class StringT>
using if_std_char32_string = std::enable_if_t<is_std_char32_string_v<StringT>, StringT>;

//
// std char8_t string traits
//

#if UTILS4CPP_HAS_CHAR8T

template<class StringT>
using is_std_char8_string = detail::_is_stlstyle_string<StringT, char8_t>;

template<class StringT>
inline constexpr bool is_std_char8_string_v = is_std_char8_string<StringT>::value;

template<class StringT>
using if_std_char8_string = std::enable_if_t<is_std_char8_string_v<StringT>, StringT>;

//
// std char string or std char8_t string traits
//

template<class StringT>
using is_std_char_or_char8_string = u_or<is_std_char_string<StringT>, is_std_char8_string<StringT>>;

template<class StringT>
inline constexpr bool is_std_char_or_char8_string_v = is_std_char_or_char8_string<StringT>::value;

template<class StringT>
using if_std_char_or_char8_string = std::enable_if_t<is_std_char_or_char8_string_v<StringT>, StringT>;

#endif // UTILS4CPP_HAS_CHAR8T

//
// std char string or std wchar_t string traits
//

template<class StringT>
using is_std_char_or_wchar_string = u_or<is_std_char_string<StringT>, is_std_wchar_string<StringT>>;

template<class StringT>
inline constexpr bool is_std_char_or_wchar_string_v = is_std_char_or_wchar_string<StringT>::value;

template<class StringT>
using if_std_char_or_wchar_string = std::enable_if_t<is_std_char_or_wchar_string_v<StringT>, StringT>;

} // namespace utils4cpp::str

#endif // UTILS4CPP_STR_USTRINGGLOBAL_HPP